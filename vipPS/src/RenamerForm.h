/**
 *  @class   RenamerForm
 *
 *  @brief   package renamer form (interface)
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
using namespace System::IO;
using namespace System::Text;


namespace vipPS
{
	/// <summary>
	/// Riepilogo per RenamerForm
	///
	/// AVVISO: se si modifica il nome della classe, sarà necessario modificare la
	///          proprietà "Nome file di risorse" relativa allo strumento di compilazione delle risorse gestite
	///          associato a tutti i file RESX da cui dipende la classe. In caso contrario,
	///          le finestre di progettazione non saranno in grado di interagire correttamente con le
	///          risorse localizzate associate al form.
	/// </summary>
	public __gc class RenamerForm : public System::Windows::Forms::Form
	{
	public:
		RenamerForm(void)
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
	private: System::Windows::Forms::Button *  button1;
	private: System::Windows::Forms::Button *  button2;
	private: System::Windows::Forms::Label *  label1;

	private: System::Windows::Forms::Panel *  panel2;
	private: System::Windows::Forms::Button *  button3;

	private: System::Windows::Forms::Label *  label2;
	private: System::Windows::Forms::Panel *  panel3;

	private: System::Windows::Forms::Label *  label3;
	private: System::Windows::Forms::Panel *  panel4;

	private: System::Windows::Forms::FolderBrowserDialog *  folderBrowserDialog1;
	private: System::Windows::Forms::Button *  button4;
	private: System::Windows::Forms::CheckBox *  cB_rename;
	private: System::Windows::Forms::TextBox *  tB_nameNew;
	private: System::Windows::Forms::TextBox *  tB_nameOld;
	private: System::Windows::Forms::TextBox *  tB_folder;

	private: System::Windows::Forms::Label *  label4;
	private: System::Windows::Forms::TextBox *  tB_path;
	private: System::Windows::Forms::TabPage *  tabPage3;
	private: System::Windows::Forms::RichTextBox *  rTB_log;
	private: System::Windows::Forms::Panel *  panel5;
	private: System::Windows::Forms::Panel *  panel6;
	private: System::Windows::Forms::Button *  button5;
	private: System::Windows::Forms::Button *  button6;

	private: System::Windows::Forms::Label *  label5;
	private: System::Windows::Forms::TextBox *  tB_dest;
	private: System::Windows::Forms::CheckBox *  cB_renameDir;
	private: System::Windows::Forms::Panel *  panel7;




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
			this->button2 = new System::Windows::Forms::Button();
			this->button1 = new System::Windows::Forms::Button();
			this->tabControl1 = new System::Windows::Forms::TabControl();
			this->tabPage1 = new System::Windows::Forms::TabPage();
			this->cB_renameDir = new System::Windows::Forms::CheckBox();
			this->cB_rename = new System::Windows::Forms::CheckBox();
			this->panel4 = new System::Windows::Forms::Panel();
			this->tB_nameNew = new System::Windows::Forms::TextBox();
			this->label3 = new System::Windows::Forms::Label();
			this->panel3 = new System::Windows::Forms::Panel();
			this->tB_nameOld = new System::Windows::Forms::TextBox();
			this->label2 = new System::Windows::Forms::Label();
			this->panel2 = new System::Windows::Forms::Panel();
			this->button4 = new System::Windows::Forms::Button();
			this->button3 = new System::Windows::Forms::Button();
			this->tB_folder = new System::Windows::Forms::TextBox();
			this->label1 = new System::Windows::Forms::Label();
			this->tabPage2 = new System::Windows::Forms::TabPage();
			this->panel6 = new System::Windows::Forms::Panel();
			this->button5 = new System::Windows::Forms::Button();
			this->button6 = new System::Windows::Forms::Button();
			this->tB_dest = new System::Windows::Forms::TextBox();
			this->label5 = new System::Windows::Forms::Label();
			this->panel5 = new System::Windows::Forms::Panel();
			this->tB_path = new System::Windows::Forms::TextBox();
			this->label4 = new System::Windows::Forms::Label();
			this->tabPage3 = new System::Windows::Forms::TabPage();
			this->rTB_log = new System::Windows::Forms::RichTextBox();
			this->folderBrowserDialog1 = new System::Windows::Forms::FolderBrowserDialog();
			this->panel7 = new System::Windows::Forms::Panel();
			this->panel1->SuspendLayout();
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->panel2->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->panel6->SuspendLayout();
			this->tabPage3->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->button2);
			this->panel1->Controls->Add(this->button1);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel1->Location = System::Drawing::Point(0, 374);
			this->panel1->Name = S"panel1";
			this->panel1->Size = System::Drawing::Size(592, 40);
			this->panel1->TabIndex = 0;
			// 
			// button2
			// 
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button2->Location = System::Drawing::Point(400, 8);
			this->button2->Name = S"button2";
			this->button2->Size = System::Drawing::Size(88, 24);
			this->button2->TabIndex = 1;
			this->button2->Text = S"&Cancel";
			// 
			// button1
			// 
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Location = System::Drawing::Point(496, 8);
			this->button1->Name = S"button1";
			this->button1->Size = System::Drawing::Size(88, 24);
			this->button1->TabIndex = 0;
			this->button1->Text = S"&Apply";
			this->button1->Click += new System::EventHandler(this, button1_Click);
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tabControl1->Location = System::Drawing::Point(8, 0);
			this->tabControl1->Name = S"tabControl1";
			this->tabControl1->Padding = System::Drawing::Point(12, 3);
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(584, 374);
			this->tabControl1->SizeMode = System::Windows::Forms::TabSizeMode::Fixed;
			this->tabControl1->TabIndex = 1;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->cB_renameDir);
			this->tabPage1->Controls->Add(this->cB_rename);
			this->tabPage1->Controls->Add(this->panel4);
			this->tabPage1->Controls->Add(this->tB_nameNew);
			this->tabPage1->Controls->Add(this->label3);
			this->tabPage1->Controls->Add(this->panel3);
			this->tabPage1->Controls->Add(this->tB_nameOld);
			this->tabPage1->Controls->Add(this->label2);
			this->tabPage1->Controls->Add(this->panel2);
			this->tabPage1->Controls->Add(this->tB_folder);
			this->tabPage1->Controls->Add(this->label1);
			this->tabPage1->DockPadding->All = 10;
			this->tabPage1->Location = System::Drawing::Point(4, 25);
			this->tabPage1->Name = S"tabPage1";
			this->tabPage1->Size = System::Drawing::Size(576, 345);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = S"Settings";
			// 
			// cB_renameDir
			// 
			this->cB_renameDir->Checked = true;
			this->cB_renameDir->CheckState = System::Windows::Forms::CheckState::Checked;
			this->cB_renameDir->Dock = System::Windows::Forms::DockStyle::Top;
			this->cB_renameDir->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->cB_renameDir->Location = System::Drawing::Point(10, 232);
			this->cB_renameDir->Name = S"cB_renameDir";
			this->cB_renameDir->Size = System::Drawing::Size(556, 24);
			this->cB_renameDir->TabIndex = 12;
			this->cB_renameDir->Text = S"Rename also directory (Package Convention)";
			// 
			// cB_rename
			// 
			this->cB_rename->Checked = true;
			this->cB_rename->CheckState = System::Windows::Forms::CheckState::Checked;
			this->cB_rename->Dock = System::Windows::Forms::DockStyle::Top;
			this->cB_rename->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->cB_rename->Location = System::Drawing::Point(10, 208);
			this->cB_rename->Name = S"cB_rename";
			this->cB_rename->Size = System::Drawing::Size(556, 24);
			this->cB_rename->TabIndex = 11;
			this->cB_rename->Text = S"Rename also files (Package Convention)";
			// 
			// panel4
			// 
			this->panel4->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel4->Location = System::Drawing::Point(10, 186);
			this->panel4->Name = S"panel4";
			this->panel4->Size = System::Drawing::Size(556, 22);
			this->panel4->TabIndex = 10;
			// 
			// tB_nameNew
			// 
			this->tB_nameNew->BackColor = System::Drawing::Color::FromArgb((System::Byte)235, (System::Byte)235, (System::Byte)255);
			this->tB_nameNew->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->tB_nameNew->Dock = System::Windows::Forms::DockStyle::Top;
			this->tB_nameNew->Location = System::Drawing::Point(10, 164);
			this->tB_nameNew->Name = S"tB_nameNew";
			this->tB_nameNew->Size = System::Drawing::Size(556, 22);
			this->tB_nameNew->TabIndex = 8;
			this->tB_nameNew->Text = S"";
			this->tB_nameNew->TextChanged += new System::EventHandler(this, tB_nameNew_TextChanged);
			// 
			// label3
			// 
			this->label3->Dock = System::Windows::Forms::DockStyle::Top;
			this->label3->Enabled = false;
			this->label3->Location = System::Drawing::Point(10, 141);
			this->label3->Name = S"label3";
			this->label3->Size = System::Drawing::Size(556, 23);
			this->label3->TabIndex = 7;
			this->label3->Text = S"Class Name (new):";
			this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// panel3
			// 
			this->panel3->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel3->Location = System::Drawing::Point(10, 133);
			this->panel3->Name = S"panel3";
			this->panel3->Size = System::Drawing::Size(556, 8);
			this->panel3->TabIndex = 6;
			// 
			// tB_nameOld
			// 
			this->tB_nameOld->BackColor = System::Drawing::Color::FromArgb((System::Byte)235, (System::Byte)235, (System::Byte)255);
			this->tB_nameOld->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->tB_nameOld->Dock = System::Windows::Forms::DockStyle::Top;
			this->tB_nameOld->Location = System::Drawing::Point(10, 111);
			this->tB_nameOld->Name = S"tB_nameOld";
			this->tB_nameOld->Size = System::Drawing::Size(556, 22);
			this->tB_nameOld->TabIndex = 5;
			this->tB_nameOld->Text = S"";
			// 
			// label2
			// 
			this->label2->Dock = System::Windows::Forms::DockStyle::Top;
			this->label2->Enabled = false;
			this->label2->Location = System::Drawing::Point(10, 88);
			this->label2->Name = S"label2";
			this->label2->Size = System::Drawing::Size(556, 23);
			this->label2->TabIndex = 4;
			this->label2->Text = S"Class Name (old):";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// panel2
			// 
			this->panel2->Controls->Add(this->button4);
			this->panel2->Controls->Add(this->button3);
			this->panel2->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel2->Location = System::Drawing::Point(10, 55);
			this->panel2->Name = S"panel2";
			this->panel2->Size = System::Drawing::Size(556, 33);
			this->panel2->TabIndex = 3;
			// 
			// button4
			// 
			this->button4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button4->Location = System::Drawing::Point(304, 8);
			this->button4->Name = S"button4";
			this->button4->Size = System::Drawing::Size(112, 23);
			this->button4->TabIndex = 1;
			this->button4->Text = S"&check content..";
			this->button4->Click += new System::EventHandler(this, button4_Click);
			// 
			// button3
			// 
			this->button3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button3->Location = System::Drawing::Point(432, 8);
			this->button3->Name = S"button3";
			this->button3->TabIndex = 0;
			this->button3->Text = S"&browse..";
			this->button3->Click += new System::EventHandler(this, button3_Click);
			// 
			// tB_folder
			// 
			this->tB_folder->BackColor = System::Drawing::Color::FromArgb((System::Byte)235, (System::Byte)235, (System::Byte)255);
			this->tB_folder->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->tB_folder->Dock = System::Windows::Forms::DockStyle::Top;
			this->tB_folder->Location = System::Drawing::Point(10, 33);
			this->tB_folder->Name = S"tB_folder";
			this->tB_folder->Size = System::Drawing::Size(556, 22);
			this->tB_folder->TabIndex = 2;
			this->tB_folder->Text = S"";
			this->tB_folder->TextChanged += new System::EventHandler(this, tB_folder_TextChanged);
			// 
			// label1
			// 
			this->label1->Dock = System::Windows::Forms::DockStyle::Top;
			this->label1->Enabled = false;
			this->label1->Location = System::Drawing::Point(10, 10);
			this->label1->Name = S"label1";
			this->label1->Size = System::Drawing::Size(556, 23);
			this->label1->TabIndex = 1;
			this->label1->Text = S"Package Folder:";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->panel6);
			this->tabPage2->Controls->Add(this->tB_dest);
			this->tabPage2->Controls->Add(this->label5);
			this->tabPage2->Controls->Add(this->panel5);
			this->tabPage2->Controls->Add(this->tB_path);
			this->tabPage2->Controls->Add(this->label4);
			this->tabPage2->DockPadding->All = 10;
			this->tabPage2->Location = System::Drawing::Point(4, 25);
			this->tabPage2->Name = S"tabPage2";
			this->tabPage2->Size = System::Drawing::Size(576, 345);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = S"Advanced";
			// 
			// panel6
			// 
			this->panel6->Controls->Add(this->button5);
			this->panel6->Controls->Add(this->button6);
			this->panel6->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel6->Location = System::Drawing::Point(10, 117);
			this->panel6->Name = S"panel6";
			this->panel6->Size = System::Drawing::Size(556, 33);
			this->panel6->TabIndex = 8;
			// 
			// button5
			// 
			this->button5->Enabled = false;
			this->button5->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button5->Location = System::Drawing::Point(304, 8);
			this->button5->Name = S"button5";
			this->button5->Size = System::Drawing::Size(112, 23);
			this->button5->TabIndex = 1;
			this->button5->Text = S"&check content..";
			// 
			// button6
			// 
			this->button6->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button6->Location = System::Drawing::Point(432, 8);
			this->button6->Name = S"button6";
			this->button6->TabIndex = 0;
			this->button6->Text = S"&browse..";
			this->button6->Click += new System::EventHandler(this, button6_Click);
			// 
			// tB_dest
			// 
			this->tB_dest->BackColor = System::Drawing::Color::FromArgb((System::Byte)235, (System::Byte)235, (System::Byte)255);
			this->tB_dest->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->tB_dest->Dock = System::Windows::Forms::DockStyle::Top;
			this->tB_dest->Location = System::Drawing::Point(10, 95);
			this->tB_dest->Name = S"tB_dest";
			this->tB_dest->Size = System::Drawing::Size(556, 22);
			this->tB_dest->TabIndex = 7;
			this->tB_dest->Text = S"";
			// 
			// label5
			// 
			this->label5->Dock = System::Windows::Forms::DockStyle::Top;
			this->label5->Enabled = false;
			this->label5->Location = System::Drawing::Point(10, 72);
			this->label5->Name = S"label5";
			this->label5->Size = System::Drawing::Size(556, 23);
			this->label5->TabIndex = 6;
			this->label5->Text = S"Destination Folder:";
			this->label5->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// panel5
			// 
			this->panel5->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel5->Location = System::Drawing::Point(10, 55);
			this->panel5->Name = S"panel5";
			this->panel5->Size = System::Drawing::Size(556, 17);
			this->panel5->TabIndex = 5;
			// 
			// tB_path
			// 
			this->tB_path->BackColor = System::Drawing::Color::FromArgb((System::Byte)235, (System::Byte)235, (System::Byte)255);
			this->tB_path->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->tB_path->Dock = System::Windows::Forms::DockStyle::Top;
			this->tB_path->Location = System::Drawing::Point(10, 33);
			this->tB_path->Name = S"tB_path";
			this->tB_path->Size = System::Drawing::Size(556, 22);
			this->tB_path->TabIndex = 4;
			this->tB_path->Text = S"*.*";
			// 
			// label4
			// 
			this->label4->Dock = System::Windows::Forms::DockStyle::Top;
			this->label4->Enabled = false;
			this->label4->Location = System::Drawing::Point(10, 10);
			this->label4->Name = S"label4";
			this->label4->Size = System::Drawing::Size(556, 23);
			this->label4->TabIndex = 3;
			this->label4->Text = S"File Pattern:";
			this->label4->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			// 
			// tabPage3
			// 
			this->tabPage3->Controls->Add(this->rTB_log);
			this->tabPage3->DockPadding->All = 10;
			this->tabPage3->Location = System::Drawing::Point(4, 25);
			this->tabPage3->Name = S"tabPage3";
			this->tabPage3->Size = System::Drawing::Size(576, 345);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = S"Log";
			// 
			// rTB_log
			// 
			this->rTB_log->BackColor = System::Drawing::Color::FromArgb((System::Byte)235, (System::Byte)255, (System::Byte)255);
			this->rTB_log->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->rTB_log->Dock = System::Windows::Forms::DockStyle::Fill;
			this->rTB_log->Location = System::Drawing::Point(10, 10);
			this->rTB_log->Name = S"rTB_log";
			this->rTB_log->Size = System::Drawing::Size(556, 325);
			this->rTB_log->TabIndex = 0;
			this->rTB_log->Text = S"";
			// 
			// folderBrowserDialog1
			// 
			this->folderBrowserDialog1->Description = S"Select package\'s folder..";
			// 
			// panel7
			// 
			this->panel7->Dock = System::Windows::Forms::DockStyle::Left;
			this->panel7->Location = System::Drawing::Point(0, 0);
			this->panel7->Name = S"panel7";
			this->panel7->Size = System::Drawing::Size(8, 374);
			this->panel7->TabIndex = 2;
			// 
			// RenamerForm
			// 
			this->AutoScaleBaseSize = System::Drawing::Size(6, 15);
			this->ClientSize = System::Drawing::Size(592, 414);
			this->Controls->Add(this->tabControl1);
			this->Controls->Add(this->panel7);
			this->Controls->Add(this->panel1);
			this->Name = S"RenamerForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = S"Package Renamer";
			this->Closing += new System::ComponentModel::CancelEventHandler(this, RenamerForm_Closing);
			this->Load += new System::EventHandler(this, RenamerForm_Load);
			this->panel1->ResumeLayout(false);
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->panel2->ResumeLayout(false);
			this->tabPage2->ResumeLayout(false);
			this->panel6->ResumeLayout(false);
			this->tabPage3->ResumeLayout(false);
			this->ResumeLayout(false);

		}
	private: System::Void button3_Click(System::Object *  sender, System::EventArgs *  e)
			 {
				 if ( folderBrowserDialog1->ShowDialog() != DialogResult::OK )
					 return;

				 tB_folder->Text = folderBrowserDialog1->SelectedPath;
				 tB_dest->Text = folderBrowserDialog1->SelectedPath;
				 button4_Click(sender, e);

			 }

private: System::Void tB_folder_TextChanged(System::Object *  sender, System::EventArgs *  e)
		 {
			 if (!Directory::Exists(tB_folder->Text))
				 return;

			 button4_Click(sender, e);
		 }

 private: System::Void button4_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 if (!Directory::Exists(tB_folder->Text))
				 return;

			 String* path;
			 if (tB_folder->Text->EndsWith(S"\\"))
				 path = tB_folder->Text->Substring(0, tB_folder->Text->Length-1);
			 else
				 path = tB_folder->Text;
			 String* name = path->Substring( tB_folder->Text->LastIndexOf(S"\\") + 1 );

			 if (File::Exists(Path::Combine(tB_folder->Text, String::Concat(name, S".h"))))
			 {
				 tB_nameOld->Text = name;
				 cB_renameDir->Enabled = true;
				 cB_renameDir->Checked = true;
			 }
			 else
			 {
				 tB_nameOld->Text = name;
				 cB_renameDir->Enabled = false;
				 cB_renameDir->Checked = false;
			 }
		 }



private: System::Void tB_nameNew_TextChanged(System::Object *  sender, System::EventArgs *  e)
		 {
			 if (!cB_renameDir->Checked)
				 return;

			 String* path;
			 if (tB_folder->Text->EndsWith(S"\\"))
				 path = tB_folder->Text->Substring(0, tB_folder->Text->Length-1);
			 else
				 path = tB_folder->Text;

			 tB_dest->Text = Path::Combine(Path::GetDirectoryName(path), tB_nameNew->Text);
		 }


private: System::Void button1_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			  rTB_log->AppendText( S"\n\r_________________JOB STARTED...\n\r" );

			 if ( tB_nameOld->Text->Length < 1 || tB_nameNew->Text->Length < 1 )
			  {
				  MessageBox::Show(this, S"Settings: Error!", S"Class name is too short!");
				  return;
			  }

			  if ( tB_nameOld->Text->CompareTo(tB_nameNew->Text) == 0 )
			  {
				  MessageBox::Show(this, S"Settings: Error!", S"Class names are equal!");
				  return;
			  }

			  IEnumerator* en = this->MdiParent->MdiChildren->GetEnumerator();
			  while ( en->MoveNext() )
			   {
				   if ( __try_cast<Form*>(en->Current)->Text->IndexOf(tB_nameOld->Text) > 0 )
				    {
						if ( MessageBox::Show(this, S"Error!", S"Are you trying to rename an opened package?\r\nPlease close all windows of selected package before this operation.\r\rClick OK to continue anyway.. at your risk.", MessageBoxButtons::OKCancel) != DialogResult::OK )
							return;
						break;
				    }
			   }
			en = NULL;
			  if ( !Directory::Exists(tB_folder->Text) )
			  {
				  MessageBox::Show(this, S"Settings: Error!", S"Directory does NOT exist!");
				  return;
			  }

			  rTB_log->AppendText( String::Format( S" Source Folder:  {0}\r\n", tB_folder->Text ) );
			  rTB_log->AppendText( String::Format( S" Destination Folder:  {0}\r\n", tB_dest->Text ) );
			  rTB_log->AppendText( String::Format( S" Old ClassName:  {0}\r\n", tB_nameOld->Text ) );
			  rTB_log->AppendText( String::Format( S" New ClassName:  {0}\r\n", tB_nameNew->Text ) );
			  rTB_log->AppendText( String::Format( S" Rename Files:  {0}\r\n\r\n", cB_rename->Checked.ToString() ) );

			  String* files[] = Directory::GetFiles(tB_folder->Text, tB_path->Text);
			  rTB_log->AppendText( String::Format( S" Reading Files..  ({0})", files->Count.ToString()) );
			  en = files->GetEnumerator();
			  while ( en->MoveNext() )
			  {
				rTB_log->AppendText( en->Current->ToString() );
				rTB_log->AppendText(S"\n");

				if ( !File::Exists(en->Current->ToString()) )
				 {
					rTB_log->AppendText(S"NOT FOUND!");
					continue;
				 }

				StreamReader* sr;
				StringBuilder* strBuilder;
				StreamWriter* fWriter;
				try {

					String* line;
					strBuilder = new StringBuilder(1024);
					sr = new StreamReader( en->Current->ToString() );
					while ( line = sr->ReadLine() )
						strBuilder->Append(String::Concat(line, S"\r\n"));

					sr->Close();
					strBuilder->Replace(tB_nameOld->Text, tB_nameNew->Text);

					fWriter = File::CreateText(en->Current->ToString());


					fWriter->Write(strBuilder->ToString());
					fWriter->Close();

				} __finally {
					sr = NULL;
					strBuilder = NULL;
					fWriter=NULL;
				}
			  }

			if ( tB_dest->Text->Length < 3 )
				tB_dest->Text = tB_folder->Text;

			if ( !tB_dest->Text->EndsWith(S"\\") )
				tB_dest->Text = String::Concat(tB_dest->Text, S"\\");

			if ( !Directory::Exists(tB_dest->Text) )
				Directory::CreateDirectory(tB_dest->Text);

			en = NULL;
			if (cB_rename->Checked)
			{
			  rTB_log->AppendText( S"Renaming Files..");

			  en = files->GetEnumerator();
			  while ( en->MoveNext() )
			   {
				  String* oldFile = en->Current->ToString();
				  String* newFile = String::Concat(tB_dest->Text,  Path::GetFileName(oldFile)->Replace(tB_nameOld->Text, tB_nameNew->Text) );
				  rTB_log->AppendText( String::Format( S" ({0})\r\n->\r\n({1})\r\n\r\n", oldFile, newFile ) );
				  File::Move(oldFile, newFile );
			   }
			}
			  rTB_log->AppendText( S"\n\r_________________JOB COMPLETED.\n\r" );

		 }

private: System::Void RenamerForm_Closing(System::Object *  sender, System::ComponentModel::CancelEventArgs *  e)
		 {
			 e->Cancel = true;
			 this->Visible = false;
		 }

private: System::Void button6_Click(System::Object *  sender, System::EventArgs *  e)
		 {
				 if ( folderBrowserDialog1->ShowDialog() != DialogResult::OK )
					 return;

				 tB_dest->Text = folderBrowserDialog1->SelectedPath;

		 }



private: System::Void RenamerForm_Load(System::Object *  sender, System::EventArgs *  e)
		 {

		 }

};
}
