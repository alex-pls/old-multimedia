/** @file vipCodec_BMP.cpp
 *
 * File containing methods for the 'vipCodec_BMP' class.
 * The header for this class can be found in vipCodec_BMP.h, check
 * that file for class description.
 *
 *
 ****************************************************************************
 * VIPLib Framework 1.1
 *  open source, founded by Alessandro Polo 2006
 *  http://mmlab.disi.unitn.it/projects/VIPLib/
 *
 ****************************************************************************/



#include "vipCodec_BMP.h"

#include <new>		// bad_alloc exception

#include <string.h>	// memcpy
#include "external_BMP/MicrosoftBMP_RT.h"
#include "external_BMP/MicrosoftRCBMP_RT.h"
#include "external_BMP/MicrosoftMonoBMP_RT.h"

#include <stdlib.h> // itoa()



vipCodec_BMP::vipCodec_BMP(const char *filename, FileFormat format) : vipFrameRGB96(), vipCodec()
/**
 * Allocates an array of size taken from file for storage of red, green and
 * blue data and fills it with data taken from file.
 * Sets the parameters Width and Height to the inputs width and height.
 *
 * @param filename The name of the image file.
 * @param FileFormat The format of the image file.
 */
 {
	DEBUGMSG("vipCodec_BMP::vipCodec_BMP(char *filename, FileFormat format) [CONTRUCTOR] ", *filename)

	myParams = NULL;
	reset();
	setParameters(NULL);

 	loadBMP( filename, format );

	strcpy(myParams->fileNameBase, filename);
	myParams->fileFormat = format;
 }

vipCodec_BMP::vipCodec_BMP( vipCodec_BMPParameters* initParams ) : vipFrameRGB96(), vipCodec()
 {
	DEBUGMSG("vipCodec_BMP::vipCodec_BMP(vipCodec_BMPParameters* initParams) [CONTRUCTOR] ", *filename)

	myParams = NULL;
	reset();
	setParameters(initParams);
 }

VIPRESULT vipCodec_BMP::reset()
 {
	INFO("int vipCodec_BMP::reset() [SET DEFAULT PARAMETERS]")

	setName("Bitmap Coder");
	setDescription("Read or write images to bitmap format.");
	setVersion(1.0);

	if (myParams != NULL)
	 {
		myParams->reset();
		strcpy(fileNameBuffer, myParams->fileNameBase);
	 }

	return VIPRET_OK;
 }


VIPRESULT vipCodec_BMP::setParameters (vipCodec_BMPParameters* initParams)
 {

	if ( initParams == NULL )
		myParams = new vipCodec_BMPParameters();
	else
		myParams = initParams;

	return VIPRET_OK;
 }

bool vipCodec_BMP::EoF()	// buggy
 {
	 if (data == NULL)
	 	return true;
	 return false;
 }

VIPRESULT vipCodec_BMP::extractTo(vipFrameYUV420& img)
 {
	DEBUGMSG("int vipCodec_BMP::extractTo(vipFrameYUV420& img) [pushing data]", doBuffering)

	VIPRESULT ret = VIPRET_OK;

	if ( myParams->autoOuput && !myParams->doBuffering )
	 {
		doFileNameCurrent();

//check it out !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! added: (FileFormat)
		ret = load(img, fileNameBuffer, (FileFormat)myParams->fileFormat);

		if ( myParams->fileNameProgression )
			myParams->fileNameIndex++;

		return ret;
	 }

	if ( myParams->autoInput )
	 {
		doFileNameCurrent();

		ret = loadBMP(fileNameBuffer, myParams->fileFormat);

		if ( myParams->fileNameProgression )
			myParams->fileNameIndex++;
	 }

	// Marco Verza fix after conversions cleanup... NOT TESTED, and cpu inefficient (multiple conversions)
	//vipFrameRGB96::operator >> (img); // was like this

	vipFrameRGB24 tmp_frame;
	vipFrameRGB96::operator >> (tmp_frame);
	tmp_frame >> img;

	return ret;
 }
 
 
 VIPRESULT vipCodec_BMP::extractTo(vipFrameYUV444& img)
 {
	DEBUGMSG("int vipCodec_BMP::extractTo(vipFrameYUV444& img) [pushing data]", doBuffering)

	return VIPRET_NOT_IMPLEMENTED;
 }

