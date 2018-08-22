#pragma once
#include "sourceInterface.h"
#include "outputInterface.h"

#include "viewForm.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

class vipDirectXInput2;

namespace vipWS3
{
	/// <summary>
	/// Riepilogo per dxcaptureForm
	///
	/// AVVISO: se si modifica il nome della classe, sarà necessario modificare la
	///          proprietà "Nome file di risorse" relativa allo strumento di compilazione delle risorse gestite
	///          associato a tutti i file RESX da cui dipende la classe. In caso contrario,
	///          le finestre di progettazione non saranno in grado di interagire correttamente con le
	///          risorse localizzate associate al form.
	/// </summary>
	public __gc class dxcaptureForm : public System::Windows::Forms::Form, public sourceInterface
	{
	public:
		dxcaptureForm(void);

		void Init(void);

		VIPRESULT extractTo(vipFrameRGB24* img);

	protected:
		void Dispose(Boolean disposing)
		{
			if (disposing && components)
			{
				components->Dispose();
			}
			__super::Dispose(disposing);
		}

	private: vipDirectXInput2* myDXInput;
	private: vipFrameRGB24* buffer;
	private: outputInterface* vF;
	private: viewForm* myPVForm;

	private: System::Windows::Forms::Panel *  panel1;
	private: System::Windows::Forms::TabControl *  tabControl1;
	private: System::Windows::Forms::TabPage *  tabPage1;
	private: System::Windows::Forms::TabPage *  tabPage2;
	private: System::Windows::Forms::TabPage *  tabPage3;
	private: System::Windows::Forms::TabPage *  tabPage4;
	private: System::Windows::Forms::ListBox *  listBox1;
	private: System::Windows::Forms::Panel *  panel2;
	private: System::Windows::Forms::Button *  button1;
	private: System::Windows::Forms::Button *  button3;
	private: System::Windows::Forms::NumericUpDown *  numericUpDown1;
	private: System::Windows::Forms::Label *  label1;
	private: System::Windows::Forms::GroupBox *  groupBox1;
	private: System::Windows::Forms::Panel *  panel4;
	private: System::Windows::Forms::CheckBox *  checkBox1;
	private: System::Windows::Forms::SaveFileDialog *  saveFileDialog1;
	private: System::Windows::Forms::GroupBox *  groupBox2;
	private: System::Windows::Forms::Panel *  panel5;
	private: System::Windows::Forms::TextBox *  tBpath;
	private: System::Windows::Forms::Panel *  panel6;
	private: System::Windows::Forms::Button *  button2;
	private: System::Windows::Forms::GroupBox *  groupBox3;
	private: System::Windows::Forms::Label *  label2;
	private: System::Windows::Forms::Label *  label3;
	private: System::Windows::Forms::Label *  label7;
	private: System::Windows::Forms::CheckBox *  checkBox2;
	private: System::Windows::Forms::Panel *  panel7;
	private: System::Windows::Forms::GroupBox *  groupBox4;
	private: System::Windows::Forms::Label *  label9;
	private: System::Windows::Forms::CheckBox *  checkBox5;
	private: System::Windows::Forms::Button *  button8;
	private: System::Windows::Forms::Button *  button7;
	private: System::Windows::Forms::Label *  label10;
	private: System::Windows::Forms::NumericUpDown *  numericUpDown2;
	private: System::Windows::Forms::Label *  lb_info_fs;
	private: System::Windows::Forms::Label *  lb_info_fsl;
	private: System::Windows::Forms::Button *  button9;
	private: System::Windows::Forms::Label *  lb_info;
	private: System::Windows::Forms::Button *  button4;
	private: System::Windows::Forms::CheckBox *  chk_updateall;
	private: System::Windows::Forms::Label *  lb_info_df;
	private: System::Windows::Forms::Label *  lb_info_cf;
	private: System::Windows::Forms::Label *  lb_info_et;
	private: System::Windows::Forms::Label *  label5;
	private: System::Windows::Forms::Label *  label8;
	private: System::Windows::Forms::Label *  lb_info_fps;
	private: System::Windows::Forms::Label *  label12;
	private: System::Windows::Forms::Label *  bl_info_afs;
	private: System::Windows::Forms::GroupBox *  groupBox5;
	private: System::Windows::Forms::Label *  lb_info_dr;
	private: System::Windows::Forms::Label *  label13;
	private: System::Windows::Forms::Label *  lb_info_format;
	private: System::Windows::Forms::Button *  button10;
	private: System::Windows::Forms::Timer *  timer1;
	private: System::Windows::Forms::TabPage *  tabPage5;
	private: System::Windows::Forms::Label *  label11;
	private: System::Windows::Forms::NumericUpDown *  numericUpDown3;
	private: System::Windows::Forms::CheckBox *  checkBox8;
	private: System::Windows::Forms::CheckBox *  checkBox7;
	private: System::Windows::Forms::CheckBox *  checkBox4;
	private: System::Windows::Forms::CheckBox *  checkBox3;
	private: System::Windows::Forms::TabPage *  tabPage6;
	private: System::Windows::Forms::TabPage *  tabPage9;
	private: System::Windows::Forms::RichTextBox *  rTBlog;

	private: System::Windows::Forms::ToolTip *  toolTip1;
	private: System::Windows::Forms::CheckBox *  checkBox9;
	private: System::Windows::Forms::ListBox *  listBox2;
	private: System::Windows::Forms::Button *  button11;
	private: System::Windows::Forms::Panel *  panel3;
	private: System::Windows::Forms::Button *  button6;
	private: System::Windows::Forms::Button *  button5;
	private: System::Windows::Forms::Label *  label6;
	private: System::Windows::Forms::Button *  button12;
	private: System::Windows::Forms::CheckBox *  checkBox10;
	private: System::Windows::Forms::CheckBox *  checkBox11;
	private: System::Windows::Forms::GroupBox *  groupBox6;
	private: System::Windows::Forms::CheckBox *  checkBox13;
	private: System::Windows::Forms::Button *  button13;
	private: System::Windows::Forms::CheckBox *  checkBox6;
	private: System::Windows::Forms::Button *  button14;
	private: System::Windows::Forms::Button *  button15;
	private: System::Windows::Forms::Button *  button16;
	private: System::Windows::Forms::GroupBox *  groupBox7;
private: System::Windows::Forms::Label *  label4;
private: System::Windows::Forms::NumericUpDown *  nUDfps;
private: System::Windows::Forms::Button *  button17;
private: System::Windows::Forms::ComboBox *  cBviews;
private: System::Windows::Forms::ContextMenu *  contextMenu1;
private: System::Windows::Forms::MenuItem *  menuItem3;
private: System::Windows::Forms::MenuItem *  menuItem1;
private: System::Windows::Forms::MenuItem *  menuItem2;
private: System::Windows::Forms::MenuItem *  menuItem4;
private: System::Windows::Forms::MenuItem *  menuItem5;
private: System::Windows::Forms::RichTextBox *  rTBinfo;
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
			this->label4 = new System::Windows::Forms::Label();
			this->nUDfps = new System::Windows::Forms::NumericUpDown();
			this->button17 = new System::Windows::Forms::Button();
			this->cBviews = new System::Windows::Forms::ComboBox();
			this->tabControl1 = new System::Windows::Forms::TabControl();
			this->tabPage1 = new System::Windows::Forms::TabPage();
			this->button12 = new System::Windows::Forms::Button();
			this->groupBox4 = new System::Windows::Forms::GroupBox();
			this->lb_info_format = new System::Windows::Forms::Label();
			this->lb_info = new System::Windows::Forms::Label();
			this->button9 = new System::Windows::Forms::Button();
			this->panel7 = new System::Windows::Forms::Panel();
			this->groupBox1 = new System::Windows::Forms::GroupBox();
			this->panel4 = new System::Windows::Forms::Panel();
			this->button15 = new System::Windows::Forms::Button();
			this->checkBox1 = new System::Windows::Forms::CheckBox();
			this->label1 = new System::Windows::Forms::Label();
			this->numericUpDown1 = new System::Windows::Forms::NumericUpDown();
			this->panel2 = new System::Windows::Forms::Panel();
			this->checkBox6 = new System::Windows::Forms::CheckBox();
			this->button10 = new System::Windows::Forms::Button();
			this->button3 = new System::Windows::Forms::Button();
			this->button1 = new System::Windows::Forms::Button();
			this->listBox1 = new System::Windows::Forms::ListBox();
			this->tabPage3 = new System::Windows::Forms::TabPage();
			this->label6 = new System::Windows::Forms::Label();
			this->panel3 = new System::Windows::Forms::Panel();
			this->button6 = new System::Windows::Forms::Button();
			this->button5 = new System::Windows::Forms::Button();
			this->listBox2 = new System::Windows::Forms::ListBox();
			this->checkBox9 = new System::Windows::Forms::CheckBox();
			this->tabPage2 = new System::Windows::Forms::TabPage();
			this->checkBox5 = new System::Windows::Forms::CheckBox();
			this->button11 = new System::Windows::Forms::Button();
			this->button4 = new System::Windows::Forms::Button();
			this->button8 = new System::Windows::Forms::Button();
			this->checkBox2 = new System::Windows::Forms::CheckBox();
			this->groupBox3 = new System::Windows::Forms::GroupBox();
			this->groupBox5 = new System::Windows::Forms::GroupBox();
			this->lb_info_dr = new System::Windows::Forms::Label();
			this->label13 = new System::Windows::Forms::Label();
			this->lb_info_fps = new System::Windows::Forms::Label();
			this->label12 = new System::Windows::Forms::Label();
			this->bl_info_afs = new System::Windows::Forms::Label();
			this->label8 = new System::Windows::Forms::Label();
			this->lb_info_et = new System::Windows::Forms::Label();
			this->label5 = new System::Windows::Forms::Label();
			this->lb_info_df = new System::Windows::Forms::Label();
			this->label9 = new System::Windows::Forms::Label();
			this->lb_info_cf = new System::Windows::Forms::Label();
			this->label7 = new System::Windows::Forms::Label();
			this->lb_info_fsl = new System::Windows::Forms::Label();
			this->lb_info_fs = new System::Windows::Forms::Label();
			this->label3 = new System::Windows::Forms::Label();
			this->label2 = new System::Windows::Forms::Label();
			this->groupBox2 = new System::Windows::Forms::GroupBox();
			this->panel5 = new System::Windows::Forms::Panel();
			this->panel6 = new System::Windows::Forms::Panel();
			this->numericUpDown2 = new System::Windows::Forms::NumericUpDown();
			this->label10 = new System::Windows::Forms::Label();
			this->button7 = new System::Windows::Forms::Button();
			this->button2 = new System::Windows::Forms::Button();
			this->tBpath = new System::Windows::Forms::TextBox();
			this->chk_updateall = new System::Windows::Forms::CheckBox();
			this->tabPage4 = new System::Windows::Forms::TabPage();
			this->button16 = new System::Windows::Forms::Button();
			this->button14 = new System::Windows::Forms::Button();
			this->checkBox13 = new System::Windows::Forms::CheckBox();
			this->groupBox6 = new System::Windows::Forms::GroupBox();
			this->checkBox11 = new System::Windows::Forms::CheckBox();
			this->tabPage5 = new System::Windows::Forms::TabPage();
			this->groupBox7 = new System::Windows::Forms::GroupBox();
			this->button13 = new System::Windows::Forms::Button();
			this->checkBox10 = new System::Windows::Forms::CheckBox();
			this->label11 = new System::Windows::Forms::Label();
			this->numericUpDown3 = new System::Windows::Forms::NumericUpDown();
			this->checkBox8 = new System::Windows::Forms::CheckBox();
			this->checkBox7 = new System::Windows::Forms::CheckBox();
			this->checkBox4 = new System::Windows::Forms::CheckBox();
			this->checkBox3 = new System::Windows::Forms::CheckBox();
			this->tabPage6 = new System::Windows::Forms::TabPage();
			this->rTBlog = new System::Windows::Forms::RichTextBox();
			this->tabPage9 = new System::Windows::Forms::TabPage();
			this->rTBinfo = new System::Windows::Forms::RichTextBox();
			this->saveFileDialog1 = new System::Windows::Forms::SaveFileDialog();
			this->timer1 = new System::Windows::Forms::Timer(this->components);
			this->toolTip1 = new System::Windows::Forms::ToolTip(this->components);
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
			this->groupBox4->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->panel4->SuspendLayout();
			(__try_cast<System::ComponentModel::ISupportInitialize *  >(this->numericUpDown1))->BeginInit();
			this->panel2->SuspendLayout();
			this->tabPage3->SuspendLayout();
			this->panel3->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->panel5->SuspendLayout();
			this->panel6->SuspendLayout();
			(__try_cast<System::ComponentModel::ISupportInitialize *  >(this->numericUpDown2))->BeginInit();
			this->tabPage4->SuspendLayout();
			this->tabPage5->SuspendLayout();
			(__try_cast<System::ComponentModel::ISupportInitialize *  >(this->numericUpDown3))->BeginInit();
			this->tabPage6->SuspendLayout();
			this->tabPage9->SuspendLayout();
			this->SuspendLayout();
			//
			// panel1
			//
			this->panel1->Controls->Add(this->label4);
			this->panel1->Controls->Add(this->nUDfps);
			this->panel1->Controls->Add(this->button17);
			this->panel1->Controls->Add(this->cBviews);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel1->Location = System::Drawing::Point(0, 454);
			this->panel1->Name = S"panel1";
			this->panel1->Size = System::Drawing::Size(520, 72);
			this->panel1->TabIndex = 0;
			//
			// label4
			//
			this->label4->AutoSize = true;
			this->label4->Enabled = false;
			this->label4->Location = System::Drawing::Point(416, 48);
			this->label4->Name = S"label4";
			this->label4->Size = System::Drawing::Size(23, 18);
			this->label4->TabIndex = 8;
			this->label4->Text = S"fps";
			//
			// nUDfps
			//
			this->nUDfps->BackColor = System::Drawing::Color::FromArgb((System::Byte)255, (System::Byte)224, (System::Byte)192);
			this->nUDfps->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->nUDfps->DecimalPlaces = 2;
			this->nUDfps->Location = System::Drawing::Point(440, 40);
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
			// button17
			//
			this->button17->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->button17->Location = System::Drawing::Point(8, 40);
			this->button17->Name = S"button17";
			this->button17->Size = System::Drawing::Size(392, 22);
			this->button17->TabIndex = 6;
			this->button17->Text = S"Extract..";
			//
			// cBviews
			//
			this->cBviews->BackColor = System::Drawing::Color::FromArgb((System::Byte)192, (System::Byte)255, (System::Byte)192);
			this->cBviews->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			System::Object* __mcTemp__3[] = new System::Object*[1];
			__mcTemp__3[0] = S"NULL";
			this->cBviews->Items->AddRange(__mcTemp__3);
			this->cBviews->Location = System::Drawing::Point(8, 8);
			this->cBviews->Name = S"cBviews";
			this->cBviews->Size = System::Drawing::Size(392, 24);
			this->cBviews->TabIndex = 5;
			//
			// tabControl1
			//
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage6);
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Controls->Add(this->tabPage4);
			this->tabControl1->Controls->Add(this->tabPage5);
			this->tabControl1->Controls->Add(this->tabPage9);
			this->tabControl1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tabControl1->Location = System::Drawing::Point(0, 0);
			this->tabControl1->Multiline = true;
			this->tabControl1->Name = S"tabControl1";
			this->tabControl1->Padding = System::Drawing::Point(24, 3);
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(520, 454);
			this->tabControl1->TabIndex = 1;
			this->tabControl1->SelectedIndexChanged += new System::EventHandler(this, tabControl1_SelectedIndexChanged);
			//
			// tabPage1
			//
			this->tabPage1->Controls->Add(this->button12);
			this->tabPage1->Controls->Add(this->groupBox4);
			this->tabPage1->Controls->Add(this->panel7);
			this->tabPage1->Controls->Add(this->groupBox1);
			this->tabPage1->Controls->Add(this->label1);
			this->tabPage1->Controls->Add(this->numericUpDown1);
			this->tabPage1->Controls->Add(this->panel2);
			this->tabPage1->Controls->Add(this->listBox1);
			this->tabPage1->DockPadding->All = 10;
			this->tabPage1->Location = System::Drawing::Point(4, 46);
			this->tabPage1->Name = S"tabPage1";
			this->tabPage1->Size = System::Drawing::Size(512, 404);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = S"General";
			//
			// button12
			//
			this->button12->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button12->Location = System::Drawing::Point(432, 376);
			this->button12->Name = S"button12";
			this->button12->Size = System::Drawing::Size(72, 23);
			this->button12->TabIndex = 16;
			this->button12->Text = S"Apply";
			this->button12->Click += new System::EventHandler(this, button12_Click);
			//
			// groupBox4
			//
			this->groupBox4->Controls->Add(this->lb_info_format);
			this->groupBox4->Controls->Add(this->lb_info);
			this->groupBox4->Controls->Add(this->button9);
			this->groupBox4->Dock = System::Windows::Forms::DockStyle::Top;
			this->groupBox4->Location = System::Drawing::Point(10, 230);
			this->groupBox4->Name = S"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(492, 136);
			this->groupBox4->TabIndex = 14;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = S"Status";
			//
			// lb_info_format
			//
			this->lb_info_format->Enabled = false;
			this->lb_info_format->Location = System::Drawing::Point(16, 64);
			this->lb_info_format->Name = S"lb_info_format";
			this->lb_info_format->Size = System::Drawing::Size(472, 32);
			this->lb_info_format->TabIndex = 1;
			this->lb_info_format->Text = S"No input.";
			//
			// lb_info
			//
			this->lb_info->Enabled = false;
			this->lb_info->Location = System::Drawing::Point(16, 24);
			this->lb_info->Name = S"lb_info";
			this->lb_info->Size = System::Drawing::Size(472, 32);
			this->lb_info->TabIndex = 0;
			this->lb_info->Text = S"Select devices..";
			//
			// button9
			//
			this->button9->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->button9->Location = System::Drawing::Point(415, 111);
			this->button9->Name = S"button9";
			this->button9->Size = System::Drawing::Size(76, 24);
			this->button9->TabIndex = 15;
			this->button9->Text = S"update";
			this->toolTip1->SetToolTip(this->button9, S"Update Status information, this should be automatic.");
			this->button9->Click += new System::EventHandler(this, button9_Click);
			//
			// panel7
			//
			this->panel7->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel7->Location = System::Drawing::Point(10, 214);
			this->panel7->Name = S"panel7";
			this->panel7->Size = System::Drawing::Size(492, 16);
			this->panel7->TabIndex = 13;
			//
			// groupBox1
			//
			this->groupBox1->Controls->Add(this->panel4);
			this->groupBox1->Dock = System::Windows::Forms::DockStyle::Top;
			this->groupBox1->Location = System::Drawing::Point(10, 142);
			this->groupBox1->Name = S"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(492, 72);
			this->groupBox1->TabIndex = 7;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = S"Preview";
			//
			// panel4
			//
			this->panel4->Controls->Add(this->button15);
			this->panel4->Controls->Add(this->checkBox1);
			this->panel4->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel4->DockPadding->Bottom = 10;
			this->panel4->DockPadding->Left = 6;
			this->panel4->DockPadding->Right = 6;
			this->panel4->DockPadding->Top = 10;
			this->panel4->Location = System::Drawing::Point(3, 18);
			this->panel4->Name = S"panel4";
			this->panel4->Size = System::Drawing::Size(486, 51);
			this->panel4->TabIndex = 0;
			//
			// button15
			//
			this->button15->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button15->Location = System::Drawing::Point(152, 10);
			this->button15->Name = S"button15";
			this->button15->Size = System::Drawing::Size(128, 31);
			this->button15->TabIndex = 8;
			this->button15->Text = S"Properties..";
			this->button15->Click += new System::EventHandler(this, button15_Click);
			//
			// checkBox1
			//
			this->checkBox1->Appearance = System::Windows::Forms::Appearance::Button;
			this->checkBox1->Dock = System::Windows::Forms::DockStyle::Left;
			this->checkBox1->Location = System::Drawing::Point(6, 10);
			this->checkBox1->Name = S"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(136, 31);
			this->checkBox1->TabIndex = 7;
			this->checkBox1->Text = S"Preview";
			this->checkBox1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->toolTip1->SetToolTip(this->checkBox1, S"Enable / disable previewing, ");
			this->checkBox1->Click += new System::EventHandler(this, checkBox1_Click);
			//
			// label1
			//
			this->label1->Location = System::Drawing::Point(160, 376);
			this->label1->Name = S"label1";
			this->label1->Size = System::Drawing::Size(144, 23);
			this->label1->TabIndex = 5;
			this->label1->Text = S"Current Frame Rate:";
			//
			// numericUpDown1
			//
			this->numericUpDown1->BackColor = System::Drawing::Color::FromArgb((System::Byte)255, (System::Byte)224, (System::Byte)192);
			this->numericUpDown1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->numericUpDown1->DecimalPlaces = 2;
			this->numericUpDown1->Location = System::Drawing::Point(304, 376);
			System::Int32 __mcTemp__4[] = new System::Int32[4];
			__mcTemp__4[0] = 1;
			__mcTemp__4[1] = 0;
			__mcTemp__4[2] = 0;
			__mcTemp__4[3] = 131072;
			this->numericUpDown1->Minimum = System::Decimal(__mcTemp__4);
			this->numericUpDown1->Name = S"numericUpDown1";
			this->numericUpDown1->TabIndex = 4;
			this->toolTip1->SetToolTip(this->numericUpDown1, S"This is the current frame rate of the whole graph.");
			System::Int32 __mcTemp__5[] = new System::Int32[4];
			__mcTemp__5[0] = 1500;
			__mcTemp__5[1] = 0;
			__mcTemp__5[2] = 0;
			__mcTemp__5[3] = 131072;
			this->numericUpDown1->Value = System::Decimal(__mcTemp__5);
			this->numericUpDown1->ValueChanged += new System::EventHandler(this, numericUpDown1_ValueChanged);
			//
			// panel2
			//
			this->panel2->Controls->Add(this->checkBox6);
			this->panel2->Controls->Add(this->button10);
			this->panel2->Controls->Add(this->button3);
			this->panel2->Controls->Add(this->button1);
			this->panel2->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel2->DockPadding->Bottom = 20;
			this->panel2->DockPadding->Top = 5;
			this->panel2->Location = System::Drawing::Point(10, 92);
			this->panel2->Name = S"panel2";
			this->panel2->Size = System::Drawing::Size(492, 50);
			this->panel2->TabIndex = 1;
			//
			// checkBox6
			//
			this->checkBox6->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->checkBox6->Location = System::Drawing::Point(120, 5);
			this->checkBox6->Name = S"checkBox6";
			this->checkBox6->Size = System::Drawing::Size(128, 16);
			this->checkBox6->TabIndex = 7;
			this->checkBox6->Text = S"MPEG2 Encoded";
			this->checkBox6->CheckedChanged += new System::EventHandler(this, checkBox6_CheckedChanged);
			//
			// button10
			//
			this->button10->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button10->Location = System::Drawing::Point(256, 5);
			this->button10->Name = S"button10";
			this->button10->Size = System::Drawing::Size(112, 27);
			this->button10->TabIndex = 6;
			this->button10->Text = S"force Close";
			this->toolTip1->SetToolTip(this->button10, S"Shoutdown current graph and clean filters up.");
			this->button10->Click += new System::EventHandler(this, button10_Click);
			//
			// button3
			//
			this->button3->Dock = System::Windows::Forms::DockStyle::Left;
			this->button3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button3->Location = System::Drawing::Point(0, 5);
			this->button3->Name = S"button3";
			this->button3->Size = System::Drawing::Size(112, 25);
			this->button3->TabIndex = 5;
			this->button3->Text = S"Properties..";
			this->toolTip1->SetToolTip(this->button3, S"Show specific driver property page of selected video device. (must be connected)");
			this->button3->Click += new System::EventHandler(this, button3_Click);
			//
			// button1
			//
			this->button1->Dock = System::Windows::Forms::DockStyle::Right;
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Location = System::Drawing::Point(380, 5);
			this->button1->Name = S"button1";
			this->button1->Size = System::Drawing::Size(112, 25);
			this->button1->TabIndex = 0;
			this->button1->Text = S"Update";
			this->toolTip1->SetToolTip(this->button1, S"Update current device list. (this will probably make system to disconnect)");
			this->button1->Click += new System::EventHandler(this, button1_Click);
			//
			// listBox1
			//
			this->listBox1->BackColor = System::Drawing::Color::FromArgb((System::Byte)255, (System::Byte)224, (System::Byte)192);
			this->listBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->listBox1->Dock = System::Windows::Forms::DockStyle::Top;
			this->listBox1->ItemHeight = 16;
			this->listBox1->Location = System::Drawing::Point(10, 10);
			this->listBox1->Name = S"listBox1";
			this->listBox1->Size = System::Drawing::Size(492, 82);
			this->listBox1->TabIndex = 0;
			this->toolTip1->SetToolTip(this->listBox1, S"Select here input Video device, click or dbl-click to connect. If system was alre"
				S"ady connected, it will be closed and re-initialized.");
			this->listBox1->DoubleClick += new System::EventHandler(this, listBox_SelectedIndexChanged);
			this->listBox1->SelectedIndexChanged += new System::EventHandler(this, listBox_SelectedIndexChanged);
			//
			// tabPage3
			//
			this->tabPage3->Controls->Add(this->label6);
			this->tabPage3->Controls->Add(this->panel3);
			this->tabPage3->Controls->Add(this->listBox2);
			this->tabPage3->Controls->Add(this->checkBox9);
			this->tabPage3->DockPadding->All = 10;
			this->tabPage3->Location = System::Drawing::Point(4, 46);
			this->tabPage3->Name = S"tabPage3";
			this->tabPage3->Size = System::Drawing::Size(512, 404);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = S"Audio";
			//
			// label6
			//
			this->label6->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label6->Enabled = false;
			this->label6->Location = System::Drawing::Point(10, 152);
			this->label6->Name = S"label6";
			this->label6->Size = System::Drawing::Size(492, 242);
			this->label6->TabIndex = 6;
			this->label6->Text = S"Audio capture has not been fully implemented jet, some errors may occur.";
			this->label6->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			//
			// panel3
			//
			this->panel3->Controls->Add(this->button6);
			this->panel3->Controls->Add(this->button5);
			this->panel3->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel3->DockPadding->Bottom = 5;
			this->panel3->DockPadding->Top = 5;
			this->panel3->Location = System::Drawing::Point(10, 116);
			this->panel3->Name = S"panel3";
			this->panel3->Size = System::Drawing::Size(492, 36);
			this->panel3->TabIndex = 5;
			//
			// button6
			//
			this->button6->Dock = System::Windows::Forms::DockStyle::Right;
			this->button6->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button6->Location = System::Drawing::Point(404, 5);
			this->button6->Name = S"button6";
			this->button6->Size = System::Drawing::Size(88, 26);
			this->button6->TabIndex = 1;
			this->button6->Text = S"Update";
			this->toolTip1->SetToolTip(this->button6, S"Update current device list. (this will probably make system to disconnect)");
			this->button6->Click += new System::EventHandler(this, button1_Click);
			//
			// button5
			//
			this->button5->Dock = System::Windows::Forms::DockStyle::Left;
			this->button5->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button5->Location = System::Drawing::Point(0, 5);
			this->button5->Name = S"button5";
			this->button5->Size = System::Drawing::Size(120, 26);
			this->button5->TabIndex = 0;
			this->button5->Text = S"Properties..";
			this->toolTip1->SetToolTip(this->button5, S"Show specific driver property page of selected audio device. (must be connected)");
			this->button5->Click += new System::EventHandler(this, button5_Click);
			//
			// listBox2
			//
			this->listBox2->BackColor = System::Drawing::Color::FromArgb((System::Byte)255, (System::Byte)224, (System::Byte)192);
			this->listBox2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->listBox2->Dock = System::Windows::Forms::DockStyle::Top;
			this->listBox2->ItemHeight = 16;
			this->listBox2->Location = System::Drawing::Point(10, 34);
			this->listBox2->Name = S"listBox2";
			this->listBox2->Size = System::Drawing::Size(492, 82);
			this->listBox2->TabIndex = 4;
			this->toolTip1->SetToolTip(this->listBox2, S"Select here input Audio device, click or dbl-click to connect. If system was alre"
				S"ady connected, it will be closed and re-initialized.");
			this->listBox2->DoubleClick += new System::EventHandler(this, listBox_SelectedIndexChanged);
			this->listBox2->SelectedIndexChanged += new System::EventHandler(this, listBox_SelectedIndexChanged);
			//
			// checkBox9
			//
			this->checkBox9->Dock = System::Windows::Forms::DockStyle::Top;
			this->checkBox9->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->checkBox9->Location = System::Drawing::Point(10, 10);
			this->checkBox9->Name = S"checkBox9";
			this->checkBox9->Size = System::Drawing::Size(492, 24);
			this->checkBox9->TabIndex = 3;
			this->checkBox9->Text = S"Enable Audio capture";
			this->toolTip1->SetToolTip(this->checkBox9, S"Changing this value will disconnect current graph.");
			this->checkBox9->CheckedChanged += new System::EventHandler(this, checkBox9_CheckedChanged);
			//
			// tabPage2
			//
			this->tabPage2->Controls->Add(this->checkBox5);
			this->tabPage2->Controls->Add(this->button11);
			this->tabPage2->Controls->Add(this->button4);
			this->tabPage2->Controls->Add(this->button8);
			this->tabPage2->Controls->Add(this->checkBox2);
			this->tabPage2->Controls->Add(this->groupBox3);
			this->tabPage2->Controls->Add(this->groupBox2);
			this->tabPage2->Controls->Add(this->chk_updateall);
			this->tabPage2->DockPadding->All = 10;
			this->tabPage2->Location = System::Drawing::Point(4, 46);
			this->tabPage2->Name = S"tabPage2";
			this->tabPage2->Size = System::Drawing::Size(512, 404);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = S"Capture";
			//
			// checkBox5
			//
			this->checkBox5->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->checkBox5->Location = System::Drawing::Point(424, 186);
			this->checkBox5->Name = S"checkBox5";
			this->checkBox5->Size = System::Drawing::Size(80, 24);
			this->checkBox5->TabIndex = 13;
			this->checkBox5->Text = S"real-time";
			this->checkBox5->CheckedChanged += new System::EventHandler(this, checkBox5_CheckedChanged);
			//
			// button11
			//
			this->button11->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button11->Location = System::Drawing::Point(8, 192);
			this->button11->Name = S"button11";
			this->button11->Size = System::Drawing::Size(240, 24);
			this->button11->TabIndex = 18;
			this->button11->Text = S"VfW Capture Properties..";
			this->toolTip1->SetToolTip(this->button11, S"Show property page of current Video for Windows driver, setup output format here."
				S" (you can\'t preview/capture at the same time!)");
			this->button11->Click += new System::EventHandler(this, button11_Click);
			//
			// button4
			//
			this->button4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button4->Location = System::Drawing::Point(8, 160);
			this->button4->Name = S"button4";
			this->button4->Size = System::Drawing::Size(240, 24);
			this->button4->TabIndex = 17;
			this->button4->Text = S"Capture Graph Properties..";
			this->toolTip1->SetToolTip(this->button4, S"Show property page of current graph, setup output format here. (you can\'t preview"
				S"/capture at the same time!)");
			this->button4->Click += new System::EventHandler(this, button4_Click);
			//
			// button8
			//
			this->button8->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->button8->Location = System::Drawing::Point(309, 214);
			this->button8->Name = S"button8";
			this->button8->Size = System::Drawing::Size(192, 24);
			this->button8->TabIndex = 14;
			this->button8->Text = S"Update Stats now";
			this->button8->Click += new System::EventHandler(this, button8_Click);
			//
			// checkBox2
			//
			this->checkBox2->Appearance = System::Windows::Forms::Appearance::Button;
			this->checkBox2->Location = System::Drawing::Point(8, 120);
			this->checkBox2->Name = S"checkBox2";
			this->checkBox2->Size = System::Drawing::Size(240, 32);
			this->checkBox2->TabIndex = 12;
			this->checkBox2->Text = S"Capture";
			this->checkBox2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->toolTip1->SetToolTip(this->checkBox2, S"Start/Stop captuing..");
			this->checkBox2->Click += new System::EventHandler(this, checkBox2_Click);
			//
			// groupBox3
			//
			this->groupBox3->Controls->Add(this->groupBox5);
			this->groupBox3->Controls->Add(this->lb_info_dr);
			this->groupBox3->Controls->Add(this->label13);
			this->groupBox3->Controls->Add(this->lb_info_fps);
			this->groupBox3->Controls->Add(this->label12);
			this->groupBox3->Controls->Add(this->bl_info_afs);
			this->groupBox3->Controls->Add(this->label8);
			this->groupBox3->Controls->Add(this->lb_info_et);
			this->groupBox3->Controls->Add(this->label5);
			this->groupBox3->Controls->Add(this->lb_info_df);
			this->groupBox3->Controls->Add(this->label9);
			this->groupBox3->Controls->Add(this->lb_info_cf);
			this->groupBox3->Controls->Add(this->label7);
			this->groupBox3->Controls->Add(this->lb_info_fsl);
			this->groupBox3->Controls->Add(this->lb_info_fs);
			this->groupBox3->Controls->Add(this->label3);
			this->groupBox3->Controls->Add(this->label2);
			this->groupBox3->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->groupBox3->Location = System::Drawing::Point(10, 234);
			this->groupBox3->Name = S"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(492, 160);
			this->groupBox3->TabIndex = 11;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = S"Statistics";
			//
			// groupBox5
			//
			this->groupBox5->Location = System::Drawing::Point(238, 22);
			this->groupBox5->Name = S"groupBox5";
			this->groupBox5->Size = System::Drawing::Size(2, 128);
			this->groupBox5->TabIndex = 18;
			this->groupBox5->TabStop = false;
			this->groupBox5->Text = S"groupBox5";
			//
			// lb_info_dr
			//
			this->lb_info_dr->AutoSize = true;
			this->lb_info_dr->Location = System::Drawing::Point(400, 128);
			this->lb_info_dr->Name = S"lb_info_dr";
			this->lb_info_dr->Size = System::Drawing::Size(58, 18);
			this->lb_info_dr->TabIndex = 17;
			this->lb_info_dr->Text = S"unknown";
			//
			// label13
			//
			this->label13->AutoSize = true;
			this->label13->Enabled = false;
			this->label13->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->label13->Location = System::Drawing::Point(264, 128);
			this->label13->Name = S"label13";
			this->label13->Size = System::Drawing::Size(69, 18);
			this->label13->TabIndex = 16;
			this->label13->Text = S"Data Rate:";
			//
			// lb_info_fps
			//
			this->lb_info_fps->AutoSize = true;
			this->lb_info_fps->Location = System::Drawing::Point(400, 56);
			this->lb_info_fps->Name = S"lb_info_fps";
			this->lb_info_fps->Size = System::Drawing::Size(58, 18);
			this->lb_info_fps->TabIndex = 15;
			this->lb_info_fps->Text = S"unknown";
			//
			// label12
			//
			this->label12->AutoSize = true;
			this->label12->Enabled = false;
			this->label12->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->label12->Location = System::Drawing::Point(264, 56);
			this->label12->Name = S"label12";
			this->label12->Size = System::Drawing::Size(79, 18);
			this->label12->TabIndex = 14;
			this->label12->Text = S"Frame Rate:";
			//
			// bl_info_afs
			//
			this->bl_info_afs->AutoSize = true;
			this->bl_info_afs->Location = System::Drawing::Point(400, 104);
			this->bl_info_afs->Name = S"bl_info_afs";
			this->bl_info_afs->Size = System::Drawing::Size(58, 18);
			this->bl_info_afs->TabIndex = 11;
			this->bl_info_afs->Text = S"unknown";
			//
			// label8
			//
			this->label8->AutoSize = true;
			this->label8->Enabled = false;
			this->label8->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->label8->Location = System::Drawing::Point(264, 104);
			this->label8->Name = S"label8";
			this->label8->Size = System::Drawing::Size(124, 18);
			this->label8->TabIndex = 10;
			this->label8->Text = S"Average frame size:";
			//
			// lb_info_et
			//
			this->lb_info_et->AutoSize = true;
			this->lb_info_et->Location = System::Drawing::Point(400, 32);
			this->lb_info_et->Name = S"lb_info_et";
			this->lb_info_et->Size = System::Drawing::Size(58, 18);
			this->lb_info_et->TabIndex = 9;
			this->lb_info_et->Text = S"unknown";
			//
			// label5
			//
			this->label5->AutoSize = true;
			this->label5->Enabled = false;
			this->label5->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->label5->Location = System::Drawing::Point(264, 32);
			this->label5->Name = S"label5";
			this->label5->Size = System::Drawing::Size(90, 18);
			this->label5->TabIndex = 8;
			this->label5->Text = S"Elapsed Time:";
			//
			// lb_info_df
			//
			this->lb_info_df->AutoSize = true;
			this->lb_info_df->Location = System::Drawing::Point(152, 128);
			this->lb_info_df->Name = S"lb_info_df";
			this->lb_info_df->Size = System::Drawing::Size(58, 18);
			this->lb_info_df->TabIndex = 7;
			this->lb_info_df->Text = S"unknown";
			//
			// label9
			//
			this->label9->AutoSize = true;
			this->label9->Enabled = false;
			this->label9->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->label9->Location = System::Drawing::Point(16, 128);
			this->label9->Name = S"label9";
			this->label9->Size = System::Drawing::Size(109, 18);
			this->label9->TabIndex = 6;
			this->label9->Text = S"Dropped Frames:";
			//
			// lb_info_cf
			//
			this->lb_info_cf->AutoSize = true;
			this->lb_info_cf->Location = System::Drawing::Point(152, 104);
			this->lb_info_cf->Name = S"lb_info_cf";
			this->lb_info_cf->Size = System::Drawing::Size(58, 18);
			this->lb_info_cf->TabIndex = 5;
			this->lb_info_cf->Text = S"unknown";
			//
			// label7
			//
			this->label7->AutoSize = true;
			this->label7->Enabled = false;
			this->label7->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->label7->Location = System::Drawing::Point(16, 104);
			this->label7->Name = S"label7";
			this->label7->Size = System::Drawing::Size(113, 18);
			this->label7->TabIndex = 4;
			this->label7->Text = S"Captured Frames:";
			//
			// lb_info_fsl
			//
			this->lb_info_fsl->AutoSize = true;
			this->lb_info_fsl->Location = System::Drawing::Point(152, 56);
			this->lb_info_fsl->Name = S"lb_info_fsl";
			this->lb_info_fsl->Size = System::Drawing::Size(58, 18);
			this->lb_info_fsl->TabIndex = 3;
			this->lb_info_fsl->Text = S"unknown";
			//
			// lb_info_fs
			//
			this->lb_info_fs->AutoSize = true;
			this->lb_info_fs->Location = System::Drawing::Point(152, 32);
			this->lb_info_fs->Name = S"lb_info_fs";
			this->lb_info_fs->Size = System::Drawing::Size(58, 18);
			this->lb_info_fs->TabIndex = 2;
			this->lb_info_fs->Text = S"unknown";
			//
			// label3
			//
			this->label3->AutoSize = true;
			this->label3->Enabled = false;
			this->label3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->label3->Location = System::Drawing::Point(16, 56);
			this->label3->Name = S"label3";
			this->label3->Size = System::Drawing::Size(103, 18);
			this->label3->TabIndex = 1;
			this->label3->Text = S"Free Space Left:";
			//
			// label2
			//
			this->label2->AutoSize = true;
			this->label2->Enabled = false;
			this->label2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->label2->Location = System::Drawing::Point(16, 32);
			this->label2->Name = S"label2";
			this->label2->Size = System::Drawing::Size(101, 18);
			this->label2->TabIndex = 0;
			this->label2->Text = S"Output File size:";
			//
			// groupBox2
			//
			this->groupBox2->Controls->Add(this->panel5);
			this->groupBox2->Dock = System::Windows::Forms::DockStyle::Top;
			this->groupBox2->Location = System::Drawing::Point(10, 10);
			this->groupBox2->Name = S"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(492, 102);
			this->groupBox2->TabIndex = 10;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = S"Current Output";
			//
			// panel5
			//
			this->panel5->Controls->Add(this->panel6);
			this->panel5->Controls->Add(this->tBpath);
			this->panel5->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel5->DockPadding->All = 10;
			this->panel5->Location = System::Drawing::Point(3, 18);
			this->panel5->Name = S"panel5";
			this->panel5->Size = System::Drawing::Size(486, 81);
			this->panel5->TabIndex = 0;
			//
			// panel6
			//
			this->panel6->Controls->Add(this->numericUpDown2);
			this->panel6->Controls->Add(this->label10);
			this->panel6->Controls->Add(this->button7);
			this->panel6->Controls->Add(this->button2);
			this->panel6->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel6->DockPadding->Top = 10;
			this->panel6->Location = System::Drawing::Point(10, 32);
			this->panel6->Name = S"panel6";
			this->panel6->Size = System::Drawing::Size(466, 38);
			this->panel6->TabIndex = 13;
			//
			// numericUpDown2
			//
			this->numericUpDown2->BackColor = System::Drawing::Color::FromArgb((System::Byte)255, (System::Byte)224, (System::Byte)192);
			this->numericUpDown2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			System::Int32 __mcTemp__6[] = new System::Int32[4];
			__mcTemp__6[0] = 12;
			__mcTemp__6[1] = 0;
			__mcTemp__6[2] = 0;
			__mcTemp__6[3] = 0;
			this->numericUpDown2->Increment = System::Decimal(__mcTemp__6);
			this->numericUpDown2->Location = System::Drawing::Point(152, 10);
			System::Int32 __mcTemp__7[] = new System::Int32[4];
			__mcTemp__7[0] = 30000;
			__mcTemp__7[1] = 0;
			__mcTemp__7[2] = 0;
			__mcTemp__7[3] = 0;
			this->numericUpDown2->Maximum = System::Decimal(__mcTemp__7);
			System::Int32 __mcTemp__8[] = new System::Int32[4];
			__mcTemp__8[0] = 1;
			__mcTemp__8[1] = 0;
			__mcTemp__8[2] = 0;
			__mcTemp__8[3] = 0;
			this->numericUpDown2->Minimum = System::Decimal(__mcTemp__8);
			this->numericUpDown2->Name = S"numericUpDown2";
			this->numericUpDown2->Size = System::Drawing::Size(56, 22);
			this->numericUpDown2->TabIndex = 19;
			this->toolTip1->SetToolTip(this->numericUpDown2, S"Pre-allocation file size, maximum value depends on you system, probably up to 4 G"
				S"b.");
			System::Int32 __mcTemp__9[] = new System::Int32[4];
			__mcTemp__9[0] = 120;
			__mcTemp__9[1] = 0;
			__mcTemp__9[2] = 0;
			__mcTemp__9[3] = 0;
			this->numericUpDown2->Value = System::Decimal(__mcTemp__9);
			//
			// label10
			//
			this->label10->AutoSize = true;
			this->label10->Enabled = false;
			this->label10->Location = System::Drawing::Point(208, 16);
			this->label10->Name = S"label10";
			this->label10->Size = System::Drawing::Size(23, 18);
			this->label10->TabIndex = 18;
			this->label10->Text = S"Mb";
			//
			// button7
			//
			this->button7->Dock = System::Windows::Forms::DockStyle::Left;
			this->button7->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button7->Location = System::Drawing::Point(0, 10);
			this->button7->Name = S"button7";
			this->button7->Size = System::Drawing::Size(144, 28);
			this->button7->TabIndex = 16;
			this->button7->Text = S"Pre-Allocate space";
			this->toolTip1->SetToolTip(this->button7, S"Pre-allocate disk space for optimizing our task, file will increase if necessary,"
				S" don\'t mind.");
			this->button7->Click += new System::EventHandler(this, button7_Click);
			//
			// button2
			//
			this->button2->Dock = System::Windows::Forms::DockStyle::Right;
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button2->Location = System::Drawing::Point(338, 10);
			this->button2->Name = S"button2";
			this->button2->Size = System::Drawing::Size(128, 28);
			this->button2->TabIndex = 15;
			this->button2->Text = S"browse..";
			this->toolTip1->SetToolTip(this->button2, S"Select output file..");
			this->button2->Click += new System::EventHandler(this, button2_Click);
			//
			// tBpath
			//
			this->tBpath->BackColor = System::Drawing::Color::FromArgb((System::Byte)255, (System::Byte)224, (System::Byte)192);
			this->tBpath->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->tBpath->Dock = System::Windows::Forms::DockStyle::Top;
			this->tBpath->Location = System::Drawing::Point(10, 10);
			this->tBpath->Name = S"tBpath";
			this->tBpath->ReadOnly = true;
			this->tBpath->Size = System::Drawing::Size(466, 22);
			this->tBpath->TabIndex = 12;
			this->tBpath->Text = S"H:\\output.avi";
			this->toolTip1->SetToolTip(this->tBpath, S"Output filepath (avi file format)");
			this->tBpath->WordWrap = false;
			//
			// chk_updateall
			//
			this->chk_updateall->Checked = true;
			this->chk_updateall->CheckState = System::Windows::Forms::CheckState::Checked;
			this->chk_updateall->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->chk_updateall->Location = System::Drawing::Point(309, 186);
			this->chk_updateall->Name = S"chk_updateall";
			this->chk_updateall->Size = System::Drawing::Size(152, 24);
			this->chk_updateall->TabIndex = 16;
			this->chk_updateall->Text = S"update all Stats";
			//
			// tabPage4
			//
			this->tabPage4->Controls->Add(this->button16);
			this->tabPage4->Controls->Add(this->button14);
			this->tabPage4->Controls->Add(this->checkBox13);
			this->tabPage4->Controls->Add(this->groupBox6);
			this->tabPage4->Controls->Add(this->checkBox11);
			this->tabPage4->DockPadding->All = 10;
			this->tabPage4->Location = System::Drawing::Point(4, 46);
			this->tabPage4->Name = S"tabPage4";
			this->tabPage4->Size = System::Drawing::Size(512, 404);
			this->tabPage4->TabIndex = 3;
			this->tabPage4->Text = S"Grabbing";
			//
			// button16
			//
			this->button16->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button16->Location = System::Drawing::Point(376, 120);
			this->button16->Name = S"button16";
			this->button16->Size = System::Drawing::Size(128, 25);
			this->button16->TabIndex = 6;
			this->button16->Text = S"Properties..";
			this->button16->Click += new System::EventHandler(this, button16_Click);
			//
			// button14
			//
			this->button14->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button14->Location = System::Drawing::Point(8, 184);
			this->button14->Name = S"button14";
			this->button14->Size = System::Drawing::Size(392, 25);
			this->button14->TabIndex = 5;
			this->button14->Text = S"Grab Single frame";
			this->button14->Click += new System::EventHandler(this, button14_Click);
			//
			// checkBox13
			//
			this->checkBox13->Appearance = System::Windows::Forms::Appearance::Button;
			this->checkBox13->Location = System::Drawing::Point(168, 288);
			this->checkBox13->Name = S"checkBox13";
			this->checkBox13->Size = System::Drawing::Size(232, 25);
			this->checkBox13->TabIndex = 4;
			this->checkBox13->Text = S"Grab!";
			this->checkBox13->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->checkBox13->Click += new System::EventHandler(this, checkBox13_Click);
			//
			// groupBox6
			//
			this->groupBox6->Dock = System::Windows::Forms::DockStyle::Top;
			this->groupBox6->Location = System::Drawing::Point(10, 34);
			this->groupBox6->Name = S"groupBox6";
			this->groupBox6->Size = System::Drawing::Size(492, 80);
			this->groupBox6->TabIndex = 2;
			this->groupBox6->TabStop = false;
			this->groupBox6->Text = S"Status";
			//
			// checkBox11
			//
			this->checkBox11->Dock = System::Windows::Forms::DockStyle::Top;
			this->checkBox11->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->checkBox11->Location = System::Drawing::Point(10, 10);
			this->checkBox11->Name = S"checkBox11";
			this->checkBox11->Size = System::Drawing::Size(492, 24);
			this->checkBox11->TabIndex = 1;
			this->checkBox11->Text = S"Enable Grabbing";
			this->checkBox11->Click += new System::EventHandler(this, checkBox11_Click);
			//
			// tabPage5
			//
			this->tabPage5->Controls->Add(this->groupBox7);
			this->tabPage5->Controls->Add(this->button13);
			this->tabPage5->Controls->Add(this->checkBox10);
			this->tabPage5->Controls->Add(this->label11);
			this->tabPage5->Controls->Add(this->numericUpDown3);
			this->tabPage5->Controls->Add(this->checkBox8);
			this->tabPage5->Controls->Add(this->checkBox7);
			this->tabPage5->Controls->Add(this->checkBox4);
			this->tabPage5->Controls->Add(this->checkBox3);
			this->tabPage5->Location = System::Drawing::Point(4, 46);
			this->tabPage5->Name = S"tabPage5";
			this->tabPage5->Size = System::Drawing::Size(512, 404);
			this->tabPage5->TabIndex = 8;
			this->tabPage5->Text = S"Options";
			//
			// groupBox7
			//
			this->groupBox7->Location = System::Drawing::Point(352, 16);
			this->groupBox7->Name = S"groupBox7";
			this->groupBox7->Size = System::Drawing::Size(3, 272);
			this->groupBox7->TabIndex = 34;
			this->groupBox7->TabStop = false;
			this->groupBox7->Text = S"groupBox7";
			//
			// button13
			//
			this->button13->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button13->Location = System::Drawing::Point(376, 24);
			this->button13->Name = S"button13";
			this->button13->Size = System::Drawing::Size(120, 40);
			this->button13->TabIndex = 33;
			this->button13->Text = S"force Showing of preview Window";
			this->button13->Click += new System::EventHandler(this, button13_Click);
			//
			// checkBox10
			//
			this->checkBox10->Checked = true;
			this->checkBox10->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox10->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->checkBox10->Location = System::Drawing::Point(24, 216);
			this->checkBox10->Name = S"checkBox10";
			this->checkBox10->Size = System::Drawing::Size(312, 24);
			this->checkBox10->TabIndex = 32;
			this->checkBox10->Text = S"Enable Frame Rate Control.";
			this->checkBox10->CheckedChanged += new System::EventHandler(this, checkBox10_CheckedChanged);
			//
			// label11
			//
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(24, 352);
			this->label11->Name = S"label11";
			this->label11->Size = System::Drawing::Size(231, 18);
			this->label11->TabIndex = 31;
			this->label11->Text = S"Stats update frequency (updates/sec):";
			//
			// numericUpDown3
			//
			this->numericUpDown3->BackColor = System::Drawing::Color::FromArgb((System::Byte)255, (System::Byte)224, (System::Byte)192);
			this->numericUpDown3->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->numericUpDown3->DecimalPlaces = 3;
			this->numericUpDown3->Location = System::Drawing::Point(264, 352);
			System::Int32 __mcTemp__10[] = new System::Int32[4];
			__mcTemp__10[0] = 55;
			__mcTemp__10[1] = 0;
			__mcTemp__10[2] = 0;
			__mcTemp__10[3] = 0;
			this->numericUpDown3->Maximum = System::Decimal(__mcTemp__10);
			System::Int32 __mcTemp__11[] = new System::Int32[4];
			__mcTemp__11[0] = 1;
			__mcTemp__11[1] = 0;
			__mcTemp__11[2] = 0;
			__mcTemp__11[3] = 196608;
			this->numericUpDown3->Minimum = System::Decimal(__mcTemp__11);
			this->numericUpDown3->Name = S"numericUpDown3";
			this->numericUpDown3->Size = System::Drawing::Size(64, 22);
			this->numericUpDown3->TabIndex = 30;
			this->toolTip1->SetToolTip(this->numericUpDown3, S"Statistics will be updated # times for second (lower value means higher delay)");
			System::Int32 __mcTemp__12[] = new System::Int32[4];
			__mcTemp__12[0] = 25;
			__mcTemp__12[1] = 0;
			__mcTemp__12[2] = 0;
			__mcTemp__12[3] = 0;
			this->numericUpDown3->Value = System::Decimal(__mcTemp__12);
			this->numericUpDown3->ValueChanged += new System::EventHandler(this, numericUpDown3_ValueChanged);
			//
			// checkBox8
			//
			this->checkBox8->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->checkBox8->Location = System::Drawing::Point(24, 48);
			this->checkBox8->Name = S"checkBox8";
			this->checkBox8->Size = System::Drawing::Size(312, 24);
			this->checkBox8->TabIndex = 29;
			this->checkBox8->Text = S"Hide preview Window when stopped.";
			this->toolTip1->SetToolTip(this->checkBox8, S"When you stop preview, windows will be hidden.");
			//
			// checkBox7
			//
			this->checkBox7->Checked = true;
			this->checkBox7->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox7->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->checkBox7->Location = System::Drawing::Point(24, 24);
			this->checkBox7->Name = S"checkBox7";
			this->checkBox7->Size = System::Drawing::Size(312, 24);
			this->checkBox7->TabIndex = 28;
			this->checkBox7->Text = S"Auto-update preview window.";
			this->toolTip1->SetToolTip(this->checkBox7, S"When graph is updated (output format), it will update windows size.");
			this->checkBox7->CheckedChanged += new System::EventHandler(this, checkBox7_CheckedChanged);
			//
			// checkBox4
			//
			this->checkBox4->Enabled = false;
			this->checkBox4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->checkBox4->Location = System::Drawing::Point(24, 144);
			this->checkBox4->Name = S"checkBox4";
			this->checkBox4->Size = System::Drawing::Size(312, 24);
			this->checkBox4->TabIndex = 27;
			this->checkBox4->Text = S"Enable runtime Device Notification.";
			this->toolTip1->SetToolTip(this->checkBox4, S"Enable hot plug detection, list and graphs will be updated when adding/removing d"
				S"evices.");
			//
			// checkBox3
			//
			this->checkBox3->Checked = true;
			this->checkBox3->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->checkBox3->Location = System::Drawing::Point(24, 72);
			this->checkBox3->Name = S"checkBox3";
			this->checkBox3->Size = System::Drawing::Size(312, 24);
			this->checkBox3->TabIndex = 26;
			this->checkBox3->Text = S"Enable built-in Error messages.";
			this->toolTip1->SetToolTip(this->checkBox3, S"Enable vipDirectXInput2 built-in error messages, you should keep this enabled, yo"
				S"u probably will get more error from the same problem but at least you will know "
				S"why that.");
			this->checkBox3->CheckedChanged += new System::EventHandler(this, checkBox3_CheckedChanged);
			//
			// tabPage6
			//
			this->tabPage6->Controls->Add(this->rTBlog);
			this->tabPage6->DockPadding->All = 10;
			this->tabPage6->Location = System::Drawing::Point(4, 46);
			this->tabPage6->Name = S"tabPage6";
			this->tabPage6->Size = System::Drawing::Size(512, 404);
			this->tabPage6->TabIndex = 9;
			this->tabPage6->Text = S"Log";
			//
			// rTBlog
			//
			this->rTBlog->BackColor = System::Drawing::Color::FromArgb((System::Byte)255, (System::Byte)224, (System::Byte)192);
			this->rTBlog->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->rTBlog->Dock = System::Windows::Forms::DockStyle::Fill;
			this->rTBlog->Location = System::Drawing::Point(10, 10);
			this->rTBlog->Name = S"rTBlog";
			this->rTBlog->Size = System::Drawing::Size(492, 384);
			this->rTBlog->TabIndex = 2;
			this->rTBlog->Text = S"richTextBox1";
			//
			// tabPage9
			//
			this->tabPage9->Controls->Add(this->rTBinfo);
			this->tabPage9->DockPadding->All = 10;
			this->tabPage9->Location = System::Drawing::Point(4, 46);
			this->tabPage9->Name = S"tabPage9";
			this->tabPage9->Size = System::Drawing::Size(512, 404);
			this->tabPage9->TabIndex = 10;
			this->tabPage9->Text = S"Module Informations";
			//
			// rTBinfo
			//
			this->rTBinfo->BackColor = System::Drawing::Color::FromArgb((System::Byte)255, (System::Byte)224, (System::Byte)192);
			this->rTBinfo->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->rTBinfo->Dock = System::Windows::Forms::DockStyle::Fill;
			this->rTBinfo->Location = System::Drawing::Point(10, 10);
			this->rTBinfo->Name = S"rTBinfo";
			this->rTBinfo->Size = System::Drawing::Size(492, 384);
			this->rTBinfo->TabIndex = 3;
			this->rTBinfo->Text = S"vipDirectXInput2\n\t\tversion 0.8.7\n\nUsing\nThis is a very complex class, problably w"
				S"e need more debug, but worked well in most tests.\n\nImportant Notes\n\nDo NOT open "
				S"more instance of this window, old connected device will be released.\n\nDocumentat"
				S"ion\nhttp://lnx.ewgate.net/viplib/documentation/html/classvip_direct_x_input2.htm"
				S"l\n\nLicense\nCopyright Alessandro Polo 2005, open source project, code is based on"
				S" Microsoft DirectX SDK Samples.";
			//
			// saveFileDialog1
			//
			this->saveFileDialog1->DefaultExt = S"avi";
			this->saveFileDialog1->FileName = S"output.avi";
			this->saveFileDialog1->Filter = S"Microsoft Audio Video Interleaved (*.AVI)|*.avi|All Files (*.*)|*.*";
			this->saveFileDialog1->Title = S"Render Stream As..";
			//
			// timer1
			//
			this->timer1->Interval = 40;
			this->timer1->Tick += new System::EventHandler(this, button8_Click);
			//
			// contextMenu1
			//
			System::Windows::Forms::MenuItem* __mcTemp__13[] = new System::Windows::Forms::MenuItem*[5];
			__mcTemp__13[0] = this->menuItem3;
			__mcTemp__13[1] = this->menuItem1;
			__mcTemp__13[2] = this->menuItem2;
			__mcTemp__13[3] = this->menuItem4;
			__mcTemp__13[4] = this->menuItem5;
			this->contextMenu1->MenuItems->AddRange(__mcTemp__13);
			//
			// menuItem3
			//
			this->menuItem3->Index = 0;
			this->menuItem3->Text = S"1 frame";
			//
			// menuItem1
			//
			this->menuItem1->Index = 1;
			this->menuItem1->Text = S"10 frames";
			//
			// menuItem2
			//
			this->menuItem2->Index = 2;
			this->menuItem2->Text = S"100 Frames";
			//
			// menuItem4
			//
			this->menuItem4->Index = 3;
			this->menuItem4->Text = S"500 Frames";
			//
			// menuItem5
			//
			this->menuItem5->Index = 4;
			this->menuItem5->Text = S"1000 Frames";
			//
			// dxcaptureForm
			//
			this->AutoScaleBaseSize = System::Drawing::Size(6, 15);
			this->ClientSize = System::Drawing::Size(520, 526);
			this->Controls->Add(this->tabControl1);
			this->Controls->Add(this->panel1);
			this->Name = S"dxcaptureForm";
			this->Text = S"vipDirectXInput2 Interface 1.0";
			this->Closing += new System::ComponentModel::CancelEventHandler(this, dxcaptureForm_Closing);
			this->Load += new System::EventHandler(this, dxcaptureForm_Load);
			this->Closed += new System::EventHandler(this, dxcaptureForm_Closed);
			this->panel1->ResumeLayout(false);
			(__try_cast<System::ComponentModel::ISupportInitialize *  >(this->nUDfps))->EndInit();
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->groupBox4->ResumeLayout(false);
			this->groupBox1->ResumeLayout(false);
			this->panel4->ResumeLayout(false);
			(__try_cast<System::ComponentModel::ISupportInitialize *  >(this->numericUpDown1))->EndInit();
			this->panel2->ResumeLayout(false);
			this->tabPage3->ResumeLayout(false);
			this->panel3->ResumeLayout(false);
			this->tabPage2->ResumeLayout(false);
			this->groupBox3->ResumeLayout(false);
			this->groupBox2->ResumeLayout(false);
			this->panel5->ResumeLayout(false);
			this->panel6->ResumeLayout(false);
			(__try_cast<System::ComponentModel::ISupportInitialize *  >(this->numericUpDown2))->EndInit();
			this->tabPage4->ResumeLayout(false);
			this->tabPage5->ResumeLayout(false);
			(__try_cast<System::ComponentModel::ISupportInitialize *  >(this->numericUpDown3))->EndInit();
			this->tabPage6->ResumeLayout(false);
			this->tabPage9->ResumeLayout(false);
			this->ResumeLayout(false);

		}
	private: System::Void button3_Click(System::Object *  sender, System::EventArgs *  e);

