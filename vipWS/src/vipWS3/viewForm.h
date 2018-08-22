#pragma once
#include "../../../../source/vipUtility.h"
#include "outputInterface.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Drawing::Imaging;

// check on MSDN: Unsafe image processing !!

namespace vipWS3
{
	/// <summary>
	/// Riepilogo per viewForm
	///
	/// AVVISO: se si modifica il nome della classe, sarà necessario modificare la
	///          proprietà "Nome file di risorse" relativa allo strumento di compilazione delle risorse gestite
	///          associato a tutti i file RESX da cui dipende la classe. In caso contrario,
	///          le finestre di progettazione non saranno in grado di interagire correttamente con le
	///          risorse localizzate associate al form.
	/// </summary>
	public __gc class viewForm : public System::Windows::Forms::Form, public outputInterface
	{
	public:
		viewForm(void)
		{
			InitializeComponent();

			bm = new Bitmap(400, 400);
			pictureBoxBuffer->Image = dynamic_cast<Image*>(bm);
		}

		void Init() {};

		VIPRESULT importFrom(vipFrameRGB24* img)
		{
			if (img == NULL)
				return VIPRET_PARAM_ERR;

			if (img->width == 0 || img->height == 0 || img->data[0] == NULL)
				return VIPRET_PARAM_ERR;

			if (img->width != bm->Width || img->height != bm->Height)
			{
				bm->Dispose();
				bm = new Bitmap(img->width, img->height);
				pictureBoxBuffer->Image = dynamic_cast<Image*>(bm);
			}

			BitmapData* bitData;
			Rectangle rec(0,0, img->width, img->height);

			bitData = bm->LockBits(rec, ImageLockMode::WriteOnly, PixelFormat::Format24bppRgb);

			//this would be great but micro$oft always LIES, it's BGR not RGB.. so
			//memcpy(bitData->Scan0.ToPointer(), img.data[0], img.height*img.width*3* sizeof(char));
			unsigned char* dest = static_cast<unsigned char*>( bitData->Scan0.ToPointer() );
			vipUtility::conv_bgr_rgb(dest, (unsigned char*)img->data[0], img->width, img->height);

			bm->UnlockBits(bitData);

			pictureBoxBuffer->Refresh();

			return VIPRET_OK;
		}

		void sourcesUpdate(void) { }
		int setSource(sourceInterface* sF) { return 0; }
public: System::Object __gc* getObjectInstance() { return this; };

	protected:
		void Dispose(Boolean disposing)
		{
			if (disposing && components)
			{
				components->Dispose();
			}
			__super::Dispose(disposing);
		}

	private: PictureBox *  pictureBoxBuffer;
	public:  Bitmap* bm;

	private: System::Windows::Forms::ContextMenu *  contextMenu1;
	private: System::Windows::Forms::MenuItem *  menuItem1;
	private: System::Windows::Forms::SaveFileDialog *  saveFileDialog1;
	private: System::Windows::Forms::MenuItem *  menuItem2;
	private: System::Windows::Forms::MenuItem *  menuItem3;
	private: System::Windows::Forms::MenuItem *  menuItem4;
	private: System::Windows::Forms::MenuItem *  menuItem5;
	private: System::Windows::Forms::MenuItem *  menuItem6;
	private: System::Windows::Forms::MenuItem *  menuItem7;
	private: System::Windows::Forms::MenuItem *  menuItem8;

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
			System::Resources::ResourceManager *  resources = new System::Resources::ResourceManager(__typeof(vipWS3::viewForm));
			this->pictureBoxBuffer = new System::Windows::Forms::PictureBox();
			this->contextMenu1 = new System::Windows::Forms::ContextMenu();
			this->menuItem6 = new System::Windows::Forms::MenuItem();
			this->menuItem5 = new System::Windows::Forms::MenuItem();
			this->menuItem4 = new System::Windows::Forms::MenuItem();
			this->menuItem2 = new System::Windows::Forms::MenuItem();
			this->menuItem8 = new System::Windows::Forms::MenuItem();
			this->menuItem7 = new System::Windows::Forms::MenuItem();
			this->menuItem3 = new System::Windows::Forms::MenuItem();
			this->menuItem1 = new System::Windows::Forms::MenuItem();
			this->saveFileDialog1 = new System::Windows::Forms::SaveFileDialog();
			this->SuspendLayout();
			//
			// pictureBoxBuffer
			//
			this->pictureBoxBuffer->ContextMenu = this->contextMenu1;
			this->pictureBoxBuffer->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBoxBuffer->Location = System::Drawing::Point(0, 0);
			this->pictureBoxBuffer->Name = S"pictureBoxBuffer";
			this->pictureBoxBuffer->Size = System::Drawing::Size(600, 398);
			this->pictureBoxBuffer->TabIndex = 0;
			this->pictureBoxBuffer->TabStop = false;
			//
			// contextMenu1
			//
			System::Windows::Forms::MenuItem* __mcTemp__1[] = new System::Windows::Forms::MenuItem*[5];
			__mcTemp__1[0] = this->menuItem6;
			__mcTemp__1[1] = this->menuItem8;
			__mcTemp__1[2] = this->menuItem7;
			__mcTemp__1[3] = this->menuItem3;
			__mcTemp__1[4] = this->menuItem1;
			this->contextMenu1->MenuItems->AddRange(__mcTemp__1);
			//
			// menuItem6
			//
			this->menuItem6->Index = 0;
			System::Windows::Forms::MenuItem* __mcTemp__2[] = new System::Windows::Forms::MenuItem*[3];
			__mcTemp__2[0] = this->menuItem5;
			__mcTemp__2[1] = this->menuItem4;
			__mcTemp__2[2] = this->menuItem2;
			this->menuItem6->MenuItems->AddRange(__mcTemp__2);
			this->menuItem6->Text = S"Canvas";
			//
			// menuItem5
			//
			this->menuItem5->Index = 0;
			this->menuItem5->RadioCheck = true;
			this->menuItem5->Text = S"Normal";
			this->menuItem5->Click += new System::EventHandler(this, menuItem5_Click);
			//
			// menuItem4
			//
			this->menuItem4->Index = 1;
			this->menuItem4->RadioCheck = true;
			this->menuItem4->Text = S"AutoSize";
			this->menuItem4->Click += new System::EventHandler(this, menuItem4_Click);
			//
			// menuItem2
			//
			this->menuItem2->Index = 2;
			this->menuItem2->RadioCheck = true;
			this->menuItem2->Text = S"Stretch";
			this->menuItem2->Click += new System::EventHandler(this, menuItem2_Click);
			//
			// menuItem8
			//
			this->menuItem8->Index = 1;
			this->menuItem8->Text = S"-";
			//
			// menuItem7
			//
			this->menuItem7->Checked = true;
			this->menuItem7->Index = 2;
			this->menuItem7->Text = S"Scrollbars";
			this->menuItem7->Click += new System::EventHandler(this, menuItem7_Click);
			//
			// menuItem3
			//
			this->menuItem3->Index = 3;
			this->menuItem3->Text = S"-";
			//
			// menuItem1
			//
			this->menuItem1->Index = 4;
			this->menuItem1->Text = S"Save Image As..";
			this->menuItem1->Click += new System::EventHandler(this, menuItem1_Click);
			//
			// saveFileDialog1
			//
			this->saveFileDialog1->DefaultExt = S"JPG";
			this->saveFileDialog1->Filter = S"Bitmaps (*.BMP)|*.bmp|JPEG (*.jpg)|*.jpg";
			this->saveFileDialog1->OverwritePrompt = false;
			this->saveFileDialog1->RestoreDirectory = true;
			this->saveFileDialog1->Title = S"Save Frame As..";
			//
			// viewForm
			//
			this->AutoScaleBaseSize = System::Drawing::Size(6, 15);
			this->BackColor = System::Drawing::Color::FromArgb((System::Byte)224, (System::Byte)224, (System::Byte)224);
			this->ClientSize = System::Drawing::Size(600, 398);
			this->ContextMenu = this->contextMenu1;
			this->Controls->Add(this->pictureBoxBuffer);
			this->Icon = (__try_cast<System::Drawing::Icon *  >(resources->GetObject(S"$this.Icon")));
			this->Name = S"viewForm";
			this->ShowInTaskbar = false;
			this->Text = S"Visualization";
			this->Closed += new System::EventHandler(this, viewForm_Closed);
			this->ResumeLayout(false);

		}











