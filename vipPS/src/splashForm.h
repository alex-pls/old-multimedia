/**
 *  @class   splashForm
 *
 *  @brief   splash form (interface)
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

#define _PS_VERSION S"0.9.12"
#define _PS_BASEURL S"http://mmlab.science.unitn.it:8080/svn/vipPS/trunk/"


#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::IO;
using namespace System::Resources;


namespace vipPS
{
	/// <summary>
	/// Riepilogo per splashForm
	///
	/// AVVISO: se si modifica il nome della classe, sarà necessario modificare la
	///          proprietà "Nome file di risorse" relativa allo strumento di compilazione delle risorse gestite
	///          associato a tutti i file RESX da cui dipende la classe. In caso contrario,
	///          le finestre di progettazione non saranno in grado di interagire correttamente con le
	///          risorse localizzate associate al form.
	/// </summary>
	public __gc class splashForm : public System::Windows::Forms::Form
	{
	public:
		splashForm(void)
		{
			InitializeComponent();
//			String* imageFile = String::Concat(Path::GetDirectoryName(Application::ExecutablePath), S"\\data\\splash.bmp");
//			if (!File::Exists(imageFile))
//			 {
//				this->Visible = false;
//				CloseInstance();
//				return;
//			 }
//			ResourceManager* resources = new ResourceManager(this->GetType());
//
//			back = __try_cast<System::Drawing::Bitmap*>((resources->GetObject("&this.bgImage")));
//			back = new Bitmap( __try_cast<System::Drawing::Bitmap*>((resources->GetObject("&this.bgImage"))));

//			MessageBox::Show(this, S"", back->Width.ToString());

//			Color tr = Color::FromArgb(128,128,128);
//			back->MakeTransparent(tr);
//			this->BackgroundImage = back;
			
//			back = new Bitmap(imageFile);
//			Color tr = Color::FromArgb(128,128,128);
//			back->MakeTransparent(tr);
//			this->BackgroundImage = back;

//			this->Width = back->Width;
//			this->Height = back->Height;

			this->Width = 500;
			this->Height = 400;

			Color tr = Color::FromArgb(200,200, 200);
			__try_cast<System::Drawing::Bitmap*>(this->BackgroundImage)->MakeTransparent(tr);

			lb_version->Text = String::Format(S"version {0}", _PS_VERSION);
		}
	private: System::Windows::Forms::Label *  lb_version;

	public: static splashForm* m_instance;

	public:
		static void newInstance(void)
		{
			m_instance = NULL;
			m_instance = new splashForm();
		}

		static void runInstance(void)
		{
			if (m_instance != NULL)
				Application::Run(m_instance);
		}

		static void CloseInstance(void)
		{
			if (m_instance != NULL)
			 {
				m_instance->Visible = false;
				m_instance->Close();
			 }
			m_instance = NULL;
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

	private: Bitmap* back;

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
			System::Resources::ResourceManager *  resources = new System::Resources::ResourceManager(__typeof(vipPS::splashForm));
			this->lb_version = new System::Windows::Forms::Label();
			this->SuspendLayout();
			// 
			// lb_version
			// 
			this->lb_version->BackColor = System::Drawing::Color::Transparent;
			this->lb_version->Font = new System::Drawing::Font(S"Verdana", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, (System::Byte)0);
			this->lb_version->ForeColor = System::Drawing::Color::CornflowerBlue;
			this->lb_version->Location = System::Drawing::Point(304, 72);
			this->lb_version->Name = S"lb_version";
			this->lb_version->Size = System::Drawing::Size(192, 40);
			this->lb_version->TabIndex = 0;
			this->lb_version->Text = S"version 0.9.12";
			this->lb_version->TextAlign = System::Drawing::ContentAlignment::BottomRight;
			// 
			// splashForm
			// 
			this->AutoScale = false;
			this->AutoScaleBaseSize = System::Drawing::Size(6, 15);
			this->BackgroundImage = (__try_cast<System::Drawing::Image *  >(resources->GetObject(S"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(500, 400);
			this->Controls->Add(this->lb_version);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = S"splashForm";
			this->ShowInTaskbar = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->TopMost = true;
			this->Click += new System::EventHandler(this, splashForm_Click);
			this->Paint += new System::Windows::Forms::PaintEventHandler(this, splashForm_Paint);
			this->ResumeLayout(false);

		}
	private: System::Void splashForm_Paint(System::Object *  sender, System::Windows::Forms::PaintEventArgs *  e)
			 {
//				 e->Graphics->DrawImage(back, 0, 0);
			 }

	private: System::Void splashForm_Click(System::Object *  sender, System::EventArgs *  e)
			 {
				 this->Visible = false;
				 CloseInstance();
			 }

	};
}
