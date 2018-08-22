/** @file vipMixtureOfGaussians.cpp
 *
 * File containing methods for the 'vipMixtureOfGaussians' and 'vipGaussian' classes.
 * The header for this class can be found in vipMixtureOfGaussians.h, check that file
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


#include "vipMixtureOfGaussians.h"
#include "../filters/vipFilterMorphological.h"


vipGaussian::vipGaussian()
{
}

vipGaussian::vipGaussian( unsigned int Width, unsigned int Height )
{
	Init( Width, Height );
}

void vipGaussian::Init( unsigned int Width, unsigned int Height )
{
	width = Width;
	height = Height;
	unsigned int PixTot = Width*Height;

	h_var = new float[PixTot];		// Gaussian variance for color component H, will be properly initialized to v0 by MoG constructor
	s_var = new float[PixTot];		// Gaussian variance for color component S, will be properly initialized to v0 by MoG constructor
	v_var = new float[PixTot];		// Gaussian variance for color component V, will be properly initialized to v0 by MoG constructor

	h_mean = new float[PixTot];		// Gaussian mean for color component H, initialize to +Inf
	s_mean = new float[PixTot];		// Gaussian mean for color component S, initialize to +Inf
	v_mean = new float[PixTot];		// Gaussian mean for color component V, initialize to +Inf
	weight = new float[PixTot];		// Weight of this gaussians' individual pixels
	memset( weight, 0,	 PixTot*sizeof(float) );

	count = 0;		// Counter for the number of effective observations for this Gaussian
	learn_rate = 0;	// Learning rate for this Gaussian
}

void vipGaussian::freeData()
{
	if( h_var != NULL )
		delete[] h_var;
	h_var = NULL;
	if( s_var != NULL )
		delete[] s_var;
	s_var = NULL;
	if( v_var != NULL )
		delete[] v_var;
	v_var = NULL;

	if( h_mean != NULL )
		delete[] h_mean;
	h_mean = NULL;
	if( s_mean != NULL )
		delete[] s_mean;
	s_mean = NULL;
	if( v_mean != NULL )
		delete[] v_mean;
	v_mean = NULL;

	if( weight != NULL )
		delete[] weight;
	weight = NULL;
}

vipGaussian::~vipGaussian()
{
	freeData();
}

float vipGaussian::TryMatch( PixelHSV pix, unsigned int pixindex, float th_var, vipMixtureOfGaussiansParameters::MATCH_CHANNEL channel, vipMixtureOfGaussiansParameters::MATCHING_MODE mode )
{
	float *used_chan_var, *used_chan_mean;
	unsigned short used_pix;

	switch( channel )
	{
	case vipMixtureOfGaussiansParameters::CHANNEL_H:
		{
			used_chan_var	= h_var;
			used_chan_mean	= h_mean;
			used_pix		= pix.hue;
		}
		break;
	case vipMixtureOfGaussiansParameters::CHANNEL_S:
		{
			used_chan_var	= s_var;
			used_chan_mean	= s_mean;
			used_pix		= pix.sat;
		}
		break;
	case vipMixtureOfGaussiansParameters::CHANNEL_V:
		{
			used_chan_var	= v_var;
			used_chan_mean	= v_mean;
			used_pix		= pix.val;
		}
		break;
	case vipMixtureOfGaussiansParameters::CHANNEL_ALL:	// recursive
		{
			// return the minimum of the 3 match values for channels H,S,V
			float minRetVal =			TryMatch( pix, pixindex, th_var, vipMixtureOfGaussiansParameters::CHANNEL_H, mode );
			minRetVal = min( minRetVal,	TryMatch( pix, pixindex, th_var, vipMixtureOfGaussiansParameters::CHANNEL_S, mode ) );
			minRetVal = min( minRetVal,	TryMatch( pix, pixindex, th_var, vipMixtureOfGaussiansParameters::CHANNEL_V, mode ) );
			return minRetVal;
		}
	default:
		{
			used_chan_var	= v_var;
			used_chan_mean	= v_mean;
			used_pix		= pix.val;
		}
		break;
	}

	// Now we can act FAST or ACCURATE.
	float ret;
	if( mode == vipMixtureOfGaussiansParameters::MATCH_FAST )
	{
		float diff = used_pix-used_chan_mean[pixindex];
		if( channel==vipMixtureOfGaussiansParameters::CHANNEL_H && diff > 180 )
			diff = 360 - diff;		// angular diff for H

		//if( abs(diff) > th_var && used_chan_var[pixindex] <= 1)	// preliminary check for faster matching... seems like it slows down actually.
		//	return 0;
		if( ( abs(diff) / sqrt(used_chan_var[pixindex]) ) < th_var )	// check VAL for now
			return 1;
		else
			return 0;
	}
	else	// MOG_MODE_ACCURATE
	{
		float diff = used_pix-used_chan_mean[pixindex];
		if( channel==vipMixtureOfGaussiansParameters::CHANNEL_H && diff > 180 )
			diff = 360 - diff;		// angular diff for H
		
		if( ( abs(diff) / sqrt(used_chan_var[pixindex]) ) < th_var )	// check VAL for now
			ret = ( weight[pixindex] * ProbabilityEstimate(used_pix,pixindex,channel) );
		else
			return 0;

		return ret;
	}
}

float vipGaussian::ProbDensityFunct( unsigned int x, unsigned int pixindex, vipMixtureOfGaussiansParameters::MATCH_CHANNEL channel )
{
	float *used_chan_var, *used_chan_mean;

	switch( channel )
	{
	case vipMixtureOfGaussiansParameters::CHANNEL_H:
		{
			used_chan_var	= h_var;
			used_chan_mean	= h_mean;
		}
		break;
	case vipMixtureOfGaussiansParameters::CHANNEL_S:
		{
			used_chan_var	= s_var;
			used_chan_mean	= s_mean;
		}
		break;
	case vipMixtureOfGaussiansParameters::CHANNEL_V:
		{
			used_chan_var	= v_var;
			used_chan_mean	= v_mean;
		}
		break;
	default:
		{
			used_chan_var	= v_var;
			used_chan_mean	= v_mean;
		}
		break;
	}

	float a;
	a = (float) ( 1/(sqrt(used_chan_var[pixindex]*2*pi)) * pow( (float)2.71828, (0-pow(x-used_chan_mean[pixindex],2)/(2*used_chan_var[pixindex])) ) );
	return a;
}

float vipGaussian::CumulDensityFunct(unsigned int x, unsigned int pixindex, vipMixtureOfGaussiansParameters::MATCH_CHANNEL channel )
{	// tested formula for a dozen values, seems to work properly
	float *used_chan_var, *used_chan_mean;

	switch( channel )
	{
	case vipMixtureOfGaussiansParameters::CHANNEL_H:
		{
			used_chan_var	= h_var;
			used_chan_mean	= h_mean;
		}
		break;
	case vipMixtureOfGaussiansParameters::CHANNEL_S:
		{
			used_chan_var	= s_var;
			used_chan_mean	= s_mean;
		}
		break;
	case vipMixtureOfGaussiansParameters::CHANNEL_V:
		{
			used_chan_var	= v_var;
			used_chan_mean	= v_mean;
		}
		break;
	default:
		{
			used_chan_var	= v_var;
			used_chan_mean	= v_mean;
		}
		break;
	}

	float diff = x-used_chan_mean[pixindex];
	if( channel==vipMixtureOfGaussiansParameters::CHANNEL_H && diff > 180 )
		diff = 360 - diff;		// angular diff for H

	float retval = (float) ( 0.5 * ( 1 + vipStatistics::erf(diff/sqrt(2*used_chan_var[pixindex])) ) );
	return retval;
}

float vipGaussian::ProbabilityEstimate(unsigned int x, unsigned int pixindex, vipMixtureOfGaussiansParameters::MATCH_CHANNEL channel )
{
	return CumulDensityFunct( (unsigned int)(x+0.5), pixindex, channel ) - CumulDensityFunct( (unsigned int)(x-0.5), pixindex, channel );
}

void vipGaussian::UpdateWith( PixelHSV pix, unsigned int pixindex )
{
#ifdef _DEBUG
	if( learn_rate == 0 )
		printf("debug: wasting cpu time in vipGaussian::UpdateWith().\n");
#endif
	// Update mean and variance for each component
	h_var[pixindex] = (1-learn_rate) * h_var[pixindex] + learn_rate * pow( pix.hue - h_mean[pixindex], 2 );
	s_var[pixindex] = (1-learn_rate) * s_var[pixindex] + learn_rate * pow( pix.sat - s_mean[pixindex], 2 );
	v_var[pixindex] = (1-learn_rate) * v_var[pixindex] + learn_rate * pow( pix.val - v_mean[pixindex], 2 );
	h_mean[pixindex] = (1-learn_rate) * h_mean[pixindex] + learn_rate * pix.hue;
	s_mean[pixindex] = (1-learn_rate) * s_mean[pixindex] + learn_rate * pix.sat;
	v_mean[pixindex] = (1-learn_rate) * v_mean[pixindex] + learn_rate * pix.val;
}


vipMixtureOfGaussians::vipMixtureOfGaussians( unsigned int number_gaussians_K, float Alpha, float V0, float Th_Var, unsigned int Width, unsigned int Height, unsigned int UpdateBgModel )
{	// Initializations...

	if( number_gaussians_K == 0 )
		throw("Please dont allocate MoG with 0 gaussians.");

	myParams = new vipMixtureOfGaussiansParameters();
	myParams->setMatchingMode( MATCH_MODE_DEFAULT );
	myParams->setInputMode( vipMixtureOfGaussiansParameters::INPUT_TRAINING );

	myParams->K = number_gaussians_K;
	gaussians = new vipGaussian[myParams->K];
	for( unsigned int k=0; k<myParams->K; k++ )
	{
		gaussians[k].Init(Width,Height);
		//gaussians[k].learn_rate = Alpha; // even if init at 0 in vipGaussian constr, should be then updated by training
	}
	foreground = new unsigned char[(unsigned int)(Width*Height)];

	myParams->alpha = Alpha;
	myParams->v0 = V0;
	myParams->th_var = Th_Var;
	myParams->WinTakeAll = true;
	width = Width;
	height = Height;
	unsigned int framesize = width*height;

	// shadow detection variables initializations
	myParams->shadAlpha = (float) SHAD_ALPHA_DEFAULT;
	myParams->shadBeta = (float) SHAD_BETA_DEFAULT;
	myParams->th_shad_h = (float) TH_SHAD_H_DEFAULT;
	myParams->th_shad_s = (float) TH_SHAD_S_DEFAULT;
	// reflex detection variables initializations
	myParams->reflAlpha = (float) REFL_ALPHA_DEFAULT;
	myParams->reflBeta = (float) REFL_BETA_DEFAULT;
	myParams->th_refl_h = (float) TH_REFL_H_DEFAULT;
	myParams->th_refl_s = (float) TH_REFL_S_DEFAULT;


	for( unsigned int i=0; i<myParams->K; i++ )
	{ // initialize variance values to v0, and mean values to 0
		for( unsigned int pixindex = 0; pixindex < framesize; pixindex++ )
		{
			gaussians[i].h_var[pixindex] = myParams->v0;
			gaussians[i].s_var[pixindex] = myParams->v0;
			gaussians[i].v_var[pixindex] = myParams->v0;
			gaussians[i].h_mean[pixindex] = -1;
			gaussians[i].s_mean[pixindex] = -1;
			gaussians[i].v_mean[pixindex] = -1;
		}
	}

	myParams->uiUseModelUpdate = UpdateBgModel;	// update bg model (by default every 10 frames)
}

vipMixtureOfGaussians::~vipMixtureOfGaussians()
{
	if( gaussians != NULL )
		delete[] gaussians;

	if( foreground != NULL )
		delete[] foreground;

	if( myParams != NULL )
		delete myParams;
}

/* TODO comment */
unsigned int vipMixtureOfGaussians::GetMinWeightIndex( unsigned int pixindex )
{ // returns the index of the gaussian with minimum weight
	unsigned int index = 0;
	float curr_min = gaussians[0].weight[pixindex];

	for( unsigned int i=0; i<myParams->K; i++ )
	{
		if( gaussians[i].weight[pixindex] < curr_min )
		{
			curr_min = gaussians[i].weight[pixindex];
			index = i;
		}
	}
	return index;

}

