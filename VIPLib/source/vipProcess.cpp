/** @file vipProcess.cpp
 *
 * File containing methods for the 'vipProcess' class.
 * The header for this class can be found in vipProcess.h, check that file
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



#include "vipProcess.h"



vipProcess::vipProcess()
 {

	v_isMultiThreadingEnabled = VIPDEF_MULITHREAD_ENABLED;
	v_MaxSimultaneousThread = VIPDEF_THREADs_MAX;

	f_name = new char[64];
	f_description = new char[128];

	setName("Abstract Filter");
	setDescription("Abstract Class");
	setVersion(0.0);
 }

vipProcess::~vipProcess()
 {
	delete f_name;
	delete f_description;

 }


VIPRESULT vipProcess::addFilter(vipFilter& aFilter)
 {

	return VIPRET_OK;
 }

VIPRESULT vipProcess::removeFilter(vipFilter& oldFilter)
 {

	return VIPRET_OK;
 }



VIPRESULT vipProcess::run()
 {

	return VIPRET_OK;
 }

VIPRESULT vipProcess::runOnce()
 {

	if ( v_source == NULL )
		return VIPRET_ILLEGAL_USE;

//	if ( v_out == NULL )
//		return VIPRET_ILLEGAL_USE;
/*
	width = v_source->getWidth();
	height = v_source->getHeight();

	vipFrameCache vfc(width, height);

	(*v_source) >> vfc;
	(*v_out) << vfc;
*/

	return VIPRET_OK;
 }


