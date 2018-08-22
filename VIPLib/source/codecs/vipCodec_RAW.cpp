/** @file vipCodec_RAW.cpp
 *
 * File containing methods for the 'vipCodec_RAW' class.
 * The header for this class can be found in vipCodec_RAW.h, check that file
 * for class description.
 *
 *
 *
 ****************************************************************************
 * VIPLibb Framework 1.02
 *  Copyright (C) Alessandro Polo 2005
 *  http://mmlab.disi.unitn.it/projects/VIPLib
 *
 *  maintained by MultiMedia Laboratory - DISI - University of Trento
 *
 ****************************************************************************/



#include "vipCodec_RAW.h"
#include "../vipUtility.h"
//#include "../../include/ccvt/ccvt.h"
#include <math.h>
//#include <string.h>
#include <string>



//////////////////////////////////////////////////////////////////


vipCodec_RAW::vipCodec_RAW( vipCodec_RAWParameters* initParams ) : vipCodec()
 {
	DEBUGMSG("vipCodec_RAW::vipCodec_RAW(vipCodec_RAWParameters* initParams) [CONTRUCTOR] ", *filename)

//printf("DEBUG:::::::vipCodec_RAW costrutt. initparam\n");

	myParams = NULL;

	f = NULL;
	reset();
	setParameters(initParams);

 }



/**
 * @brief  Initialize parameters and load image/video stream from file.
 *         vipFrameRGB constructor.
 *
 * @param[in] filename Input BMP filename.
 * @param[in] format BMP Encoding Format, default auto-selection.
 */
vipCodec_RAW::vipCodec_RAW(char *filename, int stream) : vipCodec()
 {
	DEBUGMSG("vipCodec_RAW::vipCodec_RAW(char *filename, FileFormat format) [CONTRUCTOR] ", *filename)

//printf("DEBUG:::::::vipCodec_RAW costrutt. *filename\n");


	f = NULL;

	reset();
	setParameters(NULL);
 	load(filename, stream);

 }



VIPRESULT vipCodec_RAW::reset()
 {
	INFO("int vipCodec_RAW::reset() [SET DEFAULT PARAMETERS]")

//printf("DEBUG:::::::vipCodec_RAW reset\n");


	width  = 0;      //dimension of Y plane(not necessary ...)
	height = 0;
	UVwidth = 0;
	UVheight = 0;

	range_S = 0;
	average_S = 0;

	close();

	f = NULL;

	if (myParams != NULL)
		myParams->reset();//reset the param file..



	/*if (pData != NULL){

		delete pData;
		pData = NULL;

		}*/


	setName("vipCoder_RAW");
	setDescription("Reads YUV 4:2:0");
	setVersion(1.0);

	return VIPRET_OK;
 }


vipCodec_RAW::~vipCodec_RAW()
 {
//printf("DEBUG:::::::vipCodec_RAW distrutt.\n");


	if (myParams != NULL)
		delete myParams;


	if (pData != NULL) {
		delete[] pData;
		pData = NULL;
		}

 }


bool vipCodec_RAW::EoF(){

	if ( myParams->frameIndex >= NumberFrame)

		return true;

	else

		return false;
	}



VIPRESULT vipCodec_RAW::setParameters (vipCodec_RAWParameters* initParams)
 {
//printf("DEBUG:::::::vipCodec_RAW setparameters. initparam\n");


	if ( initParams == NULL )

		myParams = new vipCodec_RAWParameters();

	else

		myParams = initParams;


	return VIPRET_OK;
 }


/**
 * @brief  Load an image/video into current buffer ().
 *
 * @param[in] filename Input
 * @
 *
 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
 */
VIPRESULT vipCodec_RAW::load(char *filename, int stream)
 {
	DEBUGMSG("int vipCodec_RAW::load(char *filename, FileFormat format) [loading data to buffer.]", filename)

//printf("DEBUG:::::::vipCodec_RAW load *filename\n");


 	myParams->setFileName(filename);
 	myParams->setStream(stream);

	load();

	return VIPRET_OK;
 }

