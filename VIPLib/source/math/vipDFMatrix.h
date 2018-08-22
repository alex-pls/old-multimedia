/**
 *  @class   vipDFMatrix
 *
 *  @brief   Class designed for Digital Filters' Kernel.
 *           It's a n*n matrix of chars + normalization char,
 *           so: char[n*n+1].
 *           For complex operations or different items types
 *           use class vipMatrix (normalization = sum is managed) .
 *           Included a set of default kernels (call createKernel_3x3).
 *
 *  @bug
 *  @warning
 *  @todo
 *
 *  @see     vipDigitalFilter
 *  @see     vipMatrix
 *  @example ../tests/test_vipDigitalFilter.cpp
 *
 *  @version 1.0.2
 *  @date    19/09/2005
 *  @author  Alessandro Polo
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



#ifndef __VIPLIB_VIPDFMATRIX_H__
 #define __VIPLIB_VIPDFMATRIX_H__

 #include "../vipDefs.h"
 #include <stdio.h>
 #include <fstream>



// for default filters
	#define VETDF_3x3_average			8700
	#define VETDF_3x3_mean_removal		8701
	#define VETDF_3x3_gaussian			8702
	#define VETDF_3x3_lowpass1			8703
	#define VETDF_3x3_lowpass2			8704
	#define VETDF_3x3_lowpass3			8705
	#define VETDF_3x3_highpass1			8706
	#define VETDF_3x3_highpass2			8707
	#define VETDF_3x3_highpass3			8708
	#define VETDF_3x3_edge_sd_h			8709
	#define VETDF_3x3_edge_sd_v			8710
	#define VETDF_3x3_edge_sd_hv		8711
	#define VETDF_3x3_laplacian1		8712
	#define VETDF_3x3_laplacian2		8713
	#define VETDF_3x3_laplacian3		8714
	#define VETDF_3x3_diagonal			8715
	#define VETDF_3x3_horizontal		8716
	#define VETDF_3x3_vertical			8717
	#define VETDF_3x3_east				8718
	#define VETDF_3x3_west				8719
	#define VETDF_3x3_north				8720
	#define VETDF_3x3_south				8721
	#define VETDF_3x3_south_east		8722
	#define VETDF_3x3_south_west		8723
	#define VETDF_3x3_north_east		8724
	#define VETDF_3x3_north_west		8725
	#define VETDF_3x3_sobel_h			8726
	#define VETDF_3x3_sobel_v			8727
	#define VETDF_3x3_prewitt_h			8728
	#define VETDF_3x3_prewitt_v			8729
	#define VETDF_3x3_emboss_east		8730
	#define VETDF_3x3_emboss_west		8731
	#define VETDF_3x3_emboss_south		8732
	#define VETDF_3x3_emboss_north		8733
	#define VETDF_3x3_emboss_south_east	8734
	#define VETDF_3x3_emboss_south_west	8735
	#define VETDF_3x3_emboss_north_east	8736
	#define VETDF_3x3_emboss_north_west	8737


class vipDFMatrix
 {
	protected:

		char* data;
		char* norm;

		unsigned int dim;



		void setDim(unsigned int size)
		 {
			dim = size;
			data = new char[size*size+1];
			norm = data+size*size;
		 };

	public:

		vipDFMatrix()
		 {
			data = NULL;
			norm = NULL;
			dim = 0;
		 };

		vipDFMatrix(char* array, unsigned int size, bool doCopy = false)
		 {
			if (doCopy && size)
			 {
				data = new char[size*size+1];
				memcpy(data, array, (size*size+1) * sizeof(char));
			 }
			else
				data = array;

			dim = size;
			norm = data+size*size;
		 };

		vipDFMatrix(const char* filename)
		 {
			data = NULL;
			norm = NULL;
			dim = 0;
			loadFromFile(filename);
		 };

		vipDFMatrix(FILE *fp)
		 {
			data = NULL;
			norm = NULL;
			dim = 0;
			loadFromStream(fp);
		 };


		~vipDFMatrix()
		 {
			if (data != NULL)              //BUGGGGGGGG
				delete [] data;
		 };

		char* dup_data() { return data; };
		unsigned int getDim() { return dim; };



		/**
		 * Overloaded array operator.
		 *
		 * This operator allows easy access to the data of the pixel as
		 * if you were refering to the data directly.
		 *
		 * @param i The index of the field to return.
		 *
		 * @return The value of the field.
		 */
		char& operator [] (int i)
		{
			return data[i];
		};

		/**
		 * Overloaded array operator.
		 *
		 * This operator allows easy access to the data of the pixel as
		 * if you were refering to the data directly.
		 *
		 * @param i The index of the field to return.
		 *
		 * @return The value of the field.
		 */
		const char& operator [] (int i) const
		{
			return data[i];
		};






		VIPRESULT saveToFile(const char* filename)
		 {
			FILE *fp;
			int ret = VIPRET_OK;

			if ( data == NULL )
				return VIPRET_ILLEGAL_USE;

			if ( (fp = fopen(filename, "w")) == NULL )
				return VIPRET_PARAM_ERR;


			ret = saveToStream(fp);

			fclose(fp);

			return ret ;
		 };



		VIPRESULT loadFromFile(const char* filename)
		 {
			FILE *fp;
			int ret = VIPRET_OK;

			if ( (fp=fopen(filename,"r")) == NULL )
				return VIPRET_PARAM_ERR;

			ret = loadFromStream(fp);

			fclose(fp);

			return ret;
		 };

		VIPRESULT saveToStream(FILE *fp)
		 {
			if ( data == NULL )
				return VIPRET_ILLEGAL_USE;

			if( fprintf(fp, "%u\n", dim) == EOF )
				return VIPRET_INTERNAL_ERR;

                        int ret = VIPRET_OK;


//			for (unsigned int i=0; i < dim*dim+1; i++)
				if ( fprintf(fp, "%s ", data) == EOF)
					ret = VIPRET_INTERNAL_ERR;

			if ( fprintf(fp, "\n") == EOF )
				ret = VIPRET_INTERNAL_ERR;

			return ret;
		 };


		VIPRESULT loadFromStream(FILE *fp)
		 {
			unsigned int newDim = 0;

			if ( fscanf(fp,"%u\n",&newDim) == EOF )
				return VIPRET_INTERNAL_ERR;

			setDim(newDim);

//			char tmpValue[1];
                        int ret = VIPRET_OK;

//			for (unsigned int i=0; i < newDim * newDim+1; i++)
				if( fscanf(fp, "%s", data) == EOF )
					ret = VIPRET_INTERNAL_ERR;
//				else
//					data[i] = *tmpValue;

			return ret;
		 };


		static vipDFMatrix* createKernel_3x3(int index)
		 {

#include "../filters/vipDigitalFilters.def"

			vipDFMatrix* ret = new vipDFMatrix(defaulFilters_3x3[index - VETDF_3x3_average], 3, true);
			return ret;
		 };


 };

#endif //__VIPLIB_VIPDFMATRIX_H__

