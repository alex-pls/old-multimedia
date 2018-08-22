////// vipMotionTracker.cpp
////// Independent module version of the Motion Tracker formerly part of SterTrack by Nicola Piotto.
//
// FILES:	vipMotionTracker.cpp	(this)
//			vipMotionTracker.h
//
// USAGE:	Add both files to your project.
//			Define/Undefine VMT_STEREOTRACK in the header as needed.
//			Define "options" in vipMotionTracker.h.
//			Include header in your code and compile.
//			Match externals as needed (see below).
//			Call Blob_Tracking() each frame.
//			Call CleanUp() after the end of processing, before exiting app.
//
// INPUT:	vipFrameHSV		*input,			// Original frame to process, in HSV color space, width w, height h.
//			unsigned char	*depth_yuv,		// Depth information for stereo processing only. Size: w*h*3?
//			unsigned short	*imagedepth16,	// Depth information for stereo processing only. Should be taken
//											// from PGR stuff, like TriclopsImage16.data.
//			unsigned char	*blobs,			// Size=w*h*3, planar YUV444 format. As input, it should be passed with Y plane
//											// marking 0 (non-moving) and 255 (moving) at pixel positions where movement
//											// has been detected by some background subtraction procedure. As output, it is
//											// a YUV444 planar framedata with differently coloured moving blobs.
//			int				*frame_nr		// Number of current frame, kinda self explaining. Try to be sequential, else
//											// it won't work. Ever.
//
// OTHER:	IMPORTANT:
//			YOU MUST CALL CleanUp() after the end of processing, before exiting app.
//
// TODO:	- Make procedure robust and secure.
//			- Handle global objects so to not run out of free global objects or memory (trash those not used for a long time).
//			- Optimize code to run faster and with less mem.
//			- Match vipLib structures and integrate into lib?


#include "vipMotionTracker.h"

// Globals, externals
extern FILE*		std_error;
extern unsigned int uiImage;
static vipMovingObject* Global_Object_array;
static bool first_frame = true;
static unsigned char* previous_final_labelled = NULL;


#ifdef VMT_STEREOTRACK
extern FILE** track_3d;
extern TriclopsContext tri_context;
#endif	// VMT_STEREOTRACK





//////////////////////// Connected Component Labeling procedures
static int SearchDirection[8][2] = {{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1}};

void Tracer(unsigned char* bitmap, int*labelmap, int *cy, int *cx, int *tracingdirection, int width, int height )
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

void ContourTracing(unsigned char* bitmap, int* labelmap,int cy, int cx, int labelindex, int tracingdirection, int width, int height )
{
	char tracingstopflag = 0, SearchAgain = 1;
	int c,fx, fy, sx = cx, sy = cy;

	Tracer(bitmap,labelmap,&cy, &cx, &tracingdirection, width, height);
	

	if(cx != sx || cy != sy)
	{
		fx = cx;
		fy = cy;

		while(SearchAgain)
		{
		c=cy*width+cx;
			tracingdirection = (tracingdirection + 6) % 8;
			labelmap[c] = labelindex;
			Tracer(bitmap,labelmap,&cy, &cx, &tracingdirection, width, height);
			
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

int ConnectedComponentLabeling(unsigned char* bitmap, unsigned char *labelmap_, int width, int height)
{
	int c,cx, cy, tracingdirection, ConnectedComponentsCount = 0, labelindex = 0;
	
	int* labelmap = new int[width*height*3];
	memset(labelmap,0,sizeof(int)*width*height*3);

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
						ContourTracing(bitmap,labelmap,cy, cx, labelindex, tracingdirection, width, height);// external contour
						labelmap[c] = labelindex;
					}
				}
			}
			else if(labelindex != 0)// white pixel & pre-pixel has been labeled
			{
				if(labelmap[c] == 0)
				{
					tracingdirection = 1;
					ContourTracing(bitmap,labelmap,cy, cx - 1, labelindex, tracingdirection, width, height);// internal contour
				}

				labelindex = 0;
			}
		}
	}

		
		
	for(int i =0; i<width*height;i++)//set the final label (color if there are more than 255 levels (blobs))
		{
			labelmap_[i] = (labelmap[i]>0) ? (unsigned char)(labelmap[i]%255)  : 0 ;
			labelmap_[i+width*height] = (unsigned char)((labelmap[i]/255)+128);
			labelmap_[i+2*width*height] = labelmap_[i+width*height];
		}

	delete[] labelmap;

	return ConnectedComponentsCount;
	}

// end of ccl stuff






/**
* @brief  Setup the pixel map for the object
*
* @param[input] input labelled img (with blob_labelling(...)) 
* @param[width.height] input img dimension 
* @return 0
*/
int vipMovingObject::Set_PixelMap(unsigned char* input,int width,int height,bool first_frame)
{
	//this routine has been adjusted to work with 'realloc'
	this->Area = 0;
	this->Countour_lenght = 0;
	int index=0;
	this->Pixel_map = NULL;

	unsigned char input_lbl = this->Get_input_label();
	
	input_lbl = input_lbl%255;
	unsigned char U_lbl = (input_lbl/255)+128;//handle (possible) color label
	
	//Area calculation and pixel map definition
	for(int cont=0;cont<height*width;cont++)
		if(input[cont]==input_lbl && input[cont+width*height]==U_lbl)
		{
			this->Area++;//lenght of pixel_map
			this->Pixel_map = (int*) realloc (this->Pixel_map, this->Area*sizeof(int));
			this->Pixel_map[this->Area-1] = cont;
		}

		//flag the smallest regions as not in use..
		if(first_frame==false) //due to initial motion problem
			if(this->Area < MIN_BLOB_SIZE)//remove too small objects
			{
				this->Set_Used(false);
				return -1;
			}

			return 0;
}

