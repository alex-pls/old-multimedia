/*****************************************************************************
 *
 * File :       MicrosoftBMP_RT.h
 *
 * Module :     ImageLib.a
 *
 * Author :     Derek Magee, School of Computer Science, Leeds University.
 *
 * Created :    31 October 1997
 *
 *****************************************************************************
 *
 * Source code for Image Library MkII
 *
 * The author, Derek Magee, gives permission for this code to be copied,
 * modified and distributed within the University of Leeds subject to the
 * following conditions:-
 *
 * - The code is not to be used for commercial gain.
 * - The code and use thereof will be attributed to the author where
 *   appropriate (inluding demonstrations which rely on it's use).
 * - All modified, distributions of the source files will retain this header.
 *
 *****************************************************************************
 *
 * Description:
 *
 * Header file for class MicrosoftBMP_RT which deals with reading and writing 24
 * bit Microsoft v3 bitmaps.
 *
 *****************************************************************************
 *
 * Revision History:
 *
 * Date         By              Revision
 *
 * 31/10/97     DRM             Created.
 *
 ****************************************************************************/

#ifndef MICROSOFTBMP_H
#define MICROSOFTBMP_H


#include <stdio.h>
#include <string.h>

#define IMAGE_DATA_OFFSET    54
#define HEADER_SIZE          40
#define NO_OF_IMAGE_PLANES   1
#define BITS_PER_PIXEL       24
#define COMPRESSION_METHOD   0
#define SIZE_OF_BITMAP       0
#define NO_COLOURS_USED      0
#define NO_SIGNIFICANT_COLS  0

#define MAX_FILENAME_LEN     99

class MicrosoftBMP_RT 
{
public:
/* 
 * This class deals with 24 bit uncompressed Microsoft v3 bitmap files only
 * thus the following parameters are constant:
 * 
 * ImageFileType         4D42h ("BM")
 * ImageDataOffset       52
 *
 * HeaderSize            40
 * NumberOfImagePlanes   1
 * BitsPerPixel          24
 * CompressionMethod     0
 * SizeOfBitmap          0
 * NumColorsUsed         0
 * NumSignificantColors  0
 * 
 */

    /* Bitmap header Data */

    unsigned int FileSize;		/* DWORD */

    /* Bitmap information header data */

    unsigned int ImageWidth;		/* DWORD */
    unsigned int ImageHeight;           /* DWORD */
    unsigned int HorizResolution;       /* DWORD */
    unsigned int VertResolution;        /* DWORD */

    /* Header items that should be const. For reading in only */

    unsigned char type1;
    unsigned char type2;
    unsigned int reserved;
    unsigned int data_off;
    unsigned int head_size;
    unsigned int no_planes;
    unsigned int bits_per_pixel;
    unsigned int comp_method;
    unsigned int bitmap_size;
    unsigned int no_cols;
    unsigned int no_sig_cols;

private:
    /* Internal stuff */

    char          file_name[MAX_FILENAME_LEN+1];
    FILE          *file_pnt;
    unsigned char *raw_data;
 
public:
          
    MicrosoftBMP_RT(const char *filename);
    ~MicrosoftBMP_RT();

    bool		read();
    bool                write();
    void                extract_data(int *);
    void                extract_data_grey(int *);
    void                put_data(int *);
    void                put_data_grey(int *);
    bool                set_size(unsigned int, unsigned int);
    void                set_filename(const char *);

private:

    bool                read_byte(unsigned char *);
    bool                read_word(unsigned int *);
    bool                read_dword(unsigned int *);
    bool                write_byte(char);
    bool                write_word(unsigned int);
    bool                write_dword(unsigned int);
    bool                allocate_storage();
    void                calculate_filesize();
    bool                check_header_valid();
};

#endif
