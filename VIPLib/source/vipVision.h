/**
 *  @class   vipVision
 *
 *  @brief   Base class for all Motion Detection modules.
 *           Simplify alert call and implements some common methods.
 *
 *
 *  @bug
 *  @warning
 *  @todo
 *
 *  @see     vipOutput
 *
 *  @version 1.0.2
 *  @date    18/09/2005
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



#ifndef __VIPLIB_VIPVISION_H__
 #define __VIPLIB_VIPVISION_H__

 #include "vipDefs.h"
 #include "vipOutput.h"
 #include "vipObject.h"

 #include "vipFrameYUV420.h"
 #include "vipFrameRGB24.h"
 #include "vipFrameT.h"



class vipVision	:	public vipOutput,
					public vipObject
 {
	protected:


		//funct di alert
 		void* (*alertCall)(void* argument);
		void* alertCallArgument;

		void doAlert();


	public:



		vipVision();

		/**
		 * @brief Destructor currenly clear only filters description strings.
		 */
		virtual ~vipVision();



		void setAlertCall(void* (*functionCall)(void*) ) { alertCall = functionCall; };
		void setAlertCallArgument(void* arg) { alertCallArgument = arg; };
		void* getAlertCallArgument() { return alertCallArgument; };



//delete that:
			template<class T, class S, class J>
		static VIPRESULT getDifference(vipFrameT<T>& diff_img, vipFrameT<S>& source_img, vipFrameT<J>& second_img);

		static VIPRESULT getDifference(vipFrameT<unsigned char>& diff_img, vipFrameT<unsigned char>& source_img, vipFrameT<unsigned char>& second_img);
		static VIPRESULT getDifference(vipFrameT<int>& diff_img, vipFrameT<int>& source_img, vipFrameT<int>& second_img);
		static VIPRESULT getDifference(vipFrameT<float>& diff_img, vipFrameT<float>& source_img, vipFrameT<float>& second_img);


		static VIPRESULT getDifference(vipFrameYUV420& diff_img, vipFrameYUV420& source_img, vipFrameYUV420& second_img);
		static VIPRESULT getDifference(vipFrameRGB24& diff_img, vipFrameRGB24& source_img, vipFrameRGB24& second_img);


		/**
		 * @brief Inherited class must implement this function,
		 *        should reset all filters' parameters, something like
		 *        constructor initialization.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 */
		virtual VIPRESULT reset() = 0;




		/**
		 * @brief Inherited class must implement this function,
		 *        processing frames to specific output (device or stream)
		 *
		 * @param[in] img VIPLib Cache Frame to be processed (encoded for example)
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note   Input operator (<<) call directly this function.
		 * @see    operator << (vipFrameYUV420&)
		 */
		virtual VIPRESULT importFrom(vipFrameYUV420& img) = 0;

		/**
		 * @brief Inherited class must implement this function,
		 *        processing frames to specific output (device or stream)
		 *
		 * @param[in] img VIPLib Cache24 Frame to be processed (encoded for example)
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note   Input operator (<<) call directly this function.
		 * @see    operator << (vipFrameRGB24&)
		 */
		virtual VIPRESULT importFrom(vipFrameRGB24& img) = 0;


		/**
		 * @brief Inherited class must implement this function,
		 *        processing frames to specific output (device or stream)
		 *
		 * @param[in] img Greyscale VIPLib Frame to be processed (encoded for example)
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note   Input operator (<<) call directly this function.
		 * @see    operator << (vipFrameT&)
		 */
		virtual VIPRESULT importFrom(vipFrameT<unsigned char>& img) = 0;







		enum{ vipClassType = VIPCLASS_TYPE_VISION };	//because of VC6 BUG
 };



////////////////////////////////////////////////////////////////////////////////////////////////


class vipVisionParameters
 {

	protected:

		bool doAlert;
		bool doEval;
		/**
		 * @brief  Default constructor, protected but inherited classes may
		 *         overload to public.
		 */
		vipVisionParameters() { }

	public:

		/**
		 * @brief  Default destructor.
		 */
		virtual ~vipVisionParameters() {}


		void setDoEval(bool value = true);
		void setDoAlert(bool value = true);

		/**
		 * @brief  Serialize class to XML file.
		 *         Open file stream and call inherited saveToStreamXML()
		 *         to save specific data structures.
		 *
		 * @param[in] filename output file name (NULL Terminated string)
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
		 */
		VIPRESULT saveToXML(const char* filename);

		/**
		 * @brief  Deserialize class from XML file.
		 *         Open file stream and call inherited loadFromStreamXML()
		 *         to load specific data structures.
		 *
		 * @param[in] filename input file name (NULL Terminated string)
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
		 */
		VIPRESULT loadFromXML(const char* filename);



		/**
		 * @brief  Serialize class to XML format.
		 *         Class' tag is <vipCoder_MOVParameters>
		 *
		 * @param[in] fp output stream's pointer
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
		 */
		virtual VIPRESULT saveToStreamXML(FILE *fp) = 0;

		/**
		 * @brief  Deserialize class from XML format.
		 *         Class' tag must be <vipCoder_MOVParameters>
		 *
		 * @param[in] fp input stream's pointer
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR else.
		 */
		virtual VIPRESULT loadFromStreamXML(FILE *fp) = 0;

 };


#endif //__VIPLIB_VIPVISION_H__

