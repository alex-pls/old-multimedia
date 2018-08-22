/**
 *  @class   vipBuffer
 *
 *  @brief   Abstract template class for all VIPLib buffers.
 *
 *  @bug
 *  @warning
 *  @todo
 *
 *  @version 1.0.2
 *  @date    23/12/2005
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



#ifndef __VIPLIB_VIPBUFFER_H__
 #define __VIPLIB_VIPBUFFER_H__

 #include "vipDefs.h"


template<class T>
class vipBuffer
 {
	protected:


		/**
		 * @brief  buffered frames' count.
		 */
		long v_fcount;


		/**
		 * @brief  if true frame are copied, not linked.
		 */
		bool copyData;

	public:


		/**
		 * @brief Default constructor must be public.
		 */
		vipBuffer()  { }


		/**
		 * @brief Default virtual destructor.
		 */
		virtual ~vipBuffer() { }



		/**
		 * @brief  Tell the component to copy frames' data.
		 *
		 * @param[in] value if true data will be copied, else only pointer is stored.
		 *
		 * @see docpyData
		 */
		void setDoDataCopy(bool value = true)
		 {
			copyData = value;
		 };

		/**
		 * @brief  Get the state data-copy.
		 *
		 * @return if true data will be copied, else only pointer is stored.
		 */
		bool isDataCopyEnabled() const { return copyData; };


		/**
		 * @brief  Reset buffers' table and parameters, frame data is NOT cleaned!
		 *
		 * @return VIPRET_OK
		 */
		virtual VIPRESULT reset() = 0;


		/**
		 * @brief  Delete all buffered frames and reset buffer.
		 *
		 * @return VIPRET_ILLEGAL_USE if buffer is empty, VIPRET_OK else.
		 */
		virtual VIPRESULT deleteFrames() = 0;




		/**
		 * @brief  Add a new frame to the buffer, frames' count is updated.
		 *         (new frame index will be v_fcount)
		 *
		 * @param[in] newFrame address of the new frame.
		 *
		 * @return VIPRET_ILLEGAL_USE if current count reached max (VIPDEF_FCOUNT_MAX),
		 *         VIPRET_OK else.
		 */
		virtual VIPRESULT addFrame(T* newFrame) = 0;

		/**
		 * @brief  Insert a frame at selected index. Following frames are moved.
		 *         frames' count is updated.
		 *
		 * @param[in] index position of the new frame.
		 * @param[in] newFrame address of the new frame.
		 *
		 * @return VIPRET_ILLEGAL_USE if current count reached max (VIPDEF_FCOUNT_MAX),
		 *         VIPRET_OK else.
		 */
		virtual VIPRESULT insertFrame(long index, T* newFrame) = 0;

		/**
		 * @brief  Update selected frame with new frame, old frame data is NOT cleaned!
		 *         Use this function only if you know what you are doing.
		 *
		 * @param[in] index old frame's index.
		 * @param[in] newFrame address of the updated frame.
		 *
		 * @return VIPRET_ILLEGAL_USE if buffer is empty, VIPRET_PARAM_ERR
		 *         if frame's address is not valid, VIPRET_OK else.
		 */
		virtual VIPRESULT updateFrame(long index, T* newFrame, bool removeold) = 0;




		/**
		 * @brief  Remove selected frame, frame data is NOT cleaned!
		 *
		 * @param[in] index frame's index to delete
		 *
		 * @return VIPRET_ILLEGAL_USE if buffer is empty, VIPRET_PARAM_ERR
		 *         if index is not valid, VIPRET_OK else.
		 */
		virtual VIPRESULT removeFrame(long index, bool freeData = false) = 0;

		/**
		 * @brief  Remove selected frame, frame data is NOT cleaned!
		 *
		 * @param[in] frameToDelete address of frame to delete
		 *
		 * @return VIPRET_ILLEGAL_USE if buffer is empty, VIPRET_PARAM_ERR
		 *         if frame's address is not valid, VIPRET_OK else.
		 */
		virtual VIPRESULT removeFrame(T* frameToDelete, bool freeData = false) = 0;




		/**
		 * @brief  Get number of buffered frames.
		 *
		 * @return frames' count.
		 *
		 * @see    v_fcount
		 */
		long getFramesCount() const { return v_fcount; };

		/**
		 * @brief  Get id of current frame.
		 *
		 * @return frame's index.
		 */
		virtual long getCurrentFrameIndex() const = 0;

		/**
		 * @brief  Get selected frame.
		 *
		 * @param[in] index frame's index.
		 *
		 * @return address of selected frame.
		 */
		virtual T* getFrame(long index) = 0;

		/**
		 * @brief  Move current frame's index to next frame (v_current_frame++).
		 *
		 * @return VIPRET_ILLEGAL_USE if buffer is empty or if current index
		 *         is greater than buffer's size, VIPRET_OK else.
		 */
		virtual VIPRESULT goToNextFrame() = 0;

		/**
		 * @brief  Move current frame's index to previous frame (v_current_frame--).
		 *
		 * @return VIPRET_ILLEGAL_USE if buffer is empty or if current index
		 *         is 0, VIPRET_OK else.
		 */
		virtual VIPRESULT goToPreviousFrame() = 0;

		/**
		 * @brief  Move current frame's index to first frame (v_current_frame=0).
		 *
		 * @return VIPRET_ILLEGAL_USE if buffer is empty, VIPRET_OK else.
		 */
		virtual VIPRESULT goToFirstFrame() = 0;

		/**
		 * @brief  Move current frame's index to last frame (v_current_frame=v_fcount-1).
		 *
		 * @return VIPRET_ILLEGAL_USE if buffer is empty, VIPRET_OK else.
		 */
		virtual VIPRESULT goToLastFrame() = 0;

		/**
		 * @brief  Move current frame's index to argument (v_current_frame=index).
		 *
		 * @param[in] index frame index to set.
		 *
		 * @return VIPRET_ILLEGAL_USE if buffer is empty, VIPRET_PARAM_ERR if index
		 *         is outside [0, v_fcount[, VIPRET_OK else.
		 */
		virtual VIPRESULT goToFrame(long index) = 0;

		/**
		 * @brief  Move current frame's index adding argument to current index
		 *         (v_current_frame+=offset).
		 * @param[in] offset number of frame to add to index (positive or negative).
		 *
		 * @return VIPRET_ILLEGAL_USE if buffer is empty, VIPRET_PARAM_ERR if final index
		 *         is outside [0, v_fcount[, VIPRET_OK else.
		 */
		virtual VIPRESULT goToStepFrame(long offset) = 0;


		/**
		 * @brief  Get last frame (v_fcount).
		 *
		 * @return address of last frame.
		 */
		virtual T* getLastFrame() = 0;

		/**
		 * @brief  Get first frame (0).
		 *
		 * @return address of first frame.
		 */
		virtual T* getFirstFrame() = 0;

		/**
		 * @brief  Get next frame (current+1).
		 *
		 * @return address of next frame.
		 */
		virtual T* getNextFrame() = 0;

		/**
		 * @brief  Get previous frame (current-1).
		 *
		 * @return address of previous frame.
		 */
		virtual T* getPreviousFrame() = 0;

		/**
		 * @brief  Get current selected frame.
		 *
		 * @return address of current selected frame.
		 */
		virtual T* getCurrentFrame() = 0;

		/**
		 * @brief  Ignore this, it's a class-type definition, mostly used
		 *         by VIPLib WorkShop, sintax is a bit more complex than
		 *         usual because of a VC6 BUG, it's the same as:
		 *         const int vipClassType = VIPCLASS_TYPE_BUFFER;
		 */
		enum{ vipClassType = VIPCLASS_TYPE_BUFFER };

 };


#endif //__VIPLIB_VIPBUFFER_H__

