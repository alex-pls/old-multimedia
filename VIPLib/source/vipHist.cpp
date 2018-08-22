/** @file vipHist.cpp
 *
 * File containing methods for the 'vipHist' class.
 * The header for this class can be found in vipHist.h, check that file
 * for class description.
 *
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


 #include "vipHist.h"
 #include <math.h>

 #include <stdio.h>
 #include <fstream>



vipHist::vipHist()
 {
	freqHist = NULL;
	probHist = NULL;
	Chist = NULL;
	reset();
 }

vipHist::vipHist(int MinValue, int MaxValue)
 {
	freqHist = NULL;
	probHist = NULL;
	Chist = NULL;
	reset(MinValue, MaxValue);
 }


vipHist::vipHist(vipFrameYUV420& img, vipFrameYUV420::ChannelYUV channel)
 {
	freqHist = NULL;
	probHist = NULL;
	Chist = NULL;

	fromImage(img, channel);
 }

vipHist::vipHist(vipFrameRGB24& img, vipFrameRGB24::ChannelRGB channel)
 {
	freqHist = NULL;
	probHist = NULL;
	Chist = NULL;

	fromImage(img, channel);
 }

vipHist::~vipHist()
 {

	if ( freqHist != NULL )
		delete [] freqHist;

	if ( probHist != NULL )
		delete [] probHist;

//BUG		
/*
	if ( Chist != NULL )
		delete [] Chist;
*/
 }



VIPRESULT vipHist::reset()
 {

	valMax = 0;
	valMin = 0;
	valBandwidth = 0;
	valCount = 0;

	valSum = 0;
	valSum2 = 0;

	if ( freqHist != NULL )
		delete [] freqHist;

	freqMax = 0;
	freqMin = 0;

	if ( probHist != NULL )
		delete [] probHist;

	probMax = 0;
	probMin = 0;

	if ( Chist != NULL )
		delete [] Chist;

	freqHist = NULL;
	probHist = NULL;
	Chist = NULL;

	return VIPRET_OK;
 }


VIPRESULT vipHist::reset(int MinValue, int MaxValue)
 {
	reset();
	valMax = MaxValue;
	valMin = MinValue;
	valCount = 0;

	valBandwidth = abs(valMax - valMin+1);

	if ( freqHist != NULL )
		delete [] freqHist;
	freqHist = new unsigned int[valBandwidth];

	freqMax = 0;
	freqMin = 0;

	if ( probHist != NULL )
		delete [] probHist;
	probHist = new float[valBandwidth];

	probMax = 0;
	probMin = 0;

	for (int i=0; i < valBandwidth; i++)
	 {
		probHist[i] = 0.0;
		freqHist[i] = 0;
	 }

	return VIPRET_OK;
 }

VIPRESULT vipHist::addValue(int data)
 {
	if ( data < valMin || data > valMax)
		return VIPRET_PARAM_ERR;

	if ( valBandwidth == 0 )
		return VIPRET_ILLEGAL_USE;

	int offset = data - valMin;

	freqHist[offset]++;
	valCount++;

	valSum  += data;
	valSum2 += data * data;


	if ( freqMax < freqHist[offset])
		freqMax = freqHist[offset];

	if ( freqMin > freqHist[offset])
		freqMin = freqHist[offset];

	return VIPRET_OK;
 }

VIPRESULT vipHist::addData(int *data, int size)
 {

	if ( data == NULL || size == 0)
		return VIPRET_PARAM_ERR;

	if ( valBandwidth == 0 )
		return VIPRET_ILLEGAL_USE;

	int offset;
	for (int i=0; i<size; i++)
	 {
		offset = data[i] - valMin;

		freqHist[offset]++;
		valCount++;

		valSum  += data[i];
		valSum2 += data[i] * data[i];

		if ( freqMax < freqHist[offset])
			freqMax = freqHist[offset];

		if ( freqMin > freqHist[offset])
			freqMin = freqHist[offset];
 	 }

	return VIPRET_OK;

 }


