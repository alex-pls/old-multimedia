/** @file vipObject.cpp
 *
 * File containing methods for the 'vipObject' class.
 * The header for this class can be found in vipObject.h, check that file
 * for class description.
 *
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



#include "vipObject.h"

#include <string.h>


/**
 * @brief Default constructor call vipInput constructor which setup frame rate,
 *        initialize description arrays and set default name (should be updated).
 *
 * @param fps Frame per second value, default is 0, the max input+processing rate.
 */
vipObject::vipObject()
 {
	f_name = new char[64];
	f_description = new char[128];

	setName("Unknown Object");
	setDescription("Unknown Object");
	setVersion(0.0);
 }


/**
 * @brief Destructor currenly clear only filters description strings.
 */
vipObject::~vipObject()
 {
	delete []f_name;
	delete []f_description;
 }

/**
 * @brief  Set Motion's name.
 *         Protected so only inherited classes can update their name.
 *
 * @param myName a (null terminated) string (max lenght 64).
 * @see    f_name
 */
void vipObject::setName(const char* myName)
 {
	strncpy(f_name, myName, 64);
 }


/**
 * @brief  Set Motion's description.
 *         Protected so only inherited classes can update their name.
 *
 * @param myDesc a (null terminated) string (max lenght 128).
 * @see    f_description
 */
void vipObject::setDescription(const char* myDesc)
 {
	strncpy(f_description, myDesc, 128);
 }

/**
 * @brief  Set Filter's version.
 *         Protected so only inherited classes can update their name.
 *
 * @param myVersion version number.
 * @see    f_version
 */
void vipObject::setVersion(const double myVer)
 {
	f_version = myVer;
 }
