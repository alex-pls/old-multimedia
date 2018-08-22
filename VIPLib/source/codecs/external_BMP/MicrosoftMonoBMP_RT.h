/*****************************************************************************
 *
 * File :       MicrosoftMonoBMP_RT.h
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
 * Header file for class MicrosoftMonoBMP_RT which deals with reading and writing
 * monocrome Microsoft v3 bitmaps.
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

#ifndef MICROSOFTBMPMONO_H
#define MICROSOFTBMPMONO_H


#include <stdio.h>
#include <string.h>

#define IMAGE_DATA_OFFSET_M    62 
#define HEADER_SIZE_M          40
#define NO_OF_IMAGE_PLANES_M   1
#define BITS_PER_PIXEL_M       1 
#define COMPRESSION_METHOD_M   0
#define SIZE_OF_BITMAP_M       0
#define NO_COLOURS_USED_M      0
#define NO_SIGNIFICANT_COLS_M  0
#define PALETTE0_R           0
#define PALETTE0_G           0
#define PALETTE0_B           0
#define PALETTE0_GREY        0
#define PALETTE1_R           255
#define PALETTE1_G           255
#define PALETTE1_B           255
#define PALETTE1_GREY        255

#define MAX_FILENAME_LEN     99

class MicrosoftMonoBMP_RT 
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
    unsigned char     pallete_false_r;
    unsigned char     pallete_false_g;
    unsigned char     pallete_false_b;
    unsigned char     pallete_false_grey;
    unsigned char     pallete_true_r;
    unsigned char     pallete_true_g;
    unsigned char     pallete_true_b;
    unsigned char     pallete_true_grey;

    /* Header items that should be const. For reading in only */

    unsigned char type1;
    unsigned char type2;
    unsigned int  reserved;
    unsigned int  data_off;
    unsigned int  head_size;
    unsigned int  no_planes;
    unsigned int  bits_per_pixel;
    unsigned int  comp_method;
    unsigned int  bitmap_size;
    unsigned int  no_cols;
    unsigned int  no_sig_cols;

private:
    /* Internal stuff */

    char file_name[MAX_FILENAME_LEN+1];
    FILE *file_pnt;
    char *raw_data;
 
public:
          
    MicrosoftMonoBMP_RT(const char *filename);
    ~MicrosoftMonoBMP_RT();

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
