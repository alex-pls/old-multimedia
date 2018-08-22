/** @file vipFilterSplitMerge.cpp
 *
 * File containing methods for the 'vipFilterSplitMerge' class.
 * The header for this class can be found in vipFilterSplitMerge.h, check that file
 * for class description.
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
 ****************************************************************************/



#include "vipFilterSplitMerge.h"

#include <math.h>



/**
 * @brief  Default constructor, initialize parameters and superclasses.
 * @param[in] initParams parameters for this module or NULL for defaults.
 */
vipFilterSplitMerge::vipFilterSplitMerge(vipFilterSplitMergeParameters* initParams) : vipFilter()
 {
	INFO("vipFilterSplitMerge::vipFilterSplitMerge(..* initParams) : vipFilter() [CONTRUCTOR]")


	myParams = NULL;
	setParameters(initParams);

	setName("Split and Merge Filter");
	setDescription("Splits image, then merges homogeneous fragments.");
	setVersion(1.0);

	// Debug variable
	UsedFrameCounter = 0;

	reset();
 }

/**
 * @brief Default destructor, free buffer.
 */
vipFilterSplitMerge::~vipFilterSplitMerge()
 {
	INFO("vipFilterSplitMerge::~vipFilterSplitMerge() [DESTRUCTOR]")

	if (myParams != NULL)
		delete myParams;
 

 }


/**
 * @brief  Reset buffers and parameters.
 *
 * @return VIPRET_OK
 */
VIPRESULT vipFilterSplitMerge::reset()
 {
	INFO("int vipFilterSplitMerge::reset() [SET DEFAULT PARAMETERS]")


	releaseBuffers();

	if (myParams != NULL)
	 {
		myParams->reset();
		allocateBuffer(myParams->currentBuffer);
	 }
	else
		setParameters(NULL);


	return VIPRET_OK;
 }



/**
 * @brief  Set parameters for this filter.
 *
 * @param[in] initParams Instance of vipFilterSplitMergeParameters or NULL,
 *                       NULL argument make function to create a new
 *                       instance with default parameters.
 *
 * @return VIPRET_OK
 */
VIPRESULT vipFilterSplitMerge::setParameters (vipFilterSplitMergeParameters* initParams)
 {

	if (initParams != NULL && myParams == initParams)
		return VIPRET_PARAM_ERR;

	if ( initParams == NULL )
	 {
		if ( myParams != NULL )
			reset();
		else
			myParams = new vipFilterSplitMergeParameters();
	 }
	else
	 {
		if ( myParams != NULL )
			delete myParams;

		myParams = initParams;
	 }

	allocateBuffer(myParams->currentBuffer);


	return VIPRET_OK;
 }



/**
 * @brief Process the frame with current settings and store in buffer (NOT USED NOR IMPLEMENTED YET).
 *
 * @param[in] img VIPLib Frame YUV420 to be processed.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if runmode is unknown,
 *         VIPRET_NOT_IMPLEMENTED if this function is not enabled jet, VIPRET_INTERNAL_ERR else.
 *
 * @note  Input operator (<<) call directly this function.
 * @see   operator << (vipFrameYUV420&)
 */
VIPRESULT vipFilterSplitMerge::importFrom(vipFrameYUV420& img)
 {
	DEBUGMSG("int vipFilterSplitMerge::importFrom(vipFrameYUV420& img) [reading data]", myParams->runMode)


	switch ( myParams->runMode )
	 {
	 case vipFilterSplitMergeParameters::DO_NOTHING:
			useBufferYUV(img.width, img.height);
			*bufferYUV = img;
			return VIPRET_OK_DEPRECATED;


	 default:
		  return VIPRET_PARAM_ERR;
 	 }


	return VIPRET_NOT_IMPLEMENTED;
 }



/**
 * @brief Process the frame with current settings and store in buffer.
 *
 * @param[in] img VIPLib Frame RGB24 to be processed. MUST be square NxN image, with N = power of 2.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_OK_DEPRECATED if runmode is DO_NOTHING,
 *         else the return value from internal methods.
 *
 * @note  Input operator (<<) call directly this function.
 * @see   operator << (vipFrameRGB24&)
 */
VIPRESULT vipFilterSplitMerge::importFrom(vipFrameRGB24& img)
{
	DEBUGMSG("int vipFilterSplitMerge::importFrom(vipFrameRGB24& img) [reading data]", myParams->runMode)


	switch ( myParams->runMode )
	 {
	 case vipFilterSplitMergeParameters::DO_NOTHING:
			useBufferRGB(img.width, img.height);
			*bufferRGB = img;
			return VIPRET_OK_DEPRECATED;

	 case vipFilterSplitMergeParameters::SPLITMERGE:
		
			// Check if input frame is square
			int srcX = img.getWidth();
			int srcY = img.getHeight();

			if( srcX != srcY )
			{
				//throw(...
				return VIPRET_ILLEGAL_USE;
			}

			// Check if size is a power of 2:
			int pow = 2;
			while( pow <= srcX )
			{
				if( pow == srcX )
				{
					break;	// Ok, it is a power of 2.
				}
				if( pow > srcX )
				{
					//throw(...
					return VIPRET_ILLEGAL_USE;	// No, it is not.
				}
				pow = pow * 2;
			}



			// YUV444 conversion
			vipFrameYUV444* iuv444 = new vipFrameYUV444(srcX,srcY);
			VIPRESULT vipret1 = vipUtility::conv_PixelRGB24toPlanarYUV444( &(img.data[0][0]), iuv444->data, srcX,srcY);

			// Do the processing
			vipQuadNode* root = new vipQuadNode();
			DataRootNode = root;
			vipRagNode* ragRoot = new vipRagNode( root, 0, img.width-1, 0, img.height-1 );
			root->pRagEquivalentNode = ragRoot;
			root->SetFrameData( iuv444 );
			VIPRESULT vipret2 = RecursiveSplitNodeIntoChild( root );

			VIPRESULT vipret3 = RecursivePropagateHomogeneity( root );
			VIPRESULT vipret4 = RecursiveMergeTree( root );

			// Now Convert back to RGB, to SAVE it
			vipFrameRGB24* merged = new vipFrameRGB24(srcX,srcY);
			VIPRESULT vipret5 = vipUtility::conv_PlanarYUV444toPixelRGB24(root->GetFrameData()->data, &merged->data[0][0],srcX,srcY);
			bufferRGB = merged;
			//vipCodec_BMP::save(*merged, "MERGED.bmp", vipCodec_BMP::FORMAT_BMP_24);	// This must done by main thread elsewhere.


			VIPRESULT vipret_final = VIPRET_INTERNAL_ERR;

			if( vipret1 == VIPRET_OK &&
				vipret2 == VIPRET_OK &&
				vipret3 == VIPRET_OK &&
				vipret4 == VIPRET_OK &&
				vipret5 == VIPRET_OK )
				vipret_final = VIPRET_OK;

			return vipret_final;

	 //default:
		//  return VIPRET_PARAM_ERR;
	 }


	return VIPRET_NOT_IMPLEMENTED;
}



