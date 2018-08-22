/** @file    outputInterface.h
 *  @class   outputInterface
 *
 *  @brief   Interface for data output (ex. visualization window).
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
public __gc __interface sourceInterface;
typedef int VIPRESULT;

public __gc __interface outputInterface
{
	void Init(void);

	VIPRESULT importFrom(vipFrameRGB24* img);
	void sourcesUpdate(void);

	System::Object __gc* getObjectInstance();

	int setSource(sourceInterface* sF);

//	sourceInterface* getSourceInterface();
//	vipProcess* getMyProcess();


/*
virtual void importFrom(vipFrameRGB24* img) = 0;
virtual void sourcesUpdate(void) = 0;
*/

};