unsigned int vipMixtureOfGaussians::GetMaxWeightIndex( unsigned int pixindex )
{ // returns the index of the gaussian with maximum weight
	unsigned int index = 0;
	float curr_max = gaussians[0].weight[pixindex];

	for( unsigned int i=0; i<myParams->K; i++ )
	{
		if( gaussians[i].weight[pixindex] > curr_max )
		{
			curr_max = gaussians[i].weight[pixindex];
			index = i;
		}
	}

	return index;
}


unsigned int vipMixtureOfGaussians::GetMinCountIndex()
{ // returns the index of the gaussian with minimum count
	unsigned int index = 0;
	float curr_min = gaussians[0].count;

	for( unsigned int i=0; i<myParams->K; i++ )
	{
		if( gaussians[i].count < curr_min )
		{
			curr_min = gaussians[i].count;
			index = i;
		}
	}
	return index;

}

unsigned int vipMixtureOfGaussians::GetMaxCountIndex()
{ // returns the index of the gaussian with maximum count
	unsigned int index = 0;
	float curr_max = gaussians[0].count;

	for( unsigned int i=0; i<myParams->K; i++ )
	{
		if( gaussians[i].count > curr_max )
		{
			curr_max = gaussians[i].count;
			index = i;
		}
	}

	return index;
}