VIPRESULT vipHist::fromImage(vipFrameYUV420& img, vipFrameYUV420::ChannelYUV channel)
 {
	reset( 0, (int)pow((float)2.0, (float) (1<<sizeof(int)) ) );

	unsigned int offset;
	unsigned int start, end;

	if ( channel == vipFrameYUV420::Lum )
	 {
		start = 0;
		end = img.width*img.height;
	 }
	else if ( channel == vipFrameYUV420::Cb )
	 {
		start = img.width*img.height;
		end = (unsigned int)(img.width*img.height*1.25);
	 }
	else if ( channel == vipFrameYUV420::Cr )
	 {
		start = img.width*img.height;
		end = (unsigned int)(img.width*img.height*1.5);
	 }
	else
	 {
		reset();
		return VIPRET_PARAM_ERR;
	 }
	for (unsigned int i=start; i<end; i++)
	 {

		offset = img.data[i];

		freqHist[offset]++;
		valCount++;

		valSum  += offset;
		valSum2 += offset * offset;

		if ( freqMax < freqHist[offset])
			freqMax = freqHist[offset];

		if ( freqMin > freqHist[offset])
			freqMin = freqHist[offset];

	 }

	 extractProbs();
	 extractChist();

	 return VIPRET_OK;

 }


VIPRESULT vipHist::fromImage(vipFrameRGB24& img, vipFrameRGB24::ChannelRGB channel)
 {
//	reset( 0, (int)pow((float)2.0, (float) (1<<sizeof(unsigned char)) ) );
	reset( 0, 255 );

//        int temp = 1<<sizeof(char);
//printf("%d", temp);

	int offset;

	for (unsigned int i=0; i<img.width*img.height; i++)
	 {
		offset = (unsigned int)img.data[i][channel];

		freqHist[offset]++;
		valCount++;

		valSum  += offset;
		valSum2 += offset * offset;

		if ( freqMax < freqHist[offset])
			freqMax = freqHist[offset];

		if ( freqMin > freqHist[offset])
			freqMin = freqHist[offset];

	 }

	 extractProbs();
	 extractChist();

	 return VIPRET_OK;
 }




VIPRESULT vipHist::extractProbs()
/**
 * Calculate histogram probabilities (probs) from frequencies (frequency_data)
 */
{
	if ( freqHist == NULL || probHist == NULL )
		return VIPRET_ILLEGAL_USE;

	if ( valBandwidth == 0 )
		return VIPRET_ILLEGAL_USE;


	probMax = 0;
	probMin = 1;

	for (int i=0; i < valBandwidth; i++)
	 {
		probHist[i] = (float)freqHist[i] / (float)valCount;

		if ( probHist[i] > probMax )
			probMax = probHist[i];

		if ( probHist[i] < probMin )
			probMin = probHist[i];

	 }

	return VIPRET_OK;
}




float vipHist::extractDifference(vipHist *compareHist)
/**
 * Returns mean absolute difference between histograms. Histograms must have
 * same dimensionality and bands_per_dim.
 *
 * @param hist Pointer to Histogram to compare with this object
 */
{

	if ( valBandwidth == 0 )
		return VIPRET_ILLEGAL_USE;

	extractProbs();
	compareHist->extractProbs();

	float diffTmp = 0;
	float diff = 0;

	for (int i=0; i < valBandwidth; i++)
	 {
		diffTmp = probHist[i] - compareHist->probHist[i];

		if ( diffTmp < 0.0 )
			diff -= diffTmp;
		else
			diff += diffTmp;

	 }

    return diff;
}


float vipHist::getMean() const
{
  return valSum/(double)valCount;
}

float vipHist::getVariance() const
{
  float n = (double)valCount;
  return (n*valSum2 - valSum*valSum)/(n*n);
}

/*
float vipHist::getEntropy() const
{
  const float log2c = log(2.0);
  float* px = new float [xNbins];
  unsigned long int i;
  for (i = 0; i < xNbins; i++)
    px[i] = (1.0/(float)valCount)*(float)data[i];

  float entropy = 0.0;
  for (i = 0; i < xNbins; i++)
    if (px[i] != 0.0)
      entropy -= px[i]*log(px[i])/log2c;

  delete [] px;

  return entropy;
}
*/








/**
* @brief calculates the values of the cumulative histogram for vipHist class.
*
* @param[in]
*
* @return VIPRET_OK if everything is fine, VIPRET_ILLEGAL_USE if probHist is NULL.
*/

 VIPRESULT vipHist::extractChist()
{
	if (probHist == NULL ) {
		return VIPRET_ILLEGAL_USE;
	}

	if (Chist != NULL) {
		delete [] Chist;
	}

	Chist = new float[255];

	float temp = 0.0;

	for (int i=0; i < 256; i++)
	{
		temp += probHist[i];
		Chist[i] = temp;
	}

	return VIPRET_OK;
 }








