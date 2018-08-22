/** @file vipMultiplexer.cpp
 *
 * File containing methods for the 'vipMultiplexer' class.
 * The header for this class can be found in vipMultiplexer.h,
 * check that file for class description.
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



#include "vipMultiplexer.h"


/**
 * @brief  Default constructor, initialize parameters and superclasses.
 * @param[in] initParams parameters for this module or NULL for defaults.
 */
vipMultiplexer::vipMultiplexer(vipMultiplexerParameters* initParams) : vipFilter()
 {
	INFO("vipMultiplexer::vipMultiplexer(..* initParams) : vipFilter() [CONTRUCTOR]")

	inputs = NULL;
	outputs = NULL;

	reset();

	setParameters(initParams);
 }

/**
 * @brief Default destructor, free buffer.
 */
vipMultiplexer::~vipMultiplexer()
 {
	INFO("vipMultiplexer::~vipMultiplexer() [DESTRUCTOR]")

	delete inputs;	// removes array only, not objects
	delete outputs;	// removes array only, not objects

	if (myParams != NULL)
		delete myParams;
	myParams = NULL;
 }

/**
 * @brief  Reset input/output lists and parameters.
 *
 * @return VIPRET_OK
 */
VIPRESULT vipMultiplexer::reset()
 {
	INFO("VIPRESULT vipMultiplexer::reset() [SET DEFAULT PARAMETERS]")

	setName("Multiplexer");
	setDescription("Link some sources with some outputs");
	setVersion(1.0);

	if ( inputs != NULL )
		delete inputs;

	if ( outputs != NULL )
		delete outputs;

	inputs = new vipInput*[VET_MP_INPUTS_MAX];
	outputs = new vipOutput*[VET_MP_OUTPUTS_MAX];

	for (int i=0; i<VET_MP_INPUTS_MAX; i++)
		inputs[i] = NULL;
	for (int j=0; j<VET_MP_OUTPUTS_MAX; j++)
		outputs[j] = NULL;

	inputCurrent = 0;
	outputCurrent = 0;
	inputCount = 0;
	outputCount = 0;

	return VIPRET_OK;
 }


/**
 * @brief  Set parameters for this filter.
 *
 * @param[in] initParams Instance of vipMultiplexerParameters or NULL,
 *                       NULL argument make function to create a new
 *                       instance with default parameters.
 *
 * @return VIPRET_OK
 */
VIPRESULT vipMultiplexer::setParameters (vipMultiplexerParameters* initParams)
 {
	if ( initParams == NULL )
		myParams = new vipMultiplexerParameters();
	else
		myParams = initParams;

	return VIPRET_OK;
 }










//TODO
//should be managed as thread!!
VIPRESULT vipMultiplexer::run(long cycles)
 {
	DEBUGMSG("VIPRESULT vipMultiplexer::run(long cycles)", cycles)

	if ( inputs[inputCurrent] == NULL || outputs[outputCurrent] == NULL )
		return VIPRET_ILLEGAL_USE;

	if ( cycles == 0)
		cycles = VET_MP_LOOP_MAX;

	if ( isBufferYUV() )
	 {
		for (long i=0; i < cycles; i++)
		 {
			*inputs[inputCurrent] >> *bufferYUV;
			*outputs[outputCurrent] << *bufferYUV;
		 }
	 }

	else if ( isBufferRGB() )
	 {
		for (long i=0; i < cycles; i++)
		 {
			*inputs[inputCurrent] >> *bufferRGB;
			*outputs[outputCurrent] << *bufferRGB;
		 }
	 }

	else
	 {
		for (long i=0; i < cycles; i++)
		 {
			*inputs[inputCurrent] >> *bufferTuC;
			*outputs[outputCurrent] << *bufferTuC;
		 }
	 }

	return VIPRET_OK;
 }















/**
 * @brief Redirect input frame to current filter/output.
 *
 * @param[in] img VIPLibb Cache Frame to be processed (redirected).
 *
 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
 *
 * @note  Input operator (<<) call directly this function.
 * @see   operator << (vipFrameYUV420&)
 */
