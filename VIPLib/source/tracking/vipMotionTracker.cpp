#include "vipMotionTracker.h"


vipMotionTracker::vipMotionTracker()
{
	vMO_Global = new vipMovingObject[DEFAULT_MAX_GLOBAL_OBJ_NR];
	for( int i=0; i<DEFAULT_MAX_GLOBAL_OBJ_NR; i++ )
	{
		vMO_Global[i].vMO_Global = vMO_Global;	// weird naming, but just linking each VMO to the "global" array
		vMO_Global[i].Set_Id(i);
		vMO_Global[i].iMaxGlobalObjNr = DEFAULT_MAX_GLOBAL_OBJ_NR;
	}
//adjust here....
	std_error = NULL;
//
	previous_final_labelled = NULL;
	bFirstFrame = true;

	// (optional) Handover support initialization
	handoverCandidatePool = NULL;
	handoverCandidatePoolSize = 0;
}

vipMotionTracker::~vipMotionTracker()
{
	// todo
	// clean
	if( vMO_Global != NULL )
		delete[] vMO_Global;
	if( previous_final_labelled != NULL )
		delete[] previous_final_labelled;
	if( std_error != NULL )
		fclose( std_error );

	// (optional) Handover support: deinitialization
	if( handoverCandidatePool )
		delete[] handoverCandidatePool;
}


