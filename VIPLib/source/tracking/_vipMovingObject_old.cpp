/** @file vipMovingObject
 *
 * File containing methods for the 'vipMovingObject' class.
 * The header for this class can be found in vipMovingObject.h, check
 * that file for class description.
 *
 *
 ****************************************************************************
 * VIPLib Framework
 *  open source, founded by Alessandro Polo 2006
 *  http://mmlab.disi.unitn.it/projects/VIPLib
 *
 *  maintained by MultiMedia Laboratory - DISI - University of Trento
 *
 ****************************************************************************/

#include "vipMovingObject.h"


 #include <stdio.h>


#include "vipTracker.h"

#include "add2lib/vipLogic.h"


//see in variable.h
////// extern int obj_free_delay;
////// extern int obj_visualization_delay;
////// extern int max_global_obj_nr;
////// extern int m_w_a;

//for buffer_presence method    vip_movng_object.cpp
int obj_visualization_delay=7; //delay in visualization (in nr of frame)7
int obj_free_delay=100; //consecutive nr of frame of inactivity after which freeing the object


vipMovingObject::vipMovingObject()
{
	Trajectory = NULL;
	Pixel_map = NULL;
	Countour = NULL;

	Reset();
}


void vipMovingObject::Reset(void)
{

	In_Use = false;
	Active = false;
	Input_label = (unsigned char) 0;
	Y_Output_label = (unsigned char) 0;
	U_Output_label = (unsigned char) 0;
	V_Output_label = (unsigned char) 0;
	Special=false;
	Centro_id= -1;

	if ( Trajectory != NULL )
		delete[] Trajectory;
	Trajectory = NULL;

	Area=0;
	Countour_lenght=0;
	Compactness=0;
	H_mean = 0;

	if ( Pixel_map != NULL )
		delete [] Pixel_map;
	Pixel_map = NULL;

	if ( Countour != NULL )
		delete[] Countour;
	Countour = NULL;

	presence_counter = 0;
	nr_last_frame = 0;
	processed = false;

	Bounding_box[0]=240;//top
	Bounding_box[1]=0;//bottom
	Bounding_box[2]=320;//left
	Bounding_box[3]=0;//right

	//init to 0 H_hist array
	for(int i=0;i<361;i++)
		H_hist[i]=0;
}

int vipMovingObject::set_Centro_id(int width,int height)
{
	/*	this->Centro_id=0;
	for(int i=0;i<this->Area;i++)
	this->Centro_id += this->Pixel_map[i];

	this->Centro_id /= this->Area;
	*/

	int sum_row=0;
	int sum_col=0;


	int row=0;
	int col=0;

	Bounding_box[0]=height;//top
	Bounding_box[1]=0;//bottom
	Bounding_box[2]=width;//left
	Bounding_box[3]=0;//right

	for(int i=0;i<this->Area;i++)
	{
		col=(int) (fmod((float)Pixel_map[i],(float)320));
		row=Pixel_map[i]/width;

		sum_row+=row;//centro_id
		sum_col+=col;
		//bounding box
		Bounding_box[0]=min(Bounding_box[0],row);
		Bounding_box[1]=max(Bounding_box[1],row);
		Bounding_box[2]=min(Bounding_box[2],col);
		Bounding_box[3]=max(Bounding_box[3],col);
	}

	sum_row/=this->Area;
	sum_col/=this->Area;

	this->Centro_id=sum_row*width+sum_col;

	return this->Centro_id;
}

/**
* @brief  Setup the pixel map for the object
*
* @param[input] input labelled img (with blob_labelling(...))
* @param[width.height] input img dimension
* @return VIPRET_OK
*/
int vipMovingObject::Set_PixelMap(unsigned char* input,int width,int height)
{
	this->Area = 0;
	this->Countour_lenght = 0;
	int index=0;
	int index_=0;

	unsigned char input_lbl = this->Get_input_label();


	//Area calculation..for pixel map lenght
	//and lenght of contour..
	for(int row=0;row<height;row++)
	{
		for(int col=0;col<width;col++)
		{
			int cont=row*width+col;
			if(input[cont]==input_lbl && input_lbl!=0)
			{
				this->Area++;//lenght of pixel_map

				if(input[cont-1]+input[cont+1]+input[cont-width]+input[cont+width]<4*input_lbl)
				{
					//means that the pixel is not 4-connected so it is part of contour
					//contour_lenght=area-4connectedpixel...
					this->Countour_lenght++;
				}
			}
		}
	}

	//memory alloc for PixelMap and contour map structure..
	this->Pixel_map = new int[this->Get_area()];
	this->Countour = new int[this->Countour_lenght];

	//storing PixelMap and contour map...
	for(int cont=0;cont<height*width;cont++)
	{
		if(input[cont]==this->Get_input_label())
		{
			this->Pixel_map[index]=cont;
			index++;
			if(input[cont-1]+input[cont+1]+input[cont-width]+input[cont+width]<4*this->Get_input_label())
			{
				this->Countour[index_]=cont;
				index_++;
			}
		}
	}

	return VIPRET_OK;
}


