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

class vipFrameRGB24;

namespace vipWS3
{
	/// <summary>
	/// Riepilogo per sourceForm
	///
	/// AVVISO: se si modifica il nome della classe, sarà necessario modificare la
	///          proprietà "Nome file di risorse" relativa allo strumento di compilazione delle risorse gestite
	///          associato a tutti i file RESX da cui dipende la classe. In caso contrario,
	///          le finestre di progettazione non saranno in grado di interagire correttamente con le
	///          risorse localizzate associate al form.
	/// </summary>
	public __gc class sourceForm : public System::Windows::Forms::Form, public sourceInterface
	{
	public:
		sourceForm(void);

		void Init(vipInput* myInputInstance, loaderDLL* myPlugInObj);
		void Init() {};

		VIPRESULT extractTo(vipFrameRGB24* img);


	protected:
		void Dispose(Boolean disposing);

	private: vipInput* myInput;
	private: loaderDLL* myObj;
	private: __vipPlugInFuncInfo** func_infoAr;
	private: int func_infoCount;
	private: outputInterface* vF;
	private: vipFrameRGB24* buffer;

	private: System::Windows::Forms::Panel *  panel1;
	private: System::Windows::Forms::TabControl *  tabControl1;
	private: System::Windows::Forms::TabPage *  tabPage1;
	private: System::Windows::Forms::TabPage *  tabPage2;
	private: System::Windows::Forms::ListBox *  lBstreamInfo;
	private: System::Windows::Forms::TabPage *  tabPage3;
	private: System::Windows::Forms::RichTextBox *  rTBinfo;
	private: System::Windows::Forms::Label *  label1;
	private: System::Windows::Forms::NumericUpDown *  nUDfps;
	private: System::Windows::Forms::Button *  button5;
	private: System::Windows::Forms::ComboBox *  cBviews;
	private: System::Windows::Forms::ContextMenu *  contextMenu1;
	private: System::Windows::Forms::MenuItem *  menuItem3;
	private: System::Windows::Forms::MenuItem *  menuItem1;
	private: System::Windows::Forms::MenuItem *  menuItem2;
	private: System::Windows::Forms::MenuItem *  menuItem4;
	private: System::Windows::Forms::MenuItem *  menuItem5;
	private: System::Windows::Forms::Button *  button6;
	private: System::Windows::Forms::Panel *  panel20;
	private: System::Windows::Forms::GroupBox *  groupBox1;
	private: System::Windows::Forms::TextBox *  tBreturn;
	private: System::Windows::Forms::Label *  lReturn;
	private: System::Windows::Forms::Panel *  panel19;
	private: System::Windows::Forms::GroupBox *  groupBox2;
	private: System::Windows::Forms::Label *  lParam;
	private: System::Windows::Forms::TextBox *  tBparam1;
	private: System::Windows::Forms::Panel *  panel18;
	private: System::Windows::Forms::ListBox *  lBcb;
	private: System::Windows::Forms::Label *  lDef;
	private: System::Windows::Forms::Panel *  panel15;
	private: System::Windows::Forms::Panel *  panel16;
	private: System::Windows::Forms::Panel *  panel17;
	private: System::Windows::Forms::Panel *  panel14;
	private: System::Windows::Forms::Button *  button8;
	private: System::Windows::Forms::CheckBox *  checkBox1;


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
			System::Resources::ResourceManager *  resources = new System::Resources::ResourceManager(__typeof(vipWS3::sourceForm));
			this->panel1 = new System::Windows::Forms::Panel();
			this->label1 = new System::Windows::Forms::Label();
			this->nUDfps = new System::Windows::Forms::NumericUpDown();
			this->button5 = new System::Windows::Forms::Button();
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
			this->checkBox1 = new System::Windows::Forms::CheckBox();
			this->button8 = new System::Windows::Forms::Button();
			this->tabPage2 = new System::Windows::Forms::TabPage();
			this->lBstreamInfo = new System::Windows::Forms::ListBox();
			this->tabPage3 = new System::Windows::Forms::TabPage();
			this->rTBinfo = new System::Windows::Forms::RichTextBox();
			this->contextMenu1 = new System::Windows::Forms::ContextMenu();
			this->menuItem3 = new System::Windows::Forms::MenuItem();
			this->menuItem1 = new System::Windows::Forms::MenuItem();
			this->menuItem2 = new System::Windows::Forms::MenuItem();
			this->menuItem4 = new System::Windows::Forms::MenuItem();
			this->menuItem5 = new System::Windows::Forms::MenuItem();
			this->panel1->SuspendLayout();
			(__try_cast<System::ComponentModel::ISupportInitialize *  >(this->nUDfps))->BeginInit();
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->panel14->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->tabPage3->SuspendLayout();
			this->SuspendLayout();
			//
			// panel1
			//
			this->panel1->Controls->Add(this->label1);
			this->panel1->Controls->Add(this->nUDfps);
			this->panel1->Controls->Add(this->button5);
			this->panel1->Controls->Add(this->cBviews);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel1->Location = System::Drawing::Point(0, 296);
			this->panel1->Name = S"panel1";
			this->panel1->Size = System::Drawing::Size(394, 72);
			this->panel1->TabIndex = 0;
			//
			// label1
			//
			this->label1->AutoSize = true;
			this->label1->Enabled = false;
			this->label1->Location = System::Drawing::Point(296, 48);
			this->label1->Name = S"label1";
			this->label1->Size = System::Drawing::Size(23, 18);
			this->label1->TabIndex = 8;
			this->label1->Text = S"fps";
			//
			// nUDfps
			//
			this->nUDfps->BackColor = System::Drawing::Color::FromArgb((System::Byte)255, (System::Byte)224, (System::Byte)192);
			this->nUDfps->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->nUDfps->DecimalPlaces = 2;
			this->nUDfps->Location = System::Drawing::Point(320, 40);
			System::Int32 __mcTemp__1[] = new System::Int32[4];
			__mcTemp__1[0] = 50;
			__mcTemp__1[1] = 0;
			__mcTemp__1[2] = 0;
			__mcTemp__1[3] = 0;
			this->nUDfps->Maximum = System::Decimal(__mcTemp__1);
			this->nUDfps->Name = S"nUDfps";
			this->nUDfps->Size = System::Drawing::Size(64, 22);
			this->nUDfps->TabIndex = 7;
			System::Int32 __mcTemp__2[] = new System::Int32[4];
			__mcTemp__2[0] = 5;
			__mcTemp__2[1] = 0;
			__mcTemp__2[2] = 0;
			__mcTemp__2[3] = 0;
			this->nUDfps->Value = System::Decimal(__mcTemp__2);
			//
			// button5
			//
			this->button5->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->button5->Location = System::Drawing::Point(8, 39);
			this->button5->Name = S"button5";
			this->button5->Size = System::Drawing::Size(272, 22);
			this->button5->TabIndex = 6;
			this->button5->Text = S"Extract..";
			this->button5->Click += new System::EventHandler(this, button5_Click);
			//
			// cBviews
			//
			this->cBviews->BackColor = System::Drawing::Color::FromArgb((System::Byte)192, (System::Byte)255, (System::Byte)192);
			this->cBviews->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			System::Object* __mcTemp__3[] = new System::Object*[1];
			__mcTemp__3[0] = S"NULL";
			this->cBviews->Items->AddRange(__mcTemp__3);
			this->cBviews->Location = System::Drawing::Point(8, 7);
			this->cBviews->Name = S"cBviews";
			this->cBviews->Size = System::Drawing::Size(376, 24);
			this->cBviews->TabIndex = 5;
			this->cBviews->SelectedIndexChanged += new System::EventHandler(this, cBviews_SelectedIndexChanged);
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
			this->tabControl1->Size = System::Drawing::Size(394, 296);
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
			this->tabPage1->Size = System::Drawing::Size(386, 267);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = S"Settings";
			//
			// button6
			//
			this->button6->Dock = System::Windows::Forms::DockStyle::Top;
			this->button6->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button6->Location = System::Drawing::Point(192, 140);
			this->button6->Name = S"button6";
			this->button6->Size = System::Drawing::Size(186, 32);
			this->button6->TabIndex = 56;
			this->button6->Text = S"Invoke Function";
			this->button6->Click += new System::EventHandler(this, button6_Click);
			//
			// panel20
			//
			this->panel20->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel20->Location = System::Drawing::Point(192, 132);
			this->panel20->Name = S"panel20";
			this->panel20->Size = System::Drawing::Size(186, 8);
			this->panel20->TabIndex = 55;
			//
			// groupBox1
			//
			this->groupBox1->Controls->Add(this->tBreturn);
			this->groupBox1->Controls->Add(this->lReturn);
			this->groupBox1->Dock = System::Windows::Forms::DockStyle::Top;
			this->groupBox1->Location = System::Drawing::Point(192, 72);
			this->groupBox1->Name = S"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(186, 60);
			this->groupBox1->TabIndex = 54;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = S"Return Value";
			//
			// tBreturn
			//
			this->tBreturn->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->tBreturn->Location = System::Drawing::Point(112, 16);
			this->tBreturn->Name = S"tBreturn";
			this->tBreturn->ReadOnly = true;
			this->tBreturn->Size = System::Drawing::Size(64, 22);
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
			this->panel19->Size = System::Drawing::Size(186, 8);
			this->panel19->TabIndex = 53;
			//
			// groupBox2
			//
			this->groupBox2->Controls->Add(this->lParam);
			this->groupBox2->Controls->Add(this->tBparam1);
			this->groupBox2->Dock = System::Windows::Forms::DockStyle::Top;
			this->groupBox2->Location = System::Drawing::Point(192, 8);
			this->groupBox2->Name = S"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(186, 56);
			this->groupBox2->TabIndex = 52;
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
			this->tBparam1->Size = System::Drawing::Size(64, 22);
			this->tBparam1->TabIndex = 27;
			this->tBparam1->Text = S"";
			//
			// panel18
			//
			this->panel18->Dock = System::Windows::Forms::DockStyle::Left;
			this->panel18->Location = System::Drawing::Point(184, 8);
			this->panel18->Name = S"panel18";
			this->panel18->Size = System::Drawing::Size(8, 179);
			this->panel18->TabIndex = 51;
			//
			// lBcb
			//
			this->lBcb->BackColor = System::Drawing::Color::FromArgb((System::Byte)255, (System::Byte)224, (System::Byte)192);
			this->lBcb->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lBcb->Dock = System::Windows::Forms::DockStyle::Left;
			this->lBcb->ItemHeight = 16;
			this->lBcb->Location = System::Drawing::Point(8, 8);
			this->lBcb->Name = S"lBcb";
			this->lBcb->Size = System::Drawing::Size(176, 178);
			this->lBcb->TabIndex = 50;
			this->lBcb->SelectedIndexChanged += new System::EventHandler(this, lBcb_SelectedIndexChanged);
			//
			// lDef
			//
			this->lDef->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->lDef->Location = System::Drawing::Point(8, 187);
			this->lDef->Name = S"lDef";
			this->lDef->Size = System::Drawing::Size(370, 32);
			this->lDef->TabIndex = 49;
			//
			// panel15
			//
			this->panel15->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel15->Location = System::Drawing::Point(8, 0);
			this->panel15->Name = S"panel15";
			this->panel15->Size = System::Drawing::Size(370, 8);
			this->panel15->TabIndex = 48;
			//
			// panel16
			//
			this->panel16->Dock = System::Windows::Forms::DockStyle::Right;
			this->panel16->Location = System::Drawing::Point(378, 0);
			this->panel16->Name = S"panel16";
			this->panel16->Size = System::Drawing::Size(8, 219);
			this->panel16->TabIndex = 47;
			//
			// panel17
			//
			this->panel17->Dock = System::Windows::Forms::DockStyle::Left;
			this->panel17->Location = System::Drawing::Point(0, 0);
			this->panel17->Name = S"panel17";
			this->panel17->Size = System::Drawing::Size(8, 219);
			this->panel17->TabIndex = 46;
			//
			// panel14
			//
			this->panel14->Controls->Add(this->checkBox1);
			this->panel14->Controls->Add(this->button8);
			this->panel14->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel14->Location = System::Drawing::Point(0, 219);
			this->panel14->Name = S"panel14";
			this->panel14->Size = System::Drawing::Size(386, 48);
			this->panel14->TabIndex = 45;
			//
			// checkBox1
			//
			this->checkBox1->Enabled = false;
			this->checkBox1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->checkBox1->Location = System::Drawing::Point(192, 8);
			this->checkBox1->Name = S"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(184, 32);
			this->checkBox1->TabIndex = 3;
			this->checkBox1->Text = S"Delegate frame rate control to Input.";
			//
			// button8
			//
			this->button8->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button8->Location = System::Drawing::Point(8, 8);
			this->button8->Name = S"button8";
			this->button8->Size = System::Drawing::Size(176, 32);
			this->button8->TabIndex = 2;
			this->button8->Text = S"Setup..";
			this->button8->Click += new System::EventHandler(this, button8_Click);
			//
			// tabPage2
			//
			this->tabPage2->Controls->Add(this->lBstreamInfo);
			this->tabPage2->Location = System::Drawing::Point(4, 25);
			this->tabPage2->Name = S"tabPage2";
			this->tabPage2->Size = System::Drawing::Size(386, 267);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = S"Stream Informations";
			//
			// lBstreamInfo
			//
			this->lBstreamInfo->BackColor = System::Drawing::Color::FromArgb((System::Byte)255, (System::Byte)224, (System::Byte)192);
			this->lBstreamInfo->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lBstreamInfo->ColumnWidth = 100;
			this->lBstreamInfo->ItemHeight = 16;
			this->lBstreamInfo->Location = System::Drawing::Point(8, 8);
			this->lBstreamInfo->MultiColumn = true;
			this->lBstreamInfo->Name = S"lBstreamInfo";
			this->lBstreamInfo->Size = System::Drawing::Size(328, 194);
			this->lBstreamInfo->TabIndex = 0;
			//
			// tabPage3
			//
			this->tabPage3->Controls->Add(this->rTBinfo);
			this->tabPage3->Location = System::Drawing::Point(4, 25);
			this->tabPage3->Name = S"tabPage3";
			this->tabPage3->Size = System::Drawing::Size(386, 267);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = S"Module Informations";
			//
			// rTBinfo
			//
			this->rTBinfo->BackColor = System::Drawing::Color::FromArgb((System::Byte)255, (System::Byte)224, (System::Byte)192);
			this->rTBinfo->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->rTBinfo->Location = System::Drawing::Point(8, 8);
			this->rTBinfo->Name = S"rTBinfo";
			this->rTBinfo->ReadOnly = true;
			this->rTBinfo->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::Vertical;
			this->rTBinfo->Size = System::Drawing::Size(328, 192);
			this->rTBinfo->TabIndex = 0;
			this->rTBinfo->Text = S"";
			this->rTBinfo->LinkClicked += new System::Windows::Forms::LinkClickedEventHandler(this, rTBinfo_LinkClicked);
			//
			// contextMenu1
			//
			System::Windows::Forms::MenuItem* __mcTemp__4[] = new System::Windows::Forms::MenuItem*[5];
			__mcTemp__4[0] = this->menuItem3;
			__mcTemp__4[1] = this->menuItem1;
			__mcTemp__4[2] = this->menuItem2;
			__mcTemp__4[3] = this->menuItem4;
			__mcTemp__4[4] = this->menuItem5;
			this->contextMenu1->MenuItems->AddRange(__mcTemp__4);
			//
			// menuItem3
			//
			this->menuItem3->Index = 0;
			this->menuItem3->Text = S"1 frame";
			this->menuItem3->Click += new System::EventHandler(this, button5_Click);
			//
			// menuItem1
			//
			this->menuItem1->Index = 1;
			this->menuItem1->Text = S"10 frames";
			this->menuItem1->Click += new System::EventHandler(this, menuItem1_Click);
			//
			// menuItem2
			//
			this->menuItem2->Index = 2;
			this->menuItem2->Text = S"100 Frames";
			this->menuItem2->Click += new System::EventHandler(this, menuItem2_Click);
			//
			// menuItem4
			//
			this->menuItem4->Index = 3;
			this->menuItem4->Text = S"500 Frames";
			this->menuItem4->Click += new System::EventHandler(this, menuItem4_Click);
			//
			// menuItem5
			//
			this->menuItem5->Index = 4;
			this->menuItem5->Text = S"1000 Frames";
			this->menuItem5->Click += new System::EventHandler(this, menuItem5_Click);
			//
			// sourceForm
			//
			this->AutoScaleBaseSize = System::Drawing::Size(6, 15);
			this->ClientSize = System::Drawing::Size(394, 368);
			this->Controls->Add(this->tabControl1);
			this->Controls->Add(this->panel1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (__try_cast<System::Drawing::Icon *  >(resources->GetObject(S"$this.Icon")));
			this->Name = S"sourceForm";
			this->Text = S"vipInput Interface 1.0";
			this->Closing += new System::ComponentModel::CancelEventHandler(this, sourceForm_Closing);
			this->Load += new System::EventHandler(this, sourceForm_Load);
			this->panel1->ResumeLayout(false);
			(__try_cast<System::ComponentModel::ISupportInitialize *  >(this->nUDfps))->EndInit();
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->groupBox1->ResumeLayout(false);
			this->groupBox2->ResumeLayout(false);
			this->panel14->ResumeLayout(false);
			this->tabPage2->ResumeLayout(false);
			this->tabPage3->ResumeLayout(false);
			this->ResumeLayout(false);

		}








		//
private: System::Void sourceForm_Load(System::Object *  sender, System::EventArgs *  e);

private: System::Void rTBinfo_LinkClicked(System::Object *  sender, System::Windows::Forms::LinkClickedEventArgs *  e)
		 {
			 System::Diagnostics::Process::Start(e->LinkText);
		 }



private: System::Void button5_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			this->Cursor = Cursors::WaitCursor;
			pushFrames(1);
			this->Cursor = Cursors::Default;
		 }

private: System::Void menuItem1_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			this->Cursor = Cursors::WaitCursor;
			pushFrames(10);
			this->Cursor = Cursors::Default;
		 }

private: System::Void menuItem2_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			this->Cursor = Cursors::WaitCursor;
			pushFrames(100);
			this->Cursor = Cursors::Default;
		 }

private: System::Void menuItem4_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			this->Cursor = Cursors::WaitCursor;
			pushFrames(500);
			this->Cursor = Cursors::Default;
		 }

private: System::Void menuItem5_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			this->Cursor = Cursors::WaitCursor;
			pushFrames(1000);
			this->Cursor = Cursors::Default;
		 }


private: System::Void pushFrames(int iLoop);


private: System::Void button8_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 int res = myObj->openSetupDialog();
			 if ( res < 0 )
				 MessageBox::Show(this, S"Cannot open Input Setup Dialog!\r\nMaybe it's not available for this plugin.", this->Text);
			 else if ( res > 0 )
				 MessageBox::Show(this, S"Input Setup Dialog returned ad error!", this->Text);

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

/////////////////////////////////////////////////////////////////////////////////
/////////// same for all data sources:
public: outputInterface* getOutputInterface() { return vF; }
public: System::Object __gc* getObjectInstance() { return this; };

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



private: System::Void sourceForm_Closing(System::Object *  sender, System::ComponentModel::CancelEventArgs *  e);

};
}
