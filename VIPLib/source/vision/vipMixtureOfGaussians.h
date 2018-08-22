/**
 *  @class   vipMixtureOfGaussians
 *
 *  @brief   This module provides a Mixture of Gaussians statistical modeling tool.
 *			 This can typically be used for background modeling in a motion detection
 *			 application. Uses HSV colorspace input (vipFrameHSV).
 *
 *
 *  @bug
 *  @warning
 *  @todo
 *
 *  @version 0.2
 *  @date    25/09/2008
 *  @author  Marco Verza
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


#ifndef _VIPLIB_VIPMIXTUREOFGAUSSIANS_H
#define _VIPLIB_VIPMIXTUREOFGAUSSIANS_H


 #include "../vipObject.h"
 #include "../vipFrameHSV.h"
 #include "../vipInput.h"
 #include "../vipOutput.h"
 #include "../math/vipStatistics.h"
 #include <math.h>


 #define MOG_FOREGROUND_OUTVAL	255
 #define MOG_BACKGROUND_OUTVAL	0

////// When output mode is graylevel (not binary), these values are used to mark shadows/reflexes.
 #define MOG_SHADOW_GRAYLEVEL	64
 #define MOG_REFLEX_GRAYLEVEL	180


// Definitions: default values.
 #define MATCH_MODE_DEFAULT	vipMixtureOfGaussiansParameters::MATCH_FAST
 #define DEFAULT_BG_CHAN	CHANNEL_V	// application dependant. default should tipically be CHANNEL_V
 #define SHAD_ALPHA_DEFAULT	0.00		// 0.4 for Cucchiara Grana Piccardi in some of their test sequences
 #define SHAD_BETA_DEFAULT	2.00		// 0.6
 #define TH_SHAD_S_DEFAULT	150			// 0.5
 #define TH_SHAD_H_DEFAULT	150			// 0.5
 
 #define REFL_ALPHA_DEFAULT	0.0			// 0.70 according to approx autotuning
 #define REFL_BETA_DEFAULT	10			// 1.20 according to approx autotuning
 #define TH_REFL_S_DEFAULT	80			// 20 according to approx autotuning
 #define TH_REFL_H_DEFAULT	110			// 10 according to approx autotuning

const float pi = (float) 3.14159;

class vipMixtureOfGaussiansParameters
{
public:
	vipMixtureOfGaussiansParameters()	// Def. constr.
	{
		verbosity = 1;
		inputMode = INPUT_TRAINING;
		outputMode = OUTPUT_BINARY;
		matchChan = DEFAULT_BG_CHAN;
		bShadowDetectEnabled = false;
		bReflexDetectEnabled = false;
		ucShadowOutValue = 0;
		ucReflexOutValue = 0;
	}
	~vipMixtureOfGaussiansParameters()		// Def. destr.
	{
	}
	enum MATCHING_MODE { MATCH_FAST, MATCH_ACCURATE };	// Two possible modes: fast or accurate. I recommend fast. Because accurate is not accurate atm. :/
	enum INPUT_MODE { INPUT_TRAINING, INPUT_SUBTRACTION };	// Two possible modes for HSV input (operator<<): training or bgsub. You tipically start with training and then switch over to bgsub.
	enum OUTPUT_MODE { OUTPUT_BINARY, OUTPUT_GRAYSCALE };	// Two possible modes for uchar output: BINARY or GRAYLEVEL. You tipically want binary output. Graylevel is used to visually debug and/or decide thresholds.
	enum MATCH_CHANNEL { CHANNEL_H, CHANNEL_S, CHANNEL_V, CHANNEL_ALL }; // Which channel(s) to compare when matching pixels

	// Member access methods
	void setMatchingMode( MATCHING_MODE mode ) { matchMode = mode; }
	MATCHING_MODE getMatchingMode() { return matchMode; }
	void setMatchingChannel( MATCH_CHANNEL chan ) { matchChan = chan; }
	MATCH_CHANNEL getMatchingChannel() { return matchChan; }
	void setVerbosity( int verb ) { verbosity = verb; }
	int getVerbosity() { return verbosity; }
	void setInputMode( INPUT_MODE mode ) { inputMode = mode; }
	INPUT_MODE getInputMode() { return inputMode; }
	void setOutputMode( OUTPUT_MODE mode ); // implemented in cpp
	OUTPUT_MODE getOutputMode() { return outputMode; }
	void setShadowDetection( bool bActive ) { bShadowDetectEnabled = bActive; }
	bool isShadowDetectionEnabled() { return bShadowDetectEnabled; }
	void setReflexDetection( bool bActive ) { bReflexDetectEnabled = bActive; }
	bool isReflexDetectionEnabled() { return bReflexDetectEnabled; }



	// Options, thresholds, and other configurable thingies... public for now. TODO: protected + access methods.
public:
	bool			WinTakeAll;	// Winner takes it all mode
	unsigned int	K;			// Number of gaussians
	float			alpha;		// Learning coefficient
	float			v0;			// Init value for variances
	float			th_var;		// Variance threshold (for bg training and matching)
	float			shadAlpha;	// Lower bound for shadow detection purposes. Range: [0,1]
	float			shadBeta;	// Upper bound for shadow detection purposes. Range: [0,1]
	float			th_shad_s;	// Threshold for Sat., shadow detection purposes
	float			th_shad_h;	// Threshold for Hue, shadow detection purposes
	float			reflAlpha;	// Lower bound for reflex detection purposes. Range: [0,1]
	float			reflBeta;	// Upper bound for reflex detection purposes. Range: [0,1]
	float			th_refl_s;	// Threshold for Sat., reflex detection purposes
	float			th_refl_h;	// Threshold for Hue, reflex detection purposes
	unsigned int	uiUseModelUpdate;	// enable(!=0)/disable(0) bg model update every uiUseModelUpdate frames


protected:
	friend class	vipMixtureOfGaussians;
	MATCHING_MODE	matchMode;	// Can be FAST or ACCURATE. For some reason at the moment FAST is more accurate than ACCURATE. 
	MATCH_CHANNEL	matchChan;	// The H,S or V channel used for matching pixels. Tipically you want to use V. If you use CHANNEL_ALL, for each pixel the minimum of H,S,V matching results is used.
	INPUT_MODE		inputMode;	// Can be Training or BgSubtraction.
	OUTPUT_MODE		outputMode;	// Can be Binary or Grayscale. Only affects foreground output with shadow/reflex detection enabled.
	int				verbosity;	// 0 = no stdout at all. well, nearly.
	bool			bShadowDetectEnabled;	// Flag to enable/disable shadow detection
	bool			bReflexDetectEnabled;	// Flag to enable/disable reflex detection
	unsigned char	ucShadowOutValue;	// 0 if outputMode is BINARY
	unsigned char	ucReflexOutValue;	// 0 if outputMode is BINARY
};






class vipGaussian
{
public:

	/**
	* @brief  Default constructor.
	*/
	vipGaussian();

	/**
	* @brief  Class constructor that actually initializes the gaussian and allocates memory.
	*/
	vipGaussian( unsigned int Width, unsigned int Height );		

	/**
	* @brief  Default destructor.
	*/
	~vipGaussian();


	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////// Member variables /////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////

	/**
	* @var  Width of the processed frames.
	*/
	unsigned int	width;

	/**
	* @var  Height of the processed frames.
	*/
	unsigned int	height;

	/**
	* @var  Array of floats representing this gaussian's variance for color component H. Length of array is width*height.
	*/
	float*			h_var;

	/**
	* @var  Array of floats representing this gaussian's variance for color component S. Length of array is width*height.
	*/
	float*			s_var;

	/**
	* @var  Array of floats representing this gaussian's variance for color component V. Length of array is width*height.
	*/
	float*			v_var;

	/**
	* @var  Array of floats representing this gaussian's mean for color component H. Length of array is width*height.
	*/
	float*			h_mean;

	/**
	* @var  Array of floats representing this gaussian's mean for color component S. Length of array is width*height.
	*/
	float*			s_mean;

	/**
	* @var  Array of floats representing this gaussian's mean for color component V. Length of array is width*height.
	*/
	float*			v_mean;

	/**
	* @var  Counter for the number of effective observations for this Gaussian. Zero count means empty (untrained or unused) gaussian.
	*/
	float			count;

	/**
	* @var  Learning rate for this Gaussian.
	*/
	float			learn_rate;

	/**
	* @var  Array of floats representing this gaussian's pixel-wise weight. High weight means many successful matches during the training (i.e., stable background). Length of array is width*height.
	*/
	float*			weight;



	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////// Helper methods ///////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	/**
	* @brief  Initialize gaussian's parameters and allocate memory according to Width and Height.
	*/
	void			Init( unsigned int Width, unsigned int Height );

	/**
	* @brief  Free all data, set pointers to null.
	*/
	void			freeData();

	/**
	* @brief  Probability density function.
	*/
	float			ProbDensityFunct( unsigned int x, unsigned int pixindex, vipMixtureOfGaussiansParameters::MATCH_CHANNEL channel );

	/**
	* @brief  Cumulative density function.
	*/
	float			CumulDensityFunct( unsigned int x, unsigned int pixindex, vipMixtureOfGaussiansParameters::MATCH_CHANNEL channel );

	/**
	* @brief  Estimate the probability as difference of cumulative density functions in the x-0.5,x+0.5 interval.
	*/
	float			ProbabilityEstimate( unsigned int x, unsigned int pixindex, vipMixtureOfGaussiansParameters::MATCH_CHANNEL channel );

	/**
	* @brief  Return an estimate of how well the input pixel matches ("fits in") the background model, according to the MoG configured modes and parameters.
	*/
	float			TryMatch( PixelHSV pix, unsigned int pixindex, float th_var, vipMixtureOfGaussiansParameters::MATCH_CHANNEL channel, vipMixtureOfGaussiansParameters::MATCHING_MODE mode );

	/**
	* @brief  Update the background model with a single pixel, with the same logic as it was fed in during the training phase.
	*/
	void			UpdateWith( PixelHSV pix, unsigned int pixindex );
};