/**
 * @brief Process the frame with current settings and store in buffer (NOT IMPLEMENTED, NOT TO BE USED).
 *
 * @param[in] img VIPLib Frame Template to be processed.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if runmode is unknown,
 *         VIPRET_NOT_IMPLEMENTED if this function is not enabled jet, VIPRET_INTERNAL_ERR else.
 *
 * @note  Input operator (<<) call directly this function.
 * @see   operator << (vipFrameT<unsigned char>&)
 */
VIPRESULT vipFilterSplitMerge::importFrom(vipFrameT<unsigned char>& img)
 {
	DEBUGMSG("int vipFilterSplitMerge::importFrom(vipFrameT<unsigned char>& img) [reading data]", myParams->runMode)


	switch ( myParams->runMode )
	 {
	 case vipFilterSplitMergeParameters::DO_NOTHING:
			useBufferTuC(img.width, img.height, img.profile);
			*bufferTuC = img;
			return VIPRET_OK_DEPRECATED;

	 default:
		  return VIPRET_PARAM_ERR;
	 }


	return VIPRET_NOT_IMPLEMENTED;
 }


///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////


VIPRESULT vipFilterSplitMerge::rotate90(vipFrameYUV444& dest, vipFrameYUV444& source)
 {
	if (dest.width != source.height || dest.height != source.width)
		dest.reAllocCanvas(source.height, source.width);

	for ( unsigned int y=0; y < dest.height; y++ ) // single pixel copy routine
	  for ( unsigned int x=0; x < dest.width; x++ )
		dest.data[(dest.height-1-y)*dest.width+x] = source.data[x*source.width + y];

	return VIPRET_OK;
 }


///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////








vipFilterSplitMergeParameters::vipFilterSplitMergeParameters()
 {
	reset();
 }

/**
 * @brief  Set Luminance Variance Treshold, used to determine if frames are homogeneous.
 * @param[in] val Luminance Variance Threshold. 0 <= val <= 1.
 * @return	VIPRET_OK is val is accepted as valid; VIPRET_PARAM_ERR otherwise.
 */
VIPRESULT vipFilterSplitMergeParameters::SetVarianceThreshold(double val)
{
	if( val < 0 )
		return VIPRET_PARAM_ERR;
	if( val > 1 )
		return VIPRET_PARAM_ERR;

	dVarianceThreshold = val;
	return VIPRET_OK;
}

/**
 * @brief  Set Minimum Frame Size (intended as area), used to limit splitting depth.
 * @param[in] val Minimum frame size. val >= 1.
 * @return	VIPRET_OK is val is accepted as valid; VIPRET_PARAM_ERR otherwise.
 */
VIPRESULT vipFilterSplitMergeParameters::SetMinFrameSize(int val)
{
	if( val < 1 )
		return VIPRET_PARAM_ERR;
	
	iMinFrameSize = val;

	return VIPRET_OK;
}

/**
 * @brief  Get Luminance Variance Treshold, which is used to determine if frames are homogeneous.
 * @return	Current Luminance Variance Treshold value .
 */
double vipFilterSplitMergeParameters::GetVarianceThreshold()
{
	return dVarianceThreshold;
}

/**
 * @brief  Get Minimum Frame Size (intended as area), which is used to limit splitting depth.
 * @return	Current Minimum frame size value.
 */
int vipFilterSplitMergeParameters::GetMinFrameSize()
{
	return iMinFrameSize;
}

/**
 * @brief  Reset parameters to default values. Also called by default constructor.
 * @return	void.
 */
void vipFilterSplitMergeParameters::reset()
 {

	runMode = vipFilterSplitMergeParameters::DO_NOTHING;
	dVarianceThreshold = 0.001;	/* Default luminance variance threshold. */
								/*	Can be used to tweak processing time at the cost of "precision".
									MUST be 0 <= dVarianceThreshold <= 1.	*/
	iMinFrameSize = 1;			/* Default splitted frame min size (area). 1 means 1x1. 4 means "dont split anymore frames which are 2x2 or smaller". */
								/*	Can be used to tweak processing time at the cost of "precision".
									MUST be iMinFrameSize >= 1	*/
	currentBuffer = vipFilterParameters::NONE;
 }

int vipFilterSplitMergeParameters::saveToStreamXML(FILE *fp)
 {

	if ( fp == NULL )
		return VIPRET_PARAM_ERR;

	if( fprintf(fp, "<vipFilterSplitMergeParameters>\n") == EOF )
		return VIPRET_INTERNAL_ERR;

	// add your variables here


	if ( fprintf(fp, "  <runmode value=\"%i\" />\n", (int)runMode) == EOF)
		return VIPRET_INTERNAL_ERR;



	if ( fprintf(fp, "  <internalBufferType value=\"%u\" />\n", (int)currentBuffer) == EOF)
		return VIPRET_INTERNAL_ERR;


	if( fprintf(fp, "</vipFilterSplitMergeParameters>\n") == EOF )
		return VIPRET_INTERNAL_ERR;

	return VIPRET_OK;
 }


int vipFilterSplitMergeParameters::loadFromStreamXML(FILE *fp)
 {
	if ( fscanf(fp, "<vipFilterSplitMergeParameters>\n") == EOF )
		throw "error in XML file, unable to import data.";

	// add your variables here



	int runTmp = 0;
	if ( fscanf(fp, "  <runmode value=\"%i\" />\n", &runTmp) == EOF )
		throw "error in XML file, unable to import data.";
	else
		runMode = (RUNMODE)runTmp;



	int cB = (int)currentBuffer;
	if ( fscanf(fp, "  <internalBufferType value=\"%u\" />\n", &cB) == EOF )
		throw "error in XML file, unable to import data.";
	currentBuffer = (BUFFER_TYPE)cB;



	return VIPRET_OK;
 }