int vipMovingObject::Update_Pixel_Map(vipMovingObject object)
{
	int area = object.Get_area();

	int orig_area = this->Get_area();
	int new_area = orig_area+area;

	this->Pixel_map = (int*) realloc(this->Pixel_map,new_area*sizeof(int));

	memcpy(Pixel_map+orig_area,object.Get_PixelMap(),sizeof(int)*area);
	this->Area = new_area;

	//setup disp16 value..
	disp16=int(orig_area*disp16+area*object.get_Disparity16())/new_area;
	disparity = unsigned char( disp16>>4 );

	//setup bounding box struct
	Bounding_box[0] = min(Bounding_box[0],object.get_BBox(0));
	Bounding_box[1] = max(Bounding_box[1],object.get_BBox(1));
	Bounding_box[2] = min(Bounding_box[2],object.get_BBox(2));
	Bounding_box[3] = max(Bounding_box[3],object.get_BBox(3));

	/*if(new_area < MIN_BLOB_SIZE)
	{
		this->Set_Used(false);
		return -1;
	}*/

	return 0;
}



/**
* @brief  Setup statistic for the object
*
* @param[original] input original img (no labelled) 
* @return 0
*/
int vipMovingObject::Get_Statistic(vipFrameHSV* original,unsigned short* depth16)
{

	int index = -1;
	int tmp = 0;
	float H_value=0;   //support variable
	int depth_sum = 0;

	//the indexes of pixel region is store in Pixel_map..
	//we do not need to scan the entire frame

	//original is in HSV color space...

	for(int cont=0; cont < this->Get_area(); cont++)
	{
		//calling the statistics retrieve module which works on original data frame (HSV)
		//giving as result the statistic of the region(for now the mean + hist of H component)
		index = this->Pixel_map[cont];
		H_value = original->data[index].hue;   //NB:original[cont] is the Hue component of the pixel..
		H_mean += H_value;	   
		H_hist[(int)H_value]+=1;

#ifdef VMT_STEREOTRACK
		if( depth16 == NULL )
			printf("WARNING: Get_Statistic used in STEREO conf but depth==NULL.\n");
		if(depth16[index]<0xFF00 && depth16[index]>0x0000)
		{ 
			tmp++;
			depth_sum+= int(depth16[index]);
			D_hist[depth16[index]>>4]+=1;
		}
#endif	//VMT_STEREOTRACK
	}

	//H_hist normalization[0-1]..
	for(int cont=0;cont<361;cont++)
		H_hist[cont]/=this->Get_area();

	H_mean /= this->Get_area();	//mean value of H in the considered region - MovingObject

	if(tmp>0)
	{
		disp16 = unsigned short(int(depth_sum) / tmp);
		disparity = unsigned char( disp16 >> 4 );
	}
	else
	{
		disp16 = 0xFFFF;
		disparity = 255;
	}

	return 0;
}




/**
* @brief  Repaint the object
*
* @param[input] input frame to repaint 
* @return 0
*/
int vipMovingObject::Re_paint(unsigned char* input)
{
	for(int cont=0; cont<this->Get_area(); cont++)
	{
		int index = this->Pixel_map[cont];

		if(input[index]==this->Get_input_label())
			input[index]=(this->Get_Output_label(0));

	}

	return 0;
}


/**
* @brief  Repaint the object (in color)
*
* @param[input] input frame to repaint (must be 3 color plane)
* @param[width.height] frame dimension
* @return 0
*/
int vipMovingObject::Re_paint_Color(unsigned char* input,int width,int height)
{
	if(this->Is_Used()==true)

		for(int cont=0; cont<this->Get_area(); cont++)
		{
			int index = this->Pixel_map[cont];
			
			input[index]	=	this->Get_Output_label(0);
			input[index+width*height]	=	this->Get_Output_label(1);
			input[index+2*width*height]	=	this->Get_Output_label(2);

		}

		return 0;
}


/**
* @brief  Repaint the object (in black)
*
* @param[input] input frame to repaint (must be 3 color plane)
* @param[width.height] frame dimension
* @return 0
*/
int vipMovingObject::Erase(unsigned char* input, int width,int height)
{
	this->In_Use = false;	// Line added by Marco Verza & Nicola Piotto on 15/04/2008
	for(int cont=0; cont<this->Get_area(); cont++)
	{
		int index = this->Pixel_map[cont];
		if(/*input[index]==this->Get_Output_label() && */this->Is_special()==false)
		{
			input[index]=(unsigned char)0;
			input[index+width*height]=(unsigned char)128;
			input[index+2*width*height]=(unsigned char)128;
		}

	}

	return 0;
}




