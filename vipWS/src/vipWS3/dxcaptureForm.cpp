#include "StdAfx.h"
#include "dxcaptureForm.h"
#include "Form1.h"

#include "../../../../source/inputs/vipDirectXInput2.h"
#include "../../../../source/vipUtility.h"

namespace vipWS3
{
	using namespace System::Drawing::Imaging;

dxcaptureForm::dxcaptureForm()
 {
	InitializeComponent();
	buffer = NULL;
	vF = NULL;
	myDXInput = NULL;
	myPVForm = NULL;
  }

void dxcaptureForm::Init(void)
 {
	static_cast<Form1*>(this->MdiParent)->writeLog(S"Creating class: vipDirectXInput", this);
	myDXInput = new vipDirectXInput2();
	rTBlog->Clear();
	rTBlog->AppendText(S"Initializing vipDirectXInput2 Module..\r\n");
 }


System::Void dxcaptureForm::dxcaptureForm_Load(System::Object *  sender, System::EventArgs *  e)
 {
	rTBlog->AppendText(S"Initializing preview Window..\r\n");

	rTBlog->AppendText(S"Initializing preview Window..\r\n");
	myPVForm = new viewForm();

	myDXInput->setErrorMessagesEnabled(true);
	myDXInput->setPreviewWindow(static_cast<void*>(myPVForm->Handle));
	myDXInput->setAutoUpdatePreviewWindowEnabled( true );

	button1_Click(sender, e);

	checkBox9_CheckedChanged(sender, e);

	if ( checkBox11->Checked )
		myDXInput->setFrameGrabbingEnabled(true);

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

 }

System::Void dxcaptureForm::dxcaptureForm_Closing(System::Object *  sender, System::ComponentModel::CancelEventArgs *  e)
 {
//TODO myDXInput->Close();
	if (myDXInput != NULL)
		delete myDXInput;
 }

System::Void dxcaptureForm::dxcaptureForm_Closed(System::Object *  sender, System::EventArgs *  e)
 {
 }


System::Void dxcaptureForm::button13_Click(System::Object *  sender, System::EventArgs *  e)
 {
	myPVForm->Show();
 }


System::Void dxcaptureForm::button1_Click(System::Object *  sender, System::EventArgs *  e)
 {
	this->Cursor = Cursors::WaitCursor;

	rTBlog->AppendText(S"Enumerating Devices and populating listboxes..\r\n");

	myDXInput->enumerateDevices();

	listBox1->Items->Clear();
	for (int i=0; i<myDXInput->getDeviceVideoCount(); i++)
	 {
		listBox1->Items->Add(new System::String( myDXInput->getDeviceVideoDescription(i) ) );
	 }

	listBox2->Items->Clear();
	for (int i=0; i<myDXInput->getDeviceAudioCount(); i++)
	 {
		listBox2->Items->Add(new System::String( myDXInput->getDeviceAudioDescription(i) ) );
	 }

	this->Cursor = Cursors::Default;
 }

System::Void dxcaptureForm::button7_Click(System::Object *  sender, System::EventArgs *  e)
 {
	if ( myDXInput->isCapturing() )
	 {
		MessageBox::Show(this, S"ERROR:\r\nCannot pre-allocate file while capturing!", this->Text, MessageBoxButtons::OK );
		return;
	 }
	this->Cursor = Cursors::WaitCursor;

	rTBlog->AppendText(String::Format(S"Pre-Allocating {0} Mb for output file..", numericUpDown2->Value.ToString() ));

	if ( myDXInput->AllocCaptureFile( (unsigned short)Convert::ToInt16(numericUpDown2->Value) ) )
		rTBlog->AppendText(S"FALIED\r\n");
	else
		rTBlog->AppendText(S"OK\r\n");

	button8_Click(sender, e);

	this->Cursor = Cursors::Default;
 }

System::Void dxcaptureForm::button8_Click(System::Object *  sender, System::EventArgs *  e)
 {
	myDXInput->UpdateStatus(chk_updateall->Checked);

	if ( chk_updateall->Checked )
	 {
		lb_info_fps->Text = String::Format(S"{0} fps\0", myDXInput->getCapturedFrameRate().ToString());

		long ldata = myDXInput->getCapturedDataRate();
		lb_info_dr->Text = String::Format(S"{0}.{1}  Mb/sec\0", (ldata / 1000000).ToString(), (ldata / 1000 - (ldata / 1000000 * 1000)).ToString() );

		lb_info_fsl->Text = String::Concat((myDXInput->getFreeSpaceLeft()/1024).ToString(), S" Mb");
		lb_info_fs->Text = String::Concat(myDXInput->getFileSize().ToString(), S" Mb");
		bl_info_afs->Text =  myDXInput->getAverageFrameSize().ToString();
	 }

	lb_info_cf->Text = myDXInput->getCapturedFramesCount().ToString();
	lb_info_df->Text = myDXInput->getDroppedFramesCount().ToString();

	long lTime = myDXInput->getCapturedElapsedTime();
	lb_info_et->Text = String::Format(S"{0}.{1} sec\0", (lTime / 1000).ToString(), (lTime / 100 - lTime / 1000 * 10).ToString() );

 }


System::Void dxcaptureForm::button9_Click(System::Object *  sender, System::EventArgs *  e)
 {
	this->Cursor = Cursors::WaitCursor;

	lb_info->Text = S"Ready.";

	if ( myDXInput->isCapturing() )
	 {
		 lb_info->Text = S"Capturing ";
		 if ( myDXInput->isUncompressed() )
			lb_info->Text = String::Concat(lb_info->Text, S" uncompressed ");
		lb_info->Text = String::Concat(lb_info->Text, S"Video");
		if ( myDXInput->isCapturingAudio() )
			lb_info->Text = String::Concat(lb_info->Text, S" and Audio");

		if ( myDXInput->isPreviewing() )
			lb_info->Text = String::Concat(lb_info->Text, S" with live preview.");
	 }
	else if ( myDXInput->isPreviewing() )
		lb_info->Text = S"Previewing video (NULL Output).";

	char buffer[256] = "unknown\0";
	myDXInput->getVideoFriendlyName(buffer);

	String* tmpStr1 = String::Format(S"Video Device: {0}", new String(buffer) );
	String* tmpStr2 = String::Format(S"; Format: {0}x{1}", myDXInput->getWidth().ToString(), myDXInput->getHeight().ToString() );
	lb_info_format->Text = String::Concat(tmpStr1, tmpStr2);

	buffer[0] = '\0';
	myDXInput->getAudioFriendlyName(buffer);

	tmpStr1 = String::Format(S"\r\nAudio Device: {0}", new String(buffer) );
	lb_info_format->Text = String::Concat(lb_info_format->Text , tmpStr2);

	if ( myDXInput->getFrameRateCurrent() )
		 numericUpDown1->Value = myDXInput->getFrameRateCurrent();

	this->Cursor = Cursors::Default;
 }

System::Void dxcaptureForm::button10_Click(System::Object *  sender, System::EventArgs *  e)
 {
	rTBlog->AppendText(S"Forcing disconnection and clean-up..\r\n");

	listBox1->SelectedIndex = -1;
	listBox2->SelectedIndex = -1;

	myDXInput->Close();

	button9_Click(sender, e);

 }

System::Void dxcaptureForm::button2_Click(System::Object *  sender, System::EventArgs *  e)
 {
//open browse

	saveFileDialog1->InitialDirectory = IO::Path::GetDirectoryName(Application::ExecutablePath);

	if ( saveFileDialog1->ShowDialog() != DialogResult::OK )
		return;

	this->Cursor = Cursors::WaitCursor;

	tBpath->Text =  saveFileDialog1->FileName->ToString();

	rTBlog->AppendText(String::Format(S"Setting output file: {0} ..", tBpath->Text ));

	if ( myDXInput->setCaptureFile( (char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(tBpath->Text)).ToPointer() ) )
		rTBlog->AppendText(S"FALIED\r\n");
	else
		rTBlog->AppendText(S"OK\r\n");

	this->Cursor = Cursors::Default;

 }

System::Void dxcaptureForm::button4_Click(System::Object *  sender, System::EventArgs *  e)
 {
	myDXInput->showGraphFilterPropertyPage();
	button9_Click( sender, e);
	button8_Click( sender, e);
 }

System::Void dxcaptureForm::checkBox3_CheckedChanged(System::Object *  sender, System::EventArgs *  e)
{
	myDXInput->setErrorMessagesEnabled( checkBox3->Checked );
}

System::Void dxcaptureForm::checkBox7_CheckedChanged(System::Object *  sender, System::EventArgs *  e)
{
	myDXInput->setAutoUpdatePreviewWindowEnabled( checkBox7->Checked );
}
System::Void dxcaptureForm::checkBox10_CheckedChanged(System::Object *  sender, System::EventArgs *  e)
{
	myDXInput->setFrameRateControlEnabled( checkBox10->Checked );
	numericUpDown1->Enabled = checkBox10->Checked;
	button12->Enabled = checkBox10->Checked;
}


System::Void dxcaptureForm::checkBox9_CheckedChanged(System::Object *  sender, System::EventArgs *  e)
{
	if ( checkBox9->Checked )
	 {
		listBox2->Enabled = true;
		button5->Enabled = true;
		listBox2->SelectedIndex = -1;

	 }
	else
	 {
		listBox2->Enabled = false;
		button5->Enabled = false;
		listBox2->SelectedIndex = -1;
	 }

}

System::Void dxcaptureForm::checkBox6_CheckedChanged(System::Object *  sender, System::EventArgs *  e)
{
	if ( myDXInput->setMPEG2Encode( checkBox6->Checked ) )
	 {
		MessageBox::Show(this, S"Cannot update stream format while capturing!", this->Text, MessageBoxButtons::OK );

		checkBox6->Checked = myDXInput->isMPEG2Encoded();
	 }
}


System::Void dxcaptureForm::checkBox1_Click(System::Object *  sender, System::EventArgs *  e)
 {
	this->Cursor = Cursors::WaitCursor;

	if ( !myDXInput->isPreviewing() )
	 {
		if (!myPVForm->Visible)
			myPVForm->Show();
		myDXInput->setPreviewEnabled(true);
		myDXInput->showPreviewWindow(true);// we are interested only in windows state

		rTBlog->AppendText(S"Starting Preview.." );
		int hr = myDXInput->StartPreview();
		if ( hr )
		 {
			MessageBox::Show(this, String::Format(S"Cannot start preview, error returned!\r\nErrorCode: {0}", hr.ToString() ), this->Text, MessageBoxButtons::OK );
			rTBlog->AppendText(S"FALIED\r\n");
		 }
		else
		 {
			checkBox1->Text = "Previewing..";
			button9_Click(sender, e);
			rTBlog->AppendText(S"OK\r\n");
		 }
	 }
	else
	 {
		rTBlog->AppendText(S"Stopping Preview.." );
		int hr = myDXInput->StopPreview();
		if ( hr )
		 {
			MessageBox::Show(this, String::Format(S"Cannot start preview, error returned!\r\nErrorCode: {0}", hr.ToString() ), this->Text, MessageBoxButtons::OK );
			rTBlog->AppendText(S"FALIED\r\n");
		 }
		else
		 {
			checkBox1->Text = "Preview";
			button9_Click(sender, e);
			if ( checkBox8->Checked )
				myDXInput->showPreviewWindow(false);
			rTBlog->AppendText(S"OK\r\n");
		 }
	 }

	checkBox1->Checked = myDXInput->isPreviewing();
	this->Cursor = Cursors::Default;
 }


System::Void dxcaptureForm::checkBox2_Click(System::Object *  sender, System::EventArgs *  e)
 {
	this->Cursor = Cursors::WaitCursor;

	if ( !myDXInput->isCapturing() )
	 {
		rTBlog->AppendText(S"Starting Capture.." );

//		if ( checkBox12->Checked && !myPVForm->Visible )
//			myPVForm->Show();
//		myDXInput->setPreviewEnabled(checkBox12->Checked);

		int hr = myDXInput->StartCapture();
		if ( hr )
		 {
			MessageBox::Show(this, String::Format(S"Cannot start capture, error returned!\r\nErrorCode: {0}", hr.ToString() ), this->Text, MessageBoxButtons::OK );
			rTBlog->AppendText(S"FALIED\r\n");
		 }
		else
		 {
			rTBlog->AppendText(S"OK\r\n");
			checkBox2->Text = "Capturing..";
			button9_Click(sender, e);

			rTBlog->AppendText(S"\r\n");
			rTBlog->AppendText(S"New Capture Task______________________\r\n");

			char buffer[256] = "unknown\0";
			myDXInput->getVideoFriendlyName(buffer);

			rTBlog->AppendText(String::Format(S"Video Device: {0}\r\n", new String(buffer) ));
			rTBlog->AppendText(String::Format(S"Video Format: {0}x{1}\r\n", myDXInput->getWidth().ToString(), myDXInput->getHeight().ToString() ));

			buffer[0] = '\0';

			rTBlog->AppendText(String::Format(S"Audio Device: {0}\r\n", new String(buffer) ));
			rTBlog->AppendText(String::Format(S"Audio Format: {0}x{1}\r\n", myDXInput->getWidth().ToString(), myDXInput->getHeight().ToString() ));

			if ( myDXInput->isPreviewing() )
			 {
				rTBlog->AppendText(S"Preview Enabled:\tyes\r\n");

				if ( myDXInput->isPreviewFaked() )
					rTBlog->AppendText(S"Preview Faked:\tyes (emulated preview pin)\r\n");
				else
					rTBlog->AppendText(S"Preview Faked:\tno (preview pin available)\r\n");

			 }
			else
				rTBlog->AppendText(S"Preview Enabled:\tno\r\n");


			rTBlog->AppendText(S"\r\n");

		 }
	 }
	else
	 {
		rTBlog->AppendText(S"Stopping Capture.." );
		int hr = myDXInput->StopCapture();
		if ( hr )
		 {
			MessageBox::Show(this, String::Format(S"Cannot stop capture, error returned!\r\nErrorCode: {0}", hr.ToString() ), this->Text, MessageBoxButtons::OK );
			rTBlog->AppendText(S"FALIED\r\n");
		 }
		else
		 {
			checkBox2->Text = "Capture";
			button9_Click(sender, e);
			rTBlog->AppendText(S"OK\r\n");
			rTBlog->AppendText(S"\r\nStats:");

			long lTime = myDXInput->getCapturedElapsedTime();

			rTBlog->AppendText( String::Format(S"Capture Time:\t{0}.{1} sec\r\n", (lTime / 1000).ToString(), (lTime / 100 - lTime / 1000 * 10).ToString() ) );
			rTBlog->AppendText( String::Format(S"Captured Frames:\t{0}\r\n", myDXInput->getCapturedFramesCount().ToString()) );
			rTBlog->AppendText( String::Format(S"Dropped Frames:\t{0}\r\n", myDXInput->getDroppedFramesCount().ToString()) );

			rTBlog->AppendText( String::Format(S"File size:\t{0} Mb\r\n", myDXInput->getFileSize().ToString()) );
			rTBlog->AppendText( String::Format(S"Average Frame Size:\t{0} Kb\r\n", myDXInput->getAverageFrameSize().ToString() ) );

			rTBlog->AppendText( String::Format(S"Last Frame Rate:\t{0} fps\r\n", myDXInput->getCapturedFrameRate().ToString() ) );

			long ldata = myDXInput->getCapturedDataRate();
			rTBlog->AppendText( String::Format(S"Last Data Rate:\t{0}.{1} Mb/sec\r\n", (ldata / 1000000).ToString(), (ldata / 1000 - (ldata / 1000000 * 1000)).ToString() ) );

			rTBlog->AppendText(S"End Capture Task______________________\r\n");
		 }
	 }


	checkBox2->Checked = myDXInput->isCapturing();
	this->Cursor = Cursors::Default;
 }

System::Void dxcaptureForm::numericUpDown1_ValueChanged(System::Object *  sender, System::EventArgs *  e)
 {
// code is in button12, for callback update problem.. is there a smart solution?
 }

System::Void dxcaptureForm::button12_Click(System::Object *  sender, System::EventArgs *  e)
 {
	this->Cursor = Cursors::WaitCursor;

	 if (myDXInput->isPreviewing() || myDXInput->isCapturing() )
	  {
		rTBlog->AppendText(S"Updating frame rate.." );

		if ( myDXInput->setFrameRate( Convert::ToDouble(numericUpDown1->Value) ) )
		 {
			rTBlog->AppendText(S"FALIED\r\n");
			numericUpDown1->Value = myDXInput->getFrameRateCurrent();
		 }
		else
		 {
			rTBlog->AppendText(S"OK\r\n");
		 }
	  }
	 else
	  {
		if ( myDXInput->setFrameRate( Convert::ToDouble(numericUpDown1->Value) ) )
		 {
			 numericUpDown1->Value = myDXInput->getFrameRate();
		 }
	  }
	this->Cursor = Cursors::Default;
 }


System::Void dxcaptureForm::listBox_SelectedIndexChanged(System::Object *  sender, System::EventArgs *  e)
 {
	this->Cursor = Cursors::WaitCursor;

	if ( myDXInput->isCapturing() )
		myDXInput->StopCapture();

	if ( myDXInput->isPreviewing() )
		myDXInput->StopPreview();

	myDXInput->setCurrentDevices(listBox1->SelectedIndex, listBox2->SelectedIndex);

	button9_Click( sender, e );

	this->Cursor = Cursors::Default;
 }

System::Void dxcaptureForm::button14_Click(System::Object *  sender, System::EventArgs *  e)
{
//	this->Cursor = Cursors::WaitCursor;
/*
	vipFrameRGB24* buf = new vipFrameRGB24(myDXInput->getWidth(), myDXInput->getHeight() );
	int ret = myDXInput->extractTo(*buf);
	if ( ret )
	 {
		 MessageBox::Show(this, S"ERROR");
	 }
	else
	{

		MessageBox::Show(this, buf->width.ToString(), buf->height.ToString());


		previewForm* myPVForm23 = new previewForm();
		myPVForm23->Show();
		myPVForm23->Text = "vipFrameCache24 Grabbed..";

			Bitmap* bm = new Bitmap(buf->width, buf->height);
		myPVForm23->BackgroundImage = dynamic_cast<Image*>(bm);

			BitmapData* bitData;
			Rectangle rec(0,0, buf->width, buf->height);

			bitData = bm->LockBits(rec, ImageLockMode::WriteOnly, PixelFormat::Format24bppRgb);

			//this would be great but micro$oft always LIES, it's BGR not RGB.. so
			//memcpy(bitData->Scan0.ToPointer(), img.data[0], img.height*img.width*3* sizeof(char));
			unsigned char* dest = static_cast<unsigned char*>( bitData->Scan0.ToPointer() );
			vipUtility::conv_bgr_rgb(dest, (unsigned char*)buf->data[0], buf->width, buf->height);

			bm->UnlockBits(bitData);

//		myPVForm23->Refresh();

	}

	delete buf;
*/
//	this->Cursor = Cursors::Default;

}


System::Void dxcaptureForm::checkBox13_Click(System::Object *  sender, System::EventArgs *  e)
 {
//	this->Cursor = Cursors::WaitCursor;
/*
	vipFrameRGB24* buf = new vipFrameRGB24(myDXInput->getWidth(), myDXInput->getHeight() );
	int ret = myDXInput->extractTo(*buf);
	if ( ret )
	 {
		 //
	 }
	else
	{
		previewForm* myPVForm23 = new previewForm();
		myPVForm23->Show();
		myPVForm23->Text = "vipFrameCache24 Grabbed..";

	}

	delete buf;
*/
//	this->Cursor = Cursors::Default;
 }


System::Void dxcaptureForm::checkBox11_Click(System::Object *  sender, System::EventArgs *  e)
 {
	this->Cursor = Cursors::WaitCursor;

	if ( myDXInput->isFrameGrabbingEnabled() )
	 {
		rTBlog->AppendText(S"Removing Grabbing Filter.." );
		int ret = myDXInput->setFrameGrabbingEnabled(false);
		if ( ret )
		 {
			MessageBox::Show(this, String::Format(S"Cannot remove grabbing filter, error returned!\r\nErrorCode: {0}", ret.ToString() ), this->Text, MessageBoxButtons::OK );
			rTBlog->AppendText(S"FALIED\r\n");

		 }
		else
		 {
			rTBlog->AppendText(S"OK\r\n");
		 }
	 }
	else
	 {
		rTBlog->AppendText(S"Adding Grabbing Filter.." );
		int ret = myDXInput->setFrameGrabbingEnabled(true);
		if ( ret )
		 {
			MessageBox::Show(this, String::Format(S"Cannot add grabbing filter, error returned!\r\nErrorCode: {0}", ret.ToString() ), this->Text, MessageBoxButtons::OK );
			rTBlog->AppendText(S"FALIED\r\n");
		 }
		else
		 {
			rTBlog->AppendText(S"OK\r\n");
		 }
	 }

	checkBox11->Checked = myDXInput->isFrameGrabbingEnabled();
	checkBox13->Enabled = checkBox11->Checked;

	this->Cursor = Cursors::Default;
 }




///////////////////////////////////////////////////////////////////////////////////////////


System::Void dxcaptureForm::button3_Click(System::Object *  sender, System::EventArgs *  e)
 {
	myDXInput->showCaptureVideoFilterPropertyPage();
	button9_Click( sender, e);
 }
System::Void dxcaptureForm::button5_Click(System::Object *  sender, System::EventArgs *  e)
 {
	myDXInput->showCaptureAudioFilterPropertyPage();
	button9_Click( sender, e);
 }

System::Void dxcaptureForm::button11_Click(System::Object *  sender, System::EventArgs *  e)
 {
	myDXInput->showCaptureVideoForWindowPropertyPage();
 }
System::Void dxcaptureForm::button15_Click(System::Object *  sender, System::EventArgs *  e)
{
	myDXInput->showVideoRendererPropertyPage();
}
System::Void dxcaptureForm::button16_Click(System::Object *  sender, System::EventArgs *  e)
{
	myDXInput->showSampleGrabberPropertyPage();
}










//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////// FRAME I\O

VIPRESULT dxcaptureForm::extractTo(vipFrameRGB24* img)
 {
	if (img != NULL && myDXInput->getCurrentDeviceVideo() != -1)
		return myDXInput->extractTo(*img);

	return VIPRET_ILLEGAL_USE;
 }

void dxcaptureForm::pushFrames(int iLoop)
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
			*myDXInput >> *buffer;
			System::Threading::Thread::Sleep(slTime);
			vF->importFrom(buffer);
		 }
	 }
	catch (Exception* eX)
	 {
		 static_cast<Form1*>(this->MdiParent)->writeLog(String::Format(S"FALIED: Exception raised!\r\n\t{0}", eX->ToString() ), this);
	 }

 }


void dxcaptureForm::pushFramesMT(int iLoop)
 {
	 thLoop = iLoop;
//	 System::Threading::Thread* pT = new System::Threading::Thread( new System::Threading::ThreadStart(*this, this->pushFrames));
//	 pT->Start();
 }

void dxcaptureForm::pushFrames()
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
			*myDXInput >> *buffer;
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