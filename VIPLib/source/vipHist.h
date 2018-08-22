/**
 *  @class   vipHist
 *
 *  @brief
 *
 *
 *
 *
 *  @bug
 *  @warning
 *  @todo
 *
 *  @see
 *  @example ../tests/test_vipHist.cpp
 *
 *  @version 0.6
 *  @date    12/07/2005 - //2005
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




#ifndef __VIPLIB_VIPHIST_H__
 #define __VIPLIB_VIPHIST_H__

#include <iostream>
using namespace std;


 #include "vipDefs.h"
 #include "vipFrameYUV420.h"
 #include "vipFrameRGB24.h"



class vipHist
 {
	protected:

		int valMax;
		int valMin;
		int valBandwidth;
		unsigned int valCount;

		double valSum;
		double valSum2;

		unsigned int* freqHist;

		unsigned int freqMax;
		unsigned int freqMin;

		float* probHist;

		float probMax;
		float probMin;

		float * Chist;


	public:


		vipHist();
		vipHist(int MinValue, int MaxValue);
		vipHist(vipFrameYUV420& img, vipFrameYUV420::ChannelYUV channel);
		vipHist(vipFrameRGB24& img, vipFrameRGB24::ChannelRGB channel);

		vipHist(char const* filename);

		~vipHist();

		VIPRESULT reset();
		VIPRESULT reset(int MinValue, int MaxValue);

		VIPRESULT addValue(int value);
		VIPRESULT addData(int *data, int size);

		VIPRESULT fromImage(vipFrameYUV420& img, vipFrameYUV420::ChannelYUV channel);
		VIPRESULT fromImage(vipFrameRGB24& img, vipFrameRGB24::ChannelRGB channel);


		unsigned int* dumpFrequency() { return freqHist; };
		float* dumpProbabilities() { return probHist; };
		/**
		* @brief return the value of Chist
		*
		* @param[in]
		*
		* @return pointer to float     
		*/
		float* dumpChist() { return Chist; };


		vipHist& operator = (vipHist& rvalue);

		int getValBandWidth() { return valBandwidth; };
		unsigned int getMinFrequencyValue() { return freqMin; };
		unsigned int getMaxFrequencyValue() { return freqMax; };
		float getMinProbabilityValue() { return probMin; };
		float getMaxProbabilityValue() { return probMax; };

		VIPRESULT extractProbs();
		float extractDifference(vipHist *compareHist);

		unsigned int getValCount() { return valCount; };

		//Return sample mean
		float getMean() const;
		//Return sample variance
		float getVariance() const;


		VIPRESULT drawGraph(vipFrameRGB24& img);


		VIPRESULT saveToXML(char const* filename);
		VIPRESULT loadFromXML(char const* filename);
		
		/**
		* @brief calculates the values of the cumulative histogram for vipHist class.
		*
		* @param[in]
		*
		* @return VIPRET_OK if everything is fine, VIPRET_ILLEGAL_USE if probHist is NULL.       
		*/

		VIPRESULT extractChist();

 };



#endif //__VIPLIB_VIPHIST_H__

