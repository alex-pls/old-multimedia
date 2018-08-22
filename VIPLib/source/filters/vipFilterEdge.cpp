/** @file vipFilterEdge.cpp
 *
 * File containing methods for the 'vipFilterEdge' class.
 * The header for this class can be found in vipFilterEdge.h, check that file
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



#include "vipFilterEdge.h"
#include "../../source/math/vipMatrix.h"
#include <math.h>

const double M_PI = 3.141292;


/**
 * @brief  Default constructor, initialize parameters and superclasses.
 * @param[in] initParams parameters for this module or NULL for defaults.
 */
vipFilterEdge::vipFilterEdge(vipFilterEdgeParameters* initParams) : vipFilter()
 {
	INFO("vipFilterEdge::vipFilterEdge(..* initParams) : vipFilter() [CONTRUCTOR]")


	myParams = NULL;
	setParameters(initParams);

	setName("Sobel Filter");
	setDescription("Edge Extraction Through Sobel Operator");
	setVersion(0.1);

	reset();
 }

/**
 * @brief Default destructor, free buffer.
 */
vipFilterEdge::~vipFilterEdge()
 {
	INFO("vipFilterEdge::~vipFilterEdge() [DESTRUCTOR]")

	if (myParams != NULL)
		delete myParams;


 }


/**
 * @brief  Reset buffers and parameters.
 *
 * @return VIPRET_OK
 */
