/**
 *  @class   vipMatrix
 *
 *  @brief   Matrix Template for common uses in VIPLibb.
 *           Data is sequenced as raster-scan.
 *           Serialization uses floating point format.
 *
 *  @bug
 *  @warning
 *  @todo
 *
 *  @see
 *  @example ../tests/test_vipMatrix.cpp
 *
 *  @version 1.0.2
 *  @date    15/09/2005
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



#ifndef __VIPLIB_VIPMATRIX_H__
 #define __VIPLIB_VIPMATRIX_H__

 #include "../vipDefs.h"
 #include <stdio.h>
 #include <fstream>


template<class T>
class vipMatrix
 {

	protected:

		unsigned int rows;
		unsigned int columns;

		T* data;
		T* dataSum;


	public:

		vipMatrix()
		 {
			rows = 0;
			columns = 0;
			data = NULL;
			dataSum = NULL;
		 }

		vipMatrix(unsigned int colCount, unsigned int rowCount)
		 {
			rows = 0;
			columns = 0;
			data = NULL;
			dataSum = NULL;
			setDim(colCount, rowCount);
		 }

		vipMatrix(const char* filename)
		 {
			rows = 0;
			columns = 0;
			data = NULL;
			dataSum = NULL;
			loadFromFile(filename);
		 }

		vipMatrix(unsigned int colCount, unsigned int rowCount, T* data_ptr)
		 {
			rows = rowCount;
			columns = colCount;

			data = data_ptr;

			dataSum = new T;
			for (int is=0; is < columns * rows; is++)
				*dataSum += data[is];

		 }

		~vipMatrix()
		 {
			if ( data != NULL )
				delete [] data;

			if ( dataSum != NULL )
				delete dataSum;
		 }

		void setDim(unsigned int colCount, unsigned int rowCount)
		 {
			if ( data != NULL )
				delete [] data;

			if ( dataSum != NULL )
				delete dataSum;

			rows = rowCount;
			columns = colCount;

			data = new T [rows*columns];
			dataSum = new T;
		 }

		unsigned int getRowsCount() { return rows; };
		unsigned int getColumnsCount() { return columns; };
		unsigned int getItemsCount() { return columns*rows; };


		T getItemsSum() { return *dataSum; };

		T* dump_data() { return data; };

		T* dump_dataSum() { return dataSum; };


		VIPRESULT setValue(unsigned int x, unsigned int y, T& value)
		 {
			if ( x < 0 || y < 0 || x >= columns || y >= rows )
				return VIPRET_PARAM_ERR;

			if ( data == NULL )
				return VIPRET_ILLEGAL_USE;


			*dataSum -= data[ y * columns + x ];
			data[ y * columns + x ] = value;
			*dataSum += value;

			return VIPRET_OK;
		 }

		T& getValue(unsigned int x, unsigned int y)
		 {
			if ( x < 0 || y < 0 || x >= columns || y >= rows )
				throw "Out of bounds.";

			if ( data == NULL )
				throw "Empty table.";

			return data[ y * columns + x ];
		 }

		T& getValueMax()
		 {
			if ( data == NULL )
				throw "Empty table.";

			T curMax = data[0];

			for (int i=0; i < columns * rows; i++)
				if ( data[i] > curMax )
					curMax = data[i];

			return curMax;
		 }

		T& getValueMin()
		 {
			if ( data == NULL )
				throw "Empty table.";

			T curMin = data[0];

			for (int i=0; i < columns * rows; i++)
				if ( data[i] < curMin )
					curMin = data[i];

			return curMin;
		 }

		void clearWith(T& value)
		 {
			if ( data == NULL )
				throw "Empty table.";

			for (int i=0; i < columns * rows; i++)
				data[i] = value;

			*dataSum = columns * rows * value;

		 }


//		T& operator() (unsigned int i, unsigned int j);




		VIPRESULT saveToFile(const char* filename)
		 {
			FILE *fp;
			int ret = VIPRET_OK;

			if ( data == NULL )
				return VIPRET_ILLEGAL_USE;

			if ( (fp = fopen(filename, "w")) == NULL )
				return VIPRET_PARAM_ERR;


			if( fprintf(fp, "%d %d\n", rows, columns) == EOF )
			 {
				fclose(fp);
				return VIPRET_INTERNAL_ERR;
			 }

			for (int i=0; i < columns * rows; i++)
				if ( fprintf(fp, "%f ", (float)data[i]) == EOF)
					ret = VIPRET_INTERNAL_ERR;

			if ( fprintf(fp, "\n") == EOF )
				ret = VIPRET_INTERNAL_ERR;

			fclose(fp);
			return ret ;
		 }



		VIPRESULT loadFromFile(const char* filename)
		 {
			FILE *fp;
			int ret = VIPRET_OK;

			if ( (fp=fopen(filename,"r")) == NULL )
				return VIPRET_PARAM_ERR;

			unsigned int newRows = 0;
			unsigned int newCols = 0;

			if ( fscanf(fp,"%u",&newRows) == EOF )
			 {
				fclose(fp);
				return VIPRET_INTERNAL_ERR;
			 }

			if ( fscanf(fp,"%u",&newCols) == EOF )
			 {
				fclose(fp);
				return VIPRET_INTERNAL_ERR;
			 }

			if ( newRows <= 0 || newCols <= 0 )
			 {
				fclose(fp);
				return VIPRET_INTERNAL_ERR;
			 }

			setDim(newRows, newCols);


			float tmpValue;

			for (int i=0; i < newRows * newCols; i++)
				if( fscanf(fp, "%f", &tmpValue) == EOF )
					ret = VIPRET_INTERNAL_ERR;
				else
					data[i] = (T)tmpValue;

			for (int is=0; is < newRows * newCols; is++)
				*dataSum += data[is];

			fclose(fp);
			return ret;
		 }


		// Method added by Marco Verza on 5 august 2008. I only need this so I wont waste time coding a generalized matrix multiply.. sorry
		static VIPRESULT multiply_3x3_3x1( vipMatrix<float> *mat_3x3, vipMatrix<float> *mat_3x1, vipMatrix<float> *out_mat_3x1 )
		{
			float val;
			VIPRESULT ret = 0;
			out_mat_3x1->setDim(1,3);

			val =	mat_3x3->getValue(0,0) * mat_3x1->getValue(0,0) +
					mat_3x3->getValue(1,0) * mat_3x1->getValue(0,1) +
					mat_3x3->getValue(2,0) * mat_3x1->getValue(0,2) ;
			ret |= out_mat_3x1->setValue(0,0, val);

			val =	mat_3x3->getValue(0,1) * mat_3x1->getValue(0,0) +
					mat_3x3->getValue(1,1) * mat_3x1->getValue(0,1) +
					mat_3x3->getValue(2,1) * mat_3x1->getValue(0,2) ;
			ret |= out_mat_3x1->setValue(0,1, val);

			val =	mat_3x3->getValue(0,2) * mat_3x1->getValue(0,0) +
					mat_3x3->getValue(1,2) * mat_3x1->getValue(0,1) +
					mat_3x3->getValue(2,2) * mat_3x1->getValue(0,2) ;
			ret |= out_mat_3x1->setValue(0,2, val);

			return ret;
		}

};

#endif //__VIPLIB_VIPMATRIX_H__

