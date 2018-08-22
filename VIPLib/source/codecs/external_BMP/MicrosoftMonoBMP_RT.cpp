/*****************************************************************************
 *
 * File :       MicrosoftMonoBMP_RT.cpp
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
 * Methods for reading and writing monochrome Microsoft v3 bitmap files.
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

#include "MicrosoftMonoBMP_RT.h"


MicrosoftMonoBMP_RT::MicrosoftMonoBMP_RT(const char *filename)
{
/* 
 * This is the constructor method for the MicrosoftMonoBMP_RT class. It copies the
 * string pointed to by filename into the file_name buffer, truncating if
 * it is greater than this buffer and initialises other parameters to sensible
 * values.
 */

    set_filename(filename);
    FileSize = IMAGE_DATA_OFFSET_M;
    ImageWidth = 0;
    ImageHeight = 0;
    HorizResolution = 0;
    VertResolution = 0;
    pallete_false_r = PALETTE0_R;
    pallete_false_g = PALETTE0_G;
    pallete_false_b = PALETTE0_B;
    pallete_false_grey = PALETTE0_GREY ;
    pallete_true_r = PALETTE1_R;
    pallete_true_g = PALETTE1_G;
    pallete_true_b = PALETTE1_B;
    pallete_true_grey = PALETTE1_GREY ;
    file_pnt = NULL;
    raw_data = NULL;
}

MicrosoftMonoBMP_RT::~MicrosoftMonoBMP_RT()
{
/*
 * This is the destructor for the class MicrosoftMonoBMP_RT. It frees allocated 
 * memory.
 */

    delete raw_data;
}

void MicrosoftMonoBMP_RT::set_filename(const char *filename)
{
/* 
 * copy string pointed to by filename into buffer file_name truncating if
 * length is greater than MAX_FILENAME_LEN.
 */

    strncpy(file_name, filename, MAX_FILENAME_LEN);

    /* Ensure string is terminated if length = MAX_FILENAME_LEN */
    file_name[MAX_FILENAME_LEN] = '\0';
}

bool MicrosoftMonoBMP_RT::set_size(unsigned int width, unsigned int height)
{
/*
 * Method sets the parameters ImageWidth and ImageHeight to width and height
 * and ensures that the memory allocated to raw_data is large enough to contain
 * this ammount of data. The method returns false if memory allocation is
 * unsuccessful and true otherwise.
 */

    bool ret_val ;

    /* First free memory currently associated with raw_data (if any) */ 
    delete raw_data ;    

    ImageWidth = width ;
    ImageHeight = height ;

    if(allocate_storage()){
    /* memory allocation was sucessful */
        ret_val = true ;
    }
    else{
        ret_val = false ;
    }

    calculate_filesize();
 
    return ret_val ;
}

bool MicrosoftMonoBMP_RT::read_byte(unsigned char *inp_chr)
{
/*
 * Reads a byte from stream pointed to by file_pnt into *inp_chr. Returns
 * false if cannot
 * read or invalid file pointer.
 */

    bool ret_val = true ;
    int char_read;
    if(file_pnt == NULL){
    /* Invalid file pointer */
        ret_val = false ;
    }
    else if( (char_read = fgetc(file_pnt)) == EOF){
    /* Could not read character from file */
        ret_val = false ;
    }
    else{
    /* Character read Ok */
        *inp_chr = (unsigned char) char_read ;
    }
    return ret_val ; 
}

bool MicrosoftMonoBMP_RT::read_word(unsigned int *inp_word)
{
/*
 * Reads a little endian word from stream pointed to by file_pnt into
 * *inp_word. Returns false if cannot read or invalid file pointer.
 */

    unsigned char inp1;
    unsigned char inp2;
    bool ret_val = true ;

    ret_val = read_byte(&inp1);
    
    if(ret_val){
    /* First byte read OK */
        ret_val = read_byte(&inp2);
    }

    if(ret_val){
    /* Both bytes read OK */
        *inp_word = inp1 + (((unsigned int)(inp2))<<8) ;
    }

    return ret_val ; 
}

