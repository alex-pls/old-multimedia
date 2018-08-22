/**
 *  @class   cppForm
 *
 *  @brief   source editor form (interface)
 *
 *  @version 1.0.0
 *  @date    12/05/2006
 *  @author  Alessandro Polo
 *
 ****************************************************************************
 * VIPLib Package Studio
 *  open source - Founded by Alessandro Polo 2006
 *  http://mmlab.science.unitn.it/projects/vipPS
 *
 *  maintained by MultiMedia Laboratory - DIT - University of Trento
 *
 ****************************************************************************/


#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace vipPS
{
	/// <summary>
	/// Riepilogo per cppForm
	///
	/// AVVISO: se si modifica il nome della classe, sarà necessario modificare la
	///          proprietà "Nome file di risorse" relativa allo strumento di compilazione delle risorse gestite
	///          associato a tutti i file RESX da cui dipende la classe. In caso contrario,
	///          le finestre di progettazione non saranno in grado di interagire correttamente con le
	///          risorse localizzate associate al form.
	/// </summary>
	public __gc class cppForm : public System::Windows::Forms::Form
	{
	public:
		cppForm(void)
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
	private: System::Windows::Forms::MainMenu *  mainMenu1;
	private: System::Windows::Forms::MenuItem *  menuItem1;
	private: System::Windows::Forms::MenuItem *  menuItem2;
	private: System::Windows::Forms::MenuItem *  menuItem3;





	private: System::Windows::Forms::Panel *  panel3;


	private: System::Windows::Forms::TextBox *  textBox1;
	private: System::Windows::Forms::StatusBar *  statusBar1;
	private: System::Windows::Forms::Panel *  panel1;
	private: System::Windows::Forms::Button *  button2;
	private: System::Windows::Forms::Button *  button1;
	private: System::Windows::Forms::Panel *  panel2;
	private: System::Windows::Forms::RichTextBox *  richTextBox1;




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
			this->mainMenu1 = new System::Windows::Forms::MainMenu();
			this->menuItem1 = new System::Windows::Forms::MenuItem();
			this->menuItem2 = new System::Windows::Forms::MenuItem();
			this->menuItem3 = new System::Windows::Forms::MenuItem();
			this->panel3 = new System::Windows::Forms::Panel();
			this->textBox1 = new System::Windows::Forms::TextBox();
			this->statusBar1 = new System::Windows::Forms::StatusBar();
			this->panel1 = new System::Windows::Forms::Panel();
			this->button2 = new System::Windows::Forms::Button();
			this->button1 = new System::Windows::Forms::Button();
			this->panel2 = new System::Windows::Forms::Panel();
			this->richTextBox1 = new System::Windows::Forms::RichTextBox();
			this->panel3->SuspendLayout();
			this->panel1->SuspendLayout();
			this->panel2->SuspendLayout();
			this->SuspendLayout();
			//
			// mainMenu1
			//
			System::Windows::Forms::MenuItem* __mcTemp__1[] = new System::Windows::Forms::MenuItem*[3];
			__mcTemp__1[0] = this->menuItem1;
			__mcTemp__1[1] = this->menuItem2;
			__mcTemp__1[2] = this->menuItem3;
			this->mainMenu1->MenuItems->AddRange(__mcTemp__1);
			//
			// menuItem1
			//
			this->menuItem1->Index = 0;
			this->menuItem1->Text = S"&File";
			//
			// menuItem2
			//
			this->menuItem2->Index = 1;
			this->menuItem2->Text = S"&Edit";
			//
			// menuItem3
			//
			this->menuItem3->Index = 2;
			this->menuItem3->Text = S"E&Xternal";
			//
			// panel3
			//
			this->panel3->Controls->Add(this->textBox1);
			this->panel3->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel3->DockPadding->All = 10;
			this->panel3->Location = System::Drawing::Point(0, 0);
			this->panel3->Name = S"panel3";
			this->panel3->Size = System::Drawing::Size(520, 40);
			this->panel3->TabIndex = 2;
			//
			// textBox1
			//
			this->textBox1->BackColor = System::Drawing::Color::FromArgb((System::Byte)235, (System::Byte)235, (System::Byte)255);
			this->textBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->textBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->textBox1->Location = System::Drawing::Point(10, 10);
			this->textBox1->Name = S"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->Size = System::Drawing::Size(500, 22);
			this->textBox1->TabIndex = 0;
			this->textBox1->Text = S"";
			//
			// statusBar1
			//
			this->statusBar1->Location = System::Drawing::Point(0, 384);
			this->statusBar1->Name = S"statusBar1";
			this->statusBar1->Size = System::Drawing::Size(520, 22);
			this->statusBar1->TabIndex = 6;
			//
			// panel1
			//
			this->panel1->Controls->Add(this->button2);
			this->panel1->Controls->Add(this->button1);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel1->Location = System::Drawing::Point(0, 344);
			this->panel1->Name = S"panel1";
			this->panel1->Size = System::Drawing::Size(520, 40);
			this->panel1->TabIndex = 7;
			//
			// button2
			//
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button2->Location = System::Drawing::Point(304, 8);
			this->button2->Name = S"button2";
			this->button2->Size = System::Drawing::Size(96, 23);
			this->button2->TabIndex = 1;
			this->button2->Text = S"Revert";
			//
			// button1
			//
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Location = System::Drawing::Point(408, 8);
			this->button1->Name = S"button1";
			this->button1->Size = System::Drawing::Size(96, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = S"Save";
			//
			// panel2
			//
			this->panel2->Controls->Add(this->richTextBox1);
			this->panel2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel2->DockPadding->All = 10;
			this->panel2->Location = System::Drawing::Point(0, 40);
			this->panel2->Name = S"panel2";
			this->panel2->Size = System::Drawing::Size(520, 304);
			this->panel2->TabIndex = 8;
			//
			// richTextBox1
			//
			this->richTextBox1->BackColor = System::Drawing::Color::FromArgb((System::Byte)232, (System::Byte)255, (System::Byte)255);
			this->richTextBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->richTextBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->richTextBox1->Location = System::Drawing::Point(10, 10);
			this->richTextBox1->Name = S"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(500, 284);
			this->richTextBox1->TabIndex = 1;
			this->richTextBox1->Text = S"";
			//
			// cppForm
			//
			this->AutoScaleBaseSize = System::Drawing::Size(6, 15);
			this->ClientSize = System::Drawing::Size(520, 406);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->statusBar1);
			this->Controls->Add(this->panel3);
			this->Menu = this->mainMenu1;
			this->Name = S"cppForm";
			this->Text = S"cppForm";
			this->panel3->ResumeLayout(false);
			this->panel1->ResumeLayout(false);
			this->panel2->ResumeLayout(false);
			this->ResumeLayout(false);

		}
	};
}
