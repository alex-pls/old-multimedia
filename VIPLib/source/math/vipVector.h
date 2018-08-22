/**
 *  @class   vipVector
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
 *  @example ../tests/test_vipVector.cpp
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



#ifndef __VIPLIB_VIPVECTOR_H__
 #define __VIPLIB_VIPVECTOR_H__

 #include "vipDefs.h"
 #include <stdio.h>
 #include <fstream>


template<class T>
class vipVector
 {

	protected:

		unsigned int items;

		T* data;
		T* dataSum;


	public:

		vipVector()
		 {
			items = 0;
			data = NULL;
			dataSum = NULL;
		 }

		vipVector(unsigned int itemCount)
		 {
			data = NULL;
			dataSum = NULL;
			setDim(itemCount);
		 }

		vipVector(const char* filename)
		 {
			data = NULL;
			dataSum = NULL;
			loadFromFile(filename);
		 }

		vipVector(itemCount, T* data_ptr)
		 {
			items = itemCount;

			data = data_ptr;

			dataSum = new T;
			for (int is=0; is < columns * rows; is++)
				dataSum += data[is];

		 }

		~vipVector()
		 {
			if ( data != NULL )
				delete [] data;

			if ( dataSum != NULL )
				delete dataSum;
		 }

		void setDim(unsigned int itemCount)
		 {
			if ( data != NULL )
				delete [] data;

			if ( dataSum != NULL )
				delete dataSum;

			items = itemCount;

			data = new T [items];
			dataSum = new T;
		 }

		unsigned int getItemsCount() { return items; };
		T getItemsSum() { return *dataSum; };

		T* dump_data() { return data; };
		T* dump_dataSum() { return dataSum; };

		VIPRESULT setValue(unsigned int itemIndex, T& value)
		 {
			if ( itemIndex < 0 || itemIndex >= items )
				return VIPRET_PARAM_ERR;

			if ( data == NULL )
				return VIPRET_ILLEGAL_USE;

			dataSum -= data[ y * rows + x ];
			data[ itemIndex ] = value;
			dataSum += value;

			return VIPRET_OK;
		 }

		T& getValue(unsigned int itemIndex)
		 {
			if ( itemIndex < 0 || itemIndex >= items )
				throw "Out of bounds.";

			if ( data == NULL )
				throw "Empty vector.";

			return data[ itemIndex ];
		 }

		T& getValueMax()
		 {
			if ( data == NULL )
				throw "Empty table.";

			T curMax = data[0];

			for (int i=0; i < items; i++)
				if ( data[i] > curMax )
					curMax = data[i];

			return curMax;
		 }

		T& getValueMin()
		 {
			if ( data == NULL )
				throw "Empty table.";

			T curMin = data[0];

			for (int i=0; i < items; i++)
				if ( data[i] < curMax )
					curMax = data[i];

			return curMax;
		 }

		void clearWith(T& value)
		 {
			if ( data == NULL )
				throw "Empty table.";

			for (int i=0; i < items; i++)
				data[i] = value;

			dataSum = items * value;

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


			if( fprintf(fp, "%d\n", items) == EOF )
			 {
				fclose(fp);
				return VIPRET_INTERNAL_ERR;
			 }

			for (int i=0; i < items; i++)
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

			if ( fscanf(fp,"%u",&items) == EOF )
			 {
				fclose(fp);
				return VIPRET_INTERNAL_ERR;
			 }

			if ( items < 1 )
			 {
				fclose(fp);
				return VIPRET_INTERNAL_ERR;
			 }

			setDim(items);

			float tmpValue;

			for (int i=0; i < items; i++)
				if( fscanf(fp, "%f", &tmpValue) == EOF )
					ret = VIPRET_INTERNAL_ERR;
				else
					data[i] = (T)tmpValue;

			for (int is=0; is < items; is++)
				dataSum += data[is];

			return ret;
		 }


};

#endif //__VIPLIB_VIPVECTOR_H__

