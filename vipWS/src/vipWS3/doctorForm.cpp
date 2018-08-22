#include "StdAfx.h"
#include "doctorForm.h"
#include "Form1.h"

namespace vipWS3
{


doctorForm::doctorForm(void)
 {
	InitializeComponent();
	myDoctor = NULL;
	autoReflesh = false;
 }


void doctorForm::Init(void)
 {
	static_cast<Form1*>(this->MdiParent)->writeLog(S"Initializing: Creating vipDoctor Instance..", this);
	myDoctor = new vipDoctor();
	MessageBox::Show(this, S"vipDoctor has NOT been fully implemented jet, sorry.", "Warning");
 }

System::Void doctorForm::doctorForm_Closing(System::Object *  sender, System::ComponentModel::CancelEventArgs *  e)
 {
	static_cast<Form1*>(this->MdiParent)->updateChildFormsList();
 }

VIPRESULT doctorForm::importFrom(vipFrameRGB24* img)
 {
	VIPRESULT ret = myDoctor->importFrom(*img);

	if (autoReflesh)
		updateInfos();

	return ret;
 }

void doctorForm::Dispose(Boolean disposing)
 {
	static_cast<Form1*>(this->MdiParent)->writeLog(S"Destroying vipDoctor Instance..", this);
	delete myDoctor;

	static_cast<Form1*>(this->MdiParent)->writeLog(S"Destroying Interface..", this);
	if (disposing && components)
	{
		components->Dispose();
	}
	__super::Dispose(disposing);
 }



void doctorForm::updateInfos(void)
 {
	 tBafps->Text = Convert::ToString(myDoctor->getInputFrameRateAverage());
	 tBcfps->Text = Convert::ToString(myDoctor->getInputFrameRateCurrent());

	 tBaext->Text = Convert::ToString(myDoctor->getExecutionTimeAverage() );
	 tBcext->Text = Convert::ToString(myDoctor->getExecutionTimeCurrent() );

 }











}
