// vipMotionTracker.h

#ifndef _VIP_MOTION_TRACKER_H
#define _VIP_MOTION_TRACKER_H
#pragma once



//////////////////////////////////////////////////////
// MONO - STEREO FLAG: Define/Undefine as needed	//
// define VMT_STEREOTRACK to use STEREO				//
// comment define to use MONO						//
//#define VMT_STEREOTRACK								//
//////////////////////////////////////////////////////




// Standard Includes
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <math.h>
#include <time.h>

// vipLib HSV Frame Include (required)
#include <vipFrameHSV.h>

// Defines ( "options" )
#define MAX_GLOBAL_OBJ_NR	40
#define	MAX_TRACKABLE_OBJS	40
#define MIN_BLOB_SIZE		120

class vipMovingObject
{

protected:

	int Id;  //object identifier
	int Corrispondent_ID; //parallel id of global object..()
	unsigned char Input_label,Y_Output_label,U_Output_label,V_Output_label;  //input output label
	int Centro_id;	//store the centroid position (progrssive nr, like pixel_map)
	int Bounding_box[4];  //store top-bottom-left-right bounding box value
	float* Trajectory;  //store the sequence of centroid 3d position(meters)
	bool Special;	 //true = special object; false = normal object
	bool In_Use;	//true if the object is used or false if could be overwritten
	//bool Active;    //true if the object is to visualize..
	int Area;    //area of specified region
	int Countour_lenght; // contour
	float Compactness;
	int* Pixel_map;   //array of indexes of pixel's region
	int* Countour;
	float H_mean;    //statistic = H mean
	float H_hist[361];   //statistic = histogram for Hue component
	int D_hist[256];     //statistic = hist for depth(8bit)..

	//next 2 feature is used only if the object is target as 'SPECIAL'
	unsigned char* fused_label;  //array of label fused in this object
	int fused_label_nr;  //lenght of fused_label array

	int presence_counter; //counter for object presence, used to remove the blinking object
	int nr_last_frame;	 //nr of frame where the object has been seen
	bool processed; //tic for the copying operation from local to global array

	//3d info (relative to the object's centro_id 
	//assuming the mean disparity of the region) 
	float x, y, z;
	unsigned char disparity;  //average value for the region...
	unsigned short disp16;

public:

	vipMovingObject()		// default constructor
	{
		Id = -1;
		In_Use = false;
//		Active = false;
		Input_label = (unsigned char) 0;
		Y_Output_label = (unsigned char) 0;
		U_Output_label = (unsigned char) 0;
		V_Output_label = (unsigned char) 0;
		Special=false;
		Centro_id= -1;
		Trajectory = NULL;
		Area=0;
		Countour_lenght=0;
		Compactness=0;
		H_mean = 0;
		Pixel_map = NULL;
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
		for(int i=0;i<256;i++)
			D_hist[i]=0;

		x = y = z = 0.0;
		disparity = 0;
		disp16=0x0000;
	}


	inline int Get_Corrispondent()	{return Corrispondent_ID;}

	inline void Reset(void)
	{
		In_Use = false;
		//Active = false;
		Input_label = (unsigned char) 0;
		Y_Output_label = (unsigned char) 0;
		U_Output_label = (unsigned char) 0;
		V_Output_label = (unsigned char) 0;
		Special=false;
		Centro_id= -1;
		delete[] Trajectory;
		Trajectory = NULL;
		Area=0;
		Countour_lenght=0;
		Compactness=0;
		H_mean = 0;
		free(Pixel_map);
		//delete[] Pixel_map;
		fused_label_nr = 0;
		Pixel_map = NULL;
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
		for(int i=0;i<256;i++)
			D_hist[i]=0;

		x = y = z = 0.0;
		disparity = 0;
		disp16=0x0000;
	}

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
		/** Here it is needed to check if the current obj is already special
		if so add the new fused obj and update the stat...	
		*/
		//first set the special tic on the object
		Special=true;
		//store the label fused in the object structure
		fused_label_nr = nr_label;
		fused_label = new unsigned char[nr_label];

