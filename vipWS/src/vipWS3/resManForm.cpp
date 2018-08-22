#include "StdAfx.h"
#include "resManForm.h"
#include "Form1.h"



namespace vipWS3
{

resManForm::resManForm(void)
 {
	InitializeComponent();
	res = NULL;

	lBlog->Items->Add( S"Setting up GUI..." );

	tN_vipInput = new TreeNode(S"vipInputs");
	tN_vipOutput = new TreeNode(S"vipOutputs");
	tN_vipFilter = new TreeNode(S"vipFilters");
	tN_vipBuffer = new TreeNode(S"vipBuffers");
	tVres->Nodes->Clear();
	tVres->Refresh();
 }

void resManForm::Init(loaderDLL** resources)
 {
	static_cast<Form1*>(this->MdiParent)->writeLog(S"Initializing: Loading Resources..", this);
	lBlog->Items->Add( S"Initializing..." );
	res = resources;

	lBlog->Items->Add( S"Loading current Resources..." );
	updateRes();

	static_cast<Form1*>(this->MdiParent)->writeLog(String::Format(S"Plug-In System supports version: {0} . {1}", loaderDLL::_supported_VETPlugInSystemVersion.ToString(), loaderDLL::_supported_VETPlugInSystemRevision.ToString()), this);
	lBlog->Items->Add( S"" );

	lBlog->Items->Add( S"Resources Limit: 64" );
	lBlog->Items->Add( String::Concat( S" Supported PlugIn-System Version: ", loaderDLL::_supported_VETPlugInSystemVersion.ToString() ) );
	lBlog->Items->Add( String::Concat( S" Supported PlugIn-System Revision: ", loaderDLL::_supported_VETPlugInSystemRevision.ToString() ) );

	lBlog->Items->Add( S"" );

	lastPath = String::Concat(Path::GetDirectoryName(Application::ExecutablePath), S"\\plugins");

 }

void resManForm::Dispose(Boolean disposing)
 {
	static_cast<Form1*>(this->MdiParent)->writeLog(S"Destroying Interface..", this);

	if (disposing && components)
	 {
		components->Dispose();
	 }
	__super::Dispose(disposing);
 }