void vipMixtureOfGaussians::PrintDebug()
{
	printf("\nG#\tCount\n");
	for( unsigned int k=0; k<myParams->K; k++ )
	{ // for each gaussian
		if( gaussians[k].count == 0 )
			printf("#%i\t[not used]\n", k );
		else
			//printf("#%i\t%4.4f\t%4.2f\n", k, gaussians[k].weight, gaussians[k].count );
			printf("#%i\t%4.2f\n", k, gaussians[k].count );
	}
	printf("UseModelUpdate=%i\n", myParams->uiUseModelUpdate );
}


void vipMixtureOfGaussians::PrintThresholdsInfo()
{
	printf("\n\tMixtureOfGaussians: Current thresholds\n");
	printf("\t\tVariance th.: %f\n", myParams->th_var );
	printf("\t\tShadow: Alpha: %f\n", myParams->shadAlpha );
	printf("\t\t\tBeta:  %f\n", myParams->shadBeta );
	printf("\t\t\tth. H: %f\n", myParams->th_shad_h );
	printf("\t\t\tth. S: %f\n", myParams->th_shad_s );
	printf("\t\tReflex: Alpha: %f\n", myParams->reflAlpha );
	printf("\t\t\tBeta:  %f\n", myParams->reflBeta );
	printf("\t\t\tth. H: %f\n", myParams->th_refl_h );
	printf("\t\t\tth. S: %f\n", myParams->th_refl_s );
}

