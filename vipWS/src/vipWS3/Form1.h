#pragma once

#include "loaderdll.h"


#include "resManForm.h"
#include "notesForm.h"
#include "logForm.h"
#include "optionForm.h"
#include "statsForm.h"
#include "splashForm.h"
#include "graphForm.h"

void CloseSplash();


namespace vipWS3
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Riepilogo per Form1
	///
	/// AVVISO: se si modifica il nome della classe, sarà necessario modificare la
	///          proprietà "Nome file di risorse" relativa allo strumento di compilazione delle risorse gestite
	///          associate a tutti i file RESX da cui dipende la classe. In caso contrario,
	///          le finestre di progettazione non saranno in grado di interagire correttamente con le
	///          risorse localizzate associate al form.
	/// </summary>
	public __gc class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void);

		void writeLog(String* message);
		void writeLog(String* message, Form* sender);

		void updateChildFormsList(void);
		void registerResource(int res_index);


	protected:


		void Dispose(Boolean disposing);

	private: loaderDLL** resources; //fixed 64
	private: resManForm* myResManForm;

	private: StreamWriter* logWriter;
	private: Form* logLastSender;
	private: logForm* myLogForm;
	private: String* logFilePath;

	private: optionForm* myOptionForm;
	private: statsForm* myStatsForm;
	private: graphForm* myGraphForm;

	private: System::Windows::Forms::MenuItem *  menuItem1;
	private: System::Windows::Forms::MenuItem *  menuItem2;
	private: System::Windows::Forms::MenuItem *  menuItem6;
	private: System::Windows::Forms::MenuItem *  menuItem8;
	private: System::Windows::Forms::MenuItem *  menuItem9;
	private: System::Windows::Forms::MenuItem *  menuItem10;
	private: System::Windows::Forms::MenuItem *  menuItem11;
	private: System::Windows::Forms::MenuItem *  menuItem12;
	private: System::Windows::Forms::MenuItem *  menuItem13;
	private: System::Windows::Forms::MenuItem *  menuItem14;
	private: System::Windows::Forms::MenuItem *  menuItem15;
	private: System::Windows::Forms::MenuItem *  menuItem16;
	private: System::Windows::Forms::MenuItem *  menuItem17;
	private: System::Windows::Forms::MenuItem *  menuItem18;
	private: System::Windows::Forms::MenuItem *  menuItem19;
	private: System::Windows::Forms::MenuItem *  menuItem20;
	private: System::Windows::Forms::MenuItem *  menuItem21;
	private: System::Windows::Forms::MenuItem *  menuItem23;
	private: System::Windows::Forms::MenuItem *  menuItem25;
	private: System::Windows::Forms::StatusBar *  statusBar1;
	private: System::Windows::Forms::StatusBarPanel *  statusBarPanel1;
	private: System::Windows::Forms::StatusBarPanel *  statusBarPanel2;
	private: System::Windows::Forms::StatusBarPanel *  statusBarPanel3;
	private: System::Windows::Forms::MainMenu *  mainMenu1;
	private: System::Windows::Forms::OpenFileDialog *  openFileDialog1;
	private: System::Windows::Forms::SaveFileDialog *  saveFileDialog1;
	private: System::Windows::Forms::MenuItem *  menuItem27;
	private: System::Windows::Forms::MenuItem *  menuItem31;
	private: System::Windows::Forms::MenuItem *  menuItem32;
	private: System::Windows::Forms::MenuItem *  menuItem34;
	private: System::Windows::Forms::MenuItem *  menuItem33;
	private: System::Windows::Forms::MenuItem *  menuItem35;
	private: System::Windows::Forms::MenuItem *  menuItem36;
	private: System::Windows::Forms::MenuItem *  menuItem28;
	private: System::Windows::Forms::MenuItem *  menuItem3;
	private: System::Windows::Forms::MenuItem *  menuItem4;
	private: System::Windows::Forms::MenuItem *  menuItem29;
	private: System::Windows::Forms::MenuItem *  menuItem30;
	private: System::Windows::Forms::MenuItem *  menuItem38;
	private: System::Windows::Forms::MenuItem *  menuItem39;
	private: System::Windows::Forms::MenuItem *  menuItem40;
	private: System::Windows::Forms::MenuItem *  menuItem41;
	private: System::Windows::Forms::MenuItem *  menuItem42;
	private: System::Windows::Forms::MenuItem *  menuItem43;
	private: System::Windows::Forms::MenuItem *  menuItem44;
	private: System::Windows::Forms::MenuItem *  menuItem45;
	private: System::Windows::Forms::MenuItem *  menuItem46;
	private: System::Windows::Forms::MenuItem *  menuItem47;
	private: System::Windows::Forms::MenuItem *  menuItem48;
	private: System::Windows::Forms::MenuItem *  menuItem49;
	private: System::Windows::Forms::MenuItem *  menuItem50;
	private: System::Windows::Forms::MenuItem *  menuItem51;
	private: System::Windows::Forms::MenuItem *  menuItem52;
	private: System::Windows::Forms::MenuItem *  menuItem53;
	private: System::Windows::Forms::MenuItem *  menuItem54;
	private: System::Windows::Forms::MenuItem *  menuItem55;
	private: System::Windows::Forms::MenuItem *  menuItem56;
	private: System::Windows::Forms::MenuItem *  menuItem57;
	private: System::Windows::Forms::MenuItem *  menuItem58;
	private: System::Windows::Forms::MenuItem *  menuItem59;
	private: System::Windows::Forms::MenuItem *  menuItem61;
	private: System::Windows::Forms::MenuItem *  menuItem62;
	private: System::Windows::Forms::ToolBar *  toolBar1;
	private: System::Windows::Forms::MenuItem *  menuItem5;
	private: System::Windows::Forms::MenuItem *  menuItem7;
	private: System::Windows::Forms::MenuItem *  menuItem37;
	private: System::Windows::Forms::ImageList *  imageList1;
	private: System::Windows::Forms::ToolBarButton *  toolBarSeparator1;
	private: System::Windows::Forms::ToolBarButton *  toolBarSeparator2;
	private: System::Windows::Forms::ToolBarButton *  tBb_openImage;
	private: System::Windows::Forms::ToolBarButton *  tBb_openVideo;
	private: System::Windows::Forms::ToolBarButton *  tBb_newView;

	private: System::Windows::Forms::ToolBarButton *  tBb_viewLog;
	private: System::Windows::Forms::ToolBarButton *  tBb_newNotepad;
	private: System::Windows::Forms::ToolBarButton *  toolBarSeparator3;
	private: System::Windows::Forms::ToolBarButton *  tBb_viewRes;
	private: System::Windows::Forms::ToolBarButton *  toolBarSeparator4;
	private: System::Windows::Forms::ToolBarButton *  toolBarButton1;
	private: System::Windows::Forms::ToolBarButton *  toolBarSeparator5;
	private: System::Windows::Forms::MenuItem *  menuItem60;
	private: System::Windows::Forms::MenuItem *  menuItem63;
	private: System::Windows::Forms::MenuItem *  menuItem64;
	private: System::Windows::Forms::MenuItem *  mISources;
	private: System::Windows::Forms::MenuItem *  mIFilters;
	private: System::Windows::Forms::MenuItem *  mIOutputs;
	private: System::Windows::Forms::MenuItem *  menuItem22;
	private: System::Windows::Forms::MenuItem *  menuItem24;
	private: System::Windows::Forms::MenuItem *  menuItem26;
	private: System::Windows::Forms::MenuItem *  menuItem65;
	private: System::Windows::Forms::MenuItem *  menuItem66;
	private: System::Windows::Forms::MenuItem *  menuItem67;
	private: System::Windows::Forms::MenuItem *  menuItem68;
	private: System::Windows::Forms::MenuItem *  menuItem69;
	private: System::Windows::Forms::MenuItem *  menuItem70;
	private: System::Windows::Forms::MenuItem *  menuItem72;
	private: System::Windows::Forms::MenuItem *  menuItem73;
	private: System::Windows::Forms::MenuItem *  menuItem74;
	private: System::Windows::Forms::MenuItem *  menuItem75;
	private: System::Windows::Forms::MenuItem *  menuItem71;
