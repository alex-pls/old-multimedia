#include "StdAfx.h"
#include "viewForm.h"
#include "Form1.h"


namespace vipWS3
{


System::Void viewForm::viewForm_Closed(System::Object *  sender, System::EventArgs *  e)
 {
	static_cast<Form1*>(this->MdiParent)->updateChildFormsList();
 }



}
