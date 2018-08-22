/** @file    sourceInterface.h
 *  @class   sourceInterface
 *
 *  @brief   Interface for data source (ex. movie file).
 *
 *  @bug
 *  @warning
 *  @todo
 *
 *  @version 1.0
 *  @date    22/12/2005
 *  @author  Alessandro Polo
 *
 *
 ****************************************************************************
 * VIPLib Framework 1.0.2 - WorkShop 0.7.256
 *  Copyright (C) Alessandro Polo 2005
 *  http://www.ewgate.net/viplib
 *
 ****************************************************************************/


#pragma once

class vipFrameRGB24;
public __gc __interface outputInterface;
typedef int VIPRESULT;

public __gc __interface sourceInterface
{
//	void Init(void);

//	outputInterface* vF;
//	String getPlugInName();
	outputInterface* getOutputInterface();
	System::Object __gc* getObjectInstance();

	VIPRESULT extractTo(vipFrameRGB24* img);
	void viewsUpdate(void);


	void Init();

//	vipProcess* getMyProcess();

/*
virtual void extractTo(vipFrameRGB24* img) = 0;
virtual void viewsUpdate(void) = 0;
*/

};
