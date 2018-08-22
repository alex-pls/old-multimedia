#pragma once
#include "../../../../source/vipBuffer.h"
#include "../../../../source/vipFrameRGB24.h"
#include "sourceInterface.h"
#include "outputInterface.h"
#include "loaderDLL.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace vipWS3
{
	/// <summary>
	/// Riepilogo per bufferForm
	///
	/// AVVISO: se si modifica il nome della classe, sarà necessario modificare la
	///          proprietà "Nome file di risorse" relativa allo strumento di compilazione delle risorse gestite
	///          associato a tutti i file RESX da cui dipende la classe. In caso contrario,
	///          le finestre di progettazione non saranno in grado di interagire correttamente con le
	///          risorse localizzate associate al form.
	/// </summary>
	public __gc class bufferForm : public System::Windows::Forms::Form, public sourceInterface, public outputInterface
	{
	public:
		bufferForm(void);

		void Init(vipBuffer<vipFrameRGB24>* myBufferInstance, loaderDLL* myPlugInObj);
		void Init() {};

		VIPRESULT importFrom(vipFrameRGB24* img);

		VIPRESULT extractTo(vipFrameRGB24* img);


	protected:
		void Dispose(Boolean disposing);

	private: loaderDLL* myObj;
	private: vipBuffer<vipFrameRGB24>* myBuffer;
	private: outputInterface* vF;
	private: sourceInterface* sF;

	private: System::Windows::Forms::Panel *  panel1;
	private: System::Windows::Forms::CheckBox *  cBautoEx;
	private: System::Windows::Forms::Button *  button3;
	private: System::Windows::Forms::ComboBox *  cBsources;
	private: System::Windows::Forms::Button *  button1;
	private: System::Windows::Forms::ComboBox *  cBviews;
	private: System::Windows::Forms::TabControl *  tabControl1;
	private: System::Windows::Forms::TabPage *  tabPage2;
	private: System::Windows::Forms::TabPage *  tabPage3;
	private: System::Windows::Forms::Panel *  panel2;
	private: System::Windows::Forms::Panel *  panel3;
	private: System::Windows::Forms::Panel *  panel4;
	private: System::Windows::Forms::Panel *  panel5;




	private: System::Windows::Forms::Panel *  panel6;
	private: System::Windows::Forms::Panel *  panel7;
	private: System::Windows::Forms::Panel *  panel8;
	private: System::Windows::Forms::Panel *  panel13;
	private: System::Windows::Forms::Panel *  panel14;
	private: System::Windows::Forms::Panel *  panel15;
	private: System::Windows::Forms::GroupBox *  groupBox2;
	private: System::Windows::Forms::GroupBox *  groupBox3;
	private: System::Windows::Forms::Button *  button2;
	private: System::Windows::Forms::Button *  button4;
	private: System::Windows::Forms::Button *  button5;
	private: System::Windows::Forms::Label *  label1;
	private: System::Windows::Forms::Label *  label2;
	private: System::Windows::Forms::Label *  label3;
	private: System::Windows::Forms::Label *  label7;
	private: System::Windows::Forms::Button *  button6;
	private: System::Windows::Forms::Button *  button7;
	private: System::Windows::Forms::CheckedListBox *  chkLbItems;
	private: System::Windows::Forms::TabPage *  tabPage5;
	private: System::Windows::Forms::Panel *  panel9;
	private: System::Windows::Forms::Panel *  panel10;
	private: System::Windows::Forms::Panel *  panel11;
	private: System::Windows::Forms::Panel *  panel12;
	private: System::Windows::Forms::RichTextBox *  rTBinfo;
	private: System::Windows::Forms::ComboBox *  cBpreviews;
	private: System::Windows::Forms::CheckBox *  cBupdateIndex;
	private: System::Windows::Forms::Label *  lb_b;
	private: System::Windows::Forms::Label *  lb_h;
	private: System::Windows::Forms::Label *  lb_w;
	private: System::Windows::Forms::CheckBox *  cBremoveData;
	private: System::Windows::Forms::GroupBox *  groupBox4;
	private: System::Windows::Forms::Panel *  panel16;
	private: System::Windows::Forms::GroupBox *  groupBox5;
	private: System::Windows::Forms::Panel *  panel17;



	private: System::Windows::Forms::Label *  label4;
	private: System::Windows::Forms::Label *  label5;
	private: System::Windows::Forms::Button *  button8;
	private: System::Windows::Forms::Label *  lB_count;
	private: System::Windows::Forms::Label *  lB_size;
	private: System::Windows::Forms::Panel *  panel18;
	private: System::Windows::Forms::CheckBox *  checkBox2;
	private: System::Windows::Forms::CheckBox *  checkBox1;
	private: System::Windows::Forms::GroupBox *  groupBox1;
	private: System::Windows::Forms::TrackBar *  tBindex;
	private: System::Windows::Forms::NumericUpDown *  nUDindex;
	private: System::Windows::Forms::Button *  button9;




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
			System::Resources::ResourceManager *  resources = new System::Resources::ResourceManager(__typeof(vipWS3::bufferForm));
			this->panel1 = new System::Windows::Forms::Panel();
			this->cBautoEx = new System::Windows::Forms::CheckBox();
			this->button3 = new System::Windows::Forms::Button();
			this->cBsources = new System::Windows::Forms::ComboBox();
			this->button1 = new System::Windows::Forms::Button();
			this->cBviews = new System::Windows::Forms::ComboBox();
			this->tabControl1 = new System::Windows::Forms::TabControl();
			this->tabPage2 = new System::Windows::Forms::TabPage();
			this->groupBox1 = new System::Windows::Forms::GroupBox();
			this->tBindex = new System::Windows::Forms::TrackBar();
			this->nUDindex = new System::Windows::Forms::NumericUpDown();
			this->panel18 = new System::Windows::Forms::Panel();
			this->checkBox2 = new System::Windows::Forms::CheckBox();
			this->checkBox1 = new System::Windows::Forms::CheckBox();
			this->panel17 = new System::Windows::Forms::Panel();
			this->groupBox5 = new System::Windows::Forms::GroupBox();
			this->lB_size = new System::Windows::Forms::Label();
			this->lB_count = new System::Windows::Forms::Label();
			this->button8 = new System::Windows::Forms::Button();
			this->label5 = new System::Windows::Forms::Label();
			this->label4 = new System::Windows::Forms::Label();
			this->panel16 = new System::Windows::Forms::Panel();
			this->groupBox4 = new System::Windows::Forms::GroupBox();
			this->button9 = new System::Windows::Forms::Button();
			this->panel2 = new System::Windows::Forms::Panel();
			this->panel3 = new System::Windows::Forms::Panel();
			this->panel4 = new System::Windows::Forms::Panel();
			this->panel5 = new System::Windows::Forms::Panel();
			this->tabPage3 = new System::Windows::Forms::TabPage();
			this->panel15 = new System::Windows::Forms::Panel();
			this->cBupdateIndex = new System::Windows::Forms::CheckBox();
			this->groupBox3 = new System::Windows::Forms::GroupBox();
			this->cBremoveData = new System::Windows::Forms::CheckBox();
			this->button5 = new System::Windows::Forms::Button();
			this->button4 = new System::Windows::Forms::Button();
			this->button2 = new System::Windows::Forms::Button();
			this->groupBox2 = new System::Windows::Forms::GroupBox();
			this->button7 = new System::Windows::Forms::Button();
			this->button6 = new System::Windows::Forms::Button();
			this->label7 = new System::Windows::Forms::Label();
			this->cBpreviews = new System::Windows::Forms::ComboBox();
			this->lb_b = new System::Windows::Forms::Label();
			this->lb_h = new System::Windows::Forms::Label();
			this->lb_w = new System::Windows::Forms::Label();
			this->label3 = new System::Windows::Forms::Label();
			this->label2 = new System::Windows::Forms::Label();
			this->label1 = new System::Windows::Forms::Label();
			this->panel14 = new System::Windows::Forms::Panel();
			this->chkLbItems = new System::Windows::Forms::CheckedListBox();
			this->panel6 = new System::Windows::Forms::Panel();
			this->panel7 = new System::Windows::Forms::Panel();
			this->panel8 = new System::Windows::Forms::Panel();
			this->panel13 = new System::Windows::Forms::Panel();
			this->tabPage5 = new System::Windows::Forms::TabPage();
			this->rTBinfo = new System::Windows::Forms::RichTextBox();
			this->panel9 = new System::Windows::Forms::Panel();
			this->panel10 = new System::Windows::Forms::Panel();
			this->panel11 = new System::Windows::Forms::Panel();
			this->panel12 = new System::Windows::Forms::Panel();
			this->panel1->SuspendLayout();
			this->tabControl1->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->groupBox1->SuspendLayout();
			(__try_cast<System::ComponentModel::ISupportInitialize *  >(this->tBindex))->BeginInit();
			(__try_cast<System::ComponentModel::ISupportInitialize *  >(this->nUDindex))->BeginInit();
			this->panel18->SuspendLayout();
			this->groupBox5->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->tabPage3->SuspendLayout();
			this->panel15->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->tabPage5->SuspendLayout();
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
			this->panel1->Location = System::Drawing::Point(0, 342);
			this->panel1->Name = S"panel1";
			this->panel1->Size = System::Drawing::Size(488, 88);
			this->panel1->TabIndex = 1;
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
			this->button3->Location = System::Drawing::Point(360, 8);
			this->button3->Name = S"button3";
			this->button3->Size = System::Drawing::Size(120, 23);
			this->button3->TabIndex = 3;
			this->button3->Text = S"Load in Buffer";
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
			this->cBsources->Size = System::Drawing::Size(344, 24);
			this->cBsources->TabIndex = 2;
			this->cBsources->SelectedIndexChanged += new System::EventHandler(this, cBsources_SelectedIndexChanged);
			//
			// button1
			//
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Location = System::Drawing::Point(360, 40);
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
			this->cBviews->Size = System::Drawing::Size(344, 24);
			this->cBviews->TabIndex = 0;
			this->cBviews->SelectedIndexChanged += new System::EventHandler(this, cBviews_SelectedIndexChanged);
			//
			// tabControl1
			//
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Controls->Add(this->tabPage5);
			this->tabControl1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tabControl1->Location = System::Drawing::Point(0, 0);
			this->tabControl1->Name = S"tabControl1";
			this->tabControl1->Padding = System::Drawing::Point(12, 3);
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(488, 342);
			this->tabControl1->TabIndex = 2;
			//
			// tabPage2
			//
			this->tabPage2->Controls->Add(this->groupBox1);
			this->tabPage2->Controls->Add(this->panel18);
			this->tabPage2->Controls->Add(this->panel17);
			this->tabPage2->Controls->Add(this->groupBox5);
			this->tabPage2->Controls->Add(this->panel16);
			this->tabPage2->Controls->Add(this->groupBox4);
			this->tabPage2->Controls->Add(this->panel2);
			this->tabPage2->Controls->Add(this->panel3);
			this->tabPage2->Controls->Add(this->panel4);
			this->tabPage2->Controls->Add(this->panel5);
			this->tabPage2->Location = System::Drawing::Point(4, 25);
			this->tabPage2->Name = S"tabPage2";
			this->tabPage2->Size = System::Drawing::Size(480, 313);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = S"Control";
			//
			// groupBox1
			//
			this->groupBox1->Controls->Add(this->tBindex);
			this->groupBox1->Controls->Add(this->nUDindex);
			this->groupBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->groupBox1->Location = System::Drawing::Point(8, 200);
			this->groupBox1->Name = S"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(464, 81);
			this->groupBox1->TabIndex = 43;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = S"IndexFrame Control";
			//
			// tBindex
			//
			this->tBindex->AutoSize = false;
			this->tBindex->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tBindex->Location = System::Drawing::Point(3, 18);
			this->tBindex->Minimum = 1;
			this->tBindex->Name = S"tBindex";
			this->tBindex->Size = System::Drawing::Size(370, 60);
			this->tBindex->TabIndex = 1;
			this->tBindex->Value = 1;
			//
			// nUDindex
			//
			this->nUDindex->BackColor = System::Drawing::Color::FromArgb((System::Byte)255, (System::Byte)224, (System::Byte)192);
			this->nUDindex->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->nUDindex->Dock = System::Windows::Forms::DockStyle::Right;
			this->nUDindex->Font = new System::Drawing::Font(S"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (System::Byte)0);
			this->nUDindex->Location = System::Drawing::Point(373, 18);
			this->nUDindex->Name = S"nUDindex";
			this->nUDindex->Size = System::Drawing::Size(88, 26);
			this->nUDindex->TabIndex = 0;
			this->nUDindex->ThousandsSeparator = true;
			//
			// panel18
			//
			this->panel18->Controls->Add(this->checkBox2);
			this->panel18->Controls->Add(this->checkBox1);
			this->panel18->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel18->Location = System::Drawing::Point(8, 281);
			this->panel18->Name = S"panel18";
			this->panel18->Size = System::Drawing::Size(464, 24);
			this->panel18->TabIndex = 42;
			//
			// checkBox2
			//
			this->checkBox2->Checked = true;
			this->checkBox2->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox2->Enabled = false;
			this->checkBox2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->checkBox2->Location = System::Drawing::Point(216, 0);
			this->checkBox2->Name = S"checkBox2";
			this->checkBox2->Size = System::Drawing::Size(200, 24);
			this->checkBox2->TabIndex = 43;
			this->checkBox2->Text = S"Delete Frame on Closing";
			//
			// checkBox1
			//
			this->checkBox1->Checked = true;
			this->checkBox1->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox1->Enabled = false;
			this->checkBox1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->checkBox1->Location = System::Drawing::Point(4, 0);
			this->checkBox1->Name = S"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(184, 24);
			this->checkBox1->TabIndex = 42;
			this->checkBox1->Text = S"Data Copy Enabled";
			//
			// panel17
			//
			this->panel17->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel17->Location = System::Drawing::Point(8, 192);
			this->panel17->Name = S"panel17";
			this->panel17->Size = System::Drawing::Size(464, 8);
			this->panel17->TabIndex = 39;
			//
			// groupBox5
			//
			this->groupBox5->Controls->Add(this->lB_size);
			this->groupBox5->Controls->Add(this->lB_count);
			this->groupBox5->Controls->Add(this->button8);
			this->groupBox5->Controls->Add(this->label5);
			this->groupBox5->Controls->Add(this->label4);
			this->groupBox5->Dock = System::Windows::Forms::DockStyle::Top;
			this->groupBox5->Location = System::Drawing::Point(8, 88);
			this->groupBox5->Name = S"groupBox5";
			this->groupBox5->Size = System::Drawing::Size(464, 104);
			this->groupBox5->TabIndex = 38;
			this->groupBox5->TabStop = false;
			this->groupBox5->Text = S"Buffer Informations";
			//
			// lB_size
			//
			this->lB_size->Location = System::Drawing::Point(128, 48);
			this->lB_size->Name = S"lB_size";
			this->lB_size->Size = System::Drawing::Size(160, 24);
			this->lB_size->TabIndex = 4;
			//
			// lB_count
			//
			this->lB_count->Location = System::Drawing::Point(128, 24);
			this->lB_count->Name = S"lB_count";
			this->lB_count->Size = System::Drawing::Size(96, 24);
			this->lB_count->TabIndex = 3;
			//
			// button8
			//
			this->button8->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button8->Location = System::Drawing::Point(312, 16);
			this->button8->Name = S"button8";
			this->button8->TabIndex = 2;
			this->button8->Text = S"Update";
			this->button8->Click += new System::EventHandler(this, button8_Click);
			//
			// label5
			//
			this->label5->Location = System::Drawing::Point(24, 48);
			this->label5->Name = S"label5";
			this->label5->TabIndex = 1;
			this->label5->Text = S"Buffer Size:";
			//
			// label4
			//
			this->label4->Location = System::Drawing::Point(24, 24);
			this->label4->Name = S"label4";
			this->label4->TabIndex = 0;
			this->label4->Text = S"Items Count:";
			//
			// panel16
			//
			this->panel16->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel16->Location = System::Drawing::Point(8, 80);
			this->panel16->Name = S"panel16";
			this->panel16->Size = System::Drawing::Size(464, 8);
			this->panel16->TabIndex = 36;
			//
			// groupBox4
			//
			this->groupBox4->Controls->Add(this->button9);
			this->groupBox4->Dock = System::Windows::Forms::DockStyle::Top;
			this->groupBox4->Location = System::Drawing::Point(8, 8);
			this->groupBox4->Name = S"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(464, 72);
			this->groupBox4->TabIndex = 35;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = S"Automation Settings";
			//
			// button9
			//
			this->button9->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->button9->Location = System::Drawing::Point(16, 24);
			this->button9->Name = S"button9";
			this->button9->Size = System::Drawing::Size(120, 32);
			this->button9->TabIndex = 0;
			this->button9->Text = S"Add at the end";
			this->button9->Click += new System::EventHandler(this, button9_Click);
			//
			// panel2
			//
			this->panel2->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel2->Location = System::Drawing::Point(8, 0);
			this->panel2->Name = S"panel2";
			this->panel2->Size = System::Drawing::Size(464, 8);
			this->panel2->TabIndex = 28;
			//
			// panel3
			//
			this->panel3->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel3->Location = System::Drawing::Point(8, 305);
			this->panel3->Name = S"panel3";
			this->panel3->Size = System::Drawing::Size(464, 8);
			this->panel3->TabIndex = 27;
			//
			// panel4
			//
			this->panel4->Dock = System::Windows::Forms::DockStyle::Right;
			this->panel4->Location = System::Drawing::Point(472, 0);
			this->panel4->Name = S"panel4";
			this->panel4->Size = System::Drawing::Size(8, 313);
			this->panel4->TabIndex = 26;
			//
			// panel5
			//
			this->panel5->Dock = System::Windows::Forms::DockStyle::Left;
			this->panel5->Location = System::Drawing::Point(0, 0);
			this->panel5->Name = S"panel5";
			this->panel5->Size = System::Drawing::Size(8, 313);
			this->panel5->TabIndex = 25;
			//
			// tabPage3
			//
			this->tabPage3->Controls->Add(this->panel15);
			this->tabPage3->Controls->Add(this->panel14);
			this->tabPage3->Controls->Add(this->chkLbItems);
			this->tabPage3->Controls->Add(this->panel6);
			this->tabPage3->Controls->Add(this->panel7);
			this->tabPage3->Controls->Add(this->panel8);
			this->tabPage3->Controls->Add(this->panel13);
			this->tabPage3->Location = System::Drawing::Point(4, 25);
			this->tabPage3->Name = S"tabPage3";
			this->tabPage3->Size = System::Drawing::Size(480, 313);
			this->tabPage3->TabIndex = 3;
			this->tabPage3->Text = S"Items";
			//
			// panel15
			//
			this->panel15->Controls->Add(this->cBupdateIndex);
			this->panel15->Controls->Add(this->groupBox3);
			this->panel15->Controls->Add(this->groupBox2);
			this->panel15->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel15->Location = System::Drawing::Point(200, 8);
			this->panel15->Name = S"panel15";
			this->panel15->Size = System::Drawing::Size(272, 297);
			this->panel15->TabIndex = 36;
			//
			// cBupdateIndex
			//
			this->cBupdateIndex->Dock = System::Windows::Forms::DockStyle::Fill;
			this->cBupdateIndex->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->cBupdateIndex->Location = System::Drawing::Point(0, 264);
			this->cBupdateIndex->Name = S"cBupdateIndex";
			this->cBupdateIndex->Size = System::Drawing::Size(272, 33);
			this->cBupdateIndex->TabIndex = 37;
			this->cBupdateIndex->Text = S"Update global Index on selection.";
			//
			// groupBox3
			//
			this->groupBox3->Controls->Add(this->cBremoveData);
			this->groupBox3->Controls->Add(this->button5);
			this->groupBox3->Controls->Add(this->button4);
			this->groupBox3->Controls->Add(this->button2);
			this->groupBox3->Dock = System::Windows::Forms::DockStyle::Top;
			this->groupBox3->Location = System::Drawing::Point(0, 152);
			this->groupBox3->Name = S"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(272, 112);
			this->groupBox3->TabIndex = 36;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = S"Item Control";
			//
			// cBremoveData
			//
			this->cBremoveData->Checked = true;
			this->cBremoveData->CheckState = System::Windows::Forms::CheckState::Checked;
			this->cBremoveData->Enabled = false;
			this->cBremoveData->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->cBremoveData->Location = System::Drawing::Point(16, 80);
			this->cBremoveData->Name = S"cBremoveData";
			this->cBremoveData->Size = System::Drawing::Size(248, 24);
			this->cBremoveData->TabIndex = 4;
			this->cBremoveData->Text = S"Remove frame Data";
			//
			// button5
			//
			this->button5->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button5->Location = System::Drawing::Point(16, 56);
			this->button5->Name = S"button5";
			this->button5->Size = System::Drawing::Size(112, 24);
			this->button5->TabIndex = 2;
			this->button5->Text = S"Delete all Items";
			this->button5->Click += new System::EventHandler(this, button5_Click);
			//
			// button4
			//
			this->button4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button4->Location = System::Drawing::Point(144, 24);
			this->button4->Name = S"button4";
			this->button4->Size = System::Drawing::Size(120, 56);
			this->button4->TabIndex = 1;
			this->button4->Text = S"Update with next imported frame";
			this->button4->Click += new System::EventHandler(this, button4_Click);
			//
			// button2
			//
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button2->Location = System::Drawing::Point(16, 24);
			this->button2->Name = S"button2";
			this->button2->Size = System::Drawing::Size(112, 23);
			this->button2->TabIndex = 0;
			this->button2->Text = S"Delete Item";
			this->button2->Click += new System::EventHandler(this, button2_Click);
			//
			// groupBox2
			//
			this->groupBox2->Controls->Add(this->button7);
			this->groupBox2->Controls->Add(this->button6);
			this->groupBox2->Controls->Add(this->label7);
			this->groupBox2->Controls->Add(this->cBpreviews);
			this->groupBox2->Controls->Add(this->lb_b);
			this->groupBox2->Controls->Add(this->lb_h);
			this->groupBox2->Controls->Add(this->lb_w);
			this->groupBox2->Controls->Add(this->label3);
			this->groupBox2->Controls->Add(this->label2);
			this->groupBox2->Controls->Add(this->label1);
			this->groupBox2->Dock = System::Windows::Forms::DockStyle::Top;
			this->groupBox2->Location = System::Drawing::Point(0, 0);
			this->groupBox2->Name = S"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(272, 152);
			this->groupBox2->TabIndex = 35;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = S"Frame Informations";
			//
			// button7
			//
			this->button7->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button7->Location = System::Drawing::Point(184, 56);
			this->button7->Name = S"button7";
			this->button7->Size = System::Drawing::Size(72, 24);
			this->button7->TabIndex = 39;
			this->button7->Text = S"Preview";
			this->button7->Click += new System::EventHandler(this, button7_Click);
			//
			// button6
			//
			this->button6->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button6->Location = System::Drawing::Point(152, 24);
			this->button6->Name = S"button6";
			this->button6->Size = System::Drawing::Size(104, 24);
			this->button6->TabIndex = 38;
			this->button6->Text = S"Push to Output";
			this->button6->Click += new System::EventHandler(this, button6_Click);
			//
			// label7
			//
			this->label7->AutoSize = true;
			this->label7->Enabled = false;
			this->label7->Location = System::Drawing::Point(160, 128);
			this->label7->Name = S"label7";
			this->label7->Size = System::Drawing::Size(96, 18);
			this->label7->TabIndex = 37;
			this->label7->Text = S"Output Preview";
			//
			// cBpreviews
			//
			this->cBpreviews->BackColor = System::Drawing::Color::FromArgb((System::Byte)192, (System::Byte)255, (System::Byte)192);
			System::Object* __mcTemp__3[] = new System::Object*[1];
			__mcTemp__3[0] = S"NULL";
			this->cBpreviews->Items->AddRange(__mcTemp__3);
			this->cBpreviews->Location = System::Drawing::Point(16, 104);
			this->cBpreviews->Name = S"cBpreviews";
			this->cBpreviews->Size = System::Drawing::Size(240, 24);
			this->cBpreviews->TabIndex = 35;
			this->cBpreviews->Text = S"select Output..";
			//
			// lb_b
			//
			this->lb_b->Location = System::Drawing::Point(72, 64);
			this->lb_b->Name = S"lb_b";
			this->lb_b->Size = System::Drawing::Size(112, 23);
			this->lb_b->TabIndex = 5;
			//
			// lb_h
			//
			this->lb_h->Location = System::Drawing::Point(72, 40);
			this->lb_h->Name = S"lb_h";
			this->lb_h->Size = System::Drawing::Size(72, 23);
			this->lb_h->TabIndex = 4;
			//
			// lb_w
			//
			this->lb_w->Location = System::Drawing::Point(72, 24);
			this->lb_w->Name = S"lb_w";
			this->lb_w->Size = System::Drawing::Size(72, 23);
			this->lb_w->TabIndex = 3;
			//
			// label3
			//
			this->label3->AutoSize = true;
			this->label3->Enabled = false;
			this->label3->Location = System::Drawing::Point(16, 72);
			this->label3->Name = S"label3";
			this->label3->Size = System::Drawing::Size(42, 18);
			this->label3->TabIndex = 2;
			this->label3->Text = S"Bytes:";
			//
			// label2
			//
			this->label2->AutoSize = true;
			this->label2->Enabled = false;
			this->label2->Location = System::Drawing::Point(16, 48);
			this->label2->Name = S"label2";
			this->label2->Size = System::Drawing::Size(47, 18);
			this->label2->TabIndex = 1;
			this->label2->Text = S"Height:";
			//
			// label1
			//
			this->label1->AutoSize = true;
			this->label1->Enabled = false;
			this->label1->Location = System::Drawing::Point(16, 24);
			this->label1->Name = S"label1";
			this->label1->Size = System::Drawing::Size(43, 18);
			this->label1->TabIndex = 0;
			this->label1->Text = S"Width:";
			//
			// panel14
			//
			this->panel14->Dock = System::Windows::Forms::DockStyle::Left;
			this->panel14->Location = System::Drawing::Point(192, 8);
			this->panel14->Name = S"panel14";
			this->panel14->Size = System::Drawing::Size(8, 297);
			this->panel14->TabIndex = 35;
			//
			// chkLbItems
			//
			this->chkLbItems->BackColor = System::Drawing::Color::FromArgb((System::Byte)255, (System::Byte)224, (System::Byte)192);
			this->chkLbItems->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->chkLbItems->Dock = System::Windows::Forms::DockStyle::Left;
			this->chkLbItems->Location = System::Drawing::Point(8, 8);
			this->chkLbItems->Name = S"chkLbItems";
			this->chkLbItems->Size = System::Drawing::Size(184, 297);
			this->chkLbItems->TabIndex = 34;
			this->chkLbItems->SelectedIndexChanged += new System::EventHandler(this, chkLbItems_SelectedIndexChanged);
			//
			// panel6
			//
			this->panel6->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel6->Location = System::Drawing::Point(8, 0);
			this->panel6->Name = S"panel6";
			this->panel6->Size = System::Drawing::Size(464, 8);
			this->panel6->TabIndex = 32;
			//
			// panel7
			//
			this->panel7->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel7->Location = System::Drawing::Point(8, 305);
			this->panel7->Name = S"panel7";
			this->panel7->Size = System::Drawing::Size(464, 8);
			this->panel7->TabIndex = 31;
			//
			// panel8
			//
			this->panel8->Dock = System::Windows::Forms::DockStyle::Right;
			this->panel8->Location = System::Drawing::Point(472, 0);
			this->panel8->Name = S"panel8";
			this->panel8->Size = System::Drawing::Size(8, 313);
			this->panel8->TabIndex = 30;
			//
			// panel13
			//
			this->panel13->Dock = System::Windows::Forms::DockStyle::Left;
			this->panel13->Location = System::Drawing::Point(0, 0);
			this->panel13->Name = S"panel13";
			this->panel13->Size = System::Drawing::Size(8, 313);
			this->panel13->TabIndex = 29;
			//
			// tabPage5
			//
			this->tabPage5->Controls->Add(this->rTBinfo);
			this->tabPage5->Controls->Add(this->panel9);
			this->tabPage5->Controls->Add(this->panel10);
			this->tabPage5->Controls->Add(this->panel11);
			this->tabPage5->Controls->Add(this->panel12);
			this->tabPage5->Location = System::Drawing::Point(4, 25);
			this->tabPage5->Name = S"tabPage5";
			this->tabPage5->Size = System::Drawing::Size(480, 313);
			this->tabPage5->TabIndex = 5;
			this->tabPage5->Text = S"Module Informations";
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
			this->rTBinfo->Size = System::Drawing::Size(464, 297);
			this->rTBinfo->TabIndex = 32;
			this->rTBinfo->Text = S"";
			//
			// panel9
			//
			this->panel9->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel9->Location = System::Drawing::Point(8, 0);
			this->panel9->Name = S"panel9";
			this->panel9->Size = System::Drawing::Size(464, 8);
			this->panel9->TabIndex = 30;
			//
			// panel10
			//
			this->panel10->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel10->Location = System::Drawing::Point(8, 305);
			this->panel10->Name = S"panel10";
			this->panel10->Size = System::Drawing::Size(464, 8);
			this->panel10->TabIndex = 29;
			//
			// panel11
			//
			this->panel11->Dock = System::Windows::Forms::DockStyle::Right;
			this->panel11->Location = System::Drawing::Point(472, 0);
			this->panel11->Name = S"panel11";
			this->panel11->Size = System::Drawing::Size(8, 313);
			this->panel11->TabIndex = 28;
			//
			// panel12
			//
			this->panel12->Dock = System::Windows::Forms::DockStyle::Left;
			this->panel12->Location = System::Drawing::Point(0, 0);
			this->panel12->Name = S"panel12";
			this->panel12->Size = System::Drawing::Size(8, 313);
			this->panel12->TabIndex = 27;
			//
			// bufferForm
			//
			this->AutoScaleBaseSize = System::Drawing::Size(6, 15);
			this->ClientSize = System::Drawing::Size(488, 430);
			this->Controls->Add(this->tabControl1);
			this->Controls->Add(this->panel1);
			this->Icon = (__try_cast<System::Drawing::Icon *  >(resources->GetObject(S"$this.Icon")));
			this->Name = S"bufferForm";
			this->Text = S"vipBuffer Interface 1.0";
			this->Closing += new System::ComponentModel::CancelEventHandler(this, bufferForm_Closing);
			this->Load += new System::EventHandler(this, bufferForm_Load);
			this->panel1->ResumeLayout(false);
			this->tabControl1->ResumeLayout(false);
			this->tabPage2->ResumeLayout(false);
			this->groupBox1->ResumeLayout(false);
			(__try_cast<System::ComponentModel::ISupportInitialize *  >(this->tBindex))->EndInit();
			(__try_cast<System::ComponentModel::ISupportInitialize *  >(this->nUDindex))->EndInit();
			this->panel18->ResumeLayout(false);
			this->groupBox5->ResumeLayout(false);
			this->groupBox4->ResumeLayout(false);
			this->tabPage3->ResumeLayout(false);
			this->panel15->ResumeLayout(false);
			this->groupBox3->ResumeLayout(false);
			this->groupBox2->ResumeLayout(false);
			this->tabPage5->ResumeLayout(false);
			this->ResumeLayout(false);

		}




		//
private: System::Void bufferForm_Load(System::Object *  sender, System::EventArgs *  e);



private: System::Void button1_Click(System::Object *  sender, System::EventArgs *  e);

private: System::Void button3_Click(System::Object *  sender, System::EventArgs *  e);

private: void updateItems(void);
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
				int oldSel2 = cBpreviews->SelectedIndex;

				cBviews->Items->Clear();
				cBpreviews->Items->Clear();
				cBviews->Items->Add( new System::String("NULL Output") );
				for (int i=0; i<this->MdiParent->MdiChildren->Count; i++)
				 {
					if (  this->MdiParent->MdiChildren->get_Item(i)->GetType()->GetInterface("outputInterface") &&
						 !this->MdiParent->MdiChildren->get_Item(i)->Equals(this) )
						cBviews->Items->Add( ( static_cast<Form*> (this->MdiParent->MdiChildren->get_Item(i)) )->Text );

					if ( this->MdiParent->MdiChildren->get_Item(i)->GetType()->Name->Equals(S"viewForm") )
						cBpreviews->Items->Add( ( static_cast<Form*> (this->MdiParent->MdiChildren->get_Item(i)) )->Text );
				 }
				if ( oldSel < 1 && cBviews->Items->Count == 2 )
					oldSel = 1;
				else if ( oldSel >= cBviews->Items->Count )
					oldSel = cBviews->Items->Count-1;
				cBviews->SelectedIndex = oldSel;
				if ( oldSel2 >= cBpreviews->Items->Count )
					oldSel2 = cBpreviews->Items->Count-1;
				cBpreviews->SelectedIndex = oldSel2;
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


private: System::Void button6_Click(System::Object *  sender, System::EventArgs *  e);

private: System::Void button7_Click(System::Object *  sender, System::EventArgs *  e);

private: System::Void chkLbItems_SelectedIndexChanged(System::Object *  sender, System::EventArgs *  e);

private: System::Void button2_Click(System::Object *  sender, System::EventArgs *  e);

private: System::Void button5_Click(System::Object *  sender, System::EventArgs *  e);

private: System::Void button4_Click(System::Object *  sender, System::EventArgs *  e);


private: System::Void button8_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			updateItems();
		 }

private: System::Void nUDindex_ValueChanged(System::Object *  sender, System::EventArgs *  e)
		 {
			 myBuffer->goToFrame( Convert::ToInt32(nUDindex->Value) );
			 tBindex->Value = Convert::ToInt16(nUDindex->Value);
			nUDindex->Enabled = true;
		 }

private: System::Void tBindex_ValueChanged(System::Object *  sender, System::EventArgs *  e)
		 {
			myBuffer->goToFrame( Convert::ToInt32(tBindex->Value) );
			if (tBindex->Value == -1)
				 nUDindex->Enabled = false;
			else
			 {
				nUDindex->Value = tBindex->Value;
				nUDindex->Enabled = true;
			 }
		 }

private: System::Void button9_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 //
		 }

private: System::Void bufferForm_Closing(System::Object *  sender, System::ComponentModel::CancelEventArgs *  e);


};
}