VIPRESULT vipCodec_BMP::extractTo(vipFrameRGB24& img)
 {
	DEBUGMSG("int vipCodec_BMP::extractTo(vipFrameRGB24& img) [pushing data]", doBuffering)

	VIPRESULT ret = VIPRET_OK;

	if ( myParams->autoOuput && !myParams->doBuffering )
	 {
		doFileNameCurrent();


		ret = load(img, fileNameBuffer, myParams->fileFormat);

		if ( myParams->fileNameProgression )
			myParams->fileNameIndex++;

		return ret;
	 }

	if ( myParams->autoInput )
	 {
		doFileNameCurrent();

//check it out !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! added: (FileFormat)
		ret = loadBMP(fileNameBuffer, (FileFormat)myParams->fileFormat);

		if ( myParams->fileNameProgression )
			myParams->fileNameIndex++;
	 }


	vipFrameRGB96::operator >> (img);

	return ret;
 }


VIPRESULT vipCodec_BMP::extractTo(vipFrameT<unsigned char>& img)
 {
	DEBUGMSG("int vipCodec_BMP::extractTo(vipFrameT<unsigned char>& img) [pushing data]", doBuffering)

	return VIPRET_NOT_IMPLEMENTED;
 }



VIPRESULT vipCodec_BMP::importFrom(vipFrameYUV420& img)
 {
	DEBUGMSG("int vipCodec_BMP::importFrom(vipFrameYUV420& img) [reading data]", doBuffering)

	VIPRESULT ret = VIPRET_OK;

	if ( myParams->autoOuput && !myParams->doBuffering )
	 {
		doFileNameCurrent();

		ret = save(img, fileNameBuffer, myParams->fileFormat);

		if ( myParams->fileNameProgression )
			myParams->fileNameIndex++;

		return ret;
	 }

	vipFrameRGB96::operator << (img);

	if ( myParams->autoOuput )
	 {
		doFileNameCurrent();

		ret = saveBMP(fileNameBuffer, myParams->fileFormat);

		if ( myParams->fileNameProgression )
			myParams->fileNameIndex++;
	 }

	return ret;
 }


VIPRESULT vipCodec_BMP::importFrom(vipFrameYUV444& img)
 {
	DEBUGMSG("int vipCodec_BMP::importFrom(vipFrameYUV444& img) [reading data]", doBuffering)

	VIPRESULT ret = VIPRET_OK;


	return VIPRET_NOT_IMPLEMENTED;
 }


VIPRESULT vipCodec_BMP::importFrom(vipFrameRGB24& img)
 {
	DEBUGMSG("int vipCodec_BMP::importFrom(vipFrameRGB24& img) [reading data]", doBuffering)

	VIPRESULT ret = VIPRET_OK;

	if ( myParams->autoOuput && !myParams->doBuffering )
	 {
		doFileNameCurrent();

		ret = save(img, fileNameBuffer, myParams->fileFormat);

		if ( myParams->fileNameProgression )
			myParams->fileNameIndex++;

		return ret;
	 }

	vipFrameRGB96::operator << (img);

	if ( myParams->autoOuput )
	 {
		doFileNameCurrent();

		ret = saveBMP(fileNameBuffer, myParams->fileFormat);

		if ( myParams->fileNameProgression )
			myParams->fileNameIndex++;
	 }

	return ret;
 }

VIPRESULT vipCodec_BMP::importFrom(vipFrameT<unsigned char>& img)
 {
	DEBUGMSG("int vipCodec_BMP::importFrom(vipFrameT<unsigned char>& img) [reading data]", doBuffering)

	return VIPRET_NOT_IMPLEMENTED;

 }

void vipCodec_BMP::setFileName(const char *filename)
 {
	strncpy(myParams->fileNameBase, filename, 64);
	strcpy(fileNameBuffer, myParams->fileNameBase);
 }


