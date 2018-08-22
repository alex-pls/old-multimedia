/** @file vipObjectSample.cpp
 *
 * File containing methods for the 'vipObjectSample' class.
 * The header for this class can be found in vipObjectSample.h, check that file
 * for class description.
 *
 *
 ****************************************************************************
 *  Class based on Package Studio template: vipObjectTemplate version 0.9.12
 ****************************************************************************
 * VIPLib Framework
 *  open source, founded by Alessandro Polo 2006
 *  http://mmlab.science.unitn.it/projects/VIPLib
 *
 *  maintained by MultiMedia Laboratory - DIT - University of Trento
 *
 ****************************************************************************/



#include "vipObjectSample.h"



vipObjectSample::vipObjectSample() : vipObject()
 {
	INFO("vipObjectSample::vipObjectSample() : vipObject() [CONTRUCTOR]")

	reset();

	setName("vipObjectSample");
	setDescription("Unknown Object");
	setVersion(1.0);


 }



vipObjectSample::~vipObjectSample()
 {
	INFO("vipObjectSample::~vipObjectSample() [DESTRUCTOR]")

 }



/**
 * @brief  Reset ...
 *
 * @return VIPRET_OK
 */
VIPRESULT vipObjectSample::reset()
 {
	INFO("int vipObjectSample::reset() [SET DEFAULT PARAMETERS]")

	return VIPRET_OK;
 }


