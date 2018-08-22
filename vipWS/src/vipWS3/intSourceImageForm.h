#pragma once
#include "../../../../source/inputs/vipDirectXInput.h"
#include "viewForm.h"
#include "sourceInterface.h"
#include "outputInterface.h"

using namespace System;
using namespace System::IO;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


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
	public __gc class intSourceImageForm :	public System::Windows::Forms::Form, public sourceInterface
	{
	public:
		intSourceImageForm(void);

		void Init() {};

		VIPRESULT extractTo(vipFrameRGB24* img);

	protected:
		void Dispose(Boolean disposing);


	private: outputInterface* vF;
	private: vipFrameRGB24* buffer;	//permanent store
	private: Bitmap* myImage;
	private: String* lastPath;

	private: System::Windows::Forms::Panel *  panel1;
	private: System::Windows::Forms::TabControl *  tabControl1;
	private: System::Windows::Forms::TabPage *  tabPage1;
	private: System::Windows::Forms::TabPage *  tabPage2;
	private: System::Windows::Forms::Button *  button1;
	private: System::Windows::Forms::ComboBox *  cBviews;
	private: System::Windows::Forms::TabPage *  tabPage3;
	private: System::Windows::Forms::Label *  label1;
	private: System::Windows::Forms::Button *  button2;
	private: System::Windows::Forms::Panel *  panel6;
	private: System::Windows::Forms::Panel *  panel7;
	private: System::Windows::Forms::Panel *  panel8;
	private: System::Windows::Forms::Panel *  panel9;
	private: System::Windows::Forms::Label *  label2;
	private: System::Windows::Forms::Button *  button4;
	private: System::Windows::Forms::Button *  button5;
	private: System::Windows::Forms::ListBox *  lBfiles;
	private: System::Windows::Forms::TextBox *  tBfolder;
	private: System::Windows::Forms::TextBox *  tBfile;
	private: System::Windows::Forms::CheckBox *  cBfilter;
	private: System::Windows::Forms::Panel *  panel10;
	private: System::Windows::Forms::Panel *  panel11;
	private: System::Windows::Forms::Panel *  panel12;
	private: System::Windows::Forms::Panel *  panel13;
	private: System::Windows::Forms::Button *  button6;
	private: System::Windows::Forms::ListBox *  lBstreamInfo;
	private: System::Windows::Forms::PictureBox *  pictureBox1;
	private: System::Windows::Forms::RadioButton *  radioButton3;
	private: System::Windows::Forms::RadioButton *  radioButton1;
	private: System::Windows::Forms::RadioButton *  radioButton2;
	private: System::Windows::Forms::Button *  button3;
	private: System::Windows::Forms::OpenFileDialog *  openFileDialog1;
	private: System::Windows::Forms::TabPage *  tabPage4;
	private: System::Windows::Forms::RichTextBox *  rTBinfo;
	private: System::Windows::Forms::Panel *  panel5;
	private: System::Windows::Forms::Panel *  panel4;
	private: System::Windows::Forms::Panel *  panel3;
	private: System::Windows::Forms::Panel *  panel2;


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
			System::Resources::ResourceManager *  resources = new System::Resources::ResourceManager(__typeof(vipWS3::intSourceImageForm));
			this->panel1 = new System::Windows::Forms::Panel();
			this->button1 = new System::Windows::Forms::Button();
			this->cBviews = new System::Windows::Forms::ComboBox();
			this->tabControl1 = new System::Windows::Forms::TabControl();
			this->tabPage1 = new System::Windows::Forms::TabPage();
			this->button6 = new System::Windows::Forms::Button();
			this->cBfilter = new System::Windows::Forms::CheckBox();
			this->button5 = new System::Windows::Forms::Button();
			this->button4 = new System::Windows::Forms::Button();
			this->lBfiles = new System::Windows::Forms::ListBox();
			this->tBfolder = new System::Windows::Forms::TextBox();
			this->label2 = new System::Windows::Forms::Label();
			this->tBfile = new System::Windows::Forms::TextBox();
			this->button2 = new System::Windows::Forms::Button();
			this->label1 = new System::Windows::Forms::Label();
			this->tabPage2 = new System::Windows::Forms::TabPage();
			this->lBstreamInfo = new System::Windows::Forms::ListBox();
			this->panel10 = new System::Windows::Forms::Panel();
			this->panel11 = new System::Windows::Forms::Panel();
			this->panel12 = new System::Windows::Forms::Panel();
			this->panel13 = new System::Windows::Forms::Panel();
			this->tabPage3 = new System::Windows::Forms::TabPage();
			this->pictureBox1 = new System::Windows::Forms::PictureBox();
			this->panel6 = new System::Windows::Forms::Panel();
			this->button3 = new System::Windows::Forms::Button();
			this->radioButton2 = new System::Windows::Forms::RadioButton();
			this->radioButton1 = new System::Windows::Forms::RadioButton();
			this->radioButton3 = new System::Windows::Forms::RadioButton();
			this->panel7 = new System::Windows::Forms::Panel();
			this->panel8 = new System::Windows::Forms::Panel();
			this->panel9 = new System::Windows::Forms::Panel();
			this->tabPage4 = new System::Windows::Forms::TabPage();
			this->rTBinfo = new System::Windows::Forms::RichTextBox();
			this->panel5 = new System::Windows::Forms::Panel();
			this->panel4 = new System::Windows::Forms::Panel();
			this->panel3 = new System::Windows::Forms::Panel();
			this->panel2 = new System::Windows::Forms::Panel();
			this->openFileDialog1 = new System::Windows::Forms::OpenFileDialog();
			this->panel1->SuspendLayout();
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->tabPage3->SuspendLayout();
			this->panel6->SuspendLayout();
			this->tabPage4->SuspendLayout();
			this->SuspendLayout();
			//
			// panel1
			//
			this->panel1->Controls->Add(this->button1);
			this->panel1->Controls->Add(this->cBviews);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel1->Location = System::Drawing::Point(0, 286);
			this->panel1->Name = S"panel1";
			this->panel1->Size = System::Drawing::Size(482, 40);
			this->panel1->TabIndex = 0;
			//
			// button1
			//
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Location = System::Drawing::Point(376, 8);
			this->button1->Name = S"button1";
			this->button1->Size = System::Drawing::Size(96, 24);
			this->button1->TabIndex = 1;
			this->button1->Text = S"Extract";
			this->button1->Click += new System::EventHandler(this, button1_Click);
			//
			// cBviews
			//
			this->cBviews->BackColor = System::Drawing::Color::FromArgb((System::Byte)192, (System::Byte)255, (System::Byte)192);
			this->cBviews->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			System::Object* __mcTemp__1[] = new System::Object*[1];
			__mcTemp__1[0] = S"NULL";
			this->cBviews->Items->AddRange(__mcTemp__1);
			this->cBviews->Location = System::Drawing::Point(16, 8);
			this->cBviews->Name = S"cBviews";
			this->cBviews->Size = System::Drawing::Size(344, 24);
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
			this->tabControl1->Padding = System::Drawing::Point(10, 4);
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(482, 286);
			this->tabControl1->TabIndex = 1;
			//
			// tabPage1
			//
			this->tabPage1->Controls->Add(this->button6);
			this->tabPage1->Controls->Add(this->cBfilter);
			this->tabPage1->Controls->Add(this->button5);
			this->tabPage1->Controls->Add(this->button4);
			this->tabPage1->Controls->Add(this->lBfiles);
			this->tabPage1->Controls->Add(this->tBfolder);
			this->tabPage1->Controls->Add(this->label2);
			this->tabPage1->Controls->Add(this->tBfile);
			this->tabPage1->Controls->Add(this->button2);
			this->tabPage1->Controls->Add(this->label1);
			this->tabPage1->Location = System::Drawing::Point(4, 25);
			this->tabPage1->Name = S"tabPage1";
			this->tabPage1->Size = System::Drawing::Size(474, 257);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = S"Image Source";
			//
			// button6
			//
			this->button6->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button6->Location = System::Drawing::Point(176, 184);
			this->button6->Name = S"button6";
			this->button6->Size = System::Drawing::Size(152, 25);
			this->button6->TabIndex = 9;
			this->button6->Text = S"Load image..";
			this->button6->Click += new System::EventHandler(this, button6_Click);
			//
			// cBfilter
			//
			this->cBfilter->Checked = true;
			this->cBfilter->CheckState = System::Windows::Forms::CheckState::Checked;
			this->cBfilter->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->cBfilter->Location = System::Drawing::Point(360, 144);
			this->cBfilter->Name = S"cBfilter";
			this->cBfilter->TabIndex = 8;
			this->cBfilter->Text = S"filter images";
			//
			// button5
			//
			this->button5->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button5->Location = System::Drawing::Point(16, 184);
			this->button5->Name = S"button5";
			this->button5->Size = System::Drawing::Size(152, 25);
			this->button5->TabIndex = 7;
			this->button5->Text = S"Load selected";
			this->button5->Click += new System::EventHandler(this, button5_Click);
			//
			// button4
			//
			this->button4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button4->Location = System::Drawing::Point(360, 120);
			this->button4->Name = S"button4";
			this->button4->Size = System::Drawing::Size(96, 24);
			this->button4->TabIndex = 6;
			this->button4->Text = S"update";
			this->button4->Click += new System::EventHandler(this, button4_Click);
			//
			// lBfiles
			//
			this->lBfiles->BackColor = System::Drawing::Color::FromArgb((System::Byte)255, (System::Byte)224, (System::Byte)192);
			this->lBfiles->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lBfiles->ItemHeight = 16;
			this->lBfiles->Location = System::Drawing::Point(16, 56);
			this->lBfiles->Name = S"lBfiles";
			this->lBfiles->ScrollAlwaysVisible = true;
			this->lBfiles->Size = System::Drawing::Size(336, 114);
			this->lBfiles->TabIndex = 5;
			//
			// tBfolder
			//
			this->tBfolder->AutoSize = false;
			this->tBfolder->BackColor = System::Drawing::Color::FromArgb((System::Byte)255, (System::Byte)224, (System::Byte)192);
			this->tBfolder->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->tBfolder->Location = System::Drawing::Point(16, 32);
			this->tBfolder->Name = S"tBfolder";
			this->tBfolder->Size = System::Drawing::Size(440, 22);
			this->tBfolder->TabIndex = 3;
			this->tBfolder->Text = S"";
			//
			// label2
			//
			this->label2->AutoSize = true;
			this->label2->Enabled = false;
			this->label2->Location = System::Drawing::Point(344, 16);
			this->label2->Name = S"label2";
			this->label2->Size = System::Drawing::Size(113, 18);
			this->label2->TabIndex = 4;
			this->label2->Text = S"current data folder";
			this->label2->TextAlign = System::Drawing::ContentAlignment::TopRight;
			//
			// tBfile
			//
			this->tBfile->AutoSize = false;
			this->tBfile->BackColor = System::Drawing::Color::FromArgb((System::Byte)255, (System::Byte)224, (System::Byte)192);
			this->tBfile->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->tBfile->Location = System::Drawing::Point(16, 224);
			this->tBfile->Name = S"tBfile";
			this->tBfile->Size = System::Drawing::Size(440, 22);
			this->tBfile->TabIndex = 0;
			this->tBfile->Text = S"";
			//
			// button2
			//
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button2->Location = System::Drawing::Point(360, 56);
			this->button2->Name = S"button2";
			this->button2->Size = System::Drawing::Size(96, 24);
			this->button2->TabIndex = 2;
			this->button2->Text = S"browse..";
			//
			// label1
			//
			this->label1->AutoSize = true;
			this->label1->Enabled = false;
			this->label1->Location = System::Drawing::Point(336, 208);
			this->label1->Name = S"label1";
			this->label1->Size = System::Drawing::Size(120, 18);
			this->label1->TabIndex = 1;
			this->label1->Text = S"current data source";
			this->label1->TextAlign = System::Drawing::ContentAlignment::TopRight;
			//
			// tabPage2
			//
			this->tabPage2->Controls->Add(this->lBstreamInfo);
			this->tabPage2->Controls->Add(this->panel10);
			this->tabPage2->Controls->Add(this->panel11);
			this->tabPage2->Controls->Add(this->panel12);
			this->tabPage2->Controls->Add(this->panel13);
			this->tabPage2->Location = System::Drawing::Point(4, 25);
			this->tabPage2->Name = S"tabPage2";
			this->tabPage2->Size = System::Drawing::Size(474, 257);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = S"Image Informations";
			//
			// lBstreamInfo
			//
			this->lBstreamInfo->BackColor = System::Drawing::Color::FromArgb((System::Byte)255, (System::Byte)224, (System::Byte)192);
			this->lBstreamInfo->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lBstreamInfo->ColumnWidth = 100;
			this->lBstreamInfo->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lBstreamInfo->ItemHeight = 16;
			this->lBstreamInfo->Location = System::Drawing::Point(8, 8);
			this->lBstreamInfo->MultiColumn = true;
			this->lBstreamInfo->Name = S"lBstreamInfo";
			this->lBstreamInfo->Size = System::Drawing::Size(458, 226);
			this->lBstreamInfo->TabIndex = 11;
			//
			// panel10
			//
			this->panel10->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel10->Location = System::Drawing::Point(8, 0);
			this->panel10->Name = S"panel10";
			this->panel10->Size = System::Drawing::Size(458, 8);
			this->panel10->TabIndex = 10;
			//
			// panel11
			//
			this->panel11->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel11->Location = System::Drawing::Point(8, 249);
			this->panel11->Name = S"panel11";
			this->panel11->Size = System::Drawing::Size(458, 8);
			this->panel11->TabIndex = 9;
			//
			// panel12
			//
			this->panel12->Dock = System::Windows::Forms::DockStyle::Right;
			this->panel12->Location = System::Drawing::Point(466, 0);
			this->panel12->Name = S"panel12";
			this->panel12->Size = System::Drawing::Size(8, 257);
			this->panel12->TabIndex = 8;
			//
			// panel13
			//
			this->panel13->Dock = System::Windows::Forms::DockStyle::Left;
			this->panel13->Location = System::Drawing::Point(0, 0);
			this->panel13->Name = S"panel13";
			this->panel13->Size = System::Drawing::Size(8, 257);
			this->panel13->TabIndex = 7;
			//
			// tabPage3
			//
			this->tabPage3->Controls->Add(this->pictureBox1);
			this->tabPage3->Controls->Add(this->panel6);
			this->tabPage3->Controls->Add(this->panel7);
			this->tabPage3->Controls->Add(this->panel8);
			this->tabPage3->Controls->Add(this->panel9);
			this->tabPage3->Location = System::Drawing::Point(4, 25);
			this->tabPage3->Name = S"tabPage3";
			this->tabPage3->Size = System::Drawing::Size(474, 257);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = S"Preview";
			//
			// pictureBox1
			//
			this->pictureBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox1->Location = System::Drawing::Point(8, 32);
			this->pictureBox1->Name = S"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(458, 217);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::CenterImage;
			this->pictureBox1->TabIndex = 11;
			this->pictureBox1->TabStop = false;
			//
			// panel6
			//
			this->panel6->Controls->Add(this->button3);
			this->panel6->Controls->Add(this->radioButton2);
			this->panel6->Controls->Add(this->radioButton1);
			this->panel6->Controls->Add(this->radioButton3);
			this->panel6->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel6->Location = System::Drawing::Point(8, 0);
			this->panel6->Name = S"panel6";
			this->panel6->Size = System::Drawing::Size(458, 32);
			this->panel6->TabIndex = 10;
			//
			// button3
			//
			this->button3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button3->Location = System::Drawing::Point(344, 6);
			this->button3->Name = S"button3";
			this->button3->Size = System::Drawing::Size(104, 20);
			this->button3->TabIndex = 7;
			this->button3->Text = S"reload";
			//
			// radioButton2
			//
			this->radioButton2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->radioButton2->Location = System::Drawing::Point(232, 8);
			this->radioButton2->Name = S"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(104, 16);
			this->radioButton2->TabIndex = 6;
			this->radioButton2->Text = S"Stretch";
			this->radioButton2->CheckedChanged += new System::EventHandler(this, radioButton_CheckedChanged);
			//
			// radioButton1
			//
			this->radioButton1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->radioButton1->Location = System::Drawing::Point(112, 8);
			this->radioButton1->Name = S"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(104, 16);
			this->radioButton1->TabIndex = 5;
			this->radioButton1->Text = S"AutoSize";
			this->radioButton1->CheckedChanged += new System::EventHandler(this, radioButton_CheckedChanged);
			//
			// radioButton3
			//
			this->radioButton3->Checked = true;
			this->radioButton3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->radioButton3->Location = System::Drawing::Point(8, 8);
			this->radioButton3->Name = S"radioButton3";
			this->radioButton3->Size = System::Drawing::Size(104, 16);
			this->radioButton3->TabIndex = 4;
			this->radioButton3->TabStop = true;
			this->radioButton3->Text = S"Center";
			this->radioButton3->CheckedChanged += new System::EventHandler(this, radioButton_CheckedChanged);
			//
			// panel7
			//
			this->panel7->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel7->Location = System::Drawing::Point(8, 249);
			this->panel7->Name = S"panel7";
			this->panel7->Size = System::Drawing::Size(458, 8);
			this->panel7->TabIndex = 9;
			//
			// panel8
			//
			this->panel8->Dock = System::Windows::Forms::DockStyle::Right;
			this->panel8->Location = System::Drawing::Point(466, 0);
			this->panel8->Name = S"panel8";
			this->panel8->Size = System::Drawing::Size(8, 257);
			this->panel8->TabIndex = 8;
			//
			// panel9
			//
			this->panel9->Dock = System::Windows::Forms::DockStyle::Left;
			this->panel9->Location = System::Drawing::Point(0, 0);
			this->panel9->Name = S"panel9";
			this->panel9->Size = System::Drawing::Size(8, 257);
			this->panel9->TabIndex = 7;
			//
			// tabPage4
			//
			this->tabPage4->Controls->Add(this->rTBinfo);
			this->tabPage4->Controls->Add(this->panel5);
			this->tabPage4->Controls->Add(this->panel4);
			this->tabPage4->Controls->Add(this->panel3);
			this->tabPage4->Controls->Add(this->panel2);
			this->tabPage4->Location = System::Drawing::Point(4, 25);
			this->tabPage4->Name = S"tabPage4";
			this->tabPage4->Size = System::Drawing::Size(474, 257);
			this->tabPage4->TabIndex = 5;
			this->tabPage4->Text = S"Module Informations";
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
			this->rTBinfo->Size = System::Drawing::Size(458, 241);
			this->rTBinfo->TabIndex = 16;
			this->rTBinfo->Text = S"";
			this->rTBinfo->LinkClicked += new System::Windows::Forms::LinkClickedEventHandler(this, rTBinfo_LinkClicked);
			//
			// panel5
			//
			this->panel5->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel5->Location = System::Drawing::Point(8, 0);
			this->panel5->Name = S"panel5";
			this->panel5->Size = System::Drawing::Size(458, 8);
			this->panel5->TabIndex = 15;
			//
			// panel4
			//
			this->panel4->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel4->Location = System::Drawing::Point(8, 249);
			this->panel4->Name = S"panel4";
			this->panel4->Size = System::Drawing::Size(458, 8);
			this->panel4->TabIndex = 14;
			//
			// panel3
			//
			this->panel3->Dock = System::Windows::Forms::DockStyle::Right;
			this->panel3->Location = System::Drawing::Point(466, 0);
			this->panel3->Name = S"panel3";
			this->panel3->Size = System::Drawing::Size(8, 257);
			this->panel3->TabIndex = 13;
			//
			// panel2
			//
			this->panel2->Dock = System::Windows::Forms::DockStyle::Left;
			this->panel2->Location = System::Drawing::Point(0, 0);
			this->panel2->Name = S"panel2";
			this->panel2->Size = System::Drawing::Size(8, 257);
			this->panel2->TabIndex = 12;
			//
			// openFileDialog1
			//
			this->openFileDialog1->DefaultExt = S"JPG";
			this->openFileDialog1->Filter = S"All Files (*.*)|*.*|Bitmap (*.BMP)|*.BMP|Joint Photogaphic Expert Group (*.JPG;*."
				S"JPEG;*.JIFF)|*.JPG;*.JPEG;*.JIFF|Graphic Interchange Format (*.GIF)|*.GIF|Tagged"
				S" Image Format File (*.TIFF)|*.TIFF|Windows Metafile Format (*.WMF)|*.WMF|Extende"
				S"d Metafile Format (*.EMF)|*.EMF|Exchangeable Image Format (*.EXIF)|*.EXIF|Portab"
				S"le Network Graphic (*.PNG)|*.PNG";
			this->openFileDialog1->Title = S"Open Source Image..";
			//
			// intSourceImageForm
			//
			this->AutoScaleBaseSize = System::Drawing::Size(6, 15);
			this->ClientSize = System::Drawing::Size(482, 326);
			this->Controls->Add(this->tabControl1);
			this->Controls->Add(this->panel1);
			this->Icon = (__try_cast<System::Drawing::Icon *  >(resources->GetObject(S"$this.Icon")));
			this->Name = S"intSourceImageForm";
			this->Text = S"InternalSourceImage 0.8";
			this->Closing += new System::ComponentModel::CancelEventHandler(this, intSourceImageForm_Closing);
			this->Load += new System::EventHandler(this, intSourceImageForm_Load);
			this->panel1->ResumeLayout(false);
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage2->ResumeLayout(false);
			this->tabPage3->ResumeLayout(false);
			this->panel6->ResumeLayout(false);
			this->tabPage4->ResumeLayout(false);
			this->ResumeLayout(false);

		}








		//
