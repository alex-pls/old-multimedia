/**
 *  @class   vipFilterSplitMerge
 *
 *  @brief	Split&Merge filter. Input must be NxN sized BMP24 frame, with N being a power of 2. 
 *
 *
 *
 *
 *  @bug		None known
 *  @warning	Strict input required (see 
 *  @todo		Garbage Collection, if needed (if not already provided in base vipLib classes)
 *
 *  @see     vipFilter
 *
 *  @version 0.1
 *  @date    29/09/2006 12.42.06
 *  @author  Marco Verza - Manuel Di Toma
 *
 *
 *
 ****************************************************************************
 *  Class based on Package Studio template: vipFilterTemplate version 0.9.12
 ****************************************************************************
 * VIPLib Framework
 *  open source, founded by Alessandro Polo 2006
 *  http://mmlab.disi.unitn.it/projects/VIPLib
 *
 *  maintained by MultiMedia Laboratory - DISI - University of Trento
 *
 *
 *	* * * * FILTER USAGE INSTRUCTIONS * * * *
 *
 *	// SETUP FILTER PARAMETERS
 *	yourSplitMergeFilter.getParameters().setRunMode( vipFilterSplitMergeParameters::SPLITMERGE );
 *	yourSplitMergeFilter.getParameters().SetVarianceThreshold( 0.001 );	// Use your favourite threshold value.
 *	yourSplitMergeFilter.getParameters().SetMinFrameSize(1);			// Use 1 for maximum depth splitting.
 *
 *	// DO THE PROCESSING
 *		yourSplitMergeFilter << squareRGB24_InputFrame;
 *	// GET PROCESSED IMAGE
 *		yourSplitMergeFilter >> processedRGB24_OutputFrame;
 *
 ****************************************************************************/

   //#define _CRTDBG_MAP_ALLOC // include Microsoft memory leak detection procedures
   //#define _INC_MALLOC	     // exclude standard memory alloc procedures



#ifndef __VIPLIB_VIPFILTERSPLITMERGE_H__
 #define __VIPLIB_VIPFILTERSPLITMERGE_H__

 #include "../../source/vipFilter.h"
 #include <list>
 #include "../../source/vipFrameYUV444.h"
 #include "../../source/vipUtility.h"
 #include "../../source/codecs/vipCodec_BMP.h"


// ***** QuadTree implementation ***** //
//// vipQuadNode class definition. This class is for internal use only.
class vipRagNode;	// just to let vipQuadNode know that vipRagNode exists.

class vipQuadNode
{

public:
	vipQuadNode();		// Default Constructor
	vipQuadNode( vipQuadNode* father, vipFrameYUV444* framedata = NULL );
	~vipQuadNode();		// Destructor

private:
	vipQuadNode*	ChildNode1;
	vipQuadNode*	ChildNode2;
	vipQuadNode*	ChildNode3;
	vipQuadNode*	ChildNode4;
	vipQuadNode*	FatherNode;
	vipFrameYUV444*	NodeFrameData;
public:
	vipRagNode*		pRagEquivalentNode;


public:				// Access methods
	VIPRESULT		SetChild(vipQuadNode* child, int index);
	VIPRESULT		SetFather(vipQuadNode* father);

	vipQuadNode*	GetChild(int index);
	vipQuadNode*	GetFather();

	VIPRESULT		SetFrameData(vipFrameYUV444* framedata);
	vipFrameYUV444*	GetFrameData();

	bool			HasChildren();

public:		// Saved analysis variables
	double		LumMean;			// -1 means "not calculated yet"
	double		LumVariance;
	double		CbMean;
	double		CrMean;
	
};


// **** Region Adjacency Graph (RAG) Implementation **** //
// This class is for internal use only.
class vipRagNode
{
public:
	vipRagNode();	// Default constructor
	vipRagNode(vipQuadNode* _pQuadNodeRepresented, int _x_min, int _x_max, int _y_min, int _y_max);	// Overloaded constructor
	~vipRagNode();	// Default destructor
public:
	//vipFrameYUV444*	pFrameData;				// Pointer to frame represented by this RAG node. Edit: we prefer using QuadNode for now
	vipQuadNode*	pQuadNodeRepresented;	// Pointer to QuadNode represented by this RAG node.
	int x_min;		// Min/Max coordinates with regard to the whole frame
	int x_max;		// 
	int y_min;		// These are used to make the split procedure "understand" adjacency
	int y_max;
private:
	list<vipRagNode*>			LinkList;	// Link list of the node
public:	// Access methods
	VIPRESULT				AddLink( vipRagNode* toNode, bool linkTwoWays = true );
	VIPRESULT				RemoveLink( vipRagNode* toNodo );
	//VIPRESULT				RemoveLink( int index );
	bool					HasLink( vipRagNode* toNode );
	list<vipRagNode*>*		GetLinkList();
public: //  Organization methods
	bool		IsAdjacentTo( vipRagNode* toNode );
	VIPRESULT	SplitIntoFour();
};