/**
 * @brief  Calculates Y,U,V mean values throughout the frame. May reuse values already saved, if bForceComputation isnt passed as true. For internal use.
 * @return	VIPRET_OK if everything went alright; throws exceptions if invalid input is used.
 */
VIPRESULT vipFilterSplitMerge::GetYUVMeanValues(vipQuadNode *pNode, bool bForceComputation )
{
	// Has the work already been done?
	if( ( pNode->LumMean != -1) && ( pNode->CbMean != -1 ) && ( pNode->CrMean != -1 ) && (!bForceComputation) )
	{
		// Node already processed, no need to do it again.
		return VIPRET_OK;
	}

	// Do the work.
	vipFrameYUV444* frame = pNode->GetFrameData();
	if( frame == NULL )
	{
		throw("GetLumVarianceFromFrame applied on invalid Quad Node.");
	}

	double mean = 0;
	int totpix = frame->getWidth() * frame->getHeight();

	if( totpix == 0 )
	{
		throw("GetLumVarianceFromFrame applied on Quad Node with empty frame.");
	}
	int i = 0;

	// Lum channel:
	if( pNode->LumMean == -1 || bForceComputation )
	{
		while(i < totpix)
		{
			mean = mean + frame->data[i];
			i++;
		}
		mean = mean/totpix;		// 1/N
		pNode->LumMean = mean;	// Save
		i = 0;					// Reset variables
		mean = 0;
	}

	// Cb channel:
	if( pNode->CbMean == -1 || bForceComputation )
	{
		while(i < totpix)
		{
			mean = mean + frame->data[i+totpix];
			i++;
		}
		mean = mean/totpix;		// 1/N
		pNode->CbMean = mean;	// Save
		i = 0;					// Reset variables
		mean = 0;
	}

	// Cr channel:
	if( pNode->CrMean == -1 || bForceComputation )
	{
		while(i < totpix)
		{
			mean = mean + frame->data[i+(totpix*2)];
			i++;
		}
		mean = mean/totpix;		// 1/N
		pNode->CrMean = mean;	// Save
	}

	return VIPRET_OK;
}

// NORMALIZED Luminance variance computation function
/**
 * @brief  Calculates Y normalized variance throughout the frame. May reuse values already saved, if bForceComputation isnt passed as true. For internal use.
 * @return	Variance value if everything went alright; throws exceptions if invalid input is used.
 */
double vipFilterSplitMerge::GetLumVarianceFromFrame( vipQuadNode* pNode, bool bForceComputation, bool bOnlyMeanNeeded )
{

	// If this method has already been run on this node, skip everything...
	if( (pNode->LumVariance != -1) && (pNode->LumMean != -1) && (!bForceComputation) )	// (unless we want to compute again)
	{	// ... and return the already calculated value.
		return pNode->LumVariance;
	}


	vipFrameYUV444* frame = pNode->GetFrameData();
	if( frame == NULL )
	{
		throw("GetLumVarianceFromFrame applied on invalid Quad Node.");
	}
	// Calculate normalised variance of luminance throughout the whole frame
	double lummean = 0;
	double lumvar = 0;
	int totpix = frame->getWidth() * frame->getHeight();

	if( totpix == 0 )
	{
		throw("GetLumVarianceFromFrame applied on Quad Node with empty frame.");
	}

	// If mean is already saved, skip its calculation:
	if( (pNode->LumMean != -1) && (!bForceComputation) )	
	{
		lummean = pNode->LumMean;	// skip mean calc.
	}
	else							// Otherwise, calculate it.
	{
		// Calculate Lum. Mean value:
		int i = 0;
		//double luminosita = 0;
		//PixelRGB24 nextpixel;
		while(i < totpix)		// Computing lum. mean value
		{
			//nextpixel = frame->data[i];
			//luminosita = (0.299*nextpixel[0] + 0.587*nextpixel[1] + 0.114*nextpixel[2] );	// Y component (from RGB to YIQ)
			//luminosita = frame->data[i];
			lummean = lummean + frame->data[i];
			i++;
		}
		lummean = lummean/totpix;
	}

	// If the call was made by GetLumVarianceFromFrames(), only mean is needed, so save & return now
	if( bOnlyMeanNeeded )
	{
		pNode->LumMean = lummean;
		return -1;
	}

	// Now calculate lum. variance
	int i = 0;
	while(i < totpix)
	{
		//nextpixel = frame->data[i];
		//luminosita = (0.299*nextpixel[0] + 0.587*nextpixel[1] + 0.114*nextpixel[2] );	// Y component (from RGB to YIQ)
		//luminosita = frame->data[i];
		lumvar = lumvar + pow((lummean - frame->data[i]),2); 
		i++;
	}
	lumvar = lumvar/totpix;		// 1/N * sum...
	lumvar = lumvar/16256.25;	// Normalization, by 127.5^2 factor

	// Save variables inside QuadNode structure.
	pNode->LumMean = lummean;
	pNode->LumVariance = lumvar;

	return lumvar;
}

/**
 * @brief  Calculates Y normalized variance throughout the 2 frames considered as a whole. May reuse values already saved, if bForceComputation isnt passed as true. For internal use.
 * @return	Variance value if everything went alright; throws exceptions if invalid input is used.
 */