private: System::Windows::Forms::MenuItem *  mIBuffers;
private: System::Windows::Forms::MenuItem *  menuItem77;
private: System::Windows::Forms::MenuItem *  menuItem76;
private: System::Windows::Forms::ToolBarButton *  tBb_newDoctor;
private: System::Windows::Forms::ToolBarButton *  tBb_viewStats;
private: System::Windows::Forms::ToolBarButton *  tBb_openDX;
private: System::Windows::Forms::ToolBarButton *  tBb_viewGraph;
private: System::Windows::Forms::MenuItem *  menuItem78;
private: System::Windows::Forms::MenuItem *  menuItem79;
private: System::Windows::Forms::MenuItem *  menuItem80;
private: System::Windows::Forms::MenuItem *  menuItem81;
private: System::Windows::Forms::MenuItem *  menuItem82;
private: System::Windows::Forms::MenuItem *  menuItem83;
private: System::Windows::Forms::MenuItem *  menuItem84;
private: System::Windows::Forms::MenuItem *  menuItem85;
private: System::Windows::Forms::MenuItem *  menuItem86;


	private: System::ComponentModel::IContainer *  components;

	private:

		/// <summary>
		/// Variabile di progettazione necessaria.
		/// </summary>


		/// <summary>
		/// Metodo necessario per il supporto della finestra di progettazione. Non modificare
		/// il contenuto del metodo con l'editor di codice.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = new System::ComponentModel::Container();
			System::Resources::ResourceManager *  resources = new System::Resources::ResourceManager(__typeof(vipWS3::Form1));
			this->mainMenu1 = new System::Windows::Forms::MainMenu();
			this->menuItem1 = new System::Windows::Forms::MenuItem();
			this->menuItem2 = new System::Windows::Forms::MenuItem();
			this->menuItem4 = new System::Windows::Forms::MenuItem();
			this->menuItem45 = new System::Windows::Forms::MenuItem();
			this->menuItem3 = new System::Windows::Forms::MenuItem();
			this->menuItem66 = new System::Windows::Forms::MenuItem();
			this->menuItem29 = new System::Windows::Forms::MenuItem();
			this->menuItem22 = new System::Windows::Forms::MenuItem();
			this->menuItem28 = new System::Windows::Forms::MenuItem();
			this->menuItem8 = new System::Windows::Forms::MenuItem();
			this->menuItem6 = new System::Windows::Forms::MenuItem();
			this->menuItem83 = new System::Windows::Forms::MenuItem();
			this->menuItem84 = new System::Windows::Forms::MenuItem();
			this->menuItem9 = new System::Windows::Forms::MenuItem();
			this->menuItem10 = new System::Windows::Forms::MenuItem();
			this->menuItem11 = new System::Windows::Forms::MenuItem();
			this->menuItem58 = new System::Windows::Forms::MenuItem();
			this->menuItem57 = new System::Windows::Forms::MenuItem();
			this->menuItem59 = new System::Windows::Forms::MenuItem();
			this->menuItem46 = new System::Windows::Forms::MenuItem();
			this->menuItem47 = new System::Windows::Forms::MenuItem();
			this->menuItem48 = new System::Windows::Forms::MenuItem();
			this->menuItem12 = new System::Windows::Forms::MenuItem();
			this->menuItem23 = new System::Windows::Forms::MenuItem();
			this->menuItem25 = new System::Windows::Forms::MenuItem();
			this->mISources = new System::Windows::Forms::MenuItem();
			this->menuItem30 = new System::Windows::Forms::MenuItem();
			this->menuItem85 = new System::Windows::Forms::MenuItem();
			this->menuItem65 = new System::Windows::Forms::MenuItem();
			this->menuItem38 = new System::Windows::Forms::MenuItem();
			this->menuItem39 = new System::Windows::Forms::MenuItem();
			this->menuItem41 = new System::Windows::Forms::MenuItem();
			this->mIFilters = new System::Windows::Forms::MenuItem();
			this->menuItem44 = new System::Windows::Forms::MenuItem();
			this->menuItem43 = new System::Windows::Forms::MenuItem();
			this->mIOutputs = new System::Windows::Forms::MenuItem();
			this->menuItem40 = new System::Windows::Forms::MenuItem();
			this->menuItem26 = new System::Windows::Forms::MenuItem();
			this->menuItem67 = new System::Windows::Forms::MenuItem();
			this->menuItem42 = new System::Windows::Forms::MenuItem();
			this->mIBuffers = new System::Windows::Forms::MenuItem();
			this->menuItem77 = new System::Windows::Forms::MenuItem();
			this->menuItem76 = new System::Windows::Forms::MenuItem();
			this->menuItem13 = new System::Windows::Forms::MenuItem();
			this->menuItem7 = new System::Windows::Forms::MenuItem();
			this->menuItem37 = new System::Windows::Forms::MenuItem();
			this->menuItem24 = new System::Windows::Forms::MenuItem();
			this->menuItem5 = new System::Windows::Forms::MenuItem();
			this->menuItem60 = new System::Windows::Forms::MenuItem();
			this->menuItem64 = new System::Windows::Forms::MenuItem();
			this->menuItem63 = new System::Windows::Forms::MenuItem();
			this->menuItem69 = new System::Windows::Forms::MenuItem();
			this->menuItem71 = new System::Windows::Forms::MenuItem();
			this->menuItem75 = new System::Windows::Forms::MenuItem();
			this->menuItem74 = new System::Windows::Forms::MenuItem();
			this->menuItem73 = new System::Windows::Forms::MenuItem();
			this->menuItem72 = new System::Windows::Forms::MenuItem();
			this->menuItem70 = new System::Windows::Forms::MenuItem();
			this->menuItem56 = new System::Windows::Forms::MenuItem();
			this->menuItem27 = new System::Windows::Forms::MenuItem();
			this->menuItem61 = new System::Windows::Forms::MenuItem();
			this->menuItem62 = new System::Windows::Forms::MenuItem();
			this->menuItem49 = new System::Windows::Forms::MenuItem();
			this->menuItem68 = new System::Windows::Forms::MenuItem();
			this->menuItem31 = new System::Windows::Forms::MenuItem();
			this->menuItem32 = new System::Windows::Forms::MenuItem();
			this->menuItem34 = new System::Windows::Forms::MenuItem();
			this->menuItem33 = new System::Windows::Forms::MenuItem();
			this->menuItem36 = new System::Windows::Forms::MenuItem();
			this->menuItem35 = new System::Windows::Forms::MenuItem();
			this->menuItem80 = new System::Windows::Forms::MenuItem();
			this->menuItem79 = new System::Windows::Forms::MenuItem();
			this->menuItem81 = new System::Windows::Forms::MenuItem();
			this->menuItem82 = new System::Windows::Forms::MenuItem();
			this->menuItem52 = new System::Windows::Forms::MenuItem();
			this->menuItem51 = new System::Windows::Forms::MenuItem();
			this->menuItem53 = new System::Windows::Forms::MenuItem();
			this->menuItem54 = new System::Windows::Forms::MenuItem();
			this->menuItem55 = new System::Windows::Forms::MenuItem();
			this->menuItem50 = new System::Windows::Forms::MenuItem();
			this->menuItem78 = new System::Windows::Forms::MenuItem();
			this->menuItem14 = new System::Windows::Forms::MenuItem();
			this->menuItem21 = new System::Windows::Forms::MenuItem();
			this->menuItem15 = new System::Windows::Forms::MenuItem();
			this->menuItem20 = new System::Windows::Forms::MenuItem();
			this->menuItem19 = new System::Windows::Forms::MenuItem();
			this->menuItem18 = new System::Windows::Forms::MenuItem();
			this->menuItem16 = new System::Windows::Forms::MenuItem();
			this->menuItem17 = new System::Windows::Forms::MenuItem();
			this->statusBar1 = new System::Windows::Forms::StatusBar();
			this->statusBarPanel1 = new System::Windows::Forms::StatusBarPanel();
			this->statusBarPanel2 = new System::Windows::Forms::StatusBarPanel();
			this->statusBarPanel3 = new System::Windows::Forms::StatusBarPanel();
			this->openFileDialog1 = new System::Windows::Forms::OpenFileDialog();
			this->saveFileDialog1 = new System::Windows::Forms::SaveFileDialog();
			this->toolBar1 = new System::Windows::Forms::ToolBar();
			this->tBb_openImage = new System::Windows::Forms::ToolBarButton();
			this->tBb_openVideo = new System::Windows::Forms::ToolBarButton();
			this->tBb_openDX = new System::Windows::Forms::ToolBarButton();
			this->toolBarSeparator1 = new System::Windows::Forms::ToolBarButton();
			this->tBb_newView = new System::Windows::Forms::ToolBarButton();
			this->toolBarSeparator4 = new System::Windows::Forms::ToolBarButton();
			this->tBb_viewRes = new System::Windows::Forms::ToolBarButton();
			this->toolBarSeparator2 = new System::Windows::Forms::ToolBarButton();
			this->toolBarButton1 = new System::Windows::Forms::ToolBarButton();
			this->toolBarSeparator5 = new System::Windows::Forms::ToolBarButton();
			this->tBb_newDoctor = new System::Windows::Forms::ToolBarButton();
			this->toolBarSeparator3 = new System::Windows::Forms::ToolBarButton();
			this->tBb_newNotepad = new System::Windows::Forms::ToolBarButton();
			this->tBb_viewGraph = new System::Windows::Forms::ToolBarButton();
			this->tBb_viewStats = new System::Windows::Forms::ToolBarButton();
			this->tBb_viewLog = new System::Windows::Forms::ToolBarButton();
			this->imageList1 = new System::Windows::Forms::ImageList(this->components);
			this->menuItem86 = new System::Windows::Forms::MenuItem();
			(__try_cast<System::ComponentModel::ISupportInitialize *  >(this->statusBarPanel1))->BeginInit();
			(__try_cast<System::ComponentModel::ISupportInitialize *  >(this->statusBarPanel2))->BeginInit();
			(__try_cast<System::ComponentModel::ISupportInitialize *  >(this->statusBarPanel3))->BeginInit();
			this->SuspendLayout();
			// 
			// mainMenu1
			// 
			System::Windows::Forms::MenuItem* __mcTemp__1[] = new System::Windows::Forms::MenuItem*[6];
			__mcTemp__1[0] = this->menuItem1;
			__mcTemp__1[1] = this->menuItem11;
			__mcTemp__1[2] = this->menuItem12;
			__mcTemp__1[3] = this->menuItem13;
			__mcTemp__1[4] = this->menuItem27;
			__mcTemp__1[5] = this->menuItem14;
			this->mainMenu1->MenuItems->AddRange(__mcTemp__1);
			this->mainMenu1->RightToLeft = (*__try_cast<__box System::Windows::Forms::RightToLeft *  >(resources->GetObject(S"mainMenu1.RightToLeft")));
			// 
			// menuItem1
			// 
			this->menuItem1->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem1.Enabled")));
			this->menuItem1->Index = 0;
			System::Windows::Forms::MenuItem* __mcTemp__2[] = new System::Windows::Forms::MenuItem*[9];
			__mcTemp__2[0] = this->menuItem2;
			__mcTemp__2[1] = this->menuItem3;
			__mcTemp__2[2] = this->menuItem22;
			__mcTemp__2[3] = this->menuItem8;
			__mcTemp__2[4] = this->menuItem6;
			__mcTemp__2[5] = this->menuItem83;
			__mcTemp__2[6] = this->menuItem84;
			__mcTemp__2[7] = this->menuItem9;
			__mcTemp__2[8] = this->menuItem10;
			this->menuItem1->MenuItems->AddRange(__mcTemp__2);
			this->menuItem1->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem1.Shortcut")));
			this->menuItem1->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem1.ShowShortcut")));
			this->menuItem1->Text = resources->GetString(S"menuItem1.Text");
			this->menuItem1->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem1.Visible")));
			// 
			// menuItem2
			// 
			this->menuItem2->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem2.Enabled")));
			this->menuItem2->Index = 0;
			System::Windows::Forms::MenuItem* __mcTemp__3[] = new System::Windows::Forms::MenuItem*[2];
			__mcTemp__3[0] = this->menuItem4;
			__mcTemp__3[1] = this->menuItem45;
			this->menuItem2->MenuItems->AddRange(__mcTemp__3);
			this->menuItem2->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem2.Shortcut")));
			this->menuItem2->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem2.ShowShortcut")));
			this->menuItem2->Text = resources->GetString(S"menuItem2.Text");
			this->menuItem2->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem2.Visible")));
			this->menuItem2->Click += new System::EventHandler(this, menuItem2_Click);
			// 
			// menuItem4
			// 
			this->menuItem4->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem4.Enabled")));
			this->menuItem4->Index = 0;
			this->menuItem4->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem4.Shortcut")));
			this->menuItem4->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem4.ShowShortcut")));
			this->menuItem4->Text = resources->GetString(S"menuItem4.Text");
			this->menuItem4->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem4.Visible")));
			this->menuItem4->Click += new System::EventHandler(this, menuItem4_Click);
			// 
			// menuItem45
			// 
			this->menuItem45->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem45.Enabled")));
			this->menuItem45->Index = 1;
			this->menuItem45->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem45.Shortcut")));
			this->menuItem45->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem45.ShowShortcut")));
			this->menuItem45->Text = resources->GetString(S"menuItem45.Text");
			this->menuItem45->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem45.Visible")));
			// 
			// menuItem3
			// 
			this->menuItem3->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem3.Enabled")));
			this->menuItem3->Index = 1;
			System::Windows::Forms::MenuItem* __mcTemp__4[] = new System::Windows::Forms::MenuItem*[3];
			__mcTemp__4[0] = this->menuItem66;
			__mcTemp__4[1] = this->menuItem29;
			__mcTemp__4[2] = this->menuItem86;
			this->menuItem3->MenuItems->AddRange(__mcTemp__4);
			this->menuItem3->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem3.Shortcut")));
			this->menuItem3->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem3.ShowShortcut")));
			this->menuItem3->Text = resources->GetString(S"menuItem3.Text");
			this->menuItem3->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem3.Visible")));
			// 
			// menuItem66
			// 
			this->menuItem66->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem66.Enabled")));
			this->menuItem66->Index = 0;
			this->menuItem66->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem66.Shortcut")));
			this->menuItem66->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem66.ShowShortcut")));
			this->menuItem66->Text = resources->GetString(S"menuItem66.Text");
			this->menuItem66->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem66.Visible")));
			this->menuItem66->Click += new System::EventHandler(this, menuItem66_Click);
			// 
			// menuItem29
			// 
			this->menuItem29->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem29.Enabled")));
			this->menuItem29->Index = 1;
			this->menuItem29->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem29.Shortcut")));
			this->menuItem29->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem29.ShowShortcut")));
			this->menuItem29->Text = resources->GetString(S"menuItem29.Text");
			this->menuItem29->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem29.Visible")));
			// 
			// menuItem22
			// 
			this->menuItem22->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem22.Enabled")));
			this->menuItem22->Index = 2;
			System::Windows::Forms::MenuItem* __mcTemp__5[] = new System::Windows::Forms::MenuItem*[1];
			__mcTemp__5[0] = this->menuItem28;
			this->menuItem22->MenuItems->AddRange(__mcTemp__5);
			this->menuItem22->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem22.Shortcut")));
			this->menuItem22->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem22.ShowShortcut")));
			this->menuItem22->Text = resources->GetString(S"menuItem22.Text");
			this->menuItem22->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem22.Visible")));
			// 
			// menuItem28
			// 
			this->menuItem28->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem28.Enabled")));
			this->menuItem28->Index = 0;
			this->menuItem28->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem28.Shortcut")));
			this->menuItem28->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem28.ShowShortcut")));
			this->menuItem28->Text = resources->GetString(S"menuItem28.Text");
			this->menuItem28->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem28.Visible")));
			this->menuItem28->Click += new System::EventHandler(this, menuItem28_Click);
			// 
			// menuItem8
			// 
			this->menuItem8->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem8.Enabled")));
			this->menuItem8->Index = 3;
			this->menuItem8->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem8.Shortcut")));
			this->menuItem8->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem8.ShowShortcut")));
			this->menuItem8->Text = resources->GetString(S"menuItem8.Text");
			this->menuItem8->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem8.Visible")));
			// 
			// menuItem6
			// 
			this->menuItem6->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem6.Enabled")));
			this->menuItem6->Index = 4;
			this->menuItem6->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem6.Shortcut")));
			this->menuItem6->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem6.ShowShortcut")));
			this->menuItem6->Text = resources->GetString(S"menuItem6.Text");
			this->menuItem6->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem6.Visible")));
			// 
			// menuItem83
			// 
			this->menuItem83->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem83.Enabled")));
			this->menuItem83->Index = 5;
			this->menuItem83->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem83.Shortcut")));
			this->menuItem83->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem83.ShowShortcut")));
			this->menuItem83->Text = resources->GetString(S"menuItem83.Text");
			this->menuItem83->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem83.Visible")));
			// 
			// menuItem84
			// 
			this->menuItem84->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem84.Enabled")));
			this->menuItem84->Index = 6;
			this->menuItem84->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem84.Shortcut")));
			this->menuItem84->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem84.ShowShortcut")));
			this->menuItem84->Text = resources->GetString(S"menuItem84.Text");
			this->menuItem84->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem84.Visible")));
			this->menuItem84->Click += new System::EventHandler(this, menuItem84_Click);
			// 
			// menuItem9
			// 
			this->menuItem9->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem9.Enabled")));
			this->menuItem9->Index = 7;
			this->menuItem9->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem9.Shortcut")));
			this->menuItem9->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem9.ShowShortcut")));
			this->menuItem9->Text = resources->GetString(S"menuItem9.Text");
			this->menuItem9->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem9.Visible")));
			// 
			// menuItem10
			// 
			this->menuItem10->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem10.Enabled")));
			this->menuItem10->Index = 8;
			this->menuItem10->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem10.Shortcut")));
			this->menuItem10->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem10.ShowShortcut")));
			this->menuItem10->Text = resources->GetString(S"menuItem10.Text");
			this->menuItem10->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem10.Visible")));
			this->menuItem10->Click += new System::EventHandler(this, menuItem10_Click);
			// 
			// menuItem11
			// 
			this->menuItem11->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem11.Enabled")));
			this->menuItem11->Index = 1;
			System::Windows::Forms::MenuItem* __mcTemp__6[] = new System::Windows::Forms::MenuItem*[6];
			__mcTemp__6[0] = this->menuItem58;
			__mcTemp__6[1] = this->menuItem57;
			__mcTemp__6[2] = this->menuItem59;
			__mcTemp__6[3] = this->menuItem46;
			__mcTemp__6[4] = this->menuItem47;
			__mcTemp__6[5] = this->menuItem48;
			this->menuItem11->MenuItems->AddRange(__mcTemp__6);
			this->menuItem11->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem11.Shortcut")));
			this->menuItem11->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem11.ShowShortcut")));
			this->menuItem11->Text = resources->GetString(S"menuItem11.Text");
			this->menuItem11->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem11.Visible")));
			// 
			// menuItem58
			// 
			this->menuItem58->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem58.Enabled")));
			this->menuItem58->Index = 0;
			this->menuItem58->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem58.Shortcut")));
			this->menuItem58->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem58.ShowShortcut")));
			this->menuItem58->Text = resources->GetString(S"menuItem58.Text");
			this->menuItem58->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem58.Visible")));
			this->menuItem58->Click += new System::EventHandler(this, menuItem58_Click);
			// 
			// menuItem57
			// 
			this->menuItem57->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem57.Enabled")));
			this->menuItem57->Index = 1;
			this->menuItem57->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem57.Shortcut")));
			this->menuItem57->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem57.ShowShortcut")));
			this->menuItem57->Text = resources->GetString(S"menuItem57.Text");
			this->menuItem57->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem57.Visible")));
			this->menuItem57->Click += new System::EventHandler(this, menuItem57_Click);
			// 
			// menuItem59
			// 
			this->menuItem59->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem59.Enabled")));
			this->menuItem59->Index = 2;
			this->menuItem59->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem59.Shortcut")));
			this->menuItem59->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem59.ShowShortcut")));
			this->menuItem59->Text = resources->GetString(S"menuItem59.Text");
			this->menuItem59->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem59.Visible")));
			this->menuItem59->Click += new System::EventHandler(this, menuItem59_Click);
			// 
			// menuItem46
			// 
			this->menuItem46->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem46.Enabled")));
			this->menuItem46->Index = 3;
			this->menuItem46->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem46.Shortcut")));
			this->menuItem46->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem46.ShowShortcut")));
			this->menuItem46->Text = resources->GetString(S"menuItem46.Text");
			this->menuItem46->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem46.Visible")));
			// 
			// menuItem47
			// 
			this->menuItem47->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem47.Enabled")));
			this->menuItem47->Index = 4;
			this->menuItem47->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem47.Shortcut")));
			this->menuItem47->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem47.ShowShortcut")));
			this->menuItem47->Text = resources->GetString(S"menuItem47.Text");
			this->menuItem47->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem47.Visible")));
			this->menuItem47->Click += new System::EventHandler(this, menuItem47_Click);
			// 
			// menuItem48
			// 
			this->menuItem48->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem48.Enabled")));
			this->menuItem48->Index = 5;
			this->menuItem48->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem48.Shortcut")));
			this->menuItem48->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem48.ShowShortcut")));
			this->menuItem48->Text = resources->GetString(S"menuItem48.Text");
			this->menuItem48->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem48.Visible")));
			// 
			// menuItem12
			// 
			this->menuItem12->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem12.Enabled")));
			this->menuItem12->Index = 2;
			System::Windows::Forms::MenuItem* __mcTemp__7[] = new System::Windows::Forms::MenuItem*[6];
			__mcTemp__7[0] = this->menuItem23;
			__mcTemp__7[1] = this->menuItem25;
			__mcTemp__7[2] = this->mISources;
			__mcTemp__7[3] = this->mIFilters;
			__mcTemp__7[4] = this->mIOutputs;
			__mcTemp__7[5] = this->mIBuffers;
			this->menuItem12->MenuItems->AddRange(__mcTemp__7);
			this->menuItem12->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem12.Shortcut")));
			this->menuItem12->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem12.ShowShortcut")));
			this->menuItem12->Text = resources->GetString(S"menuItem12.Text");
			this->menuItem12->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem12.Visible")));
			// 
			// menuItem23
			// 
			this->menuItem23->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem23.Enabled")));
			this->menuItem23->Index = 0;
			this->menuItem23->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem23.Shortcut")));
			this->menuItem23->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem23.ShowShortcut")));
			this->menuItem23->Text = resources->GetString(S"menuItem23.Text");
			this->menuItem23->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem23.Visible")));
			this->menuItem23->Click += new System::EventHandler(this, menuItem23_Click);
			// 
			// menuItem25
			// 
			this->menuItem25->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem25.Enabled")));
			this->menuItem25->Index = 1;
			this->menuItem25->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem25.Shortcut")));
			this->menuItem25->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem25.ShowShortcut")));
			this->menuItem25->Text = resources->GetString(S"menuItem25.Text");
			this->menuItem25->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem25.Visible")));
			// 
			// mISources
			// 
			this->mISources->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"mISources.Enabled")));
			this->mISources->Index = 2;
			System::Windows::Forms::MenuItem* __mcTemp__8[] = new System::Windows::Forms::MenuItem*[6];
			__mcTemp__8[0] = this->menuItem30;
			__mcTemp__8[1] = this->menuItem85;
			__mcTemp__8[2] = this->menuItem65;
			__mcTemp__8[3] = this->menuItem38;
			__mcTemp__8[4] = this->menuItem39;
			__mcTemp__8[5] = this->menuItem41;
			this->mISources->MenuItems->AddRange(__mcTemp__8);
			this->mISources->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"mISources.Shortcut")));
			this->mISources->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"mISources.ShowShortcut")));
			this->mISources->Text = resources->GetString(S"mISources.Text");
			this->mISources->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"mISources.Visible")));
			// 
			// menuItem30
			// 
			this->menuItem30->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem30.Enabled")));
			this->menuItem30->Index = 0;
			this->menuItem30->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem30.Shortcut")));
			this->menuItem30->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem30.ShowShortcut")));
			this->menuItem30->Text = resources->GetString(S"menuItem30.Text");
			this->menuItem30->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem30.Visible")));
			this->menuItem30->Click += new System::EventHandler(this, menuItem28_Click);
			// 
			// menuItem85
			// 
			this->menuItem85->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem85.Enabled")));
			this->menuItem85->Index = 1;
			this->menuItem85->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem85.Shortcut")));
			this->menuItem85->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem85.ShowShortcut")));
			this->menuItem85->Text = resources->GetString(S"menuItem85.Text");
			this->menuItem85->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem85.Visible")));
			this->menuItem85->Click += new System::EventHandler(this, menuItem85_Click);
			// 
			// menuItem65
			// 
			this->menuItem65->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem65.Enabled")));
			this->menuItem65->Index = 2;
			this->menuItem65->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem65.Shortcut")));
			this->menuItem65->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem65.ShowShortcut")));
			this->menuItem65->Text = resources->GetString(S"menuItem65.Text");
			this->menuItem65->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem65.Visible")));
			this->menuItem65->Click += new System::EventHandler(this, menuItem65_Click);
			// 
			// menuItem38
			// 
			this->menuItem38->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem38.Enabled")));
			this->menuItem38->Index = 3;
			this->menuItem38->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem38.Shortcut")));
			this->menuItem38->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem38.ShowShortcut")));
			this->menuItem38->Text = resources->GetString(S"menuItem38.Text");
			this->menuItem38->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem38.Visible")));
			this->menuItem38->Click += new System::EventHandler(this, menuItem38_Click);
			// 
			// menuItem39
			// 
			this->menuItem39->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem39.Enabled")));
			this->menuItem39->Index = 4;
			this->menuItem39->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem39.Shortcut")));
			this->menuItem39->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem39.ShowShortcut")));
			this->menuItem39->Text = resources->GetString(S"menuItem39.Text");
			this->menuItem39->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem39.Visible")));
			// 
			// menuItem41
			// 
			this->menuItem41->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem41.Enabled")));
			this->menuItem41->Index = 5;
			this->menuItem41->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem41.Shortcut")));
			this->menuItem41->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem41.ShowShortcut")));
			this->menuItem41->Text = resources->GetString(S"menuItem41.Text");
			this->menuItem41->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem41.Visible")));
			// 
			// mIFilters
			// 
			this->mIFilters->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"mIFilters.Enabled")));
			this->mIFilters->Index = 3;
			System::Windows::Forms::MenuItem* __mcTemp__9[] = new System::Windows::Forms::MenuItem*[2];
			__mcTemp__9[0] = this->menuItem44;
			__mcTemp__9[1] = this->menuItem43;
			this->mIFilters->MenuItems->AddRange(__mcTemp__9);
			this->mIFilters->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"mIFilters.Shortcut")));
			this->mIFilters->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"mIFilters.ShowShortcut")));
			this->mIFilters->Text = resources->GetString(S"mIFilters.Text");
			this->mIFilters->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"mIFilters.Visible")));
			// 
			// menuItem44
			// 
			this->menuItem44->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem44.Enabled")));
			this->menuItem44->Index = 0;
			this->menuItem44->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem44.Shortcut")));
			this->menuItem44->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem44.ShowShortcut")));
			this->menuItem44->Text = resources->GetString(S"menuItem44.Text");
			this->menuItem44->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem44.Visible")));
			// 
			// menuItem43
			// 
			this->menuItem43->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem43.Enabled")));
			this->menuItem43->Index = 1;
			this->menuItem43->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem43.Shortcut")));
			this->menuItem43->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem43.ShowShortcut")));
			this->menuItem43->Text = resources->GetString(S"menuItem43.Text");
			this->menuItem43->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem43.Visible")));
			// 
			// mIOutputs
			// 
			this->mIOutputs->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"mIOutputs.Enabled")));
			this->mIOutputs->Index = 4;
			System::Windows::Forms::MenuItem* __mcTemp__10[] = new System::Windows::Forms::MenuItem*[4];
			__mcTemp__10[0] = this->menuItem40;
			__mcTemp__10[1] = this->menuItem26;
			__mcTemp__10[2] = this->menuItem67;
			__mcTemp__10[3] = this->menuItem42;
			this->mIOutputs->MenuItems->AddRange(__mcTemp__10);
			this->mIOutputs->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"mIOutputs.Shortcut")));
			this->mIOutputs->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"mIOutputs.ShowShortcut")));
			this->mIOutputs->Text = resources->GetString(S"mIOutputs.Text");
			this->mIOutputs->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"mIOutputs.Visible")));
			// 
			// menuItem40
			// 
			this->menuItem40->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem40.Enabled")));
			this->menuItem40->Index = 0;
			this->menuItem40->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem40.Shortcut")));
			this->menuItem40->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem40.ShowShortcut")));
			this->menuItem40->Text = resources->GetString(S"menuItem40.Text");
			this->menuItem40->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem40.Visible")));
			this->menuItem40->Click += new System::EventHandler(this, menuItem37_Click);
			// 
			// menuItem26
			// 
			this->menuItem26->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem26.Enabled")));
			this->menuItem26->Index = 1;
			this->menuItem26->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem26.Shortcut")));
			this->menuItem26->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem26.ShowShortcut")));
			this->menuItem26->Text = resources->GetString(S"menuItem26.Text");
			this->menuItem26->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem26.Visible")));
			this->menuItem26->Click += new System::EventHandler(this, menuItem26_Click);
			// 
			// menuItem67
			// 
			this->menuItem67->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem67.Enabled")));
			this->menuItem67->Index = 2;
			this->menuItem67->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem67.Shortcut")));
			this->menuItem67->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem67.ShowShortcut")));
			this->menuItem67->Text = resources->GetString(S"menuItem67.Text");
			this->menuItem67->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem67.Visible")));
			this->menuItem67->Click += new System::EventHandler(this, menuItem67_Click);
			// 
			// menuItem42
			// 
			this->menuItem42->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem42.Enabled")));
			this->menuItem42->Index = 3;
			this->menuItem42->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem42.Shortcut")));
			this->menuItem42->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem42.ShowShortcut")));
			this->menuItem42->Text = resources->GetString(S"menuItem42.Text");
			this->menuItem42->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem42.Visible")));
			// 
			// mIBuffers
			// 
			this->mIBuffers->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"mIBuffers.Enabled")));
			this->mIBuffers->Index = 5;
			System::Windows::Forms::MenuItem* __mcTemp__11[] = new System::Windows::Forms::MenuItem*[2];
			__mcTemp__11[0] = this->menuItem77;
			__mcTemp__11[1] = this->menuItem76;
			this->mIBuffers->MenuItems->AddRange(__mcTemp__11);
			this->mIBuffers->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"mIBuffers.Shortcut")));
			this->mIBuffers->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"mIBuffers.ShowShortcut")));
			this->mIBuffers->Text = resources->GetString(S"mIBuffers.Text");
			this->mIBuffers->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"mIBuffers.Visible")));
			// 
			// menuItem77
			// 
			this->menuItem77->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem77.Enabled")));
			this->menuItem77->Index = 0;
			this->menuItem77->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem77.Shortcut")));
			this->menuItem77->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem77.ShowShortcut")));
			this->menuItem77->Text = resources->GetString(S"menuItem77.Text");
			this->menuItem77->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem77.Visible")));
			// 
			// menuItem76
			// 
			this->menuItem76->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem76.Enabled")));
			this->menuItem76->Index = 1;
			this->menuItem76->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem76.Shortcut")));
			this->menuItem76->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem76.ShowShortcut")));
			this->menuItem76->Text = resources->GetString(S"menuItem76.Text");
			this->menuItem76->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem76.Visible")));
			// 
			// menuItem13
			// 
			this->menuItem13->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem13.Enabled")));
			this->menuItem13->Index = 3;
			System::Windows::Forms::MenuItem* __mcTemp__12[] = new System::Windows::Forms::MenuItem*[7];
			__mcTemp__12[0] = this->menuItem7;
			__mcTemp__12[1] = this->menuItem5;
			__mcTemp__12[2] = this->menuItem60;
			__mcTemp__12[3] = this->menuItem63;
			__mcTemp__12[4] = this->menuItem69;
			__mcTemp__12[5] = this->menuItem70;
			__mcTemp__12[6] = this->menuItem56;
			this->menuItem13->MenuItems->AddRange(__mcTemp__12);
			this->menuItem13->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem13.Shortcut")));
			this->menuItem13->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem13.ShowShortcut")));
			this->menuItem13->Text = resources->GetString(S"menuItem13.Text");
			this->menuItem13->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem13.Visible")));
			// 
			// menuItem7
			// 
			this->menuItem7->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem7.Enabled")));
			this->menuItem7->Index = 0;
			System::Windows::Forms::MenuItem* __mcTemp__13[] = new System::Windows::Forms::MenuItem*[2];
			__mcTemp__13[0] = this->menuItem37;
			__mcTemp__13[1] = this->menuItem24;
			this->menuItem7->MenuItems->AddRange(__mcTemp__13);
			this->menuItem7->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem7.Shortcut")));
			this->menuItem7->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem7.ShowShortcut")));
			this->menuItem7->Text = resources->GetString(S"menuItem7.Text");
			this->menuItem7->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem7.Visible")));
			// 
			// menuItem37
			// 
			this->menuItem37->Checked = true;
			this->menuItem37->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem37.Enabled")));
			this->menuItem37->Index = 0;
			this->menuItem37->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem37.Shortcut")));
			this->menuItem37->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem37.ShowShortcut")));
			this->menuItem37->Text = resources->GetString(S"menuItem37.Text");
			this->menuItem37->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem37.Visible")));
			this->menuItem37->Click += new System::EventHandler(this, menuItem37_Click_1);
			// 
			// menuItem24
			// 
			this->menuItem24->Checked = true;
			this->menuItem24->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem24.Enabled")));
			this->menuItem24->Index = 1;
			this->menuItem24->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem24.Shortcut")));
			this->menuItem24->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem24.ShowShortcut")));
			this->menuItem24->Text = resources->GetString(S"menuItem24.Text");
			this->menuItem24->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem24.Visible")));
			this->menuItem24->Click += new System::EventHandler(this, menuItem24_Click);
			// 
			// menuItem5
			// 
			this->menuItem5->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem5.Enabled")));
			this->menuItem5->Index = 1;
			this->menuItem5->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem5.Shortcut")));
			this->menuItem5->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem5.ShowShortcut")));
			this->menuItem5->Text = resources->GetString(S"menuItem5.Text");
			this->menuItem5->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem5.Visible")));
			// 
			// menuItem60
			// 
			this->menuItem60->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem60.Enabled")));
			this->menuItem60->Index = 2;
			System::Windows::Forms::MenuItem* __mcTemp__14[] = new System::Windows::Forms::MenuItem*[1];
			__mcTemp__14[0] = this->menuItem64;
			this->menuItem60->MenuItems->AddRange(__mcTemp__14);
			this->menuItem60->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem60.Shortcut")));
			this->menuItem60->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem60.ShowShortcut")));
			this->menuItem60->Text = resources->GetString(S"menuItem60.Text");
			this->menuItem60->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem60.Visible")));
			// 
			// menuItem64
			// 
			this->menuItem64->Checked = true;
			this->menuItem64->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem64.Enabled")));
			this->menuItem64->Index = 0;
			this->menuItem64->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem64.Shortcut")));
			this->menuItem64->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem64.ShowShortcut")));
			this->menuItem64->Text = resources->GetString(S"menuItem64.Text");
			this->menuItem64->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem64.Visible")));
			// 
			// menuItem63
			// 
			this->menuItem63->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem63.Enabled")));
			this->menuItem63->Index = 3;
			this->menuItem63->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem63.Shortcut")));
			this->menuItem63->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem63.ShowShortcut")));
			this->menuItem63->Text = resources->GetString(S"menuItem63.Text");
			this->menuItem63->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem63.Visible")));
			// 
			// menuItem69
			// 
			this->menuItem69->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem69.Enabled")));
			this->menuItem69->Index = 4;
			System::Windows::Forms::MenuItem* __mcTemp__15[] = new System::Windows::Forms::MenuItem*[5];
			__mcTemp__15[0] = this->menuItem71;
			__mcTemp__15[1] = this->menuItem75;
			__mcTemp__15[2] = this->menuItem74;
			__mcTemp__15[3] = this->menuItem73;
			__mcTemp__15[4] = this->menuItem72;
			this->menuItem69->MenuItems->AddRange(__mcTemp__15);
			this->menuItem69->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem69.Shortcut")));
			this->menuItem69->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem69.ShowShortcut")));
			this->menuItem69->Text = resources->GetString(S"menuItem69.Text");
			this->menuItem69->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem69.Visible")));
			// 
			// menuItem71
			// 
			this->menuItem71->Checked = true;
			this->menuItem71->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem71.Enabled")));
			this->menuItem71->Index = 0;
			this->menuItem71->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem71.Shortcut")));
			this->menuItem71->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem71.ShowShortcut")));
			this->menuItem71->Text = resources->GetString(S"menuItem71.Text");
			this->menuItem71->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem71.Visible")));
			this->menuItem71->Click += new System::EventHandler(this, menuItem71_Click);
			// 
			// menuItem75
			// 
			this->menuItem75->Checked = true;
			this->menuItem75->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem75.Enabled")));
			this->menuItem75->Index = 1;
			this->menuItem75->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem75.Shortcut")));
			this->menuItem75->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem75.ShowShortcut")));
			this->menuItem75->Text = resources->GetString(S"menuItem75.Text");
			this->menuItem75->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem75.Visible")));
			this->menuItem75->Click += new System::EventHandler(this, menuItem75_Click);
			// 
			// menuItem74
			// 
			this->menuItem74->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem74.Enabled")));
			this->menuItem74->Index = 2;
			this->menuItem74->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem74.Shortcut")));
			this->menuItem74->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem74.ShowShortcut")));
			this->menuItem74->Text = resources->GetString(S"menuItem74.Text");
			this->menuItem74->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem74.Visible")));
			// 
			// menuItem73
			// 
			this->menuItem73->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem73.Enabled")));
			this->menuItem73->Index = 3;
			this->menuItem73->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem73.Shortcut")));
			this->menuItem73->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem73.ShowShortcut")));
			this->menuItem73->Text = resources->GetString(S"menuItem73.Text");
			this->menuItem73->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem73.Visible")));
			this->menuItem73->Click += new System::EventHandler(this, menuItem73_Click);
			// 
			// menuItem72
			// 
			this->menuItem72->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem72.Enabled")));
			this->menuItem72->Index = 4;
			this->menuItem72->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem72.Shortcut")));
			this->menuItem72->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem72.ShowShortcut")));
			this->menuItem72->Text = resources->GetString(S"menuItem72.Text");
			this->menuItem72->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem72.Visible")));
			this->menuItem72->Click += new System::EventHandler(this, menuItem72_Click);
			// 
			// menuItem70
			// 
			this->menuItem70->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem70.Enabled")));
			this->menuItem70->Index = 5;
			this->menuItem70->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem70.Shortcut")));
			this->menuItem70->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem70.ShowShortcut")));
			this->menuItem70->Text = resources->GetString(S"menuItem70.Text");
			this->menuItem70->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem70.Visible")));
			// 
			// menuItem56
			// 
			this->menuItem56->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem56.Enabled")));
			this->menuItem56->Index = 6;
			this->menuItem56->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem56.Shortcut")));
			this->menuItem56->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem56.ShowShortcut")));
			this->menuItem56->Text = resources->GetString(S"menuItem56.Text");
			this->menuItem56->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem56.Visible")));
			this->menuItem56->Click += new System::EventHandler(this, menuItem56_Click);
			// 
			// menuItem27
			// 
			this->menuItem27->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem27.Enabled")));
			this->menuItem27->Index = 4;
			this->menuItem27->MdiList = true;
			System::Windows::Forms::MenuItem* __mcTemp__16[] = new System::Windows::Forms::MenuItem*[9];
			__mcTemp__16[0] = this->menuItem61;
			__mcTemp__16[1] = this->menuItem31;
			__mcTemp__16[2] = this->menuItem32;
			__mcTemp__16[3] = this->menuItem80;
			__mcTemp__16[4] = this->menuItem79;
			__mcTemp__16[5] = this->menuItem52;
			__mcTemp__16[6] = this->menuItem51;
			__mcTemp__16[7] = this->menuItem50;
			__mcTemp__16[8] = this->menuItem78;
			this->menuItem27->MenuItems->AddRange(__mcTemp__16);
			this->menuItem27->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem27.Shortcut")));
			this->menuItem27->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem27.ShowShortcut")));
			this->menuItem27->Text = resources->GetString(S"menuItem27.Text");
			this->menuItem27->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem27.Visible")));
			// 
			// menuItem61
			// 
			this->menuItem61->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem61.Enabled")));
			this->menuItem61->Index = 0;
			System::Windows::Forms::MenuItem* __mcTemp__17[] = new System::Windows::Forms::MenuItem*[3];
			__mcTemp__17[0] = this->menuItem62;
			__mcTemp__17[1] = this->menuItem49;
			__mcTemp__17[2] = this->menuItem68;
			this->menuItem61->MenuItems->AddRange(__mcTemp__17);
			this->menuItem61->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem61.Shortcut")));
			this->menuItem61->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem61.ShowShortcut")));
			this->menuItem61->Text = resources->GetString(S"menuItem61.Text");
			this->menuItem61->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem61.Visible")));
			// 
			// menuItem62
			// 
			this->menuItem62->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem62.Enabled")));
			this->menuItem62->Index = 0;
			this->menuItem62->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem62.Shortcut")));
			this->menuItem62->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem62.ShowShortcut")));
			this->menuItem62->Text = resources->GetString(S"menuItem62.Text");
			this->menuItem62->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem62.Visible")));
			this->menuItem62->Click += new System::EventHandler(this, menuItem62_Click);
			// 
			// menuItem49
			// 
			this->menuItem49->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem49.Enabled")));
			this->menuItem49->Index = 1;
			this->menuItem49->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem49.Shortcut")));
			this->menuItem49->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem49.ShowShortcut")));
			this->menuItem49->Text = resources->GetString(S"menuItem49.Text");
			this->menuItem49->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem49.Visible")));
			this->menuItem49->Click += new System::EventHandler(this, menuItem49_Click);
			// 
			// menuItem68
			// 
			this->menuItem68->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem68.Enabled")));
			this->menuItem68->Index = 2;
			this->menuItem68->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem68.Shortcut")));
			this->menuItem68->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem68.ShowShortcut")));
			this->menuItem68->Text = resources->GetString(S"menuItem68.Text");
			this->menuItem68->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem68.Visible")));
			this->menuItem68->Click += new System::EventHandler(this, menuItem68_Click);
			// 
			// menuItem31
			// 
			this->menuItem31->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem31.Enabled")));
			this->menuItem31->Index = 1;
			this->menuItem31->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem31.Shortcut")));
			this->menuItem31->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem31.ShowShortcut")));
			this->menuItem31->Text = resources->GetString(S"menuItem31.Text");
			this->menuItem31->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem31.Visible")));
			// 
			// menuItem32
			// 
			this->menuItem32->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem32.Enabled")));
			this->menuItem32->Index = 2;
			System::Windows::Forms::MenuItem* __mcTemp__18[] = new System::Windows::Forms::MenuItem*[4];
			__mcTemp__18[0] = this->menuItem34;
			__mcTemp__18[1] = this->menuItem33;
			__mcTemp__18[2] = this->menuItem36;
			__mcTemp__18[3] = this->menuItem35;
			this->menuItem32->MenuItems->AddRange(__mcTemp__18);
			this->menuItem32->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem32.Shortcut")));
			this->menuItem32->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem32.ShowShortcut")));
			this->menuItem32->Text = resources->GetString(S"menuItem32.Text");
			this->menuItem32->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem32.Visible")));
			// 
			// menuItem34
			// 
			this->menuItem34->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem34.Enabled")));
			this->menuItem34->Index = 0;
			this->menuItem34->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem34.Shortcut")));
			this->menuItem34->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem34.ShowShortcut")));
			this->menuItem34->Text = resources->GetString(S"menuItem34.Text");
			this->menuItem34->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem34.Visible")));
			this->menuItem34->Click += new System::EventHandler(this, menuItem34_Click);
			// 
			// menuItem33
			// 
			this->menuItem33->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem33.Enabled")));
			this->menuItem33->Index = 1;
			this->menuItem33->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem33.Shortcut")));
			this->menuItem33->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem33.ShowShortcut")));
			this->menuItem33->Text = resources->GetString(S"menuItem33.Text");
			this->menuItem33->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem33.Visible")));
			this->menuItem33->Click += new System::EventHandler(this, menuItem33_Click);
			// 
			// menuItem36
			// 
			this->menuItem36->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem36.Enabled")));
			this->menuItem36->Index = 2;
			this->menuItem36->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem36.Shortcut")));
			this->menuItem36->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem36.ShowShortcut")));
			this->menuItem36->Text = resources->GetString(S"menuItem36.Text");
			this->menuItem36->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem36.Visible")));
			this->menuItem36->Click += new System::EventHandler(this, menuItem36_Click);
			// 
			// menuItem35
			// 
			this->menuItem35->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem35.Enabled")));
			this->menuItem35->Index = 3;
			this->menuItem35->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem35.Shortcut")));
			this->menuItem35->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem35.ShowShortcut")));
			this->menuItem35->Text = resources->GetString(S"menuItem35.Text");
			this->menuItem35->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem35.Visible")));
			this->menuItem35->Click += new System::EventHandler(this, menuItem35_Click);
			// 
			// menuItem80
			// 
			this->menuItem80->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem80.Enabled")));
			this->menuItem80->Index = 3;
			this->menuItem80->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem80.Shortcut")));
			this->menuItem80->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem80.ShowShortcut")));
			this->menuItem80->Text = resources->GetString(S"menuItem80.Text");
			this->menuItem80->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem80.Visible")));
			// 
			// menuItem79
			// 
			this->menuItem79->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem79.Enabled")));
			this->menuItem79->Index = 4;
			System::Windows::Forms::MenuItem* __mcTemp__19[] = new System::Windows::Forms::MenuItem*[2];
			__mcTemp__19[0] = this->menuItem81;
			__mcTemp__19[1] = this->menuItem82;
			this->menuItem79->MenuItems->AddRange(__mcTemp__19);
			this->menuItem79->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem79.Shortcut")));
			this->menuItem79->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem79.ShowShortcut")));
			this->menuItem79->Text = resources->GetString(S"menuItem79.Text");
			this->menuItem79->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem79.Visible")));
			// 
			// menuItem81
			// 
			this->menuItem81->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem81.Enabled")));
			this->menuItem81->Index = 0;
			this->menuItem81->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem81.Shortcut")));
			this->menuItem81->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem81.ShowShortcut")));
			this->menuItem81->Text = resources->GetString(S"menuItem81.Text");
			this->menuItem81->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem81.Visible")));
			this->menuItem81->Click += new System::EventHandler(this, menuItem81_Click);
			// 
			// menuItem82
			// 
			this->menuItem82->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem82.Enabled")));
			this->menuItem82->Index = 1;
			this->menuItem82->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem82.Shortcut")));
			this->menuItem82->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem82.ShowShortcut")));
			this->menuItem82->Text = resources->GetString(S"menuItem82.Text");
			this->menuItem82->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem82.Visible")));
			this->menuItem82->Click += new System::EventHandler(this, menuItem82_Click);
			// 
			// menuItem52
			// 
			this->menuItem52->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem52.Enabled")));
			this->menuItem52->Index = 5;
			this->menuItem52->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem52.Shortcut")));
			this->menuItem52->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem52.ShowShortcut")));
			this->menuItem52->Text = resources->GetString(S"menuItem52.Text");
			this->menuItem52->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem52.Visible")));
			// 
			// menuItem51
			// 
			this->menuItem51->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem51.Enabled")));
			this->menuItem51->Index = 6;
			System::Windows::Forms::MenuItem* __mcTemp__20[] = new System::Windows::Forms::MenuItem*[3];
			__mcTemp__20[0] = this->menuItem53;
			__mcTemp__20[1] = this->menuItem54;
			__mcTemp__20[2] = this->menuItem55;
			this->menuItem51->MenuItems->AddRange(__mcTemp__20);
			this->menuItem51->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem51.Shortcut")));
			this->menuItem51->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem51.ShowShortcut")));
			this->menuItem51->Text = resources->GetString(S"menuItem51.Text");
			this->menuItem51->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem51.Visible")));
			// 
			// menuItem53
			// 
			this->menuItem53->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem53.Enabled")));
			this->menuItem53->Index = 0;
			this->menuItem53->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem53.Shortcut")));
			this->menuItem53->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem53.ShowShortcut")));
			this->menuItem53->Text = resources->GetString(S"menuItem53.Text");
			this->menuItem53->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem53.Visible")));
			this->menuItem53->Click += new System::EventHandler(this, menuItem53_Click);
			// 
			// menuItem54
			// 
			this->menuItem54->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem54.Enabled")));
			this->menuItem54->Index = 1;
			this->menuItem54->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem54.Shortcut")));
			this->menuItem54->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem54.ShowShortcut")));
			this->menuItem54->Text = resources->GetString(S"menuItem54.Text");
			this->menuItem54->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem54.Visible")));
			this->menuItem54->Click += new System::EventHandler(this, menuItem54_Click);
			// 
			// menuItem55
			// 
			this->menuItem55->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem55.Enabled")));
			this->menuItem55->Index = 2;
			this->menuItem55->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem55.Shortcut")));
			this->menuItem55->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem55.ShowShortcut")));
			this->menuItem55->Text = resources->GetString(S"menuItem55.Text");
			this->menuItem55->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem55.Visible")));
			// 
			// menuItem50
			// 
			this->menuItem50->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem50.Enabled")));
			this->menuItem50->Index = 7;
			this->menuItem50->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem50.Shortcut")));
			this->menuItem50->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem50.ShowShortcut")));
			this->menuItem50->Text = resources->GetString(S"menuItem50.Text");
			this->menuItem50->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem50.Visible")));
			// 
			// menuItem78
			// 
			this->menuItem78->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem78.Enabled")));
			this->menuItem78->Index = 8;
			this->menuItem78->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem78.Shortcut")));
			this->menuItem78->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem78.ShowShortcut")));
			this->menuItem78->Text = resources->GetString(S"menuItem78.Text");
			this->menuItem78->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem78.Visible")));
			// 
			// menuItem14
			// 
			this->menuItem14->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem14.Enabled")));
			this->menuItem14->Index = 5;
			System::Windows::Forms::MenuItem* __mcTemp__21[] = new System::Windows::Forms::MenuItem*[7];
			__mcTemp__21[0] = this->menuItem21;
			__mcTemp__21[1] = this->menuItem15;
			__mcTemp__21[2] = this->menuItem20;
			__mcTemp__21[3] = this->menuItem19;
			__mcTemp__21[4] = this->menuItem18;
			__mcTemp__21[5] = this->menuItem16;
			__mcTemp__21[6] = this->menuItem17;
			this->menuItem14->MenuItems->AddRange(__mcTemp__21);
			this->menuItem14->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem14.Shortcut")));
			this->menuItem14->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem14.ShowShortcut")));
			this->menuItem14->Text = resources->GetString(S"menuItem14.Text");
			this->menuItem14->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem14.Visible")));
			// 
			// menuItem21
			// 
			this->menuItem21->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem21.Enabled")));
			this->menuItem21->Index = 0;
			this->menuItem21->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem21.Shortcut")));
			this->menuItem21->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem21.ShowShortcut")));
			this->menuItem21->Text = resources->GetString(S"menuItem21.Text");
			this->menuItem21->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem21.Visible")));
			this->menuItem21->Click += new System::EventHandler(this, menuItem21_Click);
			// 
			// menuItem15
			// 
			this->menuItem15->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem15.Enabled")));
			this->menuItem15->Index = 1;
			this->menuItem15->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem15.Shortcut")));
			this->menuItem15->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem15.ShowShortcut")));
			this->menuItem15->Text = resources->GetString(S"menuItem15.Text");
			this->menuItem15->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem15.Visible")));
			// 
			// menuItem20
			// 
			this->menuItem20->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem20.Enabled")));
			this->menuItem20->Index = 2;
			this->menuItem20->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem20.Shortcut")));
			this->menuItem20->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem20.ShowShortcut")));
			this->menuItem20->Text = resources->GetString(S"menuItem20.Text");
			this->menuItem20->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem20.Visible")));
			this->menuItem20->Click += new System::EventHandler(this, menuItem20_Click);
			// 
			// menuItem19
			// 
			this->menuItem19->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem19.Enabled")));
			this->menuItem19->Index = 3;
			this->menuItem19->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem19.Shortcut")));
			this->menuItem19->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem19.ShowShortcut")));
			this->menuItem19->Text = resources->GetString(S"menuItem19.Text");
			this->menuItem19->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem19.Visible")));
			this->menuItem19->Click += new System::EventHandler(this, menuItem19_Click);
			// 
			// menuItem18
			// 
			this->menuItem18->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem18.Enabled")));
			this->menuItem18->Index = 4;
			this->menuItem18->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem18.Shortcut")));
			this->menuItem18->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem18.ShowShortcut")));
			this->menuItem18->Text = resources->GetString(S"menuItem18.Text");
			this->menuItem18->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem18.Visible")));
			// 
			// menuItem16
			// 
			this->menuItem16->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem16.Enabled")));
			this->menuItem16->Index = 5;
			this->menuItem16->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem16.Shortcut")));
			this->menuItem16->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem16.ShowShortcut")));
			this->menuItem16->Text = resources->GetString(S"menuItem16.Text");
			this->menuItem16->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem16.Visible")));
			this->menuItem16->Click += new System::EventHandler(this, menuItem16_Click);
			// 
			// menuItem17
			// 
			this->menuItem17->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem17.Enabled")));
			this->menuItem17->Index = 6;
			this->menuItem17->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem17.Shortcut")));
			this->menuItem17->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem17.ShowShortcut")));
			this->menuItem17->Text = resources->GetString(S"menuItem17.Text");
			this->menuItem17->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem17.Visible")));
			this->menuItem17->Click += new System::EventHandler(this, menuItem17_Click);
			// 
			// statusBar1
			// 
			this->statusBar1->AccessibleDescription = resources->GetString(S"statusBar1.AccessibleDescription");
			this->statusBar1->AccessibleName = resources->GetString(S"statusBar1.AccessibleName");
			this->statusBar1->Anchor = (*__try_cast<__box System::Windows::Forms::AnchorStyles *  >(resources->GetObject(S"statusBar1.Anchor")));
			this->statusBar1->BackgroundImage = (__try_cast<System::Drawing::Image *  >(resources->GetObject(S"statusBar1.BackgroundImage")));
			this->statusBar1->Dock = (*__try_cast<__box System::Windows::Forms::DockStyle *  >(resources->GetObject(S"statusBar1.Dock")));
			this->statusBar1->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"statusBar1.Enabled")));
			this->statusBar1->Font = (__try_cast<System::Drawing::Font *  >(resources->GetObject(S"statusBar1.Font")));
			this->statusBar1->ImeMode = (*__try_cast<__box System::Windows::Forms::ImeMode *  >(resources->GetObject(S"statusBar1.ImeMode")));
			this->statusBar1->Location = (*__try_cast<__box System::Drawing::Point *  >(resources->GetObject(S"statusBar1.Location")));
			this->statusBar1->Name = S"statusBar1";
			System::Windows::Forms::StatusBarPanel* __mcTemp__22[] = new System::Windows::Forms::StatusBarPanel*[3];
			__mcTemp__22[0] = this->statusBarPanel1;
			__mcTemp__22[1] = this->statusBarPanel2;
			__mcTemp__22[2] = this->statusBarPanel3;
			this->statusBar1->Panels->AddRange(__mcTemp__22);
			this->statusBar1->RightToLeft = (*__try_cast<__box System::Windows::Forms::RightToLeft *  >(resources->GetObject(S"statusBar1.RightToLeft")));
			this->statusBar1->Size = (*__try_cast<__box System::Drawing::Size *  >(resources->GetObject(S"statusBar1.Size")));
			this->statusBar1->TabIndex = (*__try_cast<__box System::Int32 *  >(resources->GetObject(S"statusBar1.TabIndex")));
			this->statusBar1->Text = resources->GetString(S"statusBar1.Text");
			this->statusBar1->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"statusBar1.Visible")));
			// 
			// statusBarPanel1
			// 
			this->statusBarPanel1->Alignment = (*__try_cast<__box System::Windows::Forms::HorizontalAlignment *  >(resources->GetObject(S"statusBarPanel1.Alignment")));
			this->statusBarPanel1->Icon = (__try_cast<System::Drawing::Icon *  >(resources->GetObject(S"statusBarPanel1.Icon")));
			this->statusBarPanel1->MinWidth = (*__try_cast<__box System::Int32 *  >(resources->GetObject(S"statusBarPanel1.MinWidth")));
			this->statusBarPanel1->Text = resources->GetString(S"statusBarPanel1.Text");
			this->statusBarPanel1->ToolTipText = resources->GetString(S"statusBarPanel1.ToolTipText");
			this->statusBarPanel1->Width = (*__try_cast<__box System::Int32 *  >(resources->GetObject(S"statusBarPanel1.Width")));
			// 
			// statusBarPanel2
			// 
			this->statusBarPanel2->Alignment = (*__try_cast<__box System::Windows::Forms::HorizontalAlignment *  >(resources->GetObject(S"statusBarPanel2.Alignment")));
			this->statusBarPanel2->AutoSize = System::Windows::Forms::StatusBarPanelAutoSize::Spring;
			this->statusBarPanel2->Icon = (__try_cast<System::Drawing::Icon *  >(resources->GetObject(S"statusBarPanel2.Icon")));
			this->statusBarPanel2->MinWidth = (*__try_cast<__box System::Int32 *  >(resources->GetObject(S"statusBarPanel2.MinWidth")));
			this->statusBarPanel2->Text = resources->GetString(S"statusBarPanel2.Text");
			this->statusBarPanel2->ToolTipText = resources->GetString(S"statusBarPanel2.ToolTipText");
			this->statusBarPanel2->Width = (*__try_cast<__box System::Int32 *  >(resources->GetObject(S"statusBarPanel2.Width")));
			// 
			// statusBarPanel3
			// 
			this->statusBarPanel3->Alignment = (*__try_cast<__box System::Windows::Forms::HorizontalAlignment *  >(resources->GetObject(S"statusBarPanel3.Alignment")));
			this->statusBarPanel3->Icon = (__try_cast<System::Drawing::Icon *  >(resources->GetObject(S"statusBarPanel3.Icon")));
			this->statusBarPanel3->MinWidth = (*__try_cast<__box System::Int32 *  >(resources->GetObject(S"statusBarPanel3.MinWidth")));
			this->statusBarPanel3->Text = resources->GetString(S"statusBarPanel3.Text");
			this->statusBarPanel3->ToolTipText = resources->GetString(S"statusBarPanel3.ToolTipText");
			this->statusBarPanel3->Width = (*__try_cast<__box System::Int32 *  >(resources->GetObject(S"statusBarPanel3.Width")));
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->DefaultExt = S"JPG";
			this->openFileDialog1->Filter = resources->GetString(S"openFileDialog1.Filter");
			this->openFileDialog1->InitialDirectory = S".\\";
			this->openFileDialog1->Title = resources->GetString(S"openFileDialog1.Title");
			// 
			// saveFileDialog1
			// 
			this->saveFileDialog1->Filter = resources->GetString(S"saveFileDialog1.Filter");
			this->saveFileDialog1->Title = resources->GetString(S"saveFileDialog1.Title");
			// 
			// toolBar1
			// 
			this->toolBar1->AccessibleDescription = resources->GetString(S"toolBar1.AccessibleDescription");
			this->toolBar1->AccessibleName = resources->GetString(S"toolBar1.AccessibleName");
			this->toolBar1->Anchor = (*__try_cast<__box System::Windows::Forms::AnchorStyles *  >(resources->GetObject(S"toolBar1.Anchor")));
			this->toolBar1->Appearance = (*__try_cast<__box System::Windows::Forms::ToolBarAppearance *  >(resources->GetObject(S"toolBar1.Appearance")));
			this->toolBar1->AutoSize = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"toolBar1.AutoSize")));
			this->toolBar1->BackgroundImage = (__try_cast<System::Drawing::Image *  >(resources->GetObject(S"toolBar1.BackgroundImage")));
			System::Windows::Forms::ToolBarButton* __mcTemp__23[] = new System::Windows::Forms::ToolBarButton*[16];
			__mcTemp__23[0] = this->tBb_openImage;
			__mcTemp__23[1] = this->tBb_openVideo;
			__mcTemp__23[2] = this->tBb_openDX;
			__mcTemp__23[3] = this->toolBarSeparator1;
			__mcTemp__23[4] = this->tBb_newView;
			__mcTemp__23[5] = this->toolBarSeparator4;
			__mcTemp__23[6] = this->tBb_viewRes;
			__mcTemp__23[7] = this->toolBarSeparator2;
			__mcTemp__23[8] = this->toolBarButton1;
			__mcTemp__23[9] = this->toolBarSeparator5;
			__mcTemp__23[10] = this->tBb_newDoctor;
			__mcTemp__23[11] = this->toolBarSeparator3;
			__mcTemp__23[12] = this->tBb_newNotepad;
			__mcTemp__23[13] = this->tBb_viewGraph;
			__mcTemp__23[14] = this->tBb_viewStats;
			__mcTemp__23[15] = this->tBb_viewLog;
			this->toolBar1->Buttons->AddRange(__mcTemp__23);
			this->toolBar1->ButtonSize = (*__try_cast<__box System::Drawing::Size *  >(resources->GetObject(S"toolBar1.ButtonSize")));
			this->toolBar1->Dock = (*__try_cast<__box System::Windows::Forms::DockStyle *  >(resources->GetObject(S"toolBar1.Dock")));
			this->toolBar1->DropDownArrows = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"toolBar1.DropDownArrows")));
			this->toolBar1->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"toolBar1.Enabled")));
			this->toolBar1->Font = (__try_cast<System::Drawing::Font *  >(resources->GetObject(S"toolBar1.Font")));
			this->toolBar1->ImageList = this->imageList1;
			this->toolBar1->ImeMode = (*__try_cast<__box System::Windows::Forms::ImeMode *  >(resources->GetObject(S"toolBar1.ImeMode")));
			this->toolBar1->Location = (*__try_cast<__box System::Drawing::Point *  >(resources->GetObject(S"toolBar1.Location")));
			this->toolBar1->Name = S"toolBar1";
			this->toolBar1->RightToLeft = (*__try_cast<__box System::Windows::Forms::RightToLeft *  >(resources->GetObject(S"toolBar1.RightToLeft")));
			this->toolBar1->ShowToolTips = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"toolBar1.ShowToolTips")));
			this->toolBar1->Size = (*__try_cast<__box System::Drawing::Size *  >(resources->GetObject(S"toolBar1.Size")));
			this->toolBar1->TabIndex = (*__try_cast<__box System::Int32 *  >(resources->GetObject(S"toolBar1.TabIndex")));
			this->toolBar1->TextAlign = (*__try_cast<__box System::Windows::Forms::ToolBarTextAlign *  >(resources->GetObject(S"toolBar1.TextAlign")));
			this->toolBar1->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"toolBar1.Visible")));
			this->toolBar1->Wrappable = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"toolBar1.Wrappable")));
			this->toolBar1->ButtonClick += new System::Windows::Forms::ToolBarButtonClickEventHandler(this, toolBar1_ButtonClick);
			// 
			// tBb_openImage
			// 
			this->tBb_openImage->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"tBb_openImage.Enabled")));
			this->tBb_openImage->ImageIndex = (*__try_cast<__box System::Int32 *  >(resources->GetObject(S"tBb_openImage.ImageIndex")));
			this->tBb_openImage->Text = resources->GetString(S"tBb_openImage.Text");
			this->tBb_openImage->ToolTipText = resources->GetString(S"tBb_openImage.ToolTipText");
			this->tBb_openImage->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"tBb_openImage.Visible")));
			// 
			// tBb_openVideo
			// 
			this->tBb_openVideo->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"tBb_openVideo.Enabled")));
			this->tBb_openVideo->ImageIndex = (*__try_cast<__box System::Int32 *  >(resources->GetObject(S"tBb_openVideo.ImageIndex")));
			this->tBb_openVideo->Text = resources->GetString(S"tBb_openVideo.Text");
			this->tBb_openVideo->ToolTipText = resources->GetString(S"tBb_openVideo.ToolTipText");
			this->tBb_openVideo->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"tBb_openVideo.Visible")));
			// 
			// tBb_openDX
			// 
			this->tBb_openDX->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"tBb_openDX.Enabled")));
			this->tBb_openDX->ImageIndex = (*__try_cast<__box System::Int32 *  >(resources->GetObject(S"tBb_openDX.ImageIndex")));
			this->tBb_openDX->Text = resources->GetString(S"tBb_openDX.Text");
			this->tBb_openDX->ToolTipText = resources->GetString(S"tBb_openDX.ToolTipText");
			this->tBb_openDX->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"tBb_openDX.Visible")));
			// 
			// toolBarSeparator1
			// 
			this->toolBarSeparator1->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"toolBarSeparator1.Enabled")));
			this->toolBarSeparator1->ImageIndex = (*__try_cast<__box System::Int32 *  >(resources->GetObject(S"toolBarSeparator1.ImageIndex")));
			this->toolBarSeparator1->Style = System::Windows::Forms::ToolBarButtonStyle::Separator;
			this->toolBarSeparator1->Text = resources->GetString(S"toolBarSeparator1.Text");
			this->toolBarSeparator1->ToolTipText = resources->GetString(S"toolBarSeparator1.ToolTipText");
			this->toolBarSeparator1->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"toolBarSeparator1.Visible")));
			// 
			// tBb_newView
			// 
			this->tBb_newView->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"tBb_newView.Enabled")));
			this->tBb_newView->ImageIndex = (*__try_cast<__box System::Int32 *  >(resources->GetObject(S"tBb_newView.ImageIndex")));
			this->tBb_newView->Text = resources->GetString(S"tBb_newView.Text");
			this->tBb_newView->ToolTipText = resources->GetString(S"tBb_newView.ToolTipText");
			this->tBb_newView->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"tBb_newView.Visible")));
			// 
			// toolBarSeparator4
			// 
			this->toolBarSeparator4->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"toolBarSeparator4.Enabled")));
			this->toolBarSeparator4->ImageIndex = (*__try_cast<__box System::Int32 *  >(resources->GetObject(S"toolBarSeparator4.ImageIndex")));
			this->toolBarSeparator4->Style = System::Windows::Forms::ToolBarButtonStyle::Separator;
			this->toolBarSeparator4->Text = resources->GetString(S"toolBarSeparator4.Text");
			this->toolBarSeparator4->ToolTipText = resources->GetString(S"toolBarSeparator4.ToolTipText");
			this->toolBarSeparator4->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"toolBarSeparator4.Visible")));
			// 
			// tBb_viewRes
			// 
			this->tBb_viewRes->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"tBb_viewRes.Enabled")));
			this->tBb_viewRes->ImageIndex = (*__try_cast<__box System::Int32 *  >(resources->GetObject(S"tBb_viewRes.ImageIndex")));
			this->tBb_viewRes->Text = resources->GetString(S"tBb_viewRes.Text");
			this->tBb_viewRes->ToolTipText = resources->GetString(S"tBb_viewRes.ToolTipText");
			this->tBb_viewRes->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"tBb_viewRes.Visible")));
			// 
			// toolBarSeparator2
			// 
			this->toolBarSeparator2->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"toolBarSeparator2.Enabled")));
			this->toolBarSeparator2->ImageIndex = (*__try_cast<__box System::Int32 *  >(resources->GetObject(S"toolBarSeparator2.ImageIndex")));
			this->toolBarSeparator2->Style = System::Windows::Forms::ToolBarButtonStyle::Separator;
			this->toolBarSeparator2->Text = resources->GetString(S"toolBarSeparator2.Text");
			this->toolBarSeparator2->ToolTipText = resources->GetString(S"toolBarSeparator2.ToolTipText");
			this->toolBarSeparator2->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"toolBarSeparator2.Visible")));
			// 
			// toolBarButton1
			// 
			this->toolBarButton1->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"toolBarButton1.Enabled")));
			this->toolBarButton1->ImageIndex = (*__try_cast<__box System::Int32 *  >(resources->GetObject(S"toolBarButton1.ImageIndex")));
			this->toolBarButton1->Text = resources->GetString(S"toolBarButton1.Text");
			this->toolBarButton1->ToolTipText = resources->GetString(S"toolBarButton1.ToolTipText");
			this->toolBarButton1->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"toolBarButton1.Visible")));
			// 
			// toolBarSeparator5
			// 
			this->toolBarSeparator5->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"toolBarSeparator5.Enabled")));
			this->toolBarSeparator5->ImageIndex = (*__try_cast<__box System::Int32 *  >(resources->GetObject(S"toolBarSeparator5.ImageIndex")));
			this->toolBarSeparator5->Style = System::Windows::Forms::ToolBarButtonStyle::Separator;
			this->toolBarSeparator5->Text = resources->GetString(S"toolBarSeparator5.Text");
			this->toolBarSeparator5->ToolTipText = resources->GetString(S"toolBarSeparator5.ToolTipText");
			this->toolBarSeparator5->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"toolBarSeparator5.Visible")));
			// 
			// tBb_newDoctor
			// 
			this->tBb_newDoctor->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"tBb_newDoctor.Enabled")));
			this->tBb_newDoctor->ImageIndex = (*__try_cast<__box System::Int32 *  >(resources->GetObject(S"tBb_newDoctor.ImageIndex")));
			this->tBb_newDoctor->Text = resources->GetString(S"tBb_newDoctor.Text");
			this->tBb_newDoctor->ToolTipText = resources->GetString(S"tBb_newDoctor.ToolTipText");
			this->tBb_newDoctor->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"tBb_newDoctor.Visible")));
			// 
			// toolBarSeparator3
			// 
			this->toolBarSeparator3->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"toolBarSeparator3.Enabled")));
			this->toolBarSeparator3->ImageIndex = (*__try_cast<__box System::Int32 *  >(resources->GetObject(S"toolBarSeparator3.ImageIndex")));
			this->toolBarSeparator3->Style = System::Windows::Forms::ToolBarButtonStyle::Separator;
			this->toolBarSeparator3->Text = resources->GetString(S"toolBarSeparator3.Text");
			this->toolBarSeparator3->ToolTipText = resources->GetString(S"toolBarSeparator3.ToolTipText");
			this->toolBarSeparator3->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"toolBarSeparator3.Visible")));
			// 
			// tBb_newNotepad
			// 
			this->tBb_newNotepad->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"tBb_newNotepad.Enabled")));
			this->tBb_newNotepad->ImageIndex = (*__try_cast<__box System::Int32 *  >(resources->GetObject(S"tBb_newNotepad.ImageIndex")));
			this->tBb_newNotepad->Text = resources->GetString(S"tBb_newNotepad.Text");
			this->tBb_newNotepad->ToolTipText = resources->GetString(S"tBb_newNotepad.ToolTipText");
			this->tBb_newNotepad->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"tBb_newNotepad.Visible")));
			// 
			// tBb_viewGraph
			// 
			this->tBb_viewGraph->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"tBb_viewGraph.Enabled")));
			this->tBb_viewGraph->ImageIndex = (*__try_cast<__box System::Int32 *  >(resources->GetObject(S"tBb_viewGraph.ImageIndex")));
			this->tBb_viewGraph->Text = resources->GetString(S"tBb_viewGraph.Text");
			this->tBb_viewGraph->ToolTipText = resources->GetString(S"tBb_viewGraph.ToolTipText");
			this->tBb_viewGraph->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"tBb_viewGraph.Visible")));
			// 
			// tBb_viewStats
			// 
			this->tBb_viewStats->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"tBb_viewStats.Enabled")));
			this->tBb_viewStats->ImageIndex = (*__try_cast<__box System::Int32 *  >(resources->GetObject(S"tBb_viewStats.ImageIndex")));
			this->tBb_viewStats->Text = resources->GetString(S"tBb_viewStats.Text");
			this->tBb_viewStats->ToolTipText = resources->GetString(S"tBb_viewStats.ToolTipText");
			this->tBb_viewStats->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"tBb_viewStats.Visible")));
			// 
			// tBb_viewLog
			// 
			this->tBb_viewLog->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"tBb_viewLog.Enabled")));
			this->tBb_viewLog->ImageIndex = (*__try_cast<__box System::Int32 *  >(resources->GetObject(S"tBb_viewLog.ImageIndex")));
			this->tBb_viewLog->Text = resources->GetString(S"tBb_viewLog.Text");
			this->tBb_viewLog->ToolTipText = resources->GetString(S"tBb_viewLog.ToolTipText");
			this->tBb_viewLog->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"tBb_viewLog.Visible")));
			// 
			// imageList1
			// 
			this->imageList1->ColorDepth = System::Windows::Forms::ColorDepth::Depth32Bit;
			this->imageList1->ImageSize = (*__try_cast<__box System::Drawing::Size *  >(resources->GetObject(S"imageList1.ImageSize")));
			this->imageList1->ImageStream = (__try_cast<System::Windows::Forms::ImageListStreamer *  >(resources->GetObject(S"imageList1.ImageStream")));
			this->imageList1->TransparentColor = System::Drawing::Color::Transparent;
			// 
			// menuItem86
			// 
			this->menuItem86->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem86.Enabled")));
			this->menuItem86->Index = 2;
			this->menuItem86->Shortcut = (*__try_cast<__box System::Windows::Forms::Shortcut *  >(resources->GetObject(S"menuItem86.Shortcut")));
			this->menuItem86->ShowShortcut = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem86.ShowShortcut")));
			this->menuItem86->Text = resources->GetString(S"menuItem86.Text");
			this->menuItem86->Visible = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"menuItem86.Visible")));
			this->menuItem86->Click += new System::EventHandler(this, menuItem86_Click);
			// 
			// Form1
			// 
			this->AccessibleDescription = resources->GetString(S"$this.AccessibleDescription");
			this->AccessibleName = resources->GetString(S"$this.AccessibleName");
			this->AutoScaleBaseSize = (*__try_cast<__box System::Drawing::Size *  >(resources->GetObject(S"$this.AutoScaleBaseSize")));
			this->AutoScroll = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"$this.AutoScroll")));
			this->AutoScrollMargin = (*__try_cast<__box System::Drawing::Size *  >(resources->GetObject(S"$this.AutoScrollMargin")));
			this->AutoScrollMinSize = (*__try_cast<__box System::Drawing::Size *  >(resources->GetObject(S"$this.AutoScrollMinSize")));
			this->BackgroundImage = (__try_cast<System::Drawing::Image *  >(resources->GetObject(S"$this.BackgroundImage")));
			this->ClientSize = (*__try_cast<__box System::Drawing::Size *  >(resources->GetObject(S"$this.ClientSize")));
			this->Controls->Add(this->toolBar1);
			this->Controls->Add(this->statusBar1);
			this->Enabled = (*__try_cast<__box System::Boolean *  >(resources->GetObject(S"$this.Enabled")));
			this->Font = (__try_cast<System::Drawing::Font *  >(resources->GetObject(S"$this.Font")));
			this->Icon = (__try_cast<System::Drawing::Icon *  >(resources->GetObject(S"$this.Icon")));
			this->ImeMode = (*__try_cast<__box System::Windows::Forms::ImeMode *  >(resources->GetObject(S"$this.ImeMode")));
			this->IsMdiContainer = true;
			this->Location = (*__try_cast<__box System::Drawing::Point *  >(resources->GetObject(S"$this.Location")));
			this->MaximumSize = (*__try_cast<__box System::Drawing::Size *  >(resources->GetObject(S"$this.MaximumSize")));
			this->Menu = this->mainMenu1;
			this->MinimumSize = (*__try_cast<__box System::Drawing::Size *  >(resources->GetObject(S"$this.MinimumSize")));
			this->Name = S"Form1";
			this->RightToLeft = (*__try_cast<__box System::Windows::Forms::RightToLeft *  >(resources->GetObject(S"$this.RightToLeft")));
			this->StartPosition = (*__try_cast<__box System::Windows::Forms::FormStartPosition *  >(resources->GetObject(S"$this.StartPosition")));
			this->Text = resources->GetString(S"$this.Text");
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->Closing += new System::ComponentModel::CancelEventHandler(this, Form1_Closing);
			this->Load += new System::EventHandler(this, Form1_Load);
			(__try_cast<System::ComponentModel::ISupportInitialize *  >(this->statusBarPanel1))->EndInit();
			(__try_cast<System::ComponentModel::ISupportInitialize *  >(this->statusBarPanel2))->EndInit();
			(__try_cast<System::ComponentModel::ISupportInitialize *  >(this->statusBarPanel3))->EndInit();
			this->ResumeLayout(false);

		}

		//

