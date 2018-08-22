/**
 *  @class   vipMovingObject
 *
 *  @brief

 *  @bug
 *  @warning
 *  @todo
 *
 *  @see
 *
 *  @version 1.1.0
 *  @date    2007-10-08
 *  @author  Alessandro Polo (updated)
 *           Nicola Piotto (written)
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

#ifndef __VIPLIB_VIPMOVINGOBJECT_H__
 #define __VIPLIB_VIPMOVINGOBJECT_H__

#include <stdlib.h>
#include <string.h>
#include <math.h>


				//for buffer_presence method    vip_movng_object.cpp
//				int obj_visualization_delay; //delay in visualization (in nr of frame)7
//				int obj_free_delay; //consecutive nr of frame of inactivity after which freeing the object



class vipMovingObject
	{

	protected:

		int Id;  //object identifier

		int Corrispondent_ID; //parallel id of global object..()

		unsigned char Input_label,Y_Output_label,U_Output_label,V_Output_label;  //input output label

		int Centro_id;	//store the centroid position (progrssive nr, like pixel_map)
		int Bounding_box[4];  //store top-bottom-left-right bounding box value

		int* Trajectory;  //store the sequence of centroid position

		bool Special;	 //true = special object; false = normal object

		bool In_Use;	//true if the object is used or false if could be overwritten
		bool Active;    //true if the object is to visualize..

		int Area;    //area of specified region
		int Countour_lenght; // contour
		float Compactness;

		int* Pixel_map;   //array of indexes of pixel's region
		int* Countour;

		float H_mean;    //statistic = H mean

		float H_hist[361];   //statistic = histogram for Hue component

		//next 2 feature is used only if the object is target as 'SPECIAL'
		unsigned char* fused_label;  //array of label fused in this object
		int fused_label_nr;  //lenght of fused_label array

		int presence_counter; //counter for object presence, used to remove the blinking object

		int nr_last_frame;	 //nr of frame where the object has been seen

		bool processed; //tic for the copying operation from local to global array


	public:

//		static int Buffer_Presence(unsigned char* input,int width,int height,vipMovingObject* ptr, int nr_Object, int frame_nr);
		const static int max_global_obj_nr = 25;


	public:

		vipMovingObject();


	void Reset();

		inline int Get_Corrispondent(){return Corrispondent_ID;}


	int Erase(unsigned char* input, int width,int height);

	inline bool Is_special(void) { return Special; }
	inline char* Get_special(void)
	{
	 char* val;
	 val = (Special==0) ? "FALSE" : "TRUE";
	  return val;
	}
	inline void Reset_Special(void){Special=false;}
	inline void Set_Special(int nr_label,unsigned char* label_array)
	{
	//first set the special tic on the object
	Special=true;

	//store the label fused in the object structure
	fused_label_nr = nr_label;
	fused_label = new unsigned char[nr_label];

	for(int cont=0;cont<nr_label;cont++)
		fused_label[cont] = label_array[cont];

	}



	inline bool Is_Used(void) {return In_Use;}
	inline void Set_Used(bool val){In_Use = val;}

	inline void Set_Active(bool val){Active = val;}
	inline bool Is_Active(void){return Active;}



	inline void Set_processed(bool value){processed = value; }


	inline void Set_Id(int num){Id = num;}
	inline int Get_Id(void){return Id;}


	inline void Set_input_label(unsigned char label){ Input_label = label; }
	inline unsigned char Get_input_label(void){ return Input_label; }

	inline void Set_output_label(unsigned char label)
		{
		if((int)label!=0)
			{
			srand(label);
			Y_Output_label = label;
			U_Output_label = (unsigned char)(rand());
			srand(U_Output_label);
			V_Output_label = (unsigned char)(rand());
			}
		else
			{
			Y_Output_label = 0;
			U_Output_label = 128;
			V_Output_label = 128;

			}


		//printf("Y%d U%d V%d",Y_Output_label,U_Output_label,V_Output_label);getchar();
		}
	inline unsigned char* Get_Full_Output_label(void)
		{
		unsigned char* out_lbl = new unsigned char[3];
		out_lbl[0]=Y_Output_label;
		out_lbl[1]=U_Output_label;
		out_lbl[2]=V_Output_label;

		return out_lbl;
		}
	inline unsigned char Get_Output_label(){return Y_Output_label;}


	inline int Get_fused_label_nr(void){return fused_label_nr;}
	inline unsigned char* Get_fused_label(void){return fused_label;}


	inline int Get_area(void){return Area;}
	inline void Set_area(int sup){Area=sup;}


	inline int get_Countour_lenght(){return Countour_lenght;}
	int Set_PixelMap(unsigned char* input,int width,int height);
	inline void Set_PixelMap(int* ptr){Pixel_map=ptr;}
	inline int* Get_PixelMap(){return Pixel_map;}
	int Update_Pixel_Map(int* pixelmaptoadd,int area,int* contour,int c_len);
	inline void Presence(bool val){if (val==true)presence_counter+=1;}
	inline int Get_presence_counter(void){return presence_counter;}


	inline void Set_last_frame_seen(int nr){nr_last_frame=nr;}
	inline int Get_last_frame_seen(void){return nr_last_frame;}


	int drag_label(unsigned char* input,unsigned char* prev_lab);
	int Get_Statistic(float* original);
	inline float get_H_mean(void){return H_mean;}
	inline void set_H_mean(float val){H_mean=val;}

	float Hist_Intersection(vipMovingObject obj);
	inline float* get_H_hist(void){return H_hist;}
	inline void set_H_hist(float* ptr){memcpy(H_hist,ptr,361*sizeof(float));}


	int set_Centro_id(int width,int height);

	inline int* get_Bounding_box() { return Bounding_box; };

	inline int get_Centro_id(){return Centro_id;}

	inline void Add_Centro_id()
		{
		if(Trajectory==NULL)
			{
			Trajectory = new int[2500];/////////////////////////////////////////////////
			memset(Trajectory,-1,2500*sizeof(int));
			}
		Trajectory[presence_counter]=Centro_id;
		}

	inline void Draw_Trajectory(unsigned char* frame,int width,int height)
		{
		if(Trajectory != NULL)
			{
			for(int i = 0; i<presence_counter; i++)
				//draw centro_id sequence..


				if(Trajectory[i]!=-1)
					//draw '+' pattern
					{
					frame[Trajectory[i]]=Y_Output_label;
					frame[Trajectory[i]+width*height]=U_Output_label;
					frame[Trajectory[i]+2*width*height]=V_Output_label;
					frame[Trajectory[i]+1]=Y_Output_label;
					frame[Trajectory[i]+1+width*height]=U_Output_label;
					frame[Trajectory[i]+1+2*width*height]=V_Output_label;
					frame[Trajectory[i]-1]=Y_Output_label;
					frame[Trajectory[i]-1+width*height]=U_Output_label;
					frame[Trajectory[i]-1+2*width*height]=V_Output_label;
					frame[Trajectory[i]+width]=Y_Output_label;
					frame[Trajectory[i]+width+width*height]=U_Output_label;
					frame[Trajectory[i]+width+2*width*height]=V_Output_label;
					frame[Trajectory[i]-width]=Y_Output_label;
					frame[Trajectory[i]-width+width*height]=U_Output_label;
					frame[Trajectory[i]-width+2*width*height]=V_Output_label;
					}
			}


		}

	inline void Draw_Bounding_Box(unsigned char* frame,int width,int height)
		{
		//draw bounding box
		for(int row=Bounding_box[0];row<Bounding_box[1];row++)
			{
			frame[row*width+Bounding_box[2]]=Y_Output_label;
			frame[row*width+Bounding_box[3]]=Y_Output_label;
			frame[row*width+Bounding_box[2]+width*height]=U_Output_label;
			frame[row*width+Bounding_box[3]+width*height]=U_Output_label;
			frame[row*width+Bounding_box[2]+width*height*2]=V_Output_label;
			frame[row*width+Bounding_box[3]+width*height*2]=V_Output_label;
			}

		for(int col=Bounding_box[2];col<Bounding_box[3];col++)
			{
			frame[Bounding_box[0]*width+col]=Y_Output_label;
			frame[Bounding_box[1]*width+col]=Y_Output_label;
			frame[Bounding_box[0]*width+col+width*height]=U_Output_label;
			frame[Bounding_box[1]*width+col+width*height]=U_Output_label;
			frame[Bounding_box[0]*width+col+2*width*height]=V_Output_label;
			frame[Bounding_box[1]*width+col+2*width*height]=V_Output_label;
			}

		}

	inline void Draw_Silhouette(unsigned char* frame,int width,int height)
		{
		for(int i=0;i<Countour_lenght;i++)
			{
			frame[Countour[i]]=Y_Output_label;
			frame[Countour[i]+width*height]=U_Output_label;
			frame[Countour[i]+2*width*height]=V_Output_label;

			}

		}




	int Re_paint(unsigned char* input);
	int Re_paint_Color(unsigned char* input,int width,int height);


	int copy_to(vipMovingObject* ptr,int nr_Object,bool first_frame,int frame_nr);


	};








int Buffer_Presence(unsigned char* input,int width,int height,vipMovingObject* ptr, int nr_Object, int frame_nr);

int Discriminate(vipMovingObject* Local_Object_array,vipMovingObject* Global_Object_array,unsigned char duplicated_label,int lbl_nr);

int Get_Free_ID(vipMovingObject* ptr,int nr_object);

int Get_Global_ID(unsigned char label,vipMovingObject* ptr,int nr_object);


#endif //__VIPLIB_VIPMOVINGOBJECT_H__
