/**
 *  @file    Some Bit and frame logic operations functions (standalone)
 *
 *  @brief

 *  @bug
 *  @warning
 *  @todo    To Be Commented
 *
 *  @see
 *
 *  @version 1.0.0
 *  @date    27/09/2007
 *  @author  Nicola Piotto (written)
 *           Alessandro Polo (moved into library)
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

#ifndef __VIPLIB_VIPLOGIC_H__
 #define __VIPLIB_VIPLOGIC_H__

#include <vipDefs.h>



int Logic_AND(unsigned char* in1, unsigned char*in2, int width, int height, unsigned char* out);

int Logic_DIFF(unsigned char* in1, unsigned char* in2, unsigned char* in3, int width, int height, unsigned char* out);

int Logic_DIFF(unsigned char* in1, unsigned char* in2,int width, int height, unsigned char* out);



// to be tested, one is actually used in the vipTracker

int array_cmp(int* in1, int nrlabel, int value);

int array_cmp(unsigned char* in1, int nrlabel, unsigned char value);


int array_cmp(unsigned char* in1, int nrlabel, unsigned char value);



#endif //__VIPLIB_VIPLOGIC_H__





