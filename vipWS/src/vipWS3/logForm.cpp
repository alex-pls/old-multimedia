#include "StdAfx.h"
#include "logForm.h"
#include "Form1.h"


namespace vipWS3
{



System::Void logForm::logForm_Closing(System::Object *  sender, System::ComponentModel::CancelEventArgs *  e)
 {
	e->Cancel = true;
	this->Visible = false;
	static_cast<Form1*>(this->MdiParent)->updateChildFormsList();
 }

System::Void logForm::menuItem2_Click(System::Object *  sender, System::EventArgs *  e)
 {
	if ( !saveFileDialog1->InitialDirectory->Length)
		saveFileDialog1->InitialDirectory = Application::ExecutablePath;

	saveFileDialog1->FileName = S"vipWS.log";

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