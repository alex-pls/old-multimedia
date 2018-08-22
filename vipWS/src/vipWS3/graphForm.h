#pragma once
#include "sourceInterface.h"


using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace vipWS3
{
	/// <summary>
	/// Riepilogo per graphForm
	///
	/// AVVISO: se si modifica il nome della classe, sarà necessario modificare la
	///          proprietà "Nome file di risorse" relativa allo strumento di compilazione delle risorse gestite
	///          associato a tutti i file RESX da cui dipende la classe. In caso contrario,
	///          le finestre di progettazione non saranno in grado di interagire correttamente con le
	///          risorse localizzate associate al form.
	/// </summary>
	public __gc class graphForm : public System::Windows::Forms::Form
	{
	public:
		graphForm(void);

		void Init(void);


	protected:
		void Dispose(Boolean disposing);

	private: sourceInterface* sF;

	private: System::Windows::Forms::Panel *  panel1;
	private: System::Windows::Forms::Button *  button1;
	private: System::Windows::Forms::Button *  button2;

	private: System::Windows::Forms::PictureBox *  pB;
	private: System::Windows::Forms::ComboBox *  cBsources;

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
			System::Resources::ResourceManager *  resources = new System::Resources::ResourceManager(__typeof(vipWS3::graphForm));
			this->panel1 = new System::Windows::Forms::Panel();
			this->cBsources = new System::Windows::Forms::ComboBox();
			this->button2 = new System::Windows::Forms::Button();
			this->button1 = new System::Windows::Forms::Button();
			this->pB = new System::Windows::Forms::PictureBox();
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			//
			// panel1
			//
			this->panel1->Controls->Add(this->cBsources);
			this->panel1->Controls->Add(this->button2);
			this->panel1->Controls->Add(this->button1);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->panel1->Location = System::Drawing::Point(0, 238);
			this->panel1->Name = S"panel1";
			this->panel1->Size = System::Drawing::Size(592, 40);
			this->panel1->TabIndex = 0;
			//
			// cBsources
			//
			this->cBsources->BackColor = System::Drawing::Color::FromArgb((System::Byte)192, (System::Byte)255, (System::Byte)192);
			this->cBsources->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cBsources->Location = System::Drawing::Point(8, 8);
			this->cBsources->Name = S"cBsources";
			this->cBsources->Size = System::Drawing::Size(312, 24);
			this->cBsources->TabIndex = 2;
			this->cBsources->SelectedIndexChanged += new System::EventHandler(this, cBsources_SelectedIndexChanged);
			//
			// button2
			//
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button2->Location = System::Drawing::Point(328, 8);
			this->button2->Name = S"button2";
			this->button2->Size = System::Drawing::Size(128, 24);
			this->button2->TabIndex = 1;
			this->button2->Text = S"Save As..";
			//
			// button1
			//
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Location = System::Drawing::Point(464, 8);
			this->button1->Name = S"button1";
			this->button1->Size = System::Drawing::Size(120, 24);
			this->button1->TabIndex = 0;
			this->button1->Text = S"Update";
			this->button1->Click += new System::EventHandler(this, button1_Click);
			//
			// pB
			//
			this->pB->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pB->Location = System::Drawing::Point(0, 0);
			this->pB->Name = S"pB";
			this->pB->Size = System::Drawing::Size(592, 238);
			this->pB->TabIndex = 1;
			this->pB->TabStop = false;
			//
			// graphForm
			//
			this->AutoScaleBaseSize = System::Drawing::Size(6, 15);
			this->ClientSize = System::Drawing::Size(592, 278);
			this->Controls->Add(this->pB);
			this->Controls->Add(this->panel1);
			this->Icon = (__try_cast<System::Drawing::Icon *  >(resources->GetObject(S"$this.Icon")));
			this->Name = S"graphForm";
			this->Text = S"Graph View 1.0";
			this->Closing += new System::ComponentModel::CancelEventHandler(this, graphForm_Closing);
			this->panel1->ResumeLayout(false);
			this->ResumeLayout(false);

		}
		//
	private: System::Void button1_Click(System::Object *  sender, System::EventArgs *  e);



private: void drawFilter(Graphics* g, int cX, int cY, int dX, int dY, String* myT);
private: void drawSource(Graphics* g, int cX, int cY, int dX, int dY, String* myT);
private: void drawOutput(Graphics* g, int cX, int cY, int dX, int dY, String* myT);
private: void drawConnector(Graphics* g, int cX, int cY, int dX, int dY, String* myT);

private: void doDrawFilterLoop(sourceInterface* currentSource, Graphics* g, int& pX, int& pY, int& dimX, int& dimY);


public:	void sourcesUpdate(void)
			{
				int oldSel = cBsources->SelectedIndex;
				cBsources->Items->Clear();
				for (int i=0; i<this->MdiParent->MdiChildren->Count; i++)
				{
					if (this->MdiParent->MdiChildren->get_Item(i)->GetType()->GetInterface("sourceInterface") &&
						!this->MdiParent->MdiChildren->get_Item(i)->GetType()->Name->Equals(this->GetType()->Name))
						cBsources->Items->Add( ( static_cast<Form*> (this->MdiParent->MdiChildren->get_Item(i)) )->Text );
				}
				if ( oldSel < 1 && cBsources->Items->Count == 1 )
					oldSel = 0;
				else if ( oldSel >= cBsources->Items->Count )
					oldSel = cBsources->Items->Count-1;
				cBsources->SelectedIndex = oldSel;
			}


private: System::Void cBsources_SelectedIndexChanged(System::Object *  sender, System::EventArgs *  e)
		 {
			 for (int i=0; i<this->MdiParent->MdiChildren->Count; i++)
			 {

				if ( static_cast<Form*>(this->MdiParent->MdiChildren->get_Item(i))->Text->Equals(cBsources->SelectedItem->ToString() )	)
				{
					sF = static_cast<sourceInterface*>(this->MdiParent->MdiChildren->get_Item(i));
					break;
				}
			 }
		 }








	private: System::Void graphForm_Closing(System::Object *  sender, System::ComponentModel::CancelEventArgs *  e);

};
}