double vipFilterSplitMerge::GetLumVarianceFromFrames( vipQuadNode* pNode1, vipQuadNode* pNode2, bool bForceComputation )
{ // This method is used to calculate lum.variance from two frames, considering them as a whole.

	// Make sure mean values are saved inside nodes.
	GetLumVarianceFromFrame( pNode1, bForceComputation, true );	// Only mean value is needed 
	GetLumVarianceFromFrame( pNode2, bForceComputation, true );	// Only mean value is needed 

	// Get size of both.
	int iSize1 = pNode1->GetFrameData()->getWidth() * pNode1->GetFrameData()->getHeight();
	int iSize2 = pNode2->GetFrameData()->getWidth() * pNode2->GetFrameData()->getHeight();

	// Get mean lum. value for them considered as a whole.
	double WholeLumMean = ( (pNode1->LumMean * iSize1) + (pNode2->LumMean * iSize2) ) / (iSize1+iSize2);

	// Calculate variance
	int i = 0;
	double WholeLumVar = 0;
	while( i < iSize1 )		// Cycle through first frame...
	{
		WholeLumVar = WholeLumVar + pow((WholeLumMean - pNode1->GetFrameData()->data[i] ), 2);
		i++;
	}
	i = 0;					// ...restart counter...
	while( i < iSize2 )		// ...cycle through second frame...
	{
		WholeLumVar = WholeLumVar + pow((WholeLumMean - pNode2->GetFrameData()->data[i] ), 2);
		i++;
	}
	// Last operations:
	WholeLumVar = WholeLumVar/(iSize1+iSize2);	// 1/N
	WholeLumVar = WholeLumVar/16256.25;			// Normalization, by 127.5^2 factor

	return WholeLumVar;
}


// Homogeneity evaluation method.
/**
 * @brief  Checks if input node contains an homogeneous frame.
 * @return	Self explaining bool.
 */
bool vipFilterSplitMerge::IsHomogeneous( vipQuadNode* pNode, double option )
{ // This method checks if the frame linked to pNode is homogeneous.

	vipFrameYUV444* frame = pNode->GetFrameData();

	// Don't split frames into subframes smaller than iMinFrameSize (area)
	// See comments @ vipFilterSplitMergeParameters::reset()
	if( frame->height*frame->width <= getParameters().GetMinFrameSize() )
		return true;

	//      Option value control
	// Option must be a value between 0 and 1
	if ((option<0)||(option>1))
	{
		throw("Parameter not valid");
	}

	// Current Frame variance computation
	double variance = GetLumVarianceFromFrame(pNode);

	// Thresholding using variance and the given option

	double thrValue = 0 + option; // option indicates the tolerance
	if (variance < thrValue)
		//      Is homogeneus
		return true;
	else
		//      not homogeneus
		return false;
}

/**
 * @brief  Checks if two input nodes contain frames which, if considered together as a whole, are homogeneous.
 * @return	Self explaining bool.
 */
bool vipFilterSplitMerge::IsHomogeneous( vipQuadNode* pNode1, vipQuadNode* pNode2, double option )
{
	// Check if the frames are homogeneous between themselves

	vipFrameYUV444* frame1 = pNode1->GetFrameData();
	vipFrameYUV444* frame2 = pNode2->GetFrameData();

	//      Option value control
	// Option must be a value between 0 and 1
	if ((option<0)||(option>1))
	{
		throw("vipFilterSplitMerge::IsHomogeneous(): Parameter not valid");
	}

	// Current Frame variance computation
	double variance = GetLumVarianceFromFrames( pNode1, pNode2 );

	// Thresholding using variance and the given option

	double thrValue = 0 + option; // option indicates the tolerance
	if (variance < thrValue)
		//      Is homogeneus
		return true;
	else
		//      not homogeneus
		return false;
	
}

// SBRO
// Splitting function
/**
 * @brief  Splits input NxN-sized frame into 4 subframes on the output.
 * @return	VIPRET_OK if everything went alright; VIPRET_ILLEGAL_USE if output pointers refer to invalid/misconfigured frames; VIPRET_NOT_IMPLEMENTED if trying to split non NxN-sized frames (with N=2^L).
 */
VIPRESULT vipFilterSplitMerge::SplitFrameIntoFour( vipFrameYUV444* srcframe, vipFrameYUV444* out1, vipFrameYUV444* out2, vipFrameYUV444* out3, vipFrameYUV444* out4 )
{
	// Check if image has a size which can be splitted in 4 equal parts
	double height = srcframe->getHeight();
	double width = srcframe->getWidth();

	// Check if output frame pointers are valid
	if( out1 == NULL || out2 == NULL || out3 == NULL || out4 == NULL )
	{
		// Output frame pointers must point to valid frames
		return VIPRET_ILLEGAL_USE;
	}
	// Check heigth/width...
	if( // ...of each output frame:
		out1->getHeight() != height/2 || out1->getWidth() != width/2 ||
		out2->getHeight() != height/2 || out2->getWidth() != width/2 ||
		out3->getHeight() != height/2 || out3->getWidth() != width/2 ||
		out4->getHeight() != height/2 || out4->getWidth() != width/2
		)
	{
		// Output frames must be correctly configured before calling this method.
		return VIPRET_ILLEGAL_USE;
	}

	if( height != width )
	{
		return VIPRET_NOT_IMPLEMENTED;
	}

	if( (height/2) - (int)(height/2) != 0 )
	{
		// Can't split into 4 equally sized parts
		return VIPRET_NOT_IMPLEMENTED;
	}
	if( (width/2) - (int)(width/2) != 0 )
	{
		// Can't split into 4 equally sized parts
		return VIPRET_NOT_IMPLEMENTED;
	}


	// Split
	int i = 0;
	int i_out = 0;
	int i_w = 0;
	int i_h = 0;
	int w_offset = 0; // For width starting point 
	int h_offset = 0; // For height starting point
	vipFrameYUV444* curr_Frame = NULL;
	unsigned char tempPixVal[3];

	for(int j=0; j<4; j++) // Cycle 4 times (one for each quarter)
	{
		switch(j)	// Decides which quarter 
		{			// setting offsets
		case 0:
			i_out = 0;
			i_w = 0;
			i_h = 0;
			i = 0;
			curr_Frame = out1;
			break;
		case 1:
			i_out = 0;
			i_w = 0;
			i_h = 0;
			i = 0;
			w_offset = width/2;	
			curr_Frame = out2;
			break;
		case 2:
			i_out = 0;
			i_w = 0;
			i_h = 0;
			i = 0;
			w_offset = 0;
			h_offset = height/2;
			curr_Frame = out3;
			break;
		case 3:
			i_out = 0;
			i_w = 0;
			i_h = 0;
			i = 0;
			w_offset = width/2;
			h_offset = height/2;
			curr_Frame = out4;
			break;
		}
		while( i < height * width / 4 )	// Copy first quarter of image
		{

			if ( srcframe->getPixel(i_w+w_offset, i_h+h_offset, tempPixVal[0], vipFrameYUV444::Lum ) != VIPRET_OK ||
				srcframe->getPixel(i_w+w_offset, i_h+h_offset, tempPixVal[1], vipFrameYUV444::Cb ) != VIPRET_OK ||
				srcframe->getPixel(i_w+w_offset, i_h+h_offset, tempPixVal[2], vipFrameYUV444::Cr ) != VIPRET_OK
				)
			{
				// We got an invalid pixel or something from input frame
				// Maybe some error management could fit
				// throw(...
			}

			curr_Frame->data[i_out] = tempPixVal[0];
			curr_Frame->data[i_out + (int)((height/2)*(width/2))] = tempPixVal[1];
			curr_Frame->data[i_out + (int)((height/2)*(width/2)*2)] = tempPixVal[2];

			i_out++;

			// We have copied the pixel number 'i'. Now check rows/columns
			if( i_w == width/2 - 1 )	// If we are at the end of the row...
			{
				i_w = 0;				// restart new row
				i_h++;
			}
			else
			{
				i_w++;					// else, next pixel on same row
			}
			i++;
		}
	}

	return VIPRET_OK;
}