/**
* @brief  drag the label to object from prev frame
*
* @param[input] input labelled img  
* @param[fin_lab] input previous labelled img  
* @return 0 if operation ok, else 1
*/
int vipMovingObject::drag_label(unsigned char* input, unsigned char* fin_lab)
{

	//label found array (at the same position of actual region in the previous frame)
	unsigned char* label_found = new unsigned char[this->Get_area()];
	int index = 0;//nr of label found in the fin_lab frame
	int map = 0;

	for(int cont=0; cont<this->Get_area(); cont++)
	{
		map = this->Pixel_map[cont];
		if(input[map]!=0 && fin_lab[map]!=0)
			if(array_cmp(label_found,index,fin_lab[map])==0)
				//store each different label once
			{
				label_found[index] = fin_lab[map];
				index++;

			}
	}


	if(index==0)
	{
		//new object in the scene..
		//no corrisponding region in the prev_fin_lab
		delete[] label_found;
		return 1;
	}

	else if(index==1)//one object in the overlapped region..
	{
		//set the label equal to object found one..
		this->Set_output_label(label_found[0]);
		delete[] label_found;
		return 0;
	}

	else if(index==2)//case of fused object
	{
		//set the special tic on the actual object on stre the fused label
		this->Set_Special(index,label_found);

		//added 17/03
		srand( (label_found[0]+label_found[1])*time(NULL) );
		this->Set_output_label(rand()%256);

		delete[] label_found;

		return 2;
	}
	else
		return -1;
}


/**
* @brief  drag the spatial nearest label to object from prev frame
*
* @param[Global_Object_array] input global object array  
* @return the nearest label to the object
*/
unsigned char vipMovingObject::get_Spatial_nearest_label(vipMovingObject* array, int width, int height )
{
	int c_id = this->get_Centro_id();
	int th = width*height;
	unsigned char nearest_label=0;

	int col = c_id%width;
	int row = c_id/width;
	// boundaries for centroid						// when 320x240 only, these were:
	int left_bound = (int) float(width) * 0.2;		// 64
	int right_bound = (int) float(width) * 0.8;		// 256
	int top_bound = (int) float(height) * 0.2;		// 48
	int bottom_bound = (int) float(height) * 0.8;	// 192



	if(col>left_bound && col<right_bound && row>top_bound && row<bottom_bound)
	{
		for(int cont = 0; cont < MAX_GLOBAL_OBJ_NR; cont++)
		{
			int arr_cid = array[cont].get_Centro_id();
			if(arr_cid >= 0)
				if( abs( arr_cid - c_id) < th )
				{
					th = abs(arr_cid - c_id);
					nearest_label = array[cont].Get_Output_label(0);
				}

		}
		if(nearest_label>0)
			this->Set_output_label(nearest_label);

		return nearest_label;
	}
	else
		return 255;


}

/**
* @brief  drag the depth nearest label to object from prev frame
*
* @param[array] input object array (the legnth for now is 2)
* @return the nearest label to the object
*/
unsigned char vipMovingObject::get_Depth_nearest_label(vipMovingObject* array)
{
	unsigned short disp16 = this->get_Disparity16();
	unsigned char nearest_lbl = 0;
	int th = 65535;//0xFFFF

	for(int i=0; i<2; i++)
	{
		unsigned short arr_disp16 = array[i].get_Disparity16();
		if(arr_disp16 < 0xFF00)
			if( abs(disp16-arr_disp16) < th )
			{
				th = abs(disp16-arr_disp16);
				nearest_lbl = array[i].Get_Output_label(0);
			}
	}

	if(nearest_lbl > 0)
		this->Set_output_label(nearest_lbl);

	return nearest_lbl;

}

/**
* @brief  Routine to calculate the thredsold of the depth histogram.
*
* @param[Global_array] global object array in which look for... 
* @return 0 if all right 1 otherwise
*/
int vipMovingObject::get_Depth_Hist_Th(void)
{
	int threshold = 0;   // the current threshold
	int tnew = 50;      // the new threshold
	int cumtotal = 0;   // the current cumulative total
	double m1, m2;       // the two means

	int* depth_hist = get_D_hist();

	do {
		threshold = tnew;
		m1 = m2 = 0.0;
		cumtotal=0;
		for (int i=0; i<threshold; i++)
		{
			m1 += (depth_hist[i] * i);
			cumtotal += depth_hist[i];
		}

		m1 /= cumtotal;
		cumtotal=0;

		for (int i=threshold; i<256; i++)
		{
			m2 += (depth_hist[i] * i);
			cumtotal += depth_hist[i];
		}

		m2 /= cumtotal;

		tnew = (int)((m1 + m2) / 2.0);
	} while (tnew != threshold);

	return tnew;
}