void vipMixtureOfGaussians::PrintStatistics()
{
	printf("\n\tMixtureOfGaussians: Latest detections\n");
	printf("\t\t%i foreground, %i shadow and %i reflex pixels.\n", uiLastForegroundCount, uiLastShadowCount, uiLastReflexCount );
}


void vipMixtureOfGaussians::NormalizeWeights( unsigned int pixindex )
{ // Normalize weights so their sum is 1
	float w_tot = 0;
	for( unsigned int k=0; k<myParams->K; k++ )
		w_tot += gaussians[k].weight[pixindex];
	for( unsigned int k=0; k<myParams->K; k++ )
		gaussians[k].weight[pixindex] /= w_tot;
}


unsigned int argmax( float* data, unsigned int size )
{
	unsigned int arg = 0;
	float curr_max = 0;
	for( unsigned int i=0; i<size; i++ )
	{
		if( data[i] > curr_max )
		{
			arg = i;
			curr_max = data[i];
		}
	}
	return arg;
}

VIPRESULT vipMixtureOfGaussians::BackgroundSubtraction( vipFrameHSV &input, bool doBgProcNow )
{
	if( width != input.getWidth() || height != input.getHeight() )
	{
		printf("\n** ERROR: vipMixtureOfGaussians::BackgroundSubtraction(): different framesizes.\n");
		return VIPRET_ILLEGAL_USE;
	}

	unsigned int framesize = input.getWidth() * input.getHeight();
	unsigned int shadows = 0;
	unsigned int reflexes = 0;
	unsigned int fg_count = 0;
	unsigned short int k = 0;
	float* prob_p = new float[myParams->K];

	float prob_p_tot = 0;

	for( unsigned int pixnum=0; pixnum<framesize; pixnum++ )
	{ // For each pixel
		prob_p_tot = 0;
		for( k=0; k<myParams->K; k++ )
		{ // For each of the K gaussians:
			prob_p[k] = gaussians[k].TryMatch( input.data[pixnum], pixnum, myParams->th_var, myParams->matchChan, myParams->getMatchingMode() );
			prob_p_tot += prob_p[k];
		} // end of For each gaussian
		
		if( prob_p_tot > 0 )
		{
			// it's a bg pixel
			foreground[pixnum] = (unsigned char)MOG_BACKGROUND_OUTVAL;

			//// BG Model update.
			if( myParams->uiUseModelUpdate )
			{
				k = argmax(prob_p,myParams->K);
				float prob_q = prob_p[k] / prob_p_tot;

				// Update weights. TODO: should this be actually done?
				gaussians[k].weight[pixnum] = (1-myParams->alpha)*gaussians[k].weight[pixnum] + myParams->alpha*prob_q;
				NormalizeWeights( pixnum );

				// update count
				gaussians[k].count += prob_q;
				// update learning rate
				gaussians[k].learn_rate = prob_q * ( (1-myParams->alpha)/(gaussians[k].count) + myParams->alpha );
				// update stats
				gaussians[k].UpdateWith( input.data[pixnum], pixnum ); 
			} // end of model update
		}
		else	// pixel is not background
		{
			// Check shadows and Reflexes if enabled
			if( myParams->isShadowDetectionEnabled() && IsShadowPixel(input.data[pixnum],pixnum) )
			{
				foreground[pixnum] = myParams->ucShadowOutValue;	// Flag pixel as shadow
				shadows++;
			}
			else if( myParams->isReflexDetectionEnabled() && IsReflexPixel(input.data[pixnum],pixnum) )
			{
				foreground[pixnum] = myParams->ucReflexOutValue;	// Flag pixel as reflex
				reflexes++;
			}
			else	// not a shadow, not a reflex... then it's foreground.
			{
				foreground[pixnum] = (unsigned char)MOG_FOREGROUND_OUTVAL;
				fg_count++;
			}

		}
	} // end of for each pixel

	// prints stats
	if( myParams->getVerbosity() != 0 )
		PrintStatistics();

	// update stats
	uiLastForegroundCount = fg_count;
	uiLastShadowCount = shadows;
	uiLastReflexCount = reflexes;

	// Do background clean up now?
	if( doBgProcNow )
	{
		while( BackgroundProcess() ) {};	// Processing operation to remove all sparse single fg pixels
	}

#ifdef	DO_FWRITE_INTERMEDIATES
	// write a single 4:2:0 yuv frame
	FILE* fp;
	fopen_s( &fp, "intermediate/mog_bg.yuv", "a+b");
	for( int i=framesize; i<(framesize*1.5); i++ )
		background[i] = 128;
	fwrite( background, sizeof(unsigned char), 320*240*1.5, fp );
	fclose( fp );

	unsigned char *framewrite = new unsigned char[framesize*1.5];
	if( DO_FWRITE_INTERMEDIATES /*TEST FWRITE OF FRAME*/ )
	{	// write a single 4:2:0 yuv frame
		FILE* fp;
		fopen_s( &fp ,"intermediate/mog_vmean_g1.yuv", "a+");
		for( unsigned int i=0; i<framesize; i++ )
			framewrite[i] = gaussians[1].v_mean[i];			// write a gaussian's v_mean frame
		for( unsigned int i=framesize; i<(framesize*1.5); i++ )
			framewrite[i] = 128;
		fwrite( background, sizeof(unsigned char), framesize*1.5, fp );
		fclose( fp );
	}
	//if( 1 /*TEST FWRITE OF FRAME*/ )
	//{	// write a single 4:2:0 yuv frame
	//	FILE* fp = fopen("mog_vmean_g2.yuv", "a+");
	//	for( int i=0; i<framesize; i++ )
	//		framewrite[i] = gaussians[2].v_mean[i];			// write a gaussian's v_mean frame
	//	for( int i=framesize; i<(framesize*1.5); i++ )
	//		framewrite[i] = 128;
	//	fwrite( background, sizeof(unsigned char), framesize*1.5, fp );
	//	fclose( fp );
	//}
	delete[] framewrite;
#endif

	delete[] prob_p;
	if( myParams->verbosity != 0 )
		PrintDebug();

	return VIPRET_OK;
}