/**
* @brief  Tracking proicedure
*
* @param[input] in structure in HSV color space
* @param[depth_yuv] in structure in YUV444 color space				// STEREO ONLY
* @param[imagedepth16data] in structure in some triclops format		// STEREO ONLY
* @param[blobs] in,out structure in YUV444 color space
* @param[frame_nr] in number of current frame
* @return 0 if all right,!=0 else....
*/
#ifdef VMT_STEREOTRACK
int vipMotionTracker::Blob_Tracking( vipFrameHSV* input, unsigned char* rect_yuv, unsigned char* depth_yuv, unsigned short *imagedepth16data, unsigned char* blobs, int frame_nr )
#else
int vipMotionTracker::Blob_Tracking( vipFrameHSV* input, unsigned char* blobs, int frame_nr )
#endif // VMT_STEREOTRACK
{
#ifndef VMT_STEREOTRACK
	unsigned short *imagedepth16data = NULL;
#endif // VMT_STEREOTRACK

	int width = input->width;
	int height = input->height;
	int framesize = width*height;

	// moved in from motion_track()
	unsigned char *labelled = new unsigned char[framesize*3];
	memset(labelled,128,framesize*3);
	memset(labelled,0,framesize);

	int label_nr = ccl_ConnectedComponentLabeling(blobs,labelled,width,height);
	memcpy( blobs,labelled, sizeof(unsigned char)*framesize*3 );
	delete[] labelled;
	labelled = blobs;
	//the ccl function above gives as ouput an image 'labelled'
	//labeled with 'label_nr' sequential label starting from 1 going increasing

	srand( time(NULL) );	//seed for random label generation


	//static array of object found globally in the sequence
	//initialized once in the entire processing, first motion frame
	// MARCOVERZA Moved declaration to global scope
	//static vipMovingObject* Global_Object_array;

	//store the previous final labelled frame
	// MARCOVERZA Moved declaration to global scope
	//static unsigned char* previous_final_labelled;

	vipMovingObject* Local_Object_array = NULL;

	if(label_nr>0)// if there are moving object...
	{
		//allocating memory for found moving objects
		Local_Object_array = new vipMovingObject[label_nr];
		for( int i=0; i<label_nr; i++ )
		{
			//Local_Object_array[i].Reset();
			Local_Object_array[i].vMO_Global = vMO_Global;	// link each one to the global array root
			Local_Object_array[i].iMinBlobSize = this->myParams.iMinBlobSize;	// copy min blob size to locals
			Local_Object_array[i].frmWidth = this->myParams.Width;
			Local_Object_array[i].frmHeight = this->myParams.Height;
		}

		if(previous_final_labelled==NULL) //first frame with moving object..
		{
			//unique array memory allocation..(static structure)
			//memory allocation for global_object array (40 object stored)
			//Global_Object_array = new vipMovingObject[MAX_TRACKABLE_OBJS];

			//set the ID for the global objects
			//for(int i=0;i<MAX_TRACKABLE_OBJS;i++)
			//{
			//	Global_Object_array[i].Set_Id(i);
			//	Global_Object_array[i].Set_Used(false);
			//}

			//memory alloc for the labelled frame..
			previous_final_labelled = new unsigned char[framesize];
			memset(previous_final_labelled,128,framesize);
		}


		//store initial property for each blob
		for(int cont=0; cont < label_nr; cont++)
		{
			//setting up initial attributes for each moving object detected..
			Local_Object_array[cont].Set_input_label((unsigned char)(cont+1));
			Local_Object_array[cont].Set_Id(cont);
			Local_Object_array[cont].Set_Used(true);

			//setup of region Area and allocation of region pixel indexes array
			//in case of too small region IsUsed tic will be set to false
			int retval = Local_Object_array[cont].Set_PixelMap(labelled,width,height,bFirstFrame);
			if(retval==0)
			{
				//calculation of region statistic..(see .cpp file)
				//USE THE ARRAY PIXEL_MAP TO PROCESS THE FRAME!!!!!!!!!!!!!!!!!!!!!!!!
				Local_Object_array[cont].Get_Statistic(input,imagedepth16data);

				//assign to each object the final label 
				Local_Object_array[cont].Set_output_label((unsigned char)(cont+1));//(pow(3.0,cont+1))

				//repaint the region with the final label computed (if big enought)
		//		Local_Object_array[cont].Re_paint_Color(labelled,width,height);

				Local_Object_array[cont].set_Centro_id(width,height);

				Local_Object_array[cont].Presence(true);
				Local_Object_array[cont].Set_last_frame_seen(frame_nr);
			}
			else if(retval==-1)
				Local_Object_array[cont].Erase(labelled,width, height);
			else //if thjere are problem in apixelmap allocation...
			{
				Local_Object_array[cont].Reset();
			}
		}//end for(int cont=0;cont<label_nr;cont++)


		//fusion blob procedure..
		unsigned short disp_diff=0;
		bool overlap = false;

		for( int cont=0; cont < label_nr; cont++)
			if(Local_Object_array[cont].Is_Used()==true)
			{
				for(int cont1=0; cont1 < label_nr; cont1++)
					if(cont1 != cont)
					{
						overlap = Local_Object_array[cont].overlap( &Local_Object_array[cont1] );
						if(Local_Object_array[cont1].Is_Used()==true && overlap==true)
						{
							if(Local_Object_array[cont].Update_Pixel_Map( &Local_Object_array[cont1] )==0)
							{
								Local_Object_array[cont].Get_Statistic(input,imagedepth16data);
								Local_Object_array[cont1].Set_Used(false);
								cont1=0;//counter reset..
							}
							else
								Local_Object_array[cont].Erase(labelled,width, height);
						}
					}

					// Local_Object_array[cont].Re_paint_Color(labelled,width,height);
					int c_id = Local_Object_array[cont].set_Centro_id(width,height);

			} //end 'if(Local_Object_array[cont].Is_Used()==true)'



			//here drag the label(s) of the overlapped region(s) in the previous frame..
			//do the draggin only if we are not at the first frame of the sequence
			if(bFirstFrame == false) 
				for( int cont=0; cont < label_nr; cont++)
					if(Local_Object_array[cont].Is_Used()==true)

					{
						int out=0;
						int te=Local_Object_array[cont].drag_label(labelled,previous_final_labelled);
						//te = 0 is the normal case...means one overlapped object found in the prev_lab frame 
						
						//temporally commented by NP
						//out=255;

						//////////////////////// HAND OVER (optional) SUPPORT	///////////
						// Check if hand over can be performed
						bool bHandedOver = false;	// used to avoid the handed over object to be further checked for other ID/label assignments
						if( this->handoverCandidatePool != NULL )
						{
							// try the hand over 
							if( 0 /* tryHandOver(...)*/ ) // TODO: hand over. va fatto a basso livello, tutta l'intelligenza su topologia del tunnel va fuori da qui. qui solo confronti semplici sul pool di candidati pre-preparati per questa specifica istanza di tracker!
							{
								// ...

								// set the handover HOOK to the position in the sharedStorage, so it is NOT added as new vmo in the next retrieveData()
								Local_Object_array[cont].iHandOverHook = -1;	// <-- TODO : SET TO THE POS

								// hand over done: set the flag
								bHandedOver = true;
							}

						}
						/////////////////// End of HAND OVER (optional) SUPPORT	///////////

						//else
						if( te == 1 && !bHandedOver )
						{
							/**
							Have a look to this function..it doesn't do exactly what we want (it required a module to recover the tracked obj
							in case of frame dropping)
							*/
							// try to drag from nearest object
							out = Local_Object_array[cont].get_Spatial_nearest_label(width,height);
							fprintf(std_error,"\t\t:::Warning(%d):Try assigning label via nearest neighborhood to object Local_ID=%d..\n",out,Local_Object_array[cont].Get_Id()); 
						}


						if( te == 1 && out == 255  && !bHandedOver )  //means new obj is entering the scene..
						{
							srand ( time(NULL) );	//uncommented on 0304
							Local_Object_array[cont].Set_output_label(rand()%256);
						}
						if(te == 2  && !bHandedOver )	//special obj
						{ //check if the involved objs are already special
							//if so update the stat (fused_label_nr, fused_label)
							unsigned char* lbl_pt = Local_Object_array[cont].Get_fused_label();
							int gbl0 = vMO_Global->Get_Global_ID(lbl_pt[0],vMO_Global->iMaxGlobalObjNr,vMO_Global);
							int gbl1 = vMO_Global->Get_Global_ID(lbl_pt[1],vMO_Global->iMaxGlobalObjNr,vMO_Global);

							if(vMO_Global[gbl0].Is_special()==true)
							{
								Local_Object_array[cont].Update_fused_label(vMO_Global,gbl0);
							}
							else
								if(vMO_Global[gbl1].Is_special()==true)
								{
									Local_Object_array[cont].Update_fused_label(vMO_Global,gbl1);
								}

						}

						//try to disjoint the special object using depth histogram based thredsolding
						/* if(te==2)
						Local_Object_array[cont].DisJoint_Special(Global_Object_array,input,imagedepth16.data,labelled,previous_final_labelled);
						else*/
						// Local_Object_array[cont].Re_paint_Color(labelled,width,height);


					}	//end  if(Local_Object_array[cont].Is_Used()==true)

					// check if there are multiple object with the same output label..
					unsigned char lf;
					unsigned char* loc_array = new unsigned char[label_nr];
					bool do_discriminate = false;
					int occlusion_nr = 0;
					unsigned char* occlusion_label = new unsigned char[4];	//label duplicated array

					for(int cont=0; cont < label_nr; cont++)
						if(Local_Object_array[cont].Is_Used() == true)
						{
							lf = Local_Object_array[cont].Get_Output_label(0);
							if(vipMovingObject::array_cmp(loc_array,label_nr,lf) == 1)	//means there are multiple object with the same label..
							{
								do_discriminate = true;
								occlusion_label[occlusion_nr] = lf;
								occlusion_nr++;
							}
							else
								loc_array[cont] = lf;

						}

						if(do_discriminate == true)
							for(int oc = 0;oc < occlusion_nr;oc++)
								Discriminate(Local_Object_array,vMO_Global,occlusion_label[oc],label_nr);


						// (Comment added by MV:
						// I think this should be the point where processing is completed
						// and results are then stored into tracker globals)

						// so I should be able to do stuff here:
						// Add current centroid to trajectory
						unsigned int x=0, y=0, z=1;
						for(int cont=0; cont < label_nr; cont++)
						{
							if(Local_Object_array[cont].Is_Used() == true)
							{
								x = Local_Object_array[cont].get_Centro_id() % Local_Object_array[cont].frmWidth;
								y = Local_Object_array[cont].get_Centro_id() / Local_Object_array[cont].frmWidth;
								Local_Object_array[cont].m_pBlobTrajectory->addPoint( &x, &y, &z );
							}
						}


						for(int cont=0; cont < label_nr; cont++)
						{
							if(Local_Object_array[cont].Is_Used() == true)
							{
								Local_Object_array[cont].Re_paint_Color(labelled,width,height);
								Local_Object_array[cont].copy_to(vMO_Global, bFirstFrame );
							}
						}


						// TRAJECTORY UPDATE - added by MV on 23/07/2008
						//updateGlobalTrajectories();	// traj are updated in locals and then copied to tracker globals. so this should not be done
						// End of trajectory update



						//first_frame 
						if(bFirstFrame==true)
							bFirstFrame=false;

						//copy the final labelled frame to static structure..
						memcpy(previous_final_labelled,labelled,sizeof(unsigned char)*framesize);


						delete[] loc_array;
						delete[] occlusion_label;
						delete[] Local_Object_array;


	} //end if(label_nr>0)



	return 0;
}