/**
* @brief  Routine to automatic threshold the depth histogram..
*
* @param[disjoined_obj] output of disjoined object... 
* @return 0 if all right 1 otherwise
*/
int vipMovingObject::hist_th(vipMovingObject* disjoined_obj,unsigned short* depth16)
{
	int D_th = this->get_Depth_Hist_Th();

	int area1=0;
	int area2=0;
	int* pixel_tmp1=new int[this->Get_area()];//temporary pixel map array
	int* pixel_tmp2=new int[this->Get_area()];
	int* pixel_map1=NULL;
	int* pixel_map2=NULL;

	for(int i = 0; i < Get_area(); i++)
	{
		int index = Pixel_map[i];
		if( (depth16[index]>>4) < D_th)
		{
			pixel_tmp1[area1] = index;
			area1++;
		}
		else
		{
			pixel_tmp2[area2] = index;
			area2++;
		}
	}
	//set a threshold in area calculation.May happens that for few pixel the 
	//object wil be set as special, probably giving a threshold error...
	int lim = 20*Get_area()/100;
	if((area1*area2)==0 || area1<lim || area2<lim)
	{
		printf("\n\t:::WARNING in depth histogram thresholding:object area too small:::\n");
		fprintf(std_error,"\t\t:::WARNING in depth histogram thresholding:object area too small:::%d,%d--%d\n",area1,area2,Get_area());

		//in this case we procede by joining the objects together
		//considering only one to avoid probably threshold error..
		int n_area = area1+area2;
		pixel_map1 = new int[n_area];
		memcpy(pixel_map1,pixel_tmp1,area1*sizeof(int));
		memcpy(pixel_map1+area1,pixel_tmp2,area2*sizeof(int));

		disjoined_obj[0].Set_Used(true);
		disjoined_obj[0].Set_area(n_area);
		disjoined_obj[0].Set_PixelMap(pixel_map1);

		disjoined_obj[1].Set_Used(false);

		srand(n_area+25);
		int lbl=(rand())%256;
		if(lbl!=0)
			disjoined_obj[0].Set_output_label(lbl);
		else
			while(lbl==0)
			{
				lbl=(rand())%256;
				disjoined_obj[0].Set_output_label(lbl);
			}

			delete[] pixel_map1, pixel_tmp1, pixel_tmp2;

	}
	else
		//if the object has been thresholed into big enought areas...
	{
		//setup of final pixel map array...
		pixel_map1 = new int[area1];
		pixel_map2 = new int[area2];
		memcpy(pixel_map1,pixel_tmp1,area1*sizeof(int));
		memcpy(pixel_map2,pixel_tmp2,area2*sizeof(int));



		//setup of main disjoined obj attribute

		disjoined_obj[0].Set_Used(true);
		disjoined_obj[0].Set_area(area1);
		disjoined_obj[0].Set_PixelMap(pixel_map1);

		disjoined_obj[1].Set_Used(true);
		disjoined_obj[1].Set_area(area2);
		disjoined_obj[1].Set_PixelMap(pixel_map2);

		srand(area1+50);
		int lbl=(rand())%256;
		if(lbl!=0)
			disjoined_obj[0].Set_output_label(lbl);
		else
			while(lbl==0)
			{
				lbl=(rand())%256;
				disjoined_obj[0].Set_output_label(lbl);
			}

			srand(area2+70);
			lbl=(rand())%256;
			if(lbl!=0)
				disjoined_obj[1].Set_output_label(lbl);

			else
				while(lbl==0)
				{
					lbl=(rand())%256;
					disjoined_obj[1].Set_output_label(lbl);
				}


				delete[] pixel_map1,pixel_map2,pixel_tmp1,pixel_tmp2;

	}//end if area1*area2==0





	return 0;
}


/**
* @brief  Routine to disjoint 2 single object from a special one 
* @       using depth histogram automatic thredsolding..
*
* @param[Global_array] global object array in which look for... 
* @return 0 if all right 1 otherwise
*/
int vipMovingObject::DisJoint_Special(vipMovingObject* Global_array, vipFrameHSV* original, unsigned short* depth16, unsigned char* labelled, unsigned char* previous_lab)
{
	fprintf(std_error,"\n\t\t::DEBUG::Entering disjoint_special::\n");
	if(Is_special()==true)
	{
		int nr_fused_obj = Get_fused_label_nr();
		unsigned char* lbl_fused_obj = Get_fused_label();
		int* Global_Object_ID = new int[nr_fused_obj];

		vipMovingObject* disjoined_obj = new vipMovingObject[nr_fused_obj];

		for(int i=0;i<nr_fused_obj;i++)
			Global_Object_ID[i] = Get_Global_ID(lbl_fused_obj[i],Global_array,MAX_GLOBAL_OBJ_NR);

		this->hist_th(disjoined_obj,depth16);

		//this->Set_output_label(0);
		//this->Re_paint_Color(labelled,320,240);

		for(int i=0;i<nr_fused_obj;i++)
			if(disjoined_obj[i].Is_Used()==true)
			{
				disjoined_obj[i].Get_Statistic(original,depth16);
				disjoined_obj[i].set_Centro_id(original->width,original->height);
				//unsigned char lbl = disjoined_obj[i].drag_label(labelled, previous_lab);
				//unsigned char lbl = disjoined_obj[i].get_Spatial_nearest_label(Global_array);
				unsigned char lbl = disjoined_obj[i].get_Depth_nearest_label(Global_array);
				disjoined_obj[i].Re_paint_Color(labelled,original->width,original->height);
				disjoined_obj[i].copy_to(Global_array,MAX_GLOBAL_OBJ_NR,false);
			}

			//this->Set_Used(false);

			//this->Set_Active(true);

			delete[] Global_Object_ID;
			delete[] disjoined_obj;

	}
	else
		fprintf(std_error,"\n\t\t:::Warning:IsSpecial check not passed in Disjoint_Special function:::\n\n");
	return 0;
}


