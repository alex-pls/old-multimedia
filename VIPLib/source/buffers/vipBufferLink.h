/**
 *  @class   vipBufferLink
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




#ifndef __VIPLIB_VIPBUFFERLINK_H__
 #define __VIPLIB_VIPBUFFERLINK_H__

 #include "../vipBuffer.h"


#define VIPDEF_FPS_MAX		        1000  /* maximum number of frames per second */

#define VIPRET_FRAME_NOT_FOUND	    8254


template<class T>
class vipBufferLink : public vipBuffer<T>
 {
	protected:


		struct frameNode {
			T* data;
			struct frameNode * prev;
			struct frameNode * next;
		 };

		frameNode* v_first;
		frameNode* v_current;
		frameNode* v_last;



	public:


		/**
		 * @brief  Default constructor, reset parameters and initialize superclass.
		 */
		vipBufferLink() : vipBuffer<T>()
		 {
			INFO("vipBufferLink::vipBufferLink()  : vipBuffer() [CONTRUCTOR]")

			v_first = NULL;
			v_current = NULL;
			v_last = NULL;

			reset();
		 }

		/**
		 * @brief Default destructor, free frames' table but NOT frames!
		 */
		~vipBufferLink()
		 {
			INFO("vipBufferLink::~vipBufferLink() [DESTRUCTOR]")

			if ( v_first == NULL)
				return;

			v_current = v_first->next;

		 }

		/**
		 * @brief  Reset buffers' table and parameters, frame data is NOT cleaned!
		 *
		 * @return VIPRET_OK
		 */
		VIPRESULT reset()
		 {
			INFO("int vipBufferLink::reset() [SET DEFAULT PARAMETERS]")

			v_first = NULL;
			v_current = NULL;
			v_last = NULL;
			v_fcount = 0;

			return VIPRET_OK;
		 }

		/**
		 * @brief  Delete all buffered frames and reset buffer.
		 *
		 * @return VIPRET_ILLEGAL_USE if buffer is empty, VIPRET_OK else.
		 */
		VIPRESULT deleteFrames()
		 {
			if ( v_first != NULL)
			 {
				v_current = v_first->next;

				while ( v_current != NULL ) {
//BUGBUGBUG
					delete v_current->prev;
					delete v_current->data;
					v_current = v_current->next;
				 }

				delete v_last->data;
				delete v_last;
			 }
			else
				return VIPRET_ILLEGAL_USE;

			return reset();
		 }





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
			if ( &newFrame == NULL)
				return VIPRET_PARAM_ERR;

			if ( v_fcount == 0) {
				v_first = new frameNode;
				v_first->next = NULL;
				v_first->prev = NULL;

				if ( copyData )
					v_first->data = new T(*newFrame);
				else
					v_first->data = newFrame;

				v_current = v_first;
				v_last = v_first;
				++v_fcount;
				return VIPRET_OK;
			 }

			frameNode* v_newlast = new frameNode;

			if ( copyData )
				v_newlast->data = new T(*newFrame);
			else
				v_newlast->data = newFrame;

			v_newlast->prev = v_last;
			v_newlast->next = NULL;
			v_last->next = v_newlast;
			v_last = v_newlast;
			++v_fcount;

			return VIPRET_OK;
		 }

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
			if ( v_fcount == 0 && index != 0)
				return VIPRET_ILLEGAL_USE;

			if ( &newFrame == NULL)
				return VIPRET_PARAM_ERR;

			if ( v_fcount == 0 )
				return addFrame(newFrame);

			if ( index == v_fcount-1 )
				return addFrame(newFrame);

			if ( index == 0 )
			 {
				frameNode* v_newNode = new frameNode;

				if ( copyData )
					v_newNode->data = new T(*newFrame);
				else
					v_newNode->data = newFrame;

				v_newNode->prev = NULL;
				v_newNode->next = v_first;
				v_first->prev = v_newNode;
				v_first = v_newNode;
				++v_fcount;
				return VIPRET_OK;
			 }

			frameNode* iterFrame;
			iterFrame = v_first;
			long i = 0;
			while ( iterFrame )
			 {
				if ( i == index )
				 {
					frameNode* v_newNode = new frameNode;

					if ( copyData )
						v_newNode->data = new T(*newFrame);
					else
						v_newNode->data = newFrame;

					v_newNode->prev = iterFrame->prev;
					v_newNode->next = iterFrame;
					iterFrame->prev->next = v_newNode;
					iterFrame->prev = v_newNode;
					++v_fcount;
					return VIPRET_OK;
				 }
				iterFrame = iterFrame->next;
				i++;
			 }

			return VIPRET_INTERNAL_ERR;
		 }

		/**
		 * @brief  Update selected frame with new frame, optionally clean old frame's data.
		 *
		 * @param[in] oldFrame address of the old frame.
		 * @param[in] newFrame address of the new frame.
		 * @param[in] removeold if true old frame is deleted, else data is not released!
		 *
		 * @return VIPRET_ILLEGAL_USE if buffer is empty, VIPRET_PARAM_ERR
		 *         if frame's address is not valid, VIPRET_OK else.
		 */
		VIPRESULT updateFrame(T* oldFrame, T* newFrame, bool removeold)
		 {
			if ( v_fcount == 0)
				return VIPRET_ILLEGAL_USE;

			if ( &oldFrame == NULL || newFrame == NULL )
				return VIPRET_PARAM_ERR;

			frameNode* iterFrame;
			iterFrame = v_first;

			while ( iterFrame  )
			 {
				if ( iterFrame->data == oldFrame )
				 {
					if (removeold)
						delete oldFrame;

					if ( copyData )
						iterFrame->data = new T(*newFrame);
					else
						iterFrame->data = newFrame;

					return VIPRET_OK;
				 }
				iterFrame = iterFrame->next;
			 }

			return VIPRET_FRAME_NOT_FOUND;
		 }

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
			if ( v_fcount == 0)
				return VIPRET_ILLEGAL_USE;

			if ( &newFrame == NULL)
				return VIPRET_PARAM_ERR;

			if ( index > v_fcount-1 )
				return VIPRET_PARAM_ERR;

			long distEnd = v_fcount - index;
				frameNode* iterFrame;

			if ( index < distEnd )
			 {
				iterFrame = v_first;
				long i = 0;
				while ( iterFrame  )
				 {
					if ( i == index )
					 {
							if ( removeold )
								delete iterFrame->data;

							if ( copyData )
								iterFrame->data = new T(*newFrame);
							else
								iterFrame->data = newFrame;

							return VIPRET_OK;
					 }
					iterFrame = iterFrame->next;
					i++;
				 }
			 }
			else
			 {
				iterFrame = v_last;
				long i = v_fcount-1;
				while ( iterFrame  )
				 {
					if ( i == index )
					 {
						delete iterFrame->data;
						iterFrame->data = newFrame;
						return VIPRET_OK;
					 }
					iterFrame = iterFrame->prev;
					i--;
				 }
			 }

			return VIPRET_FRAME_NOT_FOUND;
		 }

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
			if ( v_fcount == 0)
				return VIPRET_ILLEGAL_USE;

			if ( frameToDelete == NULL)
				return VIPRET_PARAM_ERR;

			if ( v_fcount == 1)
			 {
				delete v_first;
				v_first = NULL;
				v_current = NULL;
				v_last = NULL;
				v_fcount = 0;
			 }

			if ( v_first->data == frameToDelete )
			 {
				v_first = v_first->next;
				delete v_first->prev;
				v_first->prev = NULL;
				--v_fcount;
				return VIPRET_OK;
			  }
			else if ( v_last->data == frameToDelete)
			 {
				v_last = v_last->prev;
				delete v_last->next;
				v_last->next = NULL;
				--v_fcount;
				return VIPRET_OK;
			 }

			frameNode* iterFrame;
			iterFrame = v_first->next;
			while ( iterFrame  )
			 {
				if ( iterFrame->data == frameToDelete )
				 {
					if ( freeData )
						delete frameToDelete;

					iterFrame->data = NULL;
					iterFrame->prev->next = iterFrame->next;
					iterFrame->next->prev = iterFrame->prev;

					delete iterFrame;
					--v_fcount;

					return VIPRET_OK;
				 }
				iterFrame = iterFrame->next;
			 }

			return VIPRET_FRAME_NOT_FOUND;

		 }

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
			if ( v_fcount == 0)
				return VIPRET_ILLEGAL_USE;

			if ( index >= v_fcount)
				return VIPRET_PARAM_ERR;

			if ( index == 0)
			 {
				v_first->next = v_first;
				delete v_first->prev;
				v_first->prev = NULL;
				return VIPRET_OK;
			 }
			else if ( index == v_fcount-1)
			 {
				v_last->prev = v_last;
				delete v_last->next;
				v_last->next = NULL;
				return VIPRET_OK;
			 }


			frameNode* iterFrame;
			iterFrame = v_first->next;
			long i = 0;
			while ( iterFrame  )
			 {
				if ( i == index )
				 {
					if ( freeData )
						delete iterFrame->data;

					iterFrame->data = NULL;
					iterFrame->prev->next = iterFrame->next;
					iterFrame->next->prev = iterFrame->prev;

					delete iterFrame;
					--v_fcount;

					return VIPRET_OK;
				 }
				iterFrame = iterFrame->next;
				i++;
			 }

			return VIPRET_FRAME_NOT_FOUND;
		 }

		/**
		 * @brief  Get current selected frame.
		 *
		 * @return address of current selected frame.
		 */
		T* getCurrentFrame()
		 {
			if ( v_fcount == 0)
				throw "Video is Empty.";

			return v_current->data;
 		 }

		/**
		 * @brief  Get previous frame (current-1).
		 *
		 * @return address of previous frame.
		 */
		T* getPreviousFrame()
		 {
			if ( v_fcount == 0)
				throw "Video is Empty.";

				if ( v_current->prev == NULL )
				throw "Out of range.";

			return v_current->prev->data;

		 }

		/**
		 * @brief  Get next frame (current+1).
		 *
		 * @return address of next frame.
		 */
		T* getNextFrame()
		 {
			if ( v_fcount == 0)
				throw "Video is Empty.";

				if ( v_current->next == NULL )
				throw "Out of range.";

			return v_current->next->data;

		 }

		/**
		 * @brief  Get first frame (0).
		 *
		 * @return address of first frame.
		 */
		T* getFirstFrame()
		 {
			if ( v_fcount == 0)
				throw "Video is Empty.";

			return v_first->data;
		 }


		/**
		 * @brief  Get last frame (v_fcount).
		 *
		 * @return address of last frame.
		 */
		T* getLastFrame()
		 {
			if ( v_fcount == 0)
				throw "Video is Empty.";

			return v_last->data;
		 }

		/**
		 * @brief  Get number of buffered frames.
		 *
		 * @return frames' count.
		 */
		long getCurrentFrameIndex() const
		 {
				frameNode* iterFrame;
				iterFrame = v_first;
				long i = 0;
				while ( iterFrame  )
				 {
					if ( iterFrame->data == v_current->data )
						return i;

					iterFrame = iterFrame->next;
					i++;
				 }

			return -1;
		 }


		/**
		 * @brief  Get selected frame.
		 *
		 * @param[in] index frame's index.
		 *
		 * @return address of selected frame.
		 */
		T* getFrame(long index)
		 {
			if ( v_fcount == 0)
				throw "Video is Empty.";

			if ( index < 0 || index >= v_fcount )
				throw "Out of range";

			long distEnd = v_fcount - index;

			if ( index < distEnd )
			 {

				frameNode* iterFrame;
				iterFrame = v_first;
				long i = 0;
				while ( iterFrame  )
				 {
					if ( i == index )
						return iterFrame->data;

					iterFrame = iterFrame->next;
					i++;
				 }

			 }
			else
			 {
				frameNode* iterFrame;
				iterFrame = v_last;
				long i = v_fcount-1;
				while ( iterFrame  )
				 {
					if ( i == index )
						return iterFrame->data;
					iterFrame = iterFrame->prev;
					i--;
				 }

			 }

			throw "Index not found, internal error.";
		 }

		/**
		 * @brief  Move current frame's index to next frame (v_current_frame++).
		 *
		 * @return VIPRET_ILLEGAL_USE if buffer is empty or if current index
		 *         is greater than buffer's size, VIPRET_OK else.
		 */
		VIPRESULT goToNextFrame()
		 {
			if ( v_fcount == 0)
				return VIPRET_ILLEGAL_USE;

			if ( v_current->next == NULL )
				return VIPRET_ILLEGAL_USE;

				v_current = v_current->next;

			return VIPRET_OK;
		 }

		/**
		 * @brief  Move current frame's index to previous frame (v_current_frame--).
		 *
		 * @return VIPRET_ILLEGAL_USE if buffer is empty or if current index
		 *         is 0, VIPRET_OK else.
		 */
		VIPRESULT goToPreviousFrame()
		 {
			if ( v_fcount == 0)
				return VIPRET_ILLEGAL_USE;

			if ( v_current->prev == NULL )
				return VIPRET_ILLEGAL_USE;

			v_current = v_current->prev;

			return VIPRET_OK;
		 }

		/**
		 * @brief  Move current frame's index to first frame (v_current_frame=0).
		 *
		 * @return VIPRET_ILLEGAL_USE if buffer is empty, VIPRET_OK else.
		 */
		VIPRESULT goToFirstFrame()
		 {
			if ( v_fcount == 0)
				return VIPRET_ILLEGAL_USE;

			v_current = v_first;

			return VIPRET_OK;
		 }

		/**
		 * @brief  Move current frame's index to last frame (v_current_frame=v_fcount-1).
		 *
		 * @return VIPRET_ILLEGAL_USE if buffer is empty, VIPRET_OK else.
		 */
		VIPRESULT goToLastFrame()
		 {
			if ( v_fcount == 0)
				return VIPRET_ILLEGAL_USE;

			v_current = v_last;

			return VIPRET_OK;
		 }

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
			if ( v_fcount == 0)
				return VIPRET_ILLEGAL_USE;

			if ( index < 0 || index >= v_fcount )
				return VIPRET_PARAM_ERR;

			long distEnd = v_fcount - index;

			if ( index < distEnd )
			 {
				frameNode* iterFrame;
				iterFrame = v_first;
				long i = 0;
				while ( iterFrame  )
				 {
					if ( i == index )
					 {
						v_current = iterFrame;
						return VIPRET_OK;
					 }
					iterFrame = iterFrame->next;
					i++;
				 }

			 }
			else
			 {
				frameNode* iterFrame;
				iterFrame = v_last;
				long i = v_fcount-1;
				while ( iterFrame  )
				 {
					if ( i == index )
					 {
						v_current = iterFrame;
						return VIPRET_OK;
					 }
					iterFrame = iterFrame->prev;
					i--;
				 }

			 }

			return VIPRET_INTERNAL_ERR;
		 }

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
			if ( v_fcount == 0 || offset == 0 )
				return VIPRET_ILLEGAL_USE;

			if ( offset >= v_fcount  || offset <= -v_fcount )
				return VIPRET_PARAM_ERR;

			frameNode* iterFrame;
			iterFrame = v_current;

			if ( offset > 0 )
			 {
				long i = 0;
				while ( iterFrame  )
				 {
					if ( i == offset )
					 {
						v_current = iterFrame;
						return VIPRET_OK;
					 }
					iterFrame = iterFrame->next;
					i++;
				 }

			 }
			else
			 {
				long i = v_fcount-1;
				while ( iterFrame  )
				 {
					if ( i == offset )
					 {
						v_current = iterFrame;
						return VIPRET_OK;
					 }
					iterFrame = iterFrame->prev;
					i--;
				 }

			 }

			return VIPRET_INTERNAL_ERR;
		 }





 };


#endif /* __VIPLIB_VIPBUFFERLINK_H__ */