void vipCodec_BMP::doFileNameCurrent()
 {

	sprintf( fileNameIndexBuffer, "%d", myParams->fileNameIndex );

	strcpy( fileNameBuffer, myParams->fileNameBase );

	if ( myParams->fileNameIndex != -1 )
		strcat( fileNameBuffer, fileNameIndexBuffer );

	strcat( fileNameBuffer, (const char*)".bmp" );

	DEBUGMSG("void vipCodec_BMP::doFileNameCurrent()", fileNameBuffer);

 }


void vipCodec_BMP::getFileNameCurrent(char* filename)
 {
	doFileNameCurrent();
	strcpy( filename, fileNameBuffer );
 }



VIPRESULT vipCodec_BMP::save()
 {
	INFO("int vipCodec_BMP::save() [saving buffered data]")

	VIPRESULT ret = VIPRET_OK;

	doFileNameCurrent();
	ret = save(reinterpret_cast<vipFrameRGB96&>(*this ), fileNameBuffer, myParams->fileFormat);

	return ret;
}

VIPRESULT vipCodec_BMP::saveBMP(const char *filename, FileFormat format)
 {
	DEBUGMSG("int vipCodec_BMP::saveBMP(char *filename, FileFormat format) [saving buffered data]", filename)

	VIPRESULT ret = VIPRET_OK;

	ret = save(reinterpret_cast<vipFrameRGB96&>(*this), filename, format);

	return ret;
 }


VIPRESULT vipCodec_BMP::load()
 {
	INFO("int vipCodec_BMP::load() [loading data to buffer]")

	VIPRESULT ret = VIPRET_OK;

	doFileNameCurrent();
	ret = load(reinterpret_cast<vipFrameRGB96&>(*this), fileNameBuffer, myParams->fileFormat);

	return ret;
}


VIPRESULT vipCodec_BMP::loadBMP(const char *filename, FileFormat format)
 {
	DEBUGMSG("int vipCodec_BMP::loadBMP(char *filename, FileFormat format) [loading data to buffer]", filename)

	VIPRESULT ret = VIPRET_OK;

	ret = load(reinterpret_cast<vipFrameRGB96&>(*this), filename, format);

	return ret;
 }


///////////////////////////////////////////////////////////////////////////
//STATICs


VIPRESULT vipCodec_BMP::load(vipFrameRGB96& source, const char *filename, FileFormat format)
 {
	DEBUGMSG("int vipCodec_BMP::load(vipFrameCache& source, char *filename, ..) [loading file data to frame]", filename)

	VIPRESULT ret = VIPRET_OK;

	switch (format)
	 {
		case FORMAT_BMP_24:
				{
				MicrosoftBMP_RT bmp(filename);

				if ( !bmp.read() )
					throw("Invalid Bitmap file specified");

				source.reAllocCanvas(bmp.ImageWidth, bmp.ImageHeight);

				bmp.extract_data( (int *)source.data );
				}
				break;

		case FORMAT_BMP_RC:
				{
				MicrosoftRCBMP_RT bmp(filename);

				if ( !bmp.read() )
					throw("Invalid Bitmap file specified");

				source.reAllocCanvas(bmp.ImageWidth, bmp.ImageHeight);
				bmp.extract_data( (int *)source.data );
				}
				break;

		case FORMAT_BMP_MONO:
				{
				MicrosoftMonoBMP_RT bmp(filename);

				if ( !bmp.read() )
					throw("Invalid Bitmap file specified");

				source.reAllocCanvas(bmp.ImageWidth, bmp.ImageHeight);
				bmp.extract_data( (int *)source.data );
				}
				break;

		default:	// FORMAT_BMP_ANY
				{
				// Check all formats
				MicrosoftBMP_RT* bmp;
				MicrosoftRCBMP_RT *bmp_rc;
				MicrosoftMonoBMP_RT *bmp_mono;

				if ( ( bmp = new  MicrosoftBMP_RT(filename) ) != NULL && bmp->read() )
				 {
					// 24 bit bmp
					source.reAllocCanvas(bmp->ImageWidth, bmp->ImageHeight);
					bmp->extract_data( (int *)source.data );

				 }
				else if ( (bmp_rc = new  MicrosoftRCBMP_RT(filename) ) != NULL && bmp_rc->read() )
				 {
					 // Reduced clour (palette) bmp
					source.reAllocCanvas(bmp->ImageWidth, bmp->ImageHeight);
					bmp->extract_data( (int *)source.data );

				}
				else if ( (bmp_mono = new  MicrosoftMonoBMP_RT(filename) ) != NULL && bmp_mono->read() )
				 {
					// Monochrome (b+w) bmp
					source.reAllocCanvas(bmp->ImageWidth, bmp->ImageHeight);
					bmp->extract_data( (int *)source.data ) ;

				 }
				}
				break;

	 }

	return ret;
 }

