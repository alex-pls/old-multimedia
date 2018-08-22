/**
 *  @class   logForm
 *
 *  @brief   log viewver form (source)
 *
 *  @version 1.0.0
 *  @date    12/05/2006
 *  @author  Alessandro Polo
 *
 ****************************************************************************
 * VIPLib Package Studio
 *  open source - Founded by Alessandro Polo 2006
 *  http://mmlab.science.unitn.it/projects/vipPS
 *
 *  maintained by MultiMedia Laboratory - DIT - University of Trento
 *
 ****************************************************************************/


#include "StdAfx.h"
#include "logForm.h"
#include "vipPKStudio.h"


namespace vipPS
{



System::Void logForm::logForm_Closing(System::Object *  sender, System::ComponentModel::CancelEventArgs *  e)
 {
	e->Cancel = true;
	this->Visible = false;
//	static_cast<vipPKStudio*>(this->MdiParent)->updateChildFormsList();
 }

System::Void logForm::menuItem2_Click(System::Object *  sender, System::EventArgs *  e)
 {
	if ( !saveFileDialog1->InitialDirectory->Length)
		saveFileDialog1->InitialDirectory = Application::ExecutablePath;

	saveFileDialog1->FileName = S"vipPS.log";

	if ( saveFileDialog1->ShowDialog() == DialogResult::OK )
	 {
		this->Cursor = Cursors::WaitCursor;
		tBlog->SaveFile(saveFileDialog1->FileName);
		this->Cursor = Cursors::Default;
	 }
 }


System::Void logForm::menuItem4_Click(System::Object *  sender, System::EventArgs *  e)
 {
	tBlog->Clear();
 }

}