VIPRESULT vipCodec_RAW::load()
 {
	DEBUGMSG("int vipCodec_RAW::load() [loading data to buffer..]",filename)

//printf("DEBUG:::::::vipCodec_RAW load\n");

	//register some info from myParams

	width = myParams->Ywidth;
	height = myParams->Yheight;


	//open file pointed by myParams

	f = fopen(myParams->fileName,"rb");
	//printf("formato %s\n",myParams->Video_Format);
	//some dditional calculation..
	//set the UV planes dimensions and the pixel/frame value..

	if(strncmp(myParams->Video_Format,"Y",10) == 0){	//only Y plane

				UVwidth = 0;
				UVheight = 0;
				NumberPixel = width * height;

	}

	else

		if(strncmp(myParams->Video_Format,"YUV_4:2:0",10) == 0){	//full YUV downsampled

				UVwidth = width/2;
				UVheight = height/2;
				NumberPixel = width * height * 3/2;


	}

	else

		if(strncmp(myParams->Video_Format,"YUV_4:4:4",10)==0){	//full YUV

				UVwidth = width;
				UVheight = height;
				NumberPixel = width * height * 3;

				}
	else
		return VIPRET_PARAM_ERR;


	//calculating the dimension of the video in frame..

	fseek(f,0,SEEK_END);
	long DataLenght = ftell(f);

	//total number of frame
	NumberFrame = (unsigned int) DataLenght / NumberPixel;
	//printf("numberframe %d\n",NumberFrame);

	//allocating space for memorize 1 frame for now..

	if (!pData)
	{
		if ((pData = new unsigned char [NumberPixel]) == NULL)
		{
			printf("pdata problem..\n");
			return VIPRET_PARAM_ERR;
		}
	}

	pData = new unsigned char [NumberPixel];


	return VIPRET_OK;
	}


unsigned char vipCodec_RAW::ReadFrame(unsigned int Frame)
{
	DEBUGMSG("unsigned char vipCodec_RAW::ReadFrame(unsigned int Frame) [reading frame..]", Frame)

//printf("DEBUG:::::::vipCodec_RAW readframe frame.\n");


	if (Frame >= NumberFrame)
		{
		printf("Error reading frame..\nframe %d,numbframe %d\n",Frame,NumberFrame);
		return VIPRET_INTERNAL_ERR;
		}

	//if we are not open for reading, then open for reading.

	if (f == NULL){//?????? so work...
		fopen(myParams->fileName,"rb");
		printf("\n (ReadFrame)I/O error..\n");
		//printf("myparam %s\n",myParams->fileName);

		return VIPRET_ILLEGAL_USE ;
	}

	//int bo = sizeof(&pData);
	//printf("\n%d \n",bo);
	//printf("\n%d\n",sizeof(unsigned char));


	myParams->frameIndex = Frame;      //FrameNumber


	//move the pointer to the right position

	fseek(f,Frame * NumberPixel, SEEK_SET);


	//read the data of a single frame..

	int num = fread(pData, 1 , NumberPixel, f);





	return VIPRET_OK;
}



VIPRESULT vipCodec_RAW::newVideo(const char *filename)
 {
	DEBUGMSG("int vipCodec_RAW::newVideo(const char *filename) [opening file for writing..]", filename)

//printf("DEBUG:::::::vipCodec_RAW newvideo *filename\n");


	if ( f != NULL)
		return VIPRET_ILLEGAL_USE;

 	myParams->setFileName(filename);
	myParams->setFrameIndex(0);
	myParams->setStream(0);//tanto per..

	f = fopen(filename, "wb");   //crea un nuovo file e sovrascrive il precedente..

	//mode binary append...
	f = fopen(filename, "ab");	//occhio che non cancella il file se c'e gia..

	if ( f == NULL)
		return VIPRET_INTERNAL_ERR;

	return VIPRET_OK;

 }


