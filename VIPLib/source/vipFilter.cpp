/** @file vipFilter.cpp
 *
 * File containing methods for the 'vipFilter' class.
 * The header for this class can be found in vipFilter.h, check that file
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



#include "vipFilter.h"


/**
 * @brief Default constructor call vipInput constructor which setup frame rate,
 *        initialize description arrays and set default name (should be updated).
 *
 * @param fps Frame per second value, default is 0, the max input+processing rate.
 */
vipFilter::vipFilter(float fps) : vipInput(fps), vipObject()
 {
	bufferYUV = NULL;
	bufferYUV444 = NULL;
	bufferRGB = NULL;
	bufferTuC = NULL;

	setName("Abstract Filter");
	setDescription("Abstract Class");
	setVersion(0.0);
 };


/**
 * @brief Destructor currenly clear only filters description strings.
 */
vipFilter::~vipFilter()
 {
	if (bufferYUV != NULL)
		delete bufferYUV;
	
	if (bufferYUV444 != NULL)
		delete bufferYUV444;

	if (bufferRGB != NULL)
		delete bufferRGB;

	if (bufferTuC != NULL)
		delete bufferTuC;

	bufferYUV = NULL;
	bufferYUV444 = NULL;
	bufferRGB = NULL;
	bufferTuC = NULL;
 };



/**
 * @brief Allocate the buffer selected BUFFER_TYPE enumeration.
 *
 * @param bType select the buffer to initialize, if value is NONE
 *        or unknown, all buffers are realeased.
 */
void vipFilter::allocateBuffer(vipFilterParameters::BUFFER_TYPE bType)
 {
	switch (bType)
	 {
		 case vipFilterParameters::YUV:
			useBufferYUV(0,0);
		 	break;
		 case vipFilterParameters::YUV444:
		 	useBufferYUV444(0,0);
		 	break;
		 case vipFilterParameters::RGB:
			useBufferRGB(0,0);
		 	break;
		 case vipFilterParameters::TuC:
			 useBufferTuC(0,0,vipFrame::VIPFRAME_NONE);
		 	break;
		 case vipFilterParameters::NONE:
		 default:
		 	releaseBuffers();
	 }
 };


/**
 * @brief Close and free all buffers, then they are set to NULL.
 */
void vipFilter::releaseBuffers()
 {
	if (bufferYUV != NULL)
		delete bufferYUV;
	if (bufferYUV444 != NULL)
		delete bufferYUV444;
	if (bufferRGB != NULL)
		delete bufferRGB;

	if (bufferTuC != NULL)
		delete bufferTuC;

	bufferYUV = NULL;
	bufferYUV444 = NULL;
	bufferRGB = NULL;
	bufferTuC = NULL;

	if ( getFilterParameters() != NULL )
		getFilterParameters()->currentBuffer = vipFilterParameters::NONE;
 };


/**
 * @brief  Update and set current buffer (vipFrameYUV420) to new size.
 * @param[in] width new buffer's width.
 * @param[in] height new buffer's height.
 */
void vipFilter::useBufferYUV(unsigned int width, unsigned int height)
 {
	if ( bufferYUV == NULL )
		bufferYUV = new vipFrameYUV420(width, height);
	else if ( bufferYUV->width != width || bufferYUV->height != height )
		bufferYUV->reAllocCanvas(width, height);

	if ( getFilterParameters() != NULL )
		getFilterParameters()->currentBuffer = vipFilterParameters::YUV;


	if ( bufferYUV444 != NULL )
	 {
		delete bufferYUV444;
		bufferYUV444 = NULL;
	 }
	if ( bufferRGB != NULL )
	 {
		delete bufferRGB;
		bufferRGB = NULL;
	 }
	if ( bufferTuC != NULL )
	 {
		delete bufferTuC;
		bufferTuC = NULL;
	 }
 };

/**
 * @brief  Update and set current buffer (vipFrameYUV444) to new size.
 * @param[in] width new buffer's width.
 * @param[in] height new buffer's height.
 */