/**
* @brief  Update the pixel map for the object (after the drag_label method)
*
* @param[pixelmap] input pixelmap to add or replace to existing one
* @param[area] input dimension of pixelmap array
* @return VIPRET_OK
*/
int vipMovingObject::Update_Pixel_Map(int* pixelmap,int area,int* contour,int c_len)
{
	//case of special object or single object broken..
	//so we update the pixelmap of the object..and the contour map
	if(this->processed==true)
	{
		int old_area = this->Get_area();
		int new_area = old_area+area;
		int* new_pixel_map = new int[new_area];

		memcpy(new_pixel_map,this->Get_PixelMap(),old_area*sizeof(int));
		memcpy(new_pixel_map+old_area,pixelmap,area*sizeof(int));

		delete[] this->Pixel_map;
		this->Pixel_map = new int[new_area];
		this->Area = new_area;

		memcpy(this->Pixel_map,new_pixel_map,sizeof(int)*new_area);
		delete[] new_pixel_map;

		//..idem for contour map...
		int old_len = this->Countour_lenght;
		int new_len = old_len + c_len;
		int* new_cont_map = new int[new_len];

		memcpy(new_cont_map,this->Countour,old_len*sizeof(int));
		memcpy(new_cont_map+old_len,contour,c_len*sizeof(int));

		delete[] this->Countour;
		this->Countour = new int[new_len];
		this->Countour_lenght = new_len;

		memcpy(this->Countour,new_cont_map,sizeof(int)*new_len);
		delete[] new_cont_map;

	}
	else if( this->processed == false) //replace of pixelmap..and contour map..
	{
		this->Set_processed(true);

		delete[] this->Countour;
		delete[] this->Pixel_map;

		this->Pixel_map = new int[area];
		this->Area = area;

		this->Countour = new int[c_len];
		this->Countour_lenght=c_len;

		memcpy(this->Pixel_map,pixelmap,sizeof(int)*area);
		memcpy(this->Countour,contour,sizeof(int)*c_len);
	}

	return VIPRET_OK;
}


/**
* @brief  Setup statistic for the object
*
* @param[original] input original img (no labelled)
* @return VIPRET_OK
*/
int vipMovingObject::Get_Statistic(float* original)
{
	int index=-1;   //pixel index
	float H_value=0;   //support variable

	//the indexes of pixel region is store in Pixel_map..
	//we do not need to scan the entire frame

	//original is in HSV color space...

	for(int cont=0; cont<this->Get_area(); cont++)
	{
		//calling the statistics retrieve module which works on original data frame (HSV)
		//giving as result the statistic of the region(for now the mean + hist of H component)
		index = this->Pixel_map[cont];
		H_value = original[3*index];   //NB:original[cont] is the Hue component of the pixel..

		H_mean = H_mean + H_value;
		H_hist[(int)H_value]+=1;
	}

	//H_hist normalization[0-1]..
	for(int cont=0;cont<360;cont++)
		H_hist[cont]/=this->Get_area();

	H_mean /=this->Get_area();	//mean value of H in the considered region - MovingObject


	return VIPRET_OK;
}




/**
* @brief  Repaint the object
*
* @param[input] input frame to repaint
* @return VIPRET_OK
*/
int vipMovingObject::Re_paint(unsigned char* input)
{
	for(int cont=0; cont<this->Get_area(); cont++)
	{
		int index = this->Pixel_map[cont];

		if(input[index]==this->Get_input_label())
			input[index]=(this->Get_Output_label());
	}

	//printf("\n::::::%d - %d - %d::::::",Id,this->Get_Output_label(),this->Get_input_label());getchar();

	return VIPRET_OK;
}