		for(int cont=0;cont<nr_label;cont++)
			fused_label[cont] = label_array[cont];

	}
	inline void Add_fused_label_nr(void){fused_label_nr++;}
	void Update_fused_label(vipMovingObject* global,int special);

	int DisJoint_Special(vipMovingObject* Global_array,vipFrameHSV* original,unsigned short* depth16, unsigned char* labelled, unsigned char* previous_lab);

	inline bool Is_Used(void) {return In_Use;}
	inline void Set_Used(bool val){In_Use = val;}

	//inline void Set_Active(bool val){Active = val;}
	//inline bool Is_Active(void){return Active;}

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
			U_Output_label = (unsigned char)(rand()%256);
			srand(U_Output_label);
			V_Output_label = (unsigned char)(rand()%256);
		}
		else
		{
			Y_Output_label = 0;
			U_Output_label = 128;
			V_Output_label = 128;

		}

	}

	inline unsigned char Get_Output_label(int index)
	{
		if(index==0)
			return Y_Output_label;
		else
			if(index==1)
				return U_Output_label;
			else
				if(index==2)
					return V_Output_label;
				else
					return(-1);//problems if exit here..

	}

	inline int Get_fused_label_nr(void){return fused_label_nr;}
	inline unsigned char* Get_fused_label(void){return fused_label;}

	inline int Get_area(void){return Area;}
	inline void Set_area(int sup){Area=sup;}


	inline int get_Countour_lenght(){return Countour_lenght;}
	int Set_PixelMap(unsigned char* input,int width,int height,bool first_frame);

	inline void Set_PixelMap(int* ptr)
	{
		//if(Pixel_map) delete[] Pixel_map;
		Pixel_map = new int[Area];
		memcpy(Pixel_map,ptr,Area*sizeof(int));
	}

	inline int* Get_PixelMap(){return Pixel_map;}
	int Update_Pixel_Map(int* pixelmaptoadd,int area);
	int Update_Pixel_Map(vipMovingObject object);
	inline void Presence(bool val){if (val==true)presence_counter+=1;}
	inline int Get_presence_counter(void){return presence_counter;}


	inline void Set_last_frame_seen(int nr){nr_last_frame=nr;}
	inline int Get_last_frame_seen(void){return nr_last_frame;}


	int drag_label(unsigned char* input,unsigned char* prev_lab);
	unsigned char get_Spatial_nearest_label(vipMovingObject* Global_Object_array, int width, int height );
	unsigned char get_Depth_nearest_label(vipMovingObject* array);

	int Get_Statistic(vipFrameHSV* original,unsigned short* depth16 = NULL);	// param2 default null for MONO case (ignores depth info)
	inline float get_H_mean(void){return H_mean;}
	inline void set_H_mean(float val){H_mean=val;}
	inline unsigned char get_Disparity(void){return disparity;}
	inline unsigned short get_Disparity16(void){return disp16;}	

	float Hist_Intersection(vipMovingObject obj);
	int hist_th(vipMovingObject* disjoined_obj,unsigned short* depth16);
	inline float* get_H_hist(void){return H_hist;}
	inline int* get_D_hist(void){return D_hist;}
	int get_Depth_Hist_Th(void);

	inline void set_H_hist(float* ptr){memcpy(H_hist,ptr,361*sizeof(float));}
	inline int set_Centro_id(int width,int height)
	{
		if(this->Is_Used() == true)
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
		}//end if (IsUsed ==true)
		else
		{  printf("\n\t:::WARNING:Problem in calculation of centro_id: the object not In_Use:::\n");
			return -1;
		}
	}



	inline int get_BBox(int i){return Bounding_box[i];}
	inline int get_Centro_id(){return Centro_id;}

	/*REVIEW this procedure and insert some kind of memory realloc
	instead of static allocation*/
	inline void Add_Centro_id()
	{
		if(Trajectory==NULL)
		{
			Trajectory = new float[2500];
			memset(Trajectory,-1,2500*sizeof(float));
		}

		Trajectory[presence_counter*3]=x;
		Trajectory[presence_counter*3+1]=y;
		Trajectory[presence_counter*3+2]=z;
	}

	inline void Set_3Dpos(float px, float py, float pz)
	{
		x=px;
		y=py;
		z=pz;
		//add the 3d centroid position in meter to trajectory array...
		Add_Centro_id();
	}


	//inline void Draw_Trajectory(unsigned char* frame,int width,int height)
	//{
	// if(Trajectory != NULL)
	// {
	//  for(int i = 0; i<presence_counter; i++)
	////draw centro_id sequence..


	//if(Trajectory[i]!=-1)
	// //draw '+' pattern
	//{
	// frame[Trajectory[i]]=Y_Output_label;
	// frame[Trajectory[i]+width*height]=U_Output_label;
	// frame[Trajectory[i]+2*width*height]=V_Output_label;
	// frame[Trajectory[i]+1]=Y_Output_label;
	// frame[Trajectory[i]+1+width*height]=U_Output_label;
	// frame[Trajectory[i]+1+2*width*height]=V_Output_label;
	// frame[Trajectory[i]-1]=Y_Output_label;
	// frame[Trajectory[i]-1+width*height]=U_Output_label;
	// frame[Trajectory[i]-1+2*width*height]=V_Output_label;
	// frame[Trajectory[i]+width]=Y_Output_label;
	// frame[Trajectory[i]+width+width*height]=U_Output_label;
	// frame[Trajectory[i]+width+2*width*height]=V_Output_label;
	// frame[Trajectory[i]-width]=Y_Output_label;
	// frame[Trajectory[i]-width+width*height]=U_Output_label;
	// frame[Trajectory[i]-width+2*width*height]=V_Output_label;
	//}
	// }

	//}

	inline float* get_Trajectory(){return Trajectory;}

	inline void Draw_Bounding_Box(unsigned char* frame,int width,int height)
	{
	 int size = width*height;	// added by MV to avoid some multplies
		//draw bounding box
		for(int row=Bounding_box[0];row<Bounding_box[1];row++)
		{
			frame[row*width+Bounding_box[2]]=Y_Output_label;
			frame[row*width+Bounding_box[3]]=Y_Output_label;
			frame[row*width+Bounding_box[2]+size]=U_Output_label;
			frame[row*width+Bounding_box[3]+size]=U_Output_label;
			frame[row*width+Bounding_box[2]+size*2]=V_Output_label;
			frame[row*width+Bounding_box[3]+size*2]=V_Output_label;
		}

		for(int col=Bounding_box[2];col<Bounding_box[3];col++)
		{
			frame[Bounding_box[0]*width+col]=Y_Output_label;
			frame[Bounding_box[1]*width+col]=Y_Output_label;
			frame[Bounding_box[0]*width+col+size]=U_Output_label;
			frame[Bounding_box[1]*width+col+size]=U_Output_label;
			frame[Bounding_box[0]*width+col+2*size]=V_Output_label;
			frame[Bounding_box[1]*width+col+2*size]=V_Output_label;
		}

	}

	inline void Draw_Silhouette(unsigned char* frame,int width,int height)
	{
			int size = width*height;	// added by MV to avoid some multplies
		for(int i=0;i<Countour_lenght;i++)
		{
			frame[Countour[i]]=Y_Output_label;
			frame[Countour[i]+size]=U_Output_label;
			frame[Countour[i]+2*size]=V_Output_label;

		}

	}


	int Re_paint(unsigned char* input);
	int Re_paint_Color(unsigned char* input,int width,int height);

	int copy_to(vipMovingObject* ptr,int nr_Object,bool first_frame);

	bool overlap(vipMovingObject obj);

};	// END OF class vipMovingObject


