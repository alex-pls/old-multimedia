/**
 *  @class   vipEditorForm
 *
 *  @brief   text editor form (interface)
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


#pragma once
#include ".\vipPKGFile.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace vipPS
{
	/// <summary>
	/// Riepilogo per vipEditorForm
	///
	/// AVVISO: se si modifica il nome della classe, sarà necessario modificare la
	///          proprietà "Nome file di risorse" relativa allo strumento di compilazione delle risorse gestite
	///          associato a tutti i file RESX da cui dipende la classe. In caso contrario,
	///          le finestre di progettazione non saranno in grado di interagire correttamente con le
	///          risorse localizzate associate al form.
	/// </summary>
	public __gc class vipEditorForm : public System::Windows::Forms::Form
	{
	public:
		vipEditorForm(void)
		{
			InitializeComponent();
			myFile = NULL;
		}

		vipEditorForm(vipPKGFile* f)
		{
			InitializeComponent();
			setFile(f);
		}

		void setFile(vipPKGFile* f)
		{
			myFile = f;
			if ( myFile!=NULL )
			 {
				this->Text = String::Concat(S"Editor: ", Path::GetFileName(f->FileOutput));

				tB_fileout->Text = myFile->FileOutput;
				tB_filetemplate->Text = myFile->FileTemplate;
				tB_descr->Text = myFile->Description;
			 }
			button3_Click(this, NULL);
		}
	private: System::Windows::Forms::Button *  button3;
	private: System::Windows::Forms::ToolBar *  toolBar1;
	private: System::Windows::Forms::Panel *  panel3;



	private: System::Windows::Forms::Panel *  panel2;
	private: System::Windows::Forms::RichTextBox *  rTbText;
	private: System::Windows::Forms::ImageList *  imageList1;
	private: System::Windows::Forms::TextBox *  tB_fileout;
	private: System::Windows::Forms::TextBox *  tB_filetemplate;
	private: System::Windows::Forms::Panel *  panel5;
	private: System::Windows::Forms::TextBox *  tB_descr;
	private: System::Windows::Forms::Panel *  panel_info;
	private: System::Windows::Forms::CheckBox *  cB_info;
	private: System::Windows::Forms::ToolBarButton *  tBB_new;
	private: System::Windows::Forms::ToolBarButton *  tBB_save;
	private: System::Windows::Forms::ToolBarButton *  tBB_sep1;
	private: System::Windows::Forms::ToolBarButton *  tBB_undo;
	private: System::Windows::Forms::ToolBarButton *  tBB_redo;
	private: System::Windows::Forms::ToolBarButton *  tBB_sep2;
	private: System::Windows::Forms::ToolBarButton *  tBB_copy;
	private: System::Windows::Forms::ToolBarButton *  tBB_cut;
	private: System::Windows::Forms::ToolBarButton *  tBB_paste;
	private: System::Windows::Forms::ToolBarButton *  tBB_sep3;
	private: System::Windows::Forms::ToolBarButton *  tBB_find;
	private: System::Windows::Forms::ToolBarButton *  tBB_replace;
	private: System::Windows::Forms::SaveFileDialog *  saveFileDialog1;















	vipPKGFile* myFile;

	protected:
		void Dispose(Boolean disposing)
		{
			if (disposing && components)
			{
				components->Dispose();
			}
			__super::Dispose(disposing);
		}


	private: System::Windows::Forms::Panel *  panel1;
	private: System::Windows::Forms::Button *  button2;
	private: System::Windows::Forms::Button *  button1;
	private: System::Windows::Forms::StatusBar *  statusBar1;
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
			System::Resources::ResourceManager *  resources = new System::Resources::ResourceManager(__typeof(vipPS::vipEditorForm));
			this->panel1 = new System::Windows::Forms::Panel();
			this->button3 = new System::Windows::Forms::Button();
			this->button2 = new System::Windows::Forms::Button();
			this->button1 = new System::Windows::Forms::Button();
			this->statusBar1 = new System::Windows::Forms::StatusBar();
			this->toolBar1 = new System::Windows::Forms::ToolBar();
			this->tBB_new = new System::Windows::Forms::ToolBarButton();
			this->tBB_save = new System::Windows::Forms::ToolBarButton();
			this->tBB_sep1 = new System::Windows::Forms::ToolBarButton();
			this->tBB_undo = new System::Windows::Forms::ToolBarButton();
			this->tBB_redo = new System::Windows::Forms::ToolBarButton();
			this->tBB_sep2 = new System::Windows::Forms::ToolBarButton();
			this->tBB_copy = new System::Windows::Forms::ToolBarButton();
			this->tBB_cut = new System::Windows::Forms::ToolBarButton();
			this->tBB_paste = new System::Windows::Forms::ToolBarButton();
			this->tBB_sep3 = new System::Windows::Forms::ToolBarButton();
			this->tBB_find = new System::Windows::Forms::ToolBarButton();
			this->tBB_replace = new System::Windows::Forms::ToolBarButton();
			this->imageList1 = new System::Windows::Forms::ImageList(this->components);
			this->panel3 = new System::Windows::Forms::Panel();
			this->tB_fileout = new System::Windows::Forms::TextBox();
			this->cB_info = new System::Windows::Forms::CheckBox();
			this->panel_info = new System::Windows::Forms::Panel();
			this->tB_descr = new System::Windows::Forms::TextBox();
			this->panel5 = new System::Windows::Forms::Panel();
			this->tB_filetemplate = new System::Windows::Forms::TextBox();
			this->panel2 = new System::Windows::Forms::Panel();
			this->rTbText = new System::Windows::Forms::RichTextBox();
			this->saveFileDialog1 = new System::Windows::Forms::SaveFileDialog();
			this->panel1->SuspendLayout();
			this->panel3->SuspendLayout();
			this->panel_info->SuspendLayout();
			this->panel2->SuspendLayout();
			this->SuspendLayout();
			//
			// panel1
			//
			this->panel1->Controls->Add(this->button3);
			this->panel1->Controls->Add(this->button2);
			this->panel1->Controls->Add(this->button1);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel1->Location = System::Drawing::Point(0, 472);
			this->panel1->Name = S"panel1";
			this->panel1->Size = System::Drawing::Size(720, 40);
			this->panel1->TabIndex = 11;
			//
			// button3
			//
			this->button3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button3->Location = System::Drawing::Point(8, 8);
			this->button3->Name = S"button3";
			this->button3->Size = System::Drawing::Size(120, 23);
			this->button3->TabIndex = 2;
			this->button3->Text = S"Revert to Cache";
			this->button3->Click += new System::EventHandler(this, button3_Click);
			//
			// button2
			//
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button2->Location = System::Drawing::Point(608, 8);
			this->button2->Name = S"button2";
			this->button2->Size = System::Drawing::Size(104, 23);
			this->button2->TabIndex = 1;
			this->button2->Text = S"Save to File";
			this->button2->Click += new System::EventHandler(this, button2_Click);
			//
			// button1
			//
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Location = System::Drawing::Point(480, 8);
			this->button1->Name = S"button1";
			this->button1->Size = System::Drawing::Size(104, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = S"Save to Cache";
			this->button1->Click += new System::EventHandler(this, button1_Click);
			//
			// statusBar1
			//
			this->statusBar1->Location = System::Drawing::Point(0, 512);
			this->statusBar1->Name = S"statusBar1";
			this->statusBar1->Size = System::Drawing::Size(720, 22);
			this->statusBar1->TabIndex = 10;
			//
			// toolBar1
			//
			this->toolBar1->Appearance = System::Windows::Forms::ToolBarAppearance::Flat;
			System::Windows::Forms::ToolBarButton* __mcTemp__1[] = new System::Windows::Forms::ToolBarButton*[12];
			__mcTemp__1[0] = this->tBB_new;
			__mcTemp__1[1] = this->tBB_save;
			__mcTemp__1[2] = this->tBB_sep1;
			__mcTemp__1[3] = this->tBB_undo;
			__mcTemp__1[4] = this->tBB_redo;
			__mcTemp__1[5] = this->tBB_sep2;
			__mcTemp__1[6] = this->tBB_copy;
			__mcTemp__1[7] = this->tBB_cut;
			__mcTemp__1[8] = this->tBB_paste;
			__mcTemp__1[9] = this->tBB_sep3;
			__mcTemp__1[10] = this->tBB_find;
			__mcTemp__1[11] = this->tBB_replace;
			this->toolBar1->Buttons->AddRange(__mcTemp__1);
			this->toolBar1->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->toolBar1->DropDownArrows = true;
			this->toolBar1->ImageList = this->imageList1;
			this->toolBar1->Location = System::Drawing::Point(0, 444);
			this->toolBar1->Name = S"toolBar1";
			this->toolBar1->ShowToolTips = true;
			this->toolBar1->Size = System::Drawing::Size(720, 28);
			this->toolBar1->TabIndex = 14;
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
			// tBB_sep1
			//
			this->tBB_sep1->Style = System::Windows::Forms::ToolBarButtonStyle::Separator;
			//
			// tBB_undo
			//
			this->tBB_undo->ImageIndex = 2;
			//
			// tBB_redo
			//
			this->tBB_redo->ImageIndex = 3;
			//
			// tBB_sep2
			//
			this->tBB_sep2->Style = System::Windows::Forms::ToolBarButtonStyle::Separator;
			//
			// tBB_copy
			//
			this->tBB_copy->ImageIndex = 5;
			//
			// tBB_cut
			//
			this->tBB_cut->ImageIndex = 6;
			//
			// tBB_paste
			//
			this->tBB_paste->ImageIndex = 7;
			//
			// tBB_sep3
			//
			this->tBB_sep3->Style = System::Windows::Forms::ToolBarButtonStyle::Separator;
			//
			// tBB_find
			//
			this->tBB_find->ImageIndex = 8;
			this->tBB_find->Visible = false;
			//
			// tBB_replace
			//
			this->tBB_replace->ImageIndex = 9;
			this->tBB_replace->Visible = false;
			//
			// imageList1
			//
			this->imageList1->ImageSize = System::Drawing::Size(16, 16);
			this->imageList1->ImageStream = (__try_cast<System::Windows::Forms::ImageListStreamer *  >(resources->GetObject(S"imageList1.ImageStream")));
			this->imageList1->TransparentColor = System::Drawing::Color::Transparent;
			//
			// panel3
			//
			this->panel3->Controls->Add(this->tB_fileout);
			this->panel3->Controls->Add(this->cB_info);
			this->panel3->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel3->DockPadding->All = 10;
			this->panel3->Location = System::Drawing::Point(0, 0);
			this->panel3->Name = S"panel3";
			this->panel3->Size = System::Drawing::Size(720, 40);
			this->panel3->TabIndex = 15;
			//
			// tB_fileout
			//
			this->tB_fileout->BackColor = System::Drawing::Color::FromArgb((System::Byte)235, (System::Byte)235, (System::Byte)255);
			this->tB_fileout->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->tB_fileout->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tB_fileout->Location = System::Drawing::Point(10, 10);
			this->tB_fileout->Name = S"tB_fileout";
			this->tB_fileout->ReadOnly = true;
			this->tB_fileout->Size = System::Drawing::Size(644, 22);
			this->tB_fileout->TabIndex = 2;
			this->tB_fileout->Text = S"";
			//
			// cB_info
			//
			this->cB_info->Dock = System::Windows::Forms::DockStyle::Right;
			this->cB_info->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->cB_info->Location = System::Drawing::Point(654, 10);
			this->cB_info->Name = S"cB_info";
			this->cB_info->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->cB_info->Size = System::Drawing::Size(56, 20);
			this->cB_info->TabIndex = 1;
			this->cB_info->Text = S"more";
			this->cB_info->CheckedChanged += new System::EventHandler(this, cB_info_CheckedChanged);
			//
			// panel_info
			//
			this->panel_info->Controls->Add(this->tB_descr);
			this->panel_info->Controls->Add(this->panel5);
			this->panel_info->Controls->Add(this->tB_filetemplate);
			this->panel_info->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel_info->DockPadding->All = 10;
			this->panel_info->Location = System::Drawing::Point(0, 40);
			this->panel_info->Name = S"panel_info";
			this->panel_info->Size = System::Drawing::Size(720, 100);
			this->panel_info->TabIndex = 16;
			this->panel_info->Visible = false;
			//
			// tB_descr
			//
			this->tB_descr->BackColor = System::Drawing::Color::FromArgb((System::Byte)235, (System::Byte)235, (System::Byte)255);
			this->tB_descr->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->tB_descr->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tB_descr->Location = System::Drawing::Point(10, 40);
			this->tB_descr->Multiline = true;
			this->tB_descr->Name = S"tB_descr";
			this->tB_descr->ReadOnly = true;
			this->tB_descr->Size = System::Drawing::Size(700, 50);
			this->tB_descr->TabIndex = 5;
			this->tB_descr->Text = S"";
			//
			// panel5
			//
			this->panel5->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel5->Location = System::Drawing::Point(10, 32);
			this->panel5->Name = S"panel5";
			this->panel5->Size = System::Drawing::Size(700, 8);
			this->panel5->TabIndex = 4;
			//
			// tB_filetemplate
			//
			this->tB_filetemplate->BackColor = System::Drawing::Color::FromArgb((System::Byte)235, (System::Byte)235, (System::Byte)255);
			this->tB_filetemplate->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->tB_filetemplate->Dock = System::Windows::Forms::DockStyle::Top;
			this->tB_filetemplate->Location = System::Drawing::Point(10, 10);
			this->tB_filetemplate->Name = S"tB_filetemplate";
			this->tB_filetemplate->ReadOnly = true;
			this->tB_filetemplate->Size = System::Drawing::Size(700, 22);
			this->tB_filetemplate->TabIndex = 3;
			this->tB_filetemplate->Text = S"";
			//
			// panel2
			//
			this->panel2->Controls->Add(this->rTbText);
			this->panel2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel2->DockPadding->All = 10;
			this->panel2->Location = System::Drawing::Point(0, 140);
			this->panel2->Name = S"panel2";
			this->panel2->Size = System::Drawing::Size(720, 304);
			this->panel2->TabIndex = 17;
			//
			// rTbText
			//
			this->rTbText->BackColor = System::Drawing::Color::FromArgb((System::Byte)232, (System::Byte)255, (System::Byte)255);
			this->rTbText->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->rTbText->Dock = System::Windows::Forms::DockStyle::Fill;
			this->rTbText->Font = new System::Drawing::Font(S"Courier New", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (System::Byte)0);
			this->rTbText->Location = System::Drawing::Point(10, 10);
			this->rTbText->Name = S"rTbText";
			this->rTbText->Size = System::Drawing::Size(700, 284);
			this->rTbText->TabIndex = 1;
			this->rTbText->Text = S"";
			this->rTbText->WordWrap = false;
			this->rTbText->TextChanged += new System::EventHandler(this, rTbText_TextChanged);
			//
			// vipEditorForm
			//
			this->AutoScaleBaseSize = System::Drawing::Size(6, 15);
			this->ClientSize = System::Drawing::Size(720, 534);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->panel_info);
			this->Controls->Add(this->panel3);
			this->Controls->Add(this->toolBar1);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->statusBar1);
			this->Name = S"vipEditorForm";
			this->Text = S"vipEditorForm";
			this->Closed += new System::EventHandler(this, vipEditorForm_Closed);
			this->panel1->ResumeLayout(false);
			this->panel3->ResumeLayout(false);
			this->panel_info->ResumeLayout(false);
			this->panel2->ResumeLayout(false);
			this->ResumeLayout(false);

		}
//
	private: System::Void button2_Click(System::Object *  sender, System::EventArgs *  e)
			 {
				if (myFile == NULL)
					 return;

				button1_Click(sender, e);

				myFile->SaveOutputFile();

				this->Text = String::Concat(S"Editor: ", Path::GetFileName(myFile->FileOutput));
			 }

private: System::Void button3_Click(System::Object *  sender, System::EventArgs *  e)
		 {
				if (myFile == NULL)
					 return;

				rTbText->Clear();
				rTbText->AppendText( myFile->getData() );
				this->Text = String::Concat(S"Editor: ", Path::GetFileName(myFile->FileOutput));
		 }

private: System::Void button1_Click(System::Object *  sender, System::EventArgs *  e)
		 {
				if (myFile == NULL)
					 return;

				myFile->SetText(rTbText->Text);
				this->Text = String::Concat(S"Editor: ", Path::GetFileName(myFile->FileOutput), S" [Cached]");

		 }

private: System::Void vipEditorForm_Closed(System::Object *  sender, System::EventArgs *  e)
		 {
				if (myFile == NULL)
					 return;
				myFile->myForm = NULL;
		 }



private: System::Void cB_info_CheckedChanged(System::Object *  sender, System::EventArgs *  e)
		 {
			 panel_info->Visible = cB_info->Checked;
		 }

private: System::Void rTbText_TextChanged(System::Object *  sender, System::EventArgs *  e)
		 {
			this->Text = String::Concat(S"Editor: ", Path::GetFileName(myFile->FileOutput), S"*");
		 }

private: System::Void toolBar1_ButtonClick(System::Object *  sender, System::Windows::Forms::ToolBarButtonClickEventArgs *  e)
		 {
			 if (e->Button == tBB_new)
			  {

			  }
			 else if (e->Button == tBB_save)
			  {

			  }
			 else if (e->Button == tBB_undo)
			  {
				  rTbText->Undo();
			  }
			 else if (e->Button == tBB_redo)
			  {
				  rTbText->Redo();
			  }
			 else if (e->Button == tBB_copy)
			  {
				  rTbText->Copy();
			  }
			 else if (e->Button == tBB_cut)
			  {
				  rTbText->Cut();
			  }
			 else if (e->Button == tBB_paste)
			  {
				  rTbText->Paste();
			  }
			 else if (e->Button == tBB_find)
			  {
//				  rTbText->Paste();
			  }
			 else if (e->Button == tBB_replace)
			  {

			  }


		 }

};
}