bool MicrosoftMonoBMP_RT::read_dword(unsigned int *inp_word)
{
/*
 * Reads a little endian double word from stream pointed to by file_pnt into
 * *inp_word. Returns false if cannot read or invalid file pointer.
 */

    unsigned char inp1;
    unsigned char inp2;
    unsigned char inp3;
    unsigned char inp4;
    bool ret_val = true ;

    ret_val = read_byte(&inp1);
    
    if(ret_val){
    /* First byte read OK */
        ret_val = read_byte(&inp2);
    }

    if(ret_val){
    /* Second byte read OK */
        ret_val = read_byte(&inp3);
    }

    if(ret_val){
    /* Third byte read OK */
        ret_val = read_byte(&inp4);
    }

    if(ret_val){
    /* All 4 bytes read OK */
        *inp_word = (unsigned int)inp1 +
                    (((unsigned int)(inp2))<<8) +
                    (((unsigned int)(inp3))<<16) +
                    (((unsigned int)(inp4))<<24) ;
    }

    return ret_val ; 
}



bool MicrosoftMonoBMP_RT::write_byte(char chr)
{
/*
 * Writes a byte (chr) to stream pointed to by file_pnt. Returns
 * false if cannot write or invalid file pointer.
 */

    bool ret_val = true ;

    if(file_pnt == NULL){
    /* Invalid file pointer */
        ret_val = false ;
    }
    else if( fputc((int)chr, file_pnt) == EOF){
    /* Could not write character to file */
        ret_val = false ;
    }
    else{
    /* Character written Ok */
        ret_val = true ; 
    }

    return ret_val ; 
}

bool MicrosoftMonoBMP_RT::write_word(unsigned int wrd)
{
/*
 *  Writes a little endian word (wrd) to stream pointed to by file_pnt. 
 *  Returns false if cannot write or invalid file pointer.
 */

    unsigned int low_b;
    unsigned int hi_b;
    bool ret_val = true ;

    low_b = wrd&0xFF ;
    hi_b  = ( wrd >> 8 ) & 0xFF ;

    ret_val = write_byte((int)low_b);
    
    if(ret_val){
    /* First byte written OK */
        ret_val = write_byte((int)hi_b);
    }

    return ret_val ; 
}

bool MicrosoftMonoBMP_RT::write_dword(unsigned int wrd)
{
/*
 * Writes a little endian double word to stream pointed to by file_pnt. 
 * *inp_word. Returns false if cannot write or invalid file pointer.
 */

    char by1;
    char by2;
    char by3;
    char by4;
    bool ret_val = true ;

    by1 = wrd&0xFF ;
    by2 = ( wrd >> 8 ) & 0xFF ;
    by3 = ( wrd >> 16 ) & 0xFF ;
    by4 = ( wrd >> 24 ) & 0xFF ;
    ret_val = write_byte(by1);
    
    if(ret_val){
    /* First byte writtten OK */
        ret_val = write_byte(by2);
    }

    if(ret_val){
    /* Second byte written OK */
        ret_val = write_byte(by3);
    }

    if(ret_val){
    /* Third byte written OK */
        ret_val = write_byte(by4);
    }

    return ret_val ; 
}


bool MicrosoftMonoBMP_RT::allocate_storage()
{
/*
 * Allocates memory for raw_data based on ImageWidth and ImageHeight.
 */

    unsigned int storage_bytes_per_row;

    storage_bytes_per_row = ImageWidth / 8 ;


    if(ImageWidth & 0xF){
    /* Bits per row is not divisible by 8 */
        storage_bytes_per_row++ ;
    }

    raw_data = new char[storage_bytes_per_row * ImageHeight];

    if(raw_data==NULL) return false;
    else               return true;
}

void MicrosoftMonoBMP_RT::calculate_filesize()
{
/*
 * Calculates the filesize from ImageWidth and ImageHeight and stores this in 
 * FileSize.
 */

    unsigned int bytes_per_row;

    bytes_per_row = ImageWidth / 8 ;

    if(ImageWidth & 0xF){
    /* Bits per row is not divisible by 8 */
        bytes_per_row++ ;
    }

    while( bytes_per_row & 0x03 ){
    /* Bytes per row is not divisible by 4 */
        bytes_per_row++ ;
    }

    FileSize = bytes_per_row * ImageHeight + IMAGE_DATA_OFFSET_M ;
}