VIPRESULT vipMixtureOfGaussians::Training( vipFrameHSV &input )
{
	if( width != input.getWidth() || height != input.getHeight() )
	{
		printf("\n** ERROR: vipMixtureOfGaussians::BackgroundSubtraction(): different framesizes.\n");
		return VIPRET_ILLEGAL_USE;
	}


	unsigned int framesize = input.getWidth() * input.getHeight();
	float *prob_p = new float[myParams->K];
	float *prob_q = new float[myParams->K];
	float prob_p_tot;

	for( unsigned int pixnum=0; pixnum<framesize; pixnum++)
	{ // For each pixel
		prob_p_tot = 0;
		for( unsigned short int k=0; k<myParams->K; k++ )
		{ // For each of the K gaussians:
			prob_p[k] = gaussians[k].TryMatch( input.data[pixnum], pixnum, myParams->th_var, myParams->matchChan, myParams->getMatchingMode() );
			prob_p_tot += prob_p[k];
		} // end of For each gaussian
		
		if( prob_p_tot > 0 )
		{ // If at least 1 match is found
			for( unsigned short int k=0; k<myParams->K; k++ )
			{ // for each gaussian
				prob_q[k] = prob_p[k] / prob_p_tot;
				if( myParams->WinTakeAll )
				{ // "Winner takes it all" mode to save cpu
					if( k == argmax(prob_p,myParams->K) )
						prob_q[k] = 1;
					else
						prob_q[k] = 0;
				} // end of "Winner takes it all"

				// Update this gaussian's weight
				gaussians[k].weight[pixnum] = (1-myParams->alpha)*gaussians[k].weight[pixnum] + myParams->alpha*prob_q[k];

				// For matched gaussians: update
				if( prob_q[k] > 0 )
				{
					// update count
					gaussians[k].count += prob_q[k];
					// update learning rate
					gaussians[k].learn_rate = prob_q[k] * ( (1-myParams->alpha)/(gaussians[k].count) + myParams->alpha );
					// update stats
					gaussians[k].UpdateWith( input.data[pixnum], pixnum ); 
				}
			} // end of for each gaussian
		} // end of If at least 1 match is found
		else
		{  // no match found
			// lower each gaussian's weight
			for( unsigned short int k=0; k<myParams->K; k++ )
				gaussians[k].weight[pixnum] = (1-myParams->alpha)*(gaussians[k].weight[pixnum]);

			// Overwrite least significant gaussian to match new pixel input
			unsigned short int argmin = GetMinWeightIndex( pixnum );
			gaussians[argmin].weight[pixnum] = myParams->alpha;
			gaussians[argmin].h_mean[pixnum] = input.data[pixnum].hue;
			gaussians[argmin].s_mean[pixnum] = input.data[pixnum].sat;
			gaussians[argmin].v_mean[pixnum] = input.data[pixnum].val;
			gaussians[argmin].h_var[pixnum] = (float) myParams->v0;
			gaussians[argmin].s_var[pixnum] = (float) myParams->v0;
			gaussians[argmin].v_var[pixnum] = (float) myParams->v0;
			gaussians[argmin].count++; // TODO: this is NOT accurate. I do not know how exactly to make it accurate without wasting resources.
		}	// end of no match found block
	NormalizeWeights( pixnum );
	} // end of For each pixel

	delete[] prob_p;
	delete[] prob_q;

	if( myParams->verbosity != 0 )
		PrintDebug();

	return VIPRET_OK;
}