/**
* @brief  discriminate beetween obj after occlusion
*
* @param[Local_array] input local_array_object 
* @param[Global_array] input global_array_object
* @param[lbl]input label of fused global
* @return 0
*/
int vipMotionTracker::Discriminate(vipMovingObject* Local_array,vipMovingObject* Global_array,unsigned char lbl,int nr_lbl)
{

	int Global_ID = vipMovingObject::Get_Global_ID(lbl,Global_array->iMaxGlobalObjNr,Global_array);
	//printf("Corrispondent Global_Object_ID = %d!!\n",Global_ID);

	if( Global_ID == -1 )
	{
		// Currently this is a BUG. Must be corrected
		printf("\nBUG in vipMotionTracker::Discriminate(): Preventing crash but NOT working as intended.\n");
		return 0;
	}

	if(Global_array[Global_ID].Is_special()==true)
	{
		//retrieve the fused object label information
		int nr_fused_obj = Global_array[Global_ID].Get_fused_label_nr();
		unsigned char* lbl_fused_obj = Global_array[Global_ID].Get_fused_label();

		//retrieve global obj ID's corrispondent to fused lbl
		int* fused_obj_GLOBAL_ID = new int[nr_fused_obj];

		//here we store the ID of local object that creates the label duplication warning..
		//indead we need for their Pixel_Map to make a decision between object (Global & Local)
		int* fused_obj_LOCAL_ID = new int[nr_fused_obj];

		//printf("\nFused Global Object ID = ");

		//for the Global...
		for(int cont=0;cont<nr_fused_obj;cont++)
			fused_obj_GLOBAL_ID[cont]= vipMovingObject::Get_Global_ID(lbl_fused_obj[cont],Global_array->iMaxGlobalObjNr,Global_array);

		//need to scan ALL local_array to find right ones..
		int index=0;
		for(int cont=0;cont<nr_lbl;cont++)
			if(Local_array[cont].Get_Output_label(0)==lbl)
			{
				fused_obj_LOCAL_ID[index]=Local_array[cont].Get_Id();
				index++;
			}


			//now call the function to make an histogram-based discriminance
			//the ID's of object to compare are stored in fused_obj_LOCAL_ID & fused_obj_GLOBAL_ID
			//substancially we procede making an histogram intersection normalized 
			//(result in range 0-1)
			float k =0;
			float h =0;
			int G_ID_choosen = 0;
			int G_ID_choosen_i = 0;
			int ID_choosen = 0;
			int ID_choosen_j = 0;

			int Loc_ID;
			int Glob_ID;

			for(int i=0;i<nr_fused_obj;i++)//scroll Global
			{			
				//REVIEW DISCRIMINATION FUNCITON
				for(int j=0;j<2;j++)//scroll the Local
					if(fused_obj_LOCAL_ID[j]>=0)
					{
						h = Global_array[fused_obj_GLOBAL_ID[i]].Hist_Intersection(&Local_array[fused_obj_LOCAL_ID[j]]);
						fprintf(std_error,"                                                              \n");
						fprintf(std_error,"Similarity between Global[%d]-Local[%d]==>[ %f ]\t\t\t\t\t\t\t\t\t\t\t\t\n",fused_obj_GLOBAL_ID[i],fused_obj_LOCAL_ID[j],h);

						if(h > k)
						{
							ID_choosen = fused_obj_LOCAL_ID[j];//ID of LOCAL_OBJ "corrispondent" to GLOBAL_OBJ[i]
							ID_choosen_j = j;
							
							G_ID_choosen = fused_obj_GLOBAL_ID[i];//
							G_ID_choosen_i = i;
							k=h;
						}
					}//end for(..) Local scroll
			}//end for(..) Global scroll..

			fprintf(std_error,"                             \n");
			fprintf(std_error,"G_ID_choosen= [%d](%d)..\t\t\t\t\t\t\n",G_ID_choosen,G_ID_choosen_i);
			fprintf(std_error,"ID_choosen= [%d](%d)..\t\t\t\t\t\t\n",ID_choosen,ID_choosen_j);
			fprintf(std_error,"Histogram intersection score = [%f]..\t\t\t\t\t\t\n",k);
			fprintf(std_error,"                             \n");

			//only for repaint right color..
			Local_array[ID_choosen].Set_output_label(Global_array[G_ID_choosen].Get_Output_label(0));
		
			if(nr_fused_obj==2)//update the stat for the other local object in the scene
			{
				Loc_ID = (ID_choosen_j == 1) ? 0 : 1;
				Glob_ID = (G_ID_choosen_i == 1) ? 0 : 1;

				Local_array[fused_obj_LOCAL_ID[Loc_ID]].Set_output_label( Global_array[fused_obj_GLOBAL_ID[Glob_ID]].Get_Output_label(0) );
			
				fprintf(std_error,"Info about the remaining object..\n");
				fprintf(std_error,"LocID = %d\n",Loc_ID);
				fprintf(std_error,"GlobID = %d\n",Glob_ID);
			
			}
			else
				if(nr_fused_obj > 2)
				{//update the remaining SPECIAL objs
					int index=0;
					unsigned char* fused_label = new unsigned char[nr_fused_obj-1];
					for(int e=0; e<nr_fused_obj; e++)
						if(Global_array[fused_obj_GLOBAL_ID[e]].Get_Output_label(0)!=Global_array[G_ID_choosen].Get_Output_label(0) )
						{
							fused_label[index] = Global_array[fused_obj_GLOBAL_ID[e]].Get_Output_label(0);
							index++;
						}
					Global_array[Global_ID].Set_Special(index, fused_label);
				}


				//}//end for(..) Global scroll..

				//getchar();

				//to remove..maybe..
				/*for(int i=0;i<nr_fused_obj;i++)//scroll the Local..
				{
				float k = 0;
				float h = 0;
				int ID_choosen=0;	 //most PROBABLE Global ID..


				for(int j=0;j<nr_fused_obj;j++)//scroll the Global..
				{
				h = Local_array[fused_obj_LOCAL_ID[i]].Hist_Intersection(Global_array[fused_obj_GLOBAL_ID[j]]);
				printf("                                                              \n");
				printf("Similarity between Local[%d]-Global[%d]==>[ %f ]\t\t\t\t\t\t\t\t\t\t\t\t\n",fused_obj_LOCAL_ID[i],fused_obj_GLOBAL_ID[j],h);

				if(h > k)
				{
				ID_choosen = fused_obj_GLOBAL_ID[j];//ID of Global_OBJ corrispondent to Local_OBJ[i]
				k=h;
				}


				}//end for(j..)Global scroll..
				printf("                             \n");
				printf("ID_choosen= [%d]..\t\t\t\t\t\t\n",ID_choosen);
				printf("                             \n");
				//getchar();

				//here going to update the corrispondent Global_obj with info retrieved from Local_obj[i]

				//only for repaint right color..
				Local_array[fused_obj_LOCAL_ID[i]].Set_output_label(Global_array[ID_choosen].Get_Output_label());
				//printf("*****%d******\n",Local_array[i].Get_PixelMap()[0]);
				//Local_array[fused_obj_LOCAL_ID[i]].Re_paint_Color(input,320,240);

				Global_array[ID_choosen].Set_Used(true);
				Global_array[ID_choosen].Set_PixelMap(Local_array[fused_obj_LOCAL_ID[i]].Get_PixelMap());
				Global_array[ID_choosen].Set_area(Local_array[fused_obj_LOCAL_ID[i]].Get_area());

				Global_array[ID_choosen].set_H_mean(Local_array[fused_obj_LOCAL_ID[i]].get_H_mean());
				Global_array[ID_choosen].set_H_hist(Local_array[fused_obj_LOCAL_ID[i]].get_H_hist());

				//Global_array[ID_choosen].Re_paint_Color(input,320,240);




				//

				}//end for(i..)Local scroll..*/


				delete[] fused_obj_GLOBAL_ID;
				delete[] fused_obj_LOCAL_ID;
	}
	else
	{//if the object is not special maybe a problem
		//or simply a normal blob that split..
		//  printf("\n\t:::WARNING:IsSpecial Check NOT passed in Discriminating function:::\n"); //getchar();
		//  printf("\t\t:::Global object [%d] is not SPECIAL:::\n",Global_ID);
		fprintf(std_error,"\n\t\t:::WARNING:IsSpecial Check NOT passed in Discriminating function:::\n");
		fprintf(std_error,"\t\t:::Global object [%d] is not SPECIAL:::\n",Global_ID);
	}

	return 0;
}


