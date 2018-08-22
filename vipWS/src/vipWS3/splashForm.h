#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::IO;

#define _IW_VERSION S"0.7.256 Alpha"

namespace vipWS3
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
			String* imageFile = String::Concat(Path::GetDirectoryName(Application::ExecutablePath), S"\\data\\splash.bmp");
			if (!File::Exists(imageFile))
			 {
				this->Visible = false;
				CloseInstance();
				return;
			 }
			back = new Bitmap(imageFile);
			Color tr = Color::FromArgb(128,128,128);
			back->MakeTransparent(tr);
			this->BackgroundImage = back;

			this->Width = back->Width;
			this->Height = back->Height;

			lb_version->Text = String::Format(S"version {0}", _IW_VERSION);
		}
	private: System::Windows::Forms::Label *  lb_version;

	public: static splashForm* m_instance;
	public:
		static void newInstance(void)
		{
			m_instance = new splashForm();
			Application::Run(m_instance);
		}
		static void CloseInstance(void)
		{
			if (m_instance != NULL)
				m_instance->Close();
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
			this->lb_version = new System::Windows::Forms::Label();
			this->SuspendLayout();
			//
			// lb_version
			//
			this->lb_version->AutoSize = true;
			this->lb_version->BackColor = System::Drawing::Color::Transparent;
			this->lb_version->Font = new System::Drawing::Font(S"Verdana", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (System::Byte)0);
			this->lb_version->ForeColor = System::Drawing::Color::FromArgb((System::Byte)128, (System::Byte)128, (System::Byte)255);
			this->lb_version->Location = System::Drawing::Point(208, 248);
			this->lb_version->Name = S"lb_version";
			this->lb_version->Size = System::Drawing::Size(196, 24);
			this->lb_version->TabIndex = 0;
			this->lb_version->Text = S"version 0.7.256 Alpha";
			this->lb_version->TextAlign = System::Drawing::ContentAlignment::TopRight;
			//
			// splashForm
			//
			this->AutoScale = false;
			this->AutoScaleBaseSize = System::Drawing::Size(6, 15);
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
				 e->Graphics->DrawImage(back, 0, 0);
			 }

	private: System::Void splashForm_Click(System::Object *  sender, System::EventArgs *  e)
			 {
				 CloseInstance();
				 this->Close();
			 }

	};
}
