#include "StdAfx.h"
#include "histForm.h"
#include "Form1.h"


namespace vipWS3
{

histForm::histForm(void)
 {
	InitializeComponent();
	hBuffer = new vipFrameRGB24(400, 400);
	myInst = new vipHist();

	bm_M = new Bitmap(400, 400);
	bm_R = new Bitmap(400, 400);
	bm_G = new Bitmap(400, 400);
	bm_B = new Bitmap(400, 400);

	pBdraw_M->Image = dynamic_cast<Image*>(bm_M);
	pBdraw_R->Image = dynamic_cast<Image*>(bm_R);
	pBdraw_G->Image = dynamic_cast<Image*>(bm_G);
	pBdraw_B->Image = dynamic_cast<Image*>(bm_B);

 }

//	static_cast<Form1*>(this->MdiParent)->writeLog(S"Initializing: Creating vipDoctor Instance..", this);


System::Void histForm::histForm_Load(System::Object *  sender, System::EventArgs *  e)
 {
	String* path = String::Concat(Path::GetDirectoryName(Application::ExecutablePath), S"\\reference\\vipHist.info.rtf");

	if ( File::Exists(path) )
		rTBinfo->LoadFile(path , RichTextBoxStreamType::RichText);
	else
	 {
		rTBinfo->Text = "ERROR\r\n\r\nCouln't load data file: \r\n";
		rTBinfo->AppendText(path);
	 }

	sourcesUpdate();

 }

System::Void histForm::histForm_Closing(System::Object *  sender, System::ComponentModel::CancelEventArgs *  e)
 {
	static_cast<Form1*>(this->MdiParent)->updateChildFormsList();
 }

void histForm::Dispose(Boolean disposing)
 {
	if (myInst != NULL)
        delete myInst;

	if (hBuffer != NULL)
		delete hBuffer;

	if (disposing && components)
	{
		components->Dispose();
	}
	__super::Dispose(disposing);
 }


VIPRESULT histForm::importFrom(vipFrameRGB24* img)
 {
	if (img != NULL && myInst != NULL)
	 {
		myInst->fromImage(*img, vipFrameRGB24::ChannelRGB::RED);

		lBinfo->Items->Clear();
		lBinfo->Items->Add(String::Format(S"Image Size:\t{0}x{1}", img->width.ToString(), img->height.ToString()));
		lBinfo->Items->Add(S"Pixel Size:\t8 bit x 3 Channels (RGB) = 24bit");
		lBinfo->Items->Add(S"");
		lBinfo->Items->Add(String::Format(S"BandWidth:\t{0} [8bit]", myInst->getValBandWidth().ToString()));


		lBinfo->Items->Add(S"");
		lBinfo->Items->Add(S"__RED CHANNEL");
		lBinfo->Items->Add(String::Format(S"Min Frequency Value:\t{0} (probability: {1})", myInst->getMinFrequencyValue().ToString(), myInst->getMinProbabilityValue().ToString()));
		lBinfo->Items->Add(String::Format(S"Max Frequency Value:\t{0} (probability: {1})", myInst->getMaxFrequencyValue().ToString(), myInst->getMaxProbabilityValue().ToString()));
		lBinfo->Items->Add(S"");
		lBinfo->Items->Add(String::Format(S"Mean:\t{0}", myInst->getMean().ToString()));
		lBinfo->Items->Add(String::Format(S"Variance:\t{0}", myInst->getVariance().ToString()));
		/*
		if (cBdraw_R->Checked)
		drawGraph(0);//RED

		if (cBdraw_M->Checked)
		drawGraph(10);//MIX

		myInst->fromImage(*img, vipFrameRGB24::ChannelRGB::GREEN);

		lBinfo->Items->Add(S"");
		lBinfo->Items->Add(S"__GREEN CHANNEL");
		lBinfo->Items->Add(String::Format(S"Min Frequency Value:\t{0} (probability: {1})", myInst->getMinFrequencyValue().ToString(), myInst->getMinProbabilityValue().ToString()));
		lBinfo->Items->Add(String::Format(S"Max Frequency Value:\t{0} (probability: {1})", myInst->getMaxFrequencyValue().ToString(), myInst->getMaxProbabilityValue().ToString()));
		lBinfo->Items->Add(S"");
		lBinfo->Items->Add(String::Format(S"Mean:\t{0}", myInst->getMean().ToString()));
		lBinfo->Items->Add(String::Format(S"Variance:\t{0}", myInst->getVariance().ToString()));

		if (cBdraw_G->Checked)
		drawGraph(0);//RED

		if (cBdraw_M->Checked)
		drawGraph(10);//MIX

		myInst->fromImage(*img, vipFrameRGB24::ChannelRGB::BLUE);

		lBinfo->Items->Add(S"");
		lBinfo->Items->Add(S"__BLUE CHANNEL");
		lBinfo->Items->Add(String::Format(S"Min Frequency Value:\t{0} (probability: {1})", myInst->getMinFrequencyValue().ToString(), myInst->getMinProbabilityValue().ToString()));
		lBinfo->Items->Add(String::Format(S"Max Frequency Value:\t{0} (probability: {1})", myInst->getMaxFrequencyValue().ToString(), myInst->getMaxProbabilityValue().ToString()));
		lBinfo->Items->Add(S"");
		lBinfo->Items->Add(String::Format(S"Mean:\t{0}", myInst->getMean().ToString()));
		lBinfo->Items->Add(String::Format(S"Variance:\t{0}", myInst->getVariance().ToString()));

		if (cBdraw_B->Checked)
		drawGraph(0);//RED

		if (cBdraw_M->Checked)
		drawGraph(10);//MIX
		*/
	 }

	 return VIPRET_OK;
 }



System::Void histForm::button3_Click(System::Object *  sender, System::EventArgs *  e)
 {
	 //
 }

void histForm::drawGraph(int channel)
 {
	if (myInst == NULL)
		return;
	PictureBox* pB_tmp = NULL;

	PixelRGB24 pix(255,255,255);
	hBuffer->clearWith(pix);

	switch(channel)
	 {
		case 0:	pB_tmp = pBdraw_R;	break;
		case 1:	pB_tmp = pBdraw_G;	break;
		case 2:	pB_tmp = pBdraw_B;	break;
		case 10:
		default:	return;
	 }

	if (pB_tmp == NULL)
		return;

	BitmapData* bitData;
	Rectangle rec(0,0, 400,400);
	bitData = dynamic_cast<Bitmap*>(pB_tmp->Image)->LockBits(rec, ImageLockMode::WriteOnly, PixelFormat::Format24bppRgb);
	unsigned char* dest = static_cast<unsigned char*>( bitData->Scan0.ToPointer() );
	vipUtility::conv_bgr_rgb(dest, (unsigned char*)hBuffer->data[0], 400, 400);
	dynamic_cast<Bitmap*>(pB_tmp->Image)->UnlockBits(bitData);
	pB_tmp->Refresh();

 }


}