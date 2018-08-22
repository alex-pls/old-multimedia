#pragma once
#include "../../../../source/vipFilter.h"
#include "sourceInterface.h"
#include "outputInterface.h"
#include "loaderDLL.h"


using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::IO;


namespace vipWS3
{
	/// <summary>
	/// Riepilogo per filterForm
	///
	/// AVVISO: se si modifica il nome della classe, sarà necessario modificare la
	///          proprietà "Nome file di risorse" relativa allo strumento di compilazione delle risorse gestite
	///          associato a tutti i file RESX da cui dipende la classe. In caso contrario,
	///          le finestre di progettazione non saranno in grado di interagire correttamente con le
	///          risorse localizzate associate al form.
	/// </summary>
	public __gc class filterForm : public System::Windows::Forms::Form, public sourceInterface, public outputInterface
	{
	public:
		filterForm(void);

		void Init(vipFilter* myFilterInstance, loaderDLL* myPlugInObj);
		void Init() {};

		VIPRESULT importFrom(vipFrameRGB24* img);

		VIPRESULT extractTo(vipFrameRGB24* img);


	protected:
		void Dispose(Boolean disposing);

	private: loaderDLL* myObj;
	private: vipFilter* myFilter;
	private: __vipPlugInFuncInfo** func_infoAr;
	private: int func_infoCount;
	private: vipFrameRGB24* buffer;
	private: outputInterface* vF;
	private: sourceInterface* sF;

	private: System::Windows::Forms::Panel *  panel1;
	private: System::Windows::Forms::TabControl *  tabControl1;
	private: System::Windows::Forms::TabPage *  tabPage1;
	private: System::Windows::Forms::TabPage *  tabPage2;
	private: System::Windows::Forms::Button *  button1;
	private: System::Windows::Forms::ComboBox *  cBviews;
	private: System::Windows::Forms::TabPage *  tabPage3;
	private: System::Windows::Forms::ComboBox *  cBsources;

	private: System::Windows::Forms::Button *  button3;

	private: System::Windows::Forms::Panel *  panel9;
	private: System::Windows::Forms::Panel *  panel10;
	private: System::Windows::Forms::Panel *  panel11;
	private: System::Windows::Forms::Panel *  panel12;
	private: System::Windows::Forms::RichTextBox *  rTBinfo;
	private: System::Windows::Forms::Panel *  panel3;
	private: System::Windows::Forms::Panel *  panel4;
	private: System::Windows::Forms::Panel *  panel5;
	private: System::Windows::Forms::Panel *  panel2;
	private: System::Windows::Forms::Button *  button4;

	private: System::Windows::Forms::TextBox *  textBox1;
	private: System::Windows::Forms::Button *  button5;
	private: System::Windows::Forms::CheckBox *  cBautoEx;
	private: System::Windows::Forms::TabPage *  tabPage4;
	private: System::Windows::Forms::Panel *  panel6;
	private: System::Windows::Forms::Panel *  panel7;
	private: System::Windows::Forms::Panel *  panel8;
	private: System::Windows::Forms::Panel *  panel13;
	private: System::Windows::Forms::ComboBox *  cBhack;
	private: System::Windows::Forms::Label *  label1;
	private: System::Windows::Forms::Label *  label2;
	private: System::Windows::Forms::ComboBox *  cBparam;
	private: System::Windows::Forms::RichTextBox *  rTBparam;
	private: System::Windows::Forms::Button *  button7;
	private: System::Windows::Forms::Panel *  panel14;
	private: System::Windows::Forms::Button *  button2;
	private: System::Windows::Forms::Button *  button8;
	private: System::Windows::Forms::Panel *  panel15;
	private: System::Windows::Forms::Panel *  panel16;
	private: System::Windows::Forms::Panel *  panel17;
	private: System::Windows::Forms::Label *  lDef;
	private: System::Windows::Forms::ListBox *  lBcb;
	private: System::Windows::Forms::Panel *  panel18;
	private: System::Windows::Forms::GroupBox *  groupBox2;
	private: System::Windows::Forms::Label *  lParam;
	private: System::Windows::Forms::TextBox *  tBparam1;
	private: System::Windows::Forms::Panel *  panel19;
	private: System::Windows::Forms::GroupBox *  groupBox1;
	private: System::Windows::Forms::TextBox *  tBreturn;
	private: System::Windows::Forms::Label *  lReturn;
	private: System::Windows::Forms::Panel *  panel20;
	private: System::Windows::Forms::Button *  button6;
























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
			System::Resources::ResourceManager *  resources = new System::Resources::ResourceManager(__typeof(vipWS3::filterForm));
			this->panel1 = new System::Windows::Forms::Panel();
			this->cBautoEx = new System::Windows::Forms::CheckBox();
			this->button3 = new System::Windows::Forms::Button();
			this->cBsources = new System::Windows::Forms::ComboBox();
			this->button1 = new System::Windows::Forms::Button();
			this->cBviews = new System::Windows::Forms::ComboBox();
			this->tabControl1 = new System::Windows::Forms::TabControl();
			this->tabPage1 = new System::Windows::Forms::TabPage();
			this->button6 = new System::Windows::Forms::Button();
			this->panel20 = new System::Windows::Forms::Panel();
			this->groupBox1 = new System::Windows::Forms::GroupBox();
			this->tBreturn = new System::Windows::Forms::TextBox();
			this->lReturn = new System::Windows::Forms::Label();
			this->panel19 = new System::Windows::Forms::Panel();
			this->groupBox2 = new System::Windows::Forms::GroupBox();
			this->lParam = new System::Windows::Forms::Label();
			this->tBparam1 = new System::Windows::Forms::TextBox();
			this->panel18 = new System::Windows::Forms::Panel();
			this->lBcb = new System::Windows::Forms::ListBox();
			this->lDef = new System::Windows::Forms::Label();
			this->panel15 = new System::Windows::Forms::Panel();
			this->panel16 = new System::Windows::Forms::Panel();
			this->panel17 = new System::Windows::Forms::Panel();
			this->panel14 = new System::Windows::Forms::Panel();
			this->button8 = new System::Windows::Forms::Button();
			this->button2 = new System::Windows::Forms::Button();
			this->tabPage2 = new System::Windows::Forms::TabPage();
			this->rTBparam = new System::Windows::Forms::RichTextBox();
			this->panel2 = new System::Windows::Forms::Panel();
			this->button7 = new System::Windows::Forms::Button();
			this->button5 = new System::Windows::Forms::Button();
			this->cBparam = new System::Windows::Forms::ComboBox();
			this->button4 = new System::Windows::Forms::Button();
			this->panel3 = new System::Windows::Forms::Panel();
			this->textBox1 = new System::Windows::Forms::TextBox();
			this->panel4 = new System::Windows::Forms::Panel();
			this->panel5 = new System::Windows::Forms::Panel();
			this->tabPage3 = new System::Windows::Forms::TabPage();
			this->rTBinfo = new System::Windows::Forms::RichTextBox();
			this->panel9 = new System::Windows::Forms::Panel();
			this->panel10 = new System::Windows::Forms::Panel();
			this->panel11 = new System::Windows::Forms::Panel();
			this->panel12 = new System::Windows::Forms::Panel();
			this->tabPage4 = new System::Windows::Forms::TabPage();
			this->label2 = new System::Windows::Forms::Label();
			this->cBhack = new System::Windows::Forms::ComboBox();
			this->panel6 = new System::Windows::Forms::Panel();
			this->label1 = new System::Windows::Forms::Label();
			this->panel7 = new System::Windows::Forms::Panel();
			this->panel8 = new System::Windows::Forms::Panel();
			this->panel13 = new System::Windows::Forms::Panel();
			this->panel1->SuspendLayout();
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->panel14->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->panel2->SuspendLayout();
			this->panel3->SuspendLayout();
			this->tabPage3->SuspendLayout();
			this->tabPage4->SuspendLayout();
			this->panel6->SuspendLayout();
			this->SuspendLayout();
			//
			// panel1
			//
			this->panel1->Controls->Add(this->cBautoEx);
			this->panel1->Controls->Add(this->button3);
			this->panel1->Controls->Add(this->cBsources);
			this->panel1->Controls->Add(this->button1);
			this->panel1->Controls->Add(this->cBviews);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel1->Location = System::Drawing::Point(0, 332);
			this->panel1->Name = S"panel1";
			this->panel1->Size = System::Drawing::Size(464, 84);
			this->panel1->TabIndex = 0;
			//
			// cBautoEx
			//
			this->cBautoEx->Checked = true;
			this->cBautoEx->CheckState = System::Windows::Forms::CheckState::Checked;
			this->cBautoEx->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->cBautoEx->Location = System::Drawing::Point(8, 64);
			this->cBautoEx->Name = S"cBautoEx";
			this->cBautoEx->Size = System::Drawing::Size(432, 20);
			this->cBautoEx->TabIndex = 4;
			this->cBautoEx->Text = S"Auto - Push (on loading: frame are processed and redirected)";
			//
			// button3
			//
			this->button3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button3->Location = System::Drawing::Point(336, 8);
			this->button3->Name = S"button3";
			this->button3->Size = System::Drawing::Size(120, 23);
			this->button3->TabIndex = 3;
			this->button3->Text = S"Load && Process";
			this->button3->Click += new System::EventHandler(this, button3_Click);
			//
			// cBsources
			//
			this->cBsources->BackColor = System::Drawing::Color::FromArgb((System::Byte)192, (System::Byte)255, (System::Byte)192);
			this->cBsources->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			System::Object* __mcTemp__1[] = new System::Object*[1];
			__mcTemp__1[0] = S"NULL";
			this->cBsources->Items->AddRange(__mcTemp__1);
			this->cBsources->Location = System::Drawing::Point(8, 8);
			this->cBsources->Name = S"cBsources";
			this->cBsources->Size = System::Drawing::Size(320, 24);
			this->cBsources->TabIndex = 2;
			this->cBsources->SelectedIndexChanged += new System::EventHandler(this, cBsources_SelectedIndexChanged);
			//
			// button1
			//
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Location = System::Drawing::Point(336, 40);
			this->button1->Name = S"button1";
			this->button1->Size = System::Drawing::Size(120, 23);
			this->button1->TabIndex = 1;
			this->button1->Text = S"Push to Output";
			this->button1->Click += new System::EventHandler(this, button1_Click);
			//
			// cBviews
			//
			this->cBviews->BackColor = System::Drawing::Color::FromArgb((System::Byte)192, (System::Byte)255, (System::Byte)192);
			this->cBviews->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			System::Object* __mcTemp__2[] = new System::Object*[1];
			__mcTemp__2[0] = S"NULL";
			this->cBviews->Items->AddRange(__mcTemp__2);
			this->cBviews->Location = System::Drawing::Point(8, 40);
			this->cBviews->Name = S"cBviews";
			this->cBviews->Size = System::Drawing::Size(320, 24);
			this->cBviews->TabIndex = 0;
			this->cBviews->SelectedIndexChanged += new System::EventHandler(this, cBviews_SelectedIndexChanged);
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
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(464, 332);
			this->tabControl1->TabIndex = 1;
			//
			// tabPage1
			//
			this->tabPage1->Controls->Add(this->button6);
			this->tabPage1->Controls->Add(this->panel20);
			this->tabPage1->Controls->Add(this->groupBox1);
			this->tabPage1->Controls->Add(this->panel19);
			this->tabPage1->Controls->Add(this->groupBox2);
			this->tabPage1->Controls->Add(this->panel18);
			this->tabPage1->Controls->Add(this->lBcb);
			this->tabPage1->Controls->Add(this->lDef);
			this->tabPage1->Controls->Add(this->panel15);
			this->tabPage1->Controls->Add(this->panel16);
			this->tabPage1->Controls->Add(this->panel17);
			this->tabPage1->Controls->Add(this->panel14);
			this->tabPage1->Location = System::Drawing::Point(4, 25);
			this->tabPage1->Name = S"tabPage1";
			this->tabPage1->Size = System::Drawing::Size(456, 303);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = S"General";
			//
			// button6
			//
			this->button6->Dock = System::Windows::Forms::DockStyle::Top;
			this->button6->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button6->Location = System::Drawing::Point(192, 140);
			this->button6->Name = S"button6";
			this->button6->Size = System::Drawing::Size(256, 32);
			this->button6->TabIndex = 44;
			this->button6->Text = S"Invoke Function";
			this->button6->Click += new System::EventHandler(this, button6_Click);
			//
			// panel20
			//
			this->panel20->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel20->Location = System::Drawing::Point(192, 132);
			this->panel20->Name = S"panel20";
			this->panel20->Size = System::Drawing::Size(256, 8);
			this->panel20->TabIndex = 43;
			//
			// groupBox1
			//
			this->groupBox1->Controls->Add(this->tBreturn);
			this->groupBox1->Controls->Add(this->lReturn);
			this->groupBox1->Dock = System::Windows::Forms::DockStyle::Top;
			this->groupBox1->Location = System::Drawing::Point(192, 72);
			this->groupBox1->Name = S"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(256, 60);
			this->groupBox1->TabIndex = 41;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = S"Return Value";
			//
			// tBreturn
			//
			this->tBreturn->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->tBreturn->Location = System::Drawing::Point(112, 16);
			this->tBreturn->Name = S"tBreturn";
			this->tBreturn->ReadOnly = true;
			this->tBreturn->Size = System::Drawing::Size(120, 22);
			this->tBreturn->TabIndex = 1;
			this->tBreturn->Text = S"";
			//
			// lReturn
			//
			this->lReturn->Location = System::Drawing::Point(8, 18);
			this->lReturn->Name = S"lReturn";
			this->lReturn->Size = System::Drawing::Size(96, 24);
			this->lReturn->TabIndex = 0;
			//
			// panel19
			//
			this->panel19->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel19->Location = System::Drawing::Point(192, 64);
			this->panel19->Name = S"panel19";
			this->panel19->Size = System::Drawing::Size(256, 8);
			this->panel19->TabIndex = 40;
			//
			// groupBox2
			//
			this->groupBox2->Controls->Add(this->lParam);
			this->groupBox2->Controls->Add(this->tBparam1);
			this->groupBox2->Dock = System::Windows::Forms::DockStyle::Top;
			this->groupBox2->Location = System::Drawing::Point(192, 8);
			this->groupBox2->Name = S"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(256, 56);
			this->groupBox2->TabIndex = 37;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = S"Parameters";
			//
			// lParam
			//
			this->lParam->Location = System::Drawing::Point(8, 24);
			this->lParam->Name = S"lParam";
			this->lParam->Size = System::Drawing::Size(96, 16);
			this->lParam->TabIndex = 28;
			//
			// tBparam1
			//
			this->tBparam1->BackColor = System::Drawing::Color::FromArgb((System::Byte)255, (System::Byte)224, (System::Byte)192);
			this->tBparam1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->tBparam1->Location = System::Drawing::Point(112, 16);
			this->tBparam1->Name = S"tBparam1";
			this->tBparam1->Size = System::Drawing::Size(120, 22);
			this->tBparam1->TabIndex = 27;
			this->tBparam1->Text = S"";
			//
			// panel18
			//
			this->panel18->Dock = System::Windows::Forms::DockStyle::Left;
			this->panel18->Location = System::Drawing::Point(184, 8);
			this->panel18->Name = S"panel18";
			this->panel18->Size = System::Drawing::Size(8, 215);
			this->panel18->TabIndex = 36;
			//
			// lBcb
			//
			this->lBcb->BackColor = System::Drawing::Color::FromArgb((System::Byte)255, (System::Byte)224, (System::Byte)192);
			this->lBcb->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lBcb->Dock = System::Windows::Forms::DockStyle::Left;
			this->lBcb->ItemHeight = 16;
			this->lBcb->Location = System::Drawing::Point(8, 8);
			this->lBcb->Name = S"lBcb";
			this->lBcb->Size = System::Drawing::Size(176, 210);
			this->lBcb->TabIndex = 32;
			this->lBcb->SelectedIndexChanged += new System::EventHandler(this, lBcb_SelectedIndexChanged);
			//
			// lDef
			//
			this->lDef->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->lDef->Location = System::Drawing::Point(8, 223);
			this->lDef->Name = S"lDef";
			this->lDef->Size = System::Drawing::Size(440, 32);
			this->lDef->TabIndex = 31;
			//
			// panel15
			//
			this->panel15->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel15->Location = System::Drawing::Point(8, 0);
			this->panel15->Name = S"panel15";
			this->panel15->Size = System::Drawing::Size(440, 8);
			this->panel15->TabIndex = 22;
			//
			// panel16
			//
			this->panel16->Dock = System::Windows::Forms::DockStyle::Right;
			this->panel16->Location = System::Drawing::Point(448, 0);
			this->panel16->Name = S"panel16";
			this->panel16->Size = System::Drawing::Size(8, 255);
			this->panel16->TabIndex = 21;
			//
			// panel17
			//
			this->panel17->Dock = System::Windows::Forms::DockStyle::Left;
			this->panel17->Location = System::Drawing::Point(0, 0);
			this->panel17->Name = S"panel17";
			this->panel17->Size = System::Drawing::Size(8, 255);
			this->panel17->TabIndex = 20;
			//
			// panel14
			//
			this->panel14->Controls->Add(this->button8);
			this->panel14->Controls->Add(this->button2);
			this->panel14->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel14->Location = System::Drawing::Point(0, 255);
			this->panel14->Name = S"panel14";
			this->panel14->Size = System::Drawing::Size(456, 48);
			this->panel14->TabIndex = 4;
			//
			// button8
			//
			this->button8->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button8->Location = System::Drawing::Point(232, 8);
			this->button8->Name = S"button8";
			this->button8->Size = System::Drawing::Size(216, 32);
			this->button8->TabIndex = 2;
			this->button8->Text = S"Setup..";
			this->button8->Click += new System::EventHandler(this, button8_Click);
			//
			// button2
			//
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button2->Location = System::Drawing::Point(8, 8);
			this->button2->Name = S"button2";
			this->button2->Size = System::Drawing::Size(216, 32);
			this->button2->TabIndex = 1;
			this->button2->Text = S"reset";
			//
			// tabPage2
			//
			this->tabPage2->Controls->Add(this->rTBparam);
			this->tabPage2->Controls->Add(this->panel2);
			this->tabPage2->Controls->Add(this->panel3);
			this->tabPage2->Controls->Add(this->panel4);
			this->tabPage2->Controls->Add(this->panel5);
			this->tabPage2->Location = System::Drawing::Point(4, 25);
			this->tabPage2->Name = S"tabPage2";
			this->tabPage2->Size = System::Drawing::Size(456, 303);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = S"Parameters";
			//
			// rTBparam
			//
			this->rTBparam->BackColor = System::Drawing::Color::FromArgb((System::Byte)255, (System::Byte)224, (System::Byte)192);
			this->rTBparam->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->rTBparam->Dock = System::Windows::Forms::DockStyle::Fill;
			this->rTBparam->Location = System::Drawing::Point(8, 112);
			this->rTBparam->Name = S"rTBparam";
			this->rTBparam->Size = System::Drawing::Size(440, 159);
			this->rTBparam->TabIndex = 24;
			this->rTBparam->Text = S"";
			//
			// panel2
			//
			this->panel2->Controls->Add(this->button7);
			this->panel2->Controls->Add(this->button5);
			this->panel2->Controls->Add(this->cBparam);
			this->panel2->Controls->Add(this->button4);
			this->panel2->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel2->Location = System::Drawing::Point(8, 0);
			this->panel2->Name = S"panel2";
			this->panel2->Size = System::Drawing::Size(440, 112);
			this->panel2->TabIndex = 23;
			//
			// button7
			//
			this->button7->Enabled = false;
			this->button7->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button7->Location = System::Drawing::Point(0, 80);
			this->button7->Name = S"button7";
			this->button7->Size = System::Drawing::Size(208, 24);
			this->button7->TabIndex = 4;
			this->button7->Text = S"Save && Update";
			this->button7->Click += new System::EventHandler(this, button7_Click);
			//
			// button5
			//
			this->button5->Enabled = false;
			this->button5->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button5->Location = System::Drawing::Point(224, 48);
			this->button5->Name = S"button5";
			this->button5->Size = System::Drawing::Size(208, 24);
			this->button5->TabIndex = 3;
			this->button5->Text = S"New from File..";
			//
			// cBparam
			//
			this->cBparam->BackColor = System::Drawing::Color::FromArgb((System::Byte)255, (System::Byte)224, (System::Byte)192);
			this->cBparam->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cBparam->Enabled = false;
			this->cBparam->Location = System::Drawing::Point(0, 16);
			this->cBparam->Name = S"cBparam";
			this->cBparam->Size = System::Drawing::Size(432, 24);
			this->cBparam->TabIndex = 2;
			this->cBparam->SelectedIndexChanged += new System::EventHandler(this, comboBox1_SelectedIndexChanged);
			//
			// button4
			//
			this->button4->Enabled = false;
			this->button4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button4->Location = System::Drawing::Point(0, 48);
			this->button4->Name = S"button4";
			this->button4->Size = System::Drawing::Size(208, 24);
			this->button4->TabIndex = 1;
			this->button4->Text = S"New Default..";
			//
			// panel3
			//
			this->panel3->Controls->Add(this->textBox1);
			this->panel3->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel3->Location = System::Drawing::Point(8, 271);
			this->panel3->Name = S"panel3";
			this->panel3->Size = System::Drawing::Size(440, 32);
			this->panel3->TabIndex = 22;
			//
			// textBox1
			//
			this->textBox1->BackColor = System::Drawing::Color::FromArgb((System::Byte)255, (System::Byte)224, (System::Byte)192);
			this->textBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->textBox1->Dock = System::Windows::Forms::DockStyle::Top;
			this->textBox1->Location = System::Drawing::Point(0, 0);
			this->textBox1->Name = S"textBox1";
			this->textBox1->Size = System::Drawing::Size(440, 22);
			this->textBox1->TabIndex = 1;
			this->textBox1->Text = S"";
			//
			// panel4
			//
			this->panel4->Dock = System::Windows::Forms::DockStyle::Right;
			this->panel4->Location = System::Drawing::Point(448, 0);
			this->panel4->Name = S"panel4";
			this->panel4->Size = System::Drawing::Size(8, 303);
			this->panel4->TabIndex = 21;
			//
			// panel5
			//
			this->panel5->Dock = System::Windows::Forms::DockStyle::Left;
			this->panel5->Location = System::Drawing::Point(0, 0);
			this->panel5->Name = S"panel5";
			this->panel5->Size = System::Drawing::Size(8, 303);
			this->panel5->TabIndex = 20;
			//
			// tabPage3
			//
			this->tabPage3->Controls->Add(this->rTBinfo);
			this->tabPage3->Controls->Add(this->panel9);
			this->tabPage3->Controls->Add(this->panel10);
			this->tabPage3->Controls->Add(this->panel11);
			this->tabPage3->Controls->Add(this->panel12);
			this->tabPage3->Location = System::Drawing::Point(4, 25);
			this->tabPage3->Name = S"tabPage3";
			this->tabPage3->Size = System::Drawing::Size(456, 303);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = S"Module Informations";
			//
			// rTBinfo
			//
			this->rTBinfo->BackColor = System::Drawing::Color::FromArgb((System::Byte)255, (System::Byte)224, (System::Byte)192);
			this->rTBinfo->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->rTBinfo->Dock = System::Windows::Forms::DockStyle::Fill;
			this->rTBinfo->Location = System::Drawing::Point(8, 8);
			this->rTBinfo->Name = S"rTBinfo";
			this->rTBinfo->ReadOnly = true;
			this->rTBinfo->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::Vertical;
			this->rTBinfo->Size = System::Drawing::Size(440, 287);
			this->rTBinfo->TabIndex = 20;
			this->rTBinfo->Text = S"";
			//
			// panel9
			//
			this->panel9->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel9->Location = System::Drawing::Point(8, 0);
			this->panel9->Name = S"panel9";
			this->panel9->Size = System::Drawing::Size(440, 8);
			this->panel9->TabIndex = 19;
			//
			// panel10
			//
			this->panel10->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel10->Location = System::Drawing::Point(8, 295);
			this->panel10->Name = S"panel10";
			this->panel10->Size = System::Drawing::Size(440, 8);
			this->panel10->TabIndex = 18;
			//
			// panel11
			//
			this->panel11->Dock = System::Windows::Forms::DockStyle::Right;
			this->panel11->Location = System::Drawing::Point(448, 0);
			this->panel11->Name = S"panel11";
			this->panel11->Size = System::Drawing::Size(8, 303);
			this->panel11->TabIndex = 17;
			//
			// panel12
			//
			this->panel12->Dock = System::Windows::Forms::DockStyle::Left;
			this->panel12->Location = System::Drawing::Point(0, 0);
			this->panel12->Name = S"panel12";
			this->panel12->Size = System::Drawing::Size(8, 303);
			this->panel12->TabIndex = 16;
			//
			// tabPage4
			//
			this->tabPage4->Controls->Add(this->label2);
			this->tabPage4->Controls->Add(this->cBhack);
			this->tabPage4->Controls->Add(this->panel6);
			this->tabPage4->Controls->Add(this->panel7);
			this->tabPage4->Controls->Add(this->panel8);
			this->tabPage4->Controls->Add(this->panel13);
			this->tabPage4->Location = System::Drawing::Point(4, 25);
			this->tabPage4->Name = S"tabPage4";
			this->tabPage4->Size = System::Drawing::Size(456, 303);
			this->tabPage4->TabIndex = 3;
			this->tabPage4->Text = S"Bind Hacking";
			//
			// label2
			//
			this->label2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label2->Location = System::Drawing::Point(8, 46);
			this->label2->Name = S"label2";
			this->label2->Size = System::Drawing::Size(440, 249);
			this->label2->TabIndex = 25;
			this->label2->Text = S"This functionality has not been implemented jet.";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			//
			// cBhack
			//
			this->cBhack->BackColor = System::Drawing::Color::FromArgb((System::Byte)255, (System::Byte)224, (System::Byte)192);
			this->cBhack->Dock = System::Windows::Forms::DockStyle::Top;
			this->cBhack->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			System::Object* __mcTemp__3[] = new System::Object*[1];
			__mcTemp__3[0] = S"void functionName(void)";
			this->cBhack->Items->AddRange(__mcTemp__3);
			this->cBhack->Location = System::Drawing::Point(8, 24);
			this->cBhack->Name = S"cBhack";
			this->cBhack->Size = System::Drawing::Size(440, 22);
			this->cBhack->TabIndex = 24;
			//
			// panel6
			//
			this->panel6->Controls->Add(this->label1);
			this->panel6->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel6->Location = System::Drawing::Point(8, 0);
			this->panel6->Name = S"panel6";
			this->panel6->Size = System::Drawing::Size(440, 24);
			this->panel6->TabIndex = 23;
			//
			// label1
			//
			this->label1->Dock = System::Windows::Forms::DockStyle::Right;
			this->label1->Location = System::Drawing::Point(338, 0);
			this->label1->Name = S"label1";
			this->label1->Size = System::Drawing::Size(102, 24);
			this->label1->TabIndex = 2;
			this->label1->Text = S"function typeDef";
			this->label1->TextAlign = System::Drawing::ContentAlignment::BottomRight;
			//
			// panel7
			//
			this->panel7->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel7->Location = System::Drawing::Point(8, 295);
			this->panel7->Name = S"panel7";
			this->panel7->Size = System::Drawing::Size(440, 8);
			this->panel7->TabIndex = 22;
			//
			// panel8
			//
			this->panel8->Dock = System::Windows::Forms::DockStyle::Right;
			this->panel8->Location = System::Drawing::Point(448, 0);
			this->panel8->Name = S"panel8";
			this->panel8->Size = System::Drawing::Size(8, 303);
			this->panel8->TabIndex = 21;
			//
			// panel13
			//
			this->panel13->Dock = System::Windows::Forms::DockStyle::Left;
			this->panel13->Location = System::Drawing::Point(0, 0);
			this->panel13->Name = S"panel13";
			this->panel13->Size = System::Drawing::Size(8, 303);
			this->panel13->TabIndex = 20;
			//
			// filterForm
			//
			this->AutoScaleBaseSize = System::Drawing::Size(6, 15);
			this->ClientSize = System::Drawing::Size(464, 416);
			this->Controls->Add(this->tabControl1);
			this->Controls->Add(this->panel1);
			this->Icon = (__try_cast<System::Drawing::Icon *  >(resources->GetObject(S"$this.Icon")));
			this->Name = S"filterForm";
			this->Text = S"vipFilter Interface 1.0";
			this->Closing += new System::ComponentModel::CancelEventHandler(this, filterForm_Closing);
			this->Load += new System::EventHandler(this, filterForm_Load);
			this->panel1->ResumeLayout(false);
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->groupBox1->ResumeLayout(false);
			this->groupBox2->ResumeLayout(false);
			this->panel14->ResumeLayout(false);
			this->tabPage2->ResumeLayout(false);
			this->panel2->ResumeLayout(false);
			this->panel3->ResumeLayout(false);
			this->tabPage3->ResumeLayout(false);
			this->tabPage4->ResumeLayout(false);
			this->panel6->ResumeLayout(false);
			this->ResumeLayout(false);

		}















//

private: System::Void filterForm_Load(System::Object *  sender, System::EventArgs *  e);


private: System::Void rTBinfo_LinkClicked(System::Object *  sender, System::Windows::Forms::LinkClickedEventArgs *  e)
		 {
			 System::Diagnostics::Process::Start(e->LinkText);
		 }


private: System::Void button1_Click(System::Object *  sender, System::EventArgs *  e);

private: System::Void button3_Click(System::Object *  sender, System::EventArgs *  e);

private: System::Void button2_Click(System::Object *  sender, System::EventArgs *  e);


/////////////////////////////////////////////////////////////////////////////////
/////////// same for all data sources:
public: outputInterface* getOutputInterface() { return vF; }
public: System::Object __gc* getObjectInstance() { return this; };


public: int setSource(sourceInterface* NsF)
 {
	if (NsF == NULL)
	 {
		cBsources->SelectedIndex = -1;
		return 0;
	 }

	for (int i=0; i<cBsources->Items->Count; i++)
	 {
		 if ( dynamic_cast<Form*>(NsF)->Text->Equals(cBsources->Items->Item[i]->ToString()) )
		  {
			cBsources->SelectedIndex = i;
			sF = NsF;
			return 0;
		  }
	 }
	cBsources->SelectedIndex = -1;
	return 1;
 }

public:	System::Void viewsUpdate(void)
			{
				int oldSel = cBviews->SelectedIndex;

				cBviews->Items->Clear();
				cBviews->Items->Add( new System::String("NULL Output") );
				for (int i=0; i<this->MdiParent->MdiChildren->Count; i++)
				 {
					if (  this->MdiParent->MdiChildren->get_Item(i)->GetType()->GetInterface("outputInterface") &&
						 !this->MdiParent->MdiChildren->get_Item(i)->Equals(this) )
						cBviews->Items->Add( ( static_cast<Form*> (this->MdiParent->MdiChildren->get_Item(i)) )->Text );
				 }
				if ( oldSel < 1 && cBviews->Items->Count == 2 )
					oldSel = 1;
				else if ( oldSel >= cBviews->Items->Count )
					oldSel = cBviews->Items->Count-1;
				cBviews->SelectedIndex = oldSel;
			}

public:	void sourcesUpdate(void)
			{
				int oldSel = cBsources->SelectedIndex;

				cBsources->Items->Clear();
				for (int i=0; i<this->MdiParent->MdiChildren->Count; i++)
				 {
					if (this->MdiParent->MdiChildren->get_Item(i)->GetType()->GetInterface("sourceInterface") &&
						!this->MdiParent->MdiChildren->get_Item(i)->Equals(this) )

							cBsources->Items->Add( ( static_cast<Form*> (this->MdiParent->MdiChildren->get_Item(i)) )->Text );
				 }
				if ( oldSel < 1 && cBsources->Items->Count == 1 )
					oldSel = 0;
				else if ( oldSel >= cBsources->Items->Count )
					oldSel = cBsources->Items->Count-1;
				cBsources->SelectedIndex = oldSel;
			}

private: System::Void cBviews_SelectedIndexChanged(System::Object *  sender, System::EventArgs *  e)
		 {
			 for (int i=0; i<this->MdiParent->MdiChildren->Count; i++)
			 {

				if ( static_cast<Form*>(this->MdiParent->MdiChildren->get_Item(i))->Text->Equals(cBviews->SelectedItem->ToString() ))
				{
					vF = static_cast<outputInterface*>(this->MdiParent->MdiChildren->get_Item(i));
					vF->setSource(this);
					break;
				}
			 }
		 }


private: System::Void cBsources_SelectedIndexChanged(System::Object *  sender, System::EventArgs *  e)
		 {
			 for (int i=0; i<this->MdiParent->MdiChildren->Count; i++)
			 {

				if ( static_cast<Form*>(this->MdiParent->MdiChildren->get_Item(i))->Text->Equals(cBsources->SelectedItem->ToString() )	)
				{
					sF = static_cast<sourceInterface*>(this->MdiParent->MdiChildren->get_Item(i));
					break;
				}
			 }
		 }



private: System::Void comboBox1_SelectedIndexChanged(System::Object *  sender, System::EventArgs *  e);


private: System::Void button7_Click(System::Object *  sender, System::EventArgs *  e);


private: System::Void button8_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 int res = myObj->openSetupDialog();
			 if ( res < 0 )
				 MessageBox::Show(this, S"Cannot open Filter Setup Dialog!\r\nMaybe it's not available for this plugin.", this->Text);
			 else if ( res > 0 )
				 MessageBox::Show(this, S"Filter Setup Dialog returned ad error!", this->Text);

		 }



private: System::Void button6_Click(System::Object *  sender, System::EventArgs *  e);

private: System::Void lBcb_SelectedIndexChanged(System::Object *  sender, System::EventArgs *  e)
		 {
			 if ( lBcb->SelectedIndex != -1)
			 {
				 lParam->Text = new String(func_infoAr[lBcb->SelectedIndex]->param1);
				 lReturn->Text = new String(func_infoAr[lBcb->SelectedIndex]->result);
				 lDef->Text = new String(func_infoAr[lBcb->SelectedIndex]->c_decl);
			 }
		 }

private: System::Void filterForm_Closing(System::Object *  sender, System::ComponentModel::CancelEventArgs *  e);


};
}
