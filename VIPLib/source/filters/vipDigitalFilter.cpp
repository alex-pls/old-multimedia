/** @file vipDigitalFilter.cpp
 *
 * File containing methods for the 'vipDigitalFilter' class.
 * The header for this class can be found in vipDigitalFilter.h, check that file
 * for class description.
 *
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



#include "vipDigitalFilter.h"


/**
 * @brief Default constructor call vipInput constructor which setup frame rate,
 *        initialize description arrays and set default name (should be updated).
 *
 * @param fps Frame per second value, default is 0, the max input+processing rate.
 */
vipDigitalFilter::vipDigitalFilter(vipDigitalFilterParameters* initParams) : vipFilter()
 {
	setParameters(initParams);
	reset();

	setName("Digital Filter");
	setDescription("Lowpass, gaussian, highpass....");
	setVersion(1.0);
 }


/**
 * @brief Destructor currenly clear only filters description strings.
 */
vipDigitalFilter::~vipDigitalFilter()
 {
	if (myParams != NULL)
		delete myParams;
	myParams = NULL;

 }


VIPRESULT vipDigitalFilter::reset()
 {
	INFO("VIPRESULT vipDigitalFilter::reset() [SET DEFAULT PARAMETERS]")

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



VIPRESULT vipDigitalFilter::setParameters (vipDigitalFilterParameters* initParams)
 {

	if ( initParams == NULL )
		myParams = new vipDigitalFilterParameters();
	else
		myParams = initParams;

	allocateBuffer(myParams->currentBuffer);

	return VIPRET_OK;
 }


VIPRESULT vipDigitalFilter::setDefaultKernel(int index)
 {

	if (myParams->currentKernel != NULL)
		delete myParams->currentKernel;

	myParams->currentKernel  = vipDFMatrix::createKernel_3x3(index);

	return VIPRET_OK;

 }



//////////////////////////////////////////////////////////




VIPRESULT vipDigitalFilter::importFrom(vipFrameYUV420& img)
 {
	DEBUGMSG("VIPRESULT vipDigitalFilter::importFrom(vipFrameYUV420& img) [reading data]", myParams->runMode)

	int ret = VIPRET_OK;

	if ( !isBufferYUV() )
	 {
		useBufferYUV(img.width, img.height);
		ret = VIPRET_OK_DEPRECATED;
	 }

	if (myParams->currentKernel == NULL)
	 {
		*bufferYUV = img;
		return ret;
	 }
	else
		ret += doProcessing(img, *bufferYUV, *myParams->currentKernel, myParams->clampNegative);

	return ret;
 }

VIPRESULT vipDigitalFilter::importFrom(vipFrameRGB24& img)
 {
	DEBUGMSG("VIPRESULT vipDigitalFilter::importFrom(vipFrameYUV420& img) [reading data]", myParams->runMode)

	int ret = VIPRET_OK;

	if ( !isBufferRGB() )
	 {
		useBufferRGB(img.width, img.height);
		ret = VIPRET_OK_DEPRECATED;
	 }

	if (myParams->currentKernel == NULL)
	 {
		*bufferRGB = img;
		return ret;
	 }
	else
		ret += doProcessing(img, *bufferRGB, *myParams->currentKernel, myParams->clampNegative);

	return ret;
 }


VIPRESULT vipDigitalFilter::importFrom(vipFrameT<unsigned char>& img)
 {
	DEBUGMSG("VIPRESULT vipDigitalFilter::importFrom(vipFrameT& img) [reading data]", myParams->runMode)

	return VIPRET_NOT_IMPLEMENTED;
 }






////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////



VIPRESULT vipDigitalFilter::doProcessing(vipFrameRGB24& source, vipFrameRGB24& dest, vipDFMatrix& kernel, bool clamp)
 {
	if (source.width != dest.width || source.height != dest.height)
		dest.reAllocCanvas(source.width, source.height);

	signed long numb;
	unsigned int src_w = source.width;

	if (kernel.getDim() == 3)
	 {
	  for(unsigned int x=0; x < src_w; x++)
	   for(unsigned int y=0; y < source.height; y++)
		{
			if ( x && y && (x != src_w-1) && (y != source.height-1)) //3x3 matrix!
			 {
			   for(int ch=0; ch < 3; ch++)
				{
					numb = (long) (	(long) source.data[(y-1) * src_w + (x-1)][ch] * kernel[0] +
									(long) source.data[(y-1) * src_w +  x   ][ch] * kernel[1] +
									(long) source.data[(y-1) * src_w + (x+1)][ch] * kernel[2] +
									(long) source.data[ y    * src_w + (x-1)][ch] * kernel[3] +
									(long) source.data[ y    * src_w +  x   ][ch] * kernel[4] +
									(long) source.data[ y    * src_w + (x+1)][ch] * kernel[5] +
									(long) source.data[(y+1) * src_w + (x-1)][ch] * kernel[6] +
									(long) source.data[(y+1) * src_w +  x   ][ch] * kernel[7] +
									(long) source.data[(y+1) * src_w + (x+1)][ch] * kernel[8]	);

					if ( numb )
						numb /= (long)kernel[9];//normalization

					dest.data[y * src_w + x][ch] = (unsigned char)numb;
				 }
			 }
			else
			 {
				dest.data[y * src_w + x][0] = source.data[y * src_w + x][0];
				dest.data[y * src_w + x][1] = source.data[y * src_w + x][1];
				dest.data[y * src_w + x][2] = source.data[y * src_w + x][2];
			 }
	   }
	 }
	else if (kernel.getDim() == 5)
	 {
	  for(unsigned int x=0; x < src_w; x++)
	   for(unsigned int y=0; y < source.height; y++)
		{
			if ( (x-2) && (y-2) && (x != src_w-2) && (y != source.height-2)) //5x5 matrix!
			 {
			   for(int ch=0; ch < 3; ch++)
				{
				 numb = (long) (
									(long) source.data[(y-2) * src_w + (x-2)][ch] * kernel[0] +
									(long) source.data[(y-2) * src_w + (x-1)][ch] * kernel[1] +
									(long) source.data[(y-2) * src_w +  x   ][ch] * kernel[2] +
									(long) source.data[(y-2) * src_w + (x+1)][ch] * kernel[3] +
									(long) source.data[(y-2) * src_w + (x+2)][ch] * kernel[4] +
									(long) source.data[(y-1) * src_w + (x-2)][ch] * kernel[5] +
									(long) source.data[(y-1) * src_w + (x-1)][ch] * kernel[6] +
									(long) source.data[(y-1) * src_w +  x   ][ch] * kernel[7] +
									(long) source.data[(y-1) * src_w + (x+1)][ch] * kernel[8] +
									(long) source.data[(y-1) * src_w + (x+2)][ch] * kernel[9] +
									(long) source.data[ y    * src_w + (x-2)][ch] * kernel[10] +
									(long) source.data[ y    * src_w + (x-1)][ch] * kernel[11] +
									 (long) source.data[ y    * src_w +  x   ][ch] * kernel[12] +
									(long) source.data[ y    * src_w + (x+1)][ch] * kernel[13] +
									(long) source.data[ y    * src_w + (x+2)][ch] * kernel[14] +
									(long) source.data[(y+1) * src_w + (x-2)][ch] * kernel[15] +
									(long) source.data[(y+1) * src_w + (x-1)][ch] * kernel[16] +
									(long) source.data[(y+1) * src_w +  x   ][ch] * kernel[17] +
									(long) source.data[(y+1) * src_w + (x+1)][ch] * kernel[18] +
									(long) source.data[(y+1) * src_w + (x+2)][ch] * kernel[19] +
									(long) source.data[(y+2) * src_w + (x-2)][ch] * kernel[20] +
									(long) source.data[(y+2) * src_w + (x-1)][ch] * kernel[21] +
									(long) source.data[(y+2) * src_w +  x   ][ch] * kernel[22] +
									(long) source.data[(y+2) * src_w + (x+1)][ch] * kernel[23] +
									(long) source.data[(y+2) * src_w + (x+2)][ch] * kernel[24]	);

				 if ( numb )
					numb /= (long)kernel[25];//normalization

				 dest.data[y * src_w + x][ch] = (unsigned char)numb;
				}
			 }
			else
			 {
				dest.data[y * src_w + x][0] = source.data[y * src_w + x][0];
				dest.data[y * src_w + x][1] = source.data[y * src_w + x][1];
				dest.data[y * src_w + x][2] = source.data[y * src_w + x][2];
			 }
	   }
	 }
	else if (kernel.getDim() == 7)
	 {
		for(unsigned int x=0; x < src_w; x++)
		   for(unsigned int y=0; y < source.height; y++)
			{
			 if ( (x-3) && (y-3) && (x != src_w-3) && (y != source.height-3)) //7x7 matrix!
			  {
			   for(int ch=0; ch < 3; ch++)
				{
				 numb = (long) (
					 				(long) source.data[(y-3) * src_w + (x-3)][ch] * kernel[0] +
					 				(long) source.data[(y-3) * src_w + (x-2)][ch] * kernel[1] +
					 				(long) source.data[(y-3) * src_w + (x-1)][ch] * kernel[2] +
					 				(long) source.data[(y-3) * src_w +  x   ][ch] * kernel[3] +
									(long) source.data[(y-3) * src_w + (x+1)][ch] * kernel[4] +
									(long) source.data[(y-3) * src_w + (x+2)][ch] * kernel[5] +
									(long) source.data[(y-3) * src_w + (x+3)][ch] * kernel[6] +
					 				(long) source.data[(y-2) * src_w + (x-3)][ch] * kernel[7] +
					 				(long) source.data[(y-2) * src_w + (x-2)][ch] * kernel[8] +
					 				(long) source.data[(y-2) * src_w + (x-1)][ch] * kernel[9] +
					 				(long) source.data[(y-2) * src_w +  x   ][ch] * kernel[10] +
									(long) source.data[(y-2) * src_w + (x+1)][ch] * kernel[11] +
									(long) source.data[(y-2) * src_w + (x+2)][ch] * kernel[12] +
									(long) source.data[(y-2) * src_w + (x+3)][ch] * kernel[13] +
					 				(long) source.data[(y-1) * src_w + (x-3)][ch] * kernel[14] +
					 				(long) source.data[(y-1) * src_w + (x-2)][ch] * kernel[15] +
					 				(long) source.data[(y-1) * src_w + (x-1)][ch] * kernel[16] +
					 				(long) source.data[(y-1) * src_w +  x   ][ch] * kernel[17] +
									(long) source.data[(y-1) * src_w + (x+1)][ch] * kernel[18] +
									(long) source.data[(y-1) * src_w + (x+2)][ch] * kernel[19] +
									(long) source.data[(y-1) * src_w + (x+3)][ch] * kernel[20] +
					 				(long) source.data[ y    * src_w + (x-3)][ch] * kernel[21] +
					 				(long) source.data[ y    * src_w + (x-2)][ch] * kernel[22] +
					 				(long) source.data[ y    * src_w + (x-1)][ch] * kernel[23] +
					 				 (long) source.data[ y    * src_w +  x   ][ch] * kernel[24] +
									(long) source.data[ y    * src_w + (x+1)][ch] * kernel[25] +
									(long) source.data[ y    * src_w + (x+2)][ch] * kernel[26] +
									(long) source.data[ y    * src_w + (x+3)][ch] * kernel[27] +
					 				(long) source.data[(y+1) * src_w + (x-3)][ch] * kernel[28] +
					 				(long) source.data[(y+1) * src_w + (x-2)][ch] * kernel[29] +
					 				(long) source.data[(y+1) * src_w + (x-1)][ch] * kernel[30] +
					 				(long) source.data[(y+1) * src_w +  x   ][ch] * kernel[31] +
									(long) source.data[(y+1) * src_w + (x+1)][ch] * kernel[32] +
									(long) source.data[(y+1) * src_w + (x+2)][ch] * kernel[33] +
									(long) source.data[(y+1) * src_w + (x+3)][ch] * kernel[34] +
					 				(long) source.data[(y+2) * src_w + (x-3)][ch] * kernel[35] +
					 				(long) source.data[(y+2) * src_w + (x-2)][ch] * kernel[36] +
					 				(long) source.data[(y+2) * src_w + (x-1)][ch] * kernel[37] +
					 				(long) source.data[(y+2) * src_w +  x   ][ch] * kernel[38] +
									(long) source.data[(y+2) * src_w + (x+1)][ch] * kernel[39] +
									(long) source.data[(y+2) * src_w + (x+2)][ch] * kernel[40] +
									(long) source.data[(y+2) * src_w + (x+3)][ch] * kernel[41] +
					 				(long) source.data[(y+3) * src_w + (x-3)][ch] * kernel[42] +
					 				(long) source.data[(y+3) * src_w + (x-2)][ch] * kernel[43] +
					 				(long) source.data[(y+3) * src_w + (x-1)][ch] * kernel[44] +
					 				(long) source.data[(y+3) * src_w +  x   ][ch] * kernel[45] +
									(long) source.data[(y+3) * src_w + (x+1)][ch] * kernel[46] +
									(long) source.data[(y+3) * src_w + (x+2)][ch] * kernel[47] +
									(long) source.data[(y+3) * src_w + (x+3)][ch] * kernel[48]	);

					if ( numb )
						numb /= (long)kernel[49];//normalization

					dest.data[y * src_w + x][ch] = (unsigned char)numb;
				 }
			 }
			else
			 {
				dest.data[y * src_w + x][0] = source.data[y * src_w + x][0];
				dest.data[y * src_w + x][1] = source.data[y * src_w + x][1];
				dest.data[y * src_w + x][2] = source.data[y * src_w + x][2];
			 }
	   }
	 }
	else
		return VIPRET_NOT_IMPLEMENTED;

   return VIPRET_OK;
 }


VIPRESULT vipDigitalFilter::doProcessing(vipFrameYUV420& source, vipFrameYUV420& dest, vipDFMatrix& kernel, bool clamp)
 {
	if (source.width != dest.width || source.height != dest.height)
		dest.reAllocCanvas(source.width, source.height);

	return VIPRET_NOT_IMPLEMENTED;

 }

VIPRESULT vipDigitalFilter::doProcessing(vipFrameT<unsigned char>& source, vipFrameT<unsigned char>& dest, vipDFMatrix& kernel, bool clamp)
 {
	if (source.width != dest.width || source.height != dest.height)
		dest.reAllocCanvas(source.width, source.height);

	return VIPRET_NOT_IMPLEMENTED;

 }


VIPRESULT vipDigitalFilter::doRotateKernel(vipDFMatrix& kernel)
{
	if (&kernel == NULL)
		return VIPRET_PARAM_ERR;

	char tmpVal;

	if (kernel.getDim() == 3)
	 {
		tmpVal = kernel[0];
		kernel[0] = kernel[3];
		kernel[3] = kernel[6];
		kernel[6] = kernel[7];
		kernel[7] = kernel[8];
		kernel[8] = kernel[5];
		kernel[5] = kernel[2];
		kernel[2] = kernel[1];
		kernel[1] = tmpVal;
	 }
	else if (kernel.getDim() == 3)
	 {
		tmpVal = kernel[0];
		kernel[0] = kernel[10];
		kernel[10] = kernel[20];
		kernel[20] = kernel[22];
		kernel[22] = kernel[24];
		kernel[24] = kernel[14];
		kernel[14] = kernel[4];
		kernel[4] = kernel[2];
		kernel[2] = tmpVal;

		tmpVal = kernel[5];
		kernel[5] = kernel[15];
		kernel[15] = kernel[21];
		kernel[21] = kernel[23];
		kernel[23] = kernel[19];
		kernel[19] = kernel[9];
		kernel[9] = kernel[3];
		kernel[3] = kernel[1];
		kernel[1] = tmpVal;

		tmpVal = kernel[6];
		kernel[6] = kernel[11];
		kernel[11] = kernel[16];
		kernel[16] = kernel[17];
		kernel[17] = kernel[18];
		kernel[18] = kernel[13];
		kernel[13] = kernel[8];
		kernel[8] = kernel[7];
		kernel[7] = tmpVal;
	 }
	else if (kernel.getDim() == 3)
	 {
		tmpVal = kernel[2];
		kernel[2] = kernel[7];
		kernel[7] = kernel[28];
		kernel[28] = kernel[43];
		kernel[43] = kernel[46];
		kernel[46] = kernel[41];
		kernel[41] = kernel[20];
		kernel[20] = kernel[5];
		kernel[5] = tmpVal;

		tmpVal = kernel[1];
		kernel[1] = kernel[14];
		kernel[14] = kernel[35];
		kernel[35] = kernel[44];
		kernel[44] = kernel[47];
		kernel[47] = kernel[34];
		kernel[34] = kernel[13];
		kernel[13] = kernel[4];
		kernel[4] = tmpVal;

		tmpVal = kernel[0];
		kernel[0] = kernel[21];
		kernel[21] = kernel[42];
		kernel[42] = kernel[45];
		kernel[45] = kernel[48];
		kernel[48] = kernel[27];
		kernel[27] = kernel[6];
		kernel[6] = kernel[3];
		kernel[3] = tmpVal;

		tmpVal = kernel[9];
		kernel[9] = kernel[15];
		kernel[15] = kernel[29];
		kernel[29] = kernel[37];
		kernel[37] = kernel[39];
		kernel[39] = kernel[33];
		kernel[33] = kernel[19];
		kernel[19] = kernel[11];
		kernel[11] = tmpVal;

		tmpVal = kernel[8];
		kernel[8] = kernel[22];
		kernel[22] = kernel[36];
		kernel[36] = kernel[38];
		kernel[38] = kernel[40];
		kernel[40] = kernel[26];
		kernel[26] = kernel[12];
		kernel[12] = kernel[10];
		kernel[10] = tmpVal;

		tmpVal = kernel[16];
		kernel[16] = kernel[23];
		kernel[23] = kernel[30];
		kernel[30] = kernel[31];
		kernel[31] = kernel[32];
		kernel[32] = kernel[25];
		kernel[25] = kernel[18];
		kernel[18] = kernel[17];
		kernel[17] = tmpVal;
    }
   else
		return VIPRET_NOT_IMPLEMENTED;
   return VIPRET_OK;
 }



////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////







vipDigitalFilterParameters::vipDigitalFilterParameters()
 {
	currentKernel = NULL;
	reset();
 }

void vipDigitalFilterParameters::reset()
 {
	currentBuffer = vipFilterParameters::NONE;
	clampNegative = true;
//... BUG
 }

void vipDigitalFilterParameters::setCurrentKernel(vipDFMatrix* data)
 {
	currentKernel = data;
 }

void vipDigitalFilterParameters::setClampNegative(bool value)
 {
	clampNegative = value;
 }


int vipDigitalFilterParameters::saveToStreamXML(FILE *fp)
 {
	int ret = VIPRET_OK;

	if ( fp == NULL )
		return VIPRET_PARAM_ERR;

	if( fprintf(fp, "<vipDigitalFilterParameters>\n") == EOF )
		return VIPRET_INTERNAL_ERR;

	if ( fprintf(fp, "  <internalBufferType value=\"%u\" />\n", (int)currentBuffer) == EOF)
		return VIPRET_INTERNAL_ERR;


	if (currentKernel != NULL)
	 {
		if( fprintf(fp, " <KernelData>\n") == EOF )
			return VIPRET_INTERNAL_ERR;

		ret = currentKernel->saveToStream(fp);

		if( fprintf(fp, " </KernelData>\n") == EOF )
			return VIPRET_INTERNAL_ERR;
	 }

	if( fprintf(fp, "</vipDigitalFilterParameters>\n") == EOF )
		return VIPRET_INTERNAL_ERR;

	return ret;
 }


int vipDigitalFilterParameters::loadFromStreamXML(FILE *fp)
 {
	if ( fscanf(fp, "<vipDigitalFilterParameters>\n") == EOF )
		throw "error in XML file, unable to import data.";

	int cB = (int)currentBuffer;
	if ( fscanf(fp, "  <internalBufferType value=\"%u\" />\n", &cB) == EOF )
		throw "error in XML file, unable to import data.";
	currentBuffer = (BUFFER_TYPE)cB;

	int ret = VIPRET_OK;

	if ( fscanf(fp, " <KernelData>\n") != EOF )
	 {
		if (currentKernel == NULL)
			currentKernel = new vipDFMatrix();

		ret = currentKernel->loadFromStream(fp);
	 }



	return ret;
 }




