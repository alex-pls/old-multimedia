#include "vipMovingObject.h"

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

	if( this->Pixel_map )	// check added by MV
	{
		printf("bug or memory leak? :)\n");
		free( Pixel_map );	// afaik, should never happen. if it does, fix it !
	}

	this->Pixel_map = NULL;

	unsigned char input_lbl = this->Get_input_label();
	
	input_lbl = input_lbl%255;
	unsigned char U_lbl = (input_lbl/255)+128;//handle (possible) color label
	
	//Area calculation and pixel map definition
	for(int cont=0;cont<height*width;cont++)
	{
		if(input[cont]==input_lbl && input[cont+width*height]==U_lbl)
		{
			this->Area++;//lenght of pixel_map
			this->Pixel_map = (int*) realloc (this->Pixel_map, this->Area*sizeof(int));
			if(this->Pixel_map == NULL)
			{
				printf("Problem in Pixel_map structure reallocation..\n\n");
				return VIPRET_INTERNAL_ERR;
			}
			this->Pixel_map[this->Area-1] = cont;
		}
	}

	//flag the smallest regions as not in use..
	if(first_frame==false) //due to initial motion problem
	{
		if(this->Area < iMinBlobSize)//remove too small objects
		{
			this->Set_Used(false);
			return -1;
		}
	}

	return 0;
}

int vipMovingObject::Update_Pixel_Map(vipMovingObject *object)
{
	int area = object->Get_area();

	int orig_area = this->Get_area();
	int new_area = orig_area+area;

	this->Pixel_map = (int*) realloc(this->Pixel_map,new_area*sizeof(int));

	memcpy(Pixel_map+orig_area,object->Get_PixelMap(),sizeof(int)*area);
	this->Area = new_area;

	//setup disp16 value..
	disp16=int(orig_area*disp16+area*object->get_Disparity16())/new_area;
	disparity = unsigned char( disp16>>4 );

	//setup bounding box struct
	Bounding_box[0] = min(Bounding_box[0],object->get_BBox(0));
	Bounding_box[1] = max(Bounding_box[1],object->get_BBox(1));
	Bounding_box[2] = min(Bounding_box[2],object->get_BBox(2));
	Bounding_box[3] = max(Bounding_box[3],object->get_BBox(3));

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

	int framesize = width*height;		// avoid some multiplies
	int framesizex2 = framesize * 2;

	for(int cont=0; cont<this->Get_area(); cont++)
	{
		int index = this->Pixel_map[cont];
		if(/*input[index]==this->Get_Output_label() && */this->Is_special()==false)
		{
			input[index]=(unsigned char)0;
			input[index+framesize]=(unsigned char)128;
			input[index+framesizex2]=(unsigned char)128;
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
	{
		delete[] label_found;
		return -1;
	}
}


/**
* @brief  drag the spatial nearest label to object from prev frame
*
* @param[Global_Object_array] input global object array  
* @return the nearest label to the object
*/
unsigned char vipMovingObject::get_Spatial_nearest_label( int width, int height )
{
	int c_id = this->get_Centro_id();
	int th = width*height;
	unsigned char nearest_label=0;

	int col = c_id%width;
	int row = c_id/width;
	// TODO : parametrizzare meglio
	// boundaries for centroid						// when 320x240 only, these were:
	int left_bound = (int) float(width) * 0.1;		// 64
	int right_bound = (int) float(width) * 0.9;		// 256
	int top_bound = (int) float(height) * 0.1;		// 48
	int bottom_bound = (int) float(height) * 0.9;	// 192

	// TODO: aggiungere check su presence / etc.

	if(col>left_bound && col<right_bound && row>top_bound && row<bottom_bound)
	{
		for(int cont = 0; cont < iMaxGlobalObjNr; cont++)
		{
			int arr_cid = vMO_Global[cont].get_Centro_id();
			if(arr_cid >= 0)
				if( abs( arr_cid - c_id) < th )
				{
					th = abs(arr_cid - c_id);
					nearest_label = vMO_Global[cont].Get_Output_label(0);
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
			Global_Object_ID[i] = Get_Global_ID(lbl_fused_obj[i], iMaxGlobalObjNr, Global_array );

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
				disjoined_obj[i].copy_to(Global_array,false);
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
int vipMovingObject::copy_to(vipMovingObject* ptr,bool first_frame)
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
		for( int i=0; i<ptr->iMaxGlobalObjNr; i++ )
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

			ptr[ID].frmWidth = this->frmWidth;
			ptr[ID].frmHeight = this->frmHeight;

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

			// test
			ptr[ID].m_pBlobTrajectory->appendFrom( this->m_pBlobTrajectory );
			ptr[ID].m_pWorldTrajectory->appendFrom( this->m_pWorldTrajectory );

			// Creation Time: set it now!
			ptr[ID].setCreationTime( time(NULL) );


	}
	else //bool first_frame = false 
	{
		//printf("NOT first frame");getchar();
		//before copy we need to find out the right global object..

		unsigned char ref_label = this->Get_Output_label(0);
		int found_ID = Get_Global_ID(ref_label, iMaxGlobalObjNr, ptr );

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

			// test
			ptr[found_ID].m_pBlobTrajectory->appendFrom( this->m_pBlobTrajectory );
			ptr[found_ID].m_pWorldTrajectory->appendFrom( this->m_pWorldTrajectory );


		}
		else// if (found_ID==-1)//new object in the scene
		{
			//printf("Global not Found..\n");

			//create new global object to copy data to
			//looking for the global object with the same final label
			int ID = Get_Free_ID(iMaxGlobalObjNr);
			if(ID==-1)
			{
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

			// test
			ptr[ID].m_pBlobTrajectory->appendFrom( this->m_pBlobTrajectory );
			ptr[ID].m_pWorldTrajectory->appendFrom( this->m_pWorldTrajectory );

			// Creation Time: set it now!
			ptr[ID].setCreationTime( time(NULL) );

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
float vipMovingObject::Hist_Intersection(vipMovingObject *obj)
{
	float sum=0;
	float tmp=0;
	for(int i=0;i<360;i++)
	{
		sum+=min(this->H_hist[i],obj->H_hist[i]);
		tmp+=obj->H_hist[i];
	}
	return (sum/tmp);
}





bool vipMovingObject::overlap(vipMovingObject *obj)
{//top`bottom`left`right = 0`1`2`3 index of bounding box
	double dist_disp = abs((disp16>>4) - (obj->disp16>>4));
	if( ((Bounding_box[2]+5 >= obj->Bounding_box[2] && 
		Bounding_box[2] <= obj->Bounding_box[3]+5) ||

		(Bounding_box[2] <= obj->Bounding_box[2]+5 &&
		Bounding_box[3]+5 >= obj->Bounding_box[2]))

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
		if( global[ Get_Global_ID(fused_label[i],iMaxGlobalObjNr,global) ].Is_special()==true)
		{
			special_lbl_tmp = global[ Get_Global_ID(fused_label[i],iMaxGlobalObjNr,global) ].Get_fused_label();
			special_lbl_nr = global[ Get_Global_ID(fused_label[i],iMaxGlobalObjNr,global) ].Get_fused_label_nr();
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