private: System::Void button4_Click(System::Object *  sender, System::EventArgs *  e);

private: System::Void checkBox1_Click(System::Object *  sender, System::EventArgs *  e);
private: System::Void checkBox2_Click(System::Object *  sender, System::EventArgs *  e);

private: System::Void numericUpDown1_ValueChanged(System::Object *  sender, System::EventArgs *  e);

private: System::Void button2_Click(System::Object *  sender, System::EventArgs *  e);

private: System::Void button1_Click(System::Object *  sender, System::EventArgs *  e);


private: System::Void tabControl1_SelectedIndexChanged(System::Object *  sender, System::EventArgs *  e)
		 {
		 }

private: System::Void dxcaptureForm_Load(System::Object *  sender, System::EventArgs *  e);

private: System::Void dxcaptureForm_Closing(System::Object *  sender, System::ComponentModel::CancelEventArgs *  e);

private: System::Void dxcaptureForm_Closed(System::Object *  sender, System::EventArgs *  e);


private: System::Void button7_Click(System::Object *  sender, System::EventArgs *  e);


private: System::Void button8_Click(System::Object *  sender, System::EventArgs *  e);

private: System::Void button9_Click(System::Object *  sender, System::EventArgs *  e);


private: System::Void checkBox3_CheckedChanged(System::Object *  sender, System::EventArgs *  e);

