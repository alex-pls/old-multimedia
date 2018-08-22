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
	/// Riepilogo per notesForm
	///
	/// AVVISO: se si modifica il nome della classe, sarà necessario modificare la
	///          proprietà "Nome file di risorse" relativa allo strumento di compilazione delle risorse gestite
	///          associato a tutti i file RESX da cui dipende la classe. In caso contrario,
	///          le finestre di progettazione non saranno in grado di interagire correttamente con le
	///          risorse localizzate associate al form.
	/// </summary>
	public __gc class notesForm : public System::Windows::Forms::Form
	{
	public:
		notesForm(void)
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

	public: System::Windows::Forms::RichTextBox *  rTBdoc;
	private: System::Windows::Forms::ContextMenu *  contextMenu1;
	private: System::Windows::Forms::MenuItem *  menuItem1;
	private: System::Windows::Forms::MenuItem *  menuItem2;
	private: System::Windows::Forms::SaveFileDialog *  saveFileDialog1;
	private: System::Windows::Forms::OpenFileDialog *  openFileDialog1;
	private: System::Windows::Forms::MenuItem *  menuItem3;
	private: System::Windows::Forms::MenuItem *  menuItem4;

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
			System::Resources::ResourceManager *  resources = new System::Resources::ResourceManager(__typeof(vipWS3::notesForm));
			this->rTBdoc = new System::Windows::Forms::RichTextBox();
			this->contextMenu1 = new System::Windows::Forms::ContextMenu();
			this->menuItem2 = new System::Windows::Forms::MenuItem();
			this->menuItem1 = new System::Windows::Forms::MenuItem();
			this->menuItem3 = new System::Windows::Forms::MenuItem();
			this->menuItem4 = new System::Windows::Forms::MenuItem();
			this->saveFileDialog1 = new System::Windows::Forms::SaveFileDialog();
			this->openFileDialog1 = new System::Windows::Forms::OpenFileDialog();
			this->SuspendLayout();
			//
			// rTBdoc
			//
			this->rTBdoc->BackColor = System::Drawing::Color::WhiteSmoke;
			this->rTBdoc->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->rTBdoc->ContextMenu = this->contextMenu1;
			this->rTBdoc->Dock = System::Windows::Forms::DockStyle::Fill;
			this->rTBdoc->Location = System::Drawing::Point(0, 0);
			this->rTBdoc->Name = S"rTBdoc";
			this->rTBdoc->Size = System::Drawing::Size(440, 278);
			this->rTBdoc->TabIndex = 0;
			this->rTBdoc->Text = S"";
			//
			// contextMenu1
			//
			System::Windows::Forms::MenuItem* __mcTemp__1[] = new System::Windows::Forms::MenuItem*[4];
			__mcTemp__1[0] = this->menuItem2;
			__mcTemp__1[1] = this->menuItem1;
			__mcTemp__1[2] = this->menuItem3;
			__mcTemp__1[3] = this->menuItem4;
			this->contextMenu1->MenuItems->AddRange(__mcTemp__1);
			//
			// menuItem2
			//
			this->menuItem2->Index = 0;
			this->menuItem2->Text = S"&Save Text..";
			this->menuItem2->Click += new System::EventHandler(this, menuItem2_Click);
			//
			// menuItem1
			//
			this->menuItem1->Index = 1;
			this->menuItem1->Text = S"&Load Text..";
			this->menuItem1->Click += new System::EventHandler(this, menuItem1_Click);
			//
			// menuItem3
			//
			this->menuItem3->Index = 2;
			this->menuItem3->Text = S"-";
			//
			// menuItem4
			//
			this->menuItem4->Index = 3;
			this->menuItem4->Text = S"&Clear";
			this->menuItem4->Click += new System::EventHandler(this, menuItem4_Click);
			//
			// saveFileDialog1
			//
			this->saveFileDialog1->FileName = S"notes.txt";
			this->saveFileDialog1->Filter = S"Plain Text(*.TXT)|*.txt|RichText Documents (*.RTF)|*.rtf|All Files (*.*)|*.*";
			this->saveFileDialog1->FilterIndex = 0;
			this->saveFileDialog1->Title = S"Save Document..";
			//
			// openFileDialog1
			//
			this->openFileDialog1->FileName = S"notes.txt";
			this->openFileDialog1->Filter = S"Plain Text(*.TXT)|*.txt|RichText Documents (*.RTF)|*.rtf|All Files (*.*)|*.*";
			this->openFileDialog1->Title = S"Open Document..";
			//
			// notesForm
			//
			this->AutoScaleBaseSize = System::Drawing::Size(6, 15);
			this->ClientSize = System::Drawing::Size(440, 278);
			this->ContextMenu = this->contextMenu1;
			this->Controls->Add(this->rTBdoc);
			this->Icon = (__try_cast<System::Drawing::Icon *  >(resources->GetObject(S"$this.Icon")));
			this->Name = S"notesForm";
			this->Text = S"notesForm";
			this->ResumeLayout(false);

		}
		//
	private: System::Void menuItem2_Click(System::Object *  sender, System::EventArgs *  e)
			 {
				if ( !saveFileDialog1->InitialDirectory->Length)
					saveFileDialog1->InitialDirectory = Application::ExecutablePath;

				if ( saveFileDialog1->ShowDialog() == DialogResult::OK )
				{
					this->Cursor = Cursors::WaitCursor;
					rTBdoc->SaveFile(saveFileDialog1->FileName);
					this->Cursor = Cursors::Default;
				}
			 }

	private: System::Void menuItem1_Click(System::Object *  sender, System::EventArgs *  e)
			 {
				if ( !openFileDialog1->InitialDirectory->Length)
					openFileDialog1->InitialDirectory = Application::ExecutablePath;

				if ( openFileDialog1->ShowDialog() == DialogResult::OK )
				{
					this->Cursor = Cursors::WaitCursor;
					rTBdoc->LoadFile(openFileDialog1->FileName);
					this->Cursor = Cursors::Default;
				}

			 }

	private: System::Void menuItem4_Click(System::Object *  sender, System::EventArgs *  e)
			 {
				 rTBdoc->Clear();
			 }

};
}