VIPRESULT vipMultiplexer::importFrom(vipFrameYUV420& img)
 {
	DEBUGMSG("VIPRESULT vipMultiplexer::importFrom(vipFrameYUV420& img) [reading data]", outputCurrent)

	*outputs[outputCurrent] << img;
	return VIPRET_OK;
 }

/**
 * @brief Redirect input frame to current filter/output.
 *
 * @param[in] img VIPLibb Cache24 Frame to be processed (redirected).
 *
 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
 *
 * @note  Input operator (<<) call directly this function.
 * @see   operator << (vipFrameRGB24&)
 */
VIPRESULT vipMultiplexer::importFrom(vipFrameRGB24& img)
 {
	DEBUGMSG("VIPRESULT vipMultiplexer::importFrom(vipFrameRGB24& img) [reading data]", outputCurrent)

	*outputs[outputCurrent] << img;
	return VIPRET_OK;
 }

/**
 * @brief Redirect input frame to current filter/output.
 *
 * @param[in] img VIPLibb Greyscale Frame to be processed (redirected).
 *
 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
 *
 * @note  Input operator (<<) call directly this function.
 * @see   operator << (vipFrameT&)
 */
VIPRESULT vipMultiplexer::importFrom(vipFrameT<unsigned char>& img)
 {
	DEBUGMSG("VIPRESULT vipMultiplexer::importFrom(vipFrameT& img) [reading data]", outputCurrent)

	*outputs[outputCurrent] << img;
	return VIPRET_OK;
 }

/**
 * @brief  Extract a frame from current filter/input.
 *
 * @param[out] img VIPLibb Cache Frame to store data.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_ILLEGAL_USE if
 *		   buffer is empty, VIPRET_INTERNAL_ERR else.
 *
 * @note   Ouput operator (>>) call directly this function.
 * @see    operator >> (vipFrameYUV420&)
 */
VIPRESULT vipMultiplexer::extractTo(vipFrameYUV420& img)
 {
	DEBUGMSG("VIPRESULT vipMultiplexer::extractTo(vipFrameYUV420& img) [pushing data]", inputCurrent)

	*inputs[inputCurrent] >> img;
	return VIPRET_OK;
 }

/**
 * @brief  Extract a frame from current filter/input.
 *
 * @param[out] img VIPLibb Cache24 Frame to store data.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_ILLEGAL_USE if
 *		   buffer is empty, VIPRET_INTERNAL_ERR else.
 *
 * @note   Ouput operator (>>) call directly this function.
 * @see    operator >> (vipFrameRGB24&)
 */
VIPRESULT vipMultiplexer::extractTo(vipFrameRGB24& img)
 {
	DEBUGMSG("VIPRESULT vipMultiplexer::extractTo(vipFrameRGB24& img) [pushing data]", inputCurrent)

	*inputs[inputCurrent] >> img;
	return VIPRET_OK;
 }

/**
 * @brief  Extract a frame from current filter/input.
 *
 * @param[out] img VIPLibb Greyscale Frame to store data.
 *
 * @return VIPRET_OK if everything is fine, VIPRET_ILLEGAL_USE if
 *		   buffer is empty, VIPRET_INTERNAL_ERR else.
 *
 * @note   Ouput operator (>>) call directly this function.
 * @see    operator >> (vipFrameT&)
 */
VIPRESULT vipMultiplexer::extractTo(vipFrameT<unsigned char>& img)
 {
	DEBUGMSG("VIPRESULT vipMultiplexer::extractTo(vipFrameT& img) [pushing data]", inputCurrent)

	*inputs[inputCurrent] >> img;
	return VIPRET_OK;
 }





/**
 * @brief  Add a new data input to current list.
 *
 * @param[in] newInput pointer to a vipInput implementation.
 *
 * @return VIPRET_PARAM_ERR if argument is NULL, VIPRET_ILLEGAL_USE
 *         if input's count is equal to VET_MP_INPUTS_MAX, VIPRET_OK else.
 */
