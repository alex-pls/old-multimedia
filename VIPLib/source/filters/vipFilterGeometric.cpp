/** @file vipFilterGeometric.cpp
 *
 * File containing methods for the 'vipFilterGeometric' class.
 * The header for this class can be found in vipFilterGeometric.h,
 * check that file for class description.
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



#include "vipFilterGeometric.h"
#include <math.h>


/**
 * @brief  Default constructor, initialize parameters and superclasses.
 * @param[in] initParams parameters for this module or NULL for defaults.
 */
vipFilterGeometric::vipFilterGeometric(vipFilterGeometricParameters* initParams) : vipFilter()
 {
	INFO("vipFilterGeometric::vipFilterGeometric(..* initParams) : vipFilter() [CONTRUCTOR]")
	myParams = NULL;
	setParameters(initParams);

	setName("Geometric Editing Filter");
	setDescription("Resize, Crop, Rotation, Flip, Resize");
	setVersion(1.0);
 }

/**
 * @brief Default destructor, free buffer.
 */
vipFilterGeometric::~vipFilterGeometric()
 {
	INFO("vipFilterGeometric::~vipFilterGeometric() [DESTRUCTOR]")

//	printf("vipFilterGeometric::~vipFilterGeometric() [DESTRUCTOR]");

	if (myParams != NULL)
		delete myParams;
	myParams = NULL;
 }

/**
 * @brief  Reset buffers and parameters.
 *
 * @return VIPRET_OK
 */
