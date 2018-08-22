/**
 *  @class   vipMultiplexer
 *
 *  @brief	 This class link any vipInput implementation to a vipOutput
 *           implementation, sources/destination capacity are defined
 *           VET_MP_INPUTS_MAX and VET_MP_OUTPUTS_MAX.
 *           Data are not buffered, but only redirected from current source
 *           to current destination, frame rate system is inherited from vipInput.
 *
 *
 *  @bug
 *  @warning
 *  @todo    MultiThreading support (on run function)
 *  @example ../../tests/test_vipMultiplexer.cpp
 *
 *  @see     vipFilter
 *
 *  @version 0.8
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



#ifndef __VIPLIB_VIPMULTIPLEXER_H__
 #define __VIPLIB_VIPMULTIPLEXER_H__

 #include "../vipDefs.h"
 #include "../vipFilter.h"

 #include "../vipThread.h"

 #include "../vipFrameYUV420.h"
 #include "../vipFrameRGB24.h"
 #include "../vipFrameT.h"


 #define VET_MP_INPUTS_MAX		12
 #define VET_MP_OUTPUTS_MAX		12

 #define VET_MP_LOOP_MAX		1000000


class vipMultiplexerParameters : public vipFilterParameters
{
	protected:

		int runMode;

		friend class vipMultiplexer;


	public:


		vipMultiplexerParameters();
		~vipMultiplexerParameters() {}

		void reset();

		VIPRESULT saveToStreamXML(FILE *fp);
		VIPRESULT loadFromStreamXML(FILE *fp);

};

class vipMultiplexer :	public vipFilter
 {

 protected:

		/**
		 * @brief  Current parameters.
		 */
		vipMultiplexerParameters* myParams;


		vipInput** inputs;
		int inputCount;

		vipOutput** outputs;
		int outputCount;

		int inputCurrent;
		int outputCurrent;


 public:


		/**
		 * @brief  Default constructor, initialize parameters and superclasses.
		 * @param[in] initParams parameters for this module or NULL for defaults.
		 */
		vipMultiplexer( vipMultiplexerParameters* initParams = NULL );

		/**
		 * @brief Default destructor, free buffer.
		 */
		~vipMultiplexer();

		float getFrameRate()  const { return 0; };


		/**
		 * @brief  Set parameters for this filter.
		 *
		 * @param[in] initParams Instance of vipMultiplexerParameters or NULL,
		 *                       NULL argument make function to create a new
		 *                       instance with default parameters.
		 *
		 * @return VIPRET_OK
		 */
		VIPRESULT setParameters(vipMultiplexerParameters* initParams);

		/**
		 * @brief  Get parameters for this filter.
		 *
		 * @return pointer to vipMultiplexerParameters instance.
		 */
		vipMultiplexerParameters& getParameters() { return *myParams; };

		/**
		 * @brief  Set parameters for this filter.
		 *
		 * @param[in] initParams Instance of vipMultiplexerParameters or NULL,
		 *                       NULL argument make function to create a new
		 *                       instance with default parameters.
		 *
		 * @return VIPRET_OK
		 */
		VIPRESULT setFilterParameters (vipFilterParameters* initParams)
		 {
			if (initParams == NULL)
				return setParameters(NULL);
			else
				return setParameters(static_cast<vipMultiplexerParameters*>(initParams));
		 };



		/**
		 * @brief  Get parameters for this filter.
		 *
		 * @return pointer to vipMultiplexerParameters instance.
		 */
		vipFilterParameters* getFilterParameters ()
		 {
			if (myParams == NULL)
				return NULL;
			else
				return static_cast<vipFilterParameters*>(myParams);
		 };

		/**
		 * @brief  Reset input/output lists and parameters.
		 *
		 * @return VIPRET_OK
		 */
		VIPRESULT reset();

		/**
		 * @brief
		 *
		 * @param[in] id input's id [0, inputCount[
		 *
		 * @return
		 */
		VIPRESULT run(long cycles = 0);

		/**
		 * @brief
		 *
		 * @return
		 */
		VIPRESULT stop();



		/**
		 * @brief  Redirect a single frame from current input to current output,
		 *         it's equal to call run(1).
		 *
		 * @return Same error-codes of int run().
		 * @see    run(1);
		 */
		VIPRESULT forward() { return run(1); };


		/**
		 * @brief  Add a new data input to current list.
		 *
		 * @param[in] newInput pointer to a vipInput implementation.
		 *
		 * @return VIPRET_PARAM_ERR if argument is NULL, VIPRET_ILLEGAL_USE
		 *         if input's count is equal to VET_MP_INPUTS_MAX, VIPRET_OK else.
		 */
		VIPRESULT addInput(vipInput* newInput);

		/**
		 * @brief  Remove a data input from current list, following items (id+n) are
		 *         moved back one position.
		 *
		 * @param[in] oldInput pointer to data input.
		 *
		 * @return VIPRET_PARAM_ERR if argument is NULL, VIPRET_ILLEGAL_USE
		 *         if input was not found in list, VIPRET_OK else.
		 */
		VIPRESULT removeInput(vipInput* oldInput);
		/**
		 * @brief  Remove a data input from current list, following items (id+n) are
		 *         moved back one position.
		 *
		 * @param[in] id data input's id to remove.
		 *
		 * @return VIPRET_PARAM_ERR if id is not valid, VIPRET_ILLEGAL_USE
		 *         if input was not found in list, VIPRET_OK else.
		 */
		VIPRESULT removeInput(int id);

		/**
		 * @brief  Add a new data output to current list.
		 *
		 * @param[in] newInput pointer to a vipOutput implementation.
		 *
		 * @return VIPRET_PARAM_ERR if argument is NULL, VIPRET_ILLEGAL_USE
		 *         if output's count is equal to VET_MP_OUTPUTS_MAX, VIPRET_OK else.
		 */
		VIPRESULT addOutput(vipOutput* newOutput);

		/**
		 * @brief  Remove a data output from current list, following items (id+n) are
		 *         moved back one position.
		 *
		 * @param[in] oldOutput pointer to data input.
		 *
		 * @return VIPRET_PARAM_ERR if argument is NULL, VIPRET_ILLEGAL_USE
		 *         if output was not found in list, VIPRET_OK else.
		 */
		VIPRESULT removeOutput(vipOutput* oldOutput);
		/**
		 * @brief  Remove a data output from current list, following items (id+n) are
		 *         moved back one position.
		 *
		 * @param[in] id data output's id to remove.
		 *
		 * @return VIPRET_PARAM_ERR if id is not valid, VIPRET_ILLEGAL_USE
		 *         if output was not found in list, VIPRET_OK else.
		 */
		VIPRESULT removeOutput(int id);

		/**
		 * @brief  Select current data input.
		 *
		 * @param[in] id input's id [0, inputCount[
		 *
		 * @return VIPRET_PARAM_ERR if id is not valid, VIPRET_OK else.
		 */
		VIPRESULT setCurrentInput(int id);
		/**
		 * @brief  Set current data input.
		 *
		 * @param[in] currIn vipInput implementation instance.
		 *
		 * @return VIPRET_PARAM_ERR if selected input was not found in current list
		 *         or if argument is NULL, VIPRET_OK else.
		 */
		VIPRESULT setCurrentInput(vipInput& currIn);

		/**
		 * @brief  Select current data output.
		 *
		 * @param[in] id output's id [0, outputCount[
		 *
		 * @return VIPRET_PARAM_ERR if id is not valid, VIPRET_OK else.
		 */
		VIPRESULT setCurrentOutput(int id);
		/**
		 * @brief  Set current data output.
		 *
		 * @param[in] currOut vipOutput implementation instance.
		 *
		 * @return VIPRET_PARAM_ERR if selected output was not found in current list
		 *         or if argument is NULL, VIPRET_OK else.
		 */
		VIPRESULT setCurrentOutput(vipOutput& currOut);

		/**
		 * @brief  Get current connected data input.
		 *
		 * @return id of current data input. [0, inputCount[
		 */
		int getCurrentInputId() { return inputCurrent; };
		/**
		 * @brief  Get current connected data input.
		 *
		 * @return pointer to current data input.
		 */
		vipInput* getCurrentInput() { return inputs[inputCurrent]; };

		/**
		 * @brief  Get current connected data output.
		 *
		 * @return id of current data output. [0, outputCount[
		 */
		int getCurrentOutputId() { return outputCurrent; };
		/**
		 * @brief  Get current connected data output.
		 *
		 * @return pointer to current data output.
		 */
		vipOutput* getCurrentOutput() { return outputs[outputCurrent]; };

		/**
		 * @brief  Get current data input count.
		 *
		 * @return number of connected inputs. [0, VET_MP_INPUTS_MAX]
		 */
		int getInputCount() { return inputCount; };
		/**
		 * @brief  Get current data output count.
		 *
		 * @return number of connected outputs. [0, VET_MP_OUTPUTS_MAX]
		 */
		int getOutputCount() { return outputCount; };


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
		VIPRESULT importFrom(vipFrameYUV420& img);

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
		VIPRESULT importFrom(vipFrameRGB24& img);

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
		VIPRESULT importFrom(vipFrameT<unsigned char>& img);


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
		VIPRESULT extractTo(vipFrameYUV420& img);

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
		VIPRESULT extractTo(vipFrameRGB24& img);

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
		VIPRESULT extractTo(vipFrameT<unsigned char>& img);


};



#endif //__VIPLIB_VIPMULTIPLEXER_H__