// End of Region Adjacency Graph (RAG) Implementation

/////////////////////////////////////////////////////////////////////


class vipFilterSplitMergeParameters : public vipFilterParameters
 {
	public:

		enum RUNMODE{ DO_NOTHING, SPLITMERGE };
 

	// See comments vipFilterSplitMergeParameters::reset() for detailed info on this parameters
	public:
		/**
		 * @brief  Set Luminance Variance Treshold, used to determine if frames are homogeneous.
		 * @param[in] val Luminance Variance Threshold. 0 <= val <= 1.
		 * @return	VIPRET_OK is val is accepted as valid; VIPRET_PARAM_ERR otherwise.
		 */
		VIPRESULT	SetVarianceThreshold( double val );

		/**
		 * @brief  Set Minimum Frame Size (intended as area), used to limit splitting depth.
		 * @param[in] val Minimum frame size. val >= 1.
		 * @return	VIPRET_OK is val is accepted as valid; VIPRET_PARAM_ERR otherwise.
		 */
		VIPRESULT	SetMinFrameSize( int val );

		/**
		 * @brief  Get Luminance Variance Treshold, which is used to determine if frames are homogeneous.
		 * @return	Current Luminance Variance Treshold value .
		 */
		double		GetVarianceThreshold();

		/**
		 * @brief  Get Minimum Frame Size (intended as area), which is used to limit splitting depth.
		 * @return	Current Minimum frame size value.
		 */
		int			GetMinFrameSize();

	protected:
		double	dVarianceThreshold;
		int		iMinFrameSize;



	protected:


		RUNMODE runMode;


		friend class vipFilterSplitMerge;

	public:

		vipFilterSplitMergeParameters();
		~vipFilterSplitMergeParameters() {};


		void reset();

		void setRunMode(RUNMODE mode) { runMode = mode; };

		RUNMODE getRunMode() { return runMode; };





		/**
		 * @brief  Serialize class to XML format.
		 *         Class' tag is <vipCoder_MOVParameters>
		 *
		 * @param[in] fp output stream's pointer
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
		 */
		VIPRESULT saveToStreamXML(FILE *fp);



		/**
		 * @brief  Deserialize class from XML format.
		 *         Class' tag must be <vipCoder_MOVParameters>
		 *
		 * @param[in] fp input stream's pointer
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
		 */
		VIPRESULT loadFromStreamXML(FILE *fp);


};



