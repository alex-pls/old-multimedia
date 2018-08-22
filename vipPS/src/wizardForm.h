/**
 *  @class   wizardForm
 *
 *  @brief   package generation wizard form (interface)
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
#include ".\prjManForm.h"
#include ".\vipDirectories.h"


using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace vipPS
{
	/// <summary>
	/// Riepilogo per wizardForm
	///
	/// AVVISO: se si modifica il nome della classe, sarà necessario modificare la
	///          proprietà "Nome file di risorse" relativa allo strumento di compilazione delle risorse gestite
	///          associato a tutti i file RESX da cui dipende la classe. In caso contrario,
	///          le finestre di progettazione non saranno in grado di interagire correttamente con le
	///          risorse localizzate associate al form.
	/// </summary>
	public __gc class wizardForm : public System::Windows::Forms::Form
	{
	public:
		wizardForm(void)
		{
			InitializeComponent();
		}
		void Reset(void);

	protected:
		void Dispose(Boolean disposing)
		{
			if (disposing && components)
			{
				components->Dispose();
			}
			__super::Dispose(disposing);
		}


	private: String* names[];
	private: vipDirectories* dirs;
	private: Array* vpp;

	private: System::Windows::Forms::Panel *  panel1;
	private: System::Windows::Forms::Panel *  panel2;
	private: System::Windows::Forms::TabPage *  tabPage1;
	private: System::Windows::Forms::TabPage *  tabPage2;
	private: System::Windows::Forms::TabPage *  tabPage3;
	private: System::Windows::Forms::TabPage *  tabPage4;
	private: System::Windows::Forms::Button *  button1;
	private: System::Windows::Forms::Button *  button2;
	private: System::Windows::Forms::Button *  button3;
	private: System::Windows::Forms::TabControl *  selPage;
	private: System::Windows::Forms::Label *  label3;
	private: System::Windows::Forms::Label *  label4;
	private: System::Windows::Forms::Label *  label5;
	private: System::Windows::Forms::Label *  label1;
	private: System::Windows::Forms::Label *  label6;
	private: System::Windows::Forms::Label *  label2;
	private: System::Windows::Forms::TextBox *  tB_authors;
	private: System::Windows::Forms::TextBox *  tB_name;
	private: System::Windows::Forms::ListBox *  lB_type;
	private: System::Windows::Forms::CheckBox *  cB_funce;
	private: System::Windows::Forms::CheckBox *  cB_funcv;
	private: System::Windows::Forms::TextBox *  tB_version;
	private: System::Windows::Forms::Label *  label7;
	private: System::Windows::Forms::CheckBox *  cB_prj_16;
	private: System::Windows::Forms::CheckBox *  cB_prj_4;
	private: System::Windows::Forms::CheckBox *  cB_prj_2;
	private: System::Windows::Forms::CheckBox *  cB_prj_8;
	private: System::Windows::Forms::CheckBox *  cB_prj_1;
	private: System::Windows::Forms::CheckBox *  cB_docs_f;
	private: System::Windows::Forms::CheckBox *  cB_docs_v;
	private: System::Windows::Forms::Label *  label8;
	private: System::Windows::Forms::Label *  label9;

	private: System::Windows::Forms::CheckBox *  checkBox2;
	private: System::Windows::Forms::CheckBox *  checkBox3;
	private: System::Windows::Forms::TextBox *  tB_dir;
	private: System::Windows::Forms::Label *  label10;

	private: System::Windows::Forms::Label *  label11;
	private: System::Windows::Forms::CheckBox *  cB_prj_32;
	private: System::Windows::Forms::Label *  lB_dir;
	private: System::Windows::Forms::HelpProvider *  helpProvider1;
	private: System::Windows::Forms::ToolTip *  toolTip1;
	private: System::Windows::Forms::CheckBox *  cB_relative;
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
			this->panel1 = new System::Windows::Forms::Panel();
			this->panel2 = new System::Windows::Forms::Panel();
			this->button3 = new System::Windows::Forms::Button();
			this->button2 = new System::Windows::Forms::Button();
			this->button1 = new System::Windows::Forms::Button();
			this->selPage = new System::Windows::Forms::TabControl();
			this->tabPage1 = new System::Windows::Forms::TabPage();
			this->tB_version = new System::Windows::Forms::TextBox();
			this->label7 = new System::Windows::Forms::Label();
			this->label5 = new System::Windows::Forms::Label();
			this->label4 = new System::Windows::Forms::Label();
			this->label3 = new System::Windows::Forms::Label();
			this->tB_authors = new System::Windows::Forms::TextBox();
			this->tB_name = new System::Windows::Forms::TextBox();
			this->lB_type = new System::Windows::Forms::ListBox();
			this->tabPage3 = new System::Windows::Forms::TabPage();
			this->cB_prj_32 = new System::Windows::Forms::CheckBox();
			this->label11 = new System::Windows::Forms::Label();
			this->cB_prj_16 = new System::Windows::Forms::CheckBox();
			this->label6 = new System::Windows::Forms::Label();
			this->label1 = new System::Windows::Forms::Label();
			this->cB_prj_4 = new System::Windows::Forms::CheckBox();
			this->cB_prj_2 = new System::Windows::Forms::CheckBox();
			this->cB_prj_8 = new System::Windows::Forms::CheckBox();
			this->cB_prj_1 = new System::Windows::Forms::CheckBox();
			this->tabPage2 = new System::Windows::Forms::TabPage();
			this->label8 = new System::Windows::Forms::Label();
			this->cB_docs_f = new System::Windows::Forms::CheckBox();
			this->cB_docs_v = new System::Windows::Forms::CheckBox();
			this->cB_funce = new System::Windows::Forms::CheckBox();
			this->label2 = new System::Windows::Forms::Label();
			this->cB_funcv = new System::Windows::Forms::CheckBox();
			this->tabPage4 = new System::Windows::Forms::TabPage();
			this->lB_dir = new System::Windows::Forms::Label();
			this->tB_dir = new System::Windows::Forms::TextBox();
			this->label10 = new System::Windows::Forms::Label();
			this->checkBox3 = new System::Windows::Forms::CheckBox();
			this->checkBox2 = new System::Windows::Forms::CheckBox();
			this->label9 = new System::Windows::Forms::Label();
			this->cB_relative = new System::Windows::Forms::CheckBox();
			this->helpProvider1 = new System::Windows::Forms::HelpProvider();
			this->toolTip1 = new System::Windows::Forms::ToolTip(this->components);
			this->panel2->SuspendLayout();
			this->selPage->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->tabPage3->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->tabPage4->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->Dock = System::Windows::Forms::DockStyle::Left;
			this->panel1->Location = System::Drawing::Point(0, 0);
			this->panel1->Name = S"panel1";
			this->panel1->Size = System::Drawing::Size(8, 350);
			this->panel1->TabIndex = 0;
			// 
			// panel2
			// 
			this->panel2->Controls->Add(this->button3);
			this->panel2->Controls->Add(this->button2);
			this->panel2->Controls->Add(this->button1);
			this->panel2->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel2->Location = System::Drawing::Point(8, 310);
			this->panel2->Name = S"panel2";
			this->panel2->Size = System::Drawing::Size(472, 40);
			this->panel2->TabIndex = 1;
			// 
			// button3
			// 
			this->button3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button3->Location = System::Drawing::Point(16, 8);
			this->button3->Name = S"button3";
			this->button3->Size = System::Drawing::Size(96, 23);
			this->button3->TabIndex = 2;
			this->button3->Text = S"<< Previous";
			this->button3->Click += new System::EventHandler(this, button3_Click);
			// 
			// button2
			// 
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button2->Location = System::Drawing::Point(376, 8);
			this->button2->Name = S"button2";
			this->button2->TabIndex = 1;
			this->button2->Text = S"Generate";
			this->button2->Click += new System::EventHandler(this, button2_Click);
			// 
			// button1
			// 
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Location = System::Drawing::Point(120, 8);
			this->button1->Name = S"button1";
			this->button1->Size = System::Drawing::Size(96, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = S"Next >>";
			this->button1->Click += new System::EventHandler(this, button1_Click);
			// 
			// selPage
			// 
			this->selPage->Controls->Add(this->tabPage1);
			this->selPage->Controls->Add(this->tabPage3);
			this->selPage->Controls->Add(this->tabPage2);
			this->selPage->Controls->Add(this->tabPage4);
			this->selPage->Dock = System::Windows::Forms::DockStyle::Fill;
			this->selPage->Location = System::Drawing::Point(8, 0);
			this->selPage->Name = S"selPage";
			this->selPage->Padding = System::Drawing::Point(16, 3);
			this->selPage->SelectedIndex = 0;
			this->selPage->Size = System::Drawing::Size(472, 310);
			this->selPage->TabIndex = 2;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->tB_version);
			this->tabPage1->Controls->Add(this->label7);
			this->tabPage1->Controls->Add(this->label5);
			this->tabPage1->Controls->Add(this->label4);
			this->tabPage1->Controls->Add(this->label3);
			this->tabPage1->Controls->Add(this->tB_authors);
			this->tabPage1->Controls->Add(this->tB_name);
			this->tabPage1->Controls->Add(this->lB_type);
			this->tabPage1->Location = System::Drawing::Point(4, 25);
			this->tabPage1->Name = S"tabPage1";
			this->tabPage1->Size = System::Drawing::Size(464, 281);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = S"General";
			// 
			// tB_version
			// 
			this->tB_version->BackColor = System::Drawing::Color::FromArgb((System::Byte)235, (System::Byte)235, (System::Byte)255);
			this->tB_version->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->tB_version->Location = System::Drawing::Point(384, 176);
			this->tB_version->Name = S"tB_version";
			this->tB_version->Size = System::Drawing::Size(64, 22);
			this->tB_version->TabIndex = 9;
			this->tB_version->Text = S"1.0";
			// 
			// label7
			// 
			this->label7->Font = new System::Drawing::Font(S"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point, (System::Byte)0);
			this->label7->Location = System::Drawing::Point(328, 176);
			this->label7->Name = S"label7";
			this->label7->TabIndex = 10;
			this->label7->Text = S"version";
			// 
			// label5
			// 
			this->label5->Font = new System::Drawing::Font(S"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, (System::Byte)0);
			this->label5->Location = System::Drawing::Point(16, 216);
			this->label5->Name = S"label5";
			this->label5->Size = System::Drawing::Size(432, 23);
			this->label5->TabIndex = 7;
			this->label5->Text = S"Type here authors\' Name:";
			// 
			// label4
			// 
			this->label4->Font = new System::Drawing::Font(S"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, (System::Byte)0);
			this->label4->Location = System::Drawing::Point(16, 152);
			this->label4->Name = S"label4";
			this->label4->Size = System::Drawing::Size(432, 23);
			this->label4->TabIndex = 6;
			this->label4->Text = S"Type here your component\'s Name:";
			// 
			// label3
			// 
			this->label3->Font = new System::Drawing::Font(S"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, (System::Byte)0);
			this->label3->Location = System::Drawing::Point(16, 16);
			this->label3->Name = S"label3";
			this->label3->Size = System::Drawing::Size(432, 23);
			this->label3->TabIndex = 5;
			this->label3->Text = S"Select the type of component you are going to develope:";
			// 
			// tB_authors
			// 
			this->tB_authors->BackColor = System::Drawing::Color::FromArgb((System::Byte)235, (System::Byte)235, (System::Byte)255);
			this->tB_authors->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->tB_authors->Location = System::Drawing::Point(32, 240);
			this->tB_authors->Name = S"tB_authors";
			this->tB_authors->Size = System::Drawing::Size(416, 22);
			this->tB_authors->TabIndex = 2;
			this->tB_authors->Text = S"";
			// 
			// tB_name
			// 
			this->tB_name->BackColor = System::Drawing::Color::FromArgb((System::Byte)255, (System::Byte)192, (System::Byte)192);
			this->tB_name->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->tB_name->Location = System::Drawing::Point(32, 176);
			this->tB_name->Name = S"tB_name";
			this->tB_name->Size = System::Drawing::Size(288, 22);
			this->tB_name->TabIndex = 1;
			this->tB_name->Text = S"";
			this->tB_name->TextChanged += new System::EventHandler(this, tB_name_TextChanged);
			// 
			// lB_type
			// 
			this->lB_type->BackColor = System::Drawing::Color::FromArgb((System::Byte)235, (System::Byte)235, (System::Byte)255);
			this->lB_type->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->helpProvider1->SetHelpString(this->lB_type, S"Select template of component (VIPLIB base interface)");
			this->lB_type->ItemHeight = 16;
			this->lB_type->Location = System::Drawing::Point(32, 40);
			this->lB_type->Name = S"lB_type";
			this->helpProvider1->SetShowHelp(this->lB_type, true);
			this->lB_type->Size = System::Drawing::Size(416, 98);
			this->lB_type->TabIndex = 0;
			this->lB_type->SelectedIndexChanged += new System::EventHandler(this, lB_type_SelectedIndexChanged);
			// 
			// tabPage3
			// 
			this->tabPage3->Controls->Add(this->cB_prj_32);
			this->tabPage3->Controls->Add(this->label11);
			this->tabPage3->Controls->Add(this->cB_prj_16);
			this->tabPage3->Controls->Add(this->label6);
			this->tabPage3->Controls->Add(this->label1);
			this->tabPage3->Controls->Add(this->cB_prj_4);
			this->tabPage3->Controls->Add(this->cB_prj_2);
			this->tabPage3->Controls->Add(this->cB_prj_8);
			this->tabPage3->Controls->Add(this->cB_prj_1);
			this->tabPage3->Location = System::Drawing::Point(4, 25);
			this->tabPage3->Name = S"tabPage3";
			this->tabPage3->Size = System::Drawing::Size(464, 281);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = S"Projects";
			// 
			// cB_prj_32
			// 
			this->cB_prj_32->Checked = true;
			this->cB_prj_32->CheckState = System::Windows::Forms::CheckState::Checked;
			this->cB_prj_32->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->cB_prj_32->Location = System::Drawing::Point(32, 240);
			this->cB_prj_32->Name = S"cB_prj_32";
			this->cB_prj_32->Size = System::Drawing::Size(416, 24);
			this->cB_prj_32->TabIndex = 15;
			this->cB_prj_32->Text = S"Yes, create default Readme and License files";
			// 
			// label11
			// 
			this->label11->Font = new System::Drawing::Font(S"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, (System::Byte)0);
			this->label11->Location = System::Drawing::Point(16, 216);
			this->label11->Name = S"label11";
			this->label11->Size = System::Drawing::Size(432, 23);
			this->label11->TabIndex = 14;
			this->label11->Text = S"Do you want me to add an \"Informations project\"\?";
			// 
			// cB_prj_16
			// 
			this->cB_prj_16->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->cB_prj_16->Location = System::Drawing::Point(32, 176);
			this->cB_prj_16->Name = S"cB_prj_16";
			this->cB_prj_16->Size = System::Drawing::Size(416, 24);
			this->cB_prj_16->TabIndex = 13;
			this->cB_prj_16->Text = S"Yes, create default project (only VC6)";
			// 
			// label6
			// 
			this->label6->Font = new System::Drawing::Font(S"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, (System::Byte)0);
			this->label6->Location = System::Drawing::Point(16, 152);
			this->label6->Name = S"label6";
			this->label6->Size = System::Drawing::Size(432, 23);
			this->label6->TabIndex = 12;
			this->label6->Text = S"Are you going to build it as WorkShop plugin\?";
			// 
			// label1
			// 
			this->label1->Font = new System::Drawing::Font(S"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, (System::Byte)0);
			this->label1->Location = System::Drawing::Point(16, 16);
			this->label1->Name = S"label1";
			this->label1->Size = System::Drawing::Size(432, 23);
			this->label1->TabIndex = 10;
			this->label1->Text = S"Which Enviroment(s) are you going to use\?";
			// 
			// cB_prj_4
			// 
			this->cB_prj_4->Checked = true;
			this->cB_prj_4->CheckState = System::Windows::Forms::CheckState::Checked;
			this->cB_prj_4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->cB_prj_4->Location = System::Drawing::Point(32, 112);
			this->cB_prj_4->Name = S"cB_prj_4";
			this->cB_prj_4->Size = System::Drawing::Size(416, 24);
			this->cB_prj_4->TabIndex = 9;
			this->cB_prj_4->Text = S"Visual Studio 7.0 (.NET)";
			// 
			// cB_prj_2
			// 
			this->cB_prj_2->Checked = true;
			this->cB_prj_2->CheckState = System::Windows::Forms::CheckState::Checked;
			this->cB_prj_2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->cB_prj_2->Location = System::Drawing::Point(32, 88);
			this->cB_prj_2->Name = S"cB_prj_2";
			this->cB_prj_2->Size = System::Drawing::Size(416, 24);
			this->cB_prj_2->TabIndex = 8;
			this->cB_prj_2->Text = S"Visual Studio 6.0";
			// 
			// cB_prj_8
			// 
			this->cB_prj_8->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->cB_prj_8->Location = System::Drawing::Point(32, 64);
			this->cB_prj_8->Name = S"cB_prj_8";
			this->cB_prj_8->Size = System::Drawing::Size(416, 24);
			this->cB_prj_8->TabIndex = 7;
			this->cB_prj_8->Text = S"Borland C++ Builder 6.0";
			// 
			// cB_prj_1
			// 
			this->cB_prj_1->Checked = true;
			this->cB_prj_1->CheckState = System::Windows::Forms::CheckState::Checked;
			this->cB_prj_1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->cB_prj_1->Location = System::Drawing::Point(32, 40);
			this->cB_prj_1->Name = S"cB_prj_1";
			this->cB_prj_1->Size = System::Drawing::Size(416, 24);
			this->cB_prj_1->TabIndex = 6;
			this->cB_prj_1->Text = S"*NIX Makefile";
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->label8);
			this->tabPage2->Controls->Add(this->cB_docs_f);
			this->tabPage2->Controls->Add(this->cB_docs_v);
			this->tabPage2->Controls->Add(this->cB_funce);
			this->tabPage2->Controls->Add(this->label2);
			this->tabPage2->Controls->Add(this->cB_funcv);
			this->tabPage2->Location = System::Drawing::Point(4, 25);
			this->tabPage2->Name = S"tabPage2";
			this->tabPage2->Size = System::Drawing::Size(464, 281);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = S"Settings";
			// 
			// label8
			// 
			this->label8->Font = new System::Drawing::Font(S"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, (System::Byte)0);
			this->label8->Location = System::Drawing::Point(24, 120);
			this->label8->Name = S"label8";
			this->label8->Size = System::Drawing::Size(432, 23);
			this->label8->TabIndex = 16;
			this->label8->Text = S"Included documentation should be cleaned\?";
			// 
			// cB_docs_f
			// 
			this->cB_docs_f->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->cB_docs_f->Location = System::Drawing::Point(32, 168);
			this->cB_docs_f->Name = S"cB_docs_f";
			this->cB_docs_f->Size = System::Drawing::Size(280, 24);
			this->cB_docs_f->TabIndex = 15;
			this->cB_docs_f->Text = S"Remove Functions Documentation";
			// 
			// cB_docs_v
			// 
			this->cB_docs_v->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->cB_docs_v->Location = System::Drawing::Point(32, 144);
			this->cB_docs_v->Name = S"cB_docs_v";
			this->cB_docs_v->Size = System::Drawing::Size(280, 24);
			this->cB_docs_v->TabIndex = 14;
			this->cB_docs_v->Text = S"Remove Variables Documentation";
			// 
			// cB_funce
			// 
			this->cB_funce->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->cB_funce->Location = System::Drawing::Point(32, 64);
			this->cB_funce->Name = S"cB_funce";
			this->cB_funce->Size = System::Drawing::Size(280, 24);
			this->cB_funce->TabIndex = 13;
			this->cB_funce->Text = S"Remove sample functions implementation";
			// 
			// label2
			// 
			this->label2->Font = new System::Drawing::Font(S"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, (System::Byte)0);
			this->label2->Location = System::Drawing::Point(16, 16);
			this->label2->Name = S"label2";
			this->label2->Size = System::Drawing::Size(432, 23);
			this->label2->TabIndex = 12;
			this->label2->Text = S"Select options for class source && header files:";
			// 
			// cB_funcv
			// 
			this->cB_funcv->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->cB_funcv->Location = System::Drawing::Point(32, 40);
			this->cB_funcv->Name = S"cB_funcv";
			this->cB_funcv->Size = System::Drawing::Size(280, 24);
			this->cB_funcv->TabIndex = 11;
			this->cB_funcv->Text = S"Remove virtual functions implementation";
			// 
			// tabPage4
			// 
			this->tabPage4->Controls->Add(this->lB_dir);
			this->tabPage4->Controls->Add(this->tB_dir);
			this->tabPage4->Controls->Add(this->label10);
			this->tabPage4->Controls->Add(this->checkBox3);
			this->tabPage4->Controls->Add(this->checkBox2);
			this->tabPage4->Controls->Add(this->label9);
			this->tabPage4->Controls->Add(this->cB_relative);
			this->tabPage4->Location = System::Drawing::Point(4, 25);
			this->tabPage4->Name = S"tabPage4";
			this->tabPage4->Size = System::Drawing::Size(464, 281);
			this->tabPage4->TabIndex = 3;
			this->tabPage4->Text = S"Advanced";
			// 
			// lB_dir
			// 
			this->lB_dir->Location = System::Drawing::Point(32, 184);
			this->lB_dir->Name = S"lB_dir";
			this->lB_dir->Size = System::Drawing::Size(416, 80);
			this->lB_dir->TabIndex = 17;
			// 
			// tB_dir
			// 
			this->tB_dir->BackColor = System::Drawing::Color::FromArgb((System::Byte)235, (System::Byte)235, (System::Byte)255);
			this->tB_dir->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->tB_dir->Location = System::Drawing::Point(32, 160);
			this->tB_dir->Name = S"tB_dir";
			this->tB_dir->Size = System::Drawing::Size(416, 22);
			this->tB_dir->TabIndex = 15;
			this->tB_dir->Text = S"";
			// 
			// label10
			// 
			this->label10->Enabled = false;
			this->label10->Location = System::Drawing::Point(368, 144);
			this->label10->Name = S"label10";
			this->label10->Size = System::Drawing::Size(88, 23);
			this->label10->TabIndex = 16;
			this->label10->Text = S"project folder";
			// 
			// checkBox3
			// 
			this->checkBox3->Enabled = false;
			this->checkBox3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->checkBox3->Location = System::Drawing::Point(32, 104);
			this->checkBox3->Name = S"checkBox3";
			this->checkBox3->Size = System::Drawing::Size(280, 24);
			this->checkBox3->TabIndex = 14;
			this->checkBox3->Text = S"Do not save after generation";
			// 
			// checkBox2
			// 
			this->checkBox2->Enabled = false;
			this->checkBox2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->checkBox2->Location = System::Drawing::Point(32, 80);
			this->checkBox2->Name = S"checkBox2";
			this->checkBox2->Size = System::Drawing::Size(280, 24);
			this->checkBox2->TabIndex = 13;
			this->checkBox2->Text = S"Do not apply hashes";
			// 
			// label9
			// 
			this->label9->Font = new System::Drawing::Font(S"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, (System::Byte)0);
			this->label9->Location = System::Drawing::Point(16, 16);
			this->label9->Name = S"label9";
			this->label9->Size = System::Drawing::Size(432, 23);
			this->label9->TabIndex = 12;
			this->label9->Text = S"Edit these options at your risk:";
			// 
			// cB_relative
			// 
			this->cB_relative->Checked = true;
			this->cB_relative->CheckState = System::Windows::Forms::CheckState::Checked;
			this->cB_relative->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->cB_relative->Location = System::Drawing::Point(32, 40);
			this->cB_relative->Name = S"cB_relative";
			this->cB_relative->Size = System::Drawing::Size(280, 24);
			this->cB_relative->TabIndex = 11;
			this->cB_relative->Text = S"Use relative paths";
			// 
			// helpProvider1
			// 
			this->helpProvider1->HelpNamespace = S"..\\reference\\vipPS.chm";
			// 
			// wizardForm
			// 
			this->AcceptButton = this->button2;
			this->AutoScaleBaseSize = System::Drawing::Size(6, 15);
			this->ClientSize = System::Drawing::Size(480, 350);
			this->Controls->Add(this->selPage);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->panel1);
			this->HelpButton = true;
			this->helpProvider1->SetHelpKeyword(this, S"Generation Wizard");
			this->helpProvider1->SetHelpNavigator(this, System::Windows::Forms::HelpNavigator::Topic);
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = S"wizardForm";
			this->helpProvider1->SetShowHelp(this, true);
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = S"Package Generation Wizard..";
			this->Closing += new System::ComponentModel::CancelEventHandler(this, wizardForm_Closing);
			this->Load += new System::EventHandler(this, wizardForm_Load);
			this->panel2->ResumeLayout(false);
			this->selPage->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage3->ResumeLayout(false);
			this->tabPage2->ResumeLayout(false);
			this->tabPage4->ResumeLayout(false);
			this->ResumeLayout(false);

		}


//
private: System::Void button1_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 selPage->SelectedIndex = selPage->SelectedIndex + 1 ;
			 if (selPage->SelectedIndex >= selPage->TabPages->Count-1)
				 button1->Enabled = false;
			 else
				 button1->Enabled = true;
			 button3->Enabled = true;
		 }

private: System::Void button3_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 selPage->SelectedIndex = selPage->SelectedIndex - 1 ;
			 if (selPage->SelectedIndex == 0)
				 button3->Enabled = false;
			 else
				 button3->Enabled = true;
			 button1->Enabled = true;
		 }

private: System::Void button2_Click(System::Object *  sender, System::EventArgs *  e);


private: System::Void wizardForm_Load(System::Object *  sender, System::EventArgs *  e);

private: System::Void lB_type_SelectedIndexChanged(System::Object *  sender, System::EventArgs *  e);

private: System::Void tB_name_TextChanged(System::Object *  sender, System::EventArgs *  e);


private: System::Void wizardForm_Closing(System::Object *  sender, System::ComponentModel::CancelEventArgs *  e)
		 {
			 e->Cancel = true;
			 this->Visible = false;

		 }


};
}