/*todo comment. if available use vipMorph::close etc etc */
unsigned int vipMixtureOfGaussians::BackgroundProcess( unsigned char *target, bool bTrimFrameEdges )
{  // After producing a background model, this method can be used to clean out single sparse foreground points
	// todo: maybe it's better to go with a region growing/splitnmerge/divide.... or other already coded stuff
	// todo: or maybe we can leave those be, and let the proper blob tracking method remove the small blobs.

	if( target == NULL )
		target = foreground;

	if( target == NULL )
	{
		printf("ERROR: vipMixtureOfGaussians::BackgroundProcess(): Pointer to BG frame is NULL.\n");
		return 0;
	}

	if( !bTrimFrameEdges )
	{
		throw("vipMixtureOfGaussians::BackgroundProcess() with bTrimFrameEdges==false: Implement this");
	}

	unsigned char BG = MOG_BACKGROUND_OUTVAL;

	// (1x1) Sparse point elimination: Raster scan of frame
	unsigned int x, y, changed=0;
	for( y=0; y<height; y++ )
	{
		for( x=0; x<width; x++ )
		{
			// Trim Frame Edges
			if( bTrimFrameEdges && (x==0 || y==0 || x==width-1 || y==height-1) )
					target[y*width+x] = (unsigned char)BG;
			// Mid frame area:
			else if(	( (target[y*width+x]!=BG) )	&&
					( ( target[y*width+x-1]==BG		&& target[y*width+x+1]==BG )		||	// check left and right
					( target[(y-1)*width+x]==BG		&& target[(y+1)*width+x]==BG ) )	)	// _OR_ check top and bottom
			{
				target[y*width+x] = (unsigned char)BG;
				changed++;
			}

		} // end of one line (x)

	} // end of raster scan



	// (2x2) Sparse point elimination: Raster scan of frame
	for( y=0; y<height; y++ )
	{
		for( x=0; x<width; x++ )
		{
			// Trim Frame Edges (2px)
			if( bTrimFrameEdges && (x==0||x==1 || y==0||y==1 || x==width-1||x==width-2 || y==height-1||y==height-2) )
				target[y*width+x] = (unsigned char)BG;
			// Mid frame area:
			else if(		(target[y*width+x]!=BG)
							&&
							(
								(// LEFT/RIGHT sides
									target[(y  )*width+x-1]==BG	&& target[(y  )*width+x+2]==BG &&
									target[(y+1)*width+x-1]==BG	&& target[(y+1)*width+x+2]==BG
								)
								|| // OR BOTTOM/TOP sides
								(
									target[(y-1)*width+x  ]==BG	&& target[(y-1)*width+x+1]==BG &&
									target[(y+2)*width+x  ]==BG	&& target[(y+1)*width+x+1]==BG
								)
							)	
					)	// check top and bottom
			{ //ok, set it to BG value
				target[y*width+x] = (unsigned char)BG;
				changed++;
			}

		} // end of one line (x)

	} // end of raster scan


	return changed;
}


