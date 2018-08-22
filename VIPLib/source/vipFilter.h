/**
 *  @class   vipFilter
 *
 *  @brief   Abstract class for all VIPLib filters, inherits vipInput
 *           and vipOutput classes both, extractTo() and importFrom()
 *           methods must be implemented but i/o operators may be
 *           overriden by inherited classes.
 *           Internal buffering implementation is left to inherited class.
 *
 *
 *  @see     vipInput, vipOutput, vipObject
 *
 *  @version 1.0.2
 *  @date    23/12/2005
 *  @author  Alessandro Polo
 *
 *
 ****************************************************************************/
/**
 *  @class   vipFilterParameters
 *
 *  @brief   This object is designed to store main filter's variables and
 *           (de)serialize data (from) to XML,
 *
 *  @version 1.0.2
 *  @date    23/12/2005
 *  @author  Alessandro Polo
 *
 ****************************************************************************/
/**
 * VIPLib Framework
 *  open source, founded by Alessandro Polo 2006
 *  http://mmlab.disi.unitn.it/projects/VIPLib
 *
 *  maintained by MultiMedia Laboratory - DISI - University of Trento
 *
 ****************************************************************************/



#ifndef __VIPLIB_VIPFILTER_H__
 #define __VIPLIB_VIPFILTER_H__

 #include "vipDefs.h"
 #include "vipObject.h"

 #include "vipInput.h"
 #include "vipOutput.h"

 #include "vipFrameYUV420.h"
 #include "vipFrameRGB24.h"
 #include "vipFrameT.h"


 #include <stdio.h>
 #include <fstream>