private: System::Void button5_Click(System::Object *  sender, System::EventArgs *  e);

private: System::Void checkBox6_CheckedChanged(System::Object *  sender, System::EventArgs *  e);

private: System::Void button10_Click(System::Object *  sender, System::EventArgs *  e);

private: System::Void checkBox7_CheckedChanged(System::Object *  sender, System::EventArgs *  e);

private: System::Void listBox_SelectedIndexChanged(System::Object *  sender, System::EventArgs *  e);


private: System::Void checkBox5_CheckedChanged(System::Object *  sender, System::EventArgs *  e)
		 {
			 timer1->Enabled = checkBox5->Checked;
		 }

private: System::Void numericUpDown3_ValueChanged(System::Object *  sender, System::EventArgs *  e)
		 {
			 timer1->Interval = (int)(1000.0 / Convert::ToDouble(numericUpDown3->Value) );
		 }

private: System::Void checkBox9_CheckedChanged(System::Object *  sender, System::EventArgs *  e);



private: System::Void button11_Click(System::Object *  sender, System::EventArgs *  e);


private: System::Void button12_Click(System::Object *  sender, System::EventArgs *  e);

private: System::Void checkBox10_CheckedChanged(System::Object *  sender, System::EventArgs *  e);

private: System::Void checkBox11_Click(System::Object *  sender, System::EventArgs *  e);

private: System::Void button13_Click(System::Object *  sender, System::EventArgs *  e);

private: System::Void checkBox13_Click(System::Object *  sender, System::EventArgs *  e);

private: System::Void button14_Click(System::Object *  sender, System::EventArgs *  e);

private: System::Void button15_Click(System::Object *  sender, System::EventArgs *  e);

private: System::Void button16_Click(System::Object *  sender, System::EventArgs *  e);


private: System::Void button17_Click(System::Object *  sender, System::EventArgs *  e)
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

private: static int thLoop;
private: void pushFrames(int iLoop);
private: void pushFrames();
private: void pushFramesMT(int iLoop);

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



};
}