/**
* @brief  Routine to copy the actual obj attributes into another
*
* @param[ptr] object array in which look for... 
* @param[nr_object] input dimension of upper array (not used) 
* @param[first_frame] input bool tic for the 1^frame
* @param[frame_nr] input frame_nr
* @return 0
*/
int vipMovingObject::copy_to(vipMovingObject* ptr,int nr_Object,bool first_frame)
{
	if(first_frame==true)
	{
		//this is the first motion frame so we only copy the local object to one location
		//of ptr (global object array)according to nr_Object index(..=0)...
		//printf("first frame");getchar();

		// Fixed by Marco Verza & Nicola Piotto on 15/04/2008. Was:
		//int ID = this->Get_Id();		// this was writing on incorrect positions of the global object array, depending on the ID of the local object to copy
		// Now it's:
		int ID;	
		for( unsigned int i=0; i<MAX_GLOBAL_OBJ_NR; i++ )
			if( ptr[i].Is_Used()==false )	// get first free global object position // TODO: test this with TWO valid used objects in first frame.
			{
				ID = i;
				break;
			}

			this->Corrispondent_ID=ID;

			ptr[ID].In_Use = true; 

			ptr[ID].Set_output_label(this->Get_Output_label(0));

			if(this->Is_special()==true)
				ptr[ID].Set_Special(this->fused_label_nr,this->fused_label);


			ptr[ID].Set_area(this->Get_area());
			ptr[ID].Set_PixelMap(this->Get_PixelMap());

			ptr[ID].presence_counter = this->presence_counter;

			ptr[ID].Set_last_frame_seen(this->Get_last_frame_seen());

			ptr[ID].H_mean = this->H_mean;
			ptr[ID].Centro_id = this->Centro_id;
			ptr[ID].Bounding_box[0] = this->Bounding_box[0];
			ptr[ID].Bounding_box[1] = this->Bounding_box[1];
			ptr[ID].Bounding_box[2] = this->Bounding_box[2];
			ptr[ID].Bounding_box[3] = this->Bounding_box[3];

			memcpy(ptr[ID].H_hist,this->H_hist,361*sizeof(float));
			memcpy(ptr[ID].D_hist,this->D_hist,256*sizeof(int));

			ptr[ID].x = this->x;
			ptr[ID].y = this->y;
			ptr[ID].z = this->z;

			ptr[ID].disparity = this->disparity;
			ptr[ID].disp16 = this->disp16;


	}
	else //bool first_frame = false 
	{
		//printf("NOT first frame");getchar();
		//before copy we need to find out the right global object..

		unsigned char ref_label = this->Get_Output_label(0);
		int found_ID = Get_Global_ID(ref_label,ptr,MAX_GLOBAL_OBJ_NR);

		if(found_ID != -1)
		{
			//update global object
			//printf("Found global..%d!!\n",found_ID);


			ptr[found_ID].In_Use = true;

			//store inthe local the corrispondent global ID.. 
			this->Corrispondent_ID=found_ID;

			if(this->Is_special()==true)
				ptr[found_ID].Set_Special(this->fused_label_nr,this->fused_label);


			ptr[found_ID].Set_last_frame_seen(this->Get_last_frame_seen());

			ptr[found_ID].Set_output_label(this->Get_Output_label(0));

			ptr[found_ID].Set_area(this->Get_area());
			ptr[found_ID].Set_PixelMap(this->Get_PixelMap());

			ptr[found_ID].presence_counter +=1;

			ptr[found_ID].H_mean = this->H_mean;
			ptr[found_ID].Centro_id = this->Centro_id;
			ptr[found_ID].Bounding_box[0] = this->Bounding_box[0];
			ptr[found_ID].Bounding_box[1] = this->Bounding_box[1];
			ptr[found_ID].Bounding_box[2] = this->Bounding_box[2];
			ptr[found_ID].Bounding_box[3] = this->Bounding_box[3];

			memcpy(ptr[found_ID].H_hist,this->H_hist,361*sizeof(float));
			memcpy(ptr[found_ID].D_hist,this->D_hist,256*sizeof(int));

			ptr[found_ID].x = this->x;
			ptr[found_ID].y = this->y;
			ptr[found_ID].z = this->z;

			ptr[found_ID].disparity = this->disparity;
			ptr[found_ID].disp16 = this->disp16;


		}
		else// if (found_ID==-1)//new object in the scene
		{
			//printf("Global not Found..\n");

			//create new global object to copy data to
			//looking for the global object with the same final label
			int ID = Get_Free_ID(ptr,MAX_GLOBAL_OBJ_NR);
			if(ID==-1){
				printf("\n\t\tERROR::::Problem finding free global object::\n");
				fprintf(std_error,"\n\t\tERROR :: - :: Problem finding free global object::\n");
			}


			this->Corrispondent_ID = ID;

			ptr[ID].In_Use = true;
			if(this->Is_special()==true)
				ptr[ID].Set_Special(this->fused_label_nr,this->fused_label);


			ptr[ID].Set_output_label(this->Get_Output_label(0));

			ptr[ID].Set_area(this->Get_area());
			ptr[ID].Set_PixelMap(this->Get_PixelMap());

			ptr[ID].presence_counter = this->presence_counter;

			ptr[ID].Set_last_frame_seen(this->Get_last_frame_seen());

			ptr[ID].H_mean = this->H_mean;
			ptr[ID].Centro_id = this->Centro_id;

			ptr[ID].Bounding_box[0] = this->Bounding_box[0];
			ptr[ID].Bounding_box[1] = this->Bounding_box[1];
			ptr[ID].Bounding_box[2] = this->Bounding_box[2];
			ptr[ID].Bounding_box[3] = this->Bounding_box[3];

			memcpy(ptr[ID].H_hist,this->H_hist,361*sizeof(float));
			memcpy(ptr[ID].D_hist,this->D_hist,256*sizeof(int));

			ptr[ID].x = this->x;
			ptr[ID].y = this->y;
			ptr[ID].z = this->z;

			ptr[ID].disparity = this->disparity;
			ptr[ID].disp16 = this->disp16;

		}

	}

	return 0;
}


