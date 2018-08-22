#pragma once
#include "../../../../source/vipUtility.h"
#include "../../../../source/outputs/vipDoctor.h"
#include "outputInterface.h"

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
	/// Riepilogo per doctorForm
	///
	/// AVVISO: se si modifica il nome della classe, sarà necessario modificare la
	///          proprietà "Nome file di risorse" relativa allo strumento di compilazione delle risorse gestite
	///          associato a tutti i file RESX da cui dipende la classe. In caso contrario,
	///          le finestre di progettazione non saranno in grado di interagire correttamente con le
	///          risorse localizzate associate al form.
	/// </summary>
	public __gc class doctorForm : public System::Windows::Forms::Form, public outputInterface
	{
	public:
		doctorForm(void);

		void Init(void);

		VIPRESULT importFrom(vipFrameRGB24* img);

		void sourcesUpdate(void) { }
		int setSource(sourceInterface* sF) { return 0; }
public: System::Object __gc* getObjectInstance() { return this; };

	protected:
		void Dispose(Boolean disposing);

	private: vipDoctor* myDoctor;
	private: bool autoReflesh;


















	private: System::Windows::Forms::Panel *  panel6;
	private: System::Windows::Forms::Button *  button1;
	private: System::Windows::Forms::Button *  button2;
	private: System::Windows::Forms::Panel *  panel7;
	private: System::Windows::Forms::CheckBox *  cBautoUpdate;
	private: System::Windows::Forms::TabControl *  tabControl1;
	private: System::Windows::Forms::TabPage *  tabPage1;
	private: System::Windows::Forms::GroupBox *  groupBox2;
	private: System::Windows::Forms::Label *  label6;
	private: System::Windows::Forms::TextBox *  tBcext;
	private: System::Windows::Forms::Label *  label3;
	private: System::Windows::Forms::TextBox *  tBcfps;
	private: System::Windows::Forms::Panel *  panel5;
	private: System::Windows::Forms::GroupBox *  groupBox1;
	private: System::Windows::Forms::Label *  label5;
	private: System::Windows::Forms::TextBox *  tBaext;
	private: System::Windows::Forms::Label *  label2;
	private: System::Windows::Forms::TextBox *  tBafps;
	private: System::Windows::Forms::Panel *  panel4;
	private: System::Windows::Forms::Panel *  panel3;
	private: System::Windows::Forms::Panel *  panel2;
	private: System::Windows::Forms::Panel *  panel1;
	private: System::Windows::Forms::TabPage *  tabPage2;
	private: System::Windows::Forms::Label *  label1;
	private: System::Windows::Forms::TabPage *  tabPage3;
	private: System::Windows::Forms::RichTextBox *  rTBinfo;
	private: System::Windows::Forms::Panel *  panel8;
	private: System::Windows::Forms::Panel *  panel9;
	private: System::Windows::Forms::Panel *  panel10;
	private: System::Windows::Forms::Panel *  panel11;


































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
			System::Resources::ResourceManager *  resources = new System::Resources::ResourceManager(__typeof(vipWS3::doctorForm));
			this->panel6 = new System::Windows::Forms::Panel();
			this->button2 = new System::Windows::Forms::Button();
			this->button1 = new System::Windows::Forms::Button();
			this->panel7 = new System::Windows::Forms::Panel();
			this->cBautoUpdate = new System::Windows::Forms::CheckBox();
			this->tabControl1 = new System::Windows::Forms::TabControl();
			this->tabPage1 = new System::Windows::Forms::TabPage();
			this->groupBox2 = new System::Windows::Forms::GroupBox();
			this->label6 = new System::Windows::Forms::Label();
			this->tBcext = new System::Windows::Forms::TextBox();
			this->label3 = new System::Windows::Forms::Label();
			this->tBcfps = new System::Windows::Forms::TextBox();
			this->panel5 = new System::Windows::Forms::Panel();
			this->groupBox1 = new System::Windows::Forms::GroupBox();
			this->label5 = new System::Windows::Forms::Label();
			this->tBaext = new System::Windows::Forms::TextBox();
			this->label2 = new System::Windows::Forms::Label();
			this->tBafps = new System::Windows::Forms::TextBox();
			this->panel4 = new System::Windows::Forms::Panel();
			this->panel3 = new System::Windows::Forms::Panel();
			this->panel2 = new System::Windows::Forms::Panel();
			this->panel1 = new System::Windows::Forms::Panel();
			this->tabPage2 = new System::Windows::Forms::TabPage();
			this->label1 = new System::Windows::Forms::Label();
			this->tabPage3 = new System::Windows::Forms::TabPage();
			this->rTBinfo = new System::Windows::Forms::RichTextBox();
			this->panel8 = new System::Windows::Forms::Panel();
			this->panel9 = new System::Windows::Forms::Panel();
			this->panel10 = new System::Windows::Forms::Panel();
			this->panel11 = new System::Windows::Forms::Panel();
			this->panel6->SuspendLayout();
			this->panel7->SuspendLayout();
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->tabPage3->SuspendLayout();
			this->SuspendLayout();
			//
			// panel6
			//
			this->panel6->Controls->Add(this->button2);
			this->panel6->Controls->Add(this->button1);
			this->panel6->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel6->Location = System::Drawing::Point(0, 310);
			this->panel6->Name = S"panel6";
			this->panel6->Size = System::Drawing::Size(376, 48);
			this->panel6->TabIndex = 16;
			//
			// button2
			//
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button2->Location = System::Drawing::Point(256, 8);
			this->button2->Name = S"button2";
			this->button2->Size = System::Drawing::Size(112, 32);
			this->button2->TabIndex = 14;
			this->button2->Text = S"Reset";
			this->button2->Click += new System::EventHandler(this, button2_Click);
			//
			// button1
			//
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Location = System::Drawing::Point(8, 8);
			this->button1->Name = S"button1";
			this->button1->Size = System::Drawing::Size(168, 32);
			this->button1->TabIndex = 12;
			this->button1->Text = S"Update Informations";
			this->button1->Click += new System::EventHandler(this, button1_Click);
			//
			// panel7
			//
			this->panel7->Controls->Add(this->cBautoUpdate);
			this->panel7->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel7->Location = System::Drawing::Point(0, 286);
			this->panel7->Name = S"panel7";
			this->panel7->Size = System::Drawing::Size(376, 24);
			this->panel7->TabIndex = 18;
			//
			// cBautoUpdate
			//
			this->cBautoUpdate->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->cBautoUpdate->Location = System::Drawing::Point(8, 0);
			this->cBautoUpdate->Name = S"cBautoUpdate";
			this->cBautoUpdate->Size = System::Drawing::Size(312, 24);
			this->cBautoUpdate->TabIndex = 18;
			this->cBautoUpdate->Text = S"Auto-Reflesh (real time informations)";
			//
			// tabControl1
			//
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tabControl1->Location = System::Drawing::Point(0, 0);
			this->tabControl1->Name = S"tabControl1";
			this->tabControl1->Padding = System::Drawing::Point(12, 3);
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(376, 286);
			this->tabControl1->TabIndex = 19;
			//
			// tabPage1
			//
			this->tabPage1->Controls->Add(this->groupBox2);
			this->tabPage1->Controls->Add(this->panel5);
			this->tabPage1->Controls->Add(this->groupBox1);
			this->tabPage1->Controls->Add(this->panel4);
			this->tabPage1->Controls->Add(this->panel3);
			this->tabPage1->Controls->Add(this->panel2);
			this->tabPage1->Controls->Add(this->panel1);
			this->tabPage1->Location = System::Drawing::Point(4, 25);
			this->tabPage1->Name = S"tabPage1";
			this->tabPage1->Size = System::Drawing::Size(368, 257);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = S"Stream Informations";
			//
			// groupBox2
			//
			this->groupBox2->Controls->Add(this->label6);
			this->groupBox2->Controls->Add(this->tBcext);
			this->groupBox2->Controls->Add(this->label3);
			this->groupBox2->Controls->Add(this->tBcfps);
			this->groupBox2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->groupBox2->Location = System::Drawing::Point(8, 128);
			this->groupBox2->Name = S"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(352, 121);
			this->groupBox2->TabIndex = 20;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = S"Current Frame Rate";
			//
			// label6
			//
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(216, 88);
			this->label6->Name = S"label6";
			this->label6->Size = System::Drawing::Size(78, 18);
			this->label6->TabIndex = 13;
			this->label6->Text = S"milliseconds";
			//
			// tBcext
			//
			this->tBcext->BackColor = System::Drawing::Color::FromArgb((System::Byte)255, (System::Byte)224, (System::Byte)192);
			this->tBcext->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->tBcext->Font = new System::Drawing::Font(S"Verdana", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (System::Byte)0);
			this->tBcext->Location = System::Drawing::Point(16, 80);
			this->tBcext->Name = S"tBcext";
			this->tBcext->ReadOnly = true;
			this->tBcext->Size = System::Drawing::Size(200, 28);
			this->tBcext->TabIndex = 12;
			this->tBcext->Text = S"";
			//
			// label3
			//
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(216, 48);
			this->label3->Name = S"label3";
			this->label3->Size = System::Drawing::Size(23, 18);
			this->label3->TabIndex = 11;
			this->label3->Text = S"fps";
			//
			// tBcfps
			//
			this->tBcfps->BackColor = System::Drawing::Color::FromArgb((System::Byte)255, (System::Byte)224, (System::Byte)192);
			this->tBcfps->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->tBcfps->Font = new System::Drawing::Font(S"Verdana", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (System::Byte)0);
			this->tBcfps->Location = System::Drawing::Point(16, 32);
			this->tBcfps->Name = S"tBcfps";
			this->tBcfps->ReadOnly = true;
			this->tBcfps->Size = System::Drawing::Size(200, 35);
			this->tBcfps->TabIndex = 10;
			this->tBcfps->Text = S"";
			//
			// panel5
			//
			this->panel5->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel5->Location = System::Drawing::Point(8, 120);
			this->panel5->Name = S"panel5";
			this->panel5->Size = System::Drawing::Size(352, 8);
			this->panel5->TabIndex = 18;
			//
			// groupBox1
			//
			this->groupBox1->Controls->Add(this->label5);
			this->groupBox1->Controls->Add(this->tBaext);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->tBafps);
			this->groupBox1->Dock = System::Windows::Forms::DockStyle::Top;
			this->groupBox1->Location = System::Drawing::Point(8, 8);
			this->groupBox1->Name = S"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(352, 112);
			this->groupBox1->TabIndex = 17;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = S"Average Frame Rate";
			//
			// label5
			//
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(216, 80);
			this->label5->Name = S"label5";
			this->label5->Size = System::Drawing::Size(78, 18);
			this->label5->TabIndex = 11;
			this->label5->Text = S"milliseconds";
			//
			// tBaext
			//
			this->tBaext->BackColor = System::Drawing::Color::FromArgb((System::Byte)255, (System::Byte)224, (System::Byte)192);
			this->tBaext->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->tBaext->Font = new System::Drawing::Font(S"Verdana", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (System::Byte)0);
			this->tBaext->Location = System::Drawing::Point(16, 72);
			this->tBaext->Name = S"tBaext";
			this->tBaext->ReadOnly = true;
			this->tBaext->Size = System::Drawing::Size(200, 28);
			this->tBaext->TabIndex = 10;
			this->tBaext->Text = S"";
			//
			// label2
			//
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(216, 48);
			this->label2->Name = S"label2";
			this->label2->Size = System::Drawing::Size(23, 18);
			this->label2->TabIndex = 9;
			this->label2->Text = S"fps";
			//
			// tBafps
			//
			this->tBafps->BackColor = System::Drawing::Color::FromArgb((System::Byte)255, (System::Byte)224, (System::Byte)192);
			this->tBafps->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->tBafps->Font = new System::Drawing::Font(S"Verdana", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (System::Byte)0);
			this->tBafps->Location = System::Drawing::Point(16, 32);
			this->tBafps->Name = S"tBafps";
			this->tBafps->ReadOnly = true;
			this->tBafps->Size = System::Drawing::Size(200, 35);
			this->tBafps->TabIndex = 8;
			this->tBafps->Text = S"";
			//
			// panel4
			//
			this->panel4->Dock = System::Windows::Forms::DockStyle::Right;
			this->panel4->Location = System::Drawing::Point(360, 8);
			this->panel4->Name = S"panel4";
			this->panel4->Size = System::Drawing::Size(8, 241);
			this->panel4->TabIndex = 16;
			//
			// panel3
			//
			this->panel3->Dock = System::Windows::Forms::DockStyle::Left;
			this->panel3->Location = System::Drawing::Point(0, 8);
			this->panel3->Name = S"panel3";
			this->panel3->Size = System::Drawing::Size(8, 241);
			this->panel3->TabIndex = 15;
			//
			// panel2
			//
			this->panel2->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel2->Location = System::Drawing::Point(0, 249);
			this->panel2->Name = S"panel2";
			this->panel2->Size = System::Drawing::Size(368, 8);
			this->panel2->TabIndex = 14;
			//
			// panel1
			//
			this->panel1->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel1->Location = System::Drawing::Point(0, 0);
			this->panel1->Name = S"panel1";
			this->panel1->Size = System::Drawing::Size(368, 8);
			this->panel1->TabIndex = 12;
			//
			// tabPage2
			//
			this->tabPage2->Controls->Add(this->label1);
			this->tabPage2->Location = System::Drawing::Point(4, 25);
			this->tabPage2->Name = S"tabPage2";
			this->tabPage2->Size = System::Drawing::Size(536, 353);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = S"Settings";
			this->tabPage2->Visible = false;
			//
			// label1
			//
			this->label1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label1->Enabled = false;
			this->label1->Location = System::Drawing::Point(0, 0);
			this->label1->Name = S"label1";
			this->label1->Size = System::Drawing::Size(536, 353);
			this->label1->TabIndex = 0;
			this->label1->Text = S"vipDoctor is not functional jet.";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			//
			// tabPage3
			//
			this->tabPage3->Controls->Add(this->rTBinfo);
			this->tabPage3->Controls->Add(this->panel8);
			this->tabPage3->Controls->Add(this->panel9);
			this->tabPage3->Controls->Add(this->panel10);
			this->tabPage3->Controls->Add(this->panel11);
			this->tabPage3->Location = System::Drawing::Point(4, 25);
			this->tabPage3->Name = S"tabPage3";
			this->tabPage3->Size = System::Drawing::Size(536, 353);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = S"Module Informations";
			this->tabPage3->Visible = false;
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
			this->rTBinfo->Size = System::Drawing::Size(520, 337);
			this->rTBinfo->TabIndex = 17;
			this->rTBinfo->Text = S"";
			this->rTBinfo->LinkClicked += new System::Windows::Forms::LinkClickedEventHandler(this, rTBinfo_LinkClicked);
			//
			// panel8
			//
			this->panel8->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel8->Location = System::Drawing::Point(8, 0);
			this->panel8->Name = S"panel8";
			this->panel8->Size = System::Drawing::Size(520, 8);
			this->panel8->TabIndex = 16;
			//
			// panel9
			//
			this->panel9->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel9->Location = System::Drawing::Point(8, 345);
			this->panel9->Name = S"panel9";
			this->panel9->Size = System::Drawing::Size(520, 8);
			this->panel9->TabIndex = 15;
			//
			// panel10
			//
			this->panel10->Dock = System::Windows::Forms::DockStyle::Right;
			this->panel10->Location = System::Drawing::Point(528, 0);
			this->panel10->Name = S"panel10";
			this->panel10->Size = System::Drawing::Size(8, 353);
			this->panel10->TabIndex = 14;
			//
			// panel11
			//
			this->panel11->Dock = System::Windows::Forms::DockStyle::Left;
			this->panel11->Location = System::Drawing::Point(0, 0);
			this->panel11->Name = S"panel11";
			this->panel11->Size = System::Drawing::Size(8, 353);
			this->panel11->TabIndex = 13;
			//
			// doctorForm
			//
			this->AutoScaleBaseSize = System::Drawing::Size(6, 15);
			this->ClientSize = System::Drawing::Size(376, 358);
			this->Controls->Add(this->tabControl1);
			this->Controls->Add(this->panel7);
			this->Controls->Add(this->panel6);
			this->Icon = (__try_cast<System::Drawing::Icon *  >(resources->GetObject(S"$this.Icon")));
			this->Name = S"doctorForm";
			this->Text = S"vipDoctor 0.4";
			this->Closing += new System::ComponentModel::CancelEventHandler(this, doctorForm_Closing);
			this->Load += new System::EventHandler(this, doctorForm_Load);
			this->panel6->ResumeLayout(false);
			this->panel7->ResumeLayout(false);
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->groupBox2->ResumeLayout(false);
			this->groupBox1->ResumeLayout(false);
			this->tabPage2->ResumeLayout(false);
			this->tabPage3->ResumeLayout(false);
			this->ResumeLayout(false);

		}
		//
		void doctorForm::updateInfos(void);

private: System::Void button1_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 updateInfos();
		 }

private: System::Void button2_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 myDoctor->reset();
		 }
private: System::Void cBautoUpdate_CheckedChanged(System::Object *  sender, System::EventArgs *  e)
		 {
			 autoReflesh = cBautoUpdate->Checked;
		 }

private: System::Void doctorForm_Closing(System::Object *  sender, System::ComponentModel::CancelEventArgs *  e);


private: System::Void rTBinfo_LinkClicked(System::Object *  sender, System::Windows::Forms::LinkClickedEventArgs *  e)
		 {
			 System::Diagnostics::Process::Start(e->LinkText);
		 }

private: System::Void doctorForm_Load(System::Object *  sender, System::EventArgs *  e)
		 {
			String* path = String::Concat(Path::GetDirectoryName(Application::ExecutablePath), S"\\reference\\vipDoctor.info.rtf");

			if ( File::Exists(path) )
				rTBinfo->LoadFile(path , RichTextBoxStreamType::RichText);
			else
			{
				rTBinfo->Text = "ERROR\r\n\r\nCouln't load data file: \r\n";
				rTBinfo->AppendText(path);
			}

		 }

};
}