/**
 * @brief  This method is used to recursively split the QuadTree structure until homogeneity is achieved.
 * @param[in]	rootNode Root node of the QuadTree structure.
 * @return	VIPRET_OK at end of recursion and if everything went alright; throws an exception if SplitFrameIntoFour fails.
 */
VIPRESULT vipFilterSplitMerge::RecursiveSplitNodeIntoChild( vipQuadNode *rootnode )
{
	// Has the frame been splitted enough?
	if( IsHomogeneous(rootnode,getParameters().GetVarianceThreshold()) )
	{ // The frame is homogeneous, and doesn't need to be splitted again.
		return VIPRET_OK;
	}

	// First split this node's frame into 4
	vipFrameYUV444* out1 = new vipFrameYUV444( rootnode->GetFrameData()->width/2, rootnode->GetFrameData()->height/2 );
	vipFrameYUV444* out2 = new vipFrameYUV444( rootnode->GetFrameData()->width/2, rootnode->GetFrameData()->height/2 );
	vipFrameYUV444* out3 = new vipFrameYUV444( rootnode->GetFrameData()->width/2, rootnode->GetFrameData()->height/2 );
	vipFrameYUV444* out4 = new vipFrameYUV444( rootnode->GetFrameData()->width/2, rootnode->GetFrameData()->height/2 );

	// This is a temp. counter. Can be removed, or restricted to "debug" mode, if necessary.
	UsedFrameCounter = UsedFrameCounter + 4;

	if( SplitFrameIntoFour(rootnode->GetFrameData(),out1,out2,out3,out4) != VIPRET_OK )
	{
		// Some sort of error during Splitting of the frame
		throw("RecursiveSplitNodeIntoChild(): Unknown error while splitting.");
		return VIPRET_NOT_IMPLEMENTED;
	}

	// Link the small frames to this node's children
	vipQuadNode* child1 = new vipQuadNode( rootnode, out1 );
	vipQuadNode* child2 = new vipQuadNode( rootnode, out2 );
	vipQuadNode* child3 = new vipQuadNode( rootnode, out3 );
	vipQuadNode* child4 = new vipQuadNode( rootnode, out4 );	// Four child nodes created.

	rootnode->SetChild(child1, 1);				// Link to children nodes.
	rootnode->SetChild(child2, 2);
	rootnode->SetChild(child3, 3);
	rootnode->SetChild(child4, 4);

	// Update RAG Structure:
	rootnode->pRagEquivalentNode->SplitIntoFour();	// this should do all the job on RAG's side...


	// Recursive call of this method on children nodes:
	RecursiveSplitNodeIntoChild( rootnode->GetChild(1) );
	RecursiveSplitNodeIntoChild( rootnode->GetChild(2) );
	RecursiveSplitNodeIntoChild( rootnode->GetChild(3) );
	RecursiveSplitNodeIntoChild( rootnode->GetChild(4) );

	return VIPRET_OK;
}

/**
 * @brief  This method is used to recursively merge the fully splitted QuadTree.
 * @param[in]	rootNode Root node of the QuadTree structure.
 * @return	VIPRET_OK at end of recursion.
 */
VIPRESULT vipFilterSplitMerge::RecursivePropagateHomogeneity( vipQuadNode* rootnode )
{ // ** This method must be applied on the rootnode of a completely splitted (=grown to full size) quadtree

	// If this node is a leaf, check its links and possibly propagate homogeneity
	if( !(rootnode->HasChildren()) )
	{
		// Cycle through this node's adjacencies
		list<vipRagNode*>::iterator Iter = rootnode->pRagEquivalentNode->GetLinkList()->begin();
		while( Iter != rootnode->pRagEquivalentNode->GetLinkList()->end() )
		{
			// Check homogeneity of current adjacent node:
			if( IsHomogeneous( rootnode, (*Iter)->pQuadNodeRepresented ), getParameters().GetVarianceThreshold() )
			{
				// They are homogeneous: propagate colour
				GetYUVMeanValues( rootnode );			// calculate mean values for each channel
				GetYUVMeanValues( (*Iter)->pQuadNodeRepresented );
				unsigned char newVal = 0;
				int iSize1 = rootnode->GetFrameData()->getWidth() * rootnode->GetFrameData()->getHeight();
				int iSize2 = (*Iter)->pQuadNodeRepresented->GetFrameData()->getWidth() * (*Iter)->pQuadNodeRepresented->GetFrameData()->getHeight();
				
				newVal = ( ( rootnode->LumMean * iSize1 ) + ((*Iter)->pQuadNodeRepresented->LumMean * iSize2) ) / ( iSize1 + iSize2 );	// Lum
				rootnode->GetFrameData()->clearWith(&newVal, vipFrameYUV444::Lum);
				newVal = ( ( rootnode->CbMean * iSize1 ) + ((*Iter)->pQuadNodeRepresented->CbMean * iSize2) ) / ( iSize1 + iSize2 );	// Cb
				rootnode->GetFrameData()->clearWith(&newVal, vipFrameYUV444::Cb);
				newVal = ( ( rootnode->CrMean * iSize1 ) + ((*Iter)->pQuadNodeRepresented->CrMean * iSize2) ) / ( iSize1 + iSize2 );	// Cr
				rootnode->GetFrameData()->clearWith(&newVal, vipFrameYUV444::Cr);
				

				// THIS SECTION IS USEFUL IF FURTHER PROCESSING IS ADDED TO MY FILTER AFTER FIRST MERGE
				// Invalidate/(update?) saved variables for the nodes/frames that we have changed.
				//rootnode->LumMean = -1 or mean color's Y
				//rootnode->LumVariance = -1 or 0?
				//(*Iter)->pQuadNodeRepresented->LumMean = -1 or mean color's Y
				//(*Iter)->pQuadNodeRepresented->LumVariance = -1 or 0?
			}

			// Increment
			Iter++;
		}
		
		return VIPRET_OK;
	}

	// Else, recursively call this function on children:
	int child_n = 1;
	while( child_n <= 4 )
	{
		RecursivePropagateHomogeneity( rootnode->GetChild(child_n) );
		child_n++;
	}

	return VIPRET_OK;				// Else, this node is a leaf: done propagating into this node and its children.
}