bool MicrosoftMonoBMP_RT::read()
{
/*
 * Method to read file data from file into the object 
 */

    bool ret_val = true ;
    unsigned int bytes_in=0;
    unsigned char *d_pointer;
    unsigned char pad;
    unsigned int line;
    unsigned int pixel;

    if((file_pnt = fopen(file_name,"rb"))==NULL){
    /* Could not open file */
        ret_val = false;
    }
    else{
    /* Read in header info */
        ret_val &= read_byte(&type1);
        ret_val &= read_byte(&type2);
        ret_val &= read_dword(&FileSize);
        ret_val &= read_dword(&reserved);
        ret_val &= read_dword(&data_off);
        ret_val &= read_dword(&head_size);
        ret_val &= read_dword(&ImageWidth);
        ret_val &= read_dword(&ImageHeight);
        ret_val &= read_word(&no_planes);
        ret_val &= read_word(&bits_per_pixel);
        ret_val &= read_dword(&comp_method);
        ret_val &= read_dword(&bitmap_size);
        ret_val &= read_dword(&HorizResolution);
        ret_val &= read_dword(&VertResolution);
        ret_val &= read_dword(&no_cols);
        ret_val &= read_dword(&no_sig_cols);

        /* Read in palette */
        ret_val &= read_byte(&pallete_false_b);
        ret_val &= read_byte(&pallete_false_g);
        ret_val &= read_byte(&pallete_false_r);
        ret_val &= read_byte(&pad);
        ret_val &= read_byte(&pallete_true_b);
        ret_val &= read_byte(&pallete_true_g);
        ret_val &= read_byte(&pallete_true_r);
        ret_val &= read_byte(&pad);
    }
    ret_val &= check_header_valid();

    if(ret_val){
    /* No problems so far */
       ret_val = allocate_storage();
    }
    if(ret_val){
    /* Read in data */
        d_pointer = (unsigned char *)raw_data ;

        for(line=0 ; line<ImageHeight && ret_val ; line ++){
 
            bytes_in = 0;
            for(pixel=0 ; pixel<ImageWidth / 8  && ret_val ; pixel ++){
                ret_val &= read_byte(d_pointer++);
                bytes_in++;
            }

            if(ImageWidth & 0xF){
            /* No of pixels is not divisible by 8 */
                ret_val &= read_byte(d_pointer++);
                bytes_in++;
            }

            while(bytes_in & 0x03){
            /* Discard padding */
                ret_val &= read_byte(&pad);
                bytes_in++;
            }
        }  
    }

    if( file_pnt == NULL ||
        fclose(file_pnt) == EOF ){
    /* Error closing file */
        ret_val = false ;
    }
    return ret_val;
}
         
bool MicrosoftMonoBMP_RT::check_header_valid()
{
/* 
 * Checks header of file is valid.
 */

    bool ret_val ;

    if( type1           != 'B'                  ||
        type2           != 'M'                  ||
        data_off        != IMAGE_DATA_OFFSET_M  ||
        head_size       != HEADER_SIZE_M        ||
        no_planes       != NO_OF_IMAGE_PLANES_M ||
        bits_per_pixel  != BITS_PER_PIXEL_M     ||           
        comp_method     != COMPRESSION_METHOD_M   ){
    /* Bitmap file header is invalid */
        ret_val = false ;
    }
    else{
        ret_val = true ;
    }
 
    return ret_val ;
}

#define NEXT_BIT bitmask = bitmask>>1; \
                 if(!bitmask) {bitmask=0x80 ; buff_pnt++;} 
               
