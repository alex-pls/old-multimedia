#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Diagnostics;
using namespace System::Diagnostics;


namespace vipWS3
{
	/// <summary>
	/// Riepilogo per statsForm
	///
	/// AVVISO: se si modifica il nome della classe, sarà necessario modificare la
	///          proprietà "Nome file di risorse" relativa allo strumento di compilazione delle risorse gestite
	///          associato a tutti i file RESX da cui dipende la classe. In caso contrario,
	///          le finestre di progettazione non saranno in grado di interagire correttamente con le
	///          risorse localizzate associate al form.
	/// </summary>
	public __gc class statsForm : public System::Windows::Forms::Form
	{
	public:
		statsForm(void)
		{
			InitializeComponent();
		}

	protected:
		void Dispose(Boolean disposing)
		{
			if (disposing && components)
			{
				components->Dispose();
			}
			__super::Dispose(disposing);
		}

	private: Process *p[];

	private: System::Windows::Forms::Panel *  panel1;
	private: System::Windows::Forms::TabControl *  tabControl1;
	private: System::Windows::Forms::TabPage *  tabPage1;
	private: System::Windows::Forms::Panel *  panel2;
	private: System::Windows::Forms::Panel *  panel7;
	private: System::Windows::Forms::Panel *  panel8;
	private: System::Windows::Forms::Panel *  panel6;
	private: System::Windows::Forms::TabPage *  tabPage2;
	private: System::Windows::Forms::Label *  label1;
	private: System::Windows::Forms::Button *  button1;
	private: System::Windows::Forms::TreeView *  tVsystem;
	private: System::Windows::Forms::TabPage *  tabPage3;
	private: System::Windows::Forms::TabPage *  tabPage4;
	private: System::Windows::Forms::TabPage *  tabPage5;
	private: System::Windows::Forms::Panel *  panel3;
	private: System::Windows::Forms::Panel *  panel4;
	private: System::Windows::Forms::Panel *  panel9;
	private: System::Windows::Forms::Panel *  panel10;
	private: System::Windows::Forms::Panel *  panel5;
	private: System::Windows::Forms::Panel *  panel11;
	private: System::Windows::Forms::Panel *  panel12;
	private: System::Windows::Forms::ListBox *  lBprocess;
	private: System::Windows::Forms::Label *  label2;
	private: System::Windows::Forms::Label *  label3;
	private: System::Windows::Forms::ListBox *  lBthread;


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
			this->button1 = new System::Windows::Forms::Button();
			this->tabControl1 = new System::Windows::Forms::TabControl();
			this->tabPage1 = new System::Windows::Forms::TabPage();
			this->tVsystem = new System::Windows::Forms::TreeView();
			this->panel2 = new System::Windows::Forms::Panel();
			this->panel7 = new System::Windows::Forms::Panel();
			this->panel8 = new System::Windows::Forms::Panel();
			this->panel6 = new System::Windows::Forms::Panel();
			this->tabPage5 = new System::Windows::Forms::TabPage();
			this->panel12 = new System::Windows::Forms::Panel();
			this->lBprocess = new System::Windows::Forms::ListBox();
			this->label2 = new System::Windows::Forms::Label();
			this->panel11 = new System::Windows::Forms::Panel();
			this->panel5 = new System::Windows::Forms::Panel();
			this->lBthread = new System::Windows::Forms::ListBox();
			this->label3 = new System::Windows::Forms::Label();
			this->panel9 = new System::Windows::Forms::Panel();
			this->panel10 = new System::Windows::Forms::Panel();
			this->panel4 = new System::Windows::Forms::Panel();
			this->panel3 = new System::Windows::Forms::Panel();
			this->tabPage2 = new System::Windows::Forms::TabPage();
			this->label1 = new System::Windows::Forms::Label();
			this->tabPage3 = new System::Windows::Forms::TabPage();
			this->tabPage4 = new System::Windows::Forms::TabPage();
			this->panel1->SuspendLayout();
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->tabPage5->SuspendLayout();
			this->panel12->SuspendLayout();
			this->panel5->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->SuspendLayout();
			//
			// panel1
			//
			this->panel1->Controls->Add(this->button1);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel1->Location = System::Drawing::Point(0, 374);
			this->panel1->Name = S"panel1";
			this->panel1->Size = System::Drawing::Size(384, 40);
			this->panel1->TabIndex = 1;
			//
			// button1
			//
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Location = System::Drawing::Point(280, 8);
			this->button1->Name = S"button1";
			this->button1->Size = System::Drawing::Size(90, 25);
			this->button1->TabIndex = 0;
			this->button1->Text = S"Update";
			this->button1->Click += new System::EventHandler(this, button1_Click);
			//
			// tabControl1
			//
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage5);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Controls->Add(this->tabPage4);
			this->tabControl1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tabControl1->Location = System::Drawing::Point(0, 0);
			this->tabControl1->Multiline = true;
			this->tabControl1->Name = S"tabControl1";
			this->tabControl1->Padding = System::Drawing::Point(12, 4);
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(384, 374);
			this->tabControl1->TabIndex = 2;
			//
			// tabPage1
			//
			this->tabPage1->Controls->Add(this->tVsystem);
			this->tabPage1->Controls->Add(this->panel2);
			this->tabPage1->Controls->Add(this->panel7);
			this->tabPage1->Controls->Add(this->panel8);
			this->tabPage1->Controls->Add(this->panel6);
			this->tabPage1->Location = System::Drawing::Point(4, 50);
			this->tabPage1->Name = S"tabPage1";
			this->tabPage1->Size = System::Drawing::Size(376, 320);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = S"System";
			//
			// tVsystem
			//
			this->tVsystem->BackColor = System::Drawing::Color::FromArgb((System::Byte)255, (System::Byte)224, (System::Byte)192);
			this->tVsystem->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->tVsystem->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tVsystem->ImageIndex = -1;
			this->tVsystem->Location = System::Drawing::Point(8, 16);
			this->tVsystem->Name = S"tVsystem";
			this->tVsystem->SelectedImageIndex = -1;
			this->tVsystem->Size = System::Drawing::Size(360, 288);
			this->tVsystem->TabIndex = 20;
			//
			// panel2
			//
			this->panel2->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel2->Location = System::Drawing::Point(8, 0);
			this->panel2->Name = S"panel2";
			this->panel2->Size = System::Drawing::Size(360, 16);
			this->panel2->TabIndex = 19;
			//
			// panel7
			//
			this->panel7->Dock = System::Windows::Forms::DockStyle::Right;
			this->panel7->Location = System::Drawing::Point(368, 0);
			this->panel7->Name = S"panel7";
			this->panel7->Size = System::Drawing::Size(8, 304);
			this->panel7->TabIndex = 18;
			//
			// panel8
			//
			this->panel8->Dock = System::Windows::Forms::DockStyle::Left;
			this->panel8->Location = System::Drawing::Point(0, 0);
			this->panel8->Name = S"panel8";
			this->panel8->Size = System::Drawing::Size(8, 304);
			this->panel8->TabIndex = 17;
			//
			// panel6
			//
			this->panel6->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel6->Location = System::Drawing::Point(0, 304);
			this->panel6->Name = S"panel6";
			this->panel6->Size = System::Drawing::Size(376, 16);
			this->panel6->TabIndex = 13;
			//
			// tabPage5
			//
			this->tabPage5->Controls->Add(this->panel12);
			this->tabPage5->Controls->Add(this->panel11);
			this->tabPage5->Controls->Add(this->panel5);
			this->tabPage5->Controls->Add(this->panel9);
			this->tabPage5->Controls->Add(this->panel10);
			this->tabPage5->Controls->Add(this->panel4);
			this->tabPage5->Controls->Add(this->panel3);
			this->tabPage5->Location = System::Drawing::Point(4, 50);
			this->tabPage5->Name = S"tabPage5";
			this->tabPage5->Size = System::Drawing::Size(376, 320);
			this->tabPage5->TabIndex = 4;
			this->tabPage5->Text = S"System Processes";
			//
			// panel12
			//
			this->panel12->Controls->Add(this->lBprocess);
			this->panel12->Controls->Add(this->label2);
			this->panel12->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel12->Location = System::Drawing::Point(8, 0);
			this->panel12->Name = S"panel12";
			this->panel12->Size = System::Drawing::Size(360, 160);
			this->panel12->TabIndex = 8;
			//
			// lBprocess
			//
			this->lBprocess->BackColor = System::Drawing::Color::FromArgb((System::Byte)255, (System::Byte)224, (System::Byte)192);
			this->lBprocess->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lBprocess->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lBprocess->ItemHeight = 16;
			this->lBprocess->Location = System::Drawing::Point(0, 23);
			this->lBprocess->Name = S"lBprocess";
			this->lBprocess->Size = System::Drawing::Size(360, 137);
			this->lBprocess->TabIndex = 1;
			this->lBprocess->SelectedIndexChanged += new System::EventHandler(this, lBprocess_SelectedIndexChanged);
			//
			// label2
			//
			this->label2->Dock = System::Windows::Forms::DockStyle::Top;
			this->label2->Location = System::Drawing::Point(0, 0);
			this->label2->Name = S"label2";
			this->label2->Size = System::Drawing::Size(360, 23);
			this->label2->TabIndex = 0;
			this->label2->Text = S"Processes";
			this->label2->TextAlign = System::Drawing::ContentAlignment::BottomRight;
			//
			// panel11
			//
			this->panel11->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel11->Location = System::Drawing::Point(8, 160);
			this->panel11->Name = S"panel11";
			this->panel11->Size = System::Drawing::Size(360, 8);
			this->panel11->TabIndex = 7;
			//
			// panel5
			//
			this->panel5->Controls->Add(this->lBthread);
			this->panel5->Controls->Add(this->label3);
			this->panel5->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel5->Location = System::Drawing::Point(8, 168);
			this->panel5->Name = S"panel5";
			this->panel5->Size = System::Drawing::Size(360, 104);
			this->panel5->TabIndex = 6;
			//
			// lBthread
			//
			this->lBthread->BackColor = System::Drawing::Color::FromArgb((System::Byte)255, (System::Byte)224, (System::Byte)192);
			this->lBthread->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lBthread->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lBthread->ItemHeight = 16;
			this->lBthread->Location = System::Drawing::Point(0, 23);
			this->lBthread->Name = S"lBthread";
			this->lBthread->Size = System::Drawing::Size(360, 81);
			this->lBthread->TabIndex = 1;
			//
			// label3
			//
			this->label3->Dock = System::Windows::Forms::DockStyle::Top;
			this->label3->Location = System::Drawing::Point(0, 0);
			this->label3->Name = S"label3";
			this->label3->Size = System::Drawing::Size(360, 23);
			this->label3->TabIndex = 0;
			this->label3->Text = S"Threads";
			this->label3->TextAlign = System::Drawing::ContentAlignment::BottomRight;
			//
			// panel9
			//
			this->panel9->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel9->Location = System::Drawing::Point(8, 272);
			this->panel9->Name = S"panel9";
			this->panel9->Size = System::Drawing::Size(360, 8);
			this->panel9->TabIndex = 5;
			//
			// panel10
			//
			this->panel10->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel10->Location = System::Drawing::Point(8, 280);
			this->panel10->Name = S"panel10";
			this->panel10->Size = System::Drawing::Size(360, 40);
			this->panel10->TabIndex = 4;
			//
			// panel4
			//
			this->panel4->Dock = System::Windows::Forms::DockStyle::Right;
			this->panel4->Location = System::Drawing::Point(368, 0);
			this->panel4->Name = S"panel4";
			this->panel4->Size = System::Drawing::Size(8, 320);
			this->panel4->TabIndex = 1;
			//
			// panel3
			//
			this->panel3->Dock = System::Windows::Forms::DockStyle::Left;
			this->panel3->Location = System::Drawing::Point(0, 0);
			this->panel3->Name = S"panel3";
			this->panel3->Size = System::Drawing::Size(8, 320);
			this->panel3->TabIndex = 0;
			//
			// tabPage2
			//
			this->tabPage2->Controls->Add(this->label1);
			this->tabPage2->Location = System::Drawing::Point(4, 50);
			this->tabPage2->Name = S"tabPage2";
			this->tabPage2->Size = System::Drawing::Size(376, 320);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = S"Threads";
			this->tabPage2->Visible = false;
			//
			// label1
			//
			this->label1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->label1->Enabled = false;
			this->label1->Location = System::Drawing::Point(0, 0);
			this->label1->Name = S"label1";
			this->label1->Size = System::Drawing::Size(376, 320);
			this->label1->TabIndex = 0;
			this->label1->Text = S"MultiThreading Engine is not functional yet.";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			//
			// tabPage3
			//
			this->tabPage3->Location = System::Drawing::Point(4, 50);
			this->tabPage3->Name = S"tabPage3";
			this->tabPage3->Size = System::Drawing::Size(376, 320);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = S"tabPage3";
			//
			// tabPage4
			//
			this->tabPage4->Location = System::Drawing::Point(4, 50);
			this->tabPage4->Name = S"tabPage4";
			this->tabPage4->Size = System::Drawing::Size(376, 320);
			this->tabPage4->TabIndex = 3;
			this->tabPage4->Text = S"tabPage4";
			//
			// statsForm
			//
			this->AutoScaleBaseSize = System::Drawing::Size(6, 15);
			this->ClientSize = System::Drawing::Size(384, 414);
			this->Controls->Add(this->tabControl1);
			this->Controls->Add(this->panel1);
			this->Name = S"statsForm";
			this->Text = S"Statistics";
			this->Closing += new System::ComponentModel::CancelEventHandler(this, statsForm_Closing);
			this->Load += new System::EventHandler(this, statsForm_Load);
			this->Closed += new System::EventHandler(this, statsForm_Closed);
			this->panel1->ResumeLayout(false);
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage5->ResumeLayout(false);
			this->panel12->ResumeLayout(false);
			this->panel5->ResumeLayout(false);
			this->tabPage2->ResumeLayout(false);
			this->ResumeLayout(false);

		}
		//
private: System::Void button1_Click(System::Object *  sender, System::EventArgs *  e);

private: System::Void statsForm_Load(System::Object *  sender, System::EventArgs *  e);

private: System::Void statsForm_Closing(System::Object *  sender, System::ComponentModel::CancelEventArgs *  e);

private: System::Void lBprocess_SelectedIndexChanged(System::Object *  sender, System::EventArgs *  e)
		 {
			lBthread->Items->Clear();
			if (lBprocess->SelectedIndex == -1)
				return;

//			ProcessThreadCollection *tC = p[lBprocess->SelectedIndex]->Threads;

//			for (int i=0; i < tC->Count; i++)
//			 {
//				 lBthread->Items->Add(String::Format(S"{0}", tC->Item[i]->Id.ToString() ));
//			 }

		 }

private: System::Void statsForm_Closed(System::Object *  sender, System::EventArgs *  e);


};
}