		//
private: System::Void viewForm_Closed(System::Object *  sender, System::EventArgs *  e);

private: System::Void menuItem1_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			saveFileDialog1->InitialDirectory = String::Concat(IO::Path::GetDirectoryName(Application::ExecutablePath), S"\\shots");

			if ( saveFileDialog1->ShowDialog() == DialogResult::OK )
			{
				if ( saveFileDialog1->FileName->ToUpper()->EndsWith("BMP") )
					bm->Save(saveFileDialog1->FileName, Imaging::ImageFormat::Bmp);
				else if ( saveFileDialog1->FileName->ToUpper()->EndsWith("JPG") || saveFileDialog1->FileName->ToUpper()->EndsWith("JPEG") )
					bm->Save(saveFileDialog1->FileName, Imaging::ImageFormat::Jpeg);
			}
		 }

private: System::Void menuItem5_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 pictureBoxBuffer->SizeMode = PictureBoxSizeMode::Normal;
			 this->Refresh();
		 }

private: System::Void menuItem4_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 pictureBoxBuffer->SizeMode = PictureBoxSizeMode::AutoSize;
			 this->ClientSize = pictureBoxBuffer->Size;
			 this->Refresh();
		 }

private: System::Void menuItem2_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 pictureBoxBuffer->SizeMode = PictureBoxSizeMode::StretchImage;
			 this->Refresh();
		 }

private: System::Void menuItem7_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 this->AutoScroll = menuItem7->Checked;
			 this->Refresh();
		 }



};
}