void MicrosoftMonoBMP_RT::extract_data(int *rgb)
{
/*
 * Converts raw data from raw_data to RGB in the buffer rgb.
 * Note: Also flips the image vertically as bitmaps are stored upsidedown.
 */

    unsigned int lines;
    unsigned int pixels;
    unsigned int bytes_read;
    char     *buff_pnt = raw_data;
    unsigned int p_off;
    unsigned int bytes_per_line;
    unsigned char bitmask = 0x80;

    bytes_per_line = ImageWidth / 8 ;

    if(ImageWidth & 0xF){
    /* Bits per line is not divisible by 8 */
        bytes_per_line++;
    }
   
    p_off = (ImageWidth*ImageHeight);
 
    for(lines=0 ; lines<ImageHeight ; lines ++){
    /* For each line in the image */

        if(bitmask != 0x80){
        /* We are in the middle of a byte */
            bitmask = 0x80 ;
            buff_pnt++;
        }
         
        /* Set pointer to beginning of previous line */
        p_off -= ImageWidth ;

        /* Loop through pixels in the line */
        for(pixels=0; pixels<ImageWidth ; pixels++){

            if(*buff_pnt & bitmask){
                rgb[p_off*3] = pallete_true_r ;
                rgb[p_off*3+1] = pallete_true_g ;
                rgb[p_off*3+2] = pallete_true_b ;

            }
            else{
                rgb[p_off*3] = pallete_false_r ;
                rgb[p_off*3+1] = pallete_false_g ;
                rgb[p_off*3+2] = pallete_false_b ;
            }
            NEXT_BIT

            p_off++;
        }

        /* Set pointer to beginning of current line */
        p_off -= ImageWidth ;
    }
} 

void MicrosoftMonoBMP_RT::extract_data_grey(int *grey)
{
/*
 * Converts raw data from raw_data to greyscale in the buffer grey.
 * Note: Also flips the image vertically as bitmaps are stored upsidedown.
 */

    unsigned int lines;
    unsigned int pixels;
    unsigned int bytes_read;
    char     *buff_pnt = raw_data;
    unsigned int p_off;
    unsigned int bytes_per_line;
    unsigned char bitmask = 0x80;

    bytes_per_line = ImageWidth / 8 ;

    if(ImageWidth & 0xF){
    /* Bits per line is not divisible by 8 */
        bytes_per_line++;
    }

    p_off = (ImageWidth*ImageHeight);

    for(lines=0 ; lines<ImageHeight ; lines ++){
    /* For each line in the image */

        if(bitmask != 0x80){
        /* We are in the middle of a byte */
            bitmask = 0x80 ;
            buff_pnt++;
        }

        /* Set pointer to beginning of previous line */
        p_off -= ImageWidth ;

        /* Loop through pixels in the line */
        for(pixels=0; pixels<ImageWidth ; pixels++){

            if(*buff_pnt & bitmask){
                grey[p_off] = pallete_true_grey ;

            }
            else{
                grey[p_off] = pallete_false_grey ;
            }
            NEXT_BIT

            p_off++;
        }

        /* Set pointer to beginning of current line */
        p_off -= ImageWidth ;
    }
}

               
void MicrosoftMonoBMP_RT::put_data(int *rgb)
{
/*
 * Converts RGB data from the buffer rgb to raw bitmap data 
 * which is stored in the buffer raw_data.
 * Note: Also flips the image vertically as bitmaps are stored upsidedown.
 */

    unsigned int lines;
    unsigned int pixels;
    char *buff_pnt = raw_data;
    unsigned int p_off;
    unsigned char bitmask = 0x80 ;
   
    p_off = (ImageWidth*ImageHeight);
 
    for(lines=0 ; lines<ImageHeight ; lines ++){
    /* For each line in the image */

        if(bitmask != 0x80){
        /* We are in the middle of a byte */
            bitmask = 0x80 ;
            buff_pnt++;
        }

        /* Set pointer to beginning of previous line */
        p_off -= ImageWidth ;

        /* Loop through pixels in the line */
        for(pixels=0; pixels<ImageWidth ; pixels++){
            if(rgb[p_off*3] || rgb[p_off*3+1] || rgb[p_off*3+2]){
            /* Any component is true */
                *buff_pnt |= bitmask ;
            }
            else{
                *buff_pnt &= ~bitmask ;
            }
            NEXT_BIT
            
            p_off++;
        }

        /* Set pointer to beginning of current line */
        p_off -= ImageWidth ;
    }
} 