/**
 * @brief  This method is used to recursively propagate homogeneity (i.e., apply mean color) throughout the fully splitted QuadTree.
 * @param[in]	rootNode Root node of the QuadTree structure.
 * @return	VIPRET_OK at end of recursion.
 */
VIPRESULT vipFilterSplitMerge::RecursiveMergeTree( vipQuadNode* node )
{
	// If this node is a leaf, just return
	if( !(node->HasChildren()) )
	{
		return VIPRET_OK;
	}

	// If this node's children are further splitted, recursively call this function to merge them first
	int child_n = 1;
	while( child_n <= 4 )
	{	// Each non-leaf child is merged bofore continuing.
		if( node->GetChild(child_n)->HasChildren() )
		{
			RecursiveMergeTree( node->GetChild(child_n) );
		}
		child_n++;
	}

	// Else if this node has children which are leaves...
	// ...merge this node's children.
	int i = 0;
	int w_offset = node->GetFrameData()->width / 2;
	int h_offset = node->GetFrameData()->height / 2;
	int curr_row = 0;
	unsigned char tempPixelVal[3];

	// Merge Child1, upper-left
	while(curr_row < h_offset)	// Copy all rows of this child frame
	{	// Start copying current row
		while(i < w_offset)	// Copy current row
		{//Can be OPTIMIZED if needed
			node->GetChild(1)->GetFrameData()->getPixel(i, curr_row, tempPixelVal[0], vipFrameYUV444::Lum );
			node->GetChild(1)->GetFrameData()->getPixel(i, curr_row, tempPixelVal[1], vipFrameYUV444::Cb );
			node->GetChild(1)->GetFrameData()->getPixel(i, curr_row, tempPixelVal[2], vipFrameYUV444::Cr );
			node->GetFrameData()->setPixel(i, curr_row, tempPixelVal[0], vipFrameYUV444::Lum );
			node->GetFrameData()->setPixel(i, curr_row, tempPixelVal[1], vipFrameYUV444::Cb );
			node->GetFrameData()->setPixel(i, curr_row, tempPixelVal[2], vipFrameYUV444::Cr );
			i++;
		}
		i = 0;		// Reset cursor to begin a new row;
		curr_row++;	// Increment current row cursor.
	}

	// Merge Child2, upper-right
	i = 0;	// Reset cursor
	curr_row = 0;
	while(curr_row < h_offset)	// Copy all rows of this child frame
	{	// Start copying current row
		while(i+w_offset < 2*w_offset)	// Copy current row
		{
			node->GetChild(2)->GetFrameData()->getPixel(i, curr_row, tempPixelVal[0], vipFrameYUV444::Lum );
			node->GetChild(2)->GetFrameData()->getPixel(i, curr_row, tempPixelVal[1], vipFrameYUV444::Cb );
			node->GetChild(2)->GetFrameData()->getPixel(i, curr_row, tempPixelVal[2], vipFrameYUV444::Cr );
			node->GetFrameData()->setPixel(i+w_offset, curr_row, tempPixelVal[0], vipFrameYUV444::Lum );
			node->GetFrameData()->setPixel(i+w_offset, curr_row, tempPixelVal[1], vipFrameYUV444::Cb );
			node->GetFrameData()->setPixel(i+w_offset, curr_row, tempPixelVal[2], vipFrameYUV444::Cr );
			i++;
		}
		i = 0;		// Reset cursor to begin a new row;
		curr_row++;	// Increment current row cursor.
	}

	// Merge Child3, bottom-left
	i = 0;	// Reset cursor
	curr_row = 0;
	while(curr_row+h_offset < 2*h_offset)	// Copy all rows of this child frame
	{	// Start copying current row
		while(i < w_offset)	// Copy current row
		{
			node->GetChild(3)->GetFrameData()->getPixel(i, curr_row, tempPixelVal[0], vipFrameYUV444::Lum );
			node->GetChild(3)->GetFrameData()->getPixel(i, curr_row, tempPixelVal[1], vipFrameYUV444::Cb );
			node->GetChild(3)->GetFrameData()->getPixel(i, curr_row, tempPixelVal[2], vipFrameYUV444::Cr );
			node->GetFrameData()->setPixel(i, curr_row+h_offset, tempPixelVal[0], vipFrameYUV444::Lum );
			node->GetFrameData()->setPixel(i, curr_row+h_offset, tempPixelVal[1], vipFrameYUV444::Cb );
			node->GetFrameData()->setPixel(i, curr_row+h_offset, tempPixelVal[2], vipFrameYUV444::Cr );
			i++;
		}
		i = 0;		// Reset cursor to begin a new row;
		curr_row++;	// Increment current row cursor.
	}


	// Merge Child4, bottom-right
	i = 0;	// Reset cursor
	curr_row = 0;
	while(curr_row+h_offset < 2*h_offset)	// Copy all rows of this child frame
	{	// Start copying current row
		while(i+w_offset < 2*w_offset)	// Copy current row
		{
			node->GetChild(4)->GetFrameData()->getPixel(i, curr_row, tempPixelVal[0], vipFrameYUV444::Lum );
			node->GetChild(4)->GetFrameData()->getPixel(i, curr_row, tempPixelVal[1], vipFrameYUV444::Cb );
			node->GetChild(4)->GetFrameData()->getPixel(i, curr_row, tempPixelVal[2], vipFrameYUV444::Cr );
			node->GetFrameData()->setPixel(i+w_offset, curr_row+h_offset, tempPixelVal[0], vipFrameYUV444::Lum );
			node->GetFrameData()->setPixel(i+w_offset, curr_row+h_offset, tempPixelVal[1], vipFrameYUV444::Cb );
			node->GetFrameData()->setPixel(i+w_offset, curr_row+h_offset, tempPixelVal[2], vipFrameYUV444::Cr );
			i++;
		}
		i = 0;		// Reset cursor to begin a new row;
		curr_row++;	// Increment current row cursor.
	}


	// Clear children (which were leaves), so this node becomes a leaf itself.
	// TODO?: Delete objects, garbage collection etc.
	node->SetChild(NULL, 1);
	node->SetChild(NULL, 2);
	node->SetChild(NULL, 3);
	node->SetChild(NULL, 4);

	// Subframes were probably processed by RecursivePropagateHomogeneity, so invalidate past saved variables:
	node->LumMean = -1;		// TODO: actually, we could set it to actual value.
	node->LumVariance = -1;	// This will need to be calculated again anyways.


	return VIPRET_OK;				// Else, this node is a leaf: done merging node and its children.
}

