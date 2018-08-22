#include "StdAfx.h"
#include "vipPKStudio.h"
#include "cppForm.h"
#include "notesForm.h"
#include "vipClassType.h"
#include "vipPkgProject.h"


namespace vipPS
{
	using namespace System::Threading;
	using namespace System::Net;
	using namespace System::Xml;
	using namespace System::IO;

	using namespace Microsoft::Win32;
	#undef MessageBox

vipPKStudio::vipPKStudio(void)
 {
	InitializeComponent();
	this->Text = String::Concat(S"VIPLib Package Studio ", _PS_VERSION);
 }

System::Void vipPKStudio::vipPKStudio_Load(System::Object *  sender, System::EventArgs *  e)
 {
	logFilePath = String::Concat(Path::GetDirectoryName(Application::ExecutablePath), S"\\vipPS.log");
	logLastSender = this;
	menuItem33_Click(sender, e);

	writeLog(S"");
	writeLog(S"\r\n###################################################################################");
	writeLog(S"\r\n###################################################################################");
	writeLog(S"\r\n# VIPLib Package Studio Log File                                        NEW SESSION");
	writeLog(String::Format(S"\r\n#\r\n#  Package Studio Built:\t{0}", _PS_VERSION));
	writeLog(String::Format(S"\r\n#\r\n#  Execution Time:\t{0}, {1}", DateTime::Now.ToLongDateString(), DateTime::Now.ToLongTimeString()));
	writeLog(S"\r\n#\r\n");

	//	this->add_Load(new EventHandler(this, FormLoad));

// LOAD CONFIG
//
	writeLog(S"Loading Directories...\r\n");
	Directories = new vipDirectories();
	Directories->current = Path::GetDirectoryName( Application::ExecutablePath );
	Directories->current = String::Concat(Directories->current, S"\\");


	if ( !loadVIPLibRootDirectory() )
		Directories->vipRoot = findVIPLibRootDirectory( Application::ExecutablePath );
	Directories->vipRoot = String::Concat(Directories->vipRoot, S"\\");

	writeLog(String::Format(S"VIPLib Root Directory:\t{0}\r\n", Directories->vipRoot));

	Directories->vipSource = String::Concat(Directories->vipRoot, S"source\\");
	Directories->vipBinaries = String::Concat(Directories->vipRoot, S"lib\\");
	Directories->vipTests = String::Concat(Directories->vipRoot, S"tests\\");

	if (Directories->vipRoot->Length < 3 )
		Directories->packages = String::Concat(Directories->current, S"packages\\");
	else
		Directories->packages = String::Concat(Directories->vipRoot, S"packages\\");
	Directories->packagesTemplate = String::Concat(Directories->current, S"templates\\");;

	// check for packages files:
	vipClassTypes = NULL;
	vipClassTypesXMLFile = String::Concat(Directories->packagesTemplate, S"vipTypes.xml");
	if ( !File::Exists(vipClassTypesXMLFile) )
	 {
		splashForm::CloseInstance();
		openFileDialog1->Title = S"Select path for vipTypes.xml";
		openFileDialog1->FileName = S"vipTypes.xml";
		openFileDialog1->Filter = S"XML File|*.XML";
		openFileDialog1->FilterIndex = 1;

		if ( openFileDialog1->ShowDialog() == DialogResult::OK )
		 {
			vipClassTypesXMLFile = openFileDialog1->FileName;
			Directories->packagesTemplate = Path::GetDirectoryName(openFileDialog1->FileName);
			LoadTypes(vipClassTypesXMLFile);
		 }
	 }
	else
		LoadTypes(vipClassTypesXMLFile);

	writeLog(String::Format(S"vipClassTypesXMLFile:\t{0}\r\n", vipClassTypesXMLFile));

	vipTemplateProjects = NULL;
	vipTemplateProjectsXMLFile = String::Concat(Directories->packagesTemplate, S"vipGroups.xml");
	if ( !File::Exists(vipTemplateProjectsXMLFile) )
	 {
		splashForm::CloseInstance();
		openFileDialog1->Title = S"Select path for vipGroups.xml";
		openFileDialog1->FileName = S"vipGroups.xml";
		openFileDialog1->Filter = S"XML File|*.XML";
		openFileDialog1->FilterIndex = 1;

		if ( openFileDialog1->ShowDialog() == DialogResult::OK )
		 {
			vipTemplateProjectsXMLFile = openFileDialog1->FileName;
			LoadGroups(vipTemplateProjectsXMLFile);
		 }
	 }
	else
		LoadGroups(vipTemplateProjectsXMLFile);

	writeLog(String::Format(S"vipTemplateProjectsXMLFile:\t{0}\r\n", vipTemplateProjectsXMLFile));

	vipNameSpace = NULL;
	vipNameSpaceFile = String::Concat(Directories->packagesTemplate, S"NAMESPACE");
	if ( !File::Exists(vipNameSpaceFile) )
	 {
		splashForm::CloseInstance();
		openFileDialog1->Title = S"Select path for NAMESPACE";
		openFileDialog1->FileName = S"NAMESPACE";
		openFileDialog1->Filter = S"All Files|*.*";
		openFileDialog1->FilterIndex = 1;

		if ( openFileDialog1->ShowDialog() == DialogResult::OK )
		 {
			vipNameSpaceFile = openFileDialog1->FileName;
			LoadNames(vipNameSpaceFile);
		 }
	 }
	else
		LoadNames(vipNameSpaceFile);

	writeLog(String::Format(S"vipNameSpaceFile:\t{0}\r\n", vipNameSpaceFile));

	writeLog(S"\r\n Starting Up..");
	writeLog(S"\r\n\tInitializing Child Windows..");

	myLogForm = NULL;
	myWizardForm = NULL;
	myOptionForm = NULL;
	writeLog(S"\r\n\tCreating GUI..");

	writeLog(S"\r\n\tShutting SplashForm down..");
	splashForm::CloseInstance();
	this->TopMost = true;
	this->TopMost = false;

	this->Focus();

	writeLog(S"\r\n Loading last Job.. DISABLED");

	writeLog(S"\r\n System is Ready.\r\n");
 }

System::Void vipPKStudio::vipPKStudio_Closing(System::Object *  sender, System::ComponentModel::CancelEventArgs *  e)
 {
	writeLog(S"\r\n Shutting Package Studio Down...");
	writeLog(String::Format(S"\r\n\tChecking Child Windows... {0} found", this->MdiChildren->Count.ToString() ));

	for (int i=0; i<this->MdiChildren->Count; i++)
	 {
		 writeLog(String::Format(S"\r\n\t Closing Child {0}...", static_cast<Form*>(this->MdiChildren->get_Item(i))->Text ));
		 static_cast<Form*>(this->MdiChildren->get_Item(i))->Close();
	 }

	writeLog(S"\r\n\tClosing Threads...");
	splashForm::CloseInstance(); // prevent infinite thread

 }

void vipPKStudio::Dispose(Boolean disposing)
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




System::Void vipPKStudio::menuItem41_Click(System::Object *  sender, System::EventArgs *  e)
 {
	LoadTypes(vipClassTypesXMLFile);
 }

System::Void vipPKStudio::menuItem48_Click(System::Object *  sender, System::EventArgs *  e)
 {
	LoadGroups(vipTemplateProjectsXMLFile);
 }

System::Void vipPKStudio::menuItem47_Click(System::Object *  sender, System::EventArgs *  e)
 {
	LoadNames(vipNameSpaceFile);
 }


void vipPKStudio::LoadGroups(String* xmlFile)
 {
	this->Cursor = Cursors::WaitCursor;

	writeLog(S"\r\n Loading vipGroups from XML..");

	XmlDocument* docXML = new XmlDocument;
	 try {
		docXML->Load(xmlFile);
	 }
	 catch (Exception* e)
	 {
		 MessageBox::Show(this, e->get_Message(), S"ERROR Loading. Invalid format?");
		 docXML = NULL;
		 this->Cursor = Cursors::Default;
		 return;
	 }

	 long iCount = 0;
	 XmlElement* nodRoot = docXML->DocumentElement;

	 if (!nodRoot->HasChildNodes)
	 {
		 MessageBox::Show(this, S"Error!", S"ERROR Loading. No child nodes found!");
		 docXML = NULL;
		 this->Cursor = Cursors::Default;
		 return;
	 }

	XmlNodeList* items = nodRoot->GetElementsByTagName(S"vipPgkProject");
	iCount = items->Count;
    if ( iCount == 0 )
	 {
		 MessageBox::Show(this, S"Error!", S"ERROR Loading. Invalid format?");
		 docXML = NULL;
		 this->Cursor = Cursors::Default;
		 return;
	 }

	if (vipTemplateProjects != NULL)
		vipTemplateProjects = NULL;
	vipTemplateProjects =  Array::CreateInstance(__typeof(vipPkgProject), iCount);

	writeLog(String::Format(S"\r\n\t Found {0} types..", iCount.ToString() ));
	int ic = 0;
	for (int i=0; i<iCount; i++)
	 {
		XmlNode* item = items->Item(i);
		if (item == NULL)
			continue;
		vipPkgProject* newPrjItem = new vipPkgProject();
		newPrjItem->TemplateDirectory = Directories->packagesTemplate;
		newPrjItem->load(item->ChildNodes);
		vipTemplateProjects->SetValue(newPrjItem, ic++);
	 }

	this->Cursor = Cursors::Default;

 }

void vipPKStudio::LoadNames(String* pathFile)
 {
	this->Cursor = Cursors::WaitCursor;

	writeLog(S"\r\n Loading NAMESPACE..");


	if ( !File::Exists(pathFile) )
	 {
		writeLog(String::Format(S"\r\n ERROR: File not found [{0}]..", pathFile));
		this->Cursor = Cursors::Default;
		return;
	 }

	if (vipNameSpace != NULL)
		vipNameSpace = NULL;
	int icount = 0;
	StreamReader* sr = new StreamReader(pathFile);
	try {
		String* line;
		while ( line = sr->ReadLine() )
		 {
			 if ( line->StartsWith(S"#") )
				 continue;

			 if ( line->Length < 1 )
				 continue;

			icount++;
		 }
	} __finally
	{
		sr = NULL;
	}

	vipNameSpace =  Array::CreateInstance(__typeof(String), icount);

	int ic = 0;
	sr = new StreamReader(pathFile);
	try {
		String* line;
		while ( line = sr->ReadLine() )
		 {
			 if ( line->StartsWith(S"#") )
				 continue;

			 if ( line->Length < 1 )
				 continue;

			 if (ic > icount)
				continue;

			 vipNameSpace->SetValue(line->Trim(), ic++);
		 }
	} __finally
	{
		sr = NULL;
	}

	writeLog(String::Format(S"\r\n\t Found {0} names..", vipNameSpace->Count.ToString() ));
	this->Cursor = Cursors::Default;
 }


void vipPKStudio::LoadTypes(String* xmlFile)
 {
	this->Cursor = Cursors::WaitCursor;

	writeLog(S"\r\n Loading vipClassTypes from XML..");

	XmlDocument* docXML = new XmlDocument;
	 try {
		docXML->Load(xmlFile);
	 }
	 catch (Exception* e)
	 {
		 MessageBox::Show(this, e->get_Message(), S"ERROR Loading. Invalid format?");
		 docXML = NULL;
		 this->Cursor = Cursors::Default;
		 return;
	 }

	 long iCount = 0;
	 XmlElement* nodRoot = docXML->DocumentElement;

	 if (!nodRoot->HasChildNodes)
	 {
		 MessageBox::Show(this, S"Error!", S"ERROR Loading. No child nodes found!");
		 docXML = NULL;
		 this->Cursor = Cursors::Default;
		 return;
	 }

	XmlNodeList* items = nodRoot->GetElementsByTagName(S"vipClassType");
	iCount = items->Count;
    if ( iCount == 0 )
	 {
		 MessageBox::Show(this, S"Error!", S"ERROR Loading. Invalid format?");
		 docXML = NULL;
		 this->Cursor = Cursors::Default;
		 return;
	 }

	if (vipClassTypes != NULL)
		vipClassTypes = NULL;
	vipClassTypes =  Array::CreateInstance(__typeof(vipClassType), iCount);

	 writeLog(String::Format(S"\r\n\t Found {0} types..", iCount.ToString() ));
	int ic = 0;
	for (int i=0; i<iCount; i++)
	 {
		XmlNode* item = items->Item(i);
		if (item == NULL)
			continue;
		vipClassType* newVTItem = new vipClassType();
		newVTItem->load(item->ChildNodes);
		vipClassTypes->SetValue(newVTItem, ic++);
	 }

	this->Cursor = Cursors::Default;
 }













////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
// new forms
System::Void vipPKStudio::menuItem15_Click(System::Object *  sender, System::EventArgs *  e)
 {
	this->Cursor = Cursors::WaitCursor;
	writeLog(S"\r\nNew SourcePad Instance..");
	cppForm* newChildForm = new cppForm();
	int j = 0;
	for (int i=0; i<this->MdiChildren->Count; i++)
	 {
		if ( this->MdiChildren->get_Item(i)->GetType()->Name->Equals(S"cppForm"))
			j++;
	 }
	if (j)
		newChildForm->Text = String::Format(String::Concat(newChildForm->Text, S" #{0}"), j.ToString());

	newChildForm->MdiParent = this;
	this->Cursor = Cursors::Default;
	newChildForm->Show();
 }

System::Void vipPKStudio::menuItem11_Click(System::Object *  sender, System::EventArgs *  e)
 {
	if (myWizardForm == NULL)
	 {
		this->Cursor = Cursors::WaitCursor;
		writeLog(S"\r\nInitializing Wizard Window");
		myWizardForm = new wizardForm();
		myWizardForm->MdiParent = this;
		this->Cursor = Cursors::Default;
	 }
	myWizardForm->Reset();
	myWizardForm->Show();

 }

System::Void vipPKStudio::menuItem44_Click(System::Object *  sender, System::EventArgs *  e)
 {
	this->Cursor = Cursors::WaitCursor;
	writeLog(S"\r\nListing loaded class types..");
	notesForm* newChildForm = new notesForm();
	newChildForm->Text = S"vipClassTypes";
	newChildForm->MdiParent = this;
	newChildForm->rTBdoc->ReadOnly = true;
	newChildForm->rTBdoc->Clear();
	newChildForm->rTBdoc->AppendText(S"");
	newChildForm->rTBdoc->AppendText(S"");

	if (vipClassTypes == NULL)
	 {
		newChildForm->rTBdoc->AppendText(S"No Base Class Loaded!\r\n\r\n");
		newChildForm->rTBdoc->AppendText(S"Wizard and most functionalities won't work..  ;/\r\n");
		newChildForm->rTBdoc->AppendText(S"\r\nvipClassTypes = NULL");
	 }
	else if (vipClassTypes->Count == 0)
	 {
		newChildForm->rTBdoc->AppendText(S"No Base Class Loaded!\r\n\r\n");
		newChildForm->rTBdoc->AppendText(S"Wizard and most functionalities won't work..  ;/\r\n");
		newChildForm->rTBdoc->AppendText(S"\r\nvipClassTypes->Count = 0");
	 }
	else
	 {
		newChildForm->rTBdoc->AppendText(String::Format(S"Base Classes:\t{0} \r\n", vipClassTypes->Count.ToString() ));
		newChildForm->rTBdoc->AppendText(S"Listing:\r\n\r\n");

		IEnumerator* en = vipClassTypes->GetEnumerator();
		while ( en->MoveNext() )
		 {
			newChildForm->rTBdoc->AppendText(S"\r\n_____________________________ITEM\r\n");

			vipClassType* obj = __try_cast<vipClassType*>( en->Current );
			if (obj == NULL)
				newChildForm->rTBdoc->AppendText(S"\r\nNULL ITEM!\r\nKERNEL PANIC\r\n");
			else
			 {
				 newChildForm->rTBdoc->AppendText( obj->ToBigString() );
			 }
		 }

	 }

	newChildForm->rTBdoc->AppendText(S"\r\n\r\nCompleted:");

	this->Cursor = Cursors::Default;
	newChildForm->Show();
 }

System::Void vipPKStudio::menuItem45_Click(System::Object *  sender, System::EventArgs *  e)
 {
	this->Cursor = Cursors::WaitCursor;
	writeLog(S"\r\nListing loaded prj groups..");
	notesForm* newChildForm = new notesForm();
	newChildForm->Text = S"vipPkgProjects";
	newChildForm->MdiParent = this;
	newChildForm->rTBdoc->ReadOnly = true;
	newChildForm->rTBdoc->Clear();
	newChildForm->rTBdoc->AppendText(S"");
	newChildForm->rTBdoc->AppendText(S"");

	if (vipTemplateProjects == NULL)
	 {
		newChildForm->rTBdoc->AppendText(S"No vipPkgProjects Loaded!\r\n\r\n");
		newChildForm->rTBdoc->AppendText(S"Wizard and most functionalities won't work..  ;/\r\n");
		newChildForm->rTBdoc->AppendText(S"\r\nvipTemplateProjects = NULL");
	 }
	else if (vipTemplateProjects->Count == 0)
	 {
		newChildForm->rTBdoc->AppendText(S"No vipPkgProjects Loaded!\r\n\r\n");
		newChildForm->rTBdoc->AppendText(S"Wizard and most functionalities won't work..  ;/\r\n");
		newChildForm->rTBdoc->AppendText(S"\r\nvipTemplateProjects->Count = 0");
	 }
	else
	 {
		newChildForm->rTBdoc->AppendText(String::Format(S"Base Package Projects:\t{0} \r\n", vipTemplateProjects->Count.ToString() ));
		newChildForm->rTBdoc->AppendText(S"Listing:\r\n\r\n");

		IEnumerator* en = vipTemplateProjects->GetEnumerator();
		while ( en->MoveNext() )
		 {
			newChildForm->rTBdoc->AppendText(S"\r\n_____________________________ITEM\r\n");

			vipPkgProject* obj = __try_cast<vipPkgProject*>( en->Current );
			if (obj == NULL)
				newChildForm->rTBdoc->AppendText(S"\r\nNULL ITEM!\r\nKERNEL PANIC\r\n");
			else
			 {
				 newChildForm->rTBdoc->AppendText( obj->ToBigString() );
			 }
		 }

	 }

	newChildForm->rTBdoc->AppendText(S"\r\n\r\nCompleted:");

	this->Cursor = Cursors::Default;
	newChildForm->Show();
 }

System::Void vipPKStudio::menuItem46_Click(System::Object *  sender, System::EventArgs *  e)
 {
	this->Cursor = Cursors::WaitCursor;
	writeLog(S"\r\nListing registered names..");
	notesForm* newChildForm = new notesForm();
	newChildForm->Text = S"NAMESPACE";
	newChildForm->MdiParent = this;
	newChildForm->rTBdoc->ReadOnly = true;
	newChildForm->rTBdoc->Clear();
	newChildForm->rTBdoc->AppendText(S"");
	newChildForm->rTBdoc->AppendText(S"");

	if (vipNameSpace == NULL)
	 {
		newChildForm->rTBdoc->AppendText(S"No NAMESPACE Loaded!\r\n\r\n");
		newChildForm->rTBdoc->AppendText(S"Take care of your class name!  ;/\r\n");
		newChildForm->rTBdoc->AppendText(S"\r\nvipNameSpace = NULL");
	 }
	else if (vipNameSpace->Count == 0)
	 {
		newChildForm->rTBdoc->AppendText(S"No NAMESPACE Loaded!\r\n\r\n");
		newChildForm->rTBdoc->AppendText(S"Take care of your class name!  ;/\r\n");
		newChildForm->rTBdoc->AppendText(S"\r\nvipNameSpace->Count = 0");
	 }
	else
	 {
		int icount = 0;
		IEnumerator* en = vipNameSpace->GetEnumerator();
		while ( en->MoveNext() )
		 {
			String* obj = __try_cast<String*>( en->Current );
			if (obj != NULL)
			 {
				icount++;
			 }
		 }

		 newChildForm->rTBdoc->AppendText(String::Format(S"Names count:\t{0} \r\n", icount.ToString() ));
		newChildForm->rTBdoc->AppendText(S"Listing:\r\n\r\n");

		en = vipNameSpace->GetEnumerator();
		while ( en->MoveNext() )
		 {
			String* obj = __try_cast<String*>( en->Current );
			if (obj != NULL)
			 {
				 newChildForm->rTBdoc->AppendText( String::Concat(obj, S"\r\n") );
			 }
		 }

	 }

	newChildForm->rTBdoc->AppendText(S"\r\n\r\nCompleted:");

	this->Cursor = Cursors::Default;
	newChildForm->Show();
 }

System::Void vipPKStudio::menuItem16_Click(System::Object *  sender, System::EventArgs *  e)
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

System::Void vipPKStudio::menuItem17_Click(System::Object *  sender, System::EventArgs *  e)
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

System::Void vipPKStudio::menuItem14_Click(System::Object *  sender, System::EventArgs *  e)
 {
	if (myRenamerForm == NULL)
	 {
		this->Cursor = Cursors::WaitCursor;
		writeLog(S"\r\nInitializing Package Renamer");
		myRenamerForm = new RenamerForm();
		myRenamerForm->MdiParent = this;
		this->Cursor = Cursors::Default;
	 }
	myRenamerForm->Show();
 }


System::Void vipPKStudio::menuItem21_Click(System::Object *  sender, System::EventArgs *  e)
 {
	this->Cursor = Cursors::WaitCursor;
	splashForm* aboutF = new splashForm();
	this->Cursor = Cursors::Default;
	aboutF->ShowDialog(this);
 }









































































bool vipPKStudio::loadVIPLibRootDirectory()
 {
	RegistryKey* VIPLibKey;
	RegistryKey* currentUser;
	currentUser = Registry::CurrentUser;
	VIPLibKey = currentUser->OpenSubKey(S"Software\\VIPLib", false);
	if (VIPLibKey == NULL)
	 {
		currentUser->CreateSubKey(S"Software\\VIPLib");
		VIPLibKey = currentUser->OpenSubKey(S"Software\\VIPLib", true);
		VIPLibKey->SetValue(S"VIPLib_Root", S"");
	 }
	else
	 {
		if (VIPLibKey->GetValue(S"VIPLib_Root") != NULL)
		 {
			String* str_root = VIPLibKey->GetValue(S"VIPLib_Root")->ToString();
			if (str_root != NULL)
			{
				if ( File::Exists( String::Concat(str_root, S"\\source\\vipDefs.h") ) )
				{
					Directories->vipRoot = String::Concat(str_root);
					return true;
				}
			}
		 }
	 }
	return false;
 }



String* vipPKStudio::findVIPLibRootDirectory(String *baseDir)
 {
	if (baseDir->Length > 3)
	{
		String* ret = Path::GetDirectoryName(baseDir);

		if ( File::Exists( String::Concat(ret, S"\\source\\vipDefs.h") ) )
		{
			RegistryKey* VIPLibKey = Registry::CurrentUser->OpenSubKey(S"Software\\VIPLib", true);
			if (VIPLibKey != NULL)
				VIPLibKey->SetValue(S"VIPLib_Root", ret);
			return String::Concat(ret);
		}
	else
	 {
		 int i = ret->LastIndexOf(S"\\");
		 if (i>0)
		  {
			ret = ret->Substring(0, i);
			return findVIPLibRootDirectory(ret);
		  }
	 }
	}
	folderBrowserDialog1->Description = S"Please select VIPLib root folder (it should contain: ./lib/VIPLib.lib and ./source/*.h).";
	splashForm::CloseInstance();
	folderBrowserDialog1->ShowDialog();

	if ( File::Exists( String::Concat(folderBrowserDialog1->SelectedPath, S"\\source\\vipDefs.h") ) )
	 {
		RegistryKey* VIPLibKey = Registry::CurrentUser->OpenSubKey(S"Software\\VIPLib", true);
		if (VIPLibKey != NULL)
			VIPLibKey->SetValue(S"VIPLib_Root", folderBrowserDialog1->SelectedPath);

		return folderBrowserDialog1->SelectedPath;
	 }

	 writeLog(S"Invalid VIPLib root folder!", NULL);
	 MessageBox::Show(this, S"VIPLib folder is empty, your projects will be created but they won't compile (headers and library binary links are broken)", S"Directory Error");
	 return S"";
 }




///////////////////////////////////////////////////////////////////////////////////////
//																				VARIOUS




System::Void vipPKStudio::menuItem27_Click(System::Object *  sender, System::EventArgs *  e)
 {
	 this->Cursor = Cursors::WaitCursor;

	Stream* str = NULL;
		notesForm* newChildForm = new notesForm();
		newChildForm->Text = S"ChangeLog";
		newChildForm->MdiParent = this;
		newChildForm->rTBdoc->Clear();
	try {
		HttpWebRequest* wReq = dynamic_cast<HttpWebRequest*>( WebRequest::Create(String::Concat(_PS_BASEURL, "/ChangeLog.txt")) );
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

	if ( newChildForm->rTBdoc->Lines[0]->Equals(_PS_VERSION) )
	 {
		 MessageBox::Show(this, String::Format(S"Current online version is {0}.\r\nNo updated needed.", _PS_VERSION), S"Package Studio is up to date");
	 }
	else
	 {
		 MessageBox::Show(this, String::Format(S"Current online version is {0}.\r\nYou should upgrade Package Studio.\r\nYou may need to unistall current version before proceding.", _PS_VERSION), S"New release found!");
	 }
	newChildForm->WindowState = Windows::Forms::FormWindowState::Maximized;
	newChildForm->Show();

 }


///////////////////////////////////////////////////////////////////////////////////////
//																				LOGGING

void vipPKStudio::writeLog(String* message)
 {
	if (logWriter == NULL)
		return;

	logWriter->Write(message);

	if (myLogForm != NULL && myLogForm->Visible)
		myLogForm->append(message);
 }

void vipPKStudio::writeLog(String* message, Form* sender)
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


System::Void vipPKStudio::menuItem33_Click(System::Object *  sender, System::EventArgs *  e)
{
	if ( menuItem33->Checked )
	 {
		if (logWriter == NULL)
		 {
			try {
				logWriter = File::AppendText( logFilePath );
				logWriter->AutoFlush = true;
			 }
			catch (Exception* ex) {
				MessageBox::Show(this, String::Concat(S"Exception Raised:\r\n", ex->ToString(), S"\r\n\r\nLogging will be disabled untill you setup a valid LOG file in 'Option' Menu."), S"Error accessing to LOG file");
				logWriter = NULL;
				menuItem33->Checked = false;
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



System::Void vipPKStudio::menuItem34_Click(System::Object *  sender, System::EventArgs *  e)
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
		logWriter->AutoFlush = true;
	 }
	catch (Exception* ex)
	 {
		MessageBox::Show(this, String::Concat(S"Exception Raised:\r\n", ex->ToString(), S"\r\n\r\nLogging will be disabled untill you setup a valid LOG file in 'Option' Menu."), S"Error exporting LOG file");
	 }
 }

}