 System::Void resManForm::resManForm_Closing(System::Object *  sender, System::ComponentModel::CancelEventArgs *  e)
 {
	e->Cancel = true;
	this->Visible = false;
 }

System::Void resManForm::resManForm_Closed(System::Object *  sender, System::EventArgs *  e)
 {
	static_cast<Form1*>(this->MdiParent)->updateChildFormsList();
 }


void resManForm::updateRes(void)
 {
	tVres->Nodes->Clear();
	tN_vipInput->Nodes->Clear();
	tN_vipOutput->Nodes->Clear();
	tN_vipFilter->Nodes->Clear();
	tN_vipBuffer->Nodes->Clear();

	for (int i=0; i<64;i++)
	 {
		if (res[i] != NULL)
		 {
			switch( res[i]->getClassType() )
			 {
				case VIPCLASS_TYPE_INPUT:	tN_vipInput->Nodes->Add( new String(res[i]->getFullName() ) ); break;// new resItem(res[i]) ); break;

				case VIPCLASS_TYPE_CODEC:
				case VIPCLASS_TYPE_FILTER:	tN_vipFilter->Nodes->Add( new String(res[i]->getFullName() ) ); break;// new resItem(res[i]) ); break;

				case VIPCLASS_TYPE_OUTPUT:
				case VIPCLASS_TYPE_VISION:	tN_vipOutput->Nodes->Add( new String(res[i]->getFullName() ) ); break;// new resItem(res[i]) ); break;

				case VIPCLASS_TYPE_BUFFER:	tN_vipBuffer->Nodes->Add( new String(res[i]->getFullName() ) ); break;// new resItem(res[i]) ); break;
			 }
		 }
	 }
	if ( tN_vipInput->Nodes->Count )
		tVres->Nodes->Add( tN_vipInput );
	if ( tN_vipOutput->Nodes->Count )
		tVres->Nodes->Add( tN_vipOutput );
	if ( tN_vipFilter->Nodes->Count )
		tVres->Nodes->Add( tN_vipFilter );
	if ( tN_vipBuffer->Nodes->Count )
		tVres->Nodes->Add( tN_vipBuffer );


	tVres->Refresh();
	tVres->ExpandAll();
 }

System::Void resManForm::button1_Click(System::Object *  sender, System::EventArgs *  e)
 {
	lBlog->Items->Add( S"Importing a new Resource.." );
	static_cast<Form1*>(this->MdiParent)->writeLog(S"Importing a new Resource..", this);
	if (res[63] != NULL)
	 {
		lBlog->Items->Add( S"FALIED: System support max 64 resources.." );
		static_cast<Form1*>(this->MdiParent)->writeLog(S"FALIED: System support max 64 resources..", this);
		MessageBox::Show(this, "FALIED:\r\nSystem support max 64 resources..", this->Text, MessageBoxButtons::OK );
		return;
	 }

	openFileDialog1->Title = S"Open Resource..";
	openFileDialog1->InitialDirectory = lastPath;

	if ( openFileDialog1->ShowDialog() == DialogResult::OK )
	 {
		this->Cursor = Cursors::WaitCursor;

		lBlog->Items->Add( S"Allocation Plug-In Interface Object.. [loaderDLL]" );
		static_cast<Form1*>(this->MdiParent)->writeLog(S"Allocation Plug-In Interface Object.. [loaderDLL]", this);

		loaderDLL* newDll = new loaderDLL();
		//System::Runtime::InteropServices CONFLICTS WITH <windows.h> ?

		lBlog->Items->Add(String::Concat(S"Loading file: ", openFileDialog1->FileName) );
		static_cast<Form1*>(this->MdiParent)->writeLog(String::Concat(S"Loading file: ", openFileDialog1->FileName), this);

		int ret = newDll->load( (char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(openFileDialog1->FileName)).ToPointer() );

		if (ret)
		 {
			this->Cursor = Cursors::Default;
			static_cast<Form1*>(this->MdiParent)->writeLog(S"FALIED: Couldn't load DLL!", this);
			lBlog->Items->Add(S"FALIED: Couldn't load DLL!");
			MessageBox::Show(this, "Error Loading DLL!", this->Text, MessageBoxButtons::OK );
			return;
		 }

		lBlog->Items->Add(S"DLL Loaded. Validating Plug-in..");
		static_cast<Form1*>(this->MdiParent)->writeLog(S"DLL Loaded. Validating Plug-in..", this);

		if (newDll->validate())
		 {
			this->Cursor = Cursors::Default;
			lBlog->Items->Add(S"ERROR: DLL is not a valid VIPLib Plugin!");
			MessageBox::Show(this, "DLL is not a valid VIPLib Plugin!");
			lBlog->Items->Add( S"" );
			lBlog->Items->Add( S"DLL Hack: Function List" );

			char **pszFunctions;
			unsigned int nCount;

			if( !newDll->GetDLLFileExports(&nCount,pszFunctions) )
			{
				lBlog->Items->Add(S" Unable to browse functions in this file");
				return;
			}

			for(unsigned int i=0;i<nCount;i++)
			{
				lBlog->Items->Add(String::Concat(S"  ", new String(pszFunctions[i])));
				delete pszFunctions[i];
			}
			delete pszFunctions;

			return;
		 }

		lBlog->Items->Add(S"Plug-in Validated..");
		static_cast<Form1*>(this->MdiParent)->writeLog(S"Plug-in Validated..", this);

		lBlog->Items->Add( String::Format( S" Resolved: {0} [{1}]", new String(newDll->getFullName()), new String(newDll->getClassTypeName()) ) );
		static_cast<Form1*>(this->MdiParent)->writeLog(String::Format( S" Resolved: {0} [{1}]", new String(newDll->getFullName()), new String(newDll->getClassTypeName()), this));

		lBlog->Items->Add(S"Adding Resource to enviroment..");
		static_cast<Form1*>(this->MdiParent)->writeLog(S"Adding Resource to enviroment..", this);

		int i = 0;
		while (i<63 && res[i] != NULL)
		  { i++; };
		res[i] = newDll;

		lBlog->Items->Add(S"Updating Informations..");
		updateRes();

		static_cast<Form1*>(this->MdiParent)->registerResource(i);
		this->Cursor = Cursors::Default;
	 }
	else
	 {
		lBlog->Items->Add( S"Importing process aborted by user." );
		static_cast<Form1*>(this->MdiParent)->writeLog(S"Importing process aborted by user.", this);
	 }
 }

loaderDLL* resManForm::getSelectedResource()
 {
	 if (tVres->SelectedNode == NULL)
		 return NULL;

	 for (int i=0; i < 64; i++)
	  {
		  if ( res[i] != NULL)
		   {
			   if (tVres->SelectedNode->Text->Equals(new String(res[i]->getFullName())) )
				   return res[i];
		   }

	  }
	return NULL;
 }

System::Void resManForm::button4_Click(System::Object *  sender, System::EventArgs *  e)
 {
	loaderDLL* cR = getSelectedResource();
	 if (cR != NULL)
	 {
		this->Cursor = Cursors::WaitCursor;

		lBlog->Items->Add(S"Creating Plug-In Instance..");
		static_cast<Form1*>(this->MdiParent)->writeLog(S"Creating Plug-In Instance..", this);

		if ( cR->getInstance() )
		 {
			this->Cursor = Cursors::Default;
			MessageBox::Show(this, S"ERROR:\r\nObject exists.", this->Text, MessageBoxButtons::OK );
			return;
		 }

		cR->createInstance();
		void* hIst = cR->getInstance();

		if (hIst)
		 {
			lBlog->Items->Add(S"New Instance created.");
			static_cast<Form1*>(this->MdiParent)->writeLog(S"New Instance created.", this);
		 }
		else
		 {
			lBlog->Items->Add(S"FALIED: Couldn't create a new instance, got NULL.");
			static_cast<Form1*>(this->MdiParent)->writeLog(S"FALIED: Couldn't create a new instance, got NULL.", this);
			this->Cursor = Cursors::Default;
			MessageBox::Show(this, "ERROR:\r\nCouldn't create a new instance, got NULL.", this->Text, MessageBoxButtons::OK );
		 }
		this->Cursor = Cursors::Default;

	 }
	else
		MessageBox::Show(this, "Select a Resource first.", this->Text, MessageBoxButtons::OK );

 }

System::Void resManForm::tabControl1_SelectedIndexChanged(System::Object *  sender, System::EventArgs *  e)
{
	if (tabControl1->SelectedIndex != 1)
		return;

	loaderDLL* myRes = getSelectedResource();
	if (myRes != NULL)
	 {
		this->Cursor = Cursors::WaitCursor;

		lBlog->Items->Add(S"Getting Resource informations..");
		lBresInfo->Items->Clear();
		lBresInfo->Items->Add( S"DLL Informations:" );
		lBresInfo->Items->Add( String::Concat( S"  File Name: ", Convert::ToString(myRes->getFileName()) ) );
		lBresInfo->Items->Add( String::Concat( S"  Internal Name: ", Convert::ToString(myRes->getInternalName()) ) );

		lBresInfo->Items->Add( String::Concat( S"  Platform ID: ", Convert::ToString((int) myRes->getDLL_PlatformID()) ) );
		lBresInfo->Items->Add( String::Concat( S"  MajorVersion: ", Convert::ToString((int) myRes->getDLL_MajorVersion()) ) );
		lBresInfo->Items->Add( String::Concat( S"  MinorVersion: ", Convert::ToString((int) myRes->getDLL_MinorVersion()) ) );
		lBresInfo->Items->Add( String::Concat( S"  BuiltNumber: ", Convert::ToString((int) myRes->getDLL_BuildNumber()) ) );
		lBresInfo->Items->Add( String::Concat( S"  DLL size: ", Convert::ToString((int) myRes->getDLL_Size()) ) );

		lBresInfo->Items->Add( S"" );
		lBresInfo->Items->Add( S"Resource Informations:" );

		if ( myRes->isInitialized() )
			lBresInfo->Items->Add( S"  Initialized: yes" );
		else
			lBresInfo->Items->Add( S"  Initialized: NO" );

		if ( myRes->isValidated() )
			lBresInfo->Items->Add( S"  Validated: yes" );
		else
			lBresInfo->Items->Add( S"  Validated: NO" );

		lBresInfo->Items->Add( String::Concat( S"  PlugIn-System Version: ", Convert::ToString((int) myRes->getVETPlugInSystemVersion() ) ) );
		lBresInfo->Items->Add( String::Concat( S"  PlugIn-System Revision: ", Convert::ToString((int) myRes->getVETPlugInSystemRevision() ) ) );

		lBresInfo->Items->Add( S"" );
		lBresInfo->Items->Add( String::Format(S"  PlugIn Type: {0} [{1}]", new String(myRes->getClassTypeName()), Convert::ToString(myRes->getClassType() )));

		lBresInfo->Items->Add( S"" );
		lBresInfo->Items->Add( S"DLL Hack: Function List" );

		char **pszFunctions;
		unsigned int nCount;

		if( !myRes->GetDLLFileExports(&nCount,pszFunctions) )
		 {
			lBresInfo->Items->Add(S" Unable to browse functions in this file");
			return;
		 }

		for(unsigned int i=0;i<nCount;i++)
		 {
			lBresInfo->Items->Add(String::Concat(S"  ", new String(pszFunctions[i])));
			delete pszFunctions[i];
		 }
		delete pszFunctions;

		this->Cursor = Cursors::Default;
	}

}

System::Void resManForm::button3_Click(System::Object *  sender, System::EventArgs *  e)
 {
	loaderDLL* myRes = getSelectedResource();
	if (myRes != NULL)
	 {
		this->Cursor = Cursors::WaitCursor;
		if (myRes->validate())
		 {
				this->Cursor = Cursors::Default;
				lBlog->Items->Add(S"ERROR: DLL is not a valid VIPLib Plugin!");
				MessageBox::Show(this, "DLL is not a valid VIPLib Plugin!", this->Text, MessageBoxButtons::OK );
				return;
		 }
		lBlog->Items->Add(S"DLL Validated.");
	 }
	else
		MessageBox::Show(this, "Select a Resource first.", this->Text, MessageBoxButtons::OK );

	this->Cursor = Cursors::Default;

 }



}