private: System::Void intSourceImageForm_Load(System::Object *  sender, System::EventArgs *  e);


private: System::Void rTBinfo_LinkClicked(System::Object *  sender, System::Windows::Forms::LinkClickedEventArgs *  e)
		 {
			 System::Diagnostics::Process::Start(e->LinkText);
		 }

private: System::Void button4_Click(System::Object *  sender, System::EventArgs *  e);

private: System::Void button5_Click(System::Object *  sender, System::EventArgs *  e);

private: System::Void button3_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 pictureBox1->Image = myImage;
			 pictureBox1->Refresh();
		 }

private: System::Void button1_Click(System::Object *  sender, System::EventArgs *  e);


private: System::Void radioButton_CheckedChanged(System::Object *  sender, System::EventArgs *  e)
		 {
			 if (radioButton1->Checked)
				 pictureBox1->SizeMode = PictureBoxSizeMode::AutoSize;

			 if (radioButton2->Checked)
				 pictureBox1->SizeMode = PictureBoxSizeMode::StretchImage;

			 if (radioButton3->Checked)
				 pictureBox1->SizeMode = PictureBoxSizeMode::CenterImage;

			 pictureBox1->Refresh();
			 this->Refresh();
		 }

public: System::Void button6_Click(System::Object *  sender, System::EventArgs *  e);

private:	System::Void updateImageInfos(void)
			{
				lBstreamInfo->Items->Clear();

				if (myImage == NULL)
					return;

				lBstreamInfo->Items->Add( System::String::Format("Filename\t:\t{0}", tBfile->Text ) );

				lBstreamInfo->Items->Add( new System::String("") );
				lBstreamInfo->Items->Add( System::String::Format("Width\t:\t{0}", myImage->Width.ToString() ) );
				lBstreamInfo->Items->Add( System::String::Format("Height\t:\t{0}", myImage->Height.ToString() ) );
				lBstreamInfo->Items->Add( new System::String("") );
				lBstreamInfo->Items->Add( System::String::Format("Horz Resolution\t:\t{0}", myImage->HorizontalResolution.ToString() ) );
				lBstreamInfo->Items->Add( System::String::Format("Vert Resolution\t:\t{0}", myImage->VerticalResolution.ToString() ) );
			}

private:	System::Void loadData(void);

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




private: System::Void intSourceImageForm_Closing(System::Object *  sender, System::ComponentModel::CancelEventArgs *  e);

};
}