// End of vipFilterSplitMerge class implementation

//////////////////////////////////////////////////////////
// SBRO
// QuadTree implementation
// vipQuadNode class

vipQuadNode::vipQuadNode()		// Default Constructor
{
	ChildNode1 = NULL;
	ChildNode2 = NULL;
	ChildNode3 = NULL;
	ChildNode4 = NULL;
	FatherNode = NULL;
	NodeFrameData = NULL;
	pRagEquivalentNode = NULL;
	LumMean = -1;
	LumVariance = -1;
	CbMean = -1;
	CrMean = -1;
}
vipQuadNode::vipQuadNode( vipQuadNode* father, vipFrameYUV444* framedata )		// Constructor
{
	ChildNode1 = NULL;
	ChildNode2 = NULL;
	ChildNode3 = NULL;
	ChildNode4 = NULL;
	FatherNode = father;
	NodeFrameData = framedata;
	pRagEquivalentNode = NULL;
	LumMean = -1;
	LumVariance = -1;
	CbMean = -1;
	CrMean = -1;
}

vipQuadNode::~vipQuadNode()		// Destructor
{
	// I don't know how exactly how garbage collection is handled in the library.
	// In case, some GC could be done here.
}

VIPRESULT vipQuadNode::SetChild(vipQuadNode* child, int index)
{
	if( index < 0 || index > 4 )
		return VIPRET_ILLEGAL_USE;

	switch( index )
	{
		case 1:
			ChildNode1 = child;
			break;
		case 2:
			ChildNode2 = child;
			break;
		case 3:
			ChildNode3 = child;
			break;
		case 4:
			ChildNode4 = child;
			break;
		default:
			throw("Somewhat terrible");
	}
	return VIPRET_OK;
}

VIPRESULT vipQuadNode::SetFather(vipQuadNode* father)
{
	FatherNode = father;
	return VIPRET_OK;
}

vipQuadNode* vipQuadNode::GetChild(int index)
{
	if( index < 0 || index > 4 )
	{
		throw("Illegal Use");
		return NULL;
	}

	switch( index )
	{
		case 1:
			return ChildNode1;
		case 2:
			return ChildNode2;
		case 3:
			return ChildNode3;
		case 4:
			return ChildNode4;
		default:
			throw("Somewhat terrible");
	}
}
vipQuadNode* vipQuadNode::GetFather()
{
	return FatherNode;
}


VIPRESULT vipQuadNode::SetFrameData(vipFrameYUV444* framedata)
{
	NodeFrameData = framedata;
	return VIPRET_OK;
}
vipFrameYUV444* vipQuadNode::GetFrameData()
{
	return NodeFrameData;
}
bool vipQuadNode::HasChildren()
{
	if( ChildNode1 == NULL && ChildNode2 == NULL && ChildNode3 == NULL && ChildNode4 == NULL )
	{	// No children
		return false;
	}
	else if( ChildNode1 != NULL && ChildNode2 != NULL && ChildNode3 != NULL && ChildNode4 != NULL )
	{	// There are 4 children
		return true;
	}
	else
	{	// Some null, some not: this shouldn't be.
		throw "vipQuadNode::HasChildren(): Some children are NULL, other are'nt.";
	}

}
// End of QuadTree implementation

// Region Adjacency Graph (RAG) Implementation

vipRagNode::vipRagNode()		// Default constructor
{
	pQuadNodeRepresented = NULL;
	//LinkList.clear();
	x_min = -1;
	x_max = -1;
	y_min = -1;
	y_max = -1;
}

vipRagNode::vipRagNode(vipQuadNode* _pQuadNodeRepresented, int _x_min, int _x_max, int _y_min, int _y_max)
{
	pQuadNodeRepresented = _pQuadNodeRepresented;
	//LinkList.clear();
	x_min = _x_min;
	x_max = _x_max;
	y_min = _y_min;
	y_max = _y_max;
}

vipRagNode::~vipRagNode()
{
}

VIPRESULT vipRagNode::AddLink( vipRagNode* toNode, bool linkTwoWays )
{	// Avoid the problem of having multiple links on one node to same node
	LinkList.push_back( toNode );
	if( linkTwoWays )
	{
		toNode->AddLink(this, false);
	}
	return VIPRET_OK;
}

VIPRESULT vipRagNode::RemoveLink( vipRagNode* toNode )
{
	list<vipRagNode*>::iterator Iter;
	Iter = LinkList.begin();
	while( Iter != LinkList.end() )
	{
		if( *Iter == toNode )
		{
			LinkList.erase( Iter );
			return VIPRET_OK;
		}
		Iter++;
	}
	// The element we were trying to remove was not present:
	return VIPRET_PARAM_ERR;
}

//
//VIPRESULT vipRagNode::RemoveLink(int index)
//{
//	vector<vipRagNode*>::iterator Iter;
//	Iter = LinkList.begin();
//	LinkList.erase(Iter+index);
//	return VIPRET_OK;
//}

