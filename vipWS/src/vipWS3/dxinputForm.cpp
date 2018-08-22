#include "StdAfx.h"
#include "dxinputForm.h"
#include "Form1.h"
#include "../../../../source/inputs/vipDirectXInput.h"

namespace vipWS3
{
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////// INIT, DISPOSE

dxinputForm::dxinputForm(void)
 {
	InitializeComponent();
	buffer = NULL;
	vF = NULL;
 }

void dxinputForm::Init()
 {
	 static_cast<Form1*>(this->MdiParent)->writeLog(S"Creating class: vipDirectXInput", this);
	 myCap = new vipDirectXInput();
 }

System::Void dxinputForm::dxinputForm_Load(System::Object *  sender, System::EventArgs *  e)
 {
	String* path = String::Concat(IO::Path::GetDirectoryName(Application::ExecutablePath), S"\\reference\\vipDirectXInput.info.rtf");
	if ( IO::File::Exists(path) )
		rTBinfo->LoadFile(path , RichTextBoxStreamType::RichText);
	else
	{
		rTBinfo->Text = "ERROR\r\n\r\nCouln't load data file: \r\n";
		rTBinfo->AppendText(path);
	}

	viewsUpdate();
	if (cBviews->Items->Count)
		cBviews->SelectedIndex = 0;

	button2_Click(this, NULL);
	button1->Enabled = false;
	button3->Enabled = true;
	button4->Enabled = false;

 }

System::Void dxinputForm::dxinputForm_Closing(System::Object *  sender, System::ComponentModel::CancelEventArgs *  e)
 {
	if (myCap->getCurrentDevice() != -1)
	 {
		static_cast<Form1*>(this->MdiParent)->writeLog(S"Still Connected, Trying to disconnect device..", this);
		if ( myCap->disconnect() )
		 {
			static_cast<Form1*>(this->MdiParent)->writeLog(S"FALIED: Cannot disconnect from current device, closing query stopped.", this);
			e->Cancel = true;
		 }
	 }
 }
System::Void dxinputForm::dxinputForm_Closed(System::Object *  sender, System::EventArgs *  e)
 {
	static_cast<Form1*>(this->MdiParent)->updateChildFormsList();
 }

void dxinputForm::Dispose(Boolean disposing)
 {
	static_cast<Form1*>(this->MdiParent)->writeLog(S"Destroying class: vipDirectXInput", this);

	delete myCap;

	static_cast<Form1*>(this->MdiParent)->writeLog(S"Destroying buffer", this);
	if (buffer != NULL)
		delete buffer;

	static_cast<Form1*>(this->MdiParent)->writeLog(S"Destroying Interface..", this);
	if (disposing && components)
	 {
		components->Dispose();
	 }
	__super::Dispose(disposing);
 }

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////// CONNECTION

System::Void dxinputForm::button2_Click(System::Object *  sender, System::EventArgs *  e)
 {
	this->Cursor = Cursors::WaitCursor;
	static_cast<Form1*>(this->MdiParent)->writeLog(S"Enumerating DirectX Devices..", this);
	myCap->enumerateDevices();
	listBoxDevices->Items->Clear();
	for (int i=0; i<myCap->getDeviceCount(); i++)
	 {
		listBoxDevices->Items->Add(new System::String( myCap->getDeviceDescription(i) ) );
	 }
	this->Cursor = Cursors::Default;
 }


System::Void dxinputForm::button3_Click(System::Object *  sender, System::EventArgs *  e)
 {
	if (myCap->getCurrentDevice() != -1)
		{
			MessageBox::Show(this, "Disconnect first!", this->Text, MessageBoxButtons::OK );
			return;
		}

	if (listBoxDevices->SelectedIndex == -1)
		{
			MessageBox::Show(this, "Select a device first!", this->Text, MessageBoxButtons::OK );
			return;
		}
	lBstreamInfo->Items->Clear();

	this->Cursor = Cursors::WaitCursor;
	static_cast<Form1*>(this->MdiParent)->writeLog(String::Format(S"Connecting to device '{0}'..",listBoxDevices->SelectedItem->ToString()), this);

	if (myCap->connectTo(listBoxDevices->SelectedIndex) != VIPRET_OK)
	 {
		this->Cursor = Cursors::Default;
		 static_cast<Form1*>(this->MdiParent)->writeLog(S"FALIED: Couldn't connect to selected device!", this);
		MessageBox::Show(this, "Couldn't connect to selected device!", this->Text, MessageBoxButtons::OK );
		button3->Enabled = true;
		button4->Enabled = false;
		button1->Enabled = false;
		return;
	 }

	int w, h, f;
	f = 0;
	char fdesc[255];

	 static_cast<Form1*>(this->MdiParent)->writeLog(S"Connected: Retrieving Stream Informations..", this);
	myCap->getFormat(f, &w, &h, fdesc);

	 static_cast<Form1*>(this->MdiParent)->writeLog(S"Updating internal Buffer..", this);

	if (buffer != NULL)
		delete buffer;

	buffer = new vipFrameRGB24(w, h);

	lBstreamInfo->Items->Add( System::String::Format("video Width\t: {0}", w.ToString() ) );
	lBstreamInfo->Items->Add( System::String::Format("video Height\t: {0}", h.ToString() ) );
	lBstreamInfo->Items->Add( System::String::Format("video Format\t: {0} - {1}", f.ToString() , new System::String(fdesc) ) );

	button3->Enabled = false;
	button4->Enabled = true;
	button1->Enabled = true;

	this->Cursor = Cursors::Default;
 }


System::Void dxinputForm::button4_Click(System::Object *  sender, System::EventArgs *  e)
 {
	this->Cursor = Cursors::WaitCursor;
	 static_cast<Form1*>(this->MdiParent)->writeLog(S"Disconnecting ..", this);
	int ret = myCap->disconnect();
	this->Cursor = Cursors::Default;

	if (ret == VIPRET_OK)
	 {
		listBoxDevices->SelectedIndex = -1;
		button3->Enabled = true;
		button4->Enabled = false;
		button1->Enabled = false;
	 }
	else
	{
		static_cast<Form1*>(this->MdiParent)->writeLog(S"FALIED: Couldn't disconnect from current device!", this);
		MessageBox::Show(this, "Couldn't disconnect from current device!", this->Text, MessageBoxButtons::OK );
		button3->Enabled = false;
		button4->Enabled = true;
		button1->Enabled = true;
	}
 }



System::Void dxinputForm::button1_Click(System::Object *  sender, System::EventArgs *  e)
 {
	if (myCap->getCurrentDevice() == -1)
	 {
		MessageBox::Show(this, "Connect first!", this->Text, MessageBoxButtons::OK );
		return;
	 }

	 if ( myCap->openPropertyPage( static_cast<void*>(this->Handle) ) )
	 {
		MessageBox::Show(this, "FALIED, internal error occured!", this->Text, MessageBoxButtons::OK );
		return;
	 }


 }


//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////// FRAME I\O

VIPRESULT dxinputForm::extractTo(vipFrameRGB24* img)
 {
	if (img != NULL && myCap->getCurrentDevice() != -1)
		return myCap->extractTo(*img);

	return VIPRET_ILLEGAL_USE;
 }

void dxinputForm::pushFrames(int iLoop)
 {
	if (vF == NULL)
		return;

	int slTime = 0;

	if (iLoop > 1)
		slTime = (int)( 1000.0 / Convert::ToDouble(nUDfps->Value) );

	static_cast<Form1*>(this->MdiParent)->writeLog(String::Format(S"PUSHING frames {0}", iLoop.ToString()), this);

	try
	 {
		for (int i = 0; i < iLoop; i++)
		 {
			*myCap >> *buffer;
			System::Threading::Thread::Sleep(slTime);
			vF->importFrom(buffer);
		 }
	 }
	catch (Exception* eX)
	 {
		 static_cast<Form1*>(this->MdiParent)->writeLog(String::Format(S"FALIED: Exception raised!\r\n\t{0}", eX->ToString() ), this);
	 }

 }


void dxinputForm::pushFramesMT(int iLoop)
 {
	 thLoop = iLoop;
//	 System::Threading::Thread* pT = new System::Threading::Thread( new System::Threading::ThreadStart(*this, this->pushFrames));
//	 pT->Start();
 }

void dxinputForm::pushFrames()
 {
	if (vF == NULL)
		return;

	int slTime = 0;

	if (thLoop > 1)
		slTime = (int)( 1000.0 / Convert::ToDouble(nUDfps->Value) );

	static_cast<Form1*>(this->MdiParent)->writeLog(String::Format(S"PUSHING frames {0}", thLoop.ToString()), this);

	try
	 {
		for (int i = 0; i < thLoop; i++)
		 {
			*myCap >> *buffer;
			System::Threading::Thread::Sleep(slTime);
			vF->importFrom(buffer);
		 }
	 }
	catch (Exception* eX)
	 {
		 static_cast<Form1*>(this->MdiParent)->writeLog(String::Format(S"FALIED: Exception raised!\r\n\t{0}", eX->ToString() ), this);
	 }

 }

}