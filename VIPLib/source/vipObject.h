/**
 *  @class   vipObject
 *
 *  @brief   An abrstract, base, class designed for many VIPLib's objects,
 *           currently it just defines some methods.
 *
 *
 *  @bug
 *  @warning
 *  @todo
 *
 *  @see
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



#ifndef __VIPLIB_VIPOBJECT_H__
 #define __VIPLIB_VIPOBJECT_H__



 #include "vipDefs.h"



class vipObject
 {
	protected:

		/**
		 * @var   Stores (inherited class) filter name, currently max 64 chars.
		 *        Char Array is initialized in constructor.
		 *
		 * @see   vipFilter()
		 * @see   setName()
		 */
		char* f_name;

		/**
		 * @var   Stores (inherited class) filter name, currently max 64 chars.
		 *        Char Array is initialized in constructor.
		 *
		 * @see   vipFilter()
		 * @see   setDescription()
		 */
		char* f_description;

		/**
		 * @var   Stores (inherited class) filter name, currently max 64 chars.
		 *        Initialized in constructor with 0.0.
		 *
		 * @see   vipFilter()
		 * @see   setVersion()
		 */
		double f_version;

		/**
		 * @brief  Set Filter's name.
		 *         Protected so only inherited classes can update their name.
		 *
		 * @param myName a (null terminated) string (max lenght 64).
		 * @see    f_name
		 */
		void setName(const char* myName);

		/**
		 * @brief  Set Filter's description.
		 *         Protected so only inherited classes can update their name.
		 *
		 * @param myDesc a (null terminated) string (max lenght 128).
		 * @see    f_description
		 */
		void setDescription(const char* myDesc);

		/**
		 * @brief  Set Filter's version.
		 *         Protected so only inherited classes can update their name.
		 *
		 * @param myVersion version number.
		 * @see    f_version
		 */
		void setVersion(const double myVersion);


	public:


		/**
		 * @brief Default public constructor.
		 */
		vipObject();

		/**
		 * @brief Destructor currenly clear only filters description strings.
		 */
		virtual ~vipObject();


		/**
		 * @brief  Get Filter's name.
		 *
		 * @return a (null terminated) string (max lenght 64).
		 * @see    f_name
		 */
		char* getName() const { return f_name; };

		/**
		 * @brief  Get Filter's description.
		 *
		 * @return a (null terminated) string (max lenght 128).
		 * @see    f_description
		 */
		char* getDescription() const { return f_description; };

		/**
		 * @brief  Get Filter's version.
		 *
		 * @return current version as a floating point value.
		 * @see    f_version
		 */
		double getVersion() const { return f_version; };



/*
		virtual VIPRESULT reset() = 0;
		virtual vipObject* clone() = 0;
		virtual DOUBLE getGUID() = 0;
		virtual VIPRESULT getChildObjects(void**, unsigned int objCount);
		virtual VIPRESULT getOwnerObjects(void**, unsigned int objCount);

*/

		void* getPointer() { return static_cast<void*>( this ); }



		/**
		 * @brief  Ignore this, it's a class-type definition, mostly used
		 *         by VIPLib WorkShop, sintax is a bit more complex than
		 *         usual because of a VC6 BUG, it's the same as:
		 *         const int vipClassType = VIPCLASS_TYPE_OBJECT;
		 */
		enum{ vipClassType = VIPCLASS_TYPE_OBJECT };

 };




#endif //__VIPLIB_VIPOBJECT_H__