VIPRESULT vipCodec_BMP::load(vipFrameRGB24& source, const char *filename, FileFormat format)
 {
	DEBUGMSG("int vipCodec_BMP::load(vipFrameRGB24& source, char *filename, ..) [loading file data to frame]", filename)

	VIPRESULT ret = VIPRET_OK;

	vipFrameRGB96 temp;
	ret = load(temp, filename, format);

	if ( ret == VIPRET_OK )
		source << temp;	// todo better !!

	return ret;
 }

VIPRESULT vipCodec_BMP::load(vipFrameYUV420& source, const char *filename, FileFormat format)
 {
	DEBUGMSG("int vipCodec_BMP::load(vipFrameRGB96& source, char *filename, ..) [loading file data to frame]", filename)

	VIPRESULT ret = VIPRET_OK;

	vipFrameRGB96 temp;
	ret = load(temp, filename, format);

	if ( ret == VIPRET_OK )
	{
		// MARCO VERZA fix: after conversions cleanup... NOT TESTED, and cpu inefficient
		//temp >> source;	// todo better !! // <- was like this
		vipFrameRGB24 tmp_rgb24;
		temp >> tmp_rgb24;
		tmp_rgb24 >> source;
	}
	return ret;
 }


VIPRESULT vipCodec_BMP::save(vipFrameRGB96& source, const char *filename, FileFormat format)
 {
	DEBUGMSG("int vipCodec_BMP::save(vipFrameRGB96& source, char *filename, FileFormat format) [saving frame to file]", filename)

	if ( source.width == 0 || source.height == 0 || source.data == NULL )
		return VIPRET_PARAM_ERR;

	VIPRESULT ret = VIPRET_OK;

	switch (format)
	 {
		case vipCodec_BMP::FORMAT_BMP_RC:
				{
				// Greyscale bitmap
				MicrosoftRCBMP_RT *btmp;
				btmp = new MicrosoftRCBMP_RT( filename );
				if ( btmp == NULL )
					ret = VIPRET_CODER_FILEOUT_ER;
				else if ( !btmp->set_size(source.width, source.height) )
					ret = VIPRET_CODER_SIZE_ER;
				else if ( !btmp->set_palette_grey256() )
					ret = VIPRET_CODER_PALETTE_ER;
				else {
					btmp->put_data( (int *)source.data );
								if ( !btmp->write() )
							ret = VIPRET_CODER_WRITE_ER;
				 }
				delete btmp ;
				break;
				}
		case vipCodec_BMP::FORMAT_BMP_MONO:
				{
				// Monochrome bitmap
				MicrosoftMonoBMP_RT *btmp;
				btmp = new MicrosoftMonoBMP_RT( filename );
				if( btmp == NULL )
					ret = VIPRET_CODER_FILEOUT_ER;
				else if ( !btmp->set_size(source.width, source.height) )
					ret = VIPRET_CODER_SIZE_ER;
				else {
					btmp->put_data( (int *)source.data );
								if ( !btmp->write() )
							ret = VIPRET_CODER_WRITE_ER;
				 }
				delete btmp ;
				break;
				}

		default:	// vipCodec_BMP::FORMAT_BMP_24 or vipCodec_BMP::FORMAT_BMP_ANY
				{
				// 24 Bit (full colour) bitmap (+default)
				MicrosoftBMP_RT *btmp;
				btmp = new MicrosoftBMP_RT( filename );

				if ( btmp == NULL )
					ret = VIPRET_CODER_FILEOUT_ER;
				else if ( !btmp->set_size(source.width, source.height) )
					ret = VIPRET_CODER_SIZE_ER;
				else {
					btmp->put_data( (int *)source.data );
								if ( !btmp->write() )
							ret = VIPRET_CODER_WRITE_ER;
				 }
				delete btmp ;
				break;
				}

	 }

	return ret;
}

