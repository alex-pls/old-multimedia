/**
 *  @class   logForm
 *
 *  @brief   log viewver form (interface)
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

namespace vipPS
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	/// <summary>
	/// Riepilogo per logForm
	///
	/// AVVISO: se si modifica il nome della classe, sarà necessario modificare la
	///          proprietà "Nome file di risorse" relativa allo strumento di compilazione delle risorse gestite
	///          associato a tutti i file RESX da cui dipende la classe. In caso contrario,
	///          le finestre di progettazione non saranno in grado di interagire correttamente con le
	///          risorse localizzate associate al form.
	/// </summary>
	public __gc class logForm : public System::Windows::Forms::Form
	{
	public:
		logForm(void)
		{
			InitializeComponent();
		}

		void append(String* message)
		{
			tBlog->AppendText(S"\r\n");
			tBlog->AppendText(message);
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

	private: System::Windows::Forms::MenuItem *  menuItem2;
	private: System::Windows::Forms::MenuItem *  menuItem3;
	private: System::Windows::Forms::MenuItem *  menuItem4;
	private: System::Windows::Forms::ContextMenu *  contextMenu1;
	private: System::Windows::Forms::SaveFileDialog *  saveFileDialog1;
	private: System::Windows::Forms::RichTextBox *  tBlog;

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
			System::Resources::ResourceManager *  resources = new System::Resources::ResourceManager(__typeof(vipPS::logForm));
			this->contextMenu1 = new System::Windows::Forms::ContextMenu();
			this->menuItem2 = new System::Windows::Forms::MenuItem();
			this->menuItem3 = new System::Windows::Forms::MenuItem();
			this->menuItem4 = new System::Windows::Forms::MenuItem();
			this->saveFileDialog1 = new System::Windows::Forms::SaveFileDialog();
			this->tBlog = new System::Windows::Forms::RichTextBox();
			this->SuspendLayout();
			// 
			// contextMenu1
			// 
			System::Windows::Forms::MenuItem* __mcTemp__1[] = new System::Windows::Forms::MenuItem*[3];
			__mcTemp__1[0] = this->menuItem2;
			__mcTemp__1[1] = this->menuItem3;
			__mcTemp__1[2] = this->menuItem4;
			this->contextMenu1->MenuItems->AddRange(__mcTemp__1);
			// 
			// menuItem2
			// 
			this->menuItem2->Index = 0;
			this->menuItem2->Text = S"&Save As..";
			this->menuItem2->Click += new System::EventHandler(this, menuItem2_Click);
			// 
			// menuItem3
			// 
			this->menuItem3->Index = 1;
			this->menuItem3->Text = S"-";
			// 
			// menuItem4
			// 
			this->menuItem4->Index = 2;
			this->menuItem4->Text = S"&Clear";
			this->menuItem4->Click += new System::EventHandler(this, menuItem4_Click);
			// 
			// tBlog
			// 
			this->tBlog->BackColor = System::Drawing::Color::PowderBlue;
			this->tBlog->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->tBlog->ContextMenu = this->contextMenu1;
			this->tBlog->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tBlog->Location = System::Drawing::Point(0, 0);
			this->tBlog->Name = S"tBlog";
			this->tBlog->ReadOnly = true;
			this->tBlog->Size = System::Drawing::Size(504, 174);
			this->tBlog->TabIndex = 0;
			this->tBlog->Text = S"";
			// 
			// logForm
			// 
			this->AutoScaleBaseSize = System::Drawing::Size(6, 15);
			this->ClientSize = System::Drawing::Size(504, 174);
			this->ContextMenu = this->contextMenu1;
			this->Controls->Add(this->tBlog);
			this->Icon = (__try_cast<System::Drawing::Icon *  >(resources->GetObject(S"$this.Icon")));
			this->Name = S"logForm";
			this->Text = S"Package Studio Log viewer";
			this->Closing += new System::ComponentModel::CancelEventHandler(this, logForm_Closing);
			this->ResumeLayout(false);

		}
		//
	private: System::Void menuItem2_Click(System::Object *  sender, System::EventArgs *  e);

	private: System::Void menuItem4_Click(System::Object *  sender, System::EventArgs *  e);

	private: System::Void logForm_Closing(System::Object *  sender, System::ComponentModel::CancelEventArgs *  e);


};
}
