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
	/// Riepilogo per aboutws
	///
	/// AVVISO: se si modifica il nome della classe, sarà necessario modificare la
	///          proprietà "Nome file di risorse" relativa allo strumento di compilazione delle risorse gestite
	///          associato a tutti i file RESX da cui dipende la classe. In caso contrario,
	///          le finestre di progettazione non saranno in grado di interagire correttamente con le
	///          risorse localizzate associate al form.
	/// </summary>
	public __gc class aboutws : public System::Windows::Forms::Form
	{
	public:
		aboutws(void)
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
	private: System::Windows::Forms::LinkLabel *  linkLabel1;

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
			System::Resources::ResourceManager *  resources = new System::Resources::ResourceManager(__typeof(vipWS3::aboutws));
			this->linkLabel1 = new System::Windows::Forms::LinkLabel();
			this->SuspendLayout();
			//
			// linkLabel1
			//
			this->linkLabel1->AutoSize = true;
			this->linkLabel1->BackColor = System::Drawing::Color::Transparent;
			this->linkLabel1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->linkLabel1->LinkColor = System::Drawing::Color::ForestGreen;
			this->linkLabel1->Location = System::Drawing::Point(192, 216);
			this->linkLabel1->Name = S"linkLabel1";
			this->linkLabel1->Size = System::Drawing::Size(120, 18);
			this->linkLabel1->TabIndex = 0;
			this->linkLabel1->TabStop = true;
			this->linkLabel1->Text = S"by Alessandro Polo";
			//
			// aboutws
			//
			this->AutoScale = false;
			this->AutoScaleBaseSize = System::Drawing::Size(6, 15);
			this->BackgroundImage = (__try_cast<System::Drawing::Image *  >(resources->GetObject(S"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(318, 238);
			this->Controls->Add(this->linkLabel1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Icon = (__try_cast<System::Drawing::Icon *  >(resources->GetObject(S"$this.Icon")));
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = S"aboutws";
			this->ShowInTaskbar = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = S"about VIPLib WorkShop..";
			this->ResumeLayout(false);

		}
	};
}