bool vipMixtureOfGaussians::IsShadowPixel(PixelHSV pix, unsigned int pixindex)
{
	// Shadow detection procedure: IEEE Trans PAMI '03, Cucchiara
	// Cucchiara, Grana, Piccardi, Prati, "Detecting moving objects, ghosts, and shadows in video streams", IEEE PAMI '03
	float v_ratio, diff_h;

	for( unsigned int k=0; k<myParams->K; k++ )
	{
		v_ratio = pix.val/gaussians[k].v_mean[pixindex];
		diff_h = abs(pix.hue-gaussians[k].h_mean[pixindex]);	// angular difference for Hue...
		if( diff_h>180 ) diff_h = 360-diff_h;					// ...
		if(		v_ratio>myParams->shadAlpha && v_ratio<myParams->shadBeta && 
				(pix.sat-gaussians[k].s_mean[pixindex])<myParams->th_shad_s && 
				diff_h<myParams->th_shad_h	)
			return true;	// it's a shadow for at least one gaussian
	}
	return false;	// not a shadow for any gaussian
}

bool vipMixtureOfGaussians::IsReflexPixel(PixelHSV pix, unsigned int pixindex)
{ // not working, afaik
	float v_ratio, diff_h;

	for( unsigned int k=0; k<myParams->K; k++ )
	{
		v_ratio = pix.val/gaussians[k].v_mean[pixindex];
		diff_h = abs(pix.hue-gaussians[k].h_mean[pixindex]);	// angular difference for Hue...
		if( diff_h>180 ) diff_h = 360-diff_h;					// ...
		if(		v_ratio>myParams->reflAlpha && v_ratio<myParams->reflBeta && 
				abs(pix.sat-gaussians[k].s_mean[pixindex])<myParams->th_refl_s && 
				diff_h<myParams->th_refl_h	)
			return true;	// it's a reflex for at least one gaussian
	}
	return false;	// not a reflex for any gaussian
}


VIPRESULT vipMixtureOfGaussians::operator >> (vipFrameT<unsigned char> &img )
{
	return extractTo( img );	// check/test if this is ok.. my first attempt at defining an operator :\ MV
}

// Inherited method
VIPRESULT	vipMixtureOfGaussians::extractTo( vipFrameT<unsigned char> &img )
{
	//// This method outputs the current foreground to img.

	// Prepare output frame
	if( width != img.width || height != img.height || img.data == NULL )
		img.reAllocCanvas( width, height );

	// Copy data
	memcpy( img.data, foreground, sizeof(unsigned char)*width*height );

	return VIPRET_OK;
}


