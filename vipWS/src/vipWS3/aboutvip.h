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
	/// Riepilogo per aboutvip
	///
	/// AVVISO: se si modifica il nome della classe, sarà necessario modificare la
	///          proprietà "Nome file di risorse" relativa allo strumento di compilazione delle risorse gestite
	///          associato a tutti i file RESX da cui dipende la classe. In caso contrario,
	///          le finestre di progettazione non saranno in grado di interagire correttamente con le
	///          risorse localizzate associate al form.
	/// </summary>
	public __gc class aboutvip : public System::Windows::Forms::Form
	{
	public:
		aboutvip(void)
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
	private: System::Windows::Forms::Label *  label1;
	private: System::Windows::Forms::Label *  label2;
	private: System::Windows::Forms::Label *  label3;
	private: System::Windows::Forms::Label *  label4;

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
			System::Resources::ResourceManager *  resources = new System::Resources::ResourceManager(__typeof(vipWS3::aboutvip));
			this->label1 = new System::Windows::Forms::Label();
			this->label2 = new System::Windows::Forms::Label();
			this->label3 = new System::Windows::Forms::Label();
			this->label4 = new System::Windows::Forms::Label();
			this->SuspendLayout();
			//
			// label1
			//
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Location = System::Drawing::Point(16, 28);
			this->label1->Name = S"label1";
			this->label1->Size = System::Drawing::Size(219, 18);
			this->label1->TabIndex = 0;
			this->label1->Text = S"Copyright (C) Alessandro Polo 2005";
			//
			// label2
			//
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = new System::Drawing::Font(S"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, (System::Byte)0);
			this->label2->ForeColor = System::Drawing::Color::Navy;
			this->label2->Location = System::Drawing::Point(8, 8);
			this->label2->Name = S"label2";
			this->label2->Size = System::Drawing::Size(183, 20);
			this->label2->TabIndex = 1;
			this->label2->Text = S"VIPLib Framework 1.0.2";
			//
			// label3
			//
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::Color::Transparent;
			this->label3->ForeColor = System::Drawing::Color::FromArgb((System::Byte)0, (System::Byte)0, (System::Byte)192);
			this->label3->Location = System::Drawing::Point(8, 48);
			this->label3->Name = S"label3";
			this->label3->Size = System::Drawing::Size(172, 18);
			this->label3->TabIndex = 2;
			this->label3->Text = S"http://www.ewgate.net/viplib";
			this->label3->Click += new System::EventHandler(this, label3_Click);
			//
			// label4
			//
			this->label4->AutoSize = true;
			this->label4->BackColor = System::Drawing::Color::Transparent;
			this->label4->ForeColor = System::Drawing::Color::Green;
			this->label4->Location = System::Drawing::Point(240, 216);
			this->label4->Name = S"label4";
			this->label4->Size = System::Drawing::Size(78, 18);
			this->label4->TabIndex = 3;
			this->label4->Text = S"open source";
			//
			// aboutvip
			//
			this->AutoScale = false;
			this->AutoScaleBaseSize = System::Drawing::Size(6, 15);
			this->BackgroundImage = (__try_cast<System::Drawing::Image *  >(resources->GetObject(S"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(320, 240);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Icon = (__try_cast<System::Drawing::Icon *  >(resources->GetObject(S"$this.Icon")));
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = S"aboutvip";
			this->ShowInTaskbar = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = S"about VIPLib FrameWork..";
			this->ResumeLayout(false);

		}
	private: System::Void label3_Click(System::Object *  sender, System::EventArgs *  e)
			 {
				 System::Diagnostics::Process::Start(S"http://www.ewgate.net/viplib/");
			 }

};
}