list<vipRagNode*>* vipRagNode::GetLinkList()
{
	return &LinkList;
}

bool vipRagNode::HasLink( vipRagNode* toNode )
{
	list<vipRagNode*>::iterator Iter;

	Iter = LinkList.begin();
	while( Iter != LinkList.end() )
	{
		if( *Iter == toNode )
		{
			return true;
		}
		Iter++;
	}
	// The element is not present:
	return false;
}

bool vipRagNode::IsAdjacentTo( vipRagNode* toNode )
{ // by MANU
	//if( /* Estensioni X con intersez !=0*/ && /*Estensioni Y con distanza nulla*/ )
	//	return true;
	//if( /* Estensioni Y con intersez !=0*/ && /*Estensioni X con distanza nulla*/ )
	//	return true;
	//else
	//	return false;

	// Manu
	// Boolean var, flag for x axis intesection 
	bool Xintersection = ((this->x_min >= toNode->x_min )&&( this->x_min <= toNode->x_max))||((toNode->x_min >= this->x_min )&&( toNode->x_min <= this->x_max ));
	// Boolean var, flag for y axis intesection
	bool Yintersection = ((this->y_min >= toNode->y_min )&&( this->y_min <= toNode->y_max))||((toNode->y_min >= this->y_min )&&( toNode->y_min <= this->y_max ));
	// Boolean var, flag for Space between cells in X
	bool XzeroSpace = ((toNode->x_min - this->x_max) == 1)||((this->x_min - toNode->x_max)==1);
	// Boolean var, flag for Space between cells in Y
	bool YzeroSpace = ((toNode->y_min - this->y_max) == 1)||((this->y_min - toNode->y_max)==1);
	// Two frames are adjacent if there's an intersection in x coordinates 
	// AND not intersection for y coordinates AND NO YSPACE between them, or VICEVERSA.
	// So there's an edge in common.
	if(( Xintersection && !Yintersection && YzeroSpace)||(Yintersection && !Xintersection & XzeroSpace))
		return true;
	else
		return false;

}

VIPRESULT vipRagNode::SplitIntoFour()
{
	// Generate 4 new RAG nodes
	vipRagNode* r1 = new vipRagNode(		/* New RAG NODE: HIGH-LEFT subframe */
		pQuadNodeRepresented->GetChild(1),	// Link to the represented QuadNode
		x_min,								// x_min of this new ragnode
		x_min + (x_max-x_min-1)/2,			// x_max of this new ragnode
		y_min,								// y_min of this new ragnode
		y_min + (y_max-y_min-1)/2			);	// y_max of this new ragnode

	vipRagNode* r2 = new vipRagNode(		/* New RAG NODE: HIGH-RIGHT subframe */
		pQuadNodeRepresented->GetChild(2),	// Link to the represented QuadNode
		x_min + (x_max-x_min+1)/2,			// x_min of this new ragnode
		x_max,								// x_max of this new ragnode
		y_min,								// y_min of this new ragnode
		y_min + (y_max-y_min-1)/2		);	// y_max of this new ragnode

	vipRagNode* r3 = new vipRagNode(		/* New RAG NODE: LOW-LEFT subframe */
		pQuadNodeRepresented->GetChild(3),	// Link to the represented QuadNode
		x_min,								// x_min of this new ragnode
		x_min + (x_max-x_min-1)/2,			// x_max of this new ragnode
		y_min + (y_max-y_min+1)/2,			// y_min of this new ragnode
		y_max							);	// y_max of this new ragnode


	vipRagNode* r4 = new vipRagNode(		/* New RAG NODE: LOW-LEFT subframe */
		pQuadNodeRepresented->GetChild(4),	// Link to the represented QuadNode
		x_min + (x_max-x_min+1)/2,			// x_min of this new ragnode
		x_max,								// x_max of this new ragnode
		y_min + (y_max-y_min+1)/2,			// y_min of this new ragnode
		y_max							);	// y_max of this new ragnode

	// On QuadTree side: 'Link' children to their RAG equivalents...
	pQuadNodeRepresented->GetChild(1)->pRagEquivalentNode = r1;
	pQuadNodeRepresented->GetChild(2)->pRagEquivalentNode = r2;
	pQuadNodeRepresented->GetChild(3)->pRagEquivalentNode = r3;
	pQuadNodeRepresented->GetChild(4)->pRagEquivalentNode = r4;

	// Link 4 nodes between themselves
	r1->AddLink( r2, true );	// true forces linking "two-ways": r2 is linked to r1, too.
	r1->AddLink( r3, true );
	r2->AddLink( r4, true );
	r3->AddLink( r4, true );

	// Check if old node had adjacent nodes.
	if( this->GetLinkList()->size() == 0 )
	{
		return VIPRET_OK;
	}

	// Old node had adjacent nodes.
	// They must now be updated to point to correct subnodes that we have created OR
	//  the link must be cleaned... VERY DELICATE
	// AND we must make the correct new nodes inherit the correct old links
	list<vipRagNode*>::iterator Iter = this->GetLinkList()->begin();

	while( Iter != this->GetLinkList()->end() )
	{ // Now (*Iter) is a pointer to a node which was adjacent to the old node (this).
		// First of all, we must delete any
		//  nearby pointers which are pointing to the old node (this)
		(*Iter)->RemoveLink( this );

		// Check if the link of the old node must be added to sons
		if( r1->IsAdjacentTo( (*Iter) ) )
		{ // Add the link (two ways)
			(*Iter)->AddLink( r1, true );
		}
		if( r2->IsAdjacentTo( (*Iter) ) )
		{ // Add the link (two ways)
			(*Iter)->AddLink( r2, true );
		}
		if( r3->IsAdjacentTo( (*Iter) ) )
		{ // Add the link (two ways)
			(*Iter)->AddLink( r3, true );
		}
		if( r4->IsAdjacentTo( (*Iter) ) )
		{ // Add the link (two ways)
			(*Iter)->AddLink( r4, true );
		}

		Iter++;
	}

	// Destroy old node // TODO : Check if this works
	delete this;	// Move delete instruction immediatly outside this method?

	return VIPRET_OK;
}


// End of Region Adjacency Graph (RAG) Implementation