void MicrosoftMonoBMP_RT::put_data_grey(int *grey)
{
/*
 * Converts greyscale data from the buffer grey to raw bitmap data  
 * which is stored in the buffer raw_data.
 * Note: Also flips the image vertically as bitmaps are stored upsidedown.
 */

    unsigned int lines;
    unsigned int pixels;
    char *buff_pnt = raw_data;
    unsigned int p_off;
    unsigned char bitmask = 0x80 ;
  
    p_off = (ImageWidth*ImageHeight);

    for(lines=0 ; lines<ImageHeight ; lines ++){
    /* For each line in the image */

        if(bitmask != 0x80){
        /* We are in the middle of a byte */
            bitmask = 0x80 ;
            buff_pnt++;
        }

        /* Set pointer to beginning of previous line */
        p_off -= ImageWidth ;

        /* Loop through pixels in the line */
        for(pixels=0; pixels<ImageWidth ; pixels++){
            if(grey[p_off]){
            /* Component is true */
                *buff_pnt |= bitmask ;
            }
            else{
                *buff_pnt &= ~bitmask ;
            }
            NEXT_BIT

            p_off++;
        }

        /* Set pointer to beginning of current line */
        p_off -= ImageWidth ;
    }
} 


bool MicrosoftMonoBMP_RT::write()
{
/*
 * Method to write file data to file from the object 
 */

    bool ret_val = true ;
    unsigned int bytes_in=0;
    char *d_pointer;
    char pad;
    unsigned int line;
    unsigned int pixel;
    if((file_pnt = fopen(file_name,"wb"))==NULL){
    /* Could not open file */
        ret_val = false;
    }
    else{
    /* Write header info */
        ret_val &= write_byte('B');
        ret_val &= write_byte('M');
        ret_val &= write_dword(FileSize);
        ret_val &= write_dword(0);
        ret_val &= write_dword(IMAGE_DATA_OFFSET_M);
        ret_val &= write_dword(HEADER_SIZE_M);
        ret_val &= write_dword(ImageWidth);
        ret_val &= write_dword(ImageHeight);
        ret_val &= write_word(NO_OF_IMAGE_PLANES_M);
        ret_val &= write_word(BITS_PER_PIXEL_M);
        ret_val &= write_dword(COMPRESSION_METHOD_M);
        ret_val &= write_dword(SIZE_OF_BITMAP_M);
        ret_val &= write_dword(HorizResolution);
        ret_val &= write_dword(VertResolution);
        ret_val &= write_dword(NO_COLOURS_USED_M);
        ret_val &= write_dword(NO_SIGNIFICANT_COLS_M);

        /* Write palette */
	ret_val &= write_byte(pallete_false_b);
        ret_val &= write_byte(pallete_false_g);
        ret_val &= write_byte(pallete_false_r);
        ret_val &= write_byte(0);
	ret_val &= write_byte(pallete_true_b);
        ret_val &= write_byte(pallete_true_g);
        ret_val &= write_byte(pallete_true_r);
        ret_val &= write_byte(0);
    }

    if(ret_val){
    /* Write data */
    
        d_pointer = raw_data ;

        for(line=0 ; line<ImageHeight && ret_val ; line ++){
 
            bytes_in = 0;
            for(pixel=0 ; pixel<ImageWidth/8 && ret_val ; pixel ++){
                ret_val &= write_byte(*(d_pointer++));
                bytes_in++;
            }

            if(ImageWidth & 0xF){
            /* No of pixels is not divisible by 8 */
                ret_val &= write_byte(*(d_pointer++));
                bytes_in++;
            }

            while(bytes_in & 0x03){
            /* Pad with zeros */
                ret_val &= write_byte(0);
                bytes_in++;
            }
        }  
    }

    if( file_pnt == NULL ||
        fclose(file_pnt) == EOF ){
    /* Error closing file */
        ret_val = false ;
    }

    return ret_val;
}
         
