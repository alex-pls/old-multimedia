#ifndef _VIP_MOVING_OBJECT_H
#define _VIP_MOVING_OBJECT_H
#pragma once

#include "vipFrameHSV.h"
#include <math.h>
#include <time.h>
#include <tracking/vipTrajectoryUtil.h>

// To use the STEREO version of the tracker, define VMT_STEREOTRACK in your project properties:
// (VS2005: Configuration Properties -> C/C++ -> Preprocessor -> Preprocessor Definitions

#define	DEFAULT_MIN_BLOB_SIZE		120
#define DEFAULT_MAX_GLOBAL_OBJ_NR	100



class vipMovingObject
{
	friend class vipMotionTracker;	// grant access to the "master" tracker

protected:
	int iMinBlobSize; 
	int iMaxGlobalObjNr;
	FILE	*std_error;
	vipMovingObject		*vMO_Global;	// should always point to the "global" object array
	unsigned int frmWidth;		// width of the frame from which this moving object has been extracted
	unsigned int frmHeight;		// height of the frame from which this moving object has been extracted


	int		Id;  //object identifier
	int		Corrispondent_ID; //parallel id of global object..()
	int		iHandOverHook;	// used in (optional) hand over proecedures. represents corresponding object's position in the shared storage
	time_t	tCreationTime;	// the second this vmo was detected and created
	
	unsigned char Input_label,Y_Output_label,U_Output_label,V_Output_label;  //input output label
	
	int Centro_id;	//store the centroid position (progrssive nr, like pixel_map)
	int Bounding_box[4];  //store top-bottom-left-right bounding box value
	float* Trajectory;  //store the sequence of centroid 3d position(meters)
	
	bool In_Use;	//true if the object is used or false if could be overwritten
	int Area;    //area of specified region
	int Countour_lenght; // contour
	float Compactness;
	int* Pixel_map;   //array of indexes of pixel's region
	int* Countour;
	float H_mean;    //statistic = H mean
	float H_hist[361];   //statistic = histogram for Hue component
	int D_hist[256];     //statistic = hist for depth(8bit)..
	
	bool Special;	 //true = special object; false = normal object
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

	// trajectory
	vipTrajectory<unsigned int>	*m_pBlobTrajectory;	// keeps blob trajectory inside image (measured in pixels)
	vipTrajectory<float>		*m_pWorldTrajectory;	// keeps estimated trajectory in real world (measured in meters)

public:

	vipMovingObject()		// default constructor
	{
		iMinBlobSize = DEFAULT_MIN_BLOB_SIZE;
		iMaxGlobalObjNr = DEFAULT_MAX_GLOBAL_OBJ_NR;
		frmHeight = 0;
		frmWidth = 0;
		std_error = NULL;	//todo
		vMO_Global = NULL;	//must be a pointer to the array of vmo's created by tracker. handled by vipMotionTracker default constructor
		Id					= -1;
		Corrispondent_ID	= -1;
		iHandOverHook		= -1;
		tCreationTime		= -1;

		Input_label =	 (unsigned char) 0;
		Y_Output_label = (unsigned char) 0;
		U_Output_label = (unsigned char) 0;
		V_Output_label = (unsigned char) 0;
		
		Centro_id= -1;
		Bounding_box[0]=240;	//top
		Bounding_box[1]=0;		//bottom
		Bounding_box[2]=320;	//left
		Bounding_box[3]=0;		//right
		Trajectory = NULL;
		
		x = y = z = 0.0;
		disparity = 0;
		disp16=0x0000;
		
		Special=false;
		fused_label_nr = -1;
		fused_label = NULL;
		
		In_Use = false;
		Area=0;
		Countour_lenght=0;
		Compactness=0;
		Countour = NULL;
		H_mean = 0;
		Pixel_map = NULL;
		
		presence_counter = 0;
		nr_last_frame = 0;
		processed = false;
		
		//init to 0 H_hist array
		memset(H_hist,0,360*sizeof(float));
		memset(H_hist,0,255*sizeof(int));

		// trajectory stuff
		m_pBlobTrajectory =	new vipTrajectory<unsigned int>( 128, true, true, true );
		m_pWorldTrajectory = new vipTrajectory<float>( 128, true, true, true );
	
		
	}