VIPRESULT vipMultiplexer::addInput(vipInput* newInput)
{
	DEBUGMSG("VIPRESULT vipMultiplexer::addInput(vipInput* newInput)", inputCount)

	if ( newInput == NULL )
		return VIPRET_PARAM_ERR;

	if ( inputCount >= VET_MP_INPUTS_MAX )
		return VIPRET_ILLEGAL_USE;

	inputs[inputCount++] = newInput;

	return VIPRET_OK;
}

/**
 * @brief  Remove a data input from current list, following items (id+n) are
 *         moved back one position.
 *
 * @param[in] oldInput pointer to data input.
 *
 * @return VIPRET_PARAM_ERR if argument is NULL, VIPRET_ILLEGAL_USE
 *         if input was not found in list, VIPRET_OK else.
 */
VIPRESULT vipMultiplexer::removeInput(vipInput* oldInput)
{
	DEBUGMSG("VIPRESULT vipMultiplexer::removeInput(vipInput* oldInput)", inputCount)

	if ( oldInput == NULL )
		return VIPRET_PARAM_ERR;

	int iter = 0;
	while ( iter < inputCount )
	 {
		if ( inputs[iter] == oldInput )
			return removeInput(iter);
		iter++;
	 }

	return VIPRET_OK;
}

/**
 * @brief  Remove a data input from current list, following items (id+n) are
 *         moved back one position.
 *
 * @param[in] id data input's id to remove.
 *
 * @return VIPRET_PARAM_ERR if id is not valid, VIPRET_ILLEGAL_USE
 *         if input was not found in list, VIPRET_OK else.
 */
VIPRESULT vipMultiplexer::removeInput(int id)
{
	DEBUGMSG("VIPRESULT vipMultiplexer::removeInput(int id)", id)

	if ( id < 0 || id >= inputCount )
		return VIPRET_PARAM_ERR;

	//move * after ID one position back
	for (int i=id; i<inputCount-1; i++) {
		inputs[i] = inputs[i+1];
	 }

	inputs[inputCount--] = NULL;

	return VIPRET_OK;
}

/**
 * @brief  Add a new data output to current list.
 *
 * @param[in] newInput pointer to a vipOutput implementation.
 *
 * @return VIPRET_PARAM_ERR if argument is NULL, VIPRET_ILLEGAL_USE
 *         if output's count is equal to VET_MP_OUTPUTS_MAX, VIPRET_OK else.
 */
VIPRESULT vipMultiplexer::addOutput(vipOutput* newOutput)
{
	DEBUGMSG("VIPRESULT vipMultiplexer::addOutput(vipOutput* newOutput)", outputCount)

	if ( newOutput == NULL )
		return VIPRET_PARAM_ERR;

	if ( outputCount >= VET_MP_OUTPUTS_MAX )
		return VIPRET_ILLEGAL_USE;

	outputs[outputCount++] = newOutput;

	return VIPRET_OK;
}

/**
 * @brief  Remove a data output from current list, following items (id+n) are
 *         moved back one position.
 *
 * @param[in] oldOutput pointer to data input.
 *
 * @return VIPRET_PARAM_ERR if argument is NULL, VIPRET_ILLEGAL_USE
 *         if output was not found in list, VIPRET_OK else.
 */
VIPRESULT vipMultiplexer::removeOutput(vipOutput* oldOutput)
{
	DEBUGMSG("VIPRESULT vipMultiplexer::removeOutput(vipOutput* oldOutput)", outputCount)

	if ( oldOutput == NULL )
		return VIPRET_PARAM_ERR;

	if ( outputCount >= VET_MP_OUTPUTS_MAX )
		return VIPRET_ILLEGAL_USE;

	int iter = 0;
	while ( iter < outputCount )
	 {
		if ( outputs[iter] == oldOutput )
			return removeOutput(iter);
		iter++;
	 }

	return VIPRET_PARAM_ERR;
}

/**
 * @brief  Remove a data output from current list, following items (id+n) are
 *         moved back one position.
 *
 * @param[in] id data output's id to remove.
 *
 * @return VIPRET_PARAM_ERR if id is not valid, VIPRET_ILLEGAL_USE
 *         if output was not found in list, VIPRET_OK else.
 */