/*
* @brief Used to free up old global objects
*/
int vipMotionTracker::cleanOldGlobals( int current_frame_num )
{
	int erased = 0;
	for( int i=0; i<DEFAULT_MAX_GLOBAL_OBJ_NR; i++ )
	{
		if( vMO_Global[i].Is_Used() && abs( vMO_Global[i].nr_last_frame - current_frame_num ) > 10 )
		{
			vMO_Global[i].Set_Used(false);
			vMO_Global[i].Reset();
			erased++;
		}
	}
	return erased;
}


VIPRESULT vipMotionTracker::updateGlobalTrajectories()	// todo: make 3d version with #define ? 
{
	if( vMO_Global == NULL )
		return VIPRET_ILLEGAL_USE;

	// cycle globals
	unsigned int x=0, y=0, z=1;
	for( int i=0; i<vMO_Global->iMaxGlobalObjNr; i++ )
	{
		if( vMO_Global[i].Is_Used() )
		{
			x = vMO_Global[i].get_Centro_id() % myParams.Width;
			y = vMO_Global[i].get_Centro_id() / myParams.Height;
			vMO_Global[i].m_pBlobTrajectory->addPoint(&x, &y, &z);
		}
	}

	return VIPRET_OK;
}



// end of vipMotionTracker implementation. below are parameters and CCL stuff.