VIPRESULT vipFilterEdge::reset()
 {
	INFO("int vipFilterEdge::reset() [SET DEFAULT PARAMETERS]")


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
 * @param[in] initParams Instance of vipFilterEdgeParameters or NULL,
 *                       NULL argument make function to create a new
 *                       instance with default parameters.
 *
 * @return VIPRET_OK
 */
VIPRESULT vipFilterEdge::setParameters (vipFilterEdgeParameters* initParams)
 {

	if (initParams != NULL && myParams == initParams)
		return VIPRET_PARAM_ERR;

	if ( initParams == NULL )
	 {
		if ( myParams != NULL )
			reset();
		else
			myParams = new vipFilterEdgeParameters();
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
 * @param[in] img VIPLib Frame YUV420 to be processed.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if runmode is unknown,
 *         VIPRET_NOT_IMPLEMENTED if this function is not enabled yet, VIPRET_INTERNAL_ERR else.
 *
 * @note  Input operator (<<) call directly this function.
 * @see   operator << (vipFrameYUV420&)
 */
VIPRESULT vipFilterEdge::importFrom(vipFrameYUV420& img)
 {
	DEBUGMSG("int vipFilterEdge::importFrom(vipFrameYUV420& img) [reading data]", myParams->runMode)


	switch ( myParams->runMode )
	 {
	 case vipFilterEdgeParameters::DO_NOTHING:
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
	 case vipFilterEdgeParameters::DO_SOBEL:
			useBufferYUV(img.width, img.height);
			return VIPRET_NOT_IMPLEMENTED;

	 default:
		  return VIPRET_PARAM_ERR;
 	 }

	return VIPRET_NOT_IMPLEMENTED;
 }


/**
 * @brief Process the frame with current settings and store in buffer.
 *
 * @param[in] img VIPLib Frame RGB24 to be processed.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if runmode is unknown,
 *         VIPRET_NOT_IMPLEMENTED if this function is not enabled yet, VIPRET_INTERNAL_ERR else.
 *
 * @note  Input operator (<<) call directly this function.
 * @see   operator << (vipFrameRGB24&)
 */
VIPRESULT vipFilterEdge::importFrom(vipFrameRGB24& img)
 {
	DEBUGMSG("int vipFilterEdge::importFrom(vipFrameRGB24& img) [reading data]", myParams->runMode)


	switch ( myParams->runMode )
	 {
	 case vipFilterEdgeParameters::DO_NOTHING:
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

	 case vipFilterEdgeParameters::DO_SOBEL:
				useBufferRGB(img.width, img.height);
				return applySobel(*bufferRGB, img, myParams->threshold_sobel);

	 case vipFilterEdgeParameters::DO_CANNY:
		 return VIPRET_NOT_IMPLEMENTED;

	 default:
		  return VIPRET_PARAM_ERR;
	 }

	return VIPRET_NOT_IMPLEMENTED;
 }



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
VIPRESULT vipFilterEdge::importFrom(vipFrameT<unsigned char>& img)
 {
	DEBUGMSG("int vipFilterEdge::importFrom(vipFrameT<unsigned char>& img) [reading data]", myParams->runMode)


	switch ( myParams->runMode )
	 {
	 case vipFilterEdgeParameters::DO_NOTHING:
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

	 case vipFilterEdgeParameters::DO_SOBEL:
			useBufferTuC(img.width, img.height, img.profile);
			return applySobel( *bufferTuC, img, myParams->threshold_sobel );

	 case vipFilterEdgeParameters::DO_CANNY:
			useBufferTuC(img.width, img.height, img.profile);
			return applyCanny( *bufferTuC, img, myParams->threshold_canny_hi, myParams->threshold_canny_lo );

	 default:
		  return VIPRET_PARAM_ERR;
	 }


	return VIPRET_NOT_IMPLEMENTED;
 }

// added by Marco Verza on 2, july 2008 after adding full support for vipFrame444
VIPRESULT vipFilterEdge::importFrom(vipFrameYUV444 &img)
{
	return VIPRET_NOT_IMPLEMENTED;
}

///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////


VIPRESULT vipFilterEdge::applySobel(vipFrameYUV420& dest, vipFrameYUV420& source, int threshold)
 {
	return VIPRET_NOT_IMPLEMENTED;
 }


VIPRESULT vipFilterEdge::applySobel(vipFrameT<unsigned char>& dest, vipFrameT<unsigned char>& source, int threshold)
 {
	 // Marco Verza implementation for mono frames. 
	 // Using integer arithmetic to perform lightning-fast filtering, using separable kernel...
	 // Actually, since the input frame is defined as 1-dimensional vector, many multiplies will be needed to read/set pixels on it, i.e. y*width+x
	 // Only some multiplications are avoided. So it's probably kinda useless. Use at your own risk! :)

	 unsigned int x,y;
	 int gx,gy;
	 unsigned char res;

	 for( x=0; x<source.width; x++ )
	 {
		 for( y=0; y<source.height; y++ )
		 {
			 // Edges of the frame: undefined, 0
			 if( x==0 || y==0 || x==source.width-1 || y==source.height-1 )
				 dest.data[y*source.width+x] = 0;
			 else
			 {
				 // Not on the frame edge, filter it
				 gx =	( (int) source.data[(y-1) * source.width + (x-1)]		)	-
						( (int) source.data[(y-1) * source.width + (x+1)]		)	+
						( (int) source.data[ y    * source.width + (x-1)] << 1	)	-
						( (int) source.data[ y    * source.width + (x+1)] << 1	)	+
						( (int) source.data[(y+1) * source.width + (x-1)]		)	-
						( (int) source.data[(y+1) * source.width + (x+1)]		)	;
				 
				 gy = -	((int) source.data[(y-1) * source.width + (x-1)]		)	-
						( (int)	source.data[(y-1) * source.width +  x   ] << 2	)	-
						( (int)	source.data[(y-1) * source.width + (x+1)]		)	+

						( (int)	source.data[(y+1) * source.width + (x-1)]		)	+
						( (int)	source.data[(y+1) * source.width +  x   ] << 2	)	+
						( (int)	source.data[(y+1) * source.width + (x+1)]		)	;

				 res = sqrt( (float)((gx*gx) + (gy*gy)) );
				 if( res > 255 )
					 res = 255;

				 //// Set output value:
				 dest.data[y*source.width+x] = (unsigned char) ( res<threshold ? 0 : 255 );	// threshold-binarized output
				 //dest.data[y*source.width+x] = (unsigned char) ( res<threshold ? 0 : res );	// thresholded but not binarized output


			 }
		 } // for y
	 }	// for x


	return VIPRET_OK;
 }


VIPRESULT vipFilterEdge::applySobel(vipFrameRGB24& dest, vipFrameRGB24& source, int threshold)
 {

	 vipMatrix<long> tmph(source.width * source.height, 3);
	 vipMatrix<long> tmpv(source.width * source.height, 3);
	 vipMatrix<long> tmptot(source.width * source.height, 3);

	 long h=0;
	 long v=0;
	 unsigned int x,y;
	 long r, g, b;
	 int kernelh[9];
	 int kernelv[9];
	 kernelv[0]=1; kernelv[1]=0; kernelv[2]=-1;
	 kernelv[3]=2; kernelv[4]=0; kernelv[5]=-2;
	 kernelv[6]=1; kernelv[7]=0; kernelv[8]=-1;

	 kernelh[0]=-1; kernelh[1]=-2; kernelh[2]=-1;
	 kernelh[3]= 0; kernelh[4]= 0; kernelh[5]= 0;
	 kernelh[6]= 1; kernelh[7]= 2; kernelh[8]= 1;

	 //---- passo la maschera per i contorni orizzontali e verticali
	 for(x=0; x < source.width; x++)
	 {
	   for(y=0; y < source.height; y++)
		{
			if ( x && y && (x != source.width-1) && (y != source.height-1)) //3x3 matrix!
			 {
			   for(int ch=0; ch < 3; ch++)
				{
					h = (long) (	(long) source.data[(y-1) * source.width + (x-1)][ch] * kernelh[0] +
									(long) source.data[(y-1) * source.width +  x   ][ch] * kernelh[1] +
									(long) source.data[(y-1) * source.width + (x+1)][ch] * kernelh[2] +
									(long) source.data[ y    * source.width + (x-1)][ch] * kernelh[3] +
									(long) source.data[ y    * source.width +  x   ][ch] * kernelh[4] +
									(long) source.data[ y    * source.width + (x+1)][ch] * kernelh[5] +
									(long) source.data[(y+1) * source.width + (x-1)][ch] * kernelh[6] +
									(long) source.data[(y+1) * source.width +  x   ][ch] * kernelh[7] +
									(long) source.data[(y+1) * source.width + (x+1)][ch] * kernelh[8]	);
					v = (long) (	(long) source.data[(y-1) * source.width + (x-1)][ch] * kernelv[0] +
									(long) source.data[(y-1) * source.width +  x   ][ch] * kernelv[1] +
									(long) source.data[(y-1) * source.width + (x+1)][ch] * kernelv[2] +
									(long) source.data[ y    * source.width + (x-1)][ch] * kernelv[3] +
									(long) source.data[ y    * source.width +  x   ][ch] * kernelv[4] +
									(long) source.data[ y    * source.width + (x+1)][ch] * kernelv[5] +
									(long) source.data[(y+1) * source.width + (x-1)][ch] * kernelv[6] +
									(long) source.data[(y+1) * source.width +  x   ][ch] * kernelv[7] +
									(long) source.data[(y+1) * source.width + (x+1)][ch] * kernelv[8]	);

					if ( h )
						h = (long) (h/9);		//normalization
//						h /= 9;//normalization


					if ( v )
						v = (long) (v/9);		//normalization
//						v /= 9;//normalization

					tmph.setValue(y * source.width + x, ch, h);
					tmpv.setValue(y * source.width + x, ch, v);	// ERROR=? tmph.setValue(y * source.width + x, ch, v);
				 }
			 }
			else
			 {
				r=(long)source.data[y * source.width + x][0];
				g=(long)source.data[y * source.width + x][1];
				b=(long)source.data[y * source.width + x][2];

				tmph.setValue(y * source.width + x, 0, r);
				tmph.setValue(y * source.width + x, 1, g);
				tmph.setValue(y * source.width + x, 2, b);

				r=(long)source.data[y * source.width + x][0];
				g=(long)source.data[y * source.width + x][1];
				b=(long)source.data[y * source.width + x][2];

				tmpv.setValue(y * source.width + x, 0, r);
				tmpv.setValue(y * source.width + x, 1, g);
				tmpv.setValue(y * source.width + x, 2, b);

			 }

	   }
	 }


for(x=0; x < source.width; x++){
	   for(y=0; y < source.height; y++)
		{

			long rh=(long)(tmph.getValue(y * source.width + x, 0));
			long gh=(long)(tmph.getValue(y * source.width + x, 1));
			long bh=(long)(tmph.getValue(y * source.width + x, 2));

			long rv=(long)(tmpv.getValue(y * source.width + x, 0));
			long gv=(long)(tmpv.getValue(y * source.width + x, 1));
			long bv=(long)(tmpv.getValue(y * source.width + x, 2));

			double res= sqrt(pow(rh,(long double)2)+pow(rv,(long double)2));

			if(res<threshold)
				dest.data[y * source.width + x][0]=0;
			else
				dest.data[y * source.width + x][0]=255;

			res= sqrt(pow(gh,(long double)2)+pow(gv,(long double)2));
			if(res<threshold)
				dest.data[y * source.width + x][1]=0;
			else
				dest.data[y * source.width + x][1]=255;

			res= sqrt(pow(bh,(long double)2)+pow(bv,(long double)2));
			if(res<threshold)
				dest.data[y * source.width + x][2]=0;
			else
				dest.data[y * source.width + x][2]=255;

		}
 }

	return VIPRET_OK;

 }



///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////








vipFilterEdgeParameters::vipFilterEdgeParameters()
 {
	reset();
 }

void vipFilterEdgeParameters::reset()
 {

	runMode = vipFilterEdgeParameters::DO_NOTHING;
	threshold_sobel = VIPFILTERSOBEL_DEFAULT_THRESHOLD;
	threshold_canny_hi = VIPFILTERCANNY_DEFAULT_THRESHOLD_HI;
	threshold_canny_lo = VIPFILTERCANNY_DEFAULT_THRESHOLD_LO;

	currentBuffer = vipFilterParameters::NONE;
 }

int vipFilterEdgeParameters::saveToStreamXML(FILE *fp)
 {

	if ( fp == NULL )
		return VIPRET_PARAM_ERR;

	if( fprintf(fp, "<vipFilterEdgeParameters>\n") == EOF )
		return VIPRET_INTERNAL_ERR;

	// add your variables here


	if ( fprintf(fp, "  <runmode value=\"%i\" />\n", (int)runMode) == EOF)
		return VIPRET_INTERNAL_ERR;

	if ( fprintf(fp, "  <threshold value=\"%i\" />\n", threshold_sobel) == EOF)
		return VIPRET_INTERNAL_ERR;

	if ( fprintf(fp, "  <internalBufferType value=\"%u\" />\n", (int)currentBuffer) == EOF)
		return VIPRET_INTERNAL_ERR;


	if( fprintf(fp, "</vipFilterEdgeParameters>\n") == EOF )
		return VIPRET_INTERNAL_ERR;

	return VIPRET_OK;
 }


int vipFilterEdgeParameters::loadFromStreamXML(FILE *fp)
 {
	if ( fscanf(fp, "<vipFilterEdgeParameters>\n") == EOF )
		throw "error in XML file, unable to import data.";

	// add your variables here



	int runTmp = 0;
	if ( fscanf(fp, "  <runmode value=\"%i\" />\n", &runTmp) == EOF )
		throw "error in XML file, unable to import data.";
	else
		runMode = (RUNMODE)runTmp;

	if ( fscanf(fp, "  <threshold value=\"%i\" />\n", &threshold_sobel) == EOF )
		throw "error in XML file, unable to import data.";


	int cB = (int)currentBuffer;
	if ( fscanf(fp, "  <internalBufferType value=\"%u\" />\n", &cB) == EOF )
		throw "error in XML file, unable to import data.";
	currentBuffer = (BUFFER_TYPE)cB;



	return VIPRET_OK;
 }




///////// Canny Edge implementation // Ported by Marco Verza (2008) from Carlo Facci & Paolo Ceresato original code (2003)
VIPRESULT vipFilterEdge::applyCanny(vipFrameT<unsigned char>& dest, vipFrameT<unsigned char>& source, int up_threshold, int low_threshold)
{
	if( up_threshold == 0 )
		up_threshold = 120;
	if( low_threshold == 0 )
		low_threshold = 40;

	int w_rect = source.width;
	int h_rect = source.height;
	vipFrameT<unsigned char> gaussian_image, imGX, imGY;
	gaussian_image.reAllocCanvas( source.width, source.height );
	imGX.reAllocCanvas( source.width, source.height );
	imGY.reAllocCanvas( source.width, source.height );

	float kernelv[3][3];
	float kernelh[3][3];
	 kernelv[0][0]=1; kernelv[1][0]=0; kernelv[2][0]=-1;
	 kernelv[0][1]=2; kernelv[1][1]=0; kernelv[2][1]=-2;
	 kernelv[0][2]=1; kernelv[1][2]=0; kernelv[2][2]=-1;

	 kernelh[0][0]=-1; kernelh[1][0]=-2; kernelh[2][0]=-1;
	 kernelh[0][1]= 0; kernelh[1][1]= 0; kernelh[2][1]= 0;
	 kernelh[0][2]= 1; kernelh[1][2]= 2; kernelh[2][2]= 1;


    //image *gaussian_image;	// qui metto l'immagine a cui e' stato applicato il passa-basso gaussiano
    //image *edge_image;	// qui metto l'immagine con i contorni estratti che poi restituira'
    int P1, P2, P3, P4, P5, P6, P7, P8;	// 8 direzioni al contorno del pixel considerato
    /*****************************************************************
    * angolo reale di direzione del contorno corrispondente all' arctg
    * del rapporto tra le due maschere di Sobel:
    * arctg (imGY/imGX)
    ******************************************************************/
    float angolo;
    /*****************************************************************
    * Puo' assumere 4 valori che corrispondono alle direzioni possibili in un'immagine partendo dal pixel considerato
    *	0 	se 	angolo<22.5° 	o 	angolo>157,5°
    *	45	se 	22,5°	<	angolo	<	67.5°
    *	90	se 	67,5°	<	angolo	<	112.5°
    *	135	se 	112,5°<	angolo	<	157.5°
    ******************************************************************/
    int direzione_contorno;
    //A seconda della direzione del contorno qui metto il valore del pixel prima e di quello dopo a quello considerato
    int pixel_prima;
    int pixel_dopo;
    int sum = 0;		// Qui memorizzo il valore del pixel, da 0 a 255
    int sumx = 0;		// Qui memorizzo il valore del pixel calcolato con la maschera di Sobel lungo X
    int sumy = 0;		// Qui memorizzo il valore del pixel calcolato con la maschera di Sobel lungo Y
    int MASK[5][5];		// maschera gaussiana per lo smoothing
    //image imGX;		// maschera di Sobel lungo X
    //image imGY;		// maschera di Sobel lungo Y
    ////dimensione dell'immagine reale lungo X e lungo Y
    //int w_rect = this->get_dimx ();
    //int h_rect = this->get_dimy ();
    //inizzializzo le immagini
    //gaussian_image = new image (w_rect, h_rect, this->get_bpp (), 1);
    //edge_image = new image (w_rect, h_rect, this->get_bpp (), 1);
    //5x5 Gaussian mask.  Ref: http://www.cee.hw.ac.uk/hipr/html/gsmooth.html
    MASK[0][0] = 2;
    MASK[0][1] = 4;
    MASK[0][2] = 5;
    MASK[0][3] = 4;
    MASK[0][4] = 2;
    MASK[1][0] = 4;
    MASK[1][1] = 9;
    MASK[1][2] = 12;
    MASK[1][3] = 9;
    MASK[1][4] = 4;
    MASK[2][0] = 5;
    MASK[2][1] = 12;
    MASK[2][2] = 15;
    MASK[2][3] = 12;
    MASK[2][4] = 5;
    MASK[3][0] = 4;
    MASK[3][1] = 9;
    MASK[3][2] = 12;
    MASK[3][3] = 9;
    MASK[3][4] = 4;
    MASK[4][0] = 2;
    MASK[4][1] = 4;
    MASK[4][2] = 5;
    MASK[4][3] = 4;
    MASK[4][4] = 2;
    // Inizzializzo le maschere di Sobel
    //imGX = sobel_h ();
    //imGY = sobel_v ();
    /**********************************************
     *	ALGORITMO MASCHERA GAUSSIANA
     **********************************************
     * Scorro su tutti i pixel dell'immagine prima in orizzontale e poi in verticale e applico il filtro
     * Gaussiano cioe' effettuo una convoluzione tra immagine e la matrice MASK
     */
    for (int x = 0; x < (w_rect); x++)
    {
        for (int y = 0; y < (h_rect); y++)
        {
            // Se mi trovo troppo vicino al bordo non considero i pixel
            // Semplicemente metto nell'immagine gaussiana il valore del pixel originale
            if (x == 0 || x == 1 || x == w_rect - 2 || x == (w_rect-1) )
				gaussian_image.setPixel(x,y, source.data[y*w_rect+x] );
                //gaussian_image->put_GL (x, y,this->get_GL (x, y));
            else if (y == 0 || y == 1 || y == h_rect - 2 || y == h_rect - 1)
				gaussian_image.setPixel(x,y, source.data[y*w_rect+x] );
                //gaussian_image->put_GL (x, y,this->get_GL (x, y));
            //Se sono sufficientemente lontano dal bordo effettuo la convoluzione
            else
            {
                for (int I = -2; I <= 2; I++)
                {
                    for (int J = -2; J <= 2; J++)
                    {
                        sum = sum +
							( source.data[x+I+(y+I)*w_rect] *(MASK[I + 2][J + 2])/ 115);
                    }
                }
            }
            //Se il valore e' al di fuori del range consentito lo metto al valore massimo o minimo
            if (sum > 255)
                sum = 255;
            else if (sum < 0)
                sum = 0;
            //metto il valore sum nell'immagine temporanea gaussian_image
			gaussian_image.data[ y*w_rect+x ] = (unsigned char) sum;
            sum = 0;	//azzero il contatore e ricomincio! :)
        }
    }

    /*******************************************************
     * FINITO ALGORITMO PER MASCHERA GAUSSIANA
     *******************************************************
     * INIZIO ALGORITMO PER MASCHERA DI SOBEL
     *******************************************************/
    sum = 0;
    sumx = 0;
    sumy = 0;
    for (int x = 0; x < (w_rect); x++)
    {
        for (int y = 0; y < (h_rect); y++)
        {
            sumx = 0;
            sumy = 0;
            //Se sono troppo vicino al bordo metto il tutto a zero
            if (x == 0 || x == w_rect-1)
                sum = 0;
            else if (y == 0 || y == h_rect-1)
                sum = 0;
            else
            {
                //La convoluzione inizia qui
                for (int X1 = -1; X1 <= 1; X1++)
                {
                    for (int X2 = -1; X2 <= 1; X2++)
                    {
						sumx = sumx + (int) (source.data[x + X1 + (y + X2)*w_rect] * kernelv[X1+1][X2+1] );
                    }
                }
                for (int Y1 = -1; Y1 <= 1; Y1++)
                {
                    for (int Y2 = -1; Y2 <= 1; Y2++)
                    {
						sumy = sumy + (int) (source.data[x + Y1 + (y + Y2)*w_rect] * kernelh[Y1+1][Y2+1] );
                        //sumy = sumy + (int) (this->get_GL (x + Y1, y + Y2) * imGY.get_px (Y1 + 1, Y2 + 1));	//*GY[Y1+1][Y2+1]);
                    }
                }
                /**********************************************************************
                * Il valore finale e' dato dalla somma del valore assoluto della convoluzione con
                * la matrice imGX e imGY, se supero i limiti metto il valore massimo o minimo
                **************************************************************************/
                sum = abs (sumx) + abs (sumy);
                if (sum > 255)
                    sum = 255;
                if (sum < 0)
                    sum = 0;
                /*******************************************
                * ASSEGNO UN'ANGOLAZIONE POSSIBILE PER IL CONTORNO
                ********************************************/
                /* Non posso dividere per zero */
                if (sumx == 0)
                {
                    if (sumy == 0)
                        angolo = 0.0;
                    else if (sumy < 0)
                    {
                        sumy = -sumy;
                        angolo = 90.0;
                    }
                    else
                        angolo = 90.0;
                }
                //Impossibile fare l' arctg di un angolo nel secondo quadrante
                else if (sumx < 0 && sumy > 0)
                {
                    sumx = -sumx;
                    angolo = 180 - ((atan((float) (sumy) /(float) (sumx))) * (180/M_PI));
                }
                //Impossibile fare l' arctg di un angolo nel terzo quadrante
                else if (sumx > 0 && sumy < 0)
                {
                    sumy = -sumy;
                    angolo = 180 -((atan((float) (sumy) /(float) (sumx))) * (180 /M_PI));
                }
                //Se siamo nel primo o nel terzo quadrante
                else
                    angolo = (atan((float) (sumy) /(float) (sumx))) * (180 /M_PI);
                //stabilisco quattro possibili direzioni
                if (angolo < 22.5)
                    direzione_contorno = 0;
                else if (angolo < 67.5)
                    direzione_contorno = 45;
                else if (angolo < 112.5)
                    direzione_contorno = 90;
                else if (angolo < 157.5)
                    direzione_contorno = 135;
                else
                    direzione_contorno = 0;
                // stabilisco i due pixel, prima e dopo a seconda dell'orientazione del gradiente
                if (direzione_contorno == 0)
                {
					pixel_prima =gaussian_image.data[x - 1 + y*w_rect];
                    pixel_dopo =gaussian_image.data[x + 1 +y*w_rect];
                }
                else if (direzione_contorno == 45)
                {
                    pixel_prima =gaussian_image.data[x - 1+ (y-1)*w_rect];
                    pixel_dopo =gaussian_image.data[x + 1 + (y+1)*w_rect];
                }
                else if (direzione_contorno == 90)
                {
                    pixel_prima =gaussian_image.data[x + (y-1)*w_rect];
                    pixel_dopo = gaussian_image.data[x+(y+1)*w_rect];
                }
                else
                {
                    pixel_prima =	gaussian_image.data[x+1+(y+1)*w_rect];
                    pixel_dopo =	gaussian_image.data[x-1+(y-1)*w_rect];
                }
                /***********************************************************************
                 * Se uno dei due pixel vicini ha un valore maggiore, cioe' e' piu' luminoso
                 * considero il pixel corrente come un punto che non fa il parte del
                 * contorno e quindi lo pongo a 0 (nero)
                 * ********************************************************************/
                if (sum < pixel_prima || sum < pixel_dopo)
                {
                    sum = 0;
                }
                else
                {
                    /********************************************************************
                    * Se il punto corrente e' il piu' luminoso dei tre lo confronto con la
                    * soglia:
                    * Se superiore alla soglia massima up_threshold e' sicuramente punto
                    * di contorno e lo metto a 255 (bianco)
                    * Se inferiore alla soglia minima low_threshold e' sicuramente un punto
                    * che NON appartiene al contorno e lo metto a 0 (nero)
                    * Se compreso tra le due soglie, lo confronto con gli otto punti al suo contorno,
                    * se uno di questo e' di edge allora anche quello che sto considerando e' edge
                        * *******************************************************************/
                    if (sum >= up_threshold)
                        sum = 255;	/* edge */
                    else if (sum < low_threshold)
                        sum = 0;	/* nonedge */
                    //Se la somma e' compresa tra le due soglie
                    else
                    {
                        //Determino il valore degli 8 pixel vicini
                        P1 = (int) gaussian_image.data[ x + (y + 1)*w_rect];
                        P2 = (int) gaussian_image.data[ x + 1 + (y + 1)*w_rect];
                        P3 = (int) gaussian_image.data[ x + 1 + y*w_rect];
                        P4 = (int) gaussian_image.data[ x + 1 + (y - 1)*w_rect];
                        P5 = (int) gaussian_image.data[ x + (y - 1)*w_rect];
                        P6 = (int) gaussian_image.data[ x - 1 + (y - 1)*w_rect];
                        P7 = (int) gaussian_image.data[ x - 1 + y*w_rect];
                        P8 = (int) gaussian_image.data[ x - 1 + (y + 1)*w_rect];
                        // Se uno di questi punti e' di contorno allora anche il punto considerato e' di contorno
                        if (P1 > up_threshold || P2 > up_threshold || P3 > up_threshold || P4 > up_threshold
                                || P5 > up_threshold || P6 > up_threshold || P7 > up_threshold || P8 > up_threshold)
                            sum = 255;	/* make edge */
                        else
                            sum = 0;	/* make nonedge */
                    }
                }
            }
            // Metto il valore 0 (nero) nonedge o 255 (bianco) edge nell'immagine
			dest.data[x + y*w_rect] = (unsigned char) sum;
        }
    }

	return VIPRET_OK;
}
///////// End of Canny Edge