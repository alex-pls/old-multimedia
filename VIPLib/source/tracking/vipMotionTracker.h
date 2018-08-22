#ifndef _VIP_MOTION_TRACKER_H
#define _VIP_MOTION_TRACKER_H
#pragma once

// To use the STEREO version of the tracker, define VMT_STEREOTRACK in your project properties:
// (VS2005: Configuration Properties -> C/C++ -> Preprocessor -> Preprocessor Definitions


#include <vipFilter.h>
#include <vipFrameHSV.h>
#include "vipMovingObject.h"
#include <tracking/vipTrajectoryUtil.h>

class vipMotionTrackerParameters : public vipFilterParameters
{
	friend class vipMotionTracker;	// used to grant access to private/protected members

public:
	vipMotionTrackerParameters();
	~vipMotionTrackerParameters();

public:
	bool	bInitialized;
	int		Width;
	int		Height;
	int		iMinBlobSize;

public:
	
	VIPRESULT saveToStreamXML(FILE *f);
	VIPRESULT loadFromStreamXML(FILE *f);
	
	inline bool Init( int width, int height, int minBlobSize )
	{
		Width = width;
		Height = height;
		iMinBlobSize = minBlobSize;
		bInitialized = true;

		return true;
	}

	inline bool CheckOk()
	{
		if( !bInitialized || !Width || !Height || !iMinBlobSize )
			return false;
		else
			return true;
	}
};


/*
* Very simple data container for vipMotionTracker.
* It is used by multicamera tracker to enable the handover.
* Info about vehicles approaching the camera view is
*	stored here by other (external) modules and is
*	optionally "offered" to the tracker.
*/
class vipMotionTrackerHandoverCandidate
{
public:
	vipMotionTrackerHandoverCandidate()
	{
		iGID = -1;
		iVerticalDist = 0;
		iHorizontalPos = 0;
		iTime = 0;
	}
	~vipMotionTrackerHandoverCandidate()
	{
	}

public:
	int		iGID;				// global ID (new format for multicam support)
	int		iVerticalDist;		// vertical distance from camera's entry view
	int		iHorizontalPos;		// horizontal position along camera entry axys
	int		iTime;				// TODO: use timestamps of some sort to handle timing
};




extern FILE		*std_error;

class vipMotionTracker : public vipFilter
{
 protected:

	unsigned char	*previous_final_labelled;
	bool			bFirstFrame;


	/**
	 * @brief  Array of moving objects, formerly Global_objects_array.
	 */
	vipMovingObject		*vMO_Global;

public:
	/**
	 * @brief  Current parameters.
	 */
	vipMotionTrackerParameters myParams;

	vipMovingObject* get_vMO_Global_pointer(void){return vMO_Global;}

	//CCL (connected component labeling) support
	void ccl_Tracer(unsigned char* bitmap, int*labelmap, int *cy, int *cx, int *tracingdirection, int width, int height );
	void ccl_ContourTracing(unsigned char* bitmap, int* labelmap,int cy, int cx, int labelindex, int tracingdirection, int width, int height );
	int ccl_ConnectedComponentLabeling(unsigned char* bitmap, unsigned char *labelmap_, int width, int height);
	


	/**
	* @brief  Main Tracking procedure.
	*/

#ifdef VMT_STEREOTRACK
	int Blob_Tracking( vipFrameHSV* input, unsigned char* rect_yuv, unsigned char* depth_yuv, unsigned short *imagedepth16data, unsigned char* blobs, int frame_nr);
#else
	int Blob_Tracking( vipFrameHSV* input, unsigned char* blobs, int frame_nr );
#endif // VMT_STEREOTRACK




	


public:
	vipMotionTracker();
	~vipMotionTracker();
	static int Discriminate(vipMovingObject* Local_array,vipMovingObject* Global_array,unsigned char lbl,int nr_lbl);
	
	int cleanOldGlobals( int current_frame_num );

	inline VIPRESULT reset() { return VIPRET_NOT_IMPLEMENTED; }
	inline VIPRESULT extractTo( vipFrameYUV444& frame ) { return VIPRET_NOT_IMPLEMENTED; }
	inline VIPRESULT setFilterParameters( vipFilterParameters *param ) { return VIPRET_NOT_IMPLEMENTED; }
	inline vipFilterParameters* getFilterParameters() { return &myParams; }
	inline VIPRESULT importFrom( vipFrameT<unsigned char>& frame ) { return VIPRET_NOT_IMPLEMENTED; }
	inline VIPRESULT importFrom( vipFrameRGB24& frame ) { return VIPRET_NOT_IMPLEMENTED; }
	inline VIPRESULT importFrom( vipFrameYUV420& frame ) { return VIPRET_NOT_IMPLEMENTED; }
	inline VIPRESULT importFrom( vipFrameYUV444& frame ) { return VIPRET_NOT_IMPLEMENTED; }	

	inline VIPRESULT setMinBlobSize( unsigned int newSize, int howManyVmoGlobals )
	{ // just propagate minblob size to all vipMovingObjects. atm should not be used during processing, but only at initializing time
		for( int i=0; i<howManyVmoGlobals; i++ )
			vMO_Global[i].iMinBlobSize = newSize;
		
		myParams.iMinBlobSize = newSize;

		return VIPRET_OK;

	}

	VIPRESULT	updateGlobalTrajectories();

	// (optional) Handover support.
	// The following stuff is meant to support and enable handover in multicamera environment.
	// In single camera environment, just ignore all this.
	vipMotionTrackerHandoverCandidate	*handoverCandidatePool;			// when NULL (i.e. empty pool), no handover will be performed.
	unsigned int						*handoverCandidatePoolSize;		// keep track of how many candidates are offered to the tracker at the current time.

};


#endif	// _VIP_MOTION_TRACKER_H