VIPRESULT vipCodec_BMP::save(vipFrameRGB24& source, const char *filename, FileFormat format)
 {
	DEBUGMSG("int vipCodec_BMP::save(vipFrameRGB24& source, char *filename, FileFormat format) [saving frame to file]", filename)

	if ( source.getWidth() == 0 || source.getHeight() == 0 )
		return VIPRET_PARAM_ERR;

	VIPRESULT ret = VIPRET_OK;
	vipFrameRGB96 temp;

	source >> temp;	// todobetter

	ret = save(temp, filename, format);

	return ret;
 }


//slow
VIPRESULT vipCodec_BMP::save(vipFrameYUV420& source, const char *filename, FileFormat format)
 {
	DEBUGMSG("int vipCodec_BMP::save(vipFrameRGB96& source, char *filename, FileFormat format) [saving frame to file]", filename)

	if ( source.getWidth() == 0 || source.getHeight() == 0 )
		return VIPRET_PARAM_ERR;

	VIPRESULT ret = VIPRET_OK;

	vipFrameRGB96 temp;

	temp << source;	// todobetter

	ret = save(temp, filename, format);

	return ret;
 }



/**
 * @brief	Enable or disable filename progression, for example:
 *          basefile name is "output", index is 13 so filename is output13.bmp,
 *			if filename progression is enabled, when an operation is done
 *          onto file, idex is incremented (output14.bmp).
 *
 * @param[in] value true to enable file name progression.
 */
void vipCodec_BMP::setFileNameProgression(bool value) { myParams->fileNameProgression = value; }

/**
 * @brief   Enable or disable auto input feature,
 *
 *
 * @param[in]
 *
 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
 *
 * @note
 * @see
 */
void vipCodec_BMP::setAutoOutputEnabled(bool value) { myParams->autoOuput = value; }

/**
 * @brief
 *
 *
 * @param[in]
 *
 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
 *
 * @note
 * @see
 */
void vipCodec_BMP::setAutoInputEnabled(bool value) { myParams->autoInput = value; }

/**
 * @brief
 *
 *
 * @param[in]
 *
 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
 *
 * @note
 * @see
 */
void vipCodec_BMP::setDoBuffering(bool value) { myParams->doBuffering = value; }

void vipCodec_BMP::setFileFormat(FileFormat format) { myParams->fileFormat = format; }

/**
 * @brief  Read current file name index, used in file name progression
 *         routines.
 *
 * @return VIPRET_OK if everything is fine,
 *		   VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
 *
 * @note
 * @see
 */

int vipCodec_BMP::getFileNameIndex() { return myParams->fileNameIndex; }
/**
 * @brief
 *
 *
 * @return true if filename progression is enabled.
 *
 * @see   fileNameProgression
 */
bool vipCodec_BMP::isFileNameProgressionEnabled() { return myParams->fileNameProgression; }

/**
 * @brief
 *

 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
 *
 * @note
 * @see
 */
bool vipCodec_BMP::isAutoInputEnabled() { return myParams->autoInput; }

/**
 * @brief
 *
 *
 * @param[in]
 *
 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
 *
 * @note
 * @see
 */
bool vipCodec_BMP::isAutoOutputEnabled() { return myParams->autoOuput; }

/**
 * @brief
 *
 *
 * @param[in]
 *
 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
 *
 * @note
 * @see
 */

bool vipCodec_BMP::isBufferingEnabled() { return myParams->doBuffering; }

