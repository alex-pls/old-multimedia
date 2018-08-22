/*****************************************************************************
 *
 * File :       MicrosoftRCBMP_RT.h
 *
 * Module :     ImageLib.a
 *
 * Author :     Derek Magee, School of Computer Science, Leeds University.
 *
 * Created :    3 November 1998
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
 * Header file for class MicrosoftRCBMP_RT which deals with reading 
 * reduced colour Microsoft v3 bitmaps.
 *
 *****************************************************************************
 *
 * Revision History:
 *
 * Date         By              Revision
 *
 * 3/11/98      DRM             Created.
 *
 ****************************************************************************/

#ifndef MICROSOFTRCBMP_H
#define MICROSOFTRCBMP_H


#include <stdio.h>
#include <string.h>

#define IMAGE_DATA_OFFSET_R    (54+256*4) 
#define HEADER_SIZE_R          40
#define NO_OF_IMAGE_PLANES_R   1
#define BITS_PER_PIXEL_R       8 
#define COMPRESSION_METHOD_R   0
#define SIZE_OF_BITMAP_R       0
#define NO_COLOURS_USED_R      0
#define NO_SIGNIFICANT_COLS_R  0

#if 0
#define PALETTE0_R           0
#define PALETTE0_G           0
#define PALETTE0_B           0
#define PALETTE1_R           255
#define PALETTE1_G           255
#define PALETTE1_B           255
#endif

#define MAX_FILENAME_LEN     99

struct rgb{
           unsigned char red ;
           unsigned char green ;
           unsigned char blue ;
};

class MicrosoftRCBMP_RT 
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
    rgb          *palette;

    /* Header items that should be const. For reading in only */

    char type1;
    char type2;
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

    char          file_name[MAX_FILENAME_LEN+1];
    FILE          *file_pnt;
    unsigned char *raw_data;
 
public:
          
    MicrosoftRCBMP_RT(const char *);
    ~MicrosoftRCBMP_RT();

    bool		read();
    bool		write();
    void                extract_data(int *);
    void                extract_data_grey(int *);
    void                put_data(int*) ;
    void                put_data_grey(int*) ;
    bool                set_size(unsigned int, unsigned int);
    bool                set_palette_grey256() ;

private:

    void                set_filename(const char *);
    bool                read_byte(char *);
    bool                read_word(unsigned int *);
    bool                read_dword(unsigned int *);
    bool                write_byte(char);
    bool                write_word(unsigned int);
    bool                write_dword(unsigned int);
    bool                allocate_storage();
    void                calculate_filesize();
    bool                check_header_valid();
    unsigned char       palette_lookup(int*) ;
};

#endif
