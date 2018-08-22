/** @file
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
 *  @see
 *
 *  @version %VERSION%
 *  @date    %TODAY%
 *  @author  %AUTHOR%
 *
 ****************************************************************************
 *  Class based on Package Studio template: vipFilterTemplate version 0.9.12
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


 #include "%SOURCEDIR%vipDefs.h"


class %CLASSNAME%
 {
	protected:



	public:

%VFI_START%
		%CLASSNAME%();
%VFI_END%


%VFI_START%
		~%CLASSNAME%();
%VFI_END%


%EFI_START%
		%DOCFUN%/**
		 * @brief  Reset ...
		 *
		 * @return VIPRET_OK
		 */
		VIPRESULT reset();
%EFI_END%



 };

#endif //__VIPLIB_%CLASSDEFINE%_H__

