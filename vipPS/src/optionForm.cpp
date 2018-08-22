/**
 *  @class   optionForm
 *
 *  @brief   options form (source)
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
#include "optionForm.h"
#include "vipPKStudio.h"


namespace vipPS
{


void optionForm::SetDirectories()
 {
	dirs = dynamic_cast<vipPKStudio*>(this->MdiParent)->Directories;

	lB_dirs->Items->Clear();
	if (dirs == NULL)
		return;
	lB_dirs->Items->Add(String::Concat(S"current:\t\t", dirs->current));
	lB_dirs->Items->Add(String::Concat(S"vipRoot:\t\t", dirs->vipRoot));
	lB_dirs->Items->Add(String::Concat(S"vipSource:\t\t", dirs->vipSource));
	lB_dirs->Items->Add(String::Concat(S"vipBinaries:\t\t", dirs->vipBinaries));
	lB_dirs->Items->Add(String::Concat(S"vipTests:\t\t", dirs->vipTests));
	lB_dirs->Items->Add(String::Concat(S"packages:\t\t", dirs->packages));
	lB_dirs->Items->Add(String::Concat(S"packagesTemplate:\t", dirs->packagesTemplate));
 }

System::Void optionForm::button3_Click(System::Object *  sender, System::EventArgs *  e)
 {
	String* selItem = lB_dirs->SelectedItem->ToString();

	if ( selItem->StartsWith(S"current") )
		dirs->current = tB_edit->Text;

	else if ( selItem->StartsWith(S"vipRoot") )
		dirs->vipRoot = tB_edit->Text;

	else if ( selItem->StartsWith(S"vipSource") )
		dirs->vipSource = tB_edit->Text;

	else if ( selItem->StartsWith(S"vipBinaries") )
		dirs->vipBinaries = tB_edit->Text;

	else if ( selItem->StartsWith(S"vipTests") )
		dirs->vipTests = tB_edit->Text;

	else if ( selItem->StartsWith(S"packages") )
		dirs->packages = tB_edit->Text;

	else if ( selItem->StartsWith(S"packagesTemplate") )
		dirs->packagesTemplate = tB_edit->Text;

	SetDirectories();
 }





}