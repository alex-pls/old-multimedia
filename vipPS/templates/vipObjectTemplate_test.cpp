/** @file    test_%CLASSNAME%.cpp
 *
 *  @brief   Testing code for class %CLASSNAME%.
 *
 *
 *
 *
 *  @bug
 *
 *  @warning
 *  @note
 *
 *  @see     %CLASSNAME%
 *
 *  @version %VERSION%
 *  @date    %TODAY%
 *  @author  %AUTHOR%
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

#include "%CLASSNAME%.h"


//---------------------------------------------------------------------------
#include <stdio.h>




int main(int argc, char* argv[])
 {

	printf("Testing %CLASSNAME% Development...\n");

	printf("\nCreating Instances...\n\n");
	%CLASSNAME% myClassInst;

	printf("Name: \t\t%s\n", myClassInst.getName() );
	printf("Description: \t%s\n", myClassInst.getDescription() );
	printf("version: \t%f\n", myClassInst.getVersion() );

%EFI_START%
	printf("\nCalling reset(), returned: %d\n", myClassInst.reset() );
%EFI_END%

	printf("\nTest Completed. Type something to continue...\n");
	getchar();

	return 0;
 }