class vipMixtureOfGaussians		:	public vipInput,
									public vipOutput,
									public vipObject
{
public:

	/**
	* @brief  Class constructor.
	*/
	vipMixtureOfGaussians( unsigned int number_gaussians_K, float Alpha, float V0, float Th_Var, unsigned int Width, unsigned int Height, unsigned int UpdateBgModel=10 );	// Default constructor

	/**
	* @brief  Default class destructor.
	*/
	~vipMixtureOfGaussians();	// Default destructor



	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////// Member variables /////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////

	/**
	* @var  Pointer to the gaussians' array. Size of the array is myParams->K.
	*/
	vipGaussian		*gaussians;	// Pointer to the gaussians array of size K

	/**
	* @var  Pointer to the uchar array of length (width*height) representing the extracted foreground, i.e. result of the background subtraction.
	*/
	unsigned char	*foreground;

	/**
	* @var  Frame width for the processing video, and therefore width of the background model, foreground, etc.
	*/
	unsigned int	width;

	/**
	* @var  Frame height for the processing video, and therefore width of the background model, foreground, etc.
	*/
	unsigned int	height;


	// Statistics and counters...
public:
	unsigned int	uiLastShadowCount;		// Latest count of shadow pixels detected during latest BackgroundSubtraction().
	unsigned int	uiLastReflexCount;		// Latest count of reflex pixels detected during latest BackgroundSubtraction().
	unsigned int	uiLastForegroundCount;	// Latest count of foreground pixels detected during latest BackgroundSubtraction(). Shadow and reflex pixels are not considered foreground.


	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////// Helper methods ///////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////


	/**
	* @brief  Prints a small table of current MoG's gaussians' statuses to stdout. Called for each input given, if verbosity is not zero.
	*/
	void			PrintDebug();

	/**
	* @brief  Prints a small table of current MoG's thresholds to stdout.
	*/
	void			PrintThresholdsInfo();

	/**
	* @brief  Prints the counters of latest backgroundsubtraction detections to stdout.
	*/
	void			PrintStatistics();


	/**
	* @brief  Performs background model training with the input HSV frame.
	*/
	VIPRESULT		Training( vipFrameHSV &input );

	/**
	* @brief  Performs the background subtraction on the input frame, internally storing the result map. If doBgProcNow==true, also performs BackgroundProcessing().
	* @see	  BackgroundProcessing()
	*/
	VIPRESULT		BackgroundSubtraction( vipFrameHSV &input, bool doBgProcNow = false );

	/**
	* @brief  Returns the index of the gaussian having the minimum weight at pixel pixindex.
	*/
	unsigned int	GetMinWeightIndex( unsigned int pixindex );

	/**
	* @brief  Returns the index of the gaussian having the maximum weight at pixel pixindex.
	*/
	unsigned int	GetMaxWeightIndex( unsigned int pixindex );

	/**
	* @brief  Returns the index of the gaussian having the maximum count.
	*/
	unsigned int	GetMaxCountIndex();

	/**
	* @brief  Returns the index of the gaussian having the minimum count.
	*/
	unsigned int	GetMinCountIndex();

	/**
	* @brief  Performs normalization to 1 of all gaussians' weights at pixel pixindex.
	*/
	void			NormalizeWeights( unsigned int pixindex );

	/**
	* @brief  Performs a weak cleanup of sparse single and 2x2 points on the internally stored foreground, or on the input target. May also be called by BackgroundSubtraction(). 
	*/
	unsigned int	BackgroundProcess( unsigned char *target = NULL, bool bTrimFrameEdges = true );

	/**
	* @brief  Tells if the input pixel is a shadow for any of the gaussians, according to the current thresholds and background model.
	*/
	bool			IsShadowPixel( PixelHSV pix, unsigned int pixindex );

	/**
	* @brief  Tells if the input pixel is a reflex for any of the gaussians, according to the current thresholds and background model.
	* @bug	  Not working so good.
	*/
	bool			IsReflexPixel( PixelHSV pix, unsigned int pixindex );

	/**
	* @brief  Calls directly extractTo(vipFrameT<unsigned char> &img), which copies current subtracted foreground to img.
	*/
	VIPRESULT		operator >> (vipFrameT<unsigned char> &img);

	/**
	* @brief  Not implemented.
	*/
	VIPRESULT		operator << (vipFrameT<unsigned char> &img);

	/**
	* @brief  Calls directly extractTo(vipFrameHSV &img), which copies to img the current BG MEAN MODEL with the highest pixel-wise weight, i.e. mean values of each pixel is taken from the gaussian with the highest weight on that pixel.
	*/
	VIPRESULT		operator >> (vipFrameHSV &img);

	/**
	* @brief  Calls directly importFrom(vipFrameHSV &img), which performs BackgroundSubtraction(img) or Training(img) depending on the input mode currently set.
	*/
	VIPRESULT		operator << (vipFrameHSV &img);





	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////// Inherited methods ////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////

	/**
	* @brief  Returns the model width.
	*/
	unsigned int	getWidth() const { return width; }

	/**
	* @brief  Returns the model height.
	*/
	unsigned int	getHeight() const { return height; }

	/**
	* @brief  Sets the model width to value.
	*/
	VIPRESULT		setWidth( unsigned int value ) { width = value; return VIPRET_OK; }

	/**
	* @brief  Sets the model height to value.
	*/
	VIPRESULT		setHeight( unsigned int value ) { height = value; return VIPRET_OK; }

	/**
	* @brief  Resets background model (all counters, weights, etc.). Does not reset parameters (make a new MoG if you need that). Also, not deeply tested, use with caution.
	*/
	VIPRESULT		reset();// { return VIPRET_NOT_IMPLEMENTED; }

	/**
	* @brief  Not applicable. But hey, it's inherited. Will just return false.
	*/
	bool			EoF() { return false; }

	/**
	* @brief  Copies current subtracted foreground to img.
	*/
	VIPRESULT		extractTo( vipFrameT<unsigned char> &img );

	/**
	* @brief  Copies to img the current BG MEAN MODEL with the highest pixel-wise weight, i.e. mean values of each pixel is taken from the gaussian with the highest weight on that pixel.
	*/
	VIPRESULT		extractTo( vipFrameHSV &img );

	/**
	* @brief  This method performs BackgroundSubtraction() or Training() depending on the input mode currently set.
	*/
	VIPRESULT		importFrom( vipFrameHSV &img );

	/**
	* @brief  Not implemented.
	*/
	VIPRESULT		extractTo( vipFrameYUV420 &img ) { return VIPRET_NOT_IMPLEMENTED; }		// not implemented (useless) methods

	/**
	* @brief  Not implemented.
	*/
	VIPRESULT		extractTo( vipFrameYUV444 &img ) { return VIPRET_NOT_IMPLEMENTED; }

	/**
	* @brief  Not implemented.
	*/
	VIPRESULT		extractTo( vipFrameRGB24 &img ) { return VIPRET_NOT_IMPLEMENTED; }

	/**
	* @brief  Not implemented.
	*/
	VIPRESULT		importFrom( vipFrameYUV420 &img ) { return VIPRET_NOT_IMPLEMENTED; }

	/**
	* @brief  Not implemented.
	*/
	VIPRESULT		importFrom( vipFrameYUV444 &img ) { return VIPRET_NOT_IMPLEMENTED; }

	/**
	* @brief  Not implemented.
	*/
	VIPRESULT		importFrom( vipFrameRGB24 &img ) { return VIPRET_NOT_IMPLEMENTED; }

	/**
	* @brief  Not implemented.
	*/
	VIPRESULT		importFrom( vipFrameT<unsigned char> &img ) { return VIPRET_NOT_IMPLEMENTED; }


	/**
	* @brief  Returns a pointer to myParams.
	*/
	vipMixtureOfGaussiansParameters* getParams() { return myParams; }

protected:

	/**
	* @var  Pointer to the vipMixtureOfGaussiansParameters instance.
	*/
	vipMixtureOfGaussiansParameters *myParams;

};

#endif // _VIPLIB_VIPMIXTUREOFGAUSSIANS_H