/** @file    %FILENAME%.h
 *  @class   %CLASSNAME%
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
 *  @see     vipBuffer
 *
 *  @version %VERSION%
 *  @date    %TODAY%
 *  @author  %AUTHOR%
 *
 ****************************************************************************
 *  Class based on Package Studio template: vipBufferTemplate version 0.9.12
 ****************************************************************************
 * VIPLib Framework
 *  open source, founded by Alessandro Polo 2006
 *  http://mmlab.science.unitn.it/projects/VIPLib
 *
 *  maintained by MultiMedia Laboratory - DIT - University of Trento
 *
 ****************************************************************************/


#ifndef __VIPLIB_%CLASSDEFINE%_H__
 #define __VIPLIB_%CLASSDEFINE%_H__

 #include "%SOURCEDIR%vipBuffer.h"


%EFI_START%
 #define VIPDEF_STACK_FRAMECOUNT			100  /*  */
 #define VIPDEF_STACK_FRAMEREALLOCSTEP		10  /*  */


 #define VIPDEF_FPS_MAX		        1000  /* maximum number of frames per second */
 #define VIPDEF_FCOUNT_MAX			32000  /* maximum number of frames */
%EFI_END%


template<class T>
class %CLASSNAME% : public vipBuffer<T>
 {

	protected:

%EFI_START%
		%DOCVAR%/**
		 * @brief  data pointers storage.
		 */
		T** v_frames;    	//frames* array

		%DOCVAR%/**
		 * @brief  current frame index.
		 */
		unsigned int v_current_frame;

		%DOCVAR%/**
		 * @brief  storage's size.
		 */
		unsigned int v_storageLenght;
%EFI_END%


	public:

%VFI_START%
		%DOCFUN%/**
		 * @brief  Default constructor, reset parameters and initialize superclass.
		 */
		%CLASSNAME%() : vipBuffer<T>()
		 {
			INFO("%CLASSNAME%::%CLASSNAME%()  : vipBuffer() [CONTRUCTOR]")
%EFI_START%
            v_frames = NULL;
			reset();
%EFI_END%
		 };
%VFI_END%

%VFI_START%
		%DOCFUN%/**
		 * @brief  Reset buffers' table and parameters, frame data is NOT cleaned!
		 *
		 * @return VIPRET_OK
		 */
		VIPRESULT reset()
		 {
			INFO("int %CLASSNAME%::reset() [SET DEFAULT PARAMETERS]")
%EFI_START%

			if (v_frames != NULL)
				delete v_frames;

			v_frames = NULL;
			v_fcount = 0;
			v_storageLenght = VIPDEF_STACK_FRAMECOUNT;
			v_current_frame = 0;
			copyData = true;

%EFI_END%
			return VIPRET_OK;
		 };
%VFI_END%

%VFI_START%
		%DOCFUN%/**
		 * @brief Default destructor, free frames' table but NOT frames!
		 */
		~%CLASSNAME%()
		 {
			INFO("%CLASSNAME%::~%CLASSNAME%() [DESTRUCTOR]")
%EFI_START%

            if (v_frames != NULL)
				delete v_frames;

%EFI_END%
		 };
%VFI_END%

%VFI_START%
		%DOCFUN%/**
		 * @brief  Delete all buffered frames (ALSO DATA) and reset buffer.
		 *
		 * @return VIPRET_ILLEGAL_USE if buffer is empty, VIPRET_OK else.
		 */
		VIPRESULT deleteFrames()
		 {
%EFI_START%

            if (v_frames != NULL)
			 {
				delete [] v_frames;
				v_frames = NULL;
				return reset();
			 }

%EFI_END%
			return VIPRET_ILLEGAL_USE;
		 };
%VFI_END%


%VFI_START%
		%DOCFUN%/**
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
%EFI_START%
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

%EFI_END%
			return VIPRET_OK;
		 };
%VFI_END%

%VFI_START%
		%DOCFUN%/**
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
%EFI_START%
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
%EFI_END%
			return VIPRET_OK;
		 };
%VFI_END%

%VFI_START%
		%DOCFUN%/**
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
%EFI_START%
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

%EFI_END%
			return VIPRET_OK;
		 };
%VFI_END%

%VFI_START%
		%DOCFUN%/**
		 * @brief  Remove selected frame, frame data is NOT cleaned!
		 *
		 * @param[in] frameToDelete address of frame to delete
		 *
		 * @return VIPRET_ILLEGAL_USE if buffer is empty, VIPRET_PARAM_ERR
		 *         if frame's address is not valid, VIPRET_OK else.
		 */
		VIPRESULT removeFrame(T* frameToDelete, bool freeData = false)
		 {
%EFI_START%
			if (v_frames == NULL)
				return VIPRET_ILLEGAL_USE;

			int i = 0;
			while ( i < v_fcount ) {

				if ( v_frames[i] == frameToDelete )
					return removeFrame(i, freeData);
				i++;
			 }

%EFI_END%
			return VIPRET_PARAM_ERR;
		 };
%VFI_END%

%VFI_START%
		%DOCFUN%/**
		 * @brief  Remove selected frame, frame data is NOT cleaned!
		 *
		 * @param[in] index frame's index to delete
		 *
		 * @return VIPRET_ILLEGAL_USE if buffer is empty, VIPRET_PARAM_ERR
		 *         if index is not valid, VIPRET_OK else.
		 */
		VIPRESULT removeFrame(long index, bool freeData = false)
		 {
			DEBUGMSG("int %CLASSNAME%::removeFrame(long index)", index)
%EFI_START%

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

%EFI_END%
			return VIPRET_OK;
		 };
%VFI_END%


%VFI_START%
		%DOCFUN%/**
		 * @brief  Get number of buffered frames.
		 *
		 * @return frames' count.
		 */
		long getCurrentFrameIndex() const
		 {
%EFI_START%
			return v_current_frame;
%EFI_END%
		 };

%VFI_END%


%VFI_START%
		%DOCFUN%/**
		 * @brief  Get selected frame.
		 *
		 * @param[in] index frame's index.
		 *
		 * @return address of selected frame.
		 */
		T* getFrame(long index)
		 {
%EFI_START%
			if (v_frames == NULL)
				throw "Buffer is empty.";
			if ( (int)index < 0 || (int)index >= v_fcount)
				throw "Index out of range.";

			return v_frames[ (int)index];
%EFI_END%
		 };
%VFI_END%

%VFI_START%
		%DOCFUN%/**
		 * @brief  Get current selected frame.
		 *
		 * @return address of current selected frame.
		 */
		T* getCurrentFrame()
		 {
%EFI_START%
			if (v_frames == NULL)
				throw "Video is Empty.";

			return v_frames[v_current_frame];
%EFI_END%
		 };
%VFI_END%

%VFI_START%
		%DOCFUN%/**
		 * @brief  Get previous frame (current-1).
		 *
		 * @return address of previous frame.
		 */
		T* getPreviousFrame()
		 {
%EFI_START%
			if (v_frames == NULL)
				throw "Video is Empty.";
			if ( v_current_frame < 1 || v_current_frame > (unsigned int)v_fcount)
				throw "Index out of range.";

			return v_frames[v_current_frame-1];
%EFI_END%
		 };
%VFI_END%

%VFI_START%
		%DOCFUN%/**
		 * @brief  Get next frame (current+1).
		 *
		 * @return address of next frame.
		 */
		T* getNextFrame()
		 {
%EFI_START%
			if (v_frames == NULL)
				throw "Video is Empty.";
			if ( v_current_frame > (unsigned int)v_fcount-2)
				throw "Index out of range.";

			return v_frames[v_current_frame+1];
%EFI_END%
		 };
%VFI_END%

%VFI_START%
		%DOCFUN%/**
		 * @brief  Get first frame (0).
		 *
		 * @return address of first frame.
		 */
		T* getFirstFrame()
		 {
%EFI_START%
			if ( v_frames == NULL )
				throw "Video is Empty.";

			return v_frames[0];
%EFI_END%
		 };
%VFI_END%

%VFI_START%
		%DOCFUN%/**
		 * @brief  Get last frame (v_fcount).
		 *
		 * @return address of last frame.
		 */
		T* getLastFrame()
		 {
%EFI_START%
			if ( v_frames == NULL )
				throw "Video is Empty.";

			return v_frames[v_fcount-1];
%EFI_END%
		 };
%VFI_END%

%VFI_START%
		%DOCFUN%/**
		 * @brief  Move current frame's index to next frame (v_current_frame++).
		 *
		 * @return VIPRET_ILLEGAL_USE if buffer is empty or if current index
		 *         is greater than buffer's size, VIPRET_OK else.
		 */
		VIPRESULT goToNextFrame()
		 {
			INFO("int %CLASSNAME%::goToNextFrame()")
%EFI_START%

			if ( v_frames == NULL )
				return VIPRET_ILLEGAL_USE;

			if ( v_current_frame > (unsigned int)v_fcount-2)
				return VIPRET_ILLEGAL_USE;

			v_current_frame++;

%EFI_END%
			return VIPRET_OK;
		 };
%VFI_END%

%VFI_START%
		%DOCFUN%/**
		 * @brief  Move current frame's index to previous frame (v_current_frame--).
		 *
		 * @return VIPRET_ILLEGAL_USE if buffer is empty or if current index
		 *         is 0, VIPRET_OK else.
		 */
		VIPRESULT goToPreviousFrame()
		 {
%EFI_START%
			if ( v_frames == NULL )
				return VIPRET_ILLEGAL_USE;

			if ( v_current_frame == 0 )
				return VIPRET_ILLEGAL_USE;

			v_current_frame--;

%EFI_END%
			return VIPRET_OK;
		 };
%VFI_END%

%VFI_START%
		%DOCFUN%/**
		 * @brief  Move current frame's index to first frame (v_current_frame=0).
		 *
		 * @return VIPRET_ILLEGAL_USE if buffer is empty, VIPRET_OK else.
		 */
		VIPRESULT goToFirstFrame()
		 {
			INFO("int %CLASSNAME%::goToFirstFrame()")
%EFI_START%
			if ( v_frames == NULL )
				return VIPRET_ILLEGAL_USE;

			v_current_frame = 0;

%EFI_END%
			return VIPRET_OK;
		 };
%VFI_END%

%VFI_START%
		%DOCFUN%/**
		 * @brief  Move current frame's index to last frame (v_current_frame=v_fcount-1).
		 *
		 * @return VIPRET_ILLEGAL_USE if buffer is empty, VIPRET_OK else.
		 */
		VIPRESULT goToLastFrame()
		 {
			INFO("int %CLASSNAME%::goToLastFrame()")
%EFI_START%

			if ( v_frames == NULL )
				return VIPRET_ILLEGAL_USE;

			v_current_frame = v_fcount-1;

%EFI_END%
			return VIPRET_OK;
		 };
%VFI_END%

%VFI_START%
		%DOCFUN%/**
		 * @brief  Move current frame's index to argument (v_current_frame=index).
		 *
		 * @param[in] index frame index to set.
		 *
		 * @return VIPRET_ILLEGAL_USE if buffer is empty, VIPRET_PARAM_ERR if index
		 *         is outside [0, v_fcount[, VIPRET_OK else.
		 */
		VIPRESULT goToFrame(long index)
		 {
			DEBUGMSG("int %CLASSNAME%::goToFrame(long index)", index)
%EFI_START%

			if ( v_frames == NULL )
				return VIPRET_ILLEGAL_USE;

			if ( (int)index < 0 || (int)index >= v_fcount)
				return VIPRET_PARAM_ERR;

			v_current_frame = (int)index;
%EFI_END%
			return VIPRET_OK;
		 };
%VFI_END%

%VFI_START%
		%DOCFUN%/**
		 * @brief  Move current frame's index adding argument to current index
		 *         (v_current_frame+=offset).
		 * @param[in] offset number of frame to add to index (positive or negative).
		 *
		 * @return VIPRET_ILLEGAL_USE if buffer is empty, VIPRET_PARAM_ERR if final index
		 *         is outside [0, v_fcount[, VIPRET_OK else.
		 */
		VIPRESULT goToStepFrame(long offset)
		 {
			DEBUGMSG("int %CLASSNAME%::goToStepFrame(long offset)", offset)
%EFI_START%

			if ( v_frames == NULL )
				return VIPRET_ILLEGAL_USE;

			if (   ( offset > 0 && v_current_frame + (int)offset < (unsigned int)v_fcount-1)
				 ||( offset < 0 && v_current_frame + (int)offset > 0)	 ) {

				v_current_frame = v_current_frame + (int)offset;
				return VIPRET_OK;
			 }

			return VIPRET_PARAM_ERR;
%EFI_END%
		 };
%VFI_END%




 };


#endif //__VIPLIB_%CLASSDEFINE%_H__