private: System::Void Form1_Load(System::Object *  sender, System::EventArgs *  e);
private: System::Void Form1_Closing(System::Object *  sender, System::ComponentModel::CancelEventArgs *  e);
private: System::Void menuItem10_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 this->Close();
		 }


private: System::Void menuItem2_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			openFileDialog1->Title = S"Open Resource..";
			openFileDialog1->InitialDirectory = Application::get_ExecutablePath();
			openFileDialog1->Filter = S"Bitmaps (*.BMP)|*.bmp|JPEG (*.jpg)|*.jpg|MPEG 1-2 (*.MPG)|*.mpg|All files (*.*)|*.*";
			openFileDialog1->FilterIndex = 2;

			if ( openFileDialog1->ShowDialog() == DialogResult::OK )
			{
//openFileDialog1->FileNames->get_FileName();
			}

		 }



private: System::Void menuItem58_Click(System::Object *  sender, System::EventArgs *  e);

private: System::Void menuItem57_Click(System::Object *  sender, System::EventArgs *  e);

private: System::Void menuItem59_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			menuItem37_Click(sender, e);
			menuItem57_Click(sender, e);
		 }


private: System::Void toolBar1_ButtonClick(System::Object *  sender, System::Windows::Forms::ToolBarButtonClickEventArgs *  e)
		 {
			//this->Cursor = Cursors::WaitCursor;

			 if (e->Button == tBb_openImage)
			  {
				menuItem4_Click(sender, NULL);
			  }
			 else if (e->Button == tBb_openVideo)
			  {
				menuItem66_Click(sender, NULL);
			  }
			 else if (e->Button == this->tBb_openDX)
			  {
				menuItem28_Click(sender, NULL);
			  }
			 else if (e->Button == tBb_newView)
			  {
				menuItem37_Click(sender, NULL);
			  }
			 else if (e->Button == tBb_viewRes)
			  {
				  if (myResManForm == NULL)
				  {
					  menuItem23_Click(sender, NULL);
					  tBb_viewRes->Pushed = true;
				  }
				  else
				  {
					  myResManForm->Visible = !myResManForm->Visible;
					  tBb_viewRes->Pushed = myResManForm->Visible;
				  }

			  }
			 else if (e->Button == tBb_viewStats)
			  {
				  if (myStatsForm == NULL)
				  {
					  menuItem62_Click(sender, NULL);
					  tBb_viewStats->Pushed = true;
				  }
				  else
				  {
					  myStatsForm->Visible = !myStatsForm->Visible;
					  tBb_viewStats->Pushed = myStatsForm->Visible;
				  }

			  }
			 else if (e->Button == tBb_newNotepad)
			  {
				menuItem47_Click(sender, NULL);
			  }
			 else if (e->Button == tBb_newDoctor)
			  {
				menuItem67_Click(sender, NULL);
			  }
			 else if (e->Button == tBb_viewGraph)
			  {
				  if (myGraphForm == NULL)
				  {
					  menuItem68_Click(sender, NULL);
					  tBb_viewGraph->Pushed = true;
				  }
				  else
				  {
					  myGraphForm->Visible = !myGraphForm->Visible;
					  tBb_viewGraph->Pushed = myGraphForm->Visible;
				  }
			  }
			 else if (e->Button == tBb_viewLog)
			  {
				  if (myLogForm == NULL)
				  {
					  menuItem49_Click(sender, NULL);
					  tBb_viewLog->Pushed = true;
				  }
				  else
				  {
					  myLogForm->Visible = !myLogForm->Visible;
					  tBb_viewLog->Pushed = myLogForm->Visible;
				  }
			  }

			//this->Cursor = Cursors::Default;
		 }



