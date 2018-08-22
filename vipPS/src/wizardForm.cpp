/**
 *  @class   wizardForm
 *
 *  @brief   package generation wizard form (source)
 *
 *  @version 1.0.0
 *  @date    12/05/2006
 *  @author  Alessandro Polo
 *
 ****************************************************************************
 * VIPLib Package Studio
 *  open source - Founded by Alessandro Polo 2006
 *  http://mmlab.science.unitn.it/projects/vipPS
 *
 *  maintained by MultiMedia Laboratory - DIT - University of Trento
 *
 ****************************************************************************/



#include "StdAfx.h"
#include "wizardForm.h"
#include "vipPKStudio.h"
#include "vipClassType.h"
#include "vipDirectories.h"
#include "vipPkgProject.h"

namespace vipPS
{

System::Void wizardForm::wizardForm_Load(System::Object *  sender, System::EventArgs *  e)
 {
	 Reset();

	 dirs = dynamic_cast<vipPKStudio*>(this->MdiParent)->Directories;
	vpp = dynamic_cast<vipPKStudio*>(this->MdiParent)->vipTemplateProjects;

 }

void wizardForm::Reset()
{
	this->Cursor = Cursors::WaitCursor;

	 Array* vct = dynamic_cast<vipPKStudio*>(this->MdiParent)->vipClassTypes;

	lB_type->Items->Clear();
	for (int i=0; i<vct->Count; i++)
		if (vct->get_Item(i) != NULL)
			lB_type->Items->Add( vct->get_Item(i) );

	Array* namesAr = dynamic_cast<vipPKStudio*>(this->MdiParent)->vipNameSpace;

	int ival = 0;
	IEnumerator* en = namesAr->GetEnumerator();
	while ( en->MoveNext() )
	 {
		String* obj = __try_cast<String*>( en->Current );
		if (obj != NULL)
		 {
			ival++;
		 }
	 }

	names = new String*[namesAr->Count];
	ival = 0;
	en = namesAr->GetEnumerator();
	while ( en->MoveNext() )
	 {
		String* obj = __try_cast<String*>( en->Current );
		if (obj != NULL)
		 {
			names[ival++] = obj;
		 }
	 }

	if (lB_type->Items->Count > 3)
		lB_type->SelectedIndex = 3;

	this->Cursor = Cursors::Default;
 }

System::Void wizardForm::lB_type_SelectedIndexChanged(System::Object *  sender, System::EventArgs *  e)
 {
	vipClassType* vct = dynamic_cast<vipClassType*>(lB_type->SelectedItem);
	tB_name->Text = vct->ClassPrefix;
 }
System::Void wizardForm::tB_name_TextChanged(System::Object *  sender, System::EventArgs *  e)
 {
	vipClassType* vct = dynamic_cast<vipClassType*>(lB_type->SelectedItem);

	if (!tB_name->Text->StartsWith(vct->ClassPrefix) )
	 {
		tB_name->BackColor = Color::FromArgb(255, 192, 192);
		return;
	 }

	for (int i=0; i < names->Count; i++)
	 {
		 if ( !tB_name->Text->CompareTo(names[i]) )
		  {
			tB_name->BackColor = Color::FromArgb(255, 192, 192);
			return;
		  }
	 }

	tB_name->BackColor = Color::FromArgb(235, 235, 255);

	lB_dir->Text = String::Concat(dirs->packages, tB_name->Text, S"\\");

 }


System::Void wizardForm::button2_Click(System::Object *  sender, System::EventArgs *  e)
 {
//check lB_type->SelectedItem

	//validate();
	if (tB_name->BackColor.R == 255)
	 {
		 MessageBox::Show(this, S"Error", S"Class name is NOT valid!");
		 return;
	 }

	this->Cursor = Cursors::WaitCursor;

	dirs = dynamic_cast<vipPKStudio*>(this->MdiParent)->Directories;
	vipClassType* vct = dynamic_cast<vipClassType*>(lB_type->SelectedItem);
	vpp = dynamic_cast<vipPKStudio*>(this->MdiParent)->vipTemplateProjects;

	vipPkgProject* newProject = new vipPkgProject();
	newProject->FriendlyName = S"Main Component Files";

	String* pathProject;
	if ( tB_dir->Text->Length > 1 )
		pathProject = tB_dir->Text;
	else
		pathProject = String::Concat(dirs->packages, tB_name->Text, S"\\");

	if ( !Directory::Exists(pathProject) )
		Directory::CreateDirectory(pathProject);

	if ( !Directory::Exists(pathProject) )
	 {
		this->Cursor = Cursors::Default;
		 MessageBox::Show(this, S"Error", S"Directory name is NOT valid!");
		 return;
	 }

// relative path workaround.. default target is /viplibROOT/packages/PKGNAME/
	String* targetSoruce = S"../../source/";
	String* targetBinaries = S"../../lib/";
	if ( !cB_relative->Checked )
	 {
		targetSoruce = dirs->vipSource;
		targetBinaries = dirs->vipBinaries;
	 }

	vipTagHash* prjHash = new vipTagHash();
	prjHash->loadDefaultHash();
	prjHash->disableAll();

	prjHash->editSimpleTag(S"%CLASSNAME%", tB_name->Text, true);
	prjHash->editSimpleTag(S"%VETTYPE%", vct->FriendlyName, true);
	prjHash->editSimpleTag(S"%CLASSDEFINE%", tB_name->Text->ToUpper(), true);
	prjHash->editSimpleTag(S"%VERSION%", tB_version->Text, true);
	prjHash->editSimpleTag(S"%AUTHOR%", tB_authors->Text, true);
	prjHash->editSimpleTag(S"%FILENAME%", tB_name->Text, true);
	prjHash->editSimpleTag(S"%TODAY%", DateTime::Now.ToString(), true);
	prjHash->editSimpleTag(S"%SOURCEDIR%", targetSoruce, true);
	prjHash->editSimpleTag(S"%LIBDIR%", targetBinaries, true);

	prjHash->editDoubleTag(S"%VFI_START%", cB_funcv->Checked);
	prjHash->editDoubleTag(S"%EFI_START%", cB_funce->Checked);
	prjHash->editDoubleTag(S"%DOCVAR%", cB_docs_v->Checked);
	prjHash->editDoubleTag(S"%DOCFUN%", cB_docs_f->Checked);

	newProject->TagHash = prjHash;

//	newPrj->TagHash->enableAllSimpleTags();
//	newPrj->TagHash->enableAllDoubleTags();

	vipPKGFile* fileH = new vipPKGFile(String::Concat(dirs->packagesTemplate, vct->TemplateFileName, S".h"), String::Concat(pathProject, tB_name->Text, S".h"));
	vipPKGFile* fileS = new vipPKGFile(String::Concat(dirs->packagesTemplate, vct->TemplateFileName, S".cpp"), String::Concat(pathProject, tB_name->Text, S".cpp"));
	vipPKGFile* fileT = new vipPKGFile(String::Concat(dirs->packagesTemplate, vct->TemplateFileName, S"_test.cpp"), String::Concat(pathProject, S"test_", tB_name->Text, S".cpp"));

	newProject->addFile(fileH);
	newProject->addFile(fileS);
	newProject->addFile(fileT);

	newProject->ApplyHashes();
	newProject->SaveOutputs();

	prjManForm* newPrj = new prjManForm();
	newPrj->MdiParent = this->MdiParent;
	newPrj->AddProject(newProject);

	IEnumerator* en = vpp->GetEnumerator();
	while ( en->MoveNext() )
		{
		vipPkgProject* obj = __try_cast<vipPkgProject*>( en->Current );
		if (obj == NULL)
			continue;

		if (	( obj->ID == 1  && cB_prj_1->Checked ) ||
				( obj->ID == 2  && cB_prj_2->Checked ) ||
				( obj->ID == 4  && cB_prj_4->Checked ) ||
				( obj->ID == 8  && cB_prj_8->Checked ) ||
				( obj->ID == 16 && cB_prj_16->Checked )||
				( obj->ID == 32 && cB_prj_32->Checked )		)
		 {
			vipPkgProject* nPrj = new vipPkgProject( obj );
			nPrj->TagHash = prjHash;
			nPrj->Directory = String::Copy( pathProject );
			nPrj->SetOutputNameFromClassName( tB_name->Text );
			nPrj->loadFiles();
			nPrj->ApplyHashes();
			nPrj->SaveOutputs();
			newPrj->AddProject(nPrj);
		 }


		}

	this->Hide();
	this->Cursor = Cursors::Default;
	newPrj->Show();
 }



}