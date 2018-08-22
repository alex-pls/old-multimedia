/** @file    test_vipInputIDWT.cpp
 *
 *  @brief   Testing code for class vipInputIDWT.
 *
 *
 *
 *
 *  @bug
 *
 *  @warning
 *  @note
 *
 *  @see     vipInputIDWT
 *
 *  @version 1.0
 *  @date    28/02/2008 10.17.35
 *  @author  Valentina Pasqualino
 *
 ****************************************************************************
 *  Source based on Package Studio template: vipInputTemplate version 0.9.12
 ****************************************************************************
 * VIPLib Framework
 *  open source, founded by Alessandro Polo 2006
 *  http://mmlab.science.unitn.it/projects/VIPLib
 *
 *  maintained by MultiMedia Laboratory - DIT - University of Trento
 *
 ****************************************************************************/


//---------------------------------------------------------------------------

#pragma hdrstop

//---------------------------------------------------------------------------

#include "../../source/vipFrameYUV420.h"
#include "../../source/vipFrameRGB24.h"
#include "../../source/outputs/vipDoctor.h"
#include "../../source/codecs/vipCodec_BMP.h"
#include "vipInputIDWT.h"



//---------------------------------------------------------------------------
#include <stdio.h>

int main(int argc, char* argv[])
 {

	printf("Testing vipInputIDWT Development...\n");

	printf("\nCreating Instances...\n");
	
	
	
	vipMatrix<double> imgsrc;
	
	
	imgsrc.loadFromFile("prova.txt");

	vipFrameRGB24 img;

	vipInputIDWT myInputClass(&img, 0);
	

	
	myInputClass.setIteration(1); // 0 = filter 5/3; 1 = filter 9/7
	myInputClass.setFilter(1);

	myInputClass>>img;

	
	

	printf("\nSaving frames...\n");

	vipCodec_BMP::save(img, "antitrasformata.bmp", vipCodec_BMP::FORMAT_BMP_24);
	

	printf("Test Completed. Type something to continue...\n");
	getchar();



	return 0;
 }