VIPRESULT vipCodec_RAW::close()
 {
	DEBUGMSG("int vipCodec_RAW::close() [closing class structure]", filename)

//printf("DEBUG:::::::vipCodec_RAW close\n");


	if ( f == NULL)
		return VIPRET_ILLEGAL_USE;

	fclose(f);


	return VIPRET_OK;
 }





/**
 * @brief  Load data into passed image, move current index to next frame.
 *
 * @param[out] img VIPLibb Cache Frame to store data.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
 *
 * @note   Ouput operator (>>) call directly this function.
 * @see    operator >> (vipFrameCache&)
 * @see    AutoInput
 */
VIPRESULT vipCodec_RAW::extractTo(vipFrameYUV420& img)
 {
	DEBUGMSG("int vipCodec_RAW::extractTo(vipFrameYUV420& img) [pushing data]", doBuffering)

//printf("DEBUG:::::::vipCodec_RAW extract\n");

	//controll about the type of capture and the dimension of the structure..

	if (width != img.width || height != img.height)
		{
		delete[] img.data;
		//create a matrix of unsigned char
		  img.data = new unsigned char [NumberPixel];
		}
	img.width = width;
	img.height = height;


//now read the frame passed from frameIndex, in myParam, into a temp array, pData
//readframe cares about onlyY capture or full YUV planes..

	ReadFrame(myParams->frameIndex);
	//for(int i = 0; i < NumberPixel; i++)
	//img.data = pData;			// huge BUG imho. Marco Verza
	memcpy( img.data, pData, sizeof(unsigned char)*NumberPixel );	// my fix. MV


	//move forward the frame indexer, in myParams...

	myParams->frameIndex++;

	return VIPRET_OK;
 }

/**
 * @brief  Load data into passed image, move current index to next frame.
 *         Added by Marco Verza.
 *
 * @param[out] img VIPLibb Cache Frame to store data.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
 *
 * @note   Ouput operator (>>) call directly this function.
 * @see    operator >> (vipFrameCache&)
 * @see    AutoInput
 */
VIPRESULT vipCodec_RAW::extractTo(vipFrameYUV444& img)
 {
	DEBUGMSG("int vipCodec_RAW::extractTo(vipFrameYUV444& img) [pushing data]", doBuffering)

//printf("DEBUG:::::::vipCodec_RAW extract\n");




	// check the type of capture and the dimension of the structure..

	if (width != img.width || height != img.height)
		{
		delete[] img.data;
		//create a matrix of unsigned char
		  img.data = new unsigned char [NumberPixel];
		}
	img.width = width;
	img.height = height;


	// MARCO VERZA added:
	if(strcmp(myParams->Video_Format,"YUV_4:2:0") == 0)
	{
		// conversion is needed
		ReadFrame(myParams->frameIndex);
		VIPRESULT ret = vipUtility::conv_PlanarYUV420toPlanarYUV444(pData, img.data, width,height);		// changed to new method by Marco Verza, was: UV_upsampling()
		myParams->frameIndex++;
		return ret;
	}
    // check format
	else if(strcmp(myParams->Video_Format,"YUV_4:4:4") != 0)
	{
		// conversion is needed
		// TODO
		throw("vipCodec_RAW::extractTo(vipFrameYUV444& img): conversion from formats other than YUV444 is not yet implemented.");
	}


//now read the frame passed from frameIndex, in myParam, into a temp array, pData
//readframe cares about onlyY capture or full YUV planes..

	ReadFrame(myParams->frameIndex);
	//for(int i = 0; i < NumberPixel; i++)
	//img.data = pData;	// HUGE BUG IMHO. Marco Verza.
	memcpy( img.data, pData, sizeof(unsigned char)*NumberPixel );	// my fix. MV

	//move forward the frame indexer, in myParams...

	myParams->frameIndex++;

	return VIPRET_OK;
 }





/**
 * @brief  Load data into passed image, move current index to next frame.
 *
 * @param[out] img VIPLibb Cache24 Frame to store data.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
 *
 * @note   Ouput operator (>>) call directly this function.
 * @see    operator >> (vipFrameCache24&)
 * @see    AutoInput
 */