/**
* @brief  Repaint the object (in color)
*
* @param[input] input frame to repaint (must be 3 color plane)
* @param[width.height] frame dimension
* @return VIPRET_OK
*/
int vipMovingObject::Re_paint_Color(unsigned char* input,int width,int height)
{
	unsigned char* out_lbl = this->Get_Full_Output_label();

	for(int cont=0; cont<this->Get_area(); cont++)
	{
		int index = this->Pixel_map[cont];
		//if(input[index]==this->Get_input_label())
		input[index]=(out_lbl[0]);
		input[index+width*height]=(out_lbl[1]);
		input[index+2*width*height]=(out_lbl[2]);
	}


	return VIPRET_OK;
}


/**
* @brief  Repaint the object (in black)
*
* @param[input] input frame to repaint (must be 3 color plane)
* @param[width.height] frame dimension
* @return VIPRET_OK
*/
int vipMovingObject::Erase(unsigned char* input, int width,int height)
{
	for(int cont=0; cont<this->Get_area(); cont++)
	{
		int index = this->Pixel_map[cont];
		if(input[index]==this->Get_Output_label() && this->Is_special()==false)
		{
			input[index]=(unsigned char)0;
			input[index+width*height]=(unsigned char)128;
			input[index+2*width*height]=(unsigned char)128;
		}
	}


	return VIPRET_OK;
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
		{
			if(array_cmp(label_found,index,fin_lab[map])==0)	//store each different label once
			{
				label_found[index] = fin_lab[map];
				index++;

			}
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
	else //if(index>1)//case of fused object
	{
		//set the special tic on the actual object on stre the fused label
		this->Set_Special(index,label_found);
		delete[] label_found;

		return 1;//in origine return 1;
	}

}



/**
* @brief  Routine to copy the actual obj attributes into another
*
* @param[ptr] object array in which look for...
* @param[nr_object] input dimension of upper array (not used)
* @param[first_frame] input bool tic for the 1^frame
* @param[frame_nr] input frame_nr
* @return VIPRET_OK
*/
int vipMovingObject::copy_to(vipMovingObject* ptr,int nr_Object,bool first_frame,int frame_nr)
{
	if(first_frame==true)
	{
		//this is the first motion frame so we only copy the local object to one location
		//of ptr (global object array)according to nr_Object index(..=0)...
		//printf("first frame");getchar();

		int ID = this->Get_Id();

		this->Corrispondent_ID=ID;

		ptr[ID].In_Use = true;

		ptr[ID].Set_output_label(this->Get_Output_label());

		if(this->Is_special()==true)
			ptr[ID].Set_Special(this->fused_label_nr,this->fused_label);

		ptr[ID].Update_Pixel_Map(this->Get_PixelMap(),this->Get_area(),this->Countour,this->Countour_lenght);

		ptr[ID].presence_counter = this->presence_counter;

		ptr[ID].Set_last_frame_seen(this->Get_last_frame_seen());

		ptr[ID].H_mean = this->H_mean;
		ptr[ID].Centro_id = this->Centro_id;
		memcpy(ptr[ID].H_hist,this->H_hist,361*sizeof(float));

	}
	else //bool first_frame = false
	{
		//printf("NOT first frame");getchar();
		//before copy we need to find out the right global object..

		int index= 0;//object scan index
		unsigned char ref_label = this->Get_Output_label();
		int found_ID = Get_Global_ID(ref_label,ptr,max_global_obj_nr);

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

			ptr[found_ID].Update_Pixel_Map(this->Get_PixelMap(),this->Get_area(),this->Countour,this->Countour_lenght);

			ptr[found_ID].presence_counter +=1;

			ptr[found_ID].H_mean = this->H_mean;
			ptr[found_ID].Centro_id = this->Centro_id;
			memcpy(ptr[found_ID].H_hist,this->H_hist,361*sizeof(float));


		}
		else// if (found_ID==-1)//new object in the scene
		{
			//printf("Global not Found..\n");

			//create new global object to copy data to
			//looking for the global object with the same final label
			int ID = Get_Free_ID(ptr,max_global_obj_nr);
			if(ID==-1)printf("\n\nERROR::::Problem finding free global object::\n\n");

			this->Corrispondent_ID = ID;

			ptr[ID].In_Use = true;
			if(this->Is_special()==true)
				ptr[ID].Set_Special(this->fused_label_nr,this->fused_label);

			ptr[ID].Set_output_label(this->Get_Output_label());

			ptr[ID].Update_Pixel_Map(this->Get_PixelMap(),this->Get_area(),this->Countour,this->Countour_lenght);

			ptr[ID].presence_counter = this->presence_counter;

			ptr[ID].Set_last_frame_seen(this->Get_last_frame_seen());

			ptr[ID].H_mean = this->H_mean;
			ptr[ID].Centro_id = this->Centro_id;
			memcpy(ptr[ID].H_hist,this->H_hist,361*sizeof(float));

		}

	}

	return VIPRET_OK;
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

/**
* @brief  Routine to remove the blinking object
*
* @param[input] input labelled img (with blob_labelling(...))
* @param[ptr] input global obj array
* @param[nr_object] dimension of upper array (not used)
* @param[frame_nr] nr of actual frame
* @return VIPRET_OK
*/
int Buffer_Presence(unsigned char* input,int width,int height,vipMovingObject* ptr, int nr_Object, int frame_nr)
{
	for(int i=0;i<vipMovingObject::max_global_obj_nr;i++)
	{
	//if(ptr[i].Is_Used()==true)
	//	{
	//	//HERE INTRODUCE OBJECT RE-ENTRANCE CONTROL
	//	//BEFORE TO INSTANCIATE NEW OBJECT(MEAN CONSIDER THE POSSIBILITY
	//	//THE ENTERED OBJ IS AN ALREADY SEEN OBJECT THAT LEAVED THE SCENE:
	//	//IF CONTROL FAIL THE NEW (UNKNOWN) OBJECT IS INSTANCIATED)
	//


	//	//setup of visualization object delay..
	////	if(ptr[i].Get_presence_counter()<obj_visualization_delay)
	////		ptr[i].Erase(input,width,height);//color repaint in black...
	//
	//	}


		//setup of delay after which free the global object..
		if((frame_nr - ptr[i].Get_last_frame_seen())>=obj_free_delay && ptr[i].Get_last_frame_seen()!=0)

			//reset object parameter.
			ptr[i].Reset();


		//calculation and drawing of trajectory for the active obj..
		if(ptr[i].Is_Active()==true)
		{
			if(ptr[i].Get_presence_counter()>obj_visualization_delay || ptr[i].Is_special()==true)
			{
				int c_id = ptr[i].set_Centro_id(width,height);

				ptr[i].Add_Centro_id();

				if( ptr[i].Is_special() == false )
				{
					//ordinary object..
					ptr[i].Draw_Trajectory(input,width,height);
					ptr[i].Draw_Bounding_Box(input,width,height);
				}
				else //special object case.. write the trajectory of fused object...
				{
					int nr_object=ptr[i].Get_fused_label_nr();
					unsigned char* fused_object;

					fused_object = ptr[i].Get_fused_label();
					for(int j=0;j<nr_object;j++)
						{
						int ID = Get_Global_ID(fused_object[j],ptr,25);
						if(ID!=-1)
						ptr[ID].Draw_Trajectory(input,width,height);

						}
					ptr[i].Draw_Bounding_Box(input,width,height);

				}//end if (is special)else

				ptr[i].Draw_Silhouette(input,width,height);

	//object information.. WORKING; JUST COMMENTED
	/*
				printf("                                                                     \n");
				printf("\nGlobal Object nr.[%d]\t\t\t\t\t\t\n",i);
				printf("Label component YUV -> %d %d %d\t\t\t\t\t\t\n",ptr[i].Get_Full_Output_label()[0],ptr[i].Get_Full_Output_label()[1],ptr[i].Get_Full_Output_label()[2]);
				printf(">Area = %d\t\t\t\t\t\t\n>Contour lenght = %d\t\t\t\t\t\t\n",ptr[i].Get_area(),ptr[i].get_Countour_lenght());
				printf(">Presence Counter = %d\t\t\t\t\t\t\n",ptr[i].Get_presence_counter());
				//printf(">Timer=%d!!\t\t\t\t\t\t\n",frame_nr +1 - ptr[i].Get_last_frame_seen());
				printf(">IsSpecial = %s\t\t\t\t\t\t\n",ptr[i].Get_special());
				printf(">Hue Mean value = %f\t\t\t\t\t\t\n",ptr[i].get_H_mean());
				printf("                                                                     \n");
	*/

					//only for visualization porpouse
			/*		char* clr = "                                  \n";

				for(int c=0;c<20;c++)
					printf("%s",clr);
				HANDLE hOut;
				COORD Position;
				hOut = GetStdHandle(STD_OUTPUT_HANDLE);
				Position.X = 2;
				Position.Y = 36;
				SetConsoleCursorPosition(hOut,Position);*/
			}
		}//end if (is active)

		//for the next frame...
		ptr[i].Set_Active(false);
		ptr[i].Set_processed(false);
		}

	return VIPRET_OK;
	}







/**
* @brief  discriminate beetween obj after occlusion
*
* @param[Local_array] input local_array_object
* @param[Global_array] input global_array_object
* @param[lbl]input label of fused global
* @return VIPRET_OK
*/
int Discriminate(vipMovingObject* Local_array,vipMovingObject* Global_array,unsigned char lbl,int nr_lbl)
	{

		int Global_ID = Get_Global_ID(lbl,Global_array,vipMovingObject::max_global_obj_nr);
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
			fused_obj_GLOBAL_ID[cont]=Get_Global_ID(lbl_fused_obj[cont],Global_array,vipMovingObject::max_global_obj_nr);

		//need to scan ALL local_array to find right ones..
		int index=0;
		for(int cont=0;cont<nr_lbl;cont++)
			if(Local_array[cont].Get_Output_label()==lbl)
				{
				fused_obj_LOCAL_ID[index]=Local_array[cont].Get_Id();
				index++;
				}


		//now call the function to make an histogram-based discriminance
		//the ID's of object to compare are stored in fused_obj_LOCAL_ID & fused_obj_GLOBAL_ID
		//substancially we procede making an histogram intersection normalized
		//(result in range 0-1)

		for(int i=0;i<nr_fused_obj;i++)//scroll Global
			{
			float k =0;
			float h =0;
			int ID_choosen=0;

			for(int j=0;j<nr_fused_obj;j++)//scroll the Local
				{
				h = Global_array[fused_obj_GLOBAL_ID[i]].Hist_Intersection(Local_array[fused_obj_LOCAL_ID[j]]);
			/*	printf("                                                              \n");
				printf("Similarity between Global[%d]-Local[%d]==>[ %f ]\t\t\t\t\t\t\t\t\t\t\t\t\n",fused_obj_GLOBAL_ID[i],fused_obj_LOCAL_ID[j],h);
			*/
				if(h > k)
					{
					ID_choosen = fused_obj_LOCAL_ID[j];//ID of LOCAL_OBJ "corrispondent" to GLOBAL_OBJ[i]
					k=h;
					}
				}//end for(..) Local scroll


			/*printf("                             \n");
			printf("ID_choosen= [%d]..\t\t\t\t\t\t\n",ID_choosen);
			printf("                             \n");
			*/
			//only for repaint right color..

			Local_array[ID_choosen].Set_output_label(Global_array[fused_obj_GLOBAL_ID[i]].Get_Output_label());

			Global_array[fused_obj_GLOBAL_ID[i]].Set_Used(true);
			Global_array[fused_obj_GLOBAL_ID[i]].Presence(true);
			Global_array[fused_obj_GLOBAL_ID[i]].Set_PixelMap(Local_array[ID_choosen].Get_PixelMap());
			Global_array[fused_obj_GLOBAL_ID[i]].Set_area(Local_array[ID_choosen].Get_area());

			Global_array[fused_obj_GLOBAL_ID[i]].set_H_mean(Local_array[ID_choosen].get_H_mean());
			Global_array[fused_obj_GLOBAL_ID[i]].set_H_hist(Local_array[ID_choosen].get_H_hist());


			}//end for(..) Global scroll..

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
		printf("\nIsSpecial Check NOT passed...\n"); //getchar();
		}

	return VIPRET_OK;
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
		if(label==ptr[i].Get_Output_label())
			//may would be a special tic controll...

			return ptr[i].Get_Id();
		}

	return -1;
	}