void vipFilter::useBufferYUV444(unsigned int width, unsigned int height)
 {
	if ( bufferYUV444 == NULL )
		bufferYUV444 = new vipFrameYUV444(width, height);
	else if ( bufferYUV444->width != width || bufferYUV444->height != height )
		bufferYUV444->reAllocCanvas(width, height);

	if ( getFilterParameters() != NULL )
		getFilterParameters()->currentBuffer = vipFilterParameters::YUV444;

	if ( bufferRGB != NULL )
	 {
		delete bufferRGB;
		bufferRGB = NULL;
	 }
	if ( bufferYUV != NULL )
	 {
		delete bufferYUV;
		bufferYUV = NULL;
	 }
	if ( bufferTuC != NULL )
	 {
		delete bufferTuC;
		bufferTuC = NULL;
	 }
 };

/**
 * @brief  Update and set current buffer (vipFrameRGB24) to new size.
 * @param[in] width new buffer's width.
 * @param[in] height new buffer's height.
 */
void vipFilter::useBufferRGB(unsigned int width, unsigned int height)
 {
	if ( bufferRGB == NULL )
		bufferRGB = new vipFrameRGB24(width, height);
	else if ( bufferRGB->width != width || bufferRGB->height != height )
		bufferRGB->reAllocCanvas(width, height);

	if ( getFilterParameters() != NULL )
		getFilterParameters()->currentBuffer = vipFilterParameters::RGB;

	if ( bufferYUV != NULL )
	 {
		delete bufferYUV;
		bufferYUV = NULL;
	 }
	if ( bufferYUV444 != NULL )
	{
		delete bufferYUV444;
		bufferYUV444 = NULL;
	}
	if ( bufferTuC != NULL )
	 {
		delete bufferTuC;
		bufferTuC = NULL;
	 }
 };

/**
 * @brief  Update and set current buffer (vipFrameT<uchar>) to new size.
 * @param[in] width new buffer's width.
 * @param[in] height new buffer's height.
 */
void vipFilter::useBufferTuC(unsigned int width, unsigned int height, vipFrame::VIPFRAME_PROFILE profile)
 {
	if ( bufferTuC == NULL )
		bufferTuC = new vipFrameT<unsigned char>(width, height, profile);
	else if ( bufferTuC->width != width || bufferTuC->height != height )
		bufferTuC->reAllocCanvas(width, height);

	if ( getFilterParameters() != NULL )
		getFilterParameters()->currentBuffer = vipFilterParameters::TuC;

	if ( bufferYUV != NULL )
	 {
		delete bufferYUV;
		bufferYUV = NULL;
	 }
	if ( bufferYUV444 != NULL )
		 {
			delete bufferYUV444;
			bufferYUV444 = NULL;
		 }
	if ( bufferRGB != NULL )
	 {
		delete bufferRGB;
		bufferRGB = NULL;
	 }
 };


/**
 * @brief  Set current canvas' height.
 *
 * @return height in pixel.
 */
VIPRESULT vipFilter::setHeight(unsigned int value)
 {
	if (bufferYUV != NULL)
	 {
		bufferYUV->reAllocCanvas(bufferYUV->width, value);
		return VIPRET_OK;
	 }
	if (bufferYUV444 != NULL)
	{
		bufferYUV444->reAllocCanvas(bufferYUV444->width, value);
		return VIPRET_OK;
	}
	else if (bufferRGB != NULL)
	 {
		bufferRGB->reAllocCanvas(bufferRGB->width, value);
		return VIPRET_OK;
	 }
	else if (bufferTuC != NULL)
	 {
		bufferTuC->reAllocCanvas(bufferTuC->width, value);
		return VIPRET_OK;
	 }

	return VIPRET_NOT_IMPLEMENTED;
 };

/**
 * @brief  Set current canvas' width.
 *
 * @return width in pixel.
 */
VIPRESULT vipFilter::setWidth(unsigned int value)
 {
	if (bufferYUV != NULL)
	 {
		bufferYUV->reAllocCanvas(value, bufferYUV->height);
		return VIPRET_OK;
	 }
	if (bufferYUV444 != NULL)
	{
		bufferYUV444->reAllocCanvas(bufferYUV444->width, value);
		return VIPRET_OK;
	}
	else if (bufferRGB != NULL)
	 {
		bufferRGB->reAllocCanvas(value, bufferRGB->height);
		return VIPRET_OK;
	 }
	else if (bufferTuC != NULL)
	 {
		bufferTuC->reAllocCanvas(value, bufferTuC->height);
		return VIPRET_OK;
	 }

	return VIPRET_NOT_IMPLEMENTED;
 };

