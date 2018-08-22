#pragma once
#include ".\vipEditorForm.h"
#include ".\vipPKGFile.h"
#include ".\vipPkgProject.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

#define MAXPROJECTS 32
#include ".\TreeNodeEx.h"

namespace vipPS
{

	/// <summary>
	/// Riepilogo per prjManForm
	///
	/// AVVISO: se si modifica il nome della classe, sarà necessario modificare la
	///          proprietà "Nome file di risorse" relativa allo strumento di compilazione delle risorse gestite
	///          associato a tutti i file RESX da cui dipende la classe. In caso contrario,
	///          le finestre di progettazione non saranno in grado di interagire correttamente con le
	///          risorse localizzate associate al form.
	/// </summary>
	public __gc class prjManForm : public System::Windows::Forms::Form
	{
	public:
		prjManForm(void)
		{
			InitializeComponent();
			myPrjs = new vipPkgProject*[MAXPROJECTS];
			for (int i=0; i<MAXPROJECTS; i++)
				myPrjs[i] = NULL;
			cB_prj->Items->Clear();
		}

		prjManForm(vipPkgProject* project)
		{
			InitializeComponent();
			AddProject(project);

			vipPKGFile* m = project->Files(0);
			if (m == NULL)
				return;
			String* prj_n = Path::GetFileNameWithoutExtension(m->FileOutput);
			if ( prj_n->Length )
				this->Text = String::Concat(S"PrjMan: ", prj_n);
		}

		void AddProject(vipPkgProject* project)
		{
			for (int i=0; i<MAXPROJECTS; i++)
				if (myPrjs[i] == NULL)
				 {
					myPrjs[i] = project;
					break;
				 }
			cB_prj->Items->Add(project);
			updateFiles();
			Refresh();
		}

		void updateFiles(void)
		{
			this->Cursor = Cursors::WaitCursor;
			rTB_tags->Clear();
			cB_tags->Items->Clear();
			cB_tags->Items->Add(S"Shared Hash");

			TreeNodeEx* nodes[];
			nodes = new TreeNodeEx*[MAXPROJECTS];
			for (int i=0; i<MAXPROJECTS; i++)
				nodes[i] = NULL;

			for (int i=0; i<MAXPROJECTS; i++)
			 {
				if (myPrjs[i] == NULL)
					continue;

				nodes[i] = new TreeNodeEx(myPrjs[i]);

				for (int j=0; j<MAXFILES; j++)
				 {
					 vipPKGFile* fP = myPrjs[i]->Files(j);
					 if (fP == NULL)
						 continue;

					cB_tags->Items->Add(fP);
					TreeNodeEx* nFi = new TreeNodeEx(fP);

					nodes[i]->Nodes->Add( nFi );
				 }

			 }

			tV_prj->Nodes->Clear();
			for (int i=0; i<MAXPROJECTS; i++)
				if ( nodes[i] != NULL )
					tV_prj->Nodes->Add( nodes[i] );

			tV_prj->Refresh();
			tV_prj->ExpandAll();
			this->Cursor = Cursors::Default;


		}

	protected:
		void Dispose(Boolean disposing)
		{
			if (disposing && components)
			{
				components->Dispose();
			}
			__super::Dispose(disposing);
		}


	public: vipPkgProject* myPrjs[];

	private: System::Windows::Forms::TabControl *  tabControl1;
	private: System::Windows::Forms::TabPage *  tabPage1;
	private: System::Windows::Forms::TabPage *  tabPage2;

	private: System::Windows::Forms::TreeView *  tV_prj;
	private: System::Windows::Forms::TabPage *  tabPage3;

	private: System::Windows::Forms::Panel *  panel1;
	private: System::Windows::Forms::ComboBox *  cB_tags;
	private: System::Windows::Forms::RichTextBox *  rTB_tags;
	private: System::Windows::Forms::ComboBox *  cB_prj;
	private: System::Windows::Forms::RichTextBox *  rTB_prjInfo;
	private: System::Windows::Forms::Panel *  panel2;
private: System::Windows::Forms::ToolBar *  toolBar1;
private: System::Windows::Forms::ImageList *  imageList1;

private: System::Windows::Forms::ToolBarButton *  tBB_sep1;


private: System::Windows::Forms::ContextMenu *  contextMenu1;
private: System::Windows::Forms::MenuItem *  menuItem1;
private: System::Windows::Forms::MenuItem *  menuItem2;
private: System::Windows::Forms::MenuItem *  menuItem3;
private: System::Windows::Forms::MenuItem *  menuItem4;
private: System::Windows::Forms::MenuItem *  menuItem5;
private: System::Windows::Forms::MenuItem *  menuItem6;
private: System::Windows::Forms::OpenFileDialog *  openFileDialog1;
private: System::Windows::Forms::SaveFileDialog *  saveFileDialog1;
private: System::Windows::Forms::ToolBarButton *  tBB_new;
private: System::Windows::Forms::ToolBarButton *  tBB_save;
private: System::Windows::Forms::ToolBarButton *  tBB_saveAll;
private: System::ComponentModel::IContainer *  components;





	private:
		/// <summary>
		/// Variabile di progettazione necessaria.
		/// </summary>


		/// <summary>
		/// Metodo necessario per il supporto della finestra di progettazione. Non modificare
		/// il contenuto del metodo con l'editor di codice.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = new System::ComponentModel::Container();
			System::Resources::ResourceManager *  resources = new System::Resources::ResourceManager(__typeof(vipPS::prjManForm));
			this->tabControl1 = new System::Windows::Forms::TabControl();
			this->tabPage1 = new System::Windows::Forms::TabPage();
			this->tV_prj = new System::Windows::Forms::TreeView();
			this->contextMenu1 = new System::Windows::Forms::ContextMenu();
			this->menuItem1 = new System::Windows::Forms::MenuItem();
			this->menuItem2 = new System::Windows::Forms::MenuItem();
			this->menuItem3 = new System::Windows::Forms::MenuItem();
			this->menuItem4 = new System::Windows::Forms::MenuItem();
			this->menuItem5 = new System::Windows::Forms::MenuItem();
			this->menuItem6 = new System::Windows::Forms::MenuItem();
			this->tabPage2 = new System::Windows::Forms::TabPage();
			this->rTB_prjInfo = new System::Windows::Forms::RichTextBox();
			this->panel2 = new System::Windows::Forms::Panel();
			this->cB_prj = new System::Windows::Forms::ComboBox();
			this->tabPage3 = new System::Windows::Forms::TabPage();
			this->rTB_tags = new System::Windows::Forms::RichTextBox();
			this->panel1 = new System::Windows::Forms::Panel();
			this->cB_tags = new System::Windows::Forms::ComboBox();
			this->toolBar1 = new System::Windows::Forms::ToolBar();
			this->tBB_new = new System::Windows::Forms::ToolBarButton();
			this->tBB_sep1 = new System::Windows::Forms::ToolBarButton();
			this->tBB_save = new System::Windows::Forms::ToolBarButton();
			this->tBB_saveAll = new System::Windows::Forms::ToolBarButton();
			this->imageList1 = new System::Windows::Forms::ImageList(this->components);
			this->openFileDialog1 = new System::Windows::Forms::OpenFileDialog();
			this->saveFileDialog1 = new System::Windows::Forms::SaveFileDialog();
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->tabPage3->SuspendLayout();
			this->SuspendLayout();
			//
			// tabControl1
			//
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tabControl1->Location = System::Drawing::Point(0, 0);
			this->tabControl1->Name = S"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(296, 298);
			this->tabControl1->SizeMode = System::Windows::Forms::TabSizeMode::FillToRight;
			this->tabControl1->TabIndex = 4;
			//
			// tabPage1
			//
			this->tabPage1->Controls->Add(this->tV_prj);
			this->tabPage1->DockPadding->All = 10;
			this->tabPage1->Location = System::Drawing::Point(4, 25);
			this->tabPage1->Name = S"tabPage1";
			this->tabPage1->Size = System::Drawing::Size(288, 269);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = S"Files";
			//
			// tV_prj
			//
			this->tV_prj->BackColor = System::Drawing::Color::FromArgb((System::Byte)235, (System::Byte)235, (System::Byte)255);
			this->tV_prj->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->tV_prj->ContextMenu = this->contextMenu1;
			this->tV_prj->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tV_prj->ImageIndex = -1;
			this->tV_prj->Location = System::Drawing::Point(10, 10);
			this->tV_prj->Name = S"tV_prj";
			this->tV_prj->SelectedImageIndex = -1;
			this->tV_prj->Size = System::Drawing::Size(268, 249);
			this->tV_prj->TabIndex = 0;
			this->tV_prj->DoubleClick += new System::EventHandler(this, tV_prj_DoubleClick);
			//
			// contextMenu1
			//
			System::Windows::Forms::MenuItem* __mcTemp__1[] = new System::Windows::Forms::MenuItem*[6];
			__mcTemp__1[0] = this->menuItem1;
			__mcTemp__1[1] = this->menuItem2;
			__mcTemp__1[2] = this->menuItem3;
			__mcTemp__1[3] = this->menuItem4;
			__mcTemp__1[4] = this->menuItem5;
			__mcTemp__1[5] = this->menuItem6;
			this->contextMenu1->MenuItems->AddRange(__mcTemp__1);
			//
			// menuItem1
			//
			this->menuItem1->Index = 0;
			this->menuItem1->Text = S"&Edit..";
			this->menuItem1->Click += new System::EventHandler(this, tV_prj_DoubleClick);
			//
			// menuItem2
			//
			this->menuItem2->Index = 1;
			this->menuItem2->Text = S"&Save";
			this->menuItem2->Click += new System::EventHandler(this, menuItem2_Click);
			//
			// menuItem3
			//
			this->menuItem3->Index = 2;
			this->menuItem3->Text = S"Save &To..";
			this->menuItem3->Click += new System::EventHandler(this, menuItem3_Click);
			//
			// menuItem4
			//
			this->menuItem4->Index = 3;
			this->menuItem4->Text = S"-";
			//
			// menuItem5
			//
			this->menuItem5->Index = 4;
			this->menuItem5->Text = S"&Revert to Template";
			this->menuItem5->Click += new System::EventHandler(this, menuItem5_Click);
			//
			// menuItem6
			//
			this->menuItem6->Index = 5;
			this->menuItem6->Text = S"&Apply Tag Hash";
			this->menuItem6->Click += new System::EventHandler(this, menuItem6_Click);
			//
			// tabPage2
			//
			this->tabPage2->Controls->Add(this->rTB_prjInfo);
			this->tabPage2->Controls->Add(this->panel2);
			this->tabPage2->Controls->Add(this->cB_prj);
			this->tabPage2->DockPadding->All = 10;
			this->tabPage2->Location = System::Drawing::Point(4, 25);
			this->tabPage2->Name = S"tabPage2";
			this->tabPage2->Size = System::Drawing::Size(288, 269);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = S"Settings";
			//
			// rTB_prjInfo
			//
			this->rTB_prjInfo->BackColor = System::Drawing::Color::FromArgb((System::Byte)235, (System::Byte)235, (System::Byte)255);
			this->rTB_prjInfo->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->rTB_prjInfo->Dock = System::Windows::Forms::DockStyle::Fill;
			this->rTB_prjInfo->Location = System::Drawing::Point(10, 40);
			this->rTB_prjInfo->Name = S"rTB_prjInfo";
			this->rTB_prjInfo->ReadOnly = true;
			this->rTB_prjInfo->Size = System::Drawing::Size(268, 219);
			this->rTB_prjInfo->TabIndex = 5;
			this->rTB_prjInfo->Text = S"";
			//
			// panel2
			//
			this->panel2->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel2->Location = System::Drawing::Point(10, 32);
			this->panel2->Name = S"panel2";
			this->panel2->Size = System::Drawing::Size(268, 8);
			this->panel2->TabIndex = 4;
			//
			// cB_prj
			//
			this->cB_prj->BackColor = System::Drawing::Color::FromArgb((System::Byte)235, (System::Byte)235, (System::Byte)255);
			this->cB_prj->Dock = System::Windows::Forms::DockStyle::Top;
			this->cB_prj->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cB_prj->Location = System::Drawing::Point(10, 10);
			this->cB_prj->Name = S"cB_prj";
			this->cB_prj->Size = System::Drawing::Size(268, 22);
			this->cB_prj->TabIndex = 1;
			this->cB_prj->SelectedIndexChanged += new System::EventHandler(this, cB_prj_SelectedIndexChanged);
			//
			// tabPage3
			//
			this->tabPage3->Controls->Add(this->rTB_tags);
			this->tabPage3->Controls->Add(this->panel1);
			this->tabPage3->Controls->Add(this->cB_tags);
			this->tabPage3->DockPadding->All = 10;
			this->tabPage3->Location = System::Drawing::Point(4, 25);
			this->tabPage3->Name = S"tabPage3";
			this->tabPage3->Size = System::Drawing::Size(288, 269);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = S"Tags";
			//
			// rTB_tags
			//
			this->rTB_tags->BackColor = System::Drawing::Color::FromArgb((System::Byte)235, (System::Byte)235, (System::Byte)255);
			this->rTB_tags->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->rTB_tags->Dock = System::Windows::Forms::DockStyle::Fill;
			this->rTB_tags->Location = System::Drawing::Point(10, 40);
			this->rTB_tags->Name = S"rTB_tags";
			this->rTB_tags->ReadOnly = true;
			this->rTB_tags->Size = System::Drawing::Size(268, 219);
			this->rTB_tags->TabIndex = 3;
			this->rTB_tags->Text = S"";
			//
			// panel1
			//
			this->panel1->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel1->Location = System::Drawing::Point(10, 32);
			this->panel1->Name = S"panel1";
			this->panel1->Size = System::Drawing::Size(268, 8);
			this->panel1->TabIndex = 2;
			//
			// cB_tags
			//
			this->cB_tags->BackColor = System::Drawing::Color::FromArgb((System::Byte)235, (System::Byte)235, (System::Byte)255);
			this->cB_tags->Dock = System::Windows::Forms::DockStyle::Top;
			this->cB_tags->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cB_tags->Location = System::Drawing::Point(10, 10);
			this->cB_tags->Name = S"cB_tags";
			this->cB_tags->Size = System::Drawing::Size(268, 22);
			this->cB_tags->TabIndex = 0;
			this->cB_tags->SelectedIndexChanged += new System::EventHandler(this, cB_tags_SelectedIndexChanged);
			//
			// toolBar1
			//
			this->toolBar1->Appearance = System::Windows::Forms::ToolBarAppearance::Flat;
			System::Windows::Forms::ToolBarButton* __mcTemp__2[] = new System::Windows::Forms::ToolBarButton*[4];
			__mcTemp__2[0] = this->tBB_new;
			__mcTemp__2[1] = this->tBB_sep1;
			__mcTemp__2[2] = this->tBB_save;
			__mcTemp__2[3] = this->tBB_saveAll;
			this->toolBar1->Buttons->AddRange(__mcTemp__2);
			this->toolBar1->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->toolBar1->DropDownArrows = true;
			this->toolBar1->ImageList = this->imageList1;
			this->toolBar1->Location = System::Drawing::Point(0, 298);
			this->toolBar1->Name = S"toolBar1";
			this->toolBar1->ShowToolTips = true;
			this->toolBar1->Size = System::Drawing::Size(296, 28);
			this->toolBar1->TabIndex = 5;
			this->toolBar1->ButtonClick += new System::Windows::Forms::ToolBarButtonClickEventHandler(this, toolBar1_ButtonClick);
			//
			// tBB_new
			//
			this->tBB_new->ImageIndex = 0;
			//
			// tBB_save
			//
			this->tBB_save->ImageIndex = 1;
			//
			// tBB_saveAll
			//
			this->tBB_saveAll->ImageIndex = 2;
			//
			// imageList1
			//
			this->imageList1->ImageSize = System::Drawing::Size(16, 16);
			this->imageList1->ImageStream = (__try_cast<System::Windows::Forms::ImageListStreamer *  >(resources->GetObject(S"imageList1.ImageStream")));
			this->imageList1->TransparentColor = System::Drawing::Color::Transparent;
			//
			// prjManForm
			//
			this->AutoScaleBaseSize = System::Drawing::Size(6, 15);
			this->ClientSize = System::Drawing::Size(296, 326);
			this->Controls->Add(this->tabControl1);
			this->Controls->Add(this->toolBar1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::SizableToolWindow;
			this->Name = S"prjManForm";
			this->Text = S"Project Manager";
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage2->ResumeLayout(false);
			this->tabPage3->ResumeLayout(false);
			this->ResumeLayout(false);

		}

//
private: System::Void tV_prj_DoubleClick(System::Object *  sender, System::EventArgs *  e)
		 {
			 if (tV_prj->SelectedNode == NULL)
				 return;

			 TreeNodeEx* sel = dynamic_cast<TreeNodeEx*>(tV_prj->SelectedNode);
			 if (sel == NULL)
				 return;

			 if (sel->file == NULL)
				return;
			Form* sF = sel->file->myForm;
			if (sF!= NULL)
				sF->Show();
			else
			{
			vipEditorForm* newEditor = new vipEditorForm( sel->file );
			newEditor->MdiParent = this->MdiParent;
			sel->file->myForm = newEditor;
			newEditor->Show();
			  }
		 }

private: System::Void cB_tags_SelectedIndexChanged(System::Object *  sender, System::EventArgs *  e)
		 {
			rTB_tags->Clear();

			if (cB_tags->SelectedIndex == 0)
				return;

			if (cB_tags->SelectedItem == NULL)
				return;

			vipTagHash* h = dynamic_cast<vipPKGFile*>(cB_tags->SelectedItem)->myHash;
			if (h==NULL)
			 {
				rTB_tags->AppendText(S"Hash Table is NULL for this file, shared hash will be used.\r\n");
			 }

			rTB_tags->AppendText(S"HASH TABLE:\r\n");
			rTB_tags->AppendText( h->ToString() );

		 }

private: System::Void cB_prj_SelectedIndexChanged(System::Object *  sender, System::EventArgs *  e)
		 {
			 rTB_prjInfo->Clear();

 			if (cB_prj->SelectedIndex == -1)
				return;

			if (cB_prj->SelectedItem == NULL)
				return;

			vipPkgProject* p = dynamic_cast<vipPkgProject*>(cB_prj->SelectedItem);
			if (p==NULL)
			 {
				rTB_tags->AppendText(S"it's NULL... \r\nKERNEL PANIC.\r\n");
			 }

			rTB_tags->AppendText(S"Project Informations:\r\n");
			rTB_tags->AppendText( p->ToString() );

		 }


private: System::Void menuItem2_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 if (tV_prj->SelectedNode == NULL)
				 return;

			 TreeNodeEx* sel = dynamic_cast<TreeNodeEx*>(tV_prj->SelectedNode);
			 if (sel == NULL)
				 return;

			 if (sel->file != NULL)
				sel->file->SaveOutputFile();

			 if (sel->project != NULL)
				sel->project->SaveOutputs();

			//bug: update form name (saved)	 Form* sF = sel->file->myForm;
		 }

private: System::Void menuItem3_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 if (tV_prj->SelectedNode == NULL)
				 return;

