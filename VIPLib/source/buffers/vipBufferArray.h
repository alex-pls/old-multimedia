/**
 *  @class   vipBufferArray
 *
 *  @brief
 *
 *
 *
 *
 *
 *  @bug
 *  @warning
 *  @todo
 *
 *  @see     vipFilter
 *  @see     vipFrameRGB
 *
 *  @version 0.9
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



#ifndef __VIPLIB_VIPBUFFERARRAY_H__
 #define __VIPLIB_VIPBUFFERARRAY_H__

 #include "../vipBuffer.h"


#define VIPDEF_STACK_FRAMECOUNT				100  /*  */
#define VIPDEF_STACK_FRAMEREALLOCSTEP		10  /*  */



#define VIPDEF_FPS_MAX		        1000  /* maximum number of frames per second */
#define VIPDEF_FCOUNT_MAX			32000  /* maximum number of frames */


template<class T>
class vipBufferArray : public vipBuffer<T>
 {

	protected:

		/**
		 * @brief  data pointers storage.
		 */
		T** v_frames;    	//frames* array

		/**
		 * @brief  current frame index.
		 */
		unsigned int v_current_frame;

		/**
		 * @brief  storage's size.
		 */
		unsigned int v_storageLenght;


	public:

		/**
		 * @brief  Default constructor, reset parameters and initialize superclass.
		 */
		vipBufferArray() : vipBuffer<T>()
		 {
			INFO("vipBufferArray::vipBufferArray()  : vipBuffer() [CONTRUCTOR]")
            v_frames = NULL;
			reset();
		 };

		/**
		 * @brief  Reset buffers' table and parameters, frame data is NOT cleaned!
		 *
		 * @return VIPRET_OK
		 */
		VIPRESULT reset()
		 {
			INFO("int vipBufferArray::reset() [SET DEFAULT PARAMETERS]")

			if (v_frames != NULL)
				delete v_frames;

			v_frames = NULL;
			v_fcount = 0;
			v_storageLenght = VIPDEF_STACK_FRAMECOUNT;
			v_current_frame = 0;
			copyData = true;

			return VIPRET_OK;
		 };

		/**
		 * @brief Default destructor, free frames' table but NOT frames!
		 */
		~vipBufferArray()
		 {
			INFO("vipBufferArray::~vipBufferArray() [DESTRUCTOR]")

            if (v_frames != NULL)
				delete v_frames;

		 };

		/**
		 * @brief  Delete all buffered frames (ALSO DATA) and reset buffer.
		 *
		 * @return VIPRET_ILLEGAL_USE if buffer is empty, VIPRET_OK else.
		 */
		VIPRESULT deleteFrames()
		 {
            if (v_frames != NULL)
			 {
				delete [] v_frames;
				v_frames = NULL;
				return reset();
			 }

			return VIPRET_ILLEGAL_USE;
		 };


		/**
		 * @brief  Add a new frame to the buffer, frames' count is updated.
		 *         (new frame index will be v_fcount)
		 *
		 * @param[in] newFrame address of the new frame.
		 *
		 * @return VIPRET_ILLEGAL_USE if current count reached max (VIPDEF_FCOUNT_MAX),
		 *         VIPRET_OK else.
		 */
		VIPRESULT addFrame(T* newFrame)
		 {
			if (v_fcount+1 > VIPDEF_FCOUNT_MAX)
				return VIPRET_ILLEGAL_USE;

			if (v_frames == NULL) // this one will be the first frame
			 {
				v_storageLenght = VIPDEF_STACK_FRAMECOUNT;
				// allocate a new frames array
				v_frames = new T*[v_storageLenght]; // first frames array allocation
				v_fcount = 1;
				// add the new frame
				if ( copyData )
					v_frames[0] = new T(*newFrame);
				else
					v_frames[0] = newFrame;

			 }
			else if (v_fcount < (long)v_storageLenght)  // there's enough space for this frame
			 {

				if ( copyData )
					v_frames[v_fcount] = new T(*newFrame);
				else
					v_frames[v_fcount] = newFrame;

				// update frame count to VetInfo
				++v_fcount;

			 }
			else {
				// recalculates new storage (array) length using default step size (>1)
				v_storageLenght = v_fcount + VIPDEF_STACK_FRAMEREALLOCSTEP;
				// allocate a new frames array
				T** new_frames = new T*[v_storageLenght];
				// copy frames* to the new array
				for (int i=0; i<v_fcount; i++) {
					new_frames[i] = v_frames[i];
				 }
				// remove old pointer and update with new array
				delete v_frames;
				v_frames = new_frames;
				// add the new frame
				if ( copyData )
					v_frames[v_fcount++] = new T(*newFrame);
				else
					v_frames[v_fcount++] = newFrame;
			 }


			return VIPRET_OK;
		 };

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
		VIPRESULT insertFrame(long index, T* newFrame)
		 {
			if (v_fcount+1 > VIPDEF_FCOUNT_MAX)
				return VIPRET_ILLEGAL_USE;

			if (v_frames == NULL) // this one will be the first frame
				return addFrame(newFrame);
			if ( index < 0 || index >= v_fcount)
				return VIPRET_PARAM_ERR;

			if (v_fcount < (long)v_storageLenght) {  // there's enough space for this frame
				//move frames* after INDEX one position next
				for (int i=v_fcount-1; i>=(int)index; i--) {
					v_frames[i+1] = v_frames[i];
				 }
				//insert the new frame
				if ( copyData )
					v_frames[index] = new T(*newFrame);
				else
					v_frames[index] = newFrame;

				++v_fcount;

			 }
			else {
				// recalculates new storage (array) length using default step size (>1)
				v_storageLenght = v_fcount + VIPDEF_STACK_FRAMEREALLOCSTEP;
				// allocate a new frames array
				T** new_frames = new T*[v_storageLenght];
				// copy frames* before INDEX to the new array
				for (int i=0; i<(int)index; i++) {
					new_frames[i] = v_frames[i];
				 }
				//insert the new frame
				if ( copyData )
					v_frames[index] = new T(*newFrame);
				else
					v_frames[index] = newFrame;
				// copy frames* after INDEX to the new array
				for (int j=(int)index; j<v_fcount; j++) {
					new_frames[j] = v_frames[j];
				 }
				// remove old pointer and update with new array
				delete v_frames;
				v_frames = new_frames;
				// update frame count to VetInfo
				++v_fcount;

			}
			return VIPRET_OK;
		 };

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
		VIPRESULT updateFrame(long index, T* newFrame, bool removeold)
		{
			if ( v_frames == NULL )
				return VIPRET_ILLEGAL_USE;
			if ( index < 0 || index >= v_fcount )
				return VIPRET_PARAM_ERR;

			// remove old frame
			if ( removeold )
				delete v_frames[ (int)index ];

			// update frame* with given address
			if ( copyData )
				v_frames[index] = new T(*newFrame);
			else
				v_frames[index] = newFrame;

			return VIPRET_OK;
		 };

		/**
		 * @brief  Remove selected frame, frame data is NOT cleaned!
		 *
		 * @param[in] frameToDelete address of frame to delete
		 *
		 * @return VIPRET_ILLEGAL_USE if buffer is empty, VIPRET_PARAM_ERR
		 *         if frame's address is not valid, VIPRET_OK else.
		 */
		VIPRESULT removeFrame(T* frameToDelete, bool freeData = false)
		 {
			if (v_frames == NULL)
				return VIPRET_ILLEGAL_USE;

			int i = 0;
			while ( i < v_fcount ) {

				if ( v_frames[i] == frameToDelete )
					return removeFrame(i, freeData);
				i++;
			 }

			return VIPRET_PARAM_ERR;

		 };

		/**
		 * @brief  Remove selected frame, frame data is NOT cleaned!
		 *
		 * @param[in] index frame's index to delete
		 *
		 * @return VIPRET_ILLEGAL_USE if buffer is empty, VIPRET_PARAM_ERR
		 *         if index is not valid, VIPRET_OK else.
		 */
		VIPRESULT removeFrame(long index, bool freeData = false)
		 {
			DEBUGMSG("int vipBufferArray::removeFrame(long index)", index)

			if (v_frames == NULL)
				return VIPRET_ILLEGAL_USE;
			if ( index < 0 || index >= v_fcount)
				return VIPRET_PARAM_ERR;

			if ( freeData )
				delete v_frames[index];

			//move frames* after INDEX one position back
			for (int i=(int)index; i<v_fcount-1; i++) {
				v_frames[i] = v_frames[i+1];
			 }

			--v_fcount;

			return VIPRET_OK;
		 };


		/**
		 * @brief  Get number of buffered frames.
		 *
		 * @return frames' count.
		 */
		long getCurrentFrameIndex() const { return v_current_frame; };



		/**
		 * @brief  Get selected frame.
		 *
		 * @param[in] index frame's index.
		 *
		 * @return address of selected frame.
		 */
		T* getFrame(long index)
		 {
			if (v_frames == NULL)
				throw "Buffer is empty.";
			if ( (int)index < 0 || (int)index >= v_fcount)
				throw "Index out of range.";

			return v_frames[ (int)index];
		 };

		/**
		 * @brief  Get current selected frame.
		 *
		 * @return address of current selected frame.
		 */
		T* getCurrentFrame()
		 {
			if (v_frames == NULL)
				throw "Video is Empty.";

			return v_frames[v_current_frame];
		 };

		/**
		 * @brief  Get previous frame (current-1).
		 *
		 * @return address of previous frame.
		 */
		T* getPreviousFrame()
		 {
			if (v_frames == NULL)
				throw "Video is Empty.";
			if ( v_current_frame < 1 || v_current_frame > (unsigned int)v_fcount)
				throw "Index out of range.";

			return v_frames[v_current_frame-1];
		 };

		/**
		 * @brief  Get next frame (current+1).
		 *
		 * @return address of next frame.
		 */
		T* getNextFrame()
		 {
			if (v_frames == NULL)
				throw "Video is Empty.";
			if ( v_current_frame > (unsigned int)v_fcount-2)
				throw "Index out of range.";

			return v_frames[v_current_frame+1];
		 };

		/**
		 * @brief  Get first frame (0).
		 *
		 * @return address of first frame.
		 */
		T* getFirstFrame()
		 {
			if ( v_frames == NULL )
				throw "Video is Empty.";

			return v_frames[0];
		 };

		/**
		 * @brief  Get last frame (v_fcount).
		 *
		 * @return address of last frame.
		 */
		T* getLastFrame()
		 {
			if ( v_frames == NULL )
				throw "Video is Empty.";

			return v_frames[v_fcount-1];
		 };

		/**
		 * @brief  Move current frame's index to next frame (v_current_frame++).
		 *
		 * @return VIPRET_ILLEGAL_USE if buffer is empty or if current index
		 *         is greater than buffer's size, VIPRET_OK else.
		 */
		VIPRESULT goToNextFrame()
		 {
			INFO("int vipBufferArray::goToNextFrame()")

			if ( v_frames == NULL )
				return VIPRET_ILLEGAL_USE;

			if ( v_current_frame > (unsigned int)v_fcount-2)
				return VIPRET_ILLEGAL_USE;

			v_current_frame++;

			return VIPRET_OK;
		 };

		/**
		 * @brief  Move current frame's index to previous frame (v_current_frame--).
		 *
		 * @return VIPRET_ILLEGAL_USE if buffer is empty or if current index
		 *         is 0, VIPRET_OK else.
		 */
		VIPRESULT goToPreviousFrame()
		 {
			INFO("")

			if ( v_frames == NULL )
				return VIPRET_ILLEGAL_USE;

			if ( v_current_frame == 0 )
				return VIPRET_ILLEGAL_USE;

			v_current_frame--;

			return VIPRET_OK;
		 };

		/**
		 * @brief  Move current frame's index to first frame (v_current_frame=0).
		 *
		 * @return VIPRET_ILLEGAL_USE if buffer is empty, VIPRET_OK else.
		 */
		VIPRESULT goToFirstFrame()
		 {
			INFO("int vipBufferArray::goToFirstFrame()")
			if ( v_frames == NULL )
				return VIPRET_ILLEGAL_USE;

			v_current_frame = 0;


			return VIPRET_OK;
		 };

		/**
		 * @brief  Move current frame's index to last frame (v_current_frame=v_fcount-1).
		 *
		 * @return VIPRET_ILLEGAL_USE if buffer is empty, VIPRET_OK else.
		 */
		VIPRESULT goToLastFrame()
		 {
			INFO("int vipBufferArray::goToLastFrame()")

			if ( v_frames == NULL )
				return VIPRET_ILLEGAL_USE;

			v_current_frame = v_fcount-1;


			return VIPRET_OK;
		 };

		/**
		 * @brief  Move current frame's index to argument (v_current_frame=index).
		 *
		 * @param[in] index frame index to set.
		 *
		 * @return VIPRET_ILLEGAL_USE if buffer is empty, VIPRET_PARAM_ERR if index
		 *         is outside [0, v_fcount[, VIPRET_OK else.
		 */
		VIPRESULT goToFrame(long index)
		 {
			DEBUGMSG("int vipBufferArray::goToFrame(long index)", index)

			if ( v_frames == NULL )
				return VIPRET_ILLEGAL_USE;

			if ( (int)index < 0 || (int)index >= v_fcount)
				return VIPRET_PARAM_ERR;

			v_current_frame = (int)index;

			return VIPRET_OK;
		 };

		/**
		 * @brief  Move current frame's index adding argument to current index
		 *         (v_current_frame+=offset).
		 * @param[in] offset number of frame to add to index (positive or negative).
		 *
		 * @return VIPRET_ILLEGAL_USE if buffer is empty, VIPRET_PARAM_ERR if final index
		 *         is outside [0, v_fcount[, VIPRET_OK else.
		 */
		VIPRESULT goToStepFrame(long offset)
		 {
			DEBUGMSG("int vipBufferArray::goToStepFrame(long offset)", offset)

			if ( v_frames == NULL )
				return VIPRET_ILLEGAL_USE;

			if (   ( offset > 0 && v_current_frame + (int)offset < (unsigned int)v_fcount-1)
				 ||( offset < 0 && v_current_frame + (int)offset > 0)	 ) {

				v_current_frame = v_current_frame + (int)offset;
				return VIPRET_OK;
			 }

			return VIPRET_PARAM_ERR;
		 };




 };


#endif//__VIPLIB_VIPBUFFERARRAY_H__