private: System::Void menuItem34_Click(System::Object *  sender, System::EventArgs *  e)
		 {	this->LayoutMdi(System::Windows::Forms::MdiLayout::Cascade);	}
private: System::Void menuItem33_Click(System::Object *  sender, System::EventArgs *  e)
		 {	this->LayoutMdi(System::Windows::Forms::MdiLayout::TileHorizontal);	}
private: System::Void menuItem36_Click(System::Object *  sender, System::EventArgs *  e)
		 {	this->LayoutMdi(System::Windows::Forms::MdiLayout::TileVertical);	}
private: System::Void menuItem35_Click(System::Object *  sender, System::EventArgs *  e)
		 {	this->LayoutMdi(System::Windows::Forms::MdiLayout::ArrangeIcons);	}

private: System::Void menuItem24_Click(System::Object *  sender, System::EventArgs *  e)
		 {	menuItem24->Checked = !menuItem24->Checked; statusBar1->Visible = menuItem24->Checked;	}
private: System::Void menuItem37_Click_1(System::Object *  sender, System::EventArgs *  e)
		 {	menuItem37->Checked = !menuItem37->Checked; toolBar1->Visible = menuItem37->Checked;	}

private: System::Void menuItem21_Click(System::Object *  sender, System::EventArgs *  e)
		 {	System::Diagnostics::Process::Start(S"http://lnx.ewgate.net/viplib/documentation.html");	}