	~vipMovingObject()
	{
		if( Trajectory != NULL )
			delete[] Trajectory;
		if( Pixel_map != NULL )
			free( Pixel_map );
		if( Countour != NULL )
			delete[] Countour;
		if( fused_label != NULL )
			delete[] fused_label;

		if( m_pBlobTrajectory != NULL )
			delete m_pBlobTrajectory;
		if( m_pWorldTrajectory != NULL )
			delete m_pWorldTrajectory;
	}


	inline int Get_MaxGlobalObjNr(void){return iMaxGlobalObjNr;}
	inline vipTrajectory<unsigned int>* getBlobTrajectory() { return m_pBlobTrajectory; }
	inline vipTrajectory<float>* getWorldTrajectory() { return m_pWorldTrajectory; }
	inline int getHandOverHook() { return iHandOverHook; }
	inline void setHandOverHook( int val ) { iHandOverHook = val; }
	inline time_t getCreationTime() { return tCreationTime; }
	inline void setCreationTime( time_t val ) { tCreationTime = val; }

	inline int Get_Corrispondent()	{return Corrispondent_ID;}

	inline void Reset(void)
	{
		iMinBlobSize = DEFAULT_MIN_BLOB_SIZE;
		iMaxGlobalObjNr = DEFAULT_MAX_GLOBAL_OBJ_NR;
		std_error = NULL;//todo
		vMO_Global = NULL;//must be a pointer to the array of vmo's created by tracker. handled by vipMotionTracker default constructor
		Input_label = (unsigned char) 0;
		Y_Output_label = (unsigned char) 0;
		U_Output_label = (unsigned char) 0;
		V_Output_label = (unsigned char) 0;
		Centro_id= -1;
		Bounding_box[0]=240;	//top			// TODO: generalize? maybe it is already re-set somewhere else, though
		Bounding_box[1]=0;		//bottom
		Bounding_box[2]=320;	//left
		Bounding_box[3]=0;		//right

		iHandOverHook = -1;

		delete[] Trajectory;
		Trajectory = NULL;
		x = y = z = 0.0;
		disparity = 0;
		disp16=0x0000;
		
		Special=false;
		fused_label_nr = -1;
		fused_label = NULL;
		In_Use = false;
		Area=0;
		Countour_lenght=0;
		Compactness=0;

		delete[] Countour;
		Countour = NULL;
		H_mean = 0;
		//printf("\nPixel map has %i mem allocated.\n", _msize(Pixel_map) );
		if( Pixel_map)
			free(Pixel_map);
		Pixel_map = NULL;
		
		presence_counter = 0;
		nr_last_frame = 0;
		processed = false;
		
		memset(H_hist,0,360*sizeof(float));
		memset(H_hist,0,255*sizeof(int));

		// (new) trajectory stuff
		m_pBlobTrajectory->reAlloc( 128, true, true, true );	// allocate 128 initial positions 
		m_pWorldTrajectory->reAlloc( 128, true, true, true );

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
		if(Pixel_map) delete[] Pixel_map;
		Pixel_map = new int[Area];
		memcpy(Pixel_map,ptr,Area*sizeof(int));
	}

	inline int* Get_PixelMap(){return Pixel_map;}
	int Update_Pixel_Map(int* pixelmaptoadd,int area);
	int Update_Pixel_Map(vipMovingObject *object);
	inline void Presence(bool val){if (val==true)presence_counter+=1;}
	inline int Get_presence_counter(void){return presence_counter;}


	inline void Set_last_frame_seen(int nr){nr_last_frame=nr;}
	inline int Get_last_frame_seen(void){return nr_last_frame;}