//// Utility methods:
#ifdef VMT_STEREOTRACK
 int Blob_Tracking( vipFrameHSV* input, unsigned char* rect_yuv,unsigned char* depth_yuv, unsigned short *imagedepth16data, unsigned char* blobs, int frame_nr );
#else
 int Blob_Tracking( vipFrameHSV* input, unsigned char* blobs, int frame_nr );
#endif // VMT_STEREOTRACK
 int array_cmp(unsigned char* in1, int nrlbl, unsigned char value);




#ifdef VMT_STEREOTRACK
 int Buffer_Presence(unsigned char* rect_yuv,unsigned char* input,unsigned char* depth16,int width,int height,vipMovingObject* ptr, int nr_Object, int frame_nr);
#else
 int Buffer_Presence(unsigned char* input,unsigned char* depth16,int width,int height,vipMovingObject* ptr, int nr_Object, int frame_nr);
#endif // VMT_STEREOTRACK




int Discriminate(vipMovingObject* Local_Object_array,vipMovingObject* Global_Object_array,unsigned char duplicated_label,int lbl_nr);
int Get_Free_ID(vipMovingObject* ptr,int nr_object);
int Get_Global_ID(unsigned char label,vipMovingObject* ptr,int nr_object);
void TrackerCleanUp();

// CCL stuff NOW IN support.h
//int ConnectedComponentLabeling(unsigned char* bitmap,unsigned char*labelmap,int width,int height);
//// End of Utility methods



#endif	// _VIP_MOTION_TRACKER_H