VIPRESULT vipCodec_RAW::extractTo(vipFrameRGB24& img)
 {
	DEBUGMSG("int vipCodec_RAW::extractTo(vipFrameRGB24& img) [pushing data]", doBuffering)

//printf("DEBUG:::::::vipCodec_RAW extract\n");
		if (width != img.width || height != img.height)
		{
		delete[] img.data;
		//create a matrix of PixelRGB, each PixelRGB is an array of unsigned char[3]
		  img.data = new PixelRGB24 [width * height];
		}
	img.width = width;
	img.height = height;


//now read the frame passed from frameIndex, in myParam, into a temp array, pData
//readframe cares about onlyY capture or full YUV planes..

	ReadFrame(myParams->frameIndex);
	//printf("myparam..%s\n",myParams->fileName);

	//chrominance upsampling..
	unsigned char* upsampled_data = new unsigned char[width*height*3];

	VIPRESULT ret = vipUtility::conv_PlanarYUV420toPlanarYUV444(pData,upsampled_data,width,height);		// changed to new method by Marco Verza, was: UV_upsampling()
	vipUtility::conv_PlanarYUV444toPixelRGB24(upsampled_data, (unsigned char*)img.data[0], width, height);
	//conv_PixelRGBtoPlanarYUV((unsigned char*) img.data[0], buffer, width, height);

	//FILE*  fi;
	//fi=fopen("YUV444.yuv","wb");
	//fwrite(upsampled_data,1,width*height*3,fi);

	//move forward the frame indexer, in myParams...

	myParams->frameIndex++;

	//free buffered resources..
	delete upsampled_data;

	return ret;
 }



/**
 * @brief  Load data into passed image, move current index to next frame.
 *
 * @param[out] img Color VIPLibb Frame to store data.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
 *
 * @note   Ouput operator (>>) call directly this function.
 * @see    operator >> (vipFrameRGB&)
 * @see    AutoInput
 */
VIPRESULT vipCodec_RAW::extractTo(vipFrameT<unsigned char>& img)
 {
	DEBUGMSG("int vipCodec_RAW::extractTo(vipFrameRGB& img) [pushing data]", doBuffering)

//printf("DEBUG:::::::vipCodec_RAW extract\n");

	return VIPRET_NOT_IMPLEMENTED;
 }



/**
 * @brief  Load data into passed image, move current index to next frame.
 *
 * @param[out] img Greyscale VIPLibb Frame to store data.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
 *
 * @note   Ouput operator (>>) call directly this function.
 * @see    operator >> (vipFrameGrey&)
 * @see    AutoInput
 */

 /*int vipCodec_RAW::extractTo(vipFrameGrey& img)
 {
	DEBUGMSG("int vipCodec_RAW::extractTo(vipFrameGrey& img) [pushing data]", doBuffering)

printf("DEBUG:::::::vipCodec_RAW extract\n");

	return VIPRET_NOT_IMPLEMENTED;
 }*/




/**
 * @brief  Add given image to current stream.
 *
 * @param[in] img VIPLibb Cache Frame to be processed (encoded for example)
 *
 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
 *
 * @note   Input operator (<<) call directly this function.
 * @see    operator << (vipFrameCache&)
 */
VIPRESULT vipCodec_RAW::importFrom(vipFrameYUV420& img)
 {
	DEBUGMSG("int vipCodec_RAW::importFrom(vipFrameYUV420& img) [reading data]", doBuffering)

//printf("DEBUG:::::::vipCodec_RAW import\n");

//control for stream dimensions..

	if ( f == NULL)
		{
		printf("I/O file error..\n");
		return VIPRET_ILLEGAL_USE;
		}


	if(myParams->Ywidth == -1 || myParams->Ywidth == -1){

		myParams->setYheight(img.getHeight());
		myParams->setYwidth(img.getWidth());


	}


	//depending on the case (full YUV capture or not..),
	//we procede by copying the data into the file structure.

	if(strcmp(myParams->Video_Format,"Y") == 0)
		fwrite(img.data, 1, img.height * img.width, f);
	else
		if(strcmp(myParams->Video_Format,"YUV_4:2:0") == 0)
			fwrite(img.data, 1, img.height * img.width * 3/2, f);
		else
			if(strcmp(myParams->Video_Format,"YUV_4:4:4") == 0)
			fwrite(img.data, sizeof(unsigned char), img.height * img.width * 3, f);


	//move forward the frame indexer, in myParams..
	myParams->frameIndex++;

	return VIPRET_OK;
 }