	int drag_label(unsigned char* input,unsigned char* prev_lab);
	unsigned char get_Spatial_nearest_label( int width, int height );
	unsigned char get_Depth_nearest_label(vipMovingObject* array);

	int Get_Statistic(vipFrameHSV* original,unsigned short* depth16 = NULL);	// param2 default null for MONO case (ignores depth info)
	inline float get_H_mean(void){return H_mean;}
	inline void set_H_mean(float val){H_mean=val;}
	inline unsigned char get_Disparity(void){return disparity;}
	inline unsigned short get_Disparity16(void){return disp16;}	

	float Hist_Intersection(vipMovingObject *obj);
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
				col=(int) (fmod((float)Pixel_map[i],(float)frmWidth));
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


#ifdef VMT_STEREOTRACK	// todo: do better parametrization
			this->Centro_id=sum_row*width+sum_col;	// original centro_id by NP
#else
			this->Centro_id = (frmWidth*((Bounding_box[0]+Bounding_box[1])/2))+((Bounding_box[2]+Bounding_box[3])/2);		// as bounding box centre
#endif

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
	 int sizex2 = size*2;
		//draw bounding box
		for(int row=Bounding_box[0];row<Bounding_box[1];row++)
		{
			frame[row*width+Bounding_box[2]]=Y_Output_label;
			frame[row*width+Bounding_box[3]]=Y_Output_label;
			frame[row*width+Bounding_box[2]+size]=U_Output_label;
			frame[row*width+Bounding_box[3]+size]=U_Output_label;
			frame[row*width+Bounding_box[2]+sizex2]=V_Output_label;
			frame[row*width+Bounding_box[3]+sizex2]=V_Output_label;
		}

		for(int col=Bounding_box[2];col<Bounding_box[3];col++)
		{
			frame[Bounding_box[0]*width+col]=Y_Output_label;
			frame[Bounding_box[1]*width+col]=Y_Output_label;
			frame[Bounding_box[0]*width+col+size]=U_Output_label;
			frame[Bounding_box[1]*width+col+size]=U_Output_label;
			frame[Bounding_box[0]*width+col+sizex2]=V_Output_label;
			frame[Bounding_box[1]*width+col+sizex2]=V_Output_label;
		}

	}

	inline void Draw_Silhouette(unsigned char* frame,int width,int height)
	{
		int size = width*height;	// added by MV to avoid some multplies
		int sizex2 = size*2;
		for(int i=0;i<Countour_lenght;i++)
		{
			frame[Countour[i]]=Y_Output_label;
			frame[Countour[i]+size]=U_Output_label;
			frame[Countour[i]+sizex2]=V_Output_label;

		}

	}


	int Re_paint(unsigned char* input);
	int Re_paint_Color(unsigned char* input,int width,int height);

	int copy_to(vipMovingObject *ptr, bool first_frame);

	bool overlap(vipMovingObject *obj);

	//support function for the class
	inline static int array_cmp(unsigned char* in1, int nrlabel, unsigned char value)
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
	* @brief  get global object ID from the label
	*
	* @param[label] input label
	* @param[nr_object]input dimension of upper array
	* @return ID if found else -1
	*/
	inline static int Get_Global_ID(unsigned char label, int num_globals, vipMovingObject *ptr )
	{

		for(int i = 0; i<num_globals;i++)
		{
			if(label==ptr[i].Get_Output_label(0))
				//may would be a special tic controll...

				return ptr[i].Get_Id();
		}

		//printf("vipMovingObject::Get_Global_ID() couldnt find GID by output label.\n");
		return -1;
	}


	/**
	* @brief  get free global object ID
	*
	* @param[ptr] input array_object 
	* @param[nr_object] input dimension of upper array
	* @return ID if found else -1
	*/
	inline int Get_Free_ID(int nr_object)
	{
		for(int i=0; i<nr_object;i++)
			if(vMO_Global[i].Is_Used()==false)
				return vMO_Global[i].Get_Id();

		return -1;
	}

};


#endif	//_VIP_MOVING_OBJECT_H