VIPRESULT vipMultiplexer::removeOutput(int id)
{
	DEBUGMSG("VIPRESULT vipMultiplexer::removeOutput(int id)", id)

	if ( id < 0 || id >= outputCount )
		return VIPRET_PARAM_ERR;

	//move * after ID one position back
	for (int i=id; i<outputCount-1; i++) {
		outputs[i] = outputs[i+1];
	 }

	outputs[outputCount--] = NULL;

	return VIPRET_OK;
}

/**
 * @brief  Select current data input.
 *
 * @param[in] id input's id [0, inputCount[
 *
 * @return VIPRET_PARAM_ERR if id is not valid, VIPRET_OK else.
 */
VIPRESULT vipMultiplexer::setCurrentInput(int id)
 {
	DEBUGMSG("VIPRESULT vipMultiplexer::setCurrentInput(int id)", id)

	if ( id < 0 || id >= inputCount )
		return VIPRET_PARAM_ERR;

	if ( inputs[id] == NULL )
		return VIPRET_PARAM_ERR;

	inputCurrent = id;

	return VIPRET_OK;
 }

/**
 * @brief  Set current data input.
 *
 * @param[in] currIn vipInput implementation instance.
 *
 * @return VIPRET_PARAM_ERR if selected input was not found in current list
 *         or if argument is NULL, VIPRET_OK else.
 */
VIPRESULT vipMultiplexer::setCurrentInput(vipInput& currIn)
 {
	INFO("VIPRESULT vipMultiplexer::setCurrentInput(vipInput& currSource)")

	if ( &currIn == NULL )
		return VIPRET_PARAM_ERR;

	int iter = 0;
	while ( iter < inputCount )
	 {
		if ( inputs[iter] == &currIn ) {
			inputCurrent = iter;
			return VIPRET_OK;
		 }
		iter++;
	 }

	return VIPRET_PARAM_ERR;
 }

/**
 * @brief  Select current data output.
 *
 * @param[in] id output's id [0, outputCount[
 *
 * @return VIPRET_PARAM_ERR if id is not valid, VIPRET_OK else.
 */
VIPRESULT vipMultiplexer::setCurrentOutput(int id)
 {
	DEBUGMSG("VIPRESULT vipMultiplexer::setCurrentOutput(int id)", id)

	if ( id < 0 || id >= outputCount )
		return VIPRET_PARAM_ERR;

	if ( outputs[id] == NULL )
		return VIPRET_PARAM_ERR;

	outputCurrent = id;

	return VIPRET_OK;
 }

/**
 * @brief  Set current data output.
 *
 * @param[in] currOut vipOutput implementation instance.
 *
 * @return VIPRET_PARAM_ERR if selected output was not found in current list
 *         or if argument is NULL, VIPRET_OK else.
 */
VIPRESULT vipMultiplexer::setCurrentOutput(vipOutput& currOut)
 {
	INFO("VIPRESULT vipMultiplexer::setCurrentOutput(vipOutput& currOut)")

	if ( &currOut == NULL )
		return VIPRET_PARAM_ERR;

	int iter = 0;
	while ( iter < outputCount )
	 {
		if ( outputs[iter] == &currOut ) {
			outputCurrent = iter;
			return VIPRET_OK;
		 }
		iter++;
	 }

	return VIPRET_PARAM_ERR;
 }

////////////////////////////////////////////////////////////////////////







///////////////////////////////////////////////////////////////////////////////////////


vipMultiplexerParameters::vipMultiplexerParameters()
 {

 }

void vipMultiplexerParameters::reset()
 {
	runMode = 0;
 }


int vipMultiplexerParameters::saveToStreamXML(FILE *fp)
 {
	return VIPRET_NOT_IMPLEMENTED;
 }


int vipMultiplexerParameters::loadFromStreamXML(FILE *fp)
 {
	return VIPRET_NOT_IMPLEMENTED;
 }
