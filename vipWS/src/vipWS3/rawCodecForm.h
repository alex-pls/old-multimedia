#pragma once
#include "../../../../source/codecs/vipCodec_RAW.h"
#include "sourceInterface.h"
#include "outputInterface.h"


using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace vipWS3
{
	/// <summary>
	/// Riepilogo per rawCodecForm
	///
	/// AVVISO: se si modifica il nome della classe, sarà necessario modificare la
	///          proprietà "Nome file di risorse" relativa allo strumento di compilazione delle risorse gestite
	///          associato a tutti i file RESX da cui dipende la classe. In caso contrario,
	///          le finestre di progettazione non saranno in grado di interagire correttamente con le
	///          risorse localizzate associate al form.
	/// </summary>
	public __gc class rawCodecForm : public System::Windows::Forms::Form, public sourceInterface
	{
	public:
		rawCodecForm(void);

		void Init(void);

		VIPRESULT extractTo(vipFrameRGB24* img);

	protected:
		void Dispose(Boolean disposing);

	private: vipCodec_RAW* myXVID;
	private: vipFrameRGB24* buffer;
	private: outputInterface* vF;
	private: String* lastPath;


















	private: System::Windows::Forms::Panel *  panel1;
	private: System::Windows::Forms::Label *  label1;
	private: System::Windows::Forms::NumericUpDown *  nUDfps;
	private: System::Windows::Forms::Button *  button5;
	private: System::Windows::Forms::ComboBox *  cBviews;
	private: System::Windows::Forms::ContextMenu *  contextMenu1;
	private: System::Windows::Forms::MenuItem *  menuItem3;
	private: System::Windows::Forms::MenuItem *  menuItem1;
	private: System::Windows::Forms::MenuItem *  menuItem2;
	private: System::Windows::Forms::OpenFileDialog *  openFileDialog1;
	private: System::Windows::Forms::TabControl *  tabControl1;
	private: System::Windows::Forms::TabPage *  tabPage1;





	private: System::Windows::Forms::Button *  button1;
	private: System::Windows::Forms::TabPage *  tabPage2;
	private: System::Windows::Forms::ListBox *  lBstreamInfo;
	private: System::Windows::Forms::Panel *  panel6;
	private: System::Windows::Forms::Panel *  panel7;
	private: System::Windows::Forms::Panel *  panel8;
	private: System::Windows::Forms::Panel *  panel9;
	private: System::Windows::Forms::TabPage *  tabPage3;
	private: System::Windows::Forms::RichTextBox *  rTBinfo;
	private: System::Windows::Forms::Panel *  panel5;
	private: System::Windows::Forms::Panel *  panel4;
	private: System::Windows::Forms::Panel *  panel3;
	private: System::Windows::Forms::Panel *  panel2;

	private: System::Windows::Forms::Panel *  panel13;
	private: System::Windows::Forms::Panel *  panel14;
	private: System::Windows::Forms::Panel *  panel10;
	private: System::Windows::Forms::TrackBar *  tBarStream;
	private: System::Windows::Forms::Label *  lbStream;
	private: System::Windows::Forms::Panel *  panel11;

	private: System::Windows::Forms::TextBox *  tBpath;
	private: System::Windows::Forms::Panel *  panel12;
	private: System::Windows::Forms::Button *  button2;
	private: System::Windows::Forms::Label *  label2;
	private: System::Windows::Forms::MenuItem *  menuItem4;
	private: System::Windows::Forms::MenuItem *  menuItem5;







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
			System::Resources::ResourceManager *  resources = new System::Resources::ResourceManager(__typeof(vipWS3::rawCodecForm));
			this->panel1 = new System::Windows::Forms::Panel();
			this->label1 = new System::Windows::Forms::Label();
			this->nUDfps = new System::Windows::Forms::NumericUpDown();
			this->button5 = new System::Windows::Forms::Button();
			this->contextMenu1 = new System::Windows::Forms::ContextMenu();
			this->menuItem3 = new System::Windows::Forms::MenuItem();
			this->menuItem1 = new System::Windows::Forms::MenuItem();
			this->menuItem2 = new System::Windows::Forms::MenuItem();
			this->menuItem4 = new System::Windows::Forms::MenuItem();
			this->menuItem5 = new System::Windows::Forms::MenuItem();
			this->cBviews = new System::Windows::Forms::ComboBox();
			this->openFileDialog1 = new System::Windows::Forms::OpenFileDialog();
			this->tabControl1 = new System::Windows::Forms::TabControl();
			this->tabPage1 = new System::Windows::Forms::TabPage();
			this->panel12 = new System::Windows::Forms::Panel();
			this->label2 = new System::Windows::Forms::Label();
			this->button2 = new System::Windows::Forms::Button();
			this->tBpath = new System::Windows::Forms::TextBox();
			this->panel10 = new System::Windows::Forms::Panel();
			this->lbStream = new System::Windows::Forms::Label();
			this->tBarStream = new System::Windows::Forms::TrackBar();
			this->panel11 = new System::Windows::Forms::Panel();
			this->panel13 = new System::Windows::Forms::Panel();
			this->panel14 = new System::Windows::Forms::Panel();
			this->button1 = new System::Windows::Forms::Button();
			this->tabPage2 = new System::Windows::Forms::TabPage();
			this->lBstreamInfo = new System::Windows::Forms::ListBox();
			this->panel6 = new System::Windows::Forms::Panel();
			this->panel7 = new System::Windows::Forms::Panel();
			this->panel8 = new System::Windows::Forms::Panel();
			this->panel9 = new System::Windows::Forms::Panel();
			this->tabPage3 = new System::Windows::Forms::TabPage();
			this->rTBinfo = new System::Windows::Forms::RichTextBox();
			this->panel5 = new System::Windows::Forms::Panel();
			this->panel4 = new System::Windows::Forms::Panel();
			this->panel3 = new System::Windows::Forms::Panel();
			this->panel2 = new System::Windows::Forms::Panel();
			this->panel1->SuspendLayout();
			(__try_cast<System::ComponentModel::ISupportInitialize *  >(this->nUDfps))->BeginInit();
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->panel12->SuspendLayout();
			this->panel10->SuspendLayout();
			(__try_cast<System::ComponentModel::ISupportInitialize *  >(this->tBarStream))->BeginInit();
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
			this->panel1->Location = System::Drawing::Point(0, 246);
			this->panel1->Name = S"panel1";
			this->panel1->Size = System::Drawing::Size(312, 63);
			this->panel1->TabIndex = 3;
			//
			// label1
			//
			this->label1->AutoSize = true;
			this->label1->Enabled = false;
			this->label1->Location = System::Drawing::Point(233, 42);
			this->label1->Name = S"label1";
			this->label1->Size = System::Drawing::Size(19, 16);
			this->label1->TabIndex = 4;
			this->label1->Text = S"fps";
			//
			// nUDfps
			//
			this->nUDfps->BackColor = System::Drawing::Color::FromArgb((System::Byte)255, (System::Byte)224, (System::Byte)192);
			this->nUDfps->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->nUDfps->DecimalPlaces = 2;
			this->nUDfps->Location = System::Drawing::Point(253, 35);
			System::Int32 __mcTemp__1[] = new System::Int32[4];
			__mcTemp__1[0] = 50;
			__mcTemp__1[1] = 0;
			__mcTemp__1[2] = 0;
			__mcTemp__1[3] = 0;
			this->nUDfps->Maximum = System::Decimal(__mcTemp__1);
			this->nUDfps->Name = S"nUDfps";
			this->nUDfps->Size = System::Drawing::Size(54, 20);
			this->nUDfps->TabIndex = 3;
			System::Int32 __mcTemp__2[] = new System::Int32[4];
			__mcTemp__2[0] = 5;
			__mcTemp__2[1] = 0;
			__mcTemp__2[2] = 0;
			__mcTemp__2[3] = 0;
			this->nUDfps->Value = System::Decimal(__mcTemp__2);
			//
			// button5
			//
			this->button5->ContextMenu = this->contextMenu1;
			this->button5->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->button5->Location = System::Drawing::Point(7, 35);
			this->button5->Name = S"button5";
			this->button5->Size = System::Drawing::Size(213, 19);
			this->button5->TabIndex = 2;
			this->button5->Text = S"Extract";
			this->button5->Click += new System::EventHandler(this, button5_Click);
			//
			// contextMenu1
			//
			System::Windows::Forms::MenuItem* __mcTemp__3[] = new System::Windows::Forms::MenuItem*[5];
			__mcTemp__3[0] = this->menuItem3;
			__mcTemp__3[1] = this->menuItem1;
			__mcTemp__3[2] = this->menuItem2;
			__mcTemp__3[3] = this->menuItem4;
			__mcTemp__3[4] = this->menuItem5;
			this->contextMenu1->MenuItems->AddRange(__mcTemp__3);
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
			// cBviews
			//
			this->cBviews->BackColor = System::Drawing::Color::FromArgb((System::Byte)192, (System::Byte)255, (System::Byte)192);
			this->cBviews->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			System::Object* __mcTemp__4[] = new System::Object*[1];
			__mcTemp__4[0] = S"NULL";
			this->cBviews->Items->AddRange(__mcTemp__4);
			this->cBviews->Location = System::Drawing::Point(7, 7);
			this->cBviews->Name = S"cBviews";
			this->cBviews->Size = System::Drawing::Size(300, 21);
			this->cBviews->TabIndex = 0;
			this->cBviews->SelectedIndexChanged += new System::EventHandler(this, cBviews_SelectedIndexChanged);
			//
			// openFileDialog1
			//
			this->openFileDialog1->Filter = S"XML data file (.xml|*.xml|YUV (.yuv)|*.yuv|Uncompressed AVI - YUV (.AVI)|*.avi|Al"
				S"l Files (*.*)|*.*";
			this->openFileDialog1->FilterIndex = 4;
			this->openFileDialog1->Title = S"Open Movie File..";
			this->openFileDialog1->FileOk += new System::ComponentModel::CancelEventHandler(this, openFileDialog1_FileOk);
			//
			// tabControl1
			//
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tabControl1->Location = System::Drawing::Point(0, 0);
			this->tabControl1->Name = S"tabControl1";
			this->tabControl1->Padding = System::Drawing::Point(10, 4);
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(312, 246);
			this->tabControl1->TabIndex = 4;
			//
			// tabPage1
			//
			this->tabPage1->Controls->Add(this->panel12);
			this->tabPage1->Controls->Add(this->tBpath);
			this->tabPage1->Controls->Add(this->panel10);
			this->tabPage1->Controls->Add(this->panel11);
			this->tabPage1->Controls->Add(this->panel13);
			this->tabPage1->Controls->Add(this->panel14);
			this->tabPage1->Controls->Add(this->button1);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = S"tabPage1";
			this->tabPage1->Size = System::Drawing::Size(304, 220);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = S"Movie";
			//
			// panel12
			//
			this->panel12->Controls->Add(this->label2);
			this->panel12->Controls->Add(this->button2);
			this->panel12->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel12->Location = System::Drawing::Point(7, 34);
			this->panel12->Name = S"panel12";
			this->panel12->Size = System::Drawing::Size(290, 23);
			this->panel12->TabIndex = 21;
			//
			// label2
			//
			this->label2->AutoSize = true;
			this->label2->Dock = System::Windows::Forms::DockStyle::Left;
			this->label2->Enabled = false;
			this->label2->Location = System::Drawing::Point(0, 0);
			this->label2->Name = S"label2";
			this->label2->Size = System::Drawing::Size(119, 16);
			this->label2->TabIndex = 5;
			this->label2->Text = S"current filename (XML)";
			//
			// button2
			//
			this->button2->Dock = System::Windows::Forms::DockStyle::Right;
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button2->Location = System::Drawing::Point(223, 0);
			this->button2->Name = S"button2";
			this->button2->Size = System::Drawing::Size(67, 23);
			this->button2->TabIndex = 3;
			this->button2->Text = S"Browse..";
			this->button2->Click += new System::EventHandler(this, button2_Click);
			//
			// tBpath
			//
			this->tBpath->BackColor = System::Drawing::Color::FromArgb((System::Byte)255, (System::Byte)224, (System::Byte)192);
			this->tBpath->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->tBpath->Dock = System::Windows::Forms::DockStyle::Top;
			this->tBpath->Location = System::Drawing::Point(7, 14);
			this->tBpath->Name = S"tBpath";
			this->tBpath->Size = System::Drawing::Size(290, 20);
			this->tBpath->TabIndex = 20;
			this->tBpath->Text = S"";
			//
			// panel10
			//
			this->panel10->Controls->Add(this->lbStream);
			this->panel10->Controls->Add(this->tBarStream);
			this->panel10->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel10->Location = System::Drawing::Point(7, 151);
			this->panel10->Name = S"panel10";
			this->panel10->Size = System::Drawing::Size(290, 69);
			this->panel10->TabIndex = 19;
			//
			// lbStream
			//
			this->lbStream->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->lbStream->Location = System::Drawing::Point(0, 7);
			this->lbStream->Name = S"lbStream";
			this->lbStream->Size = System::Drawing::Size(290, 20);
			this->lbStream->TabIndex = 7;
			//
			// tBarStream
			//
			this->tBarStream->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->tBarStream->Location = System::Drawing::Point(0, 27);
			this->tBarStream->Maximum = 2000;
			this->tBarStream->Name = S"tBarStream";
			this->tBarStream->Size = System::Drawing::Size(290, 42);
			this->tBarStream->TabIndex = 6;
			this->tBarStream->TickFrequency = 100;
			//
			// panel11
			//
			this->panel11->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel11->Location = System::Drawing::Point(7, 0);
			this->panel11->Name = S"panel11";
			this->panel11->Size = System::Drawing::Size(290, 14);
			this->panel11->TabIndex = 18;
			//
			// panel13
			//
			this->panel13->Dock = System::Windows::Forms::DockStyle::Right;
			this->panel13->Location = System::Drawing::Point(297, 0);
			this->panel13->Name = S"panel13";
			this->panel13->Size = System::Drawing::Size(7, 220);
			this->panel13->TabIndex = 16;
			//
			// panel14
			//
			this->panel14->Dock = System::Windows::Forms::DockStyle::Left;
			this->panel14->Location = System::Drawing::Point(0, 0);
			this->panel14->Name = S"panel14";
			this->panel14->Size = System::Drawing::Size(7, 220);
			this->panel14->TabIndex = 15;
			//
			// button1
			//
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Location = System::Drawing::Point(24, 120);
			this->button1->Name = S"button1";
			this->button1->Size = System::Drawing::Size(260, 28);
			this->button1->TabIndex = 1;
			this->button1->Text = S"Open Movie";
			this->button1->Click += new System::EventHandler(this, button1_Click);
			//
			// tabPage2
			//
			this->tabPage2->Controls->Add(this->lBstreamInfo);
			this->tabPage2->Controls->Add(this->panel6);
			this->tabPage2->Controls->Add(this->panel7);
			this->tabPage2->Controls->Add(this->panel8);
			this->tabPage2->Controls->Add(this->panel9);
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Name = S"tabPage2";
			this->tabPage2->Size = System::Drawing::Size(305, 165);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = S"Stream Informations";
			this->tabPage2->Visible = false;
			//
			// lBstreamInfo
			//
			this->lBstreamInfo->BackColor = System::Drawing::Color::FromArgb((System::Byte)255, (System::Byte)224, (System::Byte)192);
			this->lBstreamInfo->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lBstreamInfo->ColumnWidth = 100;
			this->lBstreamInfo->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lBstreamInfo->ItemHeight = 16;
			this->lBstreamInfo->Location = System::Drawing::Point(7, 7);
			this->lBstreamInfo->MultiColumn = true;
			this->lBstreamInfo->Name = S"lBstreamInfo";
			this->lBstreamInfo->Size = System::Drawing::Size(291, 151);
			this->lBstreamInfo->TabIndex = 16;
			//
			// panel6
			//
			this->panel6->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel6->Location = System::Drawing::Point(7, 0);
			this->panel6->Name = S"panel6";
			this->panel6->Size = System::Drawing::Size(291, 7);
			this->panel6->TabIndex = 14;
			//
			// panel7
			//
			this->panel7->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel7->Location = System::Drawing::Point(7, 158);
			this->panel7->Name = S"panel7";
			this->panel7->Size = System::Drawing::Size(291, 7);
			this->panel7->TabIndex = 13;
			//
			// panel8
			//
			this->panel8->Dock = System::Windows::Forms::DockStyle::Right;
			this->panel8->Location = System::Drawing::Point(298, 0);
			this->panel8->Name = S"panel8";
			this->panel8->Size = System::Drawing::Size(7, 165);
			this->panel8->TabIndex = 12;
			//
			// panel9
			//
			this->panel9->Dock = System::Windows::Forms::DockStyle::Left;
			this->panel9->Location = System::Drawing::Point(0, 0);
			this->panel9->Name = S"panel9";
			this->panel9->Size = System::Drawing::Size(7, 165);
			this->panel9->TabIndex = 11;
			//
			// tabPage3
			//
			this->tabPage3->Controls->Add(this->rTBinfo);
			this->tabPage3->Controls->Add(this->panel5);
			this->tabPage3->Controls->Add(this->panel4);
			this->tabPage3->Controls->Add(this->panel3);
			this->tabPage3->Controls->Add(this->panel2);
			this->tabPage3->Location = System::Drawing::Point(4, 22);
			this->tabPage3->Name = S"tabPage3";
			this->tabPage3->Size = System::Drawing::Size(305, 165);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = S"Module Informations";
			this->tabPage3->Visible = false;
			//
			// rTBinfo
			//
			this->rTBinfo->BackColor = System::Drawing::Color::FromArgb((System::Byte)255, (System::Byte)224, (System::Byte)192);
			this->rTBinfo->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->rTBinfo->Dock = System::Windows::Forms::DockStyle::Fill;
			this->rTBinfo->Location = System::Drawing::Point(7, 7);
			this->rTBinfo->Name = S"rTBinfo";
			this->rTBinfo->ReadOnly = true;
			this->rTBinfo->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::Vertical;
			this->rTBinfo->Size = System::Drawing::Size(291, 151);
			this->rTBinfo->TabIndex = 11;
			this->rTBinfo->Text = S"";
			this->rTBinfo->LinkClicked += new System::Windows::Forms::LinkClickedEventHandler(this, rTBinfo_LinkClicked);
			//
			// panel5
			//
			this->panel5->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel5->Location = System::Drawing::Point(7, 0);
			this->panel5->Name = S"panel5";
			this->panel5->Size = System::Drawing::Size(291, 7);
			this->panel5->TabIndex = 10;
			//
			// panel4
			//
			this->panel4->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel4->Location = System::Drawing::Point(7, 158);
			this->panel4->Name = S"panel4";
			this->panel4->Size = System::Drawing::Size(291, 7);
			this->panel4->TabIndex = 9;
			//
			// panel3
			//
			this->panel3->Dock = System::Windows::Forms::DockStyle::Right;
			this->panel3->Location = System::Drawing::Point(298, 0);
			this->panel3->Name = S"panel3";
			this->panel3->Size = System::Drawing::Size(7, 165);
			this->panel3->TabIndex = 8;
			//
			// panel2
			//
			this->panel2->Dock = System::Windows::Forms::DockStyle::Left;
			this->panel2->Location = System::Drawing::Point(0, 0);
			this->panel2->Name = S"panel2";
			this->panel2->Size = System::Drawing::Size(7, 165);
			this->panel2->TabIndex = 7;
			//
			// rawCodecForm
			//
			this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
			this->ClientSize = System::Drawing::Size(312, 309);
			this->Controls->Add(this->tabControl1);
			this->Controls->Add(this->panel1);
			this->Icon = (__try_cast<System::Drawing::Icon *  >(resources->GetObject(S"$this.Icon")));
			this->Name = S"rawCodecForm";
			this->Text = S"vipCodec_RAW 1.0.2 [dataSource 0.8]";
			this->Closing += new System::ComponentModel::CancelEventHandler(this, rawCodecForm_Closing);
			this->Load += new System::EventHandler(this, rawCodecForm_Load);
			this->Closed += new System::EventHandler(this, rawCodecForm_Closed);
			this->panel1->ResumeLayout(false);
			(__try_cast<System::ComponentModel::ISupportInitialize *  >(this->nUDfps))->EndInit();
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->panel12->ResumeLayout(false);
			this->panel10->ResumeLayout(false);
			(__try_cast<System::ComponentModel::ISupportInitialize *  >(this->tBarStream))->EndInit();
			this->tabPage2->ResumeLayout(false);
			this->tabPage3->ResumeLayout(false);
			this->ResumeLayout(false);

		}





			//




public: System::Void button2_Click(System::Object *  sender, System::EventArgs *  e)
		{
		openFileDialog1->InitialDirectory = lastPath;

		if ( openFileDialog1->ShowDialog() == DialogResult::OK )
		{
			tBpath->Text = openFileDialog1->FileName;
		}


		}

private: System::Void button1_Click(System::Object *  sender, System::EventArgs *  e);


private: System::Void pushFrames(int iLoop);


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


private: System::Void rTBinfo_LinkClicked(System::Object *  sender, System::Windows::Forms::LinkClickedEventArgs *  e)
		 {
			 System::Diagnostics::Process::Start(e->LinkText);
		 }

private: System::Void rawCodecForm_Load(System::Object *  sender, System::EventArgs *  e);


private: System::Void rawCodecForm_Closing(System::Object *  sender, System::ComponentModel::CancelEventArgs *  e);

private: System::Void rawCodecForm_Closed(System::Object *  sender, System::EventArgs *  e);


private: System::Void openFileDialog1_FileOk(System::Object *  sender, System::ComponentModel::CancelEventArgs *  e)
		 {
		 }

};
}