/**
 * @brief  Add given image to current stream.
 *
 * @param[in] img VIPLibb RGB24 Frame to be processed (encoded for example)
 *
 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
 *
 * @note   Input operator (<<) call directly this function.
 * @see    operator << (vipFrameRGB24&)
 */
VIPRESULT vipCodec_RAW::importFrom(vipFrameRGB24& img)
 {
	DEBUGMSG("int vipCodec_RAW::importFrom(vipFrameRGB24& img) [reading data]", doBuffering)

//printf("\n\n******************DEBUG:::::::vipCodec_RAW import******************\n\n");

	if ( f == NULL)
		{
		printf("I/O file error..\n");
		return VIPRET_ILLEGAL_USE;
		}


	unsigned char* buffer=new unsigned char[img.width*img.height*3];

	if(myParams->Ywidth == -1 || myParams->Ywidth == -1)
	{
		myParams->setYheight(img.getHeight());
		myParams->setYwidth(img.getWidth());
	}


	vipUtility::conv_PixelRGB24toPlanarYUV444((unsigned char*) img.data[0], buffer, img.width, img.height);	// edited by Marco Verza, was: conv_PixelRGBtoPlanarYUV(...

	fwrite(buffer, 1, img.height * img.width * 3, f);

	//move forward the frame indexer, in myParams..
	myParams->frameIndex++;
	delete buffer;

	return VIPRET_OK;
 }





/**
 * @brief  Add given image to current stream.
 *
 * @param[in] img Color VIPLib Frame to be processed (encoded for example)
 *
 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
 *
 * @note   Input operator (<<) call directly this function.
 * @see    operator << (vipFrameRGB&)
 */
VIPRESULT vipCodec_RAW::importFrom(vipFrameT<unsigned char>& img)
 {
	DEBUGMSG("int vipCodec_RAW::importFrom(vipFrameRGB& img) [reading data]", doBuffering)

//printf("DEBUG:::::::vipCodec_RAW import\n");


	return VIPRET_NOT_IMPLEMENTED;

 }




/**
 * @brief  Add given image to current stream.
 *
 * @param[in] img Greyscale VIPLibb Frame to be processed (encoded for example)
 *
 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
 *
 * @note   Input operator (<<) call directly this function.
 * @see    operator << (vipFrameGrey&)
 */

 /*int vipCodec_RAW::importFrom(vipFrameGrey& img)
 {
	DEBUGMSG("int vipCodec_RAW::importFrom(vipFrameCache& img) [reading data]", doBuffering)

printf("DEBUG:::::::vipCodec_RAW import\n");


	return VIPRET_OK;

 }*/






























vipCodec_RAWParameters::vipCodec_RAWParameters()
 {
//printf("DEBUG:::::::vipCodec_RAWparameters costrutt.\n");

	reset();

 }

vipCodec_RAWParameters::vipCodec_RAWParameters(const char* filename, int stream, long frameIndex)
 {
//printf("DEBUG:::::::vipCodec_RAWparameters setparameters *filename.\n");

	reset();
	setFileName(filename);
	setStream(stream);
	setFrameIndex(frameIndex);
 }

void vipCodec_RAWParameters::reset()
 {
//printf("DEBUG:::::::vipCodec_RAWparameters reset\n");

	strcpy(fileName,"not_assigned");
	Fps=-1;
	frameIndex = 0;
	stream = -1;
	Ywidth = -1;
	Yheight = -1;
	strcpy(Video_Format,"not_assigned");	//default not assigned
 }