/**
 * @brief  Read current canvas's width.
 *
 * @return Width in pixel.
 */
unsigned int vipFilter::getWidth() const
 {
	if (bufferYUV != NULL)
		return bufferYUV->width;
	
	else if (bufferYUV444 != NULL)
		return bufferYUV444->width;
	
	else if (bufferRGB != NULL)
		return bufferRGB->width;

	else if (bufferTuC != NULL)
		return bufferTuC->width;

	return 0;
 };

/**
 * @brief  Read current canvas's height.
 *
 * @return Height in pixel.
 */
unsigned int vipFilter::getHeight() const
 {
	if (bufferYUV != NULL)
		return bufferYUV->height;

	else if (bufferYUV444 != NULL)
		return bufferYUV444->height;
	
	else if (bufferRGB != NULL)
			return bufferRGB->height;

	else if (bufferTuC != NULL)
		return bufferTuC->height;

	return 0;
 };


/**
 * @brief  Evaluate if there is any data to extract, current
 *         implementation just check the state of current buffer.
 *
 * @return true if all buffers are empty.
 */
bool vipFilter::EoF()
 {
	if (bufferYUV != NULL || bufferYUV444 != NULL || bufferRGB != NULL || bufferTuC != NULL)
		return false;

	return true;
 };





VIPRESULT vipFilter::extractTo(vipFrameYUV420& img)
 {
	INFO("VIPRESULT vipFilter::extractTo(vipFrameYUV420& img) [pushing data]")

	if ( !isBufferYUV() )
		return VIPRET_ILLEGAL_USE;

	img = *bufferYUV;

	return VIPRET_OK;
 };

VIPRESULT vipFilter::extractTo(vipFrameYUV444& img)
 {
	INFO("VIPRESULT vipFilter::extractTo(vipFrameYUV444& img) [pushing data]")

	if ( !isBufferYUV444() )
		return VIPRET_ILLEGAL_USE;

	img = *bufferYUV444;

	return VIPRET_OK;
 };

VIPRESULT vipFilter::extractTo(vipFrameRGB24& img)
 {
	INFO("VIPRESULT vipFilter::extractTo(vipFrameRGB24& img) [pushing data]")

	if ( !isBufferRGB() )
		return VIPRET_ILLEGAL_USE;

	img = *bufferRGB;

	return VIPRET_OK;
 };

VIPRESULT vipFilter::extractTo(vipFrameT<unsigned char>& img)
 {
	INFO("VIPRESULT vipFilter::extractTo(vipFrameT<unsigned char>& img) [pushing data]")

	if ( !isBufferTuC() )
		return VIPRET_ILLEGAL_USE;

	img = *bufferTuC;

	return VIPRET_OK;
 };




/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////





/**
 * @brief  Serialize class to XML file.
 *         Open file stream and call inherited saveToStreamXML()
 *         to save specific data structures.
 *
 * @param[in] filename output file name (NULL Terminated string)
 *
 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
 */
int vipFilterParameters::saveToXML(const char* filename)
 {
	FILE *fp;
	int ret = VIPRET_OK;

	if ( (fp = fopen(filename, "w")) == NULL )
		return VIPRET_PARAM_ERR;

	if( fprintf(fp, "<?xml version=\"1.0\" ?>\n\n") == EOF )
	 {
		fclose(fp);
		return VIPRET_INTERNAL_ERR;
	 }

	ret = saveToStreamXML(fp);

	fclose(fp);

	return ret;
 };


/**
 * @brief  Deserialize class from XML file.
 *         Open file stream and call inherited loadFromStreamXML()
 *         to load specific data structures.
 *
 * @param[in] filename input file name (NULL Terminated string)
 *
 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
 */
int vipFilterParameters::loadFromXML(const char* filename)
 {
    FILE *fp;
	int ret = VIPRET_OK;

    if ( (fp=fopen(filename,"r")) == NULL )
    	return VIPRET_PARAM_ERR;

    float xmlversion = 1.0;

    fscanf(fp, "<?xml version=\"%f\" ?>\n\n", &xmlversion);

    if (xmlversion == 0)
    	throw "Incompatible XML file format";

	ret = loadFromStreamXML(fp);

	// closing tags reading is omitted

    fclose(fp);

    return ret;
 };


