#include "StdAfx.h"
#include "xvidCodecForm.h"
#include "Form1.h"

namespace vipWS3
{

xvidCodecForm::xvidCodecForm(void)
 {
	InitializeComponent();
	buffer = NULL;
	vF = NULL;
 }

void xvidCodecForm::Init()
 {
	 static_cast<Form1*>(this->MdiParent)->writeLog(S"Creating class: vipCodec_XVID", this);
	 myXVID = new vipCodec_XVID();
 }


System::Void xvidCodecForm::xvidCodecForm_Load(System::Object *  sender, System::EventArgs *  e)
 {
	lastPath = String::Concat(IO::Path::GetDirectoryName(Application::ExecutablePath), S"\\samples");
	String* path = String::Concat(IO::Path::GetDirectoryName(Application::ExecutablePath), S"\\reference\\vipCodec_XVID.info.rtf");

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

 }


 System::Void xvidCodecForm::xvidCodecForm_Closing(System::Object *  sender, System::ComponentModel::CancelEventArgs *  e)
 {
	//
 }
 System::Void xvidCodecForm::xvidCodecForm_Closed(System::Object *  sender, System::EventArgs *  e)
 {
	static_cast<Form1*>(this->MdiParent)->updateChildFormsList();
 }

VIPRESULT xvidCodecForm::extractTo(vipFrameRGB24* img)
 {
	if (img != NULL)
		return myXVID->extractTo(*img);

	return VIPRET_ILLEGAL_USE;
 }

void xvidCodecForm::Dispose(Boolean disposing)
 {
	static_cast<Form1*>(this->MdiParent)->writeLog(S"Destroying class: vipCodec_XVID", this);

	delete myXVID;

	static_cast<Form1*>(this->MdiParent)->writeLog(S"Destroying buffer", this);
	if (buffer != NULL)
		delete buffer;
	buffer = NULL;

	static_cast<Form1*>(this->MdiParent)->writeLog(S"Destroying Interface..", this);
	if (disposing && components)
	 {
		components->Dispose();
	 }
	__super::Dispose(disposing);
 }




System::Void xvidCodecForm::button1_Click(System::Object *  sender, System::EventArgs *  e)
 {
	 if (!File::Exists(tBpath->Text))
	  {
		MessageBox::Show(this, S"ERROR:\r\nMovie File doesn't exists!", this->Text, MessageBoxButtons::OK );
		return;
	  }

	 this->Cursor = Cursors::WaitCursor;

	 int ret = myXVID->load( (char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(tBpath->Text)).ToPointer() );

	lBstreamInfo->Items->Clear();
	tBarStream->Value = 0;
	tBarStream->Minimum = 0;
	tBarStream->Maximum = myXVID->getVideoStreamLength();
	tBarStream->TickFrequency = tBarStream->Maximum / 1000;

	if ( ret )
	 {
		this->Cursor = Cursors::Default;
		MessageBox::Show(this, S"ERROR:\r\nLoading falied", this->Text, MessageBoxButtons::OK );
		return;
	 }

	static_cast<Form1*>(this->MdiParent)->writeLog(String::Format(S"Opened movie: '{0}'..", tBpath->Text), this);

	if (buffer != NULL)
		delete buffer;

	buffer = new vipFrameRGB24(myXVID->getWidth(), myXVID->getHeight());

	lBstreamInfo->Items->Add( System::String::Format("Video Width\t: {0}", myXVID->getWidth().ToString() ) );
	lBstreamInfo->Items->Add( System::String::Format("Video Height\t: {0}", myXVID->getHeight().ToString() ) );

	lBstreamInfo->Items->Add( System::String::Format("Video Lenght\t: {0}", myXVID->getVideoStreamLength().ToString() ) );

	lbStream->Text = String::Format(S"Stream Position: {0}/{1}", S"0", myXVID->getVideoStreamLength().ToString() );

	this->Cursor = Cursors::Default;
 }








System::Void xvidCodecForm::pushFrames(int iLoop)
 {
	if (vF == NULL)
		return;

	int slTime = 0;

	if (iLoop > 1)
		slTime = (int)( 1000.0 / Convert::ToDouble(nUDfps->Value) );

	static_cast<Form1*>(this->MdiParent)->writeLog(String::Format(S"PUSHING frames {0}", iLoop.ToString()), this);

	String* nlen = Convert::ToString(tBarStream->Maximum);
	int vn = myXVID->getVideoStreamPosition();

	try
	 {
		for (int i = 0; i < iLoop; i++)
		 {
			*myXVID >> *buffer;
			System::Threading::Thread::Sleep(slTime);
			vF->importFrom(buffer);
			tBarStream->Value = ++vn;
			lbStream->Text = String::Format(S"Stream Position: {0}/{1}", vn.ToString(), nlen );
		 }
	 }
	catch (...)
	 {
		 static_cast<Form1*>(this->MdiParent)->writeLog(S"FALIED: Exception raised!", this);
	 }
	tBarStream->Value = myXVID->getVideoStreamPosition();
	lbStream->Text = String::Format(S"Stream Position: {0}/{1}", vn.ToString(), nlen );
	tBarStream->Refresh();
	lbStream->Refresh();
 }



}