void vipCodec_RAWParameters::setYwidth(int width)
 {
    Ywidth = width;
 }

void vipCodec_RAWParameters::setYheight(int height)
 {
    Yheight = height;
 }


void vipCodec_RAWParameters::setVideoFormat(const char* format)
 {
    strcpy ( Video_Format,format );

 }




void vipCodec_RAWParameters::setFileName(const char *filename)
 {
	strcpy ( fileName, filename );
 }



void vipCodec_RAWParameters::setFrameIndex(long index)
 {
	frameIndex = index;
 }



void vipCodec_RAWParameters::setStream(int s)
 {
	stream = s;
 }

 void vipCodec_RAWParameters::setFps(int fps)
 {
	Fps = fps;
 }



/**
 * @brief  Serialize class to XML format.
 *         Class' tag is <vipCodec_MOVParameters>
 *
 * @param[in] fp output stream's pointer
 *
 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
 */
VIPRESULT vipCodec_RAWParameters::saveToStreamXML(FILE *fp)
 {


	if ( fp == NULL )
		return VIPRET_PARAM_ERR;

	if( fprintf(fp, "<vipCodec_RAWParameters>\n") == EOF )
		return VIPRET_INTERNAL_ERR;

	if ( fprintf(fp, "  <filename value=\" %s \" />\n", fileName) == EOF)
		return VIPRET_INTERNAL_ERR;

	if ( fprintf(fp, "  <stream value=\" %d \" />\n", stream) == EOF)
		return VIPRET_INTERNAL_ERR;

	if ( fprintf(fp, "  <frameIndex value=\" %ld \" />\n", frameIndex) == EOF)
		return VIPRET_INTERNAL_ERR;

	if ( fprintf(fp, "  <video format=\" %s \" />\n", Video_Format) == EOF)
		return VIPRET_INTERNAL_ERR;

	if ( fprintf(fp, "  <width value=\" %d \" />\n", Ywidth) == EOF)
		return VIPRET_INTERNAL_ERR;

	if ( fprintf(fp, "  <height value=\" %d \" />\n", Yheight) == EOF)
		return VIPRET_INTERNAL_ERR;

	if ( fprintf(fp, "  <frame rate value=\" %d \" />\n", Fps) == EOF)
		return VIPRET_INTERNAL_ERR;

	if( fprintf(fp, "</vipCodec_RAWParameters>\n") == EOF )
		return VIPRET_INTERNAL_ERR;

	return VIPRET_OK;
 }




/**
 * @brief  Deserialize class from XML format.
 *         Class' tag must be <vipCodec_RAWParameters>
 *
 * @param[in] fp input stream's pointer
 *
 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
 */
