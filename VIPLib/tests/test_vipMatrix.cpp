/** @file    test_vipMatrix.cpp
 *
 *  @brief   Testing code for class vipMatrix.
 *
 *           vipMatrix template class is designed for filters'
 *           and plugins' developing, this simple code tests an
 *           integer matrix, populates the matrix incrementing
 *           value (a[0,0] = 0, a[10,10] = 99), serializes matrix
 *           to a file and tests also data loading to a new int matrix,
 *           then prints the cloned matrix to stdout.
 *
 *
 *  @see     vipMatrix
 *
 *  @version 1.0
 *  @date    15/08/2005
 *  @author  Alessandro Polo
 *
 *
 ****************************************************************************
 * VIPLib Framework
 *  open source, founded by Alessandro Polo 2006
 *  http://mmlab.science.unitn.it/projects/VIPLib
 *
 *  maintained by MultiMedia Laboratory - DIT - University of Trento
 *
 ****************************************************************************/


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

#include "../source/math/vipMatrix.h"

#include <stdio.h>



int main(int argc, char* argv[])
 {
	printf("Testing vipMatrix Development...\n");

	int x, y;

	printf("\nCreating Instances...\n");
	vipMatrix<int> intTable(10, 10);

	
	printf("\nPopulating Matrix...\n");
	int temp;
	for (y=0; y<10; y++)
		for (x=0; x<10; x++)
		 {
			temp = x+y*10;
			intTable.setValue(x, y, temp);
		 }


	printf("\nPrinting Matrix...\n");
	for (y=0; y<10; y++)
	 {
		for (x=0; x<10; x++)
			printf("%d ", intTable.getValue(x, y) );

		printf("\n");
	 }


	printf("Saving Matrix...\n");
	intTable.saveToFile("matrix.data");

	printf("\nCreating a new Matrix loading data...\n");
	vipMatrix<int> intTableCopy("matrix.data");

	printf("\nPrinting Matrix...\n");
	for (y=0; y<10; y++)
	 {
		for (x=0; x<10; x++)
			printf("%d ", intTableCopy.getValue(x, y) );

		printf("\n");
	 }


	printf("Test Completed. Type something to continue...\n");
	getchar();

	return 0;
 }
//---------------------------------------------------------------------------
