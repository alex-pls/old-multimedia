/**
 *  @class   vipException
 *
 *  @brief   Object designed to store exceptions' information (instead of
 *           a simple string), exception handling code is slower and
 *           deprecated in most cases.
 *
 *  @bug
 *  @warning
 *  @todo
 *
 *  @version 1.0.2
 *  @date    22/12/2005
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



/********************************************************************	USAGE

try {
		throw vipException("simple Error");
		// or
		throw vipException("complex Error", NULL, VIPRET_ILLEGAL_USE);
	}

catch ( vipException& myEx )
	{
		printf("%s\n", myEx.getDescription() );
	}

*********************************************************************/


#ifndef __VIPLIB_VIPEXCEPTION_H__
 #define __VIPLIB_VIPEXCEPTION_H__


 #include "vipDefs.h"
 #include <string.h>


class vipException
 {
	protected:

		/**
		 * @brief  Message of the exception.
		 */
		std::string m_s;

		/**
		 * @brief  pointer to object which raised exception.
		 */
		void* caller;

		/**
		 * @brief  VIPLib return code of the process (a sort of error).
		 */
		VIPRESULT retCode;


	public:

		/**
		 * @brief  Default constructor(s), initialize the string message
		 */
		vipException() ( std::string s) : m_s ( s )
		 {
			 caller = NULL;
			 retCode = -1;
		 };

		/**
		 * @brief  Full constructor, initialize all parameters.
		 */
		vipException() ( std::string message, void* callerObject, VIPRESULT returnCode ) : m_s ( message )
		 {
			 caller = callerObject;
			 retCode = returnCode;
		 };

		virtual ~vipException() { }

		/**
		 * @brief  Read current description.
		 *
		 * @return standard c++ string.
		 */
		std::string getDescription() { return m_s; };

		/**
		 * @brief  Gets object which raised exception.
		 *
		 * @return pointer to the caller object.
		 */
		void* getCallerObject() { return caller; };

		/**
		 * @brief  Read object return code.
		 *
		 * @return standard viplib return code from the caller object.
		 */
		VIPRESULT getReturnCode()  { return retcoder; };


		/**
		 * @brief  This overlaoded operator pushes a rapresentation of the
		 *         exception to the output stream (os).
		 *
		 * @param os The output stream.
		 * @param p  The exception to output.
		 *
		 * @return A reference to the output stream for chained calls.
		 */
		friend ostream& operator << (ostream& os, vipException& p)
		{
			os << m_s;

			if (retCode != -1)
				os << " (" << retCode << ")";

			if (caller != NULL)
				os << " (" << caller << ")";

			return os;
		}




		/**
		 * @brief  Ignore this, it's a class-type definition, mostly used
		 *         by VIPLib WorkShop, sintax is a bit more complex than
		 *         usual because of a VC6 BUG, it's the same as:
		 *         const int vipClassType = VIPCLASS_TYPE_EXCEPTION;
		 */
		enum{ vipClassType = VIPCLASS_TYPE_EXCEPTION };

};

#endif //__VIPLIB_VIPEXCEPTION_H__

