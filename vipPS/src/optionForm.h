/**
 *  @class   optionForm
 *
 *  @brief   options form (interface)
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

#include "./vipDirectories.h"


using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace vipPS
{
	/// <summary>
	/// Riepilogo per optionForm
	///
	/// AVVISO: se si modifica il nome della classe, sarà necessario modificare la
	///          proprietà "Nome file di risorse" relativa allo strumento di compilazione delle risorse gestite
	///          associato a tutti i file RESX da cui dipende la classe. In caso contrario,
	///          le finestre di progettazione non saranno in grado di interagire correttamente con le
	///          risorse localizzate associate al form.
	/// </summary>
	public __gc class optionForm : public System::Windows::Forms::Form
	{
	public:
		optionForm(void)
		{
			InitializeComponent();
		}
		void SetDirectories();

	protected:
		void Dispose(Boolean disposing)
		{
			if (disposing && components)
			{
				components->Dispose();
			}
			__super::Dispose(disposing);
		}

	private: vipDirectories* dirs;
	private: System::Windows::Forms::Panel *  panel1;
	private: System::Windows::Forms::TabControl *  tabControl1;
	private: System::Windows::Forms::TabPage *  tabPage1;
	private: System::Windows::Forms::TabPage *  tabPage2;
	private: System::Windows::Forms::Button *  button1;
	private: System::Windows::Forms::Button *  button2;
	private: System::Windows::Forms::TabPage *  tabPage3;





	private: System::Windows::Forms::TabPage *  tabPage4;
	private: System::Windows::Forms::ColorDialog *  colorDialog1;
	private: System::Windows::Forms::FontDialog *  fontDialog1;
	private: System::Windows::Forms::FolderBrowserDialog *  folderBrowserDialog1;
	private: System::Windows::Forms::Panel *  panel3;
	private: System::Windows::Forms::Button *  button4;
	private: System::Windows::Forms::Button *  button3;

	private: System::Windows::Forms::Panel *  panel2;
	private: System::Windows::Forms::ListBox *  lB_dirs;
	private: System::Windows::Forms::TextBox *  tB_edit;

	private:
		/// <summary>
		/// Variabile di progettazione necessaria.
		/// </summary>
		System::ComponentModel::Container* components;

		/// <summary>
		/// Metodo necessario per il supporto della finestra di progettazione. Non modificare
		/// il contenuto del metodo con l'editor di codice.
		/// </summary>
		void InitializeComponent(void)
		{
			this->panel1 = new System::Windows::Forms::Panel();
			this->button2 = new System::Windows::Forms::Button();
			this->button1 = new System::Windows::Forms::Button();
			this->tabControl1 = new System::Windows::Forms::TabControl();
			this->tabPage1 = new System::Windows::Forms::TabPage();
			this->tabPage2 = new System::Windows::Forms::TabPage();
			this->panel2 = new System::Windows::Forms::Panel();
			this->tB_edit = new System::Windows::Forms::TextBox();
			this->panel3 = new System::Windows::Forms::Panel();
			this->button4 = new System::Windows::Forms::Button();
			this->button3 = new System::Windows::Forms::Button();
			this->lB_dirs = new System::Windows::Forms::ListBox();
			this->tabPage3 = new System::Windows::Forms::TabPage();
			this->tabPage4 = new System::Windows::Forms::TabPage();
			this->colorDialog1 = new System::Windows::Forms::ColorDialog();
			this->fontDialog1 = new System::Windows::Forms::FontDialog();
			this->folderBrowserDialog1 = new System::Windows::Forms::FolderBrowserDialog();
			this->panel1->SuspendLayout();
			this->tabControl1->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->panel3->SuspendLayout();
			this->SuspendLayout();
			//
			// panel1
			//
			this->panel1->Controls->Add(this->button2);
			this->panel1->Controls->Add(this->button1);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel1->Location = System::Drawing::Point(0, 334);
			this->panel1->Name = S"panel1";
			this->panel1->Size = System::Drawing::Size(568, 40);
			this->panel1->TabIndex = 0;
			//
			// button2
			//
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button2->Location = System::Drawing::Point(488, 8);
			this->button2->Name = S"button2";
			this->button2->TabIndex = 1;
			this->button2->Text = S"&Close";
			this->button2->Click += new System::EventHandler(this, button2_Click);
			//
			// button1
			//
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Location = System::Drawing::Point(400, 8);
			this->button1->Name = S"button1";
			this->button1->TabIndex = 0;
			this->button1->Text = S"&Apply";
			this->button1->Click += new System::EventHandler(this, button1_Click);
			//
			// tabControl1
			//
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Controls->Add(this->tabPage4);
			this->tabControl1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tabControl1->Location = System::Drawing::Point(0, 0);
			this->tabControl1->Name = S"tabControl1";
			this->tabControl1->Padding = System::Drawing::Point(12, 3);
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(568, 334);
			this->tabControl1->TabIndex = 1;
			//
			// tabPage1
			//
			this->tabPage1->Location = System::Drawing::Point(4, 25);
			this->tabPage1->Name = S"tabPage1";
			this->tabPage1->Size = System::Drawing::Size(560, 305);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = S"General";
			//
			// tabPage2
			//
			this->tabPage2->Controls->Add(this->panel2);
			this->tabPage2->Controls->Add(this->tB_edit);
			this->tabPage2->Controls->Add(this->panel3);
			this->tabPage2->Controls->Add(this->lB_dirs);
			this->tabPage2->DockPadding->All = 10;
			this->tabPage2->Location = System::Drawing::Point(4, 25);
			this->tabPage2->Name = S"tabPage2";
			this->tabPage2->Size = System::Drawing::Size(560, 305);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = S"Directories";
			//
			// panel2
			//
			this->panel2->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel2->Location = System::Drawing::Point(10, 205);
			this->panel2->Name = S"panel2";
			this->panel2->Size = System::Drawing::Size(540, 12);
			this->panel2->TabIndex = 8;
			//
			// tB_edit
			//
			this->tB_edit->BackColor = System::Drawing::Color::FromArgb((System::Byte)235, (System::Byte)235, (System::Byte)255);
			this->tB_edit->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->tB_edit->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->tB_edit->Location = System::Drawing::Point(10, 217);
			this->tB_edit->Name = S"tB_edit";
			this->tB_edit->Size = System::Drawing::Size(540, 22);
			this->tB_edit->TabIndex = 7;
			this->tB_edit->Text = S"";
			//
			// panel3
			//
			this->panel3->Controls->Add(this->button4);
			this->panel3->Controls->Add(this->button3);
			this->panel3->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel3->Location = System::Drawing::Point(10, 239);
			this->panel3->Name = S"panel3";
			this->panel3->Size = System::Drawing::Size(540, 56);
			this->panel3->TabIndex = 6;
			//
			// button4
			//
			this->button4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button4->Location = System::Drawing::Point(96, 8);
			this->button4->Name = S"button4";
			this->button4->TabIndex = 7;
			this->button4->Text = S"Browse..";
			//
			// button3
			//
			this->button3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button3->Location = System::Drawing::Point(8, 8);
			this->button3->Name = S"button3";
			this->button3->TabIndex = 6;
			this->button3->Text = S"Set";
			this->button3->Click += new System::EventHandler(this, button3_Click);
			//
			// lB_dirs
			//
			this->lB_dirs->BackColor = System::Drawing::Color::FromArgb((System::Byte)235, (System::Byte)235, (System::Byte)255);
			this->lB_dirs->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lB_dirs->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lB_dirs->Font = new System::Drawing::Font(S"Courier New", 7.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (System::Byte)0);
			this->lB_dirs->ItemHeight = 16;
			this->lB_dirs->Location = System::Drawing::Point(10, 10);
			this->lB_dirs->Name = S"lB_dirs";
			this->lB_dirs->Size = System::Drawing::Size(540, 285);
			this->lB_dirs->TabIndex = 1;
			this->lB_dirs->SelectedIndexChanged += new System::EventHandler(this, lB_dirs_SelectedIndexChanged);
			//
			// tabPage3
			//
			this->tabPage3->DockPadding->All = 10;
			this->tabPage3->Location = System::Drawing::Point(4, 25);
			this->tabPage3->Name = S"tabPage3";
			this->tabPage3->Size = System::Drawing::Size(560, 305);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = S"LayOut";
			//
			// tabPage4
			//
			this->tabPage4->Location = System::Drawing::Point(4, 25);
			this->tabPage4->Name = S"tabPage4";
			this->tabPage4->Size = System::Drawing::Size(560, 305);
			this->tabPage4->TabIndex = 3;
			this->tabPage4->Text = S"Code Editor";
			//
			// optionForm
			//
			this->AutoScaleBaseSize = System::Drawing::Size(6, 15);
			this->ClientSize = System::Drawing::Size(568, 374);
			this->Controls->Add(this->tabControl1);
			this->Controls->Add(this->panel1);
			this->Name = S"optionForm";
			this->Text = S"Preferences..";
			this->Closing += new System::ComponentModel::CancelEventHandler(this, optionForm_Closing);
			this->Load += new System::EventHandler(this, optionForm_Load);
			this->panel1->ResumeLayout(false);
			this->tabControl1->ResumeLayout(false);
			this->tabPage2->ResumeLayout(false);
			this->panel3->ResumeLayout(false);
			this->ResumeLayout(false);

		}
	private: System::Void button2_Click(System::Object *  sender, System::EventArgs *  e)
			 {
				 button1_Click(sender, e);
				 this->Close();
			 }

private: System::Void button1_Click(System::Object *  sender, System::EventArgs *  e)
		 {
		 }

private: System::Void lB_dirs_SelectedIndexChanged(System::Object *  sender, System::EventArgs *  e)
		 {
			 tB_edit->Text = lB_dirs->SelectedItem->ToString()->Substring( lB_dirs->SelectedItem->ToString()->LastIndexOf(S"\t")+1 );
		 }

private: System::Void button3_Click(System::Object *  sender, System::EventArgs *  e);


private: System::Void optionForm_Load(System::Object *  sender, System::EventArgs *  e)
		 {
			SetDirectories();
		 }

private: System::Void optionForm_Closing(System::Object *  sender, System::ComponentModel::CancelEventArgs *  e)
		 {
			e->Cancel = true;
			this->Visible = false;
		 }

};
}
