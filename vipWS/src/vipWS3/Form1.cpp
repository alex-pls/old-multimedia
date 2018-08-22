#include "StdAfx.h"
#include "Form1.h"


#include "viewForm.h"
#include "sourceForm.h"
#include "filterForm.h"
#include "bufferForm.h"

#include "intSourceImageForm.h"
#include "dxinputForm.h"
#include "dxcaptureForm.h"
#include "xvidCodecForm.h"
#include "rawCodecForm.h"
#include "histForm.h"
#include "doctorForm.h"

#include "aboutws.h"
#include "aboutvip.h"
#include "MenuItemDll.h"
/*
namespace SysWin32 {
	using namespace System::Runtime::InteropServices;

	[DllImport("user32.dll")]
		static public IntPtr GetMenu(IntPtr hwnd);
	[DllImport("user32.dll")]
		static public IntPtr GetSubMenu(IntPtr hMenu,int nPos);
	[DllImport("user32.dll")]
		static public IntPtr GetMenuItemID(IntPtr hMenu, int nPos);
	[DllImport("user32.dll")]
		static public extern int SetMenuItemBitmaps(IntPtr hMenu, IntPtr nPosition, int wFlags, IntPtr hBitmapUnchecked, IntPtr hBitmapChecked);
}
*/
namespace vipWS3
{
	using namespace System::Threading;
	using namespace System::Net;
	using namespace System::Xml;
	using namespace System::IO;


//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////// INIT, DISPOSE

Form1::Form1(void)
 {
	InitializeComponent();
	logWriter = NULL;
	this->Text = String::Concat(S"VIPLib WorkShop ", _IW_VERSION);
 }

System::Void Form1::Form1_Load(System::Object *  sender, System::EventArgs *  e)
 {
	logFilePath = String::Concat(Path::GetDirectoryName(Application::ExecutablePath), S"\\vipWS.log");
	logLastSender = this;
	menuItem71_Click(sender, e);

	writeLog(S"");
	writeLog(S"\r\n###################################################################################");
	writeLog(S"\r\n###################################################################################");
	writeLog(S"\r\n# VIPLib WorkShop Log File                                              NEW SESSION");
	writeLog(String::Format(S"\r\n#\r\n#  WorkShop Built:\t{0}", _IW_VERSION));
	writeLog(String::Format(S"\r\n#\r\n#  Execution Time:\t{0}, {1}", DateTime::Now.ToLongDateString(), DateTime::Now.ToLongTimeString()));
	writeLog(S"\r\n#\r\n");

	//	this->add_Load(new EventHandler(this, FormLoad));

	writeLog(S"\r\n Starting Up..");
	writeLog(S"\r\n\tInitializing Child Windows..");

	myLogForm = NULL;
	myResManForm = NULL;
	myOptionForm = NULL;
	myStatsForm = NULL;

	writeLog(S"\r\n\tCreating GUI..");



	writeLog(S"\r\n\tInitializing Reasources Array.. [SUPPORT 64 RES MAX]");
	resources = new loaderDLL*[64];
	for (int i=0; i<64;i++)
		{ resources[i] = NULL; }

	// logdata = new ArrayList(); //StringS


	// this->BackgroundImage = Bitmap::FromFile(String::Concat(Path::GetDirectoryName(Application::ExecutablePath), S"\\layouts\\bg.default.jpg"));
	// Thread::Sleep(2000);
	writeLog(S"\r\n\tShutting SplashForm down..");
	splashForm::CloseInstance();
	this->TopMost = true;
	this->TopMost = false;

	writeLog(S"\r\n Loading last Job.. DISABLED");



	writeLog(S"\r\n System is Ready.\r\n");
 }

System::Void Form1::Form1_Closing(System::Object *  sender, System::ComponentModel::CancelEventArgs *  e)
 {
	writeLog(S"\r\n Shutting WorkShop Down...");
	writeLog(String::Format(S"\r\n\tChecking Child Windows... {0} found", this->MdiChildren->Count.ToString() ));

	for (int i=0; i<this->MdiChildren->Count; i++)
	 {
		 writeLog(String::Format(S"\r\n\t Closing Child {0}...", static_cast<Form*>(this->MdiChildren->get_Item(i))->Text ));
		 static_cast<Form*>(this->MdiChildren->get_Item(i))->Close();
	 }

	writeLog(S"\r\n\tClosing Threads...");
	splashForm::CloseInstance(); // prevent infinite thread

	writeLog(S"\r\n\tRemoving Resources..");
	//writeLog(S"\r\n\t Removing Completed, freeing array.");

	delete [] resources;

/*BUG?!?!?????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
	for (int i=0; i<64; i++)
	 {
		 if ( resources[i] != NULL)
		  {
//			writeLog(String::Format(S"\r\n\t Removing Resource '{0}' and freeing Library", new String(resources[i]->getFullName())  ));
			resources[i]->removeInstance();
			if ( resources[i]->release() )
				writeLog(S"\r\n\t: FALIED: FreeLibrary returned FALSE, probably it will raise a heap exception..");
		  }

	 }
	 */
//	delete resources;


 }


void Form1::Dispose(Boolean disposing)
 {
	writeLog(S"\r\n Destroying WorkShop...");

	writeLog(S"\r\n\tDestroying Interface..", this);

	if (disposing && components)
	 {
		components->Dispose();
	 }
	__super::Dispose(disposing);

	writeLog(S"\r\n\tClosing Log..");
	if (logWriter != NULL)
	 {
		logWriter->Flush();
		writeLog(S"\r\n Closing Log..");
		logWriter->Flush();
		logWriter->Close();
		logWriter = NULL;
	 }
 }




//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////// MDICHILD MANAGMENT


void Form1::updateChildFormsList(void)
 {
	writeLog(S"Updating Child Windows..");

	for (int i=0; i<this->MdiChildren->Count; i++)
	 {
		if (this->MdiChildren->get_Item(i)->GetType()->GetInterface("sourceInterface"))
			static_cast<sourceInterface*> (this->MdiChildren->get_Item(i))->viewsUpdate();

		if (this->MdiChildren->get_Item(i)->GetType()->GetInterface("outputInterface"))
			static_cast<outputInterface*> (this->MdiChildren->get_Item(i))->sourcesUpdate();
	 }

	// toolbar update
	if (myLogForm != NULL)
		tBb_viewLog->Pushed = myLogForm->Visible;

	if (myResManForm != NULL)
		tBb_viewRes->Pushed = myResManForm->Visible;

	if (myStatsForm != NULL)
		tBb_viewStats->Pushed = myStatsForm->Visible;

	if (myGraphForm != NULL)
		tBb_viewGraph->Pushed = myGraphForm->Visible;

 }



System::Void Form1::resource_Click(System::Object *  sender, System::EventArgs *  e)
 {
	writeLog(S"\r\nOpening a new PlugIn Interface..");

	writeLog(S"\r\n\tGetting loaderDLL object..");
	loaderDLL* obj = static_cast<MenuItemDll*>(sender)->myObject;

	if (obj == NULL)
	 {
		writeLog(S"\r\n\t FALIED");
		writeLog(S"\r\n\t Object is NULL, this shouldn't happen, it's probably a BUG in Resource Manager loading process. please contact project admin.");
		writeLog(S"\r\n\t DETAILS");
		writeLog(String::Format(S"\r\n\t\t Menu Name: {0}", static_cast<MenuItemDll*>(sender)->Text));
		MessageBox::Show(this, S"ERROR!\r\nCannot find plugin object reference..This shouldn't happen, it's probably a BUG, please contact project admin.", this->Text);
		return;
	 }

	this->Cursor = Cursors::WaitCursor;

	writeLog(String::Format(S"\r\n\tDetecting PlugIn ClassType.. [DLL File: {0}]", Path::GetFileName(new String(obj->getFileName())) ));

	if ( obj->getClassType() == VIPCLASS_TYPE_INPUT )
	 {
		writeLog(S"\r\n\t Creating a new sourceForm Interface.. [vipInput ClassType PlugIn]");
		sourceForm* newChildForm = new sourceForm();
		newChildForm->MdiParent = this;
		vipInput* myI = NULL;

		if (obj->getInstance() != NULL)
		 {
			writeLog(S"\r\n\t Object Instance has already been allocated. That reference will be used.");
			writeLog(S"\r\n\t  (Currently only you can allocate only ONE instance of an external rersource)");
			myI = static_cast<vipInput*>( obj->getInstance() );
		 }
		else
		 {
			writeLog(S"\r\n\t Creating a new PlugIn Core Instance..");
			myI = static_cast<vipInput*>( obj->createInstance() );
		 }

		if ( myI == NULL )
		 {
			writeLog(S"\r\n\t  FALIED: loaderDLL (PlugIn Engine) cannot create object. Got NULL.");
			writeLog(S"\r\n\t  SOLUTIONS: if this error occurs ofter it is a BIG BUG, else it's a DLL problem..");
			this->Cursor = Cursors::Default;
			MessageBox::Show(this, S"FALIED: loaderDLL (PlugIn Engine) cannot create object. Got NULL.", this->Text);
			return;
		 }

		writeLog(String::Format(S"\r\n\t Initializing sourceForm Interface.. [Core: {0}, {1}, {2}]",
					new String(obj->getClassTypeName()),
					String::Format(S"PLS: ver{0}.rev{1}", Convert::ToString( (long)obj->getVETPlugInSystemVersion() ), Convert::ToString( (long)obj->getVETPlugInSystemRevision() )),
					String::Format(S"DLL:{0}.{1}.{2}", obj->getDLL_MajorVersion().ToString(), obj->getDLL_MinorVersion().ToString(), obj->getDLL_BuildNumber().ToString())
					));
		newChildForm->Init( myI, obj );
		updateChildFormsList();
		this->Cursor = Cursors::Default;
		newChildForm->Show();
		writeLog(String::Format(S"\r\n\t {0} is ready.", new String(obj->getFullName()) ));
	 }
	else if ( obj->getClassType() == VIPCLASS_TYPE_OUTPUT )
	 {
		writeLog(S"\t Creating a new outputForm Interface.. [vipOutput PlugIn]");

	 }
	else if ( obj->getClassType() == VIPCLASS_TYPE_BUFFER )
	 {
		writeLog(S"\t Creating a new bufferForm Interface.. [vipBuffer PlugIn]");
		bufferForm* newChildForm = new bufferForm();
		newChildForm->MdiParent = this;
		vipBuffer<vipFrameRGB24>* myB = NULL;

		if (obj->getInstance() != NULL)
		 {
			writeLog(S"\r\n\t Object Instance has already been allocated. That reference will be used.");
			writeLog(S"\r\n\t  (Currently only you can allocate only ONE instance of an external rersource)");
			myB = static_cast<vipBuffer<vipFrameRGB24>*>( obj->getInstance() );
		 }
		else
		 {
			writeLog(S"\r\n\t Creating a new PlugIn Core Instance..");
			myB = static_cast<vipBuffer<vipFrameRGB24>*>( obj->createInstance() );
		 }

		writeLog(String::Format(S"\r\n\t Initializing bufferForm Interface.. [Core: {0}, {1}, {2}]",
					new String(obj->getClassTypeName()),
					String::Format(S"PLS: ver{0}.rev{1}", Convert::ToString( (long)obj->getVETPlugInSystemVersion() ), Convert::ToString( (long)obj->getVETPlugInSystemRevision() )),
					String::Format(S"DLL:{0}.{1}.{2}", obj->getDLL_MajorVersion().ToString(), obj->getDLL_MinorVersion().ToString(), obj->getDLL_BuildNumber().ToString())
					));
		newChildForm->Init( myB, obj );
		updateChildFormsList();
		this->Cursor = Cursors::Default;
		newChildForm->Show();
		writeLog(String::Format(S"\r\n\t {0} is ready.", new String(obj->getFullName()) ));
	 }
	else if ( obj->getClassType() == VIPCLASS_TYPE_FILTER )
	 {
		writeLog(S"\r\n\t Creating a new sourceForm Interface.. [vipFilter ClassType PlugIn]");
		filterForm* newChildForm = new filterForm();
		newChildForm->MdiParent = this;
		vipFilter* myF = NULL;

		if (obj->getInstance() != NULL)
		 {
			writeLog(S"\r\n\t Object Instance has already been allocated. That reference will be used.");
			writeLog(S"\r\n\t  (Currently only you can allocate only ONE instance of an external rersource)");
			myF = static_cast<vipFilter*>( obj->getInstance() );
		 }
		else
		 {
			writeLog(S"\r\n\t Creating a new PlugIn Core Instance..");
			myF = static_cast<vipFilter*>( obj->createInstance() );
		 }

		writeLog(String::Format(S"\r\n\t Initializing sourceForm Interface.. [Core: {0}, {1}, {2}]",
					new String(obj->getClassTypeName()),
					String::Format(S"PLS: ver{0}.rev{1}", Convert::ToString( (long)obj->getVETPlugInSystemVersion() ), Convert::ToString( (long)obj->getVETPlugInSystemRevision() )),
					String::Format(S"DLL:{0}.{1}.{2}", obj->getDLL_MajorVersion().ToString(), obj->getDLL_MinorVersion().ToString(), obj->getDLL_BuildNumber().ToString())
					));
		newChildForm->Init( myF, obj );
		updateChildFormsList();
		this->Cursor = Cursors::Default;
		newChildForm->Show();
		writeLog(String::Format(S"\r\n\t {0} is ready.", new String(obj->getFullName()) ));
	 }
	else
	 {
		writeLog(String::Format(S"\t FALIED: Cannot import selected ClassType [{0}]", obj->getClassType().ToString() ));
		writeLog(S"\t Supported PlugIns ClassType: vipInput, vipOutput, vipFilter, vipBuffer. [and child objects]");
		this->Cursor = Cursors::Default;
		MessageBox::Show(this, String::Format(S"\t FALIED: Cannot import selected ClassType [{0}]", obj->getClassType().ToString()), this->Text);
	 }

 }

////////////////////////////////////////////////////////////////////////////////////////// DYNAMIC FORMS

System::Void Form1::menuItem37_Click(System::Object *  sender, System::EventArgs *  e)
 {
	this->Cursor = Cursors::WaitCursor;
	writeLog(S"\r\nNew Visualization Window Instance..");
	viewForm* newChildForm = new viewForm();
	int j = 0;
	for (int i=0; i<this->MdiChildren->Count; i++)
	 {
		if ( this->MdiChildren->get_Item(i)->GetType()->Name->Equals(S"viewForm") )
			j++;
	 }
	newChildForm->Text = String::Format(String::Concat(newChildForm->Text, S" #{0}"), (++j).ToString());
	newChildForm->MdiParent = this;
	updateChildFormsList();
	this->Cursor = Cursors::Default;
	newChildForm->Show();
 }


System::Void Form1::menuItem67_Click(System::Object *  sender, System::EventArgs *  e)
 {
	this->Cursor = Cursors::WaitCursor;
	writeLog(S"\r\nNew vipDoctor Interface Instance..");
	doctorForm* newChildForm = new doctorForm();
	int j = 0;
	for (int i=0; i<this->MdiChildren->Count; i++)
	 {
		if ( this->MdiChildren->get_Item(i)->GetType()->Name->Equals(S"doctorForm"))
			j++;
	 }
	newChildForm->Text = String::Format(String::Concat(newChildForm->Text, S" #{0}"), (++j).ToString());
	newChildForm->MdiParent = this;
	newChildForm->Init();
	updateChildFormsList();
	this->Cursor = Cursors::Default;
	newChildForm->Show();
 }


System::Void Form1::menuItem38_Click(System::Object *  sender, System::EventArgs *  e)
 {
	this->Cursor = Cursors::WaitCursor;
	writeLog(S"\r\nNew InternalSourceImage Instance..");
	intSourceImageForm* newChildForm = new intSourceImageForm();
	int j = 0;
	for (int i=0; i<this->MdiChildren->Count; i++)
	 {
		if ( this->MdiChildren->get_Item(i)->GetType()->Name->Equals(S"intSourceImageForm"))
			j++;
	 }
	if ( j )
		newChildForm->Text = String::Format(String::Concat(newChildForm->Text, S" #{0}"), j.ToString());

	newChildForm->MdiParent = this;
	updateChildFormsList();
	this->Cursor = Cursors::Default;
	newChildForm->Show();
 }

System::Void Form1::menuItem26_Click(System::Object *  sender, System::EventArgs *  e)
 {
	this->Cursor = Cursors::WaitCursor;
	writeLog(S"\r\nNew vipHist Instance..");
	histForm* newChildForm = new histForm();
	int j = 0;
	for (int i=0; i<this->MdiChildren->Count; i++)
	 {
		if ( this->MdiChildren->get_Item(i)->GetType()->Name->Equals(S"histForm"))
			j++;
	 }
	if (j)
		newChildForm->Text = String::Format(String::Concat(newChildForm->Text, S" #{0}"), j.ToString());

	newChildForm->MdiParent = this;
	updateChildFormsList();
	this->Cursor = Cursors::Default;
	newChildForm->Show();
 }


System::Void Form1::menuItem47_Click(System::Object *  sender, System::EventArgs *  e)
 {
	this->Cursor = Cursors::WaitCursor;
	writeLog(S"\r\nNew NotePad Instance..");
	notesForm* newChildForm = new notesForm();
	int j = 0;
	for (int i=0; i<this->MdiChildren->Count; i++)
	 {
		if ( this->MdiChildren->get_Item(i)->GetType()->Name->Equals(S"notesForm"))
			j++;
	 }
	if (j)
		newChildForm->Text = String::Format(String::Concat(newChildForm->Text, S" #{0}"), j.ToString());

	newChildForm->MdiParent = this;
	this->Cursor = Cursors::Default;
	newChildForm->Show();
 }

System::Void Form1::menuItem4_Click(System::Object *  sender, System::EventArgs *  e)
 {
	this->Cursor = Cursors::WaitCursor;
	writeLog(S"\r\nNew InternalSourceImage Instance..");
	intSourceImageForm* newChildForm = new intSourceImageForm();
	int j = 0;
	for (int i=0; i<this->MdiChildren->Count; i++)
	 {
		if ( this->MdiChildren->get_Item(i)->GetType()->Name->Equals(S"intSourceImageForm"))
			j++;
	 }
	if (j)
		newChildForm->Text = String::Format(String::Concat(newChildForm->Text, S" #{0}"), j.ToString());

	newChildForm->MdiParent = this;
	updateChildFormsList();
	this->Cursor = Cursors::Default;
	newChildForm->button6_Click(sender, e);
	newChildForm->Show();
 }
System::Void Form1::menuItem66_Click(System::Object *  sender, System::EventArgs *  e)
 {
	this->Cursor = Cursors::WaitCursor;
	writeLog(S"\r\nNew vipCodec_XVID Instance..");
	xvidCodecForm* newChildForm = new xvidCodecForm();
	int j = 0;
	for (int i=0; i<this->MdiChildren->Count; i++)
	 {
		if ( this->MdiChildren->get_Item(i)->GetType()->Name->Equals(S"xvidCodecForm"))
			j++;
	 }
	if (j)
		newChildForm->Text = String::Format(String::Concat(newChildForm->Text, S" #{0}"), j.ToString());

	newChildForm->MdiParent = this;
	updateChildFormsList();
	newChildForm->Init();
	this->Cursor = Cursors::Default;
	newChildForm->button2_Click(sender, e);
	newChildForm->Show();
 }
System::Void Form1::menuItem86_Click(System::Object *  sender, System::EventArgs *  e)
 {
	this->Cursor = Cursors::WaitCursor;
	writeLog(S"\r\nNew vipCodec_RAW Instance..");
	rawCodecForm* newChildForm = new rawCodecForm();
	int j = 0;
	for (int i=0; i<this->MdiChildren->Count; i++)
	 {
		if ( this->MdiChildren->get_Item(i)->GetType()->Name->Equals(S"xvidCodecForm"))
			j++;
	 }
	if (j)
		newChildForm->Text = String::Format(String::Concat(newChildForm->Text, S" #{0}"), j.ToString());

	newChildForm->MdiParent = this;
	updateChildFormsList();
	newChildForm->Init();
	this->Cursor = Cursors::Default;
	newChildForm->button2_Click(sender, e);
	newChildForm->Show();

 }
System::Void Form1::menuItem28_Click(System::Object *  sender, System::EventArgs *  e)
 {
	this->Cursor = Cursors::WaitCursor;
	writeLog(S"\r\nNew vipDirectXInput Instance..");
	dxinputForm* newChildForm = new dxinputForm();
	int j = 0;
	for (int i=0; i<this->MdiChildren->Count; i++)
	 {
		if ( this->MdiChildren->get_Item(i)->GetType()->Name->Equals(S"dxinputForm"))
			j++;
	 }
	if (j)
		newChildForm->Text = String::Format(String::Concat(newChildForm->Text, S" #{0}"), j.ToString());

	newChildForm->MdiParent = this;
	newChildForm->Init();
	updateChildFormsList();
	this->Cursor = Cursors::Default;
	newChildForm->Show();
 }
System::Void Form1::menuItem85_Click(System::Object *  sender, System::EventArgs *  e)
 {
	this->Cursor = Cursors::WaitCursor;
	writeLog(S"\r\nNew vipDirectXInput2 Instance..");
	dxcaptureForm* newChildForm = new dxcaptureForm();
	int j = 0;
	for (int i=0; i<this->MdiChildren->Count; i++)
	 {
		if ( this->MdiChildren->get_Item(i)->GetType()->Name->Equals(S"dxcaptureForm"))
			j++;
	 }
	if (j)
		newChildForm->Text = String::Format(String::Concat(newChildForm->Text, S" #{0}"), j.ToString());

	newChildForm->MdiParent = this;
	newChildForm->Init();
	updateChildFormsList();
	this->Cursor = Cursors::Default;
	newChildForm->Show();
 }

System::Void Form1::menuItem65_Click(System::Object *  sender, System::EventArgs *  e)
 {
	this->Cursor = Cursors::WaitCursor;
	writeLog(S"\r\nNew vipCodec_XVID Instance..");
	xvidCodecForm* newChildForm = new xvidCodecForm();
	int j = 0;
	for (int i=0; i<this->MdiChildren->Count; i++)
	 {
		if ( this->MdiChildren->get_Item(i)->GetType()->Name->Equals(S"xvidCodecForm"))
			j++;
	 }
	if (j)
		newChildForm->Text = String::Format(String::Concat(newChildForm->Text, S" #{0}"), j.ToString());

	newChildForm->MdiParent = this;
	newChildForm->Init();
	updateChildFormsList();
	this->Cursor = Cursors::Default;
	newChildForm->Show();
 }


////////////////////////////////////////////////////////////////////////////////////////// ONE-INSTANCE FORMS

System::Void Form1::menuItem49_Click(System::Object *  sender, System::EventArgs *  e)
 {
	if (myLogForm == NULL)
	 {
		this->Cursor = Cursors::WaitCursor;
		writeLog(S"\r\nInitializing Log Window");
		myLogForm = new logForm();
		myLogForm->MdiParent = this;
		myLogForm->Location.X = 0;
		myLogForm->Location.Y = this->ClientSize.Height - myLogForm->Height - 25;
		String* filen = String::Concat(Path::GetDirectoryName(Application::ExecutablePath)->Replace(S"\\", S"/"), "vipWS.log");
		myLogForm->append(String::Format(S"[..] file://{0}", filen));
		myLogForm->append(S"Logging from Now here..");
		myLogForm->Refresh();
		this->Cursor = Cursors::Default;
	 }
	myLogForm->Show();
 }


System::Void Form1::menuItem56_Click(System::Object *  sender, System::EventArgs *  e)
 {
	if (myOptionForm == NULL)
	 {
		this->Cursor = Cursors::WaitCursor;
		writeLog(S"\r\nInitializing Options Window");
		myOptionForm = new optionForm();
		myOptionForm->MdiParent = this;
		this->Cursor = Cursors::Default;
	 }
	myOptionForm->Show();
 }


System::Void Form1::menuItem62_Click(System::Object *  sender, System::EventArgs *  e)
 {
	if (myStatsForm == NULL)
	 {
		this->Cursor = Cursors::WaitCursor;
		writeLog(S"\r\nInitializing Statistics Window");
		myStatsForm = new statsForm();
		myStatsForm->MdiParent = this;
		this->Cursor = Cursors::Default;
	 }
	myStatsForm->Show();
 }


System::Void Form1::menuItem23_Click(System::Object *  sender, System::EventArgs *  e)
 {
	if (myResManForm == NULL)
	 {
		this->Cursor = Cursors::WaitCursor;
		writeLog(S"\r\nInitializing Resource Manager..");
		myResManForm = new resManForm();
		myResManForm->MdiParent = this;
		myResManForm->Init((loaderDLL**)resources);
		this->Cursor = Cursors::Default;
	 }
	myResManForm->Show();
 }


System::Void Form1::menuItem68_Click(System::Object *  sender, System::EventArgs *  e)
 {
	if (myGraphForm == NULL)
	 {
		this->Cursor = Cursors::WaitCursor;
		writeLog(S"\r\nInitializing Graph View..");
		myGraphForm = new graphForm();
		myGraphForm->MdiParent = this;
		myGraphForm->Init();
		this->Cursor = Cursors::Default;
	 }
	myGraphForm->Show();
 }


System::Void Form1::menuItem16_Click(System::Object *  sender, System::EventArgs *  e)
 {
	this->Cursor = Cursors::WaitCursor;
	splashForm* aboutF = new splashForm();
	this->Cursor = Cursors::Default;
	aboutF->ShowDialog(this);
 }

System::Void Form1::menuItem17_Click(System::Object *  sender, System::EventArgs *  e)
 {
	this->Cursor = Cursors::WaitCursor;
	aboutvip* aboutF = new aboutvip();
	this->Cursor = Cursors::Default;
	aboutF->ShowDialog(this);
 }


System::Void Form1::menuItem84_Click(System::Object *  sender, System::EventArgs *  e)
 {
	 this->Cursor = Cursors::WaitCursor;

	Stream* str = NULL;
		notesForm* newChildForm = new notesForm();
		newChildForm->Text = S"ChangeLog";
		newChildForm->MdiParent = this;
		newChildForm->rTBdoc->Clear();
	try {
		HttpWebRequest* wReq = dynamic_cast<HttpWebRequest*>( WebRequest::Create("http://lnx.ewgate.net/viplib/distr/Tools/vipWS/ChangeLog") );
		HttpWebResponse* wRes = dynamic_cast<HttpWebResponse*>((wReq)->GetResponse() );
		str = wRes->GetResponseStream();
		System::Text::Encoding* enc = System::Text::Encoding::GetEncoding(S"utf-8");
		StreamReader* rS = new StreamReader(str, enc);
		newChildForm->rTBdoc->AppendText( rS->ReadToEnd() );
		wRes->Close();
		rS->Close();
	 }
	catch (Exception* e)
	 {
		 this->Cursor = Cursors::Default;
		 newChildForm->rTBdoc->AppendText( e->ToString() );
		 MessageBox::Show(this, e->ToString(), S"Connection FALIED");
		 newChildForm->Close();
		 newChildForm = NULL;
		 return;
	 }

	this->Cursor = Cursors::Default;

	if ( newChildForm->rTBdoc->Lines[0]->Equals(_IW_VERSION) )
	 {
		 MessageBox::Show(this, String::Format(S"Current online version is {0}.\r\nNo updated needed.", _IW_VERSION), S"WorkShop is up to date");
	 }
	else
	 {
		 MessageBox::Show(this, String::Format(S"Current online version is {0}.\r\nYou should upgrade WorkShop.", _IW_VERSION), S"New release found!");
	 }
	newChildForm->WindowState = Maximized;
	newChildForm->Show();

 }




//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////// PLUGIN SYSTEM


void Form1::registerResource(int res_index)
 {
	writeLog(S"\r\nAdding new resource to menu..");

	MenuItemDll* myMenu = new MenuItemDll( new String(resources[res_index]->getFullName()) );
	myMenu->myObject = resources[res_index];
	EventHandler* myH = new EventHandler(this, &Form1::resource_Click);
	myMenu->add_Click(myH);

	switch ( resources[res_index]->getClassType() )
	 {
		case VIPCLASS_TYPE_INPUT:	mISources->MenuItems->Add(myMenu); break;

		case VIPCLASS_TYPE_CODEC:
		case VIPCLASS_TYPE_FILTER:	mIFilters->MenuItems->Add(myMenu); break;

		case VIPCLASS_TYPE_VISION:
		case VIPCLASS_TYPE_OUTPUT:  mIOutputs->MenuItems->Add(myMenu); break;

		case VIPCLASS_TYPE_BUFFER:	mIBuffers->MenuItems->Add(myMenu); break;
	//	case VIPCLASS_TYPE_FRAME:
	//	case VIPCLASS_TYPE_UNKNOW:
//		default:
	 }
 }



//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////// SETTINGS & LAYOUT

void Form1::loadMenuIcons()
 {
/*
	 IntPtr intPtrMenu = SysWin32::GetMenu(this->Handle);

	IntPtr* intPtrMenus = new IntPtr[mainMenu1->MenuItems->Count];

	for (int i=0; i<mainMenu1->MenuItems->Count; i++)
	 {
		 intPtrMenus[i] = SysWin32::GetSubMenu(intPtrMenu, i);
	 }

	IntPtr intPtrMenuItem = SysWin32::GetMenuItemID(intPtrMenus[0], 0) ;

	String* filename = String::Concat(Path::GetDirectoryName(Application::ExecutablePath), S"\\layouts\\icons\\open.ico");

	Bitmap* hBitmap = Bitmap::FromFile(filename);

//hBitmap

	int ret = SysWin32::SetMenuItemBitmaps(intPtrMenu, intPtrMenuItem, 0, hBitmap->GetHbitmap(), hBitmap->GetHbitmap());


	delete intPtrMenus;
	*/
 }


void Form1::loadLayout(String* filePath)
 {
	this->Cursor = Cursors::WaitCursor;
/*
	 XmlDocument* docXML = new XmlDocument;

	 docXML->Load(filePath);

	 XmlElement* nodRoot = docXML->DocumentElement;

	 String* ColorStr = nodRoot->Attributes->ItemOf[S"BackGround"]->Attributes->ItemOf[S"Color"]->InnerText;
//	 Drawing::ColorConverter:
	 String* backImageStr = nodRoot->Attributes->ItemOf[S"BackGround"]->Attributes->ItemOf[S"Image"]->InnerText;

	 if ( backImageStr->Trim()->Length == 0 )
         this->BackgroundImage = NULL;
	 else
	  {
		backImageStr = String::Concat(String::Concat(Path::GetDirectoryName(Application::ExecutablePath), S"\\layouts\\"), backImageStr);

		 if ( File::Exists(backImageStr) )
			this->BackgroundImage = Bitmap::FromFile(backImageStr);
	  }


//
	 XmlNodeList *windowsItems = nodRoot->GetElementsByTagName(S"Windows");

	 for(int i = 0; i < windowsItems->Count; i++)
	  {
		String* title = windowsItems->ItemOf[i]->Attributes->ItemOf[S"Name"]->InnerText;
		int posX = Convert::ToInt16(windowsItems->ItemOf[i]->Attributes->ItemOf[S"posX"]->InnerText);
		int posY = Convert::ToInt16(windowsItems->ItemOf[i]->Attributes->ItemOf[S"posY"]->InnerText);
		int dimX = Convert::ToInt16(windowsItems->ItemOf[i]->Attributes->ItemOf[S"dimX"]->InnerText);
		int dimY = Convert::ToInt16(windowsItems->ItemOf[i]->Attributes->ItemOf[S"dimX"]->InnerText);
//		String* coreClass = windowsItems->ItemOf[i]->Attributes->ItemOf[S"coreType"]->InnerText;

	  }
	this->Refresh();
	this->Cursor = Cursors::Default;
*/
 }




System::Void Form1::menuItem53_Click(System::Object *  sender, System::EventArgs *  e)
 {
	writeLog(S"Updating Background..");
	this->Cursor = Cursors::WaitCursor;
	this->BackgroundImage = NULL;
	this->Refresh();
	this->Cursor = Cursors::Default;
 }

System::Void Form1::menuItem54_Click(System::Object *  sender, System::EventArgs *  e)
 {
	writeLog(S"Updating Background..");
	this->Cursor = Cursors::WaitCursor;
	this->BackgroundImage = NULL;
	String* filename = String::Concat(Path::GetDirectoryName(Application::ExecutablePath), S"\\layouts\\bg.default.jpg");
	if ( File::Exists(filename) )
		this->BackgroundImage = Bitmap::FromFile(filename);
	else
		MessageBox::Show(this, String::Concat(S"File not found:\r\n", filename));
	this->Refresh();
	this->Cursor = Cursors::Default;
 }


//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////// LOGGING SYSTEM

/*
using System::diagno
useing reflection

StackTrace* sT = new StackTrace();
StackFrame* sF = sT->GetFrame();
MethodBase* mB = sF->GetMethod();

[..]  methodBase->Name


*/


void Form1::writeLog(String* message)
 {
	if (logWriter == NULL)
		return;

	logWriter->Write(message);

	if (myLogForm != NULL && myLogForm->Visible)
		myLogForm->append(message);
 }

void Form1::writeLog(String* message, Form* sender)
 {
	if (logWriter == NULL)
		return;

	if ( sender != NULL && sender != logLastSender )
		logWriter->Write("\r\n___from_ {0}:", sender->ToString());

	logWriter->WriteLine(message);

	if (myLogForm != NULL && myLogForm->Visible)
	 {
		if ( sender != NULL && sender != logLastSender )
			myLogForm->append(String::Format("\r\n___from_ {0}:", sender->ToString()));

		myLogForm->append(message);
	 }

	if (sender)
		logLastSender = sender;
	else
		logLastSender = this;
 }

System::Void Form1::menuItem71_Click(System::Object *  sender, System::EventArgs *  e)
{
	if ( menuItem71->Checked )
	 {
		if (logWriter == NULL)
		 {
			try {
				logWriter = File::AppendText( logFilePath );
				logWriter->AutoFlush = menuItem75->Checked;
			 }
			catch (Exception* ex) {
				MessageBox::Show(this, String::Concat(S"Exception Raised:\r\n", ex->ToString(), S"\r\n\r\nLogging will be disabled untill you setup a valid LOG file in 'Option' Menu."), S"Error accessing to LOG file");
				logWriter = NULL;
				menuItem71->Checked = false;
			 }
		 }
	 }
	else
	 {
		if (logWriter != NULL)
		 {
			logWriter->Flush();
			writeLog(S"Closing Log..");
			logWriter->Flush();
			logWriter->Close();
		 }
	 }

}

System::Void Form1::menuItem72_Click(System::Object *  sender, System::EventArgs *  e)
 {
	if (logWriter == NULL)
	 {
		MessageBox::Show(this, S"Logging System is currently disabled.\r\nEnable it checking first item in Options->Logging menu.", this->Text);
		return;
	 }

	openFileDialog1->Title = S"Export LOG as..";
	openFileDialog1->InitialDirectory = Application::get_ExecutablePath();
	openFileDialog1->Filter = S"Plain Text LOG files (*.LOG)|*.log|Plain Text files (*.TXT)|*.txt|All files (*.*)|*.*";
	openFileDialog1->FilterIndex = 1;

	if ( openFileDialog1->ShowDialog() != DialogResult::OK )
		return;

	try
	 {
		logWriter->Flush();
		logWriter->Close();
		File::Copy(logFilePath, openFileDialog1->FileName, true);
		logWriter = File::AppendText( logFilePath );
		logWriter->AutoFlush = menuItem75->Checked;
	 }
	catch (Exception* ex)
	 {
		MessageBox::Show(this, String::Concat(S"Exception Raised:\r\n", ex->ToString(), S"\r\n\r\nLogging will be disabled untill you setup a valid LOG file in 'Option' Menu."), S"Error exporting LOG file");
	 }
 }

System::Void Form1::menuItem73_Click(System::Object *  sender, System::EventArgs *  e)
 {
	openFileDialog1->Title = S"Select LOG file..";
	openFileDialog1->InitialDirectory = Application::get_ExecutablePath();
	openFileDialog1->Filter = S"Plain Text LOG files (*.LOG)|*.log|Plain Text files (*.TXT)|*.txt|All files (*.*)|*.*";
	openFileDialog1->FilterIndex = 1;

	if ( openFileDialog1->ShowDialog() != DialogResult::OK )
		return;

	openFileDialog1->FileName->Copy(logFilePath);

	try
	 {
		if ( logWriter != NULL )
		 {
			logWriter->Flush();
			logWriter->Close();
		 }
		logWriter = File::AppendText( logFilePath );
		logWriter->AutoFlush = menuItem75->Checked;
	 }
	catch (Exception* ex)
	 {
		MessageBox::Show(this, String::Concat(S"Exception Raised:\r\n", ex->ToString(), S"\r\n\r\nLogging will be disabled untill you setup a valid LOG file in 'Option' Menu."), S"Error exporting LOG file");
		logWriter = NULL;
	 }
 }

System::Void Form1::menuItem75_Click(System::Object *  sender, System::EventArgs *  e)
 {
	if (logWriter == NULL)
	 {
		MessageBox::Show(this, S"Logging is disabled, enable it first.", this->Text);
		return;
	 }
	logWriter->AutoFlush = menuItem75->Checked;
 }





System::Void Form1::menuItem58_Click(System::Object *  sender, System::EventArgs *  e)
 {
	this->Cursor = Cursors::WaitCursor;
/*
	CustomData cD = new CustomData(myImage, myString);
	IDataObject* iData->setData(CustomData::Format::Name, false, cD);
	[..]
	GetDataPresent(CustomData::Format::Name)) ...
*/
	writeLog(String::Format(S"Pasting Clipboard data to '{0}'..", this->ActiveMdiChild->Text));

	IDataObject* iData = Clipboard::GetDataObject();

	if ( this->ActiveMdiChild->GetType()->Name->Equals(S"viewForm") )
	 {
		if (iData->GetDataPresent(DataFormats::Bitmap))
		 {
			Bitmap* bM = dynamic_cast<Bitmap*>(iData->GetData(DataFormats::Bitmap));
			if (bM->Width * bM->Height == 0)
			 {
				 writeLog(String::Format(S"FALIED: Clipboard image size is invalid [{0}, {1}]", bM->Width.ToString(), bM->Height.ToString() ));
				 this->Cursor = Cursors::Default;
				return;
			 }
			static_cast<viewForm*> (this->ActiveMdiChild)->bm = bM;
		 }
		else
			writeLog(String::Format(S"FALIED: Clipboard data format is invalid: '{0}'", S"?" ));

	 }
	else if ( this->ActiveMdiChild->GetType()->GetInterface(S"outputInterface") )
	 {
		if (iData->GetDataPresent(DataFormats::Bitmap))
		 {
			Bitmap* bM = dynamic_cast<Bitmap*>(iData->GetData(DataFormats::Bitmap));

			if (bM->Width * bM->Height == 0)
			 {
				 writeLog(String::Format(S"FALIED: Clipboard image size is invalid [{0}, {1}]", bM->Width.ToString(), bM->Height.ToString() ));
				 this->Cursor = Cursors::Default;
				return;
			 }

			vipFrameRGB24* buffer = new vipFrameRGB24(bM->Width, bM->Height);
			BitmapData* bitData;
			Rectangle rec(0,0, bM->Width, bM->Height);
			bitData = bM->LockBits(rec, ImageLockMode::WriteOnly, PixelFormat::Format24bppRgb);
			//this would be great but micro$oft always LIES, it's BGR not RGB.. so
			//memcpy(bitData->Scan0.ToPointer(), img.data[0], img.height*img.width*3* sizeof(char));
			unsigned char* dest = static_cast<unsigned char*>( bitData->Scan0.ToPointer() );
			vipUtility::conv_bgr_rgb((unsigned char*)buffer->data[0], dest, bM->Width, bM->Height);
			bM->UnlockBits(bitData);

			dynamic_cast<outputInterface*> (this->ActiveMdiChild)->importFrom(buffer);

			delete buffer;
		 }
		else
			writeLog(String::Format(S"FALIED: Clipboard data format is invalid: '{0}'", S"?" ));

	 }

	this->Cursor = Cursors::Default;
 }

System::Void Form1::menuItem57_Click(System::Object *  sender, System::EventArgs *  e)
 {
	this->Cursor = Cursors::WaitCursor;
	writeLog(String::Format(S"Copying data of '{0}' to Clipboard..", this->ActiveMdiChild->Text));
	//Clipboard::SetDataObject( static_cast<viewForm*> (this->ActiveMdiChild)->bm );

	if ( this->ActiveMdiChild->GetType()->Name->Equals(S"viewForm") )
	 {

		if ( static_cast<viewForm*>(this->ActiveMdiChild)->bm == NULL )
		 {
			writeLog(S"FALIED: source image is invalid [NULL]");
			this->Cursor = Cursors::Default;
			return;
		 }
		else
		 {
//			 IDataObject* iData = new DataObject();
//			 iData->SetData(Data

			Clipboard::SetDataObject(static_cast<viewForm*>(this->ActiveMdiChild)->bm);
		 }

	 }
	else if ( this->ActiveMdiChild->GetType()->GetInterface(S"sourceInterface") )
	 {
		vipFrameRGB24* buffer = new vipFrameRGB24();
		dynamic_cast<sourceInterface*> (this->ActiveMdiChild)->extractTo(buffer);

		if (buffer == NULL)
		 {
			writeLog(S"FALIED: extracted image is invalid [NULL], memory data lost!");
			this->Cursor = Cursors::Default;
			return;
		 }
		else if (buffer->width * buffer->height == 0 )
		 {
			writeLog(S"FALIED: source image size is invalid [w*h=0]");
			this->Cursor = Cursors::Default;
			return;
		 }
		else
		 {
			Bitmap* bM = new Bitmap(buffer->width, buffer->height);
			BitmapData* bitData;
			Rectangle rec(0,0, bM->Width, bM->Height);
			bitData = bM->LockBits(rec, ImageLockMode::WriteOnly, PixelFormat::Format24bppRgb);
			//this would be great but micro$oft always LIES, it's BGR not RGB.. so
			//memcpy(bitData->Scan0.ToPointer(), img.data[0], img.height*img.width*3* sizeof(char));
			unsigned char* dest = static_cast<unsigned char*>( bitData->Scan0.ToPointer() );
			vipUtility::conv_bgr_rgb(dest, (unsigned char*)buffer->data[0], bM->Width, bM->Height);
			bM->UnlockBits(bitData);

			Clipboard::SetDataObject(bM);
		 }


	 }

	this->Cursor = Cursors::Default;
 }



}