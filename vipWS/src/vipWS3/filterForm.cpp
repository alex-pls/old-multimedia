#include "StdAfx.h"
#include "filterForm.h"
#include "Form1.h"

namespace vipWS3
{



filterForm::filterForm(void)
 {
	InitializeComponent();
	buffer = new vipFrameRGB24(500,400);
	myFilter = NULL;
	myObj = NULL;
	func_infoAr = NULL;
	func_infoCount = 0;

 }

void filterForm::Init(vipFilter* myFilterInstance, loaderDLL* myPlugInObj)
 {
	static_cast<Form1*>(this->MdiParent)->writeLog(S"Initializing: Loading Filter Informations..", this);

	myFilter = myFilterInstance;
	myObj = myPlugInObj;

//	myFilter->useBufferRGB(10,10);

	cBparam->Items->Add(S"Current");

	lBcb->Items->Clear();

	static_cast<Form1*>(this->MdiParent)->writeLog(S"Initializing: Loading Filter Functions Informations..", this);

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

	this->Text =  new String(myFilter->getName());
	rTBinfo->AppendText(String::Format(S"Name: {0}\r\n",new String(myFilter->getName()) ));
	rTBinfo->AppendText(String::Format(S"Version: {0}\r\n",Convert::ToString(myFilter->getVersion()) ));
	rTBinfo->AppendText(String::Format(S"Description: {0}\r\n",new String(myFilter->getDescription()) ));
	rTBinfo->AppendText(S"");

	String* path = String::Format("{0}\\reference\\{1}.info.rtf", IO::Path::GetDirectoryName(Application::ExecutablePath), new String(myObj->getInternalName() ) );
	if ( IO::File::Exists(path) )
		rTBinfo->LoadFile(path , RichTextBoxStreamType::RichText);
	else
	 {
		rTBinfo->AppendText(S"ERROR\r\n\r\nCouln't load data file: \r\n");
		rTBinfo->AppendText(path);
	 }
 }


System::Void filterForm::filterForm_Closing(System::Object *  sender, System::ComponentModel::CancelEventArgs *  e)
 {
	static_cast<Form1*>(this->MdiParent)->updateChildFormsList();
 }

void filterForm::Dispose(Boolean disposing)
 {
	static_cast<Form1*>(this->MdiParent)->writeLog(S"Destroying Filter Functions Informations..", this);

	for (int i=0; i<func_infoCount; i++)
	 {
		 func_infoAr[i]->dispose();
		 delete func_infoAr[i];
	 }

	delete func_infoAr;

	 //		delete myFilter; -> done by loaderDLL
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

VIPRESULT filterForm::importFrom(vipFrameRGB24* img)
 {
	VIPRESULT ret = VIPRET_OK;
	if (img != NULL && buffer != NULL && myFilter != NULL)
	 {
		ret += myFilter->importFrom(*img);
		ret += myFilter->extractTo(*buffer);

		if (cBautoEx->Checked)
			button1_Click(NULL, NULL);

		return ret;
	 }
	return VIPRET_ILLEGAL_USE;
 }

VIPRESULT filterForm::extractTo(vipFrameRGB24* img)
 {
	if (img != buffer)
		*img = *buffer ;

	return VIPRET_OK;
 }

System::Void filterForm::filterForm_Load(System::Object *  sender, System::EventArgs *  e)
 {
	static_cast<Form1*>(this->MdiParent)->writeLog(S"Initializing GUI..", this);

	viewsUpdate();
	sourcesUpdate();
 }


System::Void filterForm::button1_Click(System::Object *  sender, System::EventArgs *  e)
 {
	if (vF && buffer != NULL)
		vF->importFrom(buffer);
 }

System::Void filterForm::button3_Click(System::Object *  sender, System::EventArgs *  e)
 {
	if (sF)
		sF->extractTo(buffer);

	myFilter->importFrom(*buffer);
	myFilter->extractTo(*buffer);

	if (cBautoEx->Checked)
		button1_Click(sender, e);
 }

System::Void filterForm::button2_Click(System::Object *  sender, System::EventArgs *  e)
 {
	if (myFilter)
	 {
		static_cast<Form1*>(this->MdiParent)->writeLog(S"Invoking vipFilter::reset()", this);
		int ret = myFilter->reset();
		if (ret)
		 {
			static_cast<Form1*>(this->MdiParent)->writeLog(String::Format(S"FALIED: reset() returned errorcode: {0}", ret.ToString()), this);
			MessageBox::Show(this, String::Format(S"Method:\r\nint vipFilter::reset()\r\n returned errorcode: {0}", ret.ToString()));
		 }
	 }
 }

System::Void filterForm::button6_Click(System::Object *  sender, System::EventArgs *  e)
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




System::Void filterForm::comboBox1_SelectedIndexChanged(System::Object *  sender, System::EventArgs *  e)
		 {
/*
			 if (cBparam->SelectedIndex == 0)
			 {
				String* path = String::Concat(Path::GetDirectoryName(Application::ExecutablePath), S"\\current.XML.tmp" );
				myFilterParam->saveToXML((char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(path)).ToPointer());
				rTBparam->LoadFile(path, RichTextBoxStreamType::PlainText);

				FILE *fp = tmpfile();
					fpos_t position;
					char str[1024];
					fgetpos(fp, &position);
					myP->saveToXML(fp);
					fsetpos(fp, &position);
					rTBparam->Clear();
					while ( fgets(str, 1024, fp) != NULL )
					 {
						rTBparam->AppendText(new String(str));
					 }
					rTBparam->AppendText(new String(str));
					fclose(fp);

				vipFilterParameters* myP = myFilter->getFilterParameters();
				vipDigitalFilterParameters* myP = static_cast<vipDigitalFilterParameters*>(myFilter->getFilterParameters());
				if (myP)
				{
					String* path = String::Concat(Path::GetDirectoryName(Application::ExecutablePath), new String(myFilter->getName()), S".XML" );
					myP->saveToXML("prova.xml");//(char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(path)).ToPointer());
					if (File::Exists(path))
						rTBparam->LoadFile(path);


				}

			 }
*/

		 }


System::Void filterForm::button7_Click(System::Object *  sender, System::EventArgs *  e)
		 {
/*
				String* path = String::Concat(Path::GetDirectoryName(Application::ExecutablePath), S"\\current.XML.tmp" );
				rTBparam->SaveFile(path, RichTextBoxStreamType::PlainText);
				myFilterParam->loadFromXML((char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(path)).ToPointer());

			 String* data = rTBparam->Lines->ToString();

				myP = static_cast<vipFilterParameters*>(new vipDigitalFilterParameters());

					FILE *fp = tmpfile();
					fpos_t position;
					fgetpos(fp, &position);
					fputs((char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(data)).ToPointer(), fp);

					fsetpos(fp, &position);

					myP->loadFromStreamXML(fp);
					fclose(fp);

					myFilter->setFilterParameters(myP);
			 */
		 }

}