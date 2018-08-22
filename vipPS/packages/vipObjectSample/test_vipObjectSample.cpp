/** @file    test_vipObjectSample.cpp
 *
 *  @brief   Testing code for class vipObjectSample.
 *
 *
 *
 *
 *  @bug
 *
 *  @warning
 *  @note
 *
 *  @see     vipObjectSample
 *
 *  @version 1.0
 *  @date    19/05/2006 7.26.11
 *  @author  Alessandro Polo
 *
 ****************************************************************************
 *  Source based on Package Studio template: vipObjectTemplate version 0.9.12
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

#include "vipObjectSample.h"


//---------------------------------------------------------------------------
#include <stdio.h>




int main(int argc, char* argv[])
 {

	printf("Testing vipObjectSample Development...\n");

	printf("\nCreating Instances...\n\n");
	vipObjectSample myClassInst;

	printf("Name: \t\t%s\n", myClassInst.getName() );
	printf("Description: \t%s\n", myClassInst.getDescription() );
	printf("version: \t%f\n", myClassInst.getVersion() );


	printf("\nCalling reset(), returned: %d\n", myClassInst.reset() );


	printf("\nTest Completed. Type something to continue...\n");
	getchar();

	return 0;
 }