private: System::Void menuItem19_Click(System::Object *  sender, System::EventArgs *  e)
		 {	System::Diagnostics::Process::Start(S"http://www.ewgate.net/research/"); }
private: System::Void menuItem20_Click(System::Object *  sender, System::EventArgs *  e)
		 {	 System::Diagnostics::Process::Start(S"http://lnx.ewgate.net/viplib/");	 }



//////////////////////////////////////////////////////////////////////// LAYOUT

private: System::Void menuItem53_Click(System::Object *  sender, System::EventArgs *  e);
private: System::Void menuItem54_Click(System::Object *  sender, System::EventArgs *  e);
private: void loadMenuIcons();
private: void loadLayout(String* filePath);

private: System::Void menuItem81_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 String* filename = String::Concat(Path::GetDirectoryName(Application::ExecutablePath), S"\\layouts\\layout.default.xml");
			 if ( File::Exists(filename) )
				 loadLayout(filename);
		 }

//////////////////////////////////////////////////////////////////////// MDI CHILDS INSTANCES



private: System::Void resource_Click(System::Object *  sender, System::EventArgs *  e);

private: System::Void menuItem37_Click(System::Object *  sender, System::EventArgs *  e);

private: System::Void menuItem67_Click(System::Object *  sender, System::EventArgs *  e);

