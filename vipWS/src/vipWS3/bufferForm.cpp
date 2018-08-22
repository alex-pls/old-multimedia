#include "StdAfx.h"
#include "bufferForm.h"
#include "Form1.h"

//#include "H:\eCenter\UNI\TESI\source\buffers\vipBufferArray.h"


namespace vipWS3
{




bufferForm::bufferForm(void)
 {
	InitializeComponent();
	myBuffer = NULL;
	myObj = NULL;
 }

void bufferForm::Init(vipBuffer<vipFrameRGB24>* myBufferInstance, loaderDLL* myPlugInObj)
 {
	static_cast<Form1*>(this->MdiParent)->writeLog(S"Initializing: Loading buffer Informations..", this);

	myBuffer = myBufferInstance;
//	myBuffer = new vipBufferArray<vipFrameRGB24>();
	myObj = myPlugInObj;

	this->Text = new String(myObj->getFullName());
	rTBinfo->AppendText(S"Initializing Plug-In [vipBuffer]");
	rTBinfo->AppendText(S"");
	rTBinfo->AppendText(S"");
	String* name = new String(myObj->getInternalName());
	String* baseName = name->Substring(0, name ->IndexOf(S"<"));
	String* path = String::Format("{0}\\reference\\{1}.info.rtf", IO::Path::GetDirectoryName(Application::ExecutablePath), baseName );
	if ( IO::File::Exists(path) )
		rTBinfo->LoadFile(path , RichTextBoxStreamType::RichText);
	else
	 {
		rTBinfo->AppendText(S"ERROR\r\n\r\nCouln't load data file: \r\n");
		rTBinfo->AppendText(path);
	 }

//	button9->
 }
System::Void bufferForm::bufferForm_Closing(System::Object *  sender, System::ComponentModel::CancelEventArgs *  e)
 {
	static_cast<Form1*>(this->MdiParent)->updateChildFormsList();
 }


void bufferForm::Dispose(Boolean disposing)
 {
	 //		delete myBuffer; -> done by loaderDLL
	static_cast<Form1*>(this->MdiParent)->writeLog(S"Destroying Interface..", this);

	myBuffer->deleteFrames();

//	if (buffer != NULL)
//		delete buffer;
//	buffer = NULL;

	if (disposing && components)
	 {
		components->Dispose();
	 }
	__super::Dispose(disposing);
 }

VIPRESULT bufferForm::importFrom(vipFrameRGB24* img)
 {
	if (img != NULL && myBuffer != NULL)
	 {
		vipFrameRGB24* nFr = new vipFrameRGB24(*img);
		myBuffer->addFrame(nFr);
		updateItems();

	 	return VIPRET_OK;
	 }

 	return VIPRET_ILLEGAL_USE;
 }

VIPRESULT bufferForm::extractTo(vipFrameRGB24* img)
 {
	vipFrameRGB24* cFr = new vipFrameRGB24( *myBuffer->getCurrentFrame() );
	 if (cFr != NULL && vF != NULL )
		return vF->importFrom(cFr);

	return VIPRET_ILLEGAL_USE;
 }

System::Void bufferForm::bufferForm_Load(System::Object *  sender, System::EventArgs *  e)
 {
	static_cast<Form1*>(this->MdiParent)->writeLog(S"Initializing GUI..", this);

	viewsUpdate();
	sourcesUpdate();
 }




void bufferForm::updateItems(void)
 {
	double bytes = 0;
	chkLbItems->Items->Clear();

	for (long i=0; i < myBuffer->getFramesCount() ; i++ )
	 {
		 chkLbItems->Items->Add(String::Format(S"Frame #{0}", i.ToString() ), false);
		 bytes += myBuffer->getFrame(i)->height * myBuffer->getFrame(i)->width * 3;
	 }

	tBindex->Maximum = myBuffer->getFramesCount() - 1;
	tBindex->TickFrequency = myBuffer->getFramesCount() / 10;
	tBindex->Location = myBuffer->getCurrentFrameIndex();

	nUDindex->Maximum = myBuffer->getFramesCount() - 1;
	nUDindex->Value = myBuffer->getCurrentFrameIndex();

	lB_count->Text = myBuffer->getFramesCount().ToString();
	lB_size->Text = Convert::ToString(bytes);
 }




System::Void bufferForm::button1_Click(System::Object *  sender, System::EventArgs *  e)
 {
	 if (vF)
		vF->importFrom(myBuffer->getCurrentFrame());
 }

System::Void bufferForm::button3_Click(System::Object *  sender, System::EventArgs *  e)
 {
	vipFrameRGB24* nFr = NULL;
	if (sF)
	 {
		nFr = new vipFrameRGB24();
		sF->extractTo(nFr);
	 }

	if ( nFr != NULL )
	 {
		myBuffer->addFrame(nFr);
		updateItems();
	 }

 }


System::Void bufferForm::button6_Click(System::Object *  sender, System::EventArgs *  e)
 {
	vipFrameRGB24* sFr = myBuffer->getFrame(chkLbItems->SelectedIndex);
	if ( sFr == NULL)
	 {
		return;
	 }

	for (int i=0; i<this->MdiParent->MdiChildren->Count; i++)
	 {
		if ( static_cast<Form*>(this->MdiParent->MdiChildren->get_Item(i))->Text->Equals(cBviews->SelectedItem->ToString() ))
		 {
			static_cast<outputInterface*>(this->MdiParent->MdiChildren->get_Item(i))->importFrom(sFr);
			return;
		 }
	 }
 }

System::Void bufferForm::button7_Click(System::Object *  sender, System::EventArgs *  e)
 {
	if (chkLbItems->SelectedIndex == -1)
		return;

	vipFrameRGB24* sFr = myBuffer->getFrame(chkLbItems->SelectedIndex);

	if ( sFr == NULL)
	 {
		return;
	 }

	if (vF)
		vF->importFrom(sFr);
 }


System::Void bufferForm::chkLbItems_SelectedIndexChanged(System::Object *  sender, System::EventArgs *  e)
 {
	if (chkLbItems->SelectedIndex == -1)
	{
		return;
	}

	 if ( cBupdateIndex->Checked )
	  {
		myBuffer->goToFrame(chkLbItems->SelectedIndex);
		tBindex->Location = myBuffer->getCurrentFrameIndex();
		if ( myBuffer->getCurrentFrameIndex() == -1)
			nUDindex->Enabled = false;
		else {
			nUDindex->Enabled = true;
			nUDindex->Value = Decimal(myBuffer->getCurrentFrameIndex());
		 }
	  }

	vipFrameRGB24* sFr = myBuffer->getFrame(chkLbItems->SelectedIndex);
	if ( sFr == NULL)
	 {
		return;
	 }
	lb_w->Text = sFr->width.ToString();
	lb_h->Text = sFr->height.ToString();
	lb_b->Text = ( (double)(sFr->width * sFr->height * 3 * 8) / 1024 ).ToString();


 }


System::Void bufferForm::button2_Click(System::Object *  sender, System::EventArgs *  e)
 {
	if (chkLbItems->SelectedIndex == -1)
		return;

	vipFrameRGB24* sFr = myBuffer->getFrame(chkLbItems->SelectedIndex);
	if ( sFr == NULL)
	 {
		return;
	 }

	myBuffer->removeFrame( sFr );

	if ( cBremoveData->Checked )
		delete sFr;

	updateItems();
 }

System::Void bufferForm::button5_Click(System::Object *  sender, System::EventArgs *  e)
 {
	 myBuffer->deleteFrames();

	 updateItems();
 }

System::Void bufferForm::button4_Click(System::Object *  sender, System::EventArgs *  e)
 {
//	button4->

	 updateItems();
 }









}