//make histogram intersection normalized..
/**
* @brief  make the normalized histogram intersection
*
* @param[obj] inpu target object 
* @return similarity in 0-1 range
*/
float vipMovingObject::Hist_Intersection(vipMovingObject obj)
{
	float sum=0;
	float tmp=0;
	for(int i=0;i<360;i++)
	{
		sum+=min(this->H_hist[i],obj.H_hist[i]);
		tmp+=obj.H_hist[i];
	}
	return (sum/tmp);
}





bool vipMovingObject::overlap(vipMovingObject obj)
{//top`bottom`left`right = 0`1`2`3 index of bounding box
	double dist_disp = abs((disp16>>4) - (obj.disp16>>4));
	if( ((Bounding_box[2]+5 >= obj.Bounding_box[2] && 
		Bounding_box[2] <= obj.Bounding_box[3]+5) ||

		(Bounding_box[2] <= obj.Bounding_box[2]+5 &&
		Bounding_box[3]+5 >= obj.Bounding_box[2]))

		//&& ( dist_disp < 50)
		)
		return true;
	else
		return false;
}





/**
*
*
*/

void vipMovingObject::Update_fused_label(vipMovingObject* global, int IDspecial)
{
	fused_label_nr++;
	unsigned char special_lbl = global[IDspecial].Get_Output_label(0);
	unsigned char* special_lbl_tmp = NULL;
	int special_lbl_nr = 0;
	unsigned char ordinary_lbl;
	unsigned char* tmp = NULL;

	for(int i = 0; i < (fused_label_nr-1); i++)
		if( global[ Get_Global_ID(fused_label[i],global,MAX_GLOBAL_OBJ_NR) ].Is_special()==true)
		{
			special_lbl_tmp = global[ Get_Global_ID(fused_label[i],global,MAX_GLOBAL_OBJ_NR) ].Get_fused_label();
			special_lbl_nr = global[ Get_Global_ID(fused_label[i],global,MAX_GLOBAL_OBJ_NR) ].Get_fused_label_nr();
		}
		else
		{
			ordinary_lbl = fused_label[i];//object normal..
		}
		tmp = new unsigned char[special_lbl_nr+1];
		memcpy(tmp,special_lbl_tmp, sizeof(unsigned char)*special_lbl_nr);
		tmp[special_lbl_nr] = ordinary_lbl; 

		delete[] fused_label;
		fused_label = new unsigned char[fused_label_nr];
		memcpy(fused_label,tmp,sizeof(unsigned char)*fused_label_nr);


		delete[] special_lbl_tmp;
		delete[] tmp;
}






//support function for the class
int array_cmp(unsigned char* in1, int nrlabel, unsigned char value)
{
	int tmp=0;

	if(nrlabel==0) 
		return 0;
	else
	{
		for(int cont=0; cont<nrlabel;cont++)
			if(in1[cont] != value)
				tmp++;

		if(tmp==nrlabel)
			return 0; //ok, value not in the array
		else
			return 1;  //value already present in the array
	}

}


/**
* @brief  Routine to remove the blinking object
*
* @param[input] input labelled img (with blob_labelling(...)) 
* @param[ptr] input global obj array
* @param[nr_object] dimension of upper array (not used)
* @param[frame_nr] nr of actual frame
* @return 0
*/



#ifdef VMT_STEREOTRACK
 int Buffer_Presence(unsigned char* rect_yuv,unsigned char* input,unsigned short* depth16,int width,int height,vipMovingObject* ptr, int nr_Object, int frame_nr)