private: System::Void menuItem38_Click(System::Object *  sender, System::EventArgs *  e);

private: System::Void menuItem26_Click(System::Object *  sender, System::EventArgs *  e);

private: System::Void menuItem47_Click(System::Object *  sender, System::EventArgs *  e);

private: System::Void menuItem4_Click(System::Object *  sender, System::EventArgs *  e);

private: System::Void menuItem28_Click(System::Object *  sender, System::EventArgs *  e);

private: System::Void menuItem65_Click(System::Object *  sender, System::EventArgs *  e);

private: System::Void menuItem49_Click(System::Object *  sender, System::EventArgs *  e);

private: System::Void menuItem56_Click(System::Object *  sender, System::EventArgs *  e);

private: System::Void menuItem62_Click(System::Object *  sender, System::EventArgs *  e);

private: System::Void menuItem16_Click(System::Object *  sender, System::EventArgs *  e);

private: System::Void menuItem17_Click(System::Object *  sender, System::EventArgs *  e);

private: System::Void menuItem23_Click(System::Object *  sender, System::EventArgs *  e);

private: System::Void menuItem68_Click(System::Object *  sender, System::EventArgs *  e);

//LOGGING
private: System::Void menuItem71_Click(System::Object *  sender, System::EventArgs *  e);
private: System::Void menuItem72_Click(System::Object *  sender, System::EventArgs *  e);
private: System::Void menuItem73_Click(System::Object *  sender, System::EventArgs *  e);
private: System::Void menuItem75_Click(System::Object *  sender, System::EventArgs *  e);

private: System::Void menuItem66_Click(System::Object *  sender, System::EventArgs *  e);
private: System::Void menuItem86_Click(System::Object *  sender, System::EventArgs *  e);


private: System::Void menuItem82_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 loadMenuIcons();
		 }

private: System::Void menuItem84_Click(System::Object *  sender, System::EventArgs *  e);


private: System::Void menuItem85_Click(System::Object *  sender, System::EventArgs *  e);



};
}