VIPRESULT vipFilterGeometric::reset()
 {
	INFO("VIPRESULT vipFilterGeometric::reset() [SET DEFAULT PARAMETERS]")

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
 * @param[in] initParams Instance of vipFilterGeometricParameters or NULL,
 *                       NULL argument make function to create a new
 *                       instance with default parameters.
 *
 * @return VIPRET_OK
 */
VIPRESULT vipFilterGeometric::setParameters (vipFilterGeometricParameters* initParams)
 {
	if (initParams != NULL && myParams == initParams)
		return VIPRET_PARAM_ERR;

	if ( initParams == NULL )
	 {
		if ( myParams != NULL )
			reset();
		else
			myParams = new vipFilterGeometricParameters();
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
 * @brief Process the frame with current settings and store in buffer.
 *
 * @param[in] img VIPLibb Cache Frame to be processed.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
 *
 * @note  Input operator (<<) call directly this function.
 * @see   operator << (vipFrameYUV420&)
 */
VIPRESULT vipFilterGeometric::importFrom(vipFrameYUV420& img)
 {
	DEBUGMSG("VIPRESULT vipFilterGeometric::importFrom(vipFrameYUV420& img) [reading data]", myParams->runMode)

	switch ( myParams->runMode )
	 {
	 case vipFilterGeometricParameters::DO_NOTHING:
			if ( !isBufferYUV() )
			 {
				useBufferYUV(img.width, img.height);
				*bufferYUV = img;
				return VIPRET_OK_DEPRECATED;
			 }
			else
			 {
				*bufferYUV = img;
				return VIPRET_OK;
			 }

	 case vipFilterGeometricParameters::ROTATE90:
			return rotate90(img);

	 case vipFilterGeometricParameters::ROTATE180:
			return rotate180(img);

	 case vipFilterGeometricParameters::ROTATE270:
			return rotate270(img);

	 case vipFilterGeometricParameters::ROTATE:
			return rotate( img, myParams->par_Rotation );

	 case vipFilterGeometricParameters::FLIP_VERTICAL:
			return flipVertical(img);

	 case vipFilterGeometricParameters::FLIP_HORIZONTAL:
			return flipHorizontal(img);

	 case vipFilterGeometricParameters::RESIZE:
			return resize( img, myParams->par_ResizeWidth, myParams->par_ResizeHeight);

	 case vipFilterGeometricParameters::RESIZECANVAS:
			return resizeCanvas( img, myParams->par_ResizeWidth, myParams->par_ResizeHeight );

	 default:
		  return VIPRET_PARAM_ERR;
	 }
 }

/**
 * @brief Process the frame with current settings and store in buffer.
 *
 * @param[in] img VIPLib Cache Frame (in YUV444 format) to be processed.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
 *
 * @note  Input operator (<<) call directly this function.
 * @see   operator << (vipFrameYUV444&)
 */
VIPRESULT vipFilterGeometric::importFrom(vipFrameYUV444& img)
 {
	DEBUGMSG("VIPRESULT vipFilterGeometric::importFrom(vipFrameYUV444& img) [reading data]", myParams->runMode)

	switch ( myParams->runMode )
	 {
	 case vipFilterGeometricParameters::DO_NOTHING:
			if ( !isBufferYUV444() )
			 {
				useBufferYUV444(img.width, img.height);
				*bufferYUV444 = img;
				return VIPRET_OK_DEPRECATED;
			 }
			else
			 {
				*bufferYUV444 = img;
				return VIPRET_OK;
			 }

	 case vipFilterGeometricParameters::ROTATE90:
			return rotate90(img);

	 case vipFilterGeometricParameters::ROTATE180:
			return rotate180(img);

	 case vipFilterGeometricParameters::ROTATE270:
			return rotate270(img);

	 case vipFilterGeometricParameters::ROTATE:
			return rotate( img, myParams->par_Rotation );

	 case vipFilterGeometricParameters::FLIP_VERTICAL:
			return flipVertical(img);

	 case vipFilterGeometricParameters::FLIP_HORIZONTAL:
			return flipHorizontal(img);

	 case vipFilterGeometricParameters::RESIZE:
			return resize( img, myParams->par_ResizeWidth, myParams->par_ResizeHeight);

	 case vipFilterGeometricParameters::RESIZECANVAS:
			return resizeCanvas( img, myParams->par_ResizeWidth, myParams->par_ResizeHeight );

	 default:
		  return VIPRET_PARAM_ERR;
	 }
 }

/**
 * @brief Process the frame with current settings and store in buffer.
 *
 * @param[in] img VIPLib Cache24 Frame to be processed.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
 *
 * @note  Input operator (<<) call directly this function.
 * @see   operator << (vipFrameRGB24&)
 */
VIPRESULT vipFilterGeometric::importFrom(vipFrameRGB24& img)
 {
	DEBUGMSG("VIPRESULT vipFilterGeometric::importFrom(vipFrameRGB24& img) [reading data]", myParams->runMode)

	switch ( myParams->runMode )
	 {
	 case vipFilterGeometricParameters::DO_NOTHING:
			if ( !isBufferRGB() )
			 {
				useBufferRGB(img.width, img.height);
				*bufferRGB = img;
				return VIPRET_OK_DEPRECATED;
			 }
			else
			 {
				*bufferRGB = img;

				return VIPRET_OK;
			 }

	 case vipFilterGeometricParameters::ROTATE90:
			return rotate90(img);

	 case vipFilterGeometricParameters::ROTATE180:
			return rotate180(img);

	 case vipFilterGeometricParameters::ROTATE270:
			return rotate270(img);

	 case vipFilterGeometricParameters::ROTATE:
			return rotate( img, myParams->par_Rotation );

	 case vipFilterGeometricParameters::FLIP_VERTICAL:
			return flipVertical(img);

	 case vipFilterGeometricParameters::FLIP_HORIZONTAL:
			return flipHorizontal(img);

	 case vipFilterGeometricParameters::RESIZE:
			return resize( img, myParams->par_ResizeWidth, myParams->par_ResizeHeight);

	 case vipFilterGeometricParameters::RESIZECANVAS:
			return resizeCanvas( img, myParams->par_ResizeWidth, myParams->par_ResizeHeight );

	 default:
		  return VIPRET_PARAM_ERR;
	 }

 }

/**
 * @brief Process the frame with current settings and store in buffer.
 *
 * @param[in] img VIPLibb Grayscale Frame to be processed.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
 *
 * @note  Input operator (<<) call directly this function.
 * @see   operator << (vipFrameT&)
 */
VIPRESULT vipFilterGeometric::importFrom(vipFrameT<unsigned char>& img)
 {
	DEBUGMSG("VIPRESULT vipFilterGeometric::importFrom(vipFrameT& img) [reading data]", myParams->runMode)

	switch ( myParams->runMode )
	 {
	 case vipFilterGeometricParameters::DO_NOTHING:
			if ( !isBufferTuC() )
			 {
				useBufferTuC(img.width, img.height, img.profile);
				*bufferTuC = img;
				return VIPRET_OK_DEPRECATED;
			 }
			else
			 {
				*bufferTuC = img;
				return VIPRET_OK;
			 }

	 case vipFilterGeometricParameters::ROTATE90:
			return rotate90(img);

	 case vipFilterGeometricParameters::ROTATE180:
			return rotate180(img);

	 case vipFilterGeometricParameters::ROTATE270:
			return rotate270(img);

	 case vipFilterGeometricParameters::ROTATE:
			return rotate( img, myParams->par_Rotation );

	 case vipFilterGeometricParameters::FLIP_VERTICAL:
			return flipVertical(img);

	 case vipFilterGeometricParameters::FLIP_HORIZONTAL:
			return flipHorizontal(img);

	 case vipFilterGeometricParameters::RESIZE:
			return resize( img, myParams->par_ResizeWidth, myParams->par_ResizeHeight);

	 case vipFilterGeometricParameters::RESIZECANVAS:
			return resizeCanvas( img, myParams->par_ResizeWidth, myParams->par_ResizeHeight );

	 default:
		  return VIPRET_PARAM_ERR;
	 }

 }




////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////


// Video Size and Trasformation Functions


VIPRESULT vipFilterGeometric::resize(vipFrameYUV420& img, unsigned int dimX , unsigned int dimY)
 {
	useBufferYUV(dimX, dimY);

	return VIPRET_NOT_IMPLEMENTED;
 }

VIPRESULT vipFilterGeometric::resize(vipFrameYUV444& img, unsigned int dimX , unsigned int dimY)
 {
	useBufferYUV444(dimX, dimY);

	return VIPRET_NOT_IMPLEMENTED;
 }

VIPRESULT vipFilterGeometric::resize(vipFrameRGB24& img, unsigned int dimX , unsigned int dimY)
 {
	

		float rx=(float)img.width/(float)dimX;
		float ry=(float)img.height/(float)dimY;
		

				

//		printf("New Size: %d, %d\n", dimX, dimY);
//		printf("Resize Rate: %.2f on X and %.2f on Y\n", rx, ry);
		int x,y;
		useBufferRGB(dimX, dimY);
		
		
		for (y=0; y<dimY; y++)
			for (x=0; x<dimX; x++)
				bufferRGB->data[y*bufferRGB->width+x] = img.data[(int)(y*ry)*img.width+(int)(x*rx)];
			
		

		

	return VIPRET_OK;
 }

VIPRESULT vipFilterGeometric::resize(vipFrameT<unsigned char>& img, unsigned int dimX , unsigned int dimY)
 {
	useBufferTuC(dimX, dimY, img.profile);

	return VIPRET_NOT_IMPLEMENTED;
 }
////////////////////////////////////////////////////////////////////////////////////

VIPRESULT vipFilterGeometric::resizeCanvas(vipFrameYUV420& img, unsigned int dimX, unsigned int dimY)
 {
	useBufferYUV(dimX, dimY);

	return VIPRET_NOT_IMPLEMENTED;
 }

VIPRESULT vipFilterGeometric::resizeCanvas(vipFrameYUV444& img, unsigned int dimX, unsigned int dimY)
 {
	useBufferYUV444(dimX, dimY);

	return VIPRET_NOT_IMPLEMENTED;
 }

VIPRESULT vipFilterGeometric::resizeCanvas(vipFrameRGB24& img, unsigned int dimX, unsigned int dimY)
 {
	useBufferRGB(dimX, dimY);

	for ( unsigned int y=0; y < img.height; y++ ) // single pixel copy routine
	  for ( unsigned int x=0; x < img.width; x++ )
		bufferRGB->data[y*bufferRGB->width+x] = img.data[ y * img.width + x ];

	return VIPRET_OK;
 }

VIPRESULT vipFilterGeometric::resizeCanvas(vipFrameT<unsigned char>& img, unsigned int dimX, unsigned int dimY)
 {
	useBufferTuC(dimX, dimY, img.profile);

	return VIPRET_NOT_IMPLEMENTED;
 }
////////////////////////////////////////////////////////////////////////////////////

VIPRESULT vipFilterGeometric::resizeCanvas(vipFrameYUV420& img, unsigned int dimX, unsigned int dimY, unsigned char& valY, unsigned char& valU, unsigned char& valV)
 {
	useBufferYUV(dimX, dimY);

	return VIPRET_NOT_IMPLEMENTED;
 }

VIPRESULT vipFilterGeometric::resizeCanvas(vipFrameYUV444& img, unsigned int dimX, unsigned int dimY, unsigned char& valY, unsigned char& valU, unsigned char& valV)
 {
	useBufferYUV444(dimX, dimY);

	return VIPRET_NOT_IMPLEMENTED;
 }

VIPRESULT vipFilterGeometric::resizeCanvas(vipFrameRGB24& img, unsigned int dimX, unsigned int dimY, PixelRGB24 background)
 {
	useBufferRGB(dimX, dimY);

	PixelRGB24 bgRGB24((unsigned char)background[0], (unsigned char)background[1], (unsigned char)background[2] );

	for ( unsigned int i=0; i < dimX * dimY; i++ )
		bufferRGB->data[i] = bgRGB24;

	for ( unsigned int y=0; y < img.height; y++ ) // single pixel copy routine
	  for ( unsigned int x=0; x < img.width; x++ )
		bufferRGB->data[y*bufferRGB->width+x] = img.data[ y * img.width + x ];

	return VIPRET_OK;
 }

VIPRESULT vipFilterGeometric::resizeCanvas(vipFrameT<unsigned char>& img, unsigned int dimX, unsigned int dimY, unsigned char& val1, unsigned char& val2, unsigned char& val3)
 {
	useBufferTuC(dimX, dimY, img.profile);

	return VIPRET_NOT_IMPLEMENTED;
 }

////////////////////////////////////////////////////////////////////////////////////

VIPRESULT vipFilterGeometric::rotate90(vipFrameYUV420& img)
 {
	INFO("VIPRESULT vipFilterGeometric::rotate90(vipFrameYUV420& img)")

	useBufferYUV(img.height, img.width);

	return VIPRET_NOT_IMPLEMENTED;
 }

VIPRESULT vipFilterGeometric::rotate90(vipFrameYUV444& img)
 {
	INFO("VIPRESULT vipFilterGeometric::rotate90(vipFrameYUV444& img)")

	useBufferYUV444(img.height, img.width);

	return VIPRET_NOT_IMPLEMENTED;
 }

VIPRESULT vipFilterGeometric::rotate90(vipFrameRGB24& img)
 {
	INFO("VIPRESULT vipFilterGeometric::rotate90(vipFrameRGB24& img)")

	useBufferRGB(img.height, img.width);

	for ( unsigned int y=0; y < bufferRGB->height; y++ ) // single pixel copy routine
	  for ( unsigned int x=0; x < bufferRGB->width; x++ )
		bufferRGB->data[(bufferRGB->width-1-x)*bufferRGB->height+y] = img.data[x*img.width + y];

		/*	 y,w_rect-1-x
0,0 > width-1, 0
1,0 > width-1, 1

i,0 > width-1, i

x,y > width-1-y, x



  int w_rect=i.get_dimx();
  int h_rect=i.get_dimy();
  imt=new image(h_rect,w_rect,i.get_bpp(),1);
  for (y=0;y<h_rect;y++)
    for (x=0;x<w_rect;x++)
      imt->put_GL(h_rect-1-y,x,i.get_GL(x,y));


	//data[0] -> rgb [newwidth-1];
	//data[1] -> rgb [2*newwidth-1];
	//data[i] > rgb[width*i-1]
	for ( unsigned int i=0; i< width * height; i++ )


		rgb[i] = img.data[   width * height-1  +i   ];


	{
		rgb [width*height-1] = img.data[width-1];
	}
  */
	return VIPRET_OK;
 }

VIPRESULT vipFilterGeometric::rotate90(vipFrameT<unsigned char>& img)
 {
	INFO("VIPRESULT vipFilterGeometric::rotate90(vipFrameT<unsigned char>& img)")

	useBufferTuC(img.height, img.width, img.profile);

	return VIPRET_NOT_IMPLEMENTED;
 }

////////////////////////////////////////////////////////////////////////////////////

VIPRESULT vipFilterGeometric::rotate180(vipFrameYUV420& img)
 {
	INFO("VIPRESULT vipFilterGeometric::rotate180(vipFrameYUV420& img)")

	useBufferYUV(img.height, img.width);

	return VIPRET_NOT_IMPLEMENTED;
 }

VIPRESULT vipFilterGeometric::rotate180(vipFrameYUV444& img)
 {
	INFO("VIPRESULT vipFilterGeometric::rotate180(vipFrameYUV444& img)")

	useBufferYUV444(img.height, img.width);

	return VIPRET_NOT_IMPLEMENTED;
 }

VIPRESULT vipFilterGeometric::rotate180(vipFrameRGB24& img)
 {
	INFO("VIPRESULT vipFilterGeometric::rotate180(vipFrameRGB24& img)")

	useBufferRGB(img.width, img.height);

	for (unsigned int i=0; i < bufferRGB->width*bufferRGB->height; i++)      // reverse array
		bufferRGB->data[i] = img.data[img.width*img.height-1-i];

	return VIPRET_OK;
 }

VIPRESULT vipFilterGeometric::rotate180(vipFrameT<unsigned char>& img)
 {
	INFO("VIPRESULT vipFilterGeometric::rotate180(vipFrameT<unsigned char>& img)")

	useBufferTuC(img.height, img.width, img.profile);

	return VIPRET_NOT_IMPLEMENTED;
 }
////////////////////////////////////////////////////////////////////////////////////

VIPRESULT vipFilterGeometric::rotate270(vipFrameYUV420& img)
 {
	INFO("VIPRESULT vipFilterGeometric::rotate270(vipFrameYUV420& img)")

	useBufferYUV(img.height, img.width);

	return VIPRET_NOT_IMPLEMENTED;
 }

VIPRESULT vipFilterGeometric::rotate270(vipFrameYUV444& img)
 {
	INFO("VIPRESULT vipFilterGeometric::rotate270(vipFrameYUV444& img)")

	useBufferYUV444(img.height, img.width);

	return VIPRET_NOT_IMPLEMENTED;
 }

VIPRESULT vipFilterGeometric::rotate270(vipFrameRGB24& img)
 {
	INFO("VIPRESULT vipFilterGeometric::rotate270(vipFrameCach24e& img)")

	useBufferRGB(img.height, img.width);

	for ( unsigned int y=0; y < bufferRGB->height; y++ ) // single pixel copy routine
	  for ( unsigned int x=0; x < bufferRGB->width; x++ )
		bufferRGB->data[(bufferRGB->height-1-y)*bufferRGB->width+x] = img.data[x*img.width + y];

	return VIPRET_OK;
 }

VIPRESULT vipFilterGeometric::rotate270(vipFrameT<unsigned char>& img)
 {
	INFO("VIPRESULT vipFilterGeometric::rotate270(vipFrameT<unsigned char>& img)")

	useBufferTuC(img.height, img.width, img.profile);

	return VIPRET_NOT_IMPLEMENTED;
 }
////////////////////////////////////////////////////////////////////////////////////

VIPRESULT vipFilterGeometric::rotate(vipFrameYUV420& img, float alpha)
 {
	unsigned int ex,ey;
	float ox,oy;
	float dx=(float) img.width;
	float dy=(float) img.height;
	float x1,x2,x3,x4,y1,y2,y3,y4;
	float xmin,xmax,ymin,ymax;
	//conversione alpha da gradi in radianti
	alpha*=(float)3.141592654/180;
	//calcolo la posizione degli angoli dell'immagine una volta ruotata
	x1=0.;
	x2=dx*cos(alpha);
	x3=dx*cos(alpha)-dy*sin(alpha);
	x4=-dy*sin(alpha);
	y1=0.;
	y2=dx*sin(alpha);
	y3=dy*cos(alpha)+dx*sin(alpha);
	y4=dy*cos(alpha);
	//ricerco quindi gli estremi per calcolare il rettangolo che conterrà la mia immagine ruotata
	xmin=x1;
	if (x2<xmin) xmin=x2;
	if (x3<xmin) xmin=x3;
	if (x4<xmin) xmin=x4;
	xmax=x1;
	if (x2>xmax) xmax=x2;
	if (x3>xmax) xmax=x3;
	if (x4>xmax) xmax=x4;
	ymin=y1;
	if (y2<ymin) ymin=y2;
	if (y3<ymin) ymin=y3;
	if (y4<ymin) ymin=y4;
	ymax=y1;
	if (y2>ymax) ymax=y2;
	if (y3>ymax) ymax=y3;
	if (y4>ymax) ymax=y4;
	//calcolo la dimensione della nuova immagine
	ex=(int)(xmax-xmin)+1;
	ey=(int)(ymax-ymin)+1;
	//calcolo il viptore di spostamento che dovrò applicare all'immagine originale ruotata
	//per farla stare nella nuova
	ox=xmin-x1;
	oy=ymin-y1;
	//istanzio l'immagine

	useBufferYUV(ex, ey);


	return VIPRET_NOT_IMPLEMENTED;
 }

VIPRESULT vipFilterGeometric::rotate(vipFrameYUV444& img, float alpha)
 {
	unsigned int ex,ey;
	float ox,oy;
	float dx=(float) img.width;
	float dy=(float) img.height;
	float x1,x2,x3,x4,y1,y2,y3,y4;
	float xmin,xmax,ymin,ymax;
	//conversione alpha da gradi in radianti
	alpha*=(float)3.141592654/180;
	//calcolo la posizione degli angoli dell'immagine una volta ruotata
	x1=0.;
	x2=dx*cos(alpha);
	x3=dx*cos(alpha)-dy*sin(alpha);
	x4=-dy*sin(alpha);
	y1=0.;
	y2=dx*sin(alpha);
	y3=dy*cos(alpha)+dx*sin(alpha);
	y4=dy*cos(alpha);
	//ricerco quindi gli estremi per calcolare il rettangolo che conterrˆ la mia immagine ruotata
	xmin=x1;
	if (x2<xmin) xmin=x2;
	if (x3<xmin) xmin=x3;
	if (x4<xmin) xmin=x4;
	xmax=x1;
	if (x2>xmax) xmax=x2;
	if (x3>xmax) xmax=x3;
	if (x4>xmax) xmax=x4;
	ymin=y1;
	if (y2<ymin) ymin=y2;
	if (y3<ymin) ymin=y3;
	if (y4<ymin) ymin=y4;
	ymax=y1;
	if (y2>ymax) ymax=y2;
	if (y3>ymax) ymax=y3;
	if (y4>ymax) ymax=y4;
	//calcolo la dimensione della nuova immagine
	ex=(int)(xmax-xmin)+1;
	ey=(int)(ymax-ymin)+1;
	//calcolo il viptore di spostamento che dovrò applicare all'immagine originale ruotata
	//per farla stare nella nuova
	ox=xmin-x1;
	oy=ymin-y1;
	//istanzio l'immagine

	useBufferYUV444(ex, ey);


	return VIPRET_NOT_IMPLEMENTED;
 }

VIPRESULT vipFilterGeometric::rotate(vipFrameRGB24& img, float alpha)
 {
	unsigned int ex,ey;
	float ox,oy;
	float dx=(float) img.width;
	float dy=(float) img.height;
	float x1,x2,x3,x4,y1,y2,y3,y4;
	float xmin,xmax,ymin,ymax;
	//conversione alpha da gradi in radianti
	alpha*=(float)3.141592654/180;
	//calcolo la posizione degli angoli dell'immagine una volta ruotata
	x1=0.;
	x2=dx*cos(alpha);
	x3=dx*cos(alpha)-dy*sin(alpha);
	x4=-dy*sin(alpha);
	y1=0.;
	y2=dx*sin(alpha);
	y3=dy*cos(alpha)+dx*sin(alpha);
	y4=dy*cos(alpha);
	//ricerco quindi gli estremi per calcolare il rettangolo che conterrà la mia immagine ruotata
	xmin=x1;
	if (x2<xmin) xmin=x2;
	if (x3<xmin) xmin=x3;
	if (x4<xmin) xmin=x4;
	xmax=x1;
	if (x2>xmax) xmax=x2;
	if (x3>xmax) xmax=x3;
	if (x4>xmax) xmax=x4;
	ymin=y1;
	if (y2<ymin) ymin=y2;
	if (y3<ymin) ymin=y3;
	if (y4<ymin) ymin=y4;
	ymax=y1;
	if (y2>ymax) ymax=y2;
	if (y3>ymax) ymax=y3;
	if (y4>ymax) ymax=y4;
	//calcolo la dimensione della nuova immagine
	ex=(int)(xmax-xmin)+1;
	ey=(int)(ymax-ymin)+1;
	//calcolo il viptore di spostamento che dovrò applicare all'immagine originale ruotata
	//per farla stare nella nuova
	ox=xmin-x1;
	oy=ymin-y1;
	//istanzio l'immagine

	useBufferRGB(ex, ey);

	//precalcolo il seno e coseno
	float cc=cos(-alpha);
	float ss=sin(-alpha);

	for ( unsigned int y=0; y < ey; y++ ) // single pixel copy routine
	  for ( unsigned int x=0; x < ex; x++ )
			bufferRGB->data[y*bufferRGB->width+x] = img.data[(int)( (( (float)(y+oy)*cc+(float)(x+ox)*ss) * img.width) + ((float)(x+ox)*cc-(float)(y+oy)*ss) )];

	return VIPRET_OK;
 }

VIPRESULT vipFilterGeometric::rotate(vipFrameT<unsigned char>& img, float alpha)
 {
	unsigned int ex,ey;
	float ox,oy;
	float dx=(float) img.width;
	float dy=(float) img.height;
	float x1,x2,x3,x4,y1,y2,y3,y4;
	float xmin,xmax,ymin,ymax;
	//conversione alpha da gradi in radianti
	alpha*=(float)3.141592654/180;
	//calcolo la posizione degli angoli dell'immagine una volta ruotata
	x1=0.;
	x2=dx*cos(alpha);
	x3=dx*cos(alpha)-dy*sin(alpha);
	x4=-dy*sin(alpha);
	y1=0.;
	y2=dx*sin(alpha);
	y3=dy*cos(alpha)+dx*sin(alpha);
	y4=dy*cos(alpha);
	//ricerco quindi gli estremi per calcolare il rettangolo che conterrà la mia immagine ruotata
	xmin=x1;
	if (x2<xmin) xmin=x2;
	if (x3<xmin) xmin=x3;
	if (x4<xmin) xmin=x4;
	xmax=x1;
	if (x2>xmax) xmax=x2;
	if (x3>xmax) xmax=x3;
	if (x4>xmax) xmax=x4;
	ymin=y1;
	if (y2<ymin) ymin=y2;
	if (y3<ymin) ymin=y3;
	if (y4<ymin) ymin=y4;
	ymax=y1;
	if (y2>ymax) ymax=y2;
	if (y3>ymax) ymax=y3;
	if (y4>ymax) ymax=y4;
	//calcolo la dimensione della nuova immagine
	ex=(int)(xmax-xmin)+1;
	ey=(int)(ymax-ymin)+1;
	//calcolo il viptore di spostamento che dovrò applicare all'immagine originale ruotata
	//per farla stare nella nuova
	ox=xmin-x1;
	oy=ymin-y1;
	//istanzio l'immagine

	useBufferTuC(ex, ey, img.profile);


	return VIPRET_NOT_IMPLEMENTED;
 }

////////////////////////////////////////////////////////////////////////////////////

VIPRESULT vipFilterGeometric::flipHorizontal(vipFrameYUV420& img)
 {
	INFO("VIPRESULT vipFilterGeometric::flipHorizontal(vipFrameYUV420& img)")

	useBufferYUV(img.width, img.height);

	return VIPRET_NOT_IMPLEMENTED;
 }

VIPRESULT vipFilterGeometric::flipHorizontal(vipFrameYUV444& img)
 {
	INFO("VIPRESULT vipFilterGeometric::flipHorizontal(vipFrameYUV444& img)")

	useBufferYUV444(img.width, img.height);

	return VIPRET_NOT_IMPLEMENTED;
 }

VIPRESULT vipFilterGeometric::flipHorizontal(vipFrameRGB24& img)
 {
	INFO("VIPRESULT vipFilterGeometric::flipHorizontal(vipFrameRGB24& img)")

	useBufferRGB(img.width, img.height);

	for ( unsigned int y=0; y < bufferRGB->height; y++ ) // single pixel copy routine
	 for ( unsigned int x=0; x < bufferRGB->width; x++ )
		bufferRGB->data[x+y*bufferRGB->width] = img.data[y*img.width + (img.width-1)-x];

	return VIPRET_OK;
 }

VIPRESULT vipFilterGeometric::flipHorizontal(vipFrameT<unsigned char>& img)
 {
	INFO("VIPRESULT vipFilterGeometric::flipHorizontal(vipFrameT<unsigned char>& img)")

	useBufferTuC(img.width, img.height, img.profile);

	return VIPRET_NOT_IMPLEMENTED;
 }

////////////////////////////////////////////////////////////////////////////////////

VIPRESULT vipFilterGeometric::flipVertical(vipFrameYUV420& img)
 {
	INFO("VIPRESULT vipFilterGeometric::flipVertical(vipFrameYUV420& img)")

	useBufferYUV(img.width, img.height);

	return VIPRET_NOT_IMPLEMENTED;
 }

VIPRESULT vipFilterGeometric::flipVertical(vipFrameYUV444& img)
 {
	INFO("VIPRESULT vipFilterGeometric::flipVertical(vipFrameYUV444& img)")

	useBufferYUV444(img.width, img.height);

	return VIPRET_NOT_IMPLEMENTED;
 }

VIPRESULT vipFilterGeometric::flipVertical(vipFrameRGB24& img)
 {
	INFO("VIPRESULT vipFilterGeometric::flipVertical(vipFrameRGB24& img)")

	useBufferRGB(img.width, img.height);

	for ( unsigned int i=0; i < bufferRGB->height; i++ ) // optimized, copy each row
		memcpy( &bufferRGB->data[i*bufferRGB->width], &img.data[(bufferRGB->height-i-1)*bufferRGB->width], bufferRGB->width * sizeof(PixelRGB24) );


	return VIPRET_OK;
 }

VIPRESULT vipFilterGeometric::flipVertical(vipFrameT<unsigned char>& img)
 {
	INFO("VIPRESULT vipFilterGeometric::flipVertical(vipFrameT<unsigned char>& img)")

	useBufferTuC(img.width, img.height, img.profile);

	return VIPRET_NOT_IMPLEMENTED;
 }

////////////////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////////////////////






////////////////////////////////////////////////////////////////////////////////////////////////





vipFilterGeometricParameters::vipFilterGeometricParameters(RUNMODE mode) : vipFilterParameters()
 {
	runMode = mode;
 }

void vipFilterGeometricParameters::reset()
 {
	runMode = vipFilterGeometricParameters::DO_NOTHING;
	par_Rotation = 0;
	par_ResizeWidth = 0;
	par_ResizeHeight = 0;
	par_forzeSize = false;
	currentBuffer = vipFilterParameters::NONE;
 }

int vipFilterGeometricParameters::saveToStreamXML(FILE *fp)
 {

	if ( fp == NULL )
		return VIPRET_PARAM_ERR;

	if( fprintf(fp, "<vipFilterGeometricParameters>\n") == EOF )
		return VIPRET_INTERNAL_ERR;

	if ( fprintf(fp, "  <runmode value=\"%i\" />\n", (int)runMode) == EOF)
		return VIPRET_INTERNAL_ERR;

	if ( fprintf(fp, "  <rotation value=\"%f\" />\n", par_Rotation) == EOF)
		return VIPRET_INTERNAL_ERR;

	if ( fprintf(fp, "  <resize width=\"%u\" height=\"%u\" />\n", par_ResizeWidth, par_ResizeHeight) == EOF)
		return VIPRET_INTERNAL_ERR;

	if ( fprintf(fp, "  <forzeSize value=\"%u\" />\n", (int)par_forzeSize) == EOF)
		return VIPRET_INTERNAL_ERR;

	if ( fprintf(fp, "  <internalBufferType value=\"%u\" />\n", (int)currentBuffer) == EOF)
		return VIPRET_INTERNAL_ERR;

	if( fprintf(fp, "</vipFilterGeometricParameters>\n") == EOF )
		return VIPRET_INTERNAL_ERR;

	return VIPRET_OK;
 }


int vipFilterGeometricParameters::loadFromStreamXML(FILE *fp)
 {
	if ( fscanf(fp, "<vipFilterGeometricParameters>\n") == EOF )
		throw "error in XML file, unable to import data.";

	int runTmp = 0;
	if ( fscanf(fp, "  <runmode value=\"%i\" />\n", &runTmp) == EOF )
		throw "error in XML file, unable to import data.";
	else
		runMode = (RUNMODE)runTmp;

	if ( fscanf(fp, "  <rotation value=\"%f\" />\n", &par_Rotation) == EOF )
		throw "error in XML file, unable to import data.";

	if ( fscanf(fp, "  <resize width=\"%u\" height=\"%u\" />\n", &par_ResizeWidth, &par_ResizeHeight) == EOF )
		throw "error in XML file, unable to import data.";

	int boolTmp = 0;
	if ( fscanf(fp, "  <forzeSize value=\"%u\" />\n", &boolTmp) == EOF )
		throw "error in XML file, unable to import data.";

	if (boolTmp == 0)
		par_forzeSize = false;
	else
		par_forzeSize = true;

	int cB = (int)currentBuffer;
	if ( fscanf(fp, "  <internalBufferType value=\"%u\" />\n", &cB) == EOF )
		throw "error in XML file, unable to import data.";
	currentBuffer = (BUFFER_TYPE)cB;

	return VIPRET_OK;
 }