#else
int Buffer_Presence(unsigned char* input,unsigned short* depth16,int width,int height,vipMovingObject* ptr, int nr_Object, int frame_nr)
#endif // VMT_STEREOTRACK
{
	int obj_visualization_delay = 5;


	for(int i=0;i<MAX_GLOBAL_OBJ_NR;i++)
	{
		// if(ptr[i].Is_Used()==true)
		// {
		//  //HERE INTRODUCE OBJECT RE-ENTRANCE CONTROL
		//  //BEFORE TO INSTANCIATE NEW OBJECT(MEAN CONSIDER THE POSSIBILITY
		//  //THE ENTERED OBJ IS AN ALREADY SEEN OBJECT THAT LEAVED THE SCENE:
		//  //IF CONTROL FAIL THE NEW (UNKNOWN) OBJECT IS INSTANCIATED)


		//  //setup of visualization object delay..
		//  if(ptr[i].Get_presence_counter()<obj_visualization_delay) 
		//ptr[i].Erase(input,width,height);//color repaint in black...	
		// }





		//setup of delay after which free the global object..
		//if(((frame_nr - ptr[i].Get_last_frame_seen())>=250 && ptr[i].Get_last_frame_seen()!=0) 
		//	//(||ptr[i].Is_special()==true && (frame_nr - ptr[i].Get_last_frame_seen())>=10)	//clear more quickly the special obj
		//	)

		//	//reset object parameter.
		//	ptr[i].Reset();


		//calculation and drawing of trajectory for the active obj..

		if(ptr[i].Get_presence_counter()>obj_visualization_delay ||
			ptr[i].Is_special()==true)
		{
#ifdef VMT_STEREOTRACK
			//3d position calculation
			//write to file 3d position of moving object (centro_id)
			float x, y, z; 
			x = y = z = 0.0;

			int c_id = ptr[i].get_Centro_id();
			unsigned short disp16 = ptr[i].get_Disparity16();
			int row = c_id / width;
			int col = c_id % width;

			if ( disp16 < 0xFF00 ) 
			{
				TriclopsError err = triclopsRCD16ToXYZ( tri_context, row, col, disp16, &x, &y, &z );
				if(err==TriclopsErrorOk)
				{
					//store into the object the 3d trajectory information
					ptr[i].Set_3Dpos(x,-y,z);
					if(i<10 /*&& ptr[i].Is_special()==false*/)//do not printf the occluded object trajectories...
						fprintf(track_3d[i],"%d)\t%f\t%f\t%f\t%d\t%d\t%d\n",uiImage,x,z,-y,frame_nr,-col,disp16>>4);

				}
			}

		//	ptr[i].Draw_Bounding_Box(rect_yuv,width, height);

#endif	// VMT_STEREOTRACK

			//print basic object information to file..
			fprintf(std_error,"\n\t\tGlobal Object nr.[%d]\t\t\t\t\t\t\n",i);
			fprintf(std_error,"\t\tLabel component YUV -> %d %d %d\t\t\t\t\t\t\n",ptr[i].Get_Output_label(0),ptr[i].Get_Output_label(1),ptr[i].Get_Output_label(2));
			fprintf(std_error,"\t\t>Area = %d\t\t\t\t\t\t\n",ptr[i].Get_area());
			fprintf(std_error,"\t\t>Presence Counter = %d\t\t\t\t\t\t\n",ptr[i].Get_presence_counter());
			fprintf(std_error,"\t\t>Timer=%d!!\t\t\t\t\t\t\n",frame_nr - ptr[i].Get_last_frame_seen());
			fprintf(std_error,"\t\t>Hue Mean value = %f\t\t\t\t\t\t\n",ptr[i].get_H_mean());
			fprintf(std_error,"\t\t>IsSpecial = %s\t\t\t\t\t\t\n",ptr[i].Get_special());
			if(ptr[i].Is_special()==true)
			{
				fprintf(std_error,"\t\t>Fused Object number= %d\t\t\t\t\t\t\n",ptr[i].Get_fused_label_nr());
				for(int e = 0; e < ptr[i].Get_fused_label_nr(); e++)
					fprintf(std_error,"\t\t>Fused ID (Y label)= %d\t(%d)\t\t\t\t\t\n",Get_Global_ID(ptr[i].Get_fused_label()[e],ptr,MAX_GLOBAL_OBJ_NR),(int)(ptr[i].Get_fused_label()[e]));	

			}
		}//end if(ptr[i].Get_presence_counter()>obj_visualization_delay ||ptr[i].Is_special()==true)

	}//end for(int i=0;i<MAX_GLOBAL_OBJ_NR;i++)

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
int Discriminate(vipMovingObject* Local_array,vipMovingObject* Global_array,unsigned char lbl,int nr_lbl)
{

	int Global_ID = Get_Global_ID(lbl,Global_array,MAX_GLOBAL_OBJ_NR);
	//printf("Corrispondent Global_Object_ID = %d!!\n",Global_ID);

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
			fused_obj_GLOBAL_ID[cont]=Get_Global_ID(lbl_fused_obj[cont],Global_array,MAX_GLOBAL_OBJ_NR);

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
						h = Global_array[fused_obj_GLOBAL_ID[i]].Hist_Intersection(Local_array[fused_obj_LOCAL_ID[j]]);
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


/**
* @brief  get free global object ID
*
* @param[ptr] input array_object 
* @param[nr_object] input dimension of upper array
* @return ID if found else -1
*/
int Get_Free_ID(vipMovingObject* ptr,int nr_object)
{
	for(int i=0; i<nr_object;i++)
		if(ptr[i].Is_Used()==false)
			return ptr[i].Get_Id();

	return -1;
}



/**
* @brief  get global object ID from the label
*
* @param[label] input label
* @param[ptr] input global_array_object
* @param[nr_object]input dimension of upper array
* @return ID if found else -1
*/
int Get_Global_ID(unsigned char label,vipMovingObject* ptr,int nr_object)
{

	for(int i = 0; i<nr_object;i++)
	{
		if(label==ptr[i].Get_Output_label(0))
			//may would be a special tic controll...

			return ptr[i].Get_Id();
	}

	return -1;
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
int Blob_Tracking( vipFrameHSV* input, unsigned char* rect_yuv, unsigned char* depth_yuv, unsigned short *imagedepth16data, unsigned char* blobs, int frame_nr )
#else
int Blob_Tracking( vipFrameHSV* input, unsigned char* blobs, int frame_nr )
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

	int label_nr = ConnectedComponentLabeling(blobs,labelled,width,height);
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

		if(previous_final_labelled==NULL) //first frame with moving object..
		{
			//unique array memory allocation..(static structure)
			//memory allocation for global_object array (40 object stored)
			Global_Object_array = new vipMovingObject[MAX_TRACKABLE_OBJS];

			//set the ID for the global objects
			for(int i=0;i<MAX_TRACKABLE_OBJS;i++)
			{
				Global_Object_array[i].Set_Id(i);
				Global_Object_array[i].Set_Used(false);
			}

			//memory alloc for the labelled frame..
			previous_final_labelled = new unsigned char[width*height];
			memset(previous_final_labelled,128,width*height);
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
			if(Local_Object_array[cont].Set_PixelMap(labelled,width,height,first_frame)==0)
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
			else
				Local_Object_array[cont].Erase(labelled,width, height);

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
						overlap = Local_Object_array[cont].overlap(Local_Object_array[cont1]);
						if(Local_Object_array[cont1].Is_Used()==true && overlap==true)
						{
							if(Local_Object_array[cont].Update_Pixel_Map( Local_Object_array[cont1] )==0)
							{
								Local_Object_array[cont].Get_Statistic(input,imagedepth16data);
								Local_Object_array[cont1].Set_Used(false);
								cont1=0;//counter reset..
							}
							else
								Local_Object_array[cont].Erase(labelled,width, height);
						}
					}

//					Local_Object_array[cont].Re_paint_Color(labelled,width,height);
					int c_id = Local_Object_array[cont].set_Centro_id(width,height);

			}//end 'if(Local_Object_array[cont].Is_Used()==true)'



			//here drag the label(s) of the overlapped region(s) in the previous frame..
			//do the draggin only if we are not at the first frame of the sequence
			if(first_frame == false) 
				for( int cont=0; cont < label_nr; cont++)
					if(Local_Object_array[cont].Is_Used()==true)
					{
						int out=0;
						int te=Local_Object_array[cont].drag_label(labelled,previous_final_labelled);
						//te = 0 is the normal case...means one overlapped object found in the prev_lab frame 
						if(te == 1)
						{
							out = Local_Object_array[cont].get_Spatial_nearest_label(Global_Object_array,width,height);
							fprintf(std_error,"\t\t:::Warning(%d):Try assigning label via nearest neighborhood to object Local_ID=%d..\n",out,Local_Object_array[cont].Get_Id()); 
						}

						if(te == 1 && out == 255)  //means new obj is entering the scene..
						{
							srand ( time(NULL) );//uncommented on 0304
							Local_Object_array[cont].Set_output_label(rand()%256);
						}
						if(te == 2)//special obj
						{//check if the involved objs are already special
							//if so update the stat (fused_label_nr, fused_label)
							unsigned char* lbl_pt = Local_Object_array[cont].Get_fused_label();
							int gbl0 = Get_Global_ID(lbl_pt[0],Global_Object_array, MAX_TRACKABLE_OBJS);
							int gbl1 = Get_Global_ID(lbl_pt[1],Global_Object_array, MAX_TRACKABLE_OBJS);

							if(Global_Object_array[gbl0].Is_special()==true)
							{
								Local_Object_array[cont].Update_fused_label(Global_Object_array,gbl0);
							}
							else
								if(Global_Object_array[gbl1].Is_special()==true)
								{
									Local_Object_array[cont].Update_fused_label(Global_Object_array,gbl1);
								}

						}

						//try to disjoint the special object using depth histogram based thredsolding
						/* if(te==2)
						Local_Object_array[cont].DisJoint_Special(Global_Object_array,input,imagedepth16.data,labelled,previous_final_labelled);
						else*/
			//			Local_Object_array[cont].Re_paint_Color(labelled,width,height);


					}//end  if(Local_Object_array[cont].Is_Used()==true)

					//check if there are multiple object with the same output label..
					unsigned char lf;
					unsigned char* loc_array = new unsigned char[label_nr];
					bool do_discriminate = false;
					int occlusion_nr = 0;
					unsigned char* occlusion_label = new unsigned char[4];//label duplicated array

					for(int cont=0; cont < label_nr; cont++)
						if(Local_Object_array[cont].Is_Used() == true)
						{
							lf = Local_Object_array[cont].Get_Output_label(0);
							if(array_cmp(loc_array,label_nr,lf) == 1)//means there are multiple object with the same label..
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
								Discriminate(Local_Object_array,Global_Object_array,occlusion_label[oc],label_nr);

						for(int cont=0; cont < label_nr; cont++)	
							if(Local_Object_array[cont].Is_Used() == true)
							{
								Local_Object_array[cont].Re_paint_Color(labelled,width,height);
								Local_Object_array[cont].copy_to(Global_Object_array,MAX_TRACKABLE_OBJS,first_frame);
							}

							//first_frame 
							if(first_frame==true)
								first_frame=false;

							//copy the final labelled frame to static structure..
							memcpy(previous_final_labelled,labelled,sizeof(unsigned char)*width*height);


							#ifdef VMT_STEREOTRACK
							 Buffer_Presence(rect_yuv,labelled,imagedepth16data,width,height,Global_Object_array,label_nr,frame_nr);
							#else
							 Buffer_Presence(labelled,imagedepth16data,width,height,Global_Object_array,label_nr,frame_nr);
							#endif // VMT_STEREOTRACK
							


							delete[] loc_array;
							delete[] occlusion_label;
							delete[] Local_Object_array;


	}//end if(label_nr>0)



	return 0;
}

/* Important to call this after finishing the tracking and before exiting program */
void TrackerCleanUp()
{
	if( Global_Object_array != NULL )
		delete[] Global_Object_array;

	if( previous_final_labelled != NULL )
		delete[] previous_final_labelled;

	Global_Object_array = NULL;
	previous_final_labelled = NULL;
	first_frame = true;


}
