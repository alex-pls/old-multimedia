#pragma once

#include "loaderdll.h"
#include "../../../../source/vipDefs.h"

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
	/// Riepilogo per resManForm
	///
	/// AVVISO: se si modifica il nome della classe, sarà necessario modificare la
	///          proprietà "Nome file di risorse" relativa allo strumento di compilazione delle risorse gestite
	///          associato a tutti i file RESX da cui dipende la classe. In caso contrario,
	///          le finestre di progettazione non saranno in grado di interagire correttamente con le
	///          risorse localizzate associate al form.
	/// </summary>
	public __gc class resManForm : public System::Windows::Forms::Form
	{
	public:
		resManForm(void);

		void Init(loaderDLL** resources);

	protected:
		void Dispose(Boolean disposing);

	private: loaderDLL** res; //link
	private: TreeNode* tN_vipInput;
	private: TreeNode* tN_vipOutput;
	private: TreeNode* tN_vipFilter;
	private: TreeNode* tN_vipBuffer;
	private: String* lastPath;

	private: System::Windows::Forms::Panel *  panel5;
	private: System::Windows::Forms::Panel *  panel4;
	private: System::Windows::Forms::Panel *  panel3;
	private: System::Windows::Forms::Panel *  panel2;
	private: System::Windows::Forms::Button *  button3;
	private: System::Windows::Forms::Button *  button2;
	private: System::Windows::Forms::Button *  button1;
	private: System::Windows::Forms::Panel *  panel1;
	private: System::Windows::Forms::Panel *  panel6;
	private: System::Windows::Forms::Panel *  panel7;
	private: System::Windows::Forms::Panel *  panel8;
	private: System::Windows::Forms::ListBox *  lBresInfo;
	private: System::Windows::Forms::TabPage *  tabPage3;
	private: System::Windows::Forms::Panel *  panel9;
	private: System::Windows::Forms::Panel *  panel10;
	private: System::Windows::Forms::Panel *  panel11;
	private: System::Windows::Forms::Panel *  panel12;
	private: System::Windows::Forms::ListBox *  lBlog;
	private: System::Windows::Forms::Button *  button4;

	private: System::Windows::Forms::TabControl *  tabControl1;
	private: System::Windows::Forms::TabPage *  tabPage1;
	private: System::Windows::Forms::TabPage *  tabPage2;
	private: System::Windows::Forms::OpenFileDialog *  openFileDialog1;
	private: System::Windows::Forms::TreeView *  tVres;



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
			System::Resources::ResourceManager *  resources = new System::Resources::ResourceManager(__typeof(vipWS3::resManForm));
			this->tabControl1 = new System::Windows::Forms::TabControl();
			this->tabPage1 = new System::Windows::Forms::TabPage();
			this->tVres = new System::Windows::Forms::TreeView();
			this->panel5 = new System::Windows::Forms::Panel();
			this->panel4 = new System::Windows::Forms::Panel();
			this->button4 = new System::Windows::Forms::Button();
			this->button3 = new System::Windows::Forms::Button();
			this->button2 = new System::Windows::Forms::Button();
			this->button1 = new System::Windows::Forms::Button();
			this->panel3 = new System::Windows::Forms::Panel();
			this->panel2 = new System::Windows::Forms::Panel();
			this->tabPage2 = new System::Windows::Forms::TabPage();
			this->lBresInfo = new System::Windows::Forms::ListBox();
			this->panel1 = new System::Windows::Forms::Panel();
			this->panel6 = new System::Windows::Forms::Panel();
			this->panel7 = new System::Windows::Forms::Panel();
			this->panel8 = new System::Windows::Forms::Panel();
			this->tabPage3 = new System::Windows::Forms::TabPage();
			this->lBlog = new System::Windows::Forms::ListBox();
			this->panel9 = new System::Windows::Forms::Panel();
			this->panel10 = new System::Windows::Forms::Panel();
			this->panel11 = new System::Windows::Forms::Panel();
			this->panel12 = new System::Windows::Forms::Panel();
			this->openFileDialog1 = new System::Windows::Forms::OpenFileDialog();
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->panel4->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->tabPage3->SuspendLayout();
			this->SuspendLayout();
			//
			// tabControl1
			//
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tabControl1->Location = System::Drawing::Point(0, 0);
			this->tabControl1->Multiline = true;
			this->tabControl1->Name = S"tabControl1";
			this->tabControl1->Padding = System::Drawing::Point(12, 4);
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(384, 326);
			this->tabControl1->TabIndex = 1;
			this->tabControl1->SelectedIndexChanged += new System::EventHandler(this, tabControl1_SelectedIndexChanged);
			//
			// tabPage1
			//
			this->tabPage1->Controls->Add(this->tVres);
			this->tabPage1->Controls->Add(this->panel5);
			this->tabPage1->Controls->Add(this->panel4);
			this->tabPage1->Controls->Add(this->panel3);
			this->tabPage1->Controls->Add(this->panel2);
			this->tabPage1->Location = System::Drawing::Point(4, 27);
			this->tabPage1->Name = S"tabPage1";
			this->tabPage1->Size = System::Drawing::Size(376, 295);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = S"Current Resources";
			//
			// tVres
			//
			this->tVres->BackColor = System::Drawing::Color::FromArgb((System::Byte)255, (System::Byte)224, (System::Byte)192);
			this->tVres->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->tVres->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tVres->ImageIndex = -1;
			this->tVres->Location = System::Drawing::Point(8, 16);
			this->tVres->Name = S"tVres";
			System::Windows::Forms::TreeNode* __mcTemp__1[] = new System::Windows::Forms::TreeNode*[4];
			__mcTemp__1[0] = new System::Windows::Forms::TreeNode(S"vipInput");
			__mcTemp__1[1] = new System::Windows::Forms::TreeNode(S"vipOutput");
			__mcTemp__1[2] = new System::Windows::Forms::TreeNode(S"vipFilter");
			__mcTemp__1[3] = new System::Windows::Forms::TreeNode(S"vipBuffer");
			this->tVres->Nodes->AddRange(__mcTemp__1);
			this->tVres->SelectedImageIndex = -1;
			this->tVres->Size = System::Drawing::Size(360, 207);
			this->tVres->TabIndex = 11;
			//
			// panel5
			//
			this->panel5->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel5->Location = System::Drawing::Point(8, 0);
			this->panel5->Name = S"panel5";
			this->panel5->Size = System::Drawing::Size(360, 16);
			this->panel5->TabIndex = 10;
			//
			// panel4
			//
			this->panel4->Controls->Add(this->button4);
			this->panel4->Controls->Add(this->button3);
			this->panel4->Controls->Add(this->button2);
			this->panel4->Controls->Add(this->button1);
			this->panel4->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel4->Location = System::Drawing::Point(8, 223);
			this->panel4->Name = S"panel4";
			this->panel4->Size = System::Drawing::Size(360, 72);
			this->panel4->TabIndex = 9;
			//
			// button4
			//
			this->button4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button4->Location = System::Drawing::Point(8, 40);
			this->button4->Name = S"button4";
			this->button4->Size = System::Drawing::Size(264, 23);
			this->button4->TabIndex = 8;
			this->button4->Text = S"new Resource Instance";
			this->button4->Click += new System::EventHandler(this, button4_Click);
			//
			// button3
			//
			this->button3->Enabled = false;
			this->button3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button3->Location = System::Drawing::Point(288, 40);
			this->button3->Name = S"button3";
			this->button3->Size = System::Drawing::Size(72, 23);
			this->button3->TabIndex = 7;
			this->button3->Text = S"Validate";
			this->button3->Click += new System::EventHandler(this, button3_Click);
			//
			// button2
			//
			this->button2->Enabled = false;
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button2->Location = System::Drawing::Point(288, 8);
			this->button2->Name = S"button2";
			this->button2->Size = System::Drawing::Size(72, 23);
			this->button2->TabIndex = 6;
			this->button2->Text = S"Remove";
			//
			// button1
			//
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Location = System::Drawing::Point(8, 8);
			this->button1->Name = S"button1";
			this->button1->Size = System::Drawing::Size(264, 23);
			this->button1->TabIndex = 5;
			this->button1->Text = S"Auto Import..";
			this->button1->Click += new System::EventHandler(this, button1_Click);
			//
			// panel3
			//
			this->panel3->Dock = System::Windows::Forms::DockStyle::Right;
			this->panel3->Location = System::Drawing::Point(368, 0);
			this->panel3->Name = S"panel3";
			this->panel3->Size = System::Drawing::Size(8, 295);
			this->panel3->TabIndex = 8;
			//
			// panel2
			//
			this->panel2->Dock = System::Windows::Forms::DockStyle::Left;
			this->panel2->Location = System::Drawing::Point(0, 0);
			this->panel2->Name = S"panel2";
			this->panel2->Size = System::Drawing::Size(8, 295);
			this->panel2->TabIndex = 7;
			//
			// tabPage2
			//
			this->tabPage2->Controls->Add(this->lBresInfo);
			this->tabPage2->Controls->Add(this->panel1);
			this->tabPage2->Controls->Add(this->panel6);
			this->tabPage2->Controls->Add(this->panel7);
			this->tabPage2->Controls->Add(this->panel8);
			this->tabPage2->Location = System::Drawing::Point(4, 27);
			this->tabPage2->Name = S"tabPage2";
			this->tabPage2->Size = System::Drawing::Size(376, 295);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = S"Resource Inspector";
			//
			// lBresInfo
			//
			this->lBresInfo->BackColor = System::Drawing::Color::FromArgb((System::Byte)255, (System::Byte)224, (System::Byte)192);
			this->lBresInfo->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lBresInfo->ColumnWidth = 100;
			this->lBresInfo->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lBresInfo->ItemHeight = 16;
			this->lBresInfo->Location = System::Drawing::Point(8, 16);
			this->lBresInfo->Name = S"lBresInfo";
			this->lBresInfo->Size = System::Drawing::Size(360, 263);
			this->lBresInfo->TabIndex = 11;
			//
			// panel1
			//
			this->panel1->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel1->Location = System::Drawing::Point(8, 0);
			this->panel1->Name = S"panel1";
			this->panel1->Size = System::Drawing::Size(360, 16);
			this->panel1->TabIndex = 10;
			//
			// panel6
			//
			this->panel6->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel6->Location = System::Drawing::Point(8, 279);
			this->panel6->Name = S"panel6";
			this->panel6->Size = System::Drawing::Size(360, 16);
			this->panel6->TabIndex = 9;
			//
			// panel7
			//
			this->panel7->Dock = System::Windows::Forms::DockStyle::Right;
			this->panel7->Location = System::Drawing::Point(368, 0);
			this->panel7->Name = S"panel7";
			this->panel7->Size = System::Drawing::Size(8, 295);
			this->panel7->TabIndex = 8;
			//
			// panel8
			//
			this->panel8->Dock = System::Windows::Forms::DockStyle::Left;
			this->panel8->Location = System::Drawing::Point(0, 0);
			this->panel8->Name = S"panel8";
			this->panel8->Size = System::Drawing::Size(8, 295);
			this->panel8->TabIndex = 7;
			//
			// tabPage3
			//
			this->tabPage3->Controls->Add(this->lBlog);
			this->tabPage3->Controls->Add(this->panel9);
			this->tabPage3->Controls->Add(this->panel10);
			this->tabPage3->Controls->Add(this->panel11);
			this->tabPage3->Controls->Add(this->panel12);
			this->tabPage3->Location = System::Drawing::Point(4, 27);
			this->tabPage3->Name = S"tabPage3";
			this->tabPage3->Size = System::Drawing::Size(376, 295);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = S"Log";
			//
			// lBlog
			//
			this->lBlog->BackColor = System::Drawing::Color::FromArgb((System::Byte)255, (System::Byte)224, (System::Byte)192);
			this->lBlog->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lBlog->ColumnWidth = 100;
			this->lBlog->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lBlog->ItemHeight = 16;
			this->lBlog->Location = System::Drawing::Point(8, 16);
			this->lBlog->MultiColumn = true;
			this->lBlog->Name = S"lBlog";
			this->lBlog->Size = System::Drawing::Size(360, 263);
			this->lBlog->TabIndex = 16;
			//
			// panel9
			//
			this->panel9->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel9->Location = System::Drawing::Point(8, 0);
			this->panel9->Name = S"panel9";
			this->panel9->Size = System::Drawing::Size(360, 16);
			this->panel9->TabIndex = 15;
			//
			// panel10
			//
			this->panel10->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel10->Location = System::Drawing::Point(8, 279);
			this->panel10->Name = S"panel10";
			this->panel10->Size = System::Drawing::Size(360, 16);
			this->panel10->TabIndex = 14;
			//
			// panel11
			//
			this->panel11->Dock = System::Windows::Forms::DockStyle::Right;
			this->panel11->Location = System::Drawing::Point(368, 0);
			this->panel11->Name = S"panel11";
			this->panel11->Size = System::Drawing::Size(8, 295);
			this->panel11->TabIndex = 13;
			//
			// panel12
			//
			this->panel12->Dock = System::Windows::Forms::DockStyle::Left;
			this->panel12->Location = System::Drawing::Point(0, 0);
			this->panel12->Name = S"panel12";
			this->panel12->Size = System::Drawing::Size(8, 295);
			this->panel12->TabIndex = 12;
			//
			// openFileDialog1
			//
			this->openFileDialog1->DefaultExt = S"DLL";
			this->openFileDialog1->Filter = S"Dynamic Link Libraries (*.DLL)|*.dll|All files (*.*)|*.*";
			this->openFileDialog1->Title = S"Open Resource..";
			//
			// resManForm
			//
			this->AutoScaleBaseSize = System::Drawing::Size(6, 15);
			this->ClientSize = System::Drawing::Size(384, 326);
			this->Controls->Add(this->tabControl1);
			this->Icon = (__try_cast<System::Drawing::Icon *  >(resources->GetObject(S"$this.Icon")));
			this->Name = S"resManForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = S"Resource Manager 1.0";
			this->Closing += new System::ComponentModel::CancelEventHandler(this, resManForm_Closing);
			this->Closed += new System::EventHandler(this, resManForm_Closed);
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->panel4->ResumeLayout(false);
			this->tabPage2->ResumeLayout(false);
			this->tabPage3->ResumeLayout(false);
			this->ResumeLayout(false);

		}



		//
	private: System::Void button1_Click(System::Object *  sender, System::EventArgs *  e);

	private: System::Void tabControl1_SelectedIndexChanged(System::Object *  sender, System::EventArgs *  e);

	private: System::Void button3_Click(System::Object *  sender, System::EventArgs *  e);

	private: System::Void button4_Click(System::Object *  sender, System::EventArgs *  e);

	private: void updateRes(void);
	private: loaderDLL* resManForm::getSelectedResource();

	private: System::Void resManForm_Closing(System::Object *  sender, System::ComponentModel::CancelEventArgs *  e);

private: System::Void resManForm_Closed(System::Object *  sender, System::EventArgs *  e);

};
}
