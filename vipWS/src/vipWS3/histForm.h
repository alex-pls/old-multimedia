#pragma once

#include "../../../../source/vipHist.h"
#include "../../../../source/vipUtility.h"
#include "sourceInterface.h"
#include "outputInterface.h"


using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Drawing::Imaging;
using namespace System::IO;


namespace vipWS3
{
	/// <summary>
	/// Riepilogo per histForm
	///
	/// AVVISO: se si modifica il nome della classe, sarà necessario modificare la
	///          proprietà "Nome file di risorse" relativa allo strumento di compilazione delle risorse gestite
	///          associato a tutti i file RESX da cui dipende la classe. In caso contrario,
	///          le finestre di progettazione non saranno in grado di interagire correttamente con le
	///          risorse localizzate associate al form.
	/// </summary>
	public __gc class histForm : public System::Windows::Forms::Form, public outputInterface
	{
	public:
		histForm(void);

		void Init() {};

		VIPRESULT importFrom(vipFrameRGB24* img);


	protected:
		void Dispose(Boolean disposing);


	private: vipHist* myInst;
	private: vipFrameRGB24* hBuffer;
	private: sourceInterface* sF;

	private: Bitmap* bm_M;
	private: Bitmap* bm_R;
	private: Bitmap* bm_G;
	private: Bitmap* bm_B;

	private: System::Windows::Forms::Panel *  panel1;
	private: System::Windows::Forms::TabControl *  tabControl1;
	private: System::Windows::Forms::TabPage *  tabPage1;
	private: System::Windows::Forms::TabPage *  tabPage2;
	private: System::Windows::Forms::TabPage *  tabPage3;
	private: System::Windows::Forms::RichTextBox *  rTBinfo;
	private: System::Windows::Forms::Panel *  panel5;
	private: System::Windows::Forms::Panel *  panel4;
	private: System::Windows::Forms::Panel *  panel3;
	private: System::Windows::Forms::Panel *  panel2;
	private: System::Windows::Forms::Panel *  panel6;
	private: System::Windows::Forms::Panel *  panel7;
	private: System::Windows::Forms::Panel *  panel8;
	private: System::Windows::Forms::Panel *  panel9;
	private: System::Windows::Forms::Button *  button3;
	private: System::Windows::Forms::ComboBox *  cBsources;
	private: System::Windows::Forms::Panel *  panel10;
	private: System::Windows::Forms::Panel *  panel11;
	private: System::Windows::Forms::Panel *  panel12;
	private: System::Windows::Forms::Panel *  panel13;
	private: System::Windows::Forms::ListBox *  lBinfo;
	private: System::Windows::Forms::TabControl *  tabControl2;
	private: System::Windows::Forms::TabPage *  tabPage4;
	private: System::Windows::Forms::TabPage *  tabPage5;
	private: System::Windows::Forms::TabPage *  tabPage6;
	private: System::Windows::Forms::TabPage *  tabPage7;
	private: System::Windows::Forms::Panel *  panel14;
	private: System::Windows::Forms::Panel *  panel15;
	private: System::Windows::Forms::Panel *  panel16;
	private: System::Windows::Forms::Panel *  panel17;
	private: System::Windows::Forms::CheckBox *  cBdraw_M;
	private: System::Windows::Forms::PictureBox *  pBdraw_M;
	private: System::Windows::Forms::PictureBox *  pBdraw_R;
	private: System::Windows::Forms::Panel *  panel18;
	private: System::Windows::Forms::Panel *  panel19;
	private: System::Windows::Forms::CheckBox *  cBdraw_R;
	private: System::Windows::Forms::Panel *  panel20;
	private: System::Windows::Forms::Panel *  panel21;
	private: System::Windows::Forms::PictureBox *  pBdraw_G;
	private: System::Windows::Forms::Panel *  panel22;
	private: System::Windows::Forms::Panel *  panel23;
	private: System::Windows::Forms::CheckBox *  cBdraw_G;
	private: System::Windows::Forms::Panel *  panel24;
	private: System::Windows::Forms::Panel *  panel25;
	private: System::Windows::Forms::PictureBox *  pBdraw_B;
	private: System::Windows::Forms::Panel *  panel26;
	private: System::Windows::Forms::Panel *  panel27;
	private: System::Windows::Forms::CheckBox *  cBdraw_B;
	private: System::Windows::Forms::Panel *  panel28;
	private: System::Windows::Forms::Panel *  panel29;

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
			System::Resources::ResourceManager *  resources = new System::Resources::ResourceManager(__typeof(vipWS3::histForm));
			this->panel1 = new System::Windows::Forms::Panel();
			this->button3 = new System::Windows::Forms::Button();
			this->cBsources = new System::Windows::Forms::ComboBox();
			this->tabControl1 = new System::Windows::Forms::TabControl();
			this->tabPage1 = new System::Windows::Forms::TabPage();
			this->tabControl2 = new System::Windows::Forms::TabControl();
			this->tabPage4 = new System::Windows::Forms::TabPage();
			this->pBdraw_M = new System::Windows::Forms::PictureBox();
			this->panel14 = new System::Windows::Forms::Panel();
			this->panel15 = new System::Windows::Forms::Panel();
			this->cBdraw_M = new System::Windows::Forms::CheckBox();
			this->panel16 = new System::Windows::Forms::Panel();
			this->panel17 = new System::Windows::Forms::Panel();
			this->tabPage5 = new System::Windows::Forms::TabPage();
			this->pBdraw_R = new System::Windows::Forms::PictureBox();
			this->panel18 = new System::Windows::Forms::Panel();
			this->panel19 = new System::Windows::Forms::Panel();
			this->cBdraw_R = new System::Windows::Forms::CheckBox();
			this->panel20 = new System::Windows::Forms::Panel();
			this->panel21 = new System::Windows::Forms::Panel();
			this->tabPage6 = new System::Windows::Forms::TabPage();
			this->pBdraw_G = new System::Windows::Forms::PictureBox();
			this->panel22 = new System::Windows::Forms::Panel();
			this->panel23 = new System::Windows::Forms::Panel();
			this->cBdraw_G = new System::Windows::Forms::CheckBox();
			this->panel24 = new System::Windows::Forms::Panel();
			this->panel25 = new System::Windows::Forms::Panel();
			this->tabPage7 = new System::Windows::Forms::TabPage();
			this->pBdraw_B = new System::Windows::Forms::PictureBox();
			this->panel26 = new System::Windows::Forms::Panel();
			this->panel27 = new System::Windows::Forms::Panel();
			this->cBdraw_B = new System::Windows::Forms::CheckBox();
			this->panel28 = new System::Windows::Forms::Panel();
			this->panel29 = new System::Windows::Forms::Panel();
			this->panel10 = new System::Windows::Forms::Panel();
			this->panel11 = new System::Windows::Forms::Panel();
			this->panel12 = new System::Windows::Forms::Panel();
			this->panel13 = new System::Windows::Forms::Panel();
			this->tabPage2 = new System::Windows::Forms::TabPage();
			this->lBinfo = new System::Windows::Forms::ListBox();
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
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->tabControl2->SuspendLayout();
			this->tabPage4->SuspendLayout();
			this->panel15->SuspendLayout();
			this->tabPage5->SuspendLayout();
			this->panel19->SuspendLayout();
			this->tabPage6->SuspendLayout();
			this->panel23->SuspendLayout();
			this->tabPage7->SuspendLayout();
			this->panel27->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->tabPage3->SuspendLayout();
			this->SuspendLayout();
			//
			// panel1
			//
			this->panel1->Controls->Add(this->button3);
			this->panel1->Controls->Add(this->cBsources);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel1->Location = System::Drawing::Point(0, 342);
			this->panel1->Name = S"panel1";
			this->panel1->Size = System::Drawing::Size(488, 48);
			this->panel1->TabIndex = 0;
			//
			// button3
			//
			this->button3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button3->Location = System::Drawing::Point(352, 8);
			this->button3->Name = S"button3";
			this->button3->Size = System::Drawing::Size(112, 23);
			this->button3->TabIndex = 5;
			this->button3->Text = S"load frame";
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
			this->cBsources->Size = System::Drawing::Size(328, 24);
			this->cBsources->TabIndex = 4;
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
			this->tabControl1->Size = System::Drawing::Size(488, 342);
			this->tabControl1->TabIndex = 1;
			//
			// tabPage1
			//
			this->tabPage1->Controls->Add(this->tabControl2);
			this->tabPage1->Controls->Add(this->panel10);
			this->tabPage1->Controls->Add(this->panel11);
			this->tabPage1->Controls->Add(this->panel12);
			this->tabPage1->Controls->Add(this->panel13);
			this->tabPage1->Location = System::Drawing::Point(4, 25);
			this->tabPage1->Name = S"tabPage1";
			this->tabPage1->Size = System::Drawing::Size(480, 313);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = S"Graphic Histogram";
			//
			// tabControl2
			//
			this->tabControl2->Appearance = System::Windows::Forms::TabAppearance::Buttons;
			this->tabControl2->Controls->Add(this->tabPage4);
			this->tabControl2->Controls->Add(this->tabPage5);
			this->tabControl2->Controls->Add(this->tabPage6);
			this->tabControl2->Controls->Add(this->tabPage7);
			this->tabControl2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tabControl2->Location = System::Drawing::Point(8, 8);
			this->tabControl2->Name = S"tabControl2";
			this->tabControl2->Padding = System::Drawing::Point(24, 3);
			this->tabControl2->SelectedIndex = 0;
			this->tabControl2->Size = System::Drawing::Size(464, 297);
			this->tabControl2->TabIndex = 21;
			//
			// tabPage4
			//
			this->tabPage4->Controls->Add(this->pBdraw_M);
			this->tabPage4->Controls->Add(this->panel14);
			this->tabPage4->Controls->Add(this->panel15);
			this->tabPage4->Controls->Add(this->panel16);
			this->tabPage4->Controls->Add(this->panel17);
			this->tabPage4->Location = System::Drawing::Point(4, 28);
			this->tabPage4->Name = S"tabPage4";
			this->tabPage4->Size = System::Drawing::Size(456, 265);
			this->tabPage4->TabIndex = 0;
			this->tabPage4->Text = S"Mixed";
			//
			// pBdraw_M
			//
			this->pBdraw_M->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pBdraw_M->Location = System::Drawing::Point(8, 8);
			this->pBdraw_M->Name = S"pBdraw_M";
			this->pBdraw_M->Size = System::Drawing::Size(440, 241);
			this->pBdraw_M->TabIndex = 20;
			this->pBdraw_M->TabStop = false;
			//
			// panel14
			//
			this->panel14->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel14->Location = System::Drawing::Point(8, 0);
			this->panel14->Name = S"panel14";
			this->panel14->Size = System::Drawing::Size(440, 8);
			this->panel14->TabIndex = 19;
			//
			// panel15
			//
			this->panel15->Controls->Add(this->cBdraw_M);
			this->panel15->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel15->Location = System::Drawing::Point(8, 249);
			this->panel15->Name = S"panel15";
			this->panel15->Size = System::Drawing::Size(440, 16);
			this->panel15->TabIndex = 18;
			//
			// cBdraw_M
			//
			this->cBdraw_M->Checked = true;
			this->cBdraw_M->CheckState = System::Windows::Forms::CheckState::Checked;
			this->cBdraw_M->Location = System::Drawing::Point(0, 0);
			this->cBdraw_M->Name = S"cBdraw_M";
			this->cBdraw_M->Size = System::Drawing::Size(176, 16);
			this->cBdraw_M->TabIndex = 2;
			this->cBdraw_M->Text = S"Always draw histogram";
			//
			// panel16
			//
			this->panel16->Dock = System::Windows::Forms::DockStyle::Right;
			this->panel16->Location = System::Drawing::Point(448, 0);
			this->panel16->Name = S"panel16";
			this->panel16->Size = System::Drawing::Size(8, 265);
			this->panel16->TabIndex = 17;
			//
			// panel17
			//
			this->panel17->Dock = System::Windows::Forms::DockStyle::Left;
			this->panel17->Location = System::Drawing::Point(0, 0);
			this->panel17->Name = S"panel17";
			this->panel17->Size = System::Drawing::Size(8, 265);
			this->panel17->TabIndex = 16;
			//
			// tabPage5
			//
			this->tabPage5->Controls->Add(this->pBdraw_R);
			this->tabPage5->Controls->Add(this->panel18);
			this->tabPage5->Controls->Add(this->panel19);
			this->tabPage5->Controls->Add(this->panel20);
			this->tabPage5->Controls->Add(this->panel21);
			this->tabPage5->Location = System::Drawing::Point(4, 28);
			this->tabPage5->Name = S"tabPage5";
			this->tabPage5->Size = System::Drawing::Size(456, 265);
			this->tabPage5->TabIndex = 1;
			this->tabPage5->Text = S"RED";
			this->tabPage5->Visible = false;
			//
			// pBdraw_R
			//
			this->pBdraw_R->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pBdraw_R->Location = System::Drawing::Point(8, 8);
			this->pBdraw_R->Name = S"pBdraw_R";
			this->pBdraw_R->Size = System::Drawing::Size(440, 241);
			this->pBdraw_R->TabIndex = 25;
			this->pBdraw_R->TabStop = false;
			//
			// panel18
			//
			this->panel18->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel18->Location = System::Drawing::Point(8, 0);
			this->panel18->Name = S"panel18";
			this->panel18->Size = System::Drawing::Size(440, 8);
			this->panel18->TabIndex = 24;
			//
			// panel19
			//
			this->panel19->Controls->Add(this->cBdraw_R);
			this->panel19->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel19->Location = System::Drawing::Point(8, 249);
			this->panel19->Name = S"panel19";
			this->panel19->Size = System::Drawing::Size(440, 16);
			this->panel19->TabIndex = 23;
			//
			// cBdraw_R
			//
			this->cBdraw_R->Checked = true;
			this->cBdraw_R->CheckState = System::Windows::Forms::CheckState::Checked;
			this->cBdraw_R->Location = System::Drawing::Point(0, 0);
			this->cBdraw_R->Name = S"cBdraw_R";
			this->cBdraw_R->Size = System::Drawing::Size(176, 16);
			this->cBdraw_R->TabIndex = 2;
			this->cBdraw_R->Text = S"Always draw histogram";
			//
			// panel20
			//
			this->panel20->Dock = System::Windows::Forms::DockStyle::Right;
			this->panel20->Location = System::Drawing::Point(448, 0);
			this->panel20->Name = S"panel20";
			this->panel20->Size = System::Drawing::Size(8, 265);
			this->panel20->TabIndex = 22;
			//
			// panel21
			//
			this->panel21->Dock = System::Windows::Forms::DockStyle::Left;
			this->panel21->Location = System::Drawing::Point(0, 0);
			this->panel21->Name = S"panel21";
			this->panel21->Size = System::Drawing::Size(8, 265);
			this->panel21->TabIndex = 21;
			//
			// tabPage6
			//
			this->tabPage6->Controls->Add(this->pBdraw_G);
			this->tabPage6->Controls->Add(this->panel22);
			this->tabPage6->Controls->Add(this->panel23);
			this->tabPage6->Controls->Add(this->panel24);
			this->tabPage6->Controls->Add(this->panel25);
			this->tabPage6->Location = System::Drawing::Point(4, 28);
			this->tabPage6->Name = S"tabPage6";
			this->tabPage6->Size = System::Drawing::Size(456, 265);
			this->tabPage6->TabIndex = 2;
			this->tabPage6->Text = S"GREEN";
			this->tabPage6->Visible = false;
			//
			// pBdraw_G
			//
			this->pBdraw_G->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pBdraw_G->Location = System::Drawing::Point(8, 8);
			this->pBdraw_G->Name = S"pBdraw_G";
			this->pBdraw_G->Size = System::Drawing::Size(440, 241);
			this->pBdraw_G->TabIndex = 25;
			this->pBdraw_G->TabStop = false;
			//
			// panel22
			//
			this->panel22->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel22->Location = System::Drawing::Point(8, 0);
			this->panel22->Name = S"panel22";
			this->panel22->Size = System::Drawing::Size(440, 8);
			this->panel22->TabIndex = 24;
			//
			// panel23
			//
			this->panel23->Controls->Add(this->cBdraw_G);
			this->panel23->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel23->Location = System::Drawing::Point(8, 249);
			this->panel23->Name = S"panel23";
			this->panel23->Size = System::Drawing::Size(440, 16);
			this->panel23->TabIndex = 23;
			//
			// cBdraw_G
			//
			this->cBdraw_G->Checked = true;
			this->cBdraw_G->CheckState = System::Windows::Forms::CheckState::Checked;
			this->cBdraw_G->Location = System::Drawing::Point(0, 0);
			this->cBdraw_G->Name = S"cBdraw_G";
			this->cBdraw_G->Size = System::Drawing::Size(176, 16);
			this->cBdraw_G->TabIndex = 2;
			this->cBdraw_G->Text = S"Always draw histogram";
			//
			// panel24
			//
			this->panel24->Dock = System::Windows::Forms::DockStyle::Right;
			this->panel24->Location = System::Drawing::Point(448, 0);
			this->panel24->Name = S"panel24";
			this->panel24->Size = System::Drawing::Size(8, 265);
			this->panel24->TabIndex = 22;
			//
			// panel25
			//
			this->panel25->Dock = System::Windows::Forms::DockStyle::Left;
			this->panel25->Location = System::Drawing::Point(0, 0);
			this->panel25->Name = S"panel25";
			this->panel25->Size = System::Drawing::Size(8, 265);
			this->panel25->TabIndex = 21;
			//
			// tabPage7
			//
			this->tabPage7->Controls->Add(this->pBdraw_B);
			this->tabPage7->Controls->Add(this->panel26);
			this->tabPage7->Controls->Add(this->panel27);
			this->tabPage7->Controls->Add(this->panel28);
			this->tabPage7->Controls->Add(this->panel29);
			this->tabPage7->Location = System::Drawing::Point(4, 28);
			this->tabPage7->Name = S"tabPage7";
			this->tabPage7->Size = System::Drawing::Size(456, 265);
			this->tabPage7->TabIndex = 3;
			this->tabPage7->Text = S"BLUE";
			this->tabPage7->Visible = false;
			//
			// pBdraw_B
			//
			this->pBdraw_B->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pBdraw_B->Location = System::Drawing::Point(8, 8);
			this->pBdraw_B->Name = S"pBdraw_B";
			this->pBdraw_B->Size = System::Drawing::Size(440, 241);
			this->pBdraw_B->TabIndex = 25;
			this->pBdraw_B->TabStop = false;
			//
			// panel26
			//
			this->panel26->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel26->Location = System::Drawing::Point(8, 0);
			this->panel26->Name = S"panel26";
			this->panel26->Size = System::Drawing::Size(440, 8);
			this->panel26->TabIndex = 24;
			//
			// panel27
			//
			this->panel27->Controls->Add(this->cBdraw_B);
			this->panel27->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel27->Location = System::Drawing::Point(8, 249);
			this->panel27->Name = S"panel27";
			this->panel27->Size = System::Drawing::Size(440, 16);
			this->panel27->TabIndex = 23;
			//
			// cBdraw_B
			//
			this->cBdraw_B->Checked = true;
			this->cBdraw_B->CheckState = System::Windows::Forms::CheckState::Checked;
			this->cBdraw_B->Location = System::Drawing::Point(0, 0);
			this->cBdraw_B->Name = S"cBdraw_B";
			this->cBdraw_B->Size = System::Drawing::Size(176, 16);
			this->cBdraw_B->TabIndex = 2;
			this->cBdraw_B->Text = S"Always draw histogram";
			//
			// panel28
			//
			this->panel28->Dock = System::Windows::Forms::DockStyle::Right;
			this->panel28->Location = System::Drawing::Point(448, 0);
			this->panel28->Name = S"panel28";
			this->panel28->Size = System::Drawing::Size(8, 265);
			this->panel28->TabIndex = 22;
			//
			// panel29
			//
			this->panel29->Dock = System::Windows::Forms::DockStyle::Left;
			this->panel29->Location = System::Drawing::Point(0, 0);
			this->panel29->Name = S"panel29";
			this->panel29->Size = System::Drawing::Size(8, 265);
			this->panel29->TabIndex = 21;
			//
			// panel10
			//
			this->panel10->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel10->Location = System::Drawing::Point(8, 0);
			this->panel10->Name = S"panel10";
			this->panel10->Size = System::Drawing::Size(464, 8);
			this->panel10->TabIndex = 19;
			//
			// panel11
			//
			this->panel11->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel11->Location = System::Drawing::Point(8, 305);
			this->panel11->Name = S"panel11";
			this->panel11->Size = System::Drawing::Size(464, 8);
			this->panel11->TabIndex = 18;
			//
			// panel12
			//
			this->panel12->Dock = System::Windows::Forms::DockStyle::Right;
			this->panel12->Location = System::Drawing::Point(472, 0);
			this->panel12->Name = S"panel12";
			this->panel12->Size = System::Drawing::Size(8, 313);
			this->panel12->TabIndex = 17;
			//
			// panel13
			//
			this->panel13->Dock = System::Windows::Forms::DockStyle::Left;
			this->panel13->Location = System::Drawing::Point(0, 0);
			this->panel13->Name = S"panel13";
			this->panel13->Size = System::Drawing::Size(8, 313);
			this->panel13->TabIndex = 16;
			//
			// tabPage2
			//
			this->tabPage2->Controls->Add(this->lBinfo);
			this->tabPage2->Controls->Add(this->panel6);
			this->tabPage2->Controls->Add(this->panel7);
			this->tabPage2->Controls->Add(this->panel8);
			this->tabPage2->Controls->Add(this->panel9);
			this->tabPage2->Location = System::Drawing::Point(4, 25);
			this->tabPage2->Name = S"tabPage2";
			this->tabPage2->Size = System::Drawing::Size(480, 313);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = S"Image Informations";
			//
			// lBinfo
			//
			this->lBinfo->BackColor = System::Drawing::Color::FromArgb((System::Byte)255, (System::Byte)224, (System::Byte)192);
			this->lBinfo->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lBinfo->ColumnWidth = 100;
			this->lBinfo->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lBinfo->ItemHeight = 16;
			this->lBinfo->Location = System::Drawing::Point(8, 8);
			this->lBinfo->MultiColumn = true;
			this->lBinfo->Name = S"lBinfo";
			this->lBinfo->Size = System::Drawing::Size(464, 297);
			this->lBinfo->TabIndex = 16;
			//
			// panel6
			//
			this->panel6->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel6->Location = System::Drawing::Point(8, 0);
			this->panel6->Name = S"panel6";
			this->panel6->Size = System::Drawing::Size(464, 8);
			this->panel6->TabIndex = 15;
			//
			// panel7
			//
			this->panel7->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel7->Location = System::Drawing::Point(8, 305);
			this->panel7->Name = S"panel7";
			this->panel7->Size = System::Drawing::Size(464, 8);
			this->panel7->TabIndex = 14;
			//
			// panel8
			//
			this->panel8->Dock = System::Windows::Forms::DockStyle::Right;
			this->panel8->Location = System::Drawing::Point(472, 0);
			this->panel8->Name = S"panel8";
			this->panel8->Size = System::Drawing::Size(8, 313);
			this->panel8->TabIndex = 13;
			//
			// panel9
			//
			this->panel9->Dock = System::Windows::Forms::DockStyle::Left;
			this->panel9->Location = System::Drawing::Point(0, 0);
			this->panel9->Name = S"panel9";
			this->panel9->Size = System::Drawing::Size(8, 313);
			this->panel9->TabIndex = 12;
			//
			// tabPage3
			//
			this->tabPage3->Controls->Add(this->rTBinfo);
			this->tabPage3->Controls->Add(this->panel5);
			this->tabPage3->Controls->Add(this->panel4);
			this->tabPage3->Controls->Add(this->panel3);
			this->tabPage3->Controls->Add(this->panel2);
			this->tabPage3->Location = System::Drawing::Point(4, 25);
			this->tabPage3->Name = S"tabPage3";
			this->tabPage3->Size = System::Drawing::Size(480, 313);
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
			this->rTBinfo->Size = System::Drawing::Size(464, 297);
			this->rTBinfo->TabIndex = 12;
			this->rTBinfo->Text = S"";
			this->rTBinfo->LinkClicked += new System::Windows::Forms::LinkClickedEventHandler(this, rTBinfo_LinkClicked);
			//
			// panel5
			//
			this->panel5->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel5->Location = System::Drawing::Point(8, 0);
			this->panel5->Name = S"panel5";
			this->panel5->Size = System::Drawing::Size(464, 8);
			this->panel5->TabIndex = 11;
			//
			// panel4
			//
			this->panel4->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel4->Location = System::Drawing::Point(8, 305);
			this->panel4->Name = S"panel4";
			this->panel4->Size = System::Drawing::Size(464, 8);
			this->panel4->TabIndex = 10;
			//
			// panel3
			//
			this->panel3->Dock = System::Windows::Forms::DockStyle::Right;
			this->panel3->Location = System::Drawing::Point(472, 0);
			this->panel3->Name = S"panel3";
			this->panel3->Size = System::Drawing::Size(8, 313);
			this->panel3->TabIndex = 9;
			//
			// panel2
			//
			this->panel2->Dock = System::Windows::Forms::DockStyle::Left;
			this->panel2->Location = System::Drawing::Point(0, 0);
			this->panel2->Name = S"panel2";
			this->panel2->Size = System::Drawing::Size(8, 313);
			this->panel2->TabIndex = 8;
			//
			// histForm
			//
			this->AutoScaleBaseSize = System::Drawing::Size(6, 15);
			this->ClientSize = System::Drawing::Size(488, 390);
			this->Controls->Add(this->tabControl1);
			this->Controls->Add(this->panel1);
			this->Icon = (__try_cast<System::Drawing::Icon *  >(resources->GetObject(S"$this.Icon")));
			this->Name = S"histForm";
			this->Text = S"Histogram - vipHist Interface 1.0";
			this->Closing += new System::ComponentModel::CancelEventHandler(this, histForm_Closing);
			this->Load += new System::EventHandler(this, histForm_Load);
			this->panel1->ResumeLayout(false);
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabControl2->ResumeLayout(false);
			this->tabPage4->ResumeLayout(false);
			this->panel15->ResumeLayout(false);
			this->tabPage5->ResumeLayout(false);
			this->panel19->ResumeLayout(false);
			this->tabPage6->ResumeLayout(false);
			this->panel23->ResumeLayout(false);
			this->tabPage7->ResumeLayout(false);
			this->panel27->ResumeLayout(false);
			this->tabPage2->ResumeLayout(false);
			this->tabPage3->ResumeLayout(false);
			this->ResumeLayout(false);

		}
		//
private: System::Void histForm_Load(System::Object *  sender, System::EventArgs *  e);
private: System::Void histForm_Closing(System::Object *  sender, System::ComponentModel::CancelEventArgs *  e);

private: System::Void button3_Click(System::Object *  sender, System::EventArgs *  e);

private: void drawGraph(int channel);


////////////////////////////////////////////////////////////////////////////
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

private: System::Void cBsources_SelectedIndexChanged(System::Object *  sender, System::EventArgs *  e)
		 {
			 for (int i=0; i<this->MdiParent->MdiChildren->Count; i++)
			 {

				 if ( static_cast<Form*>(this->MdiParent->MdiChildren->get_Item(i))->Text->Equals(cBsources->SelectedItem->ToString() ))
				{
					sF = static_cast<sourceInterface*>(this->MdiParent->MdiChildren->get_Item(i));
					break;
				}
			 }
		 }




private: System::Void rTBinfo_LinkClicked(System::Object *  sender, System::Windows::Forms::LinkClickedEventArgs *  e)
		 {
			 System::Diagnostics::Process::Start(e->LinkText);
		 }

};
}