			 TreeNodeEx* sel = dynamic_cast<TreeNodeEx*>(tV_prj->SelectedNode);
			 if (sel == NULL)
				 return;

			 if (sel->file != NULL)
				sel->file->SaveOutputFile();

			 if (sel->project != NULL)
				sel->project->SaveOutputs();

//			 sel->file->SaveOutputFile();

		 }


private: System::Void menuItem5_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 if (tV_prj->SelectedNode == NULL)
				 return;

			 TreeNodeEx* sel = dynamic_cast<TreeNodeEx*>(tV_prj->SelectedNode);
			 if (sel == NULL)
				 return;
// are you sure?
			 if (sel->file != NULL)
				 sel->file->loadData();

			 if (sel->project != NULL)
				 sel->project->loadFiles();

		 }

private: System::Void menuItem6_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 if (tV_prj->SelectedNode == NULL)
				 return;

			 TreeNodeEx* sel = dynamic_cast<TreeNodeEx*>(tV_prj->SelectedNode);
			 if (sel == NULL)
				 return;
// are you sure?
			 if (sel->file != NULL)
				 sel->file->ApplyTagHash();

			 if (sel->project != NULL)
				 sel->project->ApplyHashes();
		 }

private: System::Void toolBar1_ButtonClick(System::Object *  sender, System::Windows::Forms::ToolBarButtonClickEventArgs *  e)
		 {
			 if (e->Button == tBB_new)
			  {

			  }
			 else if (e->Button == tBB_save)
			  {
				menuItem2_Click(sender, NULL);
			  }
			 else if (e->Button == tBB_saveAll)
			  {
				for (int i=0; i<MAXPROJECTS; i++)
					if ( myPrjs[i] != NULL )
						myPrjs[i]->SaveOutputs();
			  }
		 }

};
}