unsigned char	graphBackground[] =	{  12,23

								};

VIPRESULT vipHist::drawGraph(vipFrameRGB24& img)
 {
//assert 400x400
	unsigned int upperBorder = 35;//<img.height
	unsigned int bottomBorder = 45;//<img.height
	unsigned int leftBorder = 100;//<img.width-255
	bool fillCol = true;

	if (img.width < leftBorder+255)
		return VIPRET_ILLEGAL_USE;

	if ( freqHist == NULL )
		return VIPRET_ILLEGAL_USE;

	PixelRGB24 black(0,0,0);
	PixelRGB24 grey(192,192,192);
	PixelRGB24 back(255,255,255);

	img.clearWith(back);

	unsigned int y;
	float scale = (float)(img.height-(upperBorder+bottomBorder)) / (float)freqMax;
	unsigned int offset = img.height * img.width - bottomBorder * img.width + leftBorder;

printf("value %d\n" , offset);

	for (unsigned int x=0; x<255; x++)
	 {
		y = (unsigned int)( (float)freqHist[x] * scale);
//printf("value %d" , y);
//setpixel ( x+leftBorder, img.height-y-bottomBorder)
//		img.data[x+leftBorder   +  (img.height-y-bottomBorder) * img.width] = black;
		img.data[offset + x - y * img.width] = black;

		if (fillCol)
			while (y++ < (img.height-upperBorder-bottomBorder))
				img.data[offset + x - y * img.width] = grey;

	 }

	return VIPRET_OK;
 }




VIPRESULT vipHist::saveToXML(const char* filename)
/**
 * Saves histogram data to an (XML format) file.
 */
{
    FILE *fp;
	int ret = VIPRET_OK;

	if ( valBandwidth == 0 )
    	return VIPRET_INTERNAL_ERR;

    if ( (fp = fopen(filename, "w")) == NULL )
    	return VIPRET_PARAM_ERR;

    ret = extractProbs();

    if ( ret != VIPRET_OK )
    	return ret;

    if( fprintf(fp, "<?xml version=\"1.0\" ?>\n\n") == EOF )
	 {
		fclose(fp);
		return VIPRET_INTERNAL_ERR;
	 }

    if( fprintf(fp, "<histogram value-count=\"%i\" min-value=\"%i\" max-value=\"%i\">\n", valCount, valMin, valMax) == EOF )
	 {
	    fclose(fp);
    	return VIPRET_INTERNAL_ERR;
	 }

	if (!extractProbs())
		for (int i=0; i < valBandwidth; i++)
		 {
			if ( fprintf(fp, "  <prob index=\"%u\">%f</prob>\n", i, probHist[i]) == EOF)
		    	ret = VIPRET_INTERNAL_ERR;
	     }
	else
    	ret = VIPRET_INTERNAL_ERR;

    if ( fprintf(fp, "</histogram>\n") == EOF)
    	ret = VIPRET_INTERNAL_ERR;

    fclose(fp);

	return ret;
 }


VIPRESULT vipHist::loadFromXML(const char* filename)
/**
 * Loads histogram from a (XML format) file.
 */
{
    FILE *fp;
	int ret = VIPRET_OK;

    if ( (fp=fopen(filename,"r")) == NULL )
    	return VIPRET_PARAM_ERR;

    int n;  // return values for fscanf, set to number of items read

    /* xml version string */

    float xmlversion = 0;

    n = fscanf(fp, "<?xml version=\"%f\" ?>\n\n", &xmlversion);

    if (xmlversion == 0)
    	throw "Incompatible hst file format";


    /* histogram attributes */

    n = fscanf(fp, "<histogram value-count=\"%i\" min-value=\"%i\" max-value=\"%i\">\n", &valCount, &valMin, &valMax);

    if (n != 4)
    	throw "error in hst file, unable to import data.";

	reset(valMin, valMax);

    unsigned int i = 0;
    float p = 0;

    while (n == 2)
     {
        n = fscanf(fp, "  <prob index=\"%u\">%f</prob>\n", &i, &p);
        probHist[i] = p;
     }


    char last[2];
    n = fscanf(fp, "/histogram%[>]", last);

    if (n != 1)
        throw "Reading hst file.";

    fclose(fp);

    return ret;
 }
