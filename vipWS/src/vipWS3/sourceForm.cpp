#include "StdAfx.h"
#include "sourceForm.h"
#include "Form1.h"

namespace vipWS3
{

sourceForm::sourceForm(void)
 {
	InitializeComponent();
	buffer = new vipFrameRGB24(500,400);
	myInput = NULL;
	myObj = NULL;
	func_infoAr = NULL;
	func_infoCount = 0;

 }

void sourceForm::Init(vipInput* myInputInstance, loaderDLL* myPlugInObj)
 {
	static_cast<Form1*>(this->MdiParent)->writeLog(S"Initializing: Loading vipInput Informations..", this);

	myInput = myInputInstance;
	myObj = myPlugInObj;

	rTBinfo->AppendText(S"Initializing Plug-In [vipInput]");
	rTBinfo->AppendText(S"");
	this->Text = new String(myObj->getClassTypeName());
//	rTBinfo->AppendText(String::Format(S"Name: {0}\r\n",new String(myFilter->getName()) ));
//	rTBinfo->AppendText(String::Format(S"Version: {0}\r\n",Convert::ToString(myFilter->getVersion()) ));
//	rTBinfo->AppendText(String::Format(S"Description: {0}\r\n",new String(myFilter->getDescription()) ));

	lBcb->Items->Clear();

	static_cast<Form1*>(this->MdiParent)->writeLog(S"Initializing: Loading Input Functions Informations..", this);

	func_infoCount = myObj->get__callback_function_list_count();
	rTBinfo->AppendText(String::Format(S"Setup Functions: {0}\r\n", func_infoCount.ToString() ));

	if ( func_infoCount > 0 )
	 {
		func_infoAr = new __vipPlugInFuncInfo*[func_infoCount];

		for (int i=0; i<func_infoCount; i++)
			{ func_infoAr[i] = new __vipPlugInFuncInfo; }

		myObj->get__callback_function_list_info(func_infoAr);

		for (int i=0; i<func_infoCount; i++)
		{
			lBcb->Items->Add(new String( func_infoAr[i]->name ));
			rTBinfo->AppendText(String::Format(S"Setup Functions: {0}\r\n", new String( func_infoAr[i]->name ) ));
		}

	 }

 }

System::Void sourceForm::sourceForm_Closing(System::Object *  sender, System::ComponentModel::CancelEventArgs *  e)
 {
	static_cast<Form1*>(this->MdiParent)->updateChildFormsList();
 }



void sourceForm::Dispose(Boolean disposing)
 {
	static_cast<Form1*>(this->MdiParent)->writeLog(S"Destroying Input Functions Informations..", this);


	for (int i=0; i<func_infoCount; i++)
	 {
		 func_infoAr[i]->dispose();
		 delete func_infoAr[i];
	 }

	delete func_infoAr;

	 //		delete myInput; -> done by loaderDLL
	static_cast<Form1*>(this->MdiParent)->writeLog(S"Destroying Interface..", this);

	if (buffer != NULL)
		delete buffer;
	buffer = NULL;

	if (disposing && components)
	 {
		components->Dispose();
	 }
	__super::Dispose(disposing);
 }



VIPRESULT sourceForm::extractTo(vipFrameRGB24* img)
 {
	if (img != NULL && myInput != NULL)
		return myInput->extractTo(*img);

	return VIPRET_ILLEGAL_USE;
 }




System::Void sourceForm::sourceForm_Load(System::Object *  sender, System::EventArgs *  e)
 {
	static_cast<Form1*>(this->MdiParent)->writeLog(S"Initializing GUI..", this);

	rTBinfo->AppendText(S"");

	String* path = String::Concat(IO::Path::GetDirectoryName(Application::ExecutablePath), S"\\reference\\.info.rtf");
	if ( IO::File::Exists(path) )
		rTBinfo->LoadFile(path , RichTextBoxStreamType::RichText);
	else
	 {
		rTBinfo->Text = "ERROR\r\n\r\nCouln't load data file: \r\n";
		rTBinfo->AppendText(path);
	 }

	viewsUpdate();
 }

System::Void sourceForm::button6_Click(System::Object *  sender, System::EventArgs *  e)
 {
	if ( lBcb->SelectedIndex == -1)
	 {
		MessageBox::Show(this, S"Select a function first!", this->Text);
		return;
	 }

	if (!tBparam1->Text->Length && !S"VOID"->Equals( new String(func_infoAr[lBcb->SelectedIndex]->param1)) )
	 {
		MessageBox::Show(this, S"Parameter Required!", this->Text);
		return;
	 }

	static_cast<Form1*>(this->MdiParent)->writeLog(String::Format(S"Invoking function: {0}{1}({2})", new String(func_infoAr[lBcb->SelectedIndex]->result), new String(func_infoAr[lBcb->SelectedIndex]->name), new String(func_infoAr[lBcb->SelectedIndex]->param1) ), this);

	__vipPlugInParams* f_param =  new __vipPlugInParams;

	if (S"BOOL"->Equals( new String(func_infoAr[lBcb->SelectedIndex]->param1)) )
		f_param->bool_value = Convert::ToBoolean(tBparam1->Text);
	else if (S"INT"->Equals( new String(func_infoAr[lBcb->SelectedIndex]->param1)) )
		f_param->int_value = Convert::ToInt32(tBparam1->Text);
	else if (S"DOUBLE"->Equals( new String(func_infoAr[lBcb->SelectedIndex]->param1)) )
		f_param->double_value = Convert::ToDouble(tBparam1->Text);
	else if (S"CHARP"->Equals( new String(func_infoAr[lBcb->SelectedIndex]->param1)) )
		f_param->charP_value = (char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(tBparam1->Text)).ToPointer();
	else if (!S"VOID"->Equals( new String(func_infoAr[lBcb->SelectedIndex]->param1)) )
	 {
		MessageBox::Show(this, S"Unknown Parameter Type!", this->Text);
	 }
//			  else if (S"VOIDP"->Equals( new String(func_infoAr[lBcb->SelectedIndex]->param1)) )
//				  f_param->charP_value = (tBparam1->Text);

	f_param->result = NULL;

	int res = 0;
	try {
		res = myObj->do__callback_function(func_infoAr[lBcb->SelectedIndex]->id, f_param);
	 }
	catch (System::Exception* ex)
	 {
		static_cast<Form1*>(this->MdiParent)->writeLog(S"Exception Raised!", this);
		static_cast<Form1*>(this->MdiParent)->writeLog(ex->ToString(), this);
		MessageBox::Show(this, ex->ToString(), String::Concat(this->Text, S": Exception Raised!"));
		return;
	 }

	if ( res < 0 )
		MessageBox::Show(this, S"Cannot call this function!\r\nProxy didn't found it!?", this->Text);
	else if ( res > 0 )
		MessageBox::Show(this, String::Format(S"Function returned an error code?\r\nErrorCode: {0}", res.ToString()), this->Text);

	if (f_param->result != NULL)
	 {
		if (S"INT"->Equals( new String(func_infoAr[lBcb->SelectedIndex]->result)) )
		 {
			int val = *( static_cast<int*>(f_param->result) );
			tBreturn->Text = val.ToString();
		 }
		else if (S"BOOL"->Equals( new String(func_infoAr[lBcb->SelectedIndex]->result)) )
		 {
			bool val = *( static_cast<bool*>(f_param->result) );
			tBreturn->Text = val.ToString();
		 }
		else
			tBreturn->Text = String::Format(S"UNKNOWN? ({0})", new String(func_infoAr[lBcb->SelectedIndex]->result));

	 }

}




System::Void sourceForm::pushFrames(int iLoop)
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
			*myInput >> *buffer;
			System::Threading::Thread::Sleep(slTime);
			vF->importFrom(buffer);
		 }
	 }
	catch (...)
	 {
		 static_cast<Form1*>(this->MdiParent)->writeLog(S"FALIED: Exception raised!", this);
	 }

 }




}