// parameters //

vipMotionTrackerParameters::vipMotionTrackerParameters()
{
	Width = 0;
	Height = 0;
	iMinBlobSize = 0;
}
vipMotionTrackerParameters::~vipMotionTrackerParameters()
{
}

VIPRESULT vipMotionTrackerParameters::saveToStreamXML(FILE *f)
{ return VIPRET_NOT_IMPLEMENTED; }

VIPRESULT vipMotionTrackerParameters::loadFromStreamXML(FILE *f)
{ return VIPRET_NOT_IMPLEMENTED; }


//////////////////////// Connected Component Labeling procedures
static int SearchDirection[8][2] = {{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1}};

void vipMotionTracker::ccl_Tracer(unsigned char* bitmap, int*labelmap, int *cy, int *cx, int *tracingdirection, int width, int height )
{
	int i, y, x, c;

	for(i = 0; i < 7; i++)
	{
		y = *cy + SearchDirection[*tracingdirection][0];
		x = *cx + SearchDirection[*tracingdirection][1];

		c = y*width+x;
		if(bitmap[c] == 0)//was '0'
		{
			labelmap[c] = -1;
			*tracingdirection = (*tracingdirection + 1) % 8;
		}
		else
		{
			*cy = y;
			*cx = x;
			break;
		}
	}
}