class vipFilterSplitMerge :	public vipFilter
 {

 protected:


		/**
		 * @brief  Current parameters.
		 */
		vipFilterSplitMergeParameters* myParams;


 public:


		/**
		 * @brief  Default constructor, initialize parameters and superclasses.
		 * @param[in] initParams parameters for this module or NULL for defaults.
		 */
		vipFilterSplitMerge(vipFilterSplitMergeParameters* initParams = NULL );



		/**
		 * @brief Default destructor, free buffer.
		 */
		~vipFilterSplitMerge();



		/**
		 * @brief  Set parameters for this filter.
		 *
		 * @param[in] initParams Instance of vipFilterSplitMergeParameters or NULL,
		 *                       NULL argument make function to create a new
		 *                       instance with default parameters.
		 *
		 * @return VIPRET_OK
		 */
		VIPRESULT setParameters(vipFilterSplitMergeParameters* initParams);



		/**
		 * @brief  Get parameters for this filter.
		 *
		 * @return pointer to vipFilterSplitMergeParameters instance.
		 */
		vipFilterSplitMergeParameters& getParameters() { return *myParams; };



		/**
		 * @brief  Set parameters for this filter.
		 *
		 * @param[in] initParams Instance of vipFilterSplitMergeParameters or NULL,
		 *                       NULL argument make function to create a new
		 *                       instance with default parameters.
		 *
		 * @return VIPRET_OK
		 */
		VIPRESULT setFilterParameters (vipFilterParameters* initParams)
		 {
			if (initParams == NULL)
				return setParameters(NULL);
			else
				return setParameters(static_cast<vipFilterSplitMergeParameters*>(initParams));
		 };



		/**
		 * @brief  Get parameters for this filter.
		 *
		 * @return pointer to vipFilterSplitMergeParameters instance.
		 */
		vipFilterParameters* getFilterParameters ()
		 {
			if (myParams == NULL)
				return NULL;
			else
				return static_cast<vipFilterParameters*>(myParams);
		 };



		/**
		 * @brief  Reset buffers and parameters.
		 *
		 * @return VIPRET_OK
		 */
		VIPRESULT reset();



		/**
		 * @brief Rotate each frame 90 degrees (right).
		 *
		 * @param[out] dest destination frame.
		 * @param[in] source source frame.
		 *
		 * @return VIPRET_OK if success, VIPRET_ILLEGAL_USE if video is empty.
		 */
		static VIPRESULT rotate90(vipFrameYUV444& dest, vipFrameYUV444& source);



		/**
		 * @brief Process the frame with current settings and store in buffer.
		 *
		 * @param[in] img VIPLib Frame YUV420 to be processed.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if runmode is unknown,
		 *         VIPRET_NOT_IMPLEMENTED if this function is not enabled jet, VIPRET_INTERNAL_ERR else.
		 *
		 * @note  Input operator (<<) call directly this function.
		 * @see   operator << (vipFrameYUV420&)
		 */
		VIPRESULT importFrom(vipFrameYUV420& img);



		/**
		 * @brief Process the frame with current settings and store in buffer.
		 *
		 * @param[in] img VIPLib Frame RGB24 to be processed.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if runmode is unknown,
		 *         VIPRET_NOT_IMPLEMENTED if this function is not enabled jet, VIPRET_INTERNAL_ERR else.
		 *
		 * @note  Input operator (<<) call directly this function.
		 * @see   operator << (vipFrameRGB24&)
		 */
		VIPRESULT importFrom(vipFrameRGB24& img);



		/**
		 * @brief Process the frame with current settings and store in buffer.
		 *
		 * @param[in] img VIPLib Frame Template to be processed.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if runmode is unknown,
		 *         VIPRET_NOT_IMPLEMENTED if this function is not enabled jet, VIPRET_INTERNAL_ERR else.
		 *
		 * @note  Input operator (<<) call directly this function.
		 * @see   operator << (vipFrameT<unsigned char>&)
		 */
		VIPRESULT importFrom(vipFrameT<unsigned char>& img);

		VIPRESULT extractTo(vipFrameYUV444 &)
		{return VIPRET_NOT_IMPLEMENTED;};

		// Link to the QuadNode structure.
		vipQuadNode* DataRootNode;

		// Tools for analyzing frames. For internal use only.
		VIPRESULT GetYUVMeanValues( vipQuadNode* pNode, bool bForceComputation = false );
		double GetLumVarianceFromFrame( vipQuadNode* pNode, bool bForceComputation = false, bool bOnlyMeanNeeded = false );
		double GetLumVarianceFromFrames( vipQuadNode* pNode1, vipQuadNode* pNode2, bool bForceComputation = false );
		bool IsHomogeneous( vipQuadNode* pNode, double option = 0 );
		bool IsHomogeneous( vipQuadNode* pNode1, vipQuadNode* pNode2, double option = 0 );
		VIPRESULT SplitFrameIntoFour( vipFrameYUV444* srcframe, vipFrameYUV444* out1, vipFrameYUV444* out2, vipFrameYUV444* out3, vipFrameYUV444* out4 );
		VIPRESULT RecursiveSplitNodeIntoChild( vipQuadNode* rootnode );
		VIPRESULT RecursivePropagateHomogeneity( vipQuadNode* rootnode );	// This is used to propagate homogeneity across every RAG link.
		VIPRESULT RecursiveMergeTree( vipQuadNode* node );	// This is used on tree's root quadnode, to merge everything into the whole frame.

		int UsedFrameCounter;	// debug. counter

};




#endif //__VIPLIB_VIPFILTERSPLITMERGE_H__


