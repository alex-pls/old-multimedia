#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace vipWS3
{
	/// <summary>
	/// Riepilogo per optionForm
	///
	/// AVVISO: se si modifica il nome della classe, sarà necessario modificare la
	///          proprietà "Nome file di risorse" relativa allo strumento di compilazione delle risorse gestite
	///          associato a tutti i file RESX da cui dipende la classe. In caso contrario,
	///          le finestre di progettazione non saranno in grado di interagire correttamente con le
	///          risorse localizzate associate al form.
	/// </summary>
	public __gc class optionForm : public System::Windows::Forms::Form
	{
	public:
		optionForm(void)
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
	private: System::Windows::Forms::Panel *  panel1;
	private: System::Windows::Forms::TabControl *  tabControl1;
	private: System::Windows::Forms::TabPage *  tabPage1;
	private: System::Windows::Forms::TabPage *  tabPage2;
	private: System::Windows::Forms::TabPage *  tabPage3;
	private: System::Windows::Forms::Button *  button1;
	private: System::Windows::Forms::Button *  button2;



	private: System::Windows::Forms::CheckBox *  checkBox1;
	private: System::Windows::Forms::CheckBox *  checkBox2;
	private: System::Windows::Forms::CheckBox *  checkBox3;

	private: System::Windows::Forms::Button *  button4;
	private: System::Windows::Forms::TabPage *  tabPage4;
	private: System::Windows::Forms::Button *  button3;
	private: System::Windows::Forms::Label *  label1;
	private: System::Windows::Forms::TextBox *  textBox1;
	private: System::Windows::Forms::ListBox *  listBox1;
	private: System::Windows::Forms::CheckBox *  checkBox4;


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
			System::Resources::ResourceManager *  resources = new System::Resources::ResourceManager(__typeof(vipWS3::optionForm));
			this->panel1 = new System::Windows::Forms::Panel();
			this->button4 = new System::Windows::Forms::Button();
			this->button2 = new System::Windows::Forms::Button();
			this->button1 = new System::Windows::Forms::Button();
			this->tabControl1 = new System::Windows::Forms::TabControl();
			this->tabPage1 = new System::Windows::Forms::TabPage();
			this->checkBox2 = new System::Windows::Forms::CheckBox();
			this->checkBox1 = new System::Windows::Forms::CheckBox();
			this->tabPage3 = new System::Windows::Forms::TabPage();
			this->checkBox4 = new System::Windows::Forms::CheckBox();
			this->tabPage2 = new System::Windows::Forms::TabPage();
			this->checkBox3 = new System::Windows::Forms::CheckBox();
			this->tabPage4 = new System::Windows::Forms::TabPage();
			this->button3 = new System::Windows::Forms::Button();
			this->label1 = new System::Windows::Forms::Label();
			this->textBox1 = new System::Windows::Forms::TextBox();
			this->listBox1 = new System::Windows::Forms::ListBox();
			this->panel1->SuspendLayout();
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->tabPage3->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->tabPage4->SuspendLayout();
			this->SuspendLayout();
			//
			// panel1
			//
			this->panel1->Controls->Add(this->button4);
			this->panel1->Controls->Add(this->button2);
			this->panel1->Controls->Add(this->button1);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel1->Location = System::Drawing::Point(0, 296);
			this->panel1->Name = S"panel1";
			this->panel1->Size = System::Drawing::Size(410, 40);
			this->panel1->TabIndex = 0;
			//
			// button4
			//
			this->button4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button4->Location = System::Drawing::Point(16, 8);
			this->button4->Name = S"button4";
			this->button4->TabIndex = 2;
			this->button4->Text = S"Reload";
			//
			// button2
			//
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button2->Location = System::Drawing::Point(320, 8);
			this->button2->Name = S"button2";
			this->button2->TabIndex = 1;
			this->button2->Text = S"Ok";
			//
			// button1
			//
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Location = System::Drawing::Point(232, 8);
			this->button1->Name = S"button1";
			this->button1->TabIndex = 0;
			this->button1->Text = S"Apply";
			//
			// tabControl1
			//
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Controls->Add(this->tabPage4);
			this->tabControl1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tabControl1->Location = System::Drawing::Point(0, 0);
			this->tabControl1->Name = S"tabControl1";
			this->tabControl1->Padding = System::Drawing::Point(12, 4);
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(410, 296);
			this->tabControl1->TabIndex = 1;
			//
			// tabPage1
			//
			this->tabPage1->Controls->Add(this->checkBox2);
			this->tabPage1->Controls->Add(this->checkBox1);
			this->tabPage1->Location = System::Drawing::Point(4, 25);
			this->tabPage1->Name = S"tabPage1";
			this->tabPage1->Size = System::Drawing::Size(402, 267);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = S"BootStrap";
			//
			// checkBox2
			//
			this->checkBox2->Enabled = false;
			this->checkBox2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->checkBox2->Location = System::Drawing::Point(24, 200);
			this->checkBox2->Name = S"checkBox2";
			this->checkBox2->Size = System::Drawing::Size(176, 16);
			this->checkBox2->TabIndex = 1;
			this->checkBox2->Text = S"Load resources";
			//
			// checkBox1
			//
			this->checkBox1->Enabled = false;
			this->checkBox1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->checkBox1->Location = System::Drawing::Point(16, 176);
			this->checkBox1->Name = S"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(232, 16);
			this->checkBox1->TabIndex = 0;
			this->checkBox1->Text = S"Load last layout;";
			//
			// tabPage3
			//
			this->tabPage3->Controls->Add(this->checkBox4);
			this->tabPage3->Location = System::Drawing::Point(4, 25);
			this->tabPage3->Name = S"tabPage3";
			this->tabPage3->Size = System::Drawing::Size(402, 267);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = S"General";
			//
			// checkBox4
			//
			this->checkBox4->Checked = true;
			this->checkBox4->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox4->Enabled = false;
			this->checkBox4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->checkBox4->Location = System::Drawing::Point(16, 24);
			this->checkBox4->Name = S"checkBox4";
			this->checkBox4->Size = System::Drawing::Size(344, 16);
			this->checkBox4->TabIndex = 0;
			this->checkBox4->Text = S"Save Log on exit;";
			//
			// tabPage2
			//
			this->tabPage2->Controls->Add(this->checkBox3);
			this->tabPage2->Location = System::Drawing::Point(4, 25);
			this->tabPage2->Name = S"tabPage2";
			this->tabPage2->Size = System::Drawing::Size(402, 267);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = S"Behaviours";
			//
			// checkBox3
			//
			this->checkBox3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->checkBox3->Location = System::Drawing::Point(16, 24);
			this->checkBox3->Name = S"checkBox3";
			this->checkBox3->Size = System::Drawing::Size(368, 16);
			this->checkBox3->TabIndex = 3;
			this->checkBox3->Text = S"Auto open a new visualization Window linked with source;";
			//
			// tabPage4
			//
			this->tabPage4->Controls->Add(this->button3);
			this->tabPage4->Controls->Add(this->label1);
			this->tabPage4->Controls->Add(this->textBox1);
			this->tabPage4->Controls->Add(this->listBox1);
			this->tabPage4->Location = System::Drawing::Point(4, 25);
			this->tabPage4->Name = S"tabPage4";
			this->tabPage4->Size = System::Drawing::Size(402, 267);
			this->tabPage4->TabIndex = 3;
			this->tabPage4->Text = S"Folders";
			//
			// button3
			//
			this->button3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button3->Location = System::Drawing::Point(312, 161);
			this->button3->Name = S"button3";
			this->button3->TabIndex = 7;
			this->button3->Text = S"browse..";
			//
			// label1
			//
			this->label1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->label1->Location = System::Drawing::Point(16, 193);
			this->label1->Name = S"label1";
			this->label1->Size = System::Drawing::Size(368, 56);
			this->label1->TabIndex = 6;
			//
			// textBox1
			//
			this->textBox1->BackColor = System::Drawing::Color::FromArgb((System::Byte)255, (System::Byte)224, (System::Byte)192);
			this->textBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->textBox1->Location = System::Drawing::Point(16, 161);
			this->textBox1->Name = S"textBox1";
			this->textBox1->Size = System::Drawing::Size(288, 22);
			this->textBox1->TabIndex = 5;
			this->textBox1->Text = S"";
			//
			// listBox1
			//
			this->listBox1->BackColor = System::Drawing::Color::FromArgb((System::Byte)255, (System::Byte)224, (System::Byte)192);
			this->listBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->listBox1->ItemHeight = 16;
			this->listBox1->Location = System::Drawing::Point(16, 17);
			this->listBox1->Name = S"listBox1";
			this->listBox1->Size = System::Drawing::Size(368, 130);
			this->listBox1->TabIndex = 4;
			//
			// optionForm
			//
			this->AutoScaleBaseSize = System::Drawing::Size(6, 15);
			this->ClientSize = System::Drawing::Size(410, 336);
			this->Controls->Add(this->tabControl1);
			this->Controls->Add(this->panel1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (__try_cast<System::Drawing::Icon *  >(resources->GetObject(S"$this.Icon")));
			this->Name = S"optionForm";
			this->Text = S"WorkShop Options";
			this->Closing += new System::ComponentModel::CancelEventHandler(this, optionForm_Closing);
			this->panel1->ResumeLayout(false);
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage3->ResumeLayout(false);
			this->tabPage2->ResumeLayout(false);
			this->tabPage4->ResumeLayout(false);
			this->ResumeLayout(false);

		}
	private: System::Void optionForm_Closing(System::Object *  sender, System::ComponentModel::CancelEventArgs *  e)
			 {
				 e->Cancel = true;
				 this->Visible = false;
			 }

};
}