void vipMotionTracker::ccl_ContourTracing(unsigned char* bitmap, int* labelmap,int cy, int cx, int labelindex, int tracingdirection, int width, int height )
{
	char tracingstopflag = 0, SearchAgain = 1;
	int c,fx, fy, sx = cx, sy = cy;

	ccl_Tracer(bitmap,labelmap,&cy, &cx, &tracingdirection, width, height);
	

	if(cx != sx || cy != sy)
	{
		fx = cx;
		fy = cy;

		while(SearchAgain)
		{
		c=cy*width+cx;
			tracingdirection = (tracingdirection + 6) % 8;
			labelmap[c] = labelindex;
			ccl_Tracer(bitmap,labelmap,&cy, &cx, &tracingdirection, width, height);
			
			if(cx == sx && cy == sy)
			{
				tracingstopflag = 1;
			}
			else if(tracingstopflag)
			{
				if(cx == fx && cy == fy)
				{
					SearchAgain = 0;
				}
				else
				{
					tracingstopflag = 0;
				}
			}
		}
	}
}

int vipMotionTracker::ccl_ConnectedComponentLabeling(unsigned char* bitmap, unsigned char *labelmap_, int width, int height)
{
	int c,cx, cy, tracingdirection, ConnectedComponentsCount = 0, labelindex = 0;
	int framesize = width*height;
	
	int* labelmap = new int[framesize*3];
	memset(labelmap,0,sizeof(int)*framesize*3);

	for(cy = 1; cy < height - 1; cy++)
	{
		for(cx = 1, labelindex = 0; cx < width - 1; cx++)
		{
		
			c = cy*width+cx;
			if(bitmap[c] == 255)// black pixel=was1
			{
				if(labelindex != 0)// use pre-pixel label
				{
					labelmap[c] = labelindex;
				}
				else
				{
					labelindex = labelmap[c];

					if(labelindex == 0)
					{
						labelindex = ++ConnectedComponentsCount;
						tracingdirection = 0;
						ccl_ContourTracing(bitmap,labelmap,cy, cx, labelindex, tracingdirection, width, height);// external contour
						labelmap[c] = labelindex;
					}
				}
			}
			else if(labelindex != 0)// white pixel & pre-pixel has been labeled
			{
				if(labelmap[c] == 0)
				{
					tracingdirection = 1;
					ccl_ContourTracing(bitmap,labelmap,cy, cx - 1, labelindex, tracingdirection, width, height);// internal contour
				}

				labelindex = 0;
			}
		}
	}

		
		
	for(int i =0; i<width*height;i++)//set the final label (color if there are more than 255 levels (blobs))
	{
		labelmap_[i] = (labelmap[i]>0) ? (unsigned char)(labelmap[i]%255)  : 0 ;
		labelmap_[i+framesize] = (unsigned char)((labelmap[i]/255)+128);
		labelmap_[i+2*framesize] = labelmap_[i+framesize];
	}

	delete[] labelmap;

	return ConnectedComponentsCount;
}

// end of ccl stuff




////////////////// Hand-over utils //////////////

