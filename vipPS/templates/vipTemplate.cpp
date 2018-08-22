/** @file %FILENAME%.cpp
 *
 * File containing methods for the '%CLASSNAME%' class.
 * The header for this class can be found in %FILENAME%.h, check that file
 * for class description.
 *
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



#include "%FILENAME%.h"


%VFI_START%
%CLASSNAME%::%CLASSNAME%()
 {
	INFO("%CLASSNAME%::%CLASSNAME%() [CONTRUCTOR]")
%EFI_START%
	reset();
%EFI_END%
 }
%VFI_END%

%VFI_START%
%CLASSNAME%::~%CLASSNAME%()
 {
	INFO("%CLASSNAME%::~%CLASSNAME%() [DESTRUCTOR]")

 }
%VFI_END%

%EFI_START%
%DOCFUN%/**
 * @brief  Reset ...
 *
 * @return VIPRET_OK
 */
VIPRESULT %CLASSNAME%::reset()
 {
	INFO("int %CLASSNAME%::reset() [SET DEFAULT PARAMETERS]")

	return VIPRET_OK;
 }
%EFI_END%