class vipFilterParameters
 {
	public:

		/**
		 * @brief  Selector of available buffer types in vipFilter class.
		 */
		enum BUFFER_TYPE { NONE, YUV, YUV444, RGB, TuC };

	protected:

		/**
		 * @brief  Selector of current buffer in vipFilter class (useful for
		 *         serialization).
		 */
		BUFFER_TYPE currentBuffer;

		/**
		 * @brief  Makes protected variables (currentBuffer) accessible from
		 *         vipFilter class.
		 */
		friend class vipFilter;

	public:

		/**
		 * @brief  Default constructor, call it in your constructor to init class.
		 */
		vipFilterParameters() {};//{ reset(); }

		/**
		 * @brief  Default destructor.
		 */
		virtual ~vipFilterParameters() {}

		/**
		 * @brief  Initialize stored variables to default values,
		 *         called also by constructor.
		 */
//		virtual void reset() = 0;


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




////////////////////////////////////////////////////////////////////////////////////////////////





class vipFilter :	public vipInput,
					public vipOutput,
					public vipObject
 {

	protected:

		/**
		 * @brief Our YUV buffer.
		 */
		vipFrameYUV420* bufferYUV;
		
		/**
		 * @brief Our YUV444 buffer.
		 */
		vipFrameYUV444* bufferYUV444;

		/**
		 * @brief Our RGB buffer.
		 */
		vipFrameRGB24* bufferRGB;

		/**
		 * @brief Our "Template" buffer.
		 */
		vipFrameT<unsigned char>* bufferTuC;


		/**
		 * @brief Allocate the buffer selected BUFFER_TYPE enumeration.
		 *
		 * @param bType select the buffer to initialize, if value is NONE
		 *        or unknown, all buffers are realeased.
		 */
		void allocateBuffer(vipFilterParameters::BUFFER_TYPE bType);

		/**
		 * @brief Close and free all buffers, then they are set to NULL.
		 */
		void releaseBuffers();

	public:


		/**
		 * @brief Default constructor is protected because this is an
		 *        abstract class and instance cannot be created directly.
		 *
		 * @param fps Frame per second value, default is 0, the max input+processing rate.
		 */
		vipFilter(float fps = 0);


		/**
		 * @brief Destructor currenly clear only filters description strings.
		 */
		~vipFilter();



		/**
		 * @brief Initialize Filter with any parameters needed, vipFilterParameters should be inherited
		 *		  and implemented for each filter, this is useful for vipProcess and multithreading,
		 *		  after initialization run() call will execute Filter specific processes described in parameters.
		 *
		 *
		 * @return VIPRET_OK if all is fine, VIPRET_PARAM_ERR if initParams is NULL or not valid,
		 *		   VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 */
		virtual VIPRESULT setFilterParameters (vipFilterParameters* initParams) = 0;



		virtual vipFilterParameters* getFilterParameters () = 0;



		/**
		 * @brief Inherited class must implement this function,
		 *        should reset all filters' parameters, something like
		 *        constructor initialization.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 */
		virtual VIPRESULT reset() = 0;



		/**
		 * @brief  Get YUV frame buffer's pointer.
		 *
		 * @note   DEPRECATED
		 *
		 * @return pointer to vipFrameYUV420 buffer or NULL if this buffer is disabled.
		 */
		vipFrameYUV420* dump_buffer_YUV() { return bufferYUV; };
		
		/**
		 * @brief  Get YUV frame buffer's pointer.
		 *
		 * @note   DEPRECATED
		 *
		 * @return pointer to vipFrameYUV444 buffer or NULL if this buffer is disabled.
		 */
		vipFrameYUV444* dump_buffer_YUV444() { return bufferYUV444; };

		/**
		 * @brief  Get RGB frame buffer's pointer.
		 *
		 * @note   DEPRECATED
		 *
		 * @return pointer to vipFrameRGB24 buffer or NULL if this buffer is disabled.
		 */
		vipFrameRGB24* dump_buffer_RGB() { return bufferRGB; };

		/**
		 * @brief  Get "Template" frame buffer's pointer.
		 *
		 * @note   DEPRECATED
		 *
		 * @return pointer to vipFrameT<uchar> buffer or NULL if this buffer is disabled.
		 */
		vipFrameT<unsigned char>* dump_buffer_TuC() { return bufferTuC; };

		/**
		 * @brief  Update and set current buffer (vipFrameYUV420) to new size.
		 * @param[in] width new buffer's width.
		 * @param[in] height new buffer's height.
		 */
		void useBufferYUV(unsigned int width, unsigned int height);
		
		/**
		 * @brief  Update and set current buffer (vipFrameYUV444) to new size.
		 * @param[in] width new buffer's width.
		 * @param[in] height new buffer's height.
		 */
		void useBufferYUV444(unsigned int width, unsigned int height);

		/**
		 * @brief  Update and set current buffer (vipFrameRGB24) to new size.
		 * @param[in] width new buffer's width.
		 * @param[in] height new buffer's height.
		 */
		void useBufferRGB(unsigned int width, unsigned int height);

		/**
		 * @brief  Update and set current buffer (vipFrameT<uchar>) to new size.
		 * @param[in] width new buffer's width.
		 * @param[in] height new buffer's height.
		 */
		void useBufferTuC(unsigned int width, unsigned int height, vipFrame::VIPFRAME_PROFILE profile);

		/**
		 * @brief  Evaluate is current buffer is a vipFrameYUV420.
		 *
		 * @return true is this is the current buffer, false else.
		 */
		bool isBufferYUV() { if ( bufferYUV != NULL ) return true; return false; };
		
		/**
		 * @brief  Evaluate is current buffer is a vipFrameYUV444.
		 *
		 * @return true is this is the current buffer, false else.
		 */
		bool isBufferYUV444() { if ( bufferYUV444 != NULL ) return true; return false; };

		/**
		 * @brief  Evaluate is current buffer is a vipFrameRGB24.
		 *
		 * @return true is this is the current buffer, false else.
		 */
		bool isBufferRGB() { if ( bufferRGB != NULL ) return true; return false; };

		/**
		 * @brief  Evaluate is current buffer is a vipFrameT<uchar>.
		 *
		 * @return true is this is the current buffer, false else.
		 */
		bool isBufferTuC() { if ( bufferTuC != NULL ) return true; return false; };


		/**
		 * @brief  Set current canvas' height.
		 *
		 * @return height in pixel.
		 */
		VIPRESULT setHeight(unsigned int value);

		/**
		 * @brief  Set current canvas' width.
		 *
		 * @return width in pixel.
		 */
		VIPRESULT setWidth(unsigned int value);

		/**
		 * @brief  Read current canvas's width.
		 *
		 * @return Width in pixel.
		 */
		unsigned int getWidth() const;


		/**
		 * @brief  Read current canvas's height.
		 *
		 * @return Height in pixel.
		 */
		unsigned int getHeight() const;


		/**
		 * @brief  Evaluate if there is any data to extract, current
		 *         implementation just check the state of current buffer.
		 *
		 * @return true if all buffers are empty.
		 */
		bool EoF();



		/**
		 * @brief This class offers a base implementatio of extraction methods, it
		 *        just copies current buffer to output image, no automatic conversion
		 *        is applied, formats must be the same.
		 *
		 * @param[out] img YUV 4:2:0 Frame to store data.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_ILLEGAL_USE if current
		 *		   buffer is in a different format.
		 *
		 * @note   Output operator (>>) call directly this function.
		 * @see    operator >> (vipFrameYUV420&)
		 */
		VIPRESULT extractTo(vipFrameYUV420& img);
		
		/**
		 * @brief This class offers a base implementatio of extraction methods, it
		 *        just copies current buffer to output image, no automatic conversion
		 *        is applied, formats must be the same.
		 *
		 * @param[out] img YUV 4:4:4 Frame to store data.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_ILLEGAL_USE if current
		 *		   buffer is in a different format.
		 *
		 * @note   Output operator (>>) call directly this function.
		 * @see    operator >> (vipFrameYUV444&)
		 */
		VIPRESULT extractTo(vipFrameYUV444& img);

		/**
		 * @brief This class offers a base implementatio of extraction methods, it
		 *        just copies current buffer to output image, no automatic conversion
		 *        is applied, formats must be the same.
		 *
		 * @param[out] img RGB24 Frame to store data.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_ILLEGAL_USE if current
		 *		   buffer is in a different format.
		 *
		 * @note   Output operator (>>) call directly this function.
		 * @see    operator >> (vipFrameRGB24&)
		 */
		VIPRESULT extractTo(vipFrameRGB24& img);

		/**
		 * @brief This class offers a base implementatio of extraction methods, it
		 *        just copies current buffer to output image, no automatic conversion
		 *        is applied, formats must be the same.
		 *
		 * @param[out] img vipFrameT image to store data.
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_ILLEGAL_USE if current
		 *		   buffer is in a different format or profile.
		 *
		 * @note   Output operator (>>) call directly this function.
		 * @see    operator >> (vipFrameT<unsigned char>&)
		 */
		VIPRESULT extractTo(vipFrameT<unsigned char>& img);



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
		 * @param[in] img VIPLib Cache Frame (YUV444) to be processed (encoded for example)
		 *
		 * @return VIPRET_OK if everything is fine, VIPRET_PARAM_ERR if frame
		 *		   is not valid, VIPRET_INTERNAL_ERR or VIPRET_ILLEGAL_USE else.
		 *
		 * @note   Input operator (<<) call directly this function.
		 * @see    operator << (vipFrameYUV444&)
		 */
		virtual VIPRESULT importFrom(vipFrameYUV444& img) = 0;
		

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



		/**
		 * @brief  Ignore this, it's a class-type definition, mostly used
		 *         by VIPLib WorkShop, sintax is a bit more complex than
		 *         usual because of a VC6 BUG, it's the same as:
		 *         const int vipClassType = VIPCLASS_TYPE_FILTER;
		 */
		enum{ vipClassType = VIPCLASS_TYPE_FILTER };

};



#endif //__VIPLIB_VIPFILTER_H__