VIPRESULT vipCodec_RAWParameters::loadFromStreamXML(FILE *fp)
 {
	char line[64];

	fgets(line,64,fp);
	if(strcmp(line,"<vipCodec_RAWParameters>\n") != 0)
		throw( "error in XML file, unable to import data.");

	fgets(line,64,fp);
	if (sscanf(line,"  <filename value=\"%s\" />\n",fileName) == EOF)
		throw ("error in XML file, unable to import data.");
	//else
	//	printf("filename read %s\n",fileName);

	fgets(line,64,fp);
	if ( sscanf(line, "  <stream value=\"%d\" />\n", &stream) == EOF )
		throw ("error in XML file, unable to import data.");
	//else
	//	printf("stream value loaded= %d\n", stream);

	fgets(line,64,fp);
	if ( sscanf(line, "  <frameIndex value=\"%ld\" />\n", &frameIndex) == EOF )
		throw ("error in XML file, unable to import data.");
	//else
	//	printf("frameindex value loaded= %ld\n", frameIndex);

	fgets(line,64,fp);
	if ( sscanf(line, "  <video format=\"%s\" />\n", Video_Format) == EOF)
		throw ("error in XML file, unable to import data.");
	//else
	//	printf("video format= %s\n",Video_Format);

	fgets(line,64,fp);
	if ( sscanf(line, "  <width value=\"%d\" />\n", &Ywidth) == EOF)
		throw ("error in XML file, unable to import data.");
	//else
	//	printf("width loaded= %d\n",Ywidth);

	fgets(line,64,fp);
	if ( sscanf(line, "  <height value=\"%d\" />\n", &Yheight) == EOF)
		throw ("error in XML file, unable to import data.");
	//else
	//	printf("height loaded= %d\n",Yheight);

	fgets(line,64,fp);
	if ( sscanf(line, "  <frame rate value=\"%d\" />\n", &Fps) == EOF)
		throw ("error in XML file, unable to import data.");


/*char* line;
	fpos_t init_position;
	//memorize the init_position in file..
	int i = fgetpos(fp,&init_position);

	//go to the end of file to see how long it is..
	fseek(fp,1,SEEK_END);
	int end_position = ftell(fp);
	printf("end_position %d",end_position);
	int file_lenght = end_position - init_position;

	//allocate a char buffer..
	line = new char [file_lenght];
	printf("file lungo %d\n", file_lenght);

	//reset the file pointer to the init_position..
	fsetpos(fp,&init_position);

	//read tha fiel content..
	fread(line,sizeof(char),file_lenght,fp);
	printf("file letto %s\n",line);


	//retrieve info from file and store in local variables..
*/
	/*if ( fscanf(fp, "<vipCodec_RAWParameters>\n") == EOF )
		throw( "error in XML file, unable to import data.");



	if ( fscanf(fp, "  <filename value=\"%s\" />\n", fileName) == EOF )
		throw( "error in XML file, unable to import data.");
	else
		printf("filename loaded= %s\n",fileName);


	if ( fscanf(fp, "  <stream value=\"%d\" />\n", &stream) == EOF )
		throw ("error in XML file, unable to import data.");
	else
		printf("stream value loaded= %d\n", stream);


	if ( fscanf(fp, "  <frameIndex value=\"%ld\" />\n", &frameIndex) == EOF )
		throw ("error in XML file, unable to import data.");
	else
		printf("frameindex value loaded= %ld\n", frameIndex);


	if ( fscanf(fp, "  <video format=\"%s\" />\n", Video_Format) == EOF)
		throw ("error in XML file, unable to import data.");
	else
		printf("video format= %s\n",Video_Format);


	if ( fscanf(fp, "  <width value=\"%d\" />\n", &Ywidth) == EOF)
		throw ("error in XML file, unable to import data.");
	else
		printf("width loaded= %d\n",Ywidth);


	if ( fscanf(fp, "  <height value=\"%d\" />\n", &Yheight) == EOF)
		throw ("error in XML file, unable to import data.");
	else
		printf("height loaded= %d\n",Yheight);*/








	return VIPRET_OK;
 }



///**
// * @brief  Perform UV upsampling from 420 to 444.
// *         
// * @note   Implemented by Marco Verza for vipFrame444. Not tested yet
// *
// * @todo   Consider interpolation instead of duplication (slower)
// *
// * @param[in] in input pointer to data
// * @param[in] width image width
// * @param[in] height image height
// * @return pointer to upsampled data
// *
// * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
// */
// unsigned char* vipCodec_RAW::UV_upsampling(unsigned char* in, int width, int height)
// {
//	 // check input
//	 if( in == NULL )
//		 throw("vipCodec_RAW::UV_upsampling: input data pointer is null.");
//
//	 unsigned char* uv_up = new unsigned char[ width * height * 3 ];
//	 const unsigned int len = width * height;
//	 unsigned int j = 0;
//
//	 // upsample UV components
//	 for( int i=len; i<len*1.5; i++)
//	 {
//		 uv_up[j] = in[i];
//		 uv_up[j+1] = in[i];
//		 uv_up[j+2] = in[i];
//		 uv_up[j+3] = in[i];
//		 j+=4;
//	 }
//
//	 return uv_up;	// 
// }









































// temporaneamente, da spostare in vipUtility o classi affini :