// This method outputs the current BG MEAN MODEL with the highest weight, i.e. mean values of that gaussian.
VIPRESULT vipMixtureOfGaussians::extractTo( vipFrameHSV &img )
{
	unsigned int framesize = width*height;
	unsigned int mwi;	// Maximum weight index

	if( gaussians[ GetMaxCountIndex() ].count <= 0 )
		printf("\n**WARNING: vipMixtureOfGaussians::extractTo( vipFrameHSV &img ): gaussian with highest count has count==0 (is empty).\n");

	// Prepare output frame
	if( width != img.width || height != img.height || img.data == NULL )
		img.reAllocCanvas( width, height );

	for( unsigned int i=0; i<framesize; i++ )
	{ // copy mean of the 3 components to img data
		mwi = GetMaxWeightIndex(i);
#ifdef _DEBUG
		if( (unsigned short) gaussians[mwi].h_mean[i] == -1 || (unsigned char) gaussians[mwi].s_mean[i] == -1 || (unsigned char) gaussians[mwi].v_mean[i] == -1 )
			printf("\n**WARNING: vipMixtureOfGaussians::extractTo( vipFrameHSV &img ): gaussian #%i with highest weight (%.4f) has count==0 (is empty). Value output: -1.\n", mwi, gaussians[mwi].weight[i] );
#endif		img.data[i].hue = (unsigned short) gaussians[mwi].h_mean[i];
		img.data[i].sat = (unsigned char) gaussians[mwi].s_mean[i];
		img.data[i].val = (unsigned char) gaussians[mwi].v_mean[i];
	}

	return VIPRET_OK;
}


VIPRESULT vipMixtureOfGaussians::operator >> (vipFrameHSV &img)
{
	return extractTo( img );
}


// This method performs BackgroundSubtraction OR Training depending on the mode currently set.
VIPRESULT vipMixtureOfGaussians::importFrom( vipFrameHSV &img )
{
	switch( myParams->getInputMode() )
	{
	case vipMixtureOfGaussiansParameters::INPUT_TRAINING:
		return Training( img );
		
	case vipMixtureOfGaussiansParameters::INPUT_SUBTRACTION:
		return BackgroundSubtraction( img );

	default:
		return VIPRET_INTERNAL_ERR;

	}

}


VIPRESULT vipMixtureOfGaussians::reset()
{
	// reset gaussians
	for( unsigned int k=0; k<myParams->K; k++ )
	{
		gaussians[k].freeData();
		gaussians[k].Init(width,height);
	}
	// reset foreground
	int framesize = width*height;
	if( foreground != NULL )
		memset( foreground, 0, sizeof(unsigned char)*(framesize) );

	for( unsigned int i=0; i<myParams->K; i++ )
	{ // initialize variance values to v0, and mean values to 0
		for( int pixindex = 0; pixindex < framesize; pixindex++ )
		{
			gaussians[i].h_var[pixindex] = myParams->v0;
			gaussians[i].s_var[pixindex] = myParams->v0;
			gaussians[i].v_var[pixindex] = myParams->v0;
			gaussians[i].h_mean[pixindex] = -1;
			gaussians[i].s_mean[pixindex] = -1;
			gaussians[i].v_mean[pixindex] = -1;
		}
	}

	return VIPRET_OK;

}


VIPRESULT vipMixtureOfGaussians::operator << (vipFrameHSV &img)
{
	return importFrom( img );
}

void vipMixtureOfGaussiansParameters::setOutputMode(vipMixtureOfGaussiansParameters::OUTPUT_MODE mode)
{
	outputMode = mode;

	switch( mode )
	{
	case OUTPUT_BINARY:
		ucShadowOutValue = MOG_BACKGROUND_OUTVAL;	// 0
		ucReflexOutValue = MOG_BACKGROUND_OUTVAL;	// 0
		break;
	case OUTPUT_GRAYSCALE:
		ucShadowOutValue = MOG_SHADOW_GRAYLEVEL;	// e.g. 64
		ucReflexOutValue = MOG_REFLEX_GRAYLEVEL;	// e.g. 180
		break;
	default:
		throw("vipMixtureOfGaussiansParameters::setOutputMode(): Invalid OUTPUT_MODE.");
	}
}