/**
 * @brief Read current bitmap encoding/decoding format.
 *
 * @return Current I/O BMP format.
 *
 * @see   FileFormat
 * @see   fileFormat
 */



vipCodec_BMP::FileFormat vipCodec_BMP::getFileFormat()
 {
  return myParams->fileFormat;
 }








vipCodec_BMPParameters::vipCodec_BMPParameters()
 {
	reset();
 }

vipCodec_BMPParameters::vipCodec_BMPParameters(const char* filename, vipCodec_BMP::FileFormat format)
 {
	reset();
	setFileName(filename);
	setFileFormat(format);
}

void vipCodec_BMPParameters::reset()
 {
	strcpy(fileNameBase, (const char*)"OUTPUT_1\0");
	setFileFormat();
	setDoBuffering(true);
	setFileNameProgression(true);
	setFileNameIndex(-1);
	setAutoInputEnabled(false);
	setAutoOutputEnabled(true);
 }



void vipCodec_BMPParameters::setFileName(const char *filename)
 {
	strncpy(fileNameBase, filename, 64);
 }


void vipCodec_BMPParameters::getFileName(char *filename)
 {
	strcpy(filename, fileNameBase);
 }


int vipCodec_BMPParameters::saveToStreamXML(FILE *fp)
 {
	if ( fp == NULL )
		return VIPRET_PARAM_ERR;

	if( fprintf(fp, "<vipCodec_BMPParameters>\n") == EOF )
		return VIPRET_INTERNAL_ERR;

	if ( fprintf(fp, "  <filename value=\"%s\" />\n", fileNameBase) == EOF)
		return VIPRET_INTERNAL_ERR;

	if ( fprintf(fp, "  <fileFormat value=\"%i\" />\n", (int)fileFormat) == EOF)
		return VIPRET_INTERNAL_ERR;

	if ( fprintf(fp, "  <fileNameIndex value=\"%i\" />\n", fileNameIndex) == EOF)
		return VIPRET_INTERNAL_ERR;

	if ( fprintf(fp, "  <doBuffering value=\"%u\" />\n", (int)doBuffering) == EOF)
		return VIPRET_INTERNAL_ERR;

	if ( fprintf(fp, "  <autoOuput value=\"%u\" />\n", (int)autoOuput) == EOF)
		return VIPRET_INTERNAL_ERR;

	if ( fprintf(fp, "  <autoInput value=\"%u\" />\n", (int)autoInput) == EOF)
		return VIPRET_INTERNAL_ERR;

	if( fprintf(fp, "</vipCodec_BMPParameters>\n") == EOF )
		return VIPRET_INTERNAL_ERR;

	return VIPRET_OK;
 }


int vipCodec_BMPParameters::loadFromStreamXML(FILE *fp)
 {
	if ( fscanf(fp, "<vipCodec_BMPParameters>\n") == EOF )
		throw "error in XML file, unable to import data.";

	if ( fscanf(fp, "  <filename value=\"%s\" />\n", fileNameBase) == EOF )
		throw "error in XML file, unable to import data.";

	if ( fscanf(fp, "  <fileNameIndex value=\"%i\" />\n", &fileNameIndex) == EOF )
		throw "error in XML file, unable to import data.";

	int boolTmp = 1;
	if ( fscanf(fp, "  <doBuffering value=\"%u\" />\n", &boolTmp) == EOF )
		throw "error in XML file, unable to import data.";

	if (boolTmp == 0)
		doBuffering = false;
	else
		doBuffering = true;

	boolTmp = 0;
	if ( fscanf(fp, "  <autoOuput value=\"%u\" />\n", &boolTmp) == EOF )
		throw "error in XML file, unable to import data.";

	if (boolTmp == 0)
		autoOuput = false;
	else
		autoOuput = true;

	boolTmp = 0;
	if ( fscanf(fp, "  <autoInput value=\"%u\" />\n", &boolTmp) == EOF )
		throw "error in XML file, unable to import data.";

	if (boolTmp == 0)
		autoInput = false;
	else
		autoInput = true;

	return VIPRET_OK;
 }




