/**
 *  @class   vipPKStudio
 *
 *  @brief   Main form (interface)
 *
 *  @version 1.0
 *  @date    /05/2006
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

#include "logForm.h"
#include "splashForm.h"
#include "wizardForm.h"
#include "RenamerForm.h"
#include "optionForm.h"
#include "vipDirectories.h"

void CloseSplash();

namespace vipPS
{

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Riepilogo per vipPKStudio
	///
	/// AVVISO: se si modifica il nome della classe, sarà necessario modificare la
	///          proprietà "Nome file di risorse" relativa allo strumento di compilazione delle risorse gestite
	///          associato a tutti i file RESX da cui dipende la classe. In caso contrario,
	///          le finestre di progettazione non saranno in grado di interagire correttamente con le
	///          risorse localizzate associate al form.
	/// </summary>
	public __gc class vipPKStudio : public System::Windows::Forms::Form
	{
	public:
		vipPKStudio(void);

		void writeLog(String* message);
		void writeLog(String* message, Form* sender);

	protected:
		void Dispose(Boolean disposing);


	public: Array* vipClassTypes;
	private: String* vipClassTypesXMLFile;
	public: Array* vipTemplateProjects;
	private: String* vipTemplateProjectsXMLFile;
	public: Array* vipNameSpace;
	private: String* vipNameSpaceFile;

	public: vipDirectories* Directories;
	private: StreamWriter* logWriter;
	private: Form* logLastSender;
	private: String* logFilePath;

	private: logForm* myLogForm;
	private: wizardForm* myWizardForm;
	private: optionForm* myOptionForm;
	private: RenamerForm* myRenamerForm;


	private: System::Windows::Forms::MainMenu *  mainMenu1;
	private: System::Windows::Forms::StatusBar *  statusBar1;
	private: System::Windows::Forms::MenuItem *  menuItem1;
	private: System::Windows::Forms::MenuItem *  menuItem2;
	private: System::Windows::Forms::MenuItem *  menuItem3;
	private: System::Windows::Forms::MenuItem *  menuItem4;
	private: System::Windows::Forms::MenuItem *  menuItem5;
	private: System::Windows::Forms::MenuItem *  menuItem6;
	private: System::Windows::Forms::MenuItem *  menuItem7;
	private: System::Windows::Forms::MenuItem *  menuItem8;
	private: System::Windows::Forms::MenuItem *  menuItem9;
	private: System::Windows::Forms::MenuItem *  menuItem11;
	private: System::Windows::Forms::MenuItem *  menuItem12;
	private: System::Windows::Forms::MenuItem *  menuItem13;

	private: System::Windows::Forms::MenuItem *  menuItem15;
	private: System::Windows::Forms::MenuItem *  menuItem16;
	private: System::Windows::Forms::MenuItem *  menuItem17;
	private: System::Windows::Forms::MenuItem *  menuItem18;
	private: System::Windows::Forms::MenuItem *  menuItem19;
	private: System::Windows::Forms::MenuItem *  menuItem20;
	private: System::Windows::Forms::MenuItem *  menuItem21;

	private: System::Windows::Forms::MenuItem *  menuItem23;
	private: System::Windows::Forms::MenuItem *  menuItem24;
	private: System::Windows::Forms::MenuItem *  menuItem25;
	private: System::Windows::Forms::MenuItem *  menuItem26;
	private: System::Windows::Forms::MenuItem *  menuItem27;
	private: System::Windows::Forms::MenuItem *  menuItem28;




	private: System::Windows::Forms::MenuItem *  menuItem33;
	private: System::Windows::Forms::SaveFileDialog *  saveFileDialog1;
	private: System::Windows::Forms::OpenFileDialog *  openFileDialog1;
	private: System::Windows::Forms::MenuItem *  menuItem34;
	private: System::Windows::Forms::MenuItem *  menuItem35;
	private: System::Windows::Forms::MenuItem *  menuItem36;
	private: System::Windows::Forms::MenuItem *  menuItem38;
	private: System::Windows::Forms::MenuItem *  menuItem10;

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
	private: System::Windows::Forms::MenuItem *  menuItem37;
	private: System::Windows::Forms::MenuItem *  menuItem14;
	private: System::Windows::Forms::MenuItem *  menuItem49;
	private: System::Windows::Forms::MenuItem *  menuItem50;
	private: System::Windows::Forms::MenuItem *  menuItem51;
	private: System::Windows::Forms::MenuItem *  menuItem52;
	private: System::Windows::Forms::MenuItem *  menuItem53;
	private: System::Windows::Forms::MenuItem *  menuItem54;
	private: System::Windows::Forms::MenuItem *  menuItem55;
	private: System::Windows::Forms::MenuItem *  menuItem56;
	private: System::Windows::Forms::MenuItem *  menuItem57;
	private: System::Windows::Forms::FolderBrowserDialog *  folderBrowserDialog1;
	private: System::Windows::Forms::MenuItem *  menuItem58;
	private: System::Windows::Forms::HelpProvider *  helpProvider1;
	private: System::Windows::Forms::MenuItem *  menuItem29;
	private: System::Windows::Forms::MenuItem *  menuItem30;

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
			System::Resources::ResourceManager *  resources = new System::Resources::ResourceManager(__typeof(vipPS::vipPKStudio));
			this->mainMenu1 = new System::Windows::Forms::MainMenu();
			this->menuItem1 = new System::Windows::Forms::MenuItem();
			this->menuItem15 = new System::Windows::Forms::MenuItem();
			this->menuItem13 = new System::Windows::Forms::MenuItem();
			this->menuItem12 = new System::Windows::Forms::MenuItem();
			this->menuItem8 = new System::Windows::Forms::MenuItem();
			this->menuItem6 = new System::Windows::Forms::MenuItem();
			this->menuItem27 = new System::Windows::Forms::MenuItem();
			this->menuItem28 = new System::Windows::Forms::MenuItem();
			this->menuItem7 = new System::Windows::Forms::MenuItem();
			this->menuItem2 = new System::Windows::Forms::MenuItem();
			this->menuItem19 = new System::Windows::Forms::MenuItem();
			this->menuItem18 = new System::Windows::Forms::MenuItem();
			this->menuItem9 = new System::Windows::Forms::MenuItem();
			this->menuItem11 = new System::Windows::Forms::MenuItem();
			this->menuItem14 = new System::Windows::Forms::MenuItem();
			this->menuItem38 = new System::Windows::Forms::MenuItem();
			this->menuItem35 = new System::Windows::Forms::MenuItem();
			this->menuItem10 = new System::Windows::Forms::MenuItem();
			this->menuItem36 = new System::Windows::Forms::MenuItem();
			this->menuItem37 = new System::Windows::Forms::MenuItem();
			this->menuItem42 = new System::Windows::Forms::MenuItem();
			this->menuItem43 = new System::Windows::Forms::MenuItem();
			this->menuItem44 = new System::Windows::Forms::MenuItem();
			this->menuItem45 = new System::Windows::Forms::MenuItem();
			this->menuItem46 = new System::Windows::Forms::MenuItem();
			this->menuItem3 = new System::Windows::Forms::MenuItem();
			this->menuItem55 = new System::Windows::Forms::MenuItem();
			this->menuItem56 = new System::Windows::Forms::MenuItem();
			this->menuItem57 = new System::Windows::Forms::MenuItem();
			this->menuItem20 = new System::Windows::Forms::MenuItem();
			this->menuItem33 = new System::Windows::Forms::MenuItem();
			this->menuItem16 = new System::Windows::Forms::MenuItem();
			this->menuItem34 = new System::Windows::Forms::MenuItem();
			this->menuItem39 = new System::Windows::Forms::MenuItem();
			this->menuItem41 = new System::Windows::Forms::MenuItem();
			this->menuItem48 = new System::Windows::Forms::MenuItem();
			this->menuItem47 = new System::Windows::Forms::MenuItem();
			this->menuItem40 = new System::Windows::Forms::MenuItem();
			this->menuItem17 = new System::Windows::Forms::MenuItem();
			this->menuItem4 = new System::Windows::Forms::MenuItem();
			this->menuItem54 = new System::Windows::Forms::MenuItem();
			this->menuItem26 = new System::Windows::Forms::MenuItem();
			this->menuItem52 = new System::Windows::Forms::MenuItem();
			this->menuItem53 = new System::Windows::Forms::MenuItem();
			this->menuItem25 = new System::Windows::Forms::MenuItem();
			this->menuItem5 = new System::Windows::Forms::MenuItem();
			this->menuItem24 = new System::Windows::Forms::MenuItem();
			this->menuItem58 = new System::Windows::Forms::MenuItem();
			this->menuItem51 = new System::Windows::Forms::MenuItem();
			this->menuItem29 = new System::Windows::Forms::MenuItem();
			this->menuItem50 = new System::Windows::Forms::MenuItem();
			this->menuItem30 = new System::Windows::Forms::MenuItem();
			this->menuItem49 = new System::Windows::Forms::MenuItem();
			this->menuItem23 = new System::Windows::Forms::MenuItem();
			this->menuItem21 = new System::Windows::Forms::MenuItem();
			this->statusBar1 = new System::Windows::Forms::StatusBar();
			this->saveFileDialog1 = new System::Windows::Forms::SaveFileDialog();
			this->openFileDialog1 = new System::Windows::Forms::OpenFileDialog();
			this->folderBrowserDialog1 = new System::Windows::Forms::FolderBrowserDialog();
			this->helpProvider1 = new System::Windows::Forms::HelpProvider();
			this->SuspendLayout();
			// 
			// mainMenu1
			// 
			System::Windows::Forms::MenuItem* __mcTemp__1[] = new System::Windows::Forms::MenuItem*[6];
			__mcTemp__1[0] = this->menuItem1;
			__mcTemp__1[1] = this->menuItem2;
			__mcTemp__1[2] = this->menuItem9;
			__mcTemp__1[3] = this->menuItem3;
			__mcTemp__1[4] = this->menuItem4;
			__mcTemp__1[5] = this->menuItem5;
			this->mainMenu1->MenuItems->AddRange(__mcTemp__1);
			// 
			// menuItem1
			// 
			this->menuItem1->Index = 0;
			System::Windows::Forms::MenuItem* __mcTemp__2[] = new System::Windows::Forms::MenuItem*[8];
			__mcTemp__2[0] = this->menuItem15;
			__mcTemp__2[1] = this->menuItem13;
			__mcTemp__2[2] = this->menuItem12;
			__mcTemp__2[3] = this->menuItem8;
			__mcTemp__2[4] = this->menuItem6;
			__mcTemp__2[5] = this->menuItem27;
			__mcTemp__2[6] = this->menuItem28;
			__mcTemp__2[7] = this->menuItem7;
			this->menuItem1->MenuItems->AddRange(__mcTemp__2);
			this->menuItem1->Text = S"&File";
			// 
			// menuItem15
			// 
			this->menuItem15->Index = 0;
			this->menuItem15->Text = S"&New File..";
			this->menuItem15->Click += new System::EventHandler(this, menuItem15_Click);
			// 
			// menuItem13
			// 
			this->menuItem13->Index = 1;
			this->menuItem13->Text = S"-";
			// 
			// menuItem12
			// 
			this->menuItem12->Index = 2;
			this->menuItem12->Text = S"Save &All..";
			// 
			// menuItem8
			// 
			this->menuItem8->Index = 3;
			this->menuItem8->Text = S"&Close All";
			// 
			// menuItem6
			// 
			this->menuItem6->Index = 4;
			this->menuItem6->Text = S"-";
			// 
			// menuItem27
			// 
			this->menuItem27->Index = 5;
			this->menuItem27->Text = S"Check for &Updates..";
			this->menuItem27->Click += new System::EventHandler(this, menuItem27_Click);
			// 
			// menuItem28
			// 
			this->menuItem28->Index = 6;
			this->menuItem28->Text = S"-";
			// 
			// menuItem7
			// 
			this->menuItem7->Index = 7;
			this->menuItem7->Text = S"E&xit";
			this->menuItem7->Click += new System::EventHandler(this, menuItem7_Click);
			// 
			// menuItem2
			// 
			this->menuItem2->Index = 1;
			System::Windows::Forms::MenuItem* __mcTemp__3[] = new System::Windows::Forms::MenuItem*[2];
			__mcTemp__3[0] = this->menuItem19;
			__mcTemp__3[1] = this->menuItem18;
			this->menuItem2->MenuItems->AddRange(__mcTemp__3);
			this->menuItem2->Text = S"&Edit";
			// 
			// menuItem19
			// 
			this->menuItem19->Enabled = false;
			this->menuItem19->Index = 0;
			this->menuItem19->Text = S"&Copy";
			// 
			// menuItem18
			// 
			this->menuItem18->Index = 1;
			this->menuItem18->Text = S"-";
			// 
			// menuItem9
			// 
			this->menuItem9->Index = 2;
			System::Windows::Forms::MenuItem* __mcTemp__4[] = new System::Windows::Forms::MenuItem*[7];
			__mcTemp__4[0] = this->menuItem11;
			__mcTemp__4[1] = this->menuItem14;
			__mcTemp__4[2] = this->menuItem38;
			__mcTemp__4[3] = this->menuItem35;
			__mcTemp__4[4] = this->menuItem36;
			__mcTemp__4[5] = this->menuItem42;
			__mcTemp__4[6] = this->menuItem43;
			this->menuItem9->MenuItems->AddRange(__mcTemp__4);
			this->menuItem9->Text = S"&Packages";
			// 
			// menuItem11
			// 
			this->menuItem11->Index = 0;
			this->menuItem11->Text = S"Generation &Wizard..";
			this->menuItem11->Click += new System::EventHandler(this, menuItem11_Click);
			// 
			// menuItem14
			// 
			this->menuItem14->Index = 1;
			this->menuItem14->Text = S"Package &Renamer..";
			this->menuItem14->Click += new System::EventHandler(this, menuItem14_Click);
			// 
			// menuItem38
			// 
			this->menuItem38->Index = 2;
			this->menuItem38->Text = S"-";
			// 
			// menuItem35
			// 
			this->menuItem35->Enabled = false;
			this->menuItem35->Index = 3;
			System::Windows::Forms::MenuItem* __mcTemp__5[] = new System::Windows::Forms::MenuItem*[1];
			__mcTemp__5[0] = this->menuItem10;
			this->menuItem35->MenuItems->AddRange(__mcTemp__5);
			this->menuItem35->Text = S"Empty Package from";
			// 
			// menuItem10
			// 
			this->menuItem10->Enabled = false;
			this->menuItem10->Index = 0;
			this->menuItem10->Text = S"NIJ";
			// 
			// menuItem36
			// 
			this->menuItem36->Enabled = false;
			this->menuItem36->Index = 4;
			System::Windows::Forms::MenuItem* __mcTemp__6[] = new System::Windows::Forms::MenuItem*[1];
			__mcTemp__6[0] = this->menuItem37;
			this->menuItem36->MenuItems->AddRange(__mcTemp__6);
			this->menuItem36->Text = S"Sample Package from";
			// 
			// menuItem37
			// 
			this->menuItem37->Enabled = false;
			this->menuItem37->Index = 0;
			this->menuItem37->Text = S"NIJ";
			// 
			// menuItem42
			// 
			this->menuItem42->Index = 5;
			this->menuItem42->Text = S"-";
			// 
			// menuItem43
			// 
			this->menuItem43->Index = 6;
			System::Windows::Forms::MenuItem* __mcTemp__7[] = new System::Windows::Forms::MenuItem*[3];
			__mcTemp__7[0] = this->menuItem44;
			__mcTemp__7[1] = this->menuItem45;
			__mcTemp__7[2] = this->menuItem46;
			this->menuItem43->MenuItems->AddRange(__mcTemp__7);
			this->menuItem43->Text = S"View current";
			// 
			// menuItem44
			// 
			this->menuItem44->Index = 0;
			this->menuItem44->Text = S"vipClassTypes";
			this->menuItem44->Click += new System::EventHandler(this, menuItem44_Click);
			// 
			// menuItem45
			// 
			this->menuItem45->Index = 1;
			this->menuItem45->Text = S"vipPkgProjects";
			this->menuItem45->Click += new System::EventHandler(this, menuItem45_Click);
			// 
			// menuItem46
			// 
			this->menuItem46->Index = 2;
			this->menuItem46->Text = S"NAMESPACE";
			this->menuItem46->Click += new System::EventHandler(this, menuItem46_Click);
			// 
			// menuItem3
			// 
			this->menuItem3->Index = 3;
			System::Windows::Forms::MenuItem* __mcTemp__8[] = new System::Windows::Forms::MenuItem*[8];
			__mcTemp__8[0] = this->menuItem55;
			__mcTemp__8[1] = this->menuItem20;
			__mcTemp__8[2] = this->menuItem39;
			__mcTemp__8[3] = this->menuItem41;
			__mcTemp__8[4] = this->menuItem48;
			__mcTemp__8[5] = this->menuItem47;
			__mcTemp__8[6] = this->menuItem40;
			__mcTemp__8[7] = this->menuItem17;
			this->menuItem3->MenuItems->AddRange(__mcTemp__8);
			this->menuItem3->Text = S"&Options";
			// 
			// menuItem55
			// 
			this->menuItem55->Index = 0;
			System::Windows::Forms::MenuItem* __mcTemp__9[] = new System::Windows::Forms::MenuItem*[2];
			__mcTemp__9[0] = this->menuItem56;
			__mcTemp__9[1] = this->menuItem57;
			this->menuItem55->MenuItems->AddRange(__mcTemp__9);
			this->menuItem55->Text = S"ToolBars";
			// 
			// menuItem56
			// 
			this->menuItem56->Enabled = false;
			this->menuItem56->Index = 0;
			this->menuItem56->Text = S"Standard";
			this->menuItem56->Click += new System::EventHandler(this, menuItem56_Click);
			// 
			// menuItem57
			// 
			this->menuItem57->Checked = true;
			this->menuItem57->Index = 1;
			this->menuItem57->Text = S"Status Bar";
			this->menuItem57->Click += new System::EventHandler(this, menuItem57_Click);
			// 
			// menuItem20
			// 
			this->menuItem20->Index = 1;
			System::Windows::Forms::MenuItem* __mcTemp__10[] = new System::Windows::Forms::MenuItem*[3];
			__mcTemp__10[0] = this->menuItem33;
			__mcTemp__10[1] = this->menuItem16;
			__mcTemp__10[2] = this->menuItem34;
			this->menuItem20->MenuItems->AddRange(__mcTemp__10);
			this->menuItem20->Text = S"&Logging";
			// 
			// menuItem33
			// 
			this->menuItem33->Checked = true;
			this->menuItem33->Index = 0;
			this->menuItem33->Text = S"Enabled";
			this->menuItem33->Click += new System::EventHandler(this, menuItem33_Click);
			// 
			// menuItem16
			// 
			this->menuItem16->Index = 1;
			this->menuItem16->Text = S"&View Log";
			this->menuItem16->Click += new System::EventHandler(this, menuItem16_Click);
			// 
			// menuItem34
			// 
			this->menuItem34->Index = 2;
			this->menuItem34->Text = S"Export &As..";
			this->menuItem34->Click += new System::EventHandler(this, menuItem34_Click);
			// 
			// menuItem39
			// 
			this->menuItem39->Index = 2;
			this->menuItem39->Text = S"-";
			// 
			// menuItem41
			// 
			this->menuItem41->Index = 3;
			this->menuItem41->Text = S"Reload vipClassTypes";
			this->menuItem41->Click += new System::EventHandler(this, menuItem41_Click);
			// 
			// menuItem48
			// 
			this->menuItem48->Index = 4;
			this->menuItem48->Text = S"Reload vipPkgProjects";
			this->menuItem48->Click += new System::EventHandler(this, menuItem48_Click);
			// 
			// menuItem47
			// 
			this->menuItem47->Index = 5;
			this->menuItem47->Text = S"Reload NAMESPACE";
			this->menuItem47->Click += new System::EventHandler(this, menuItem47_Click);
			// 
			// menuItem40
			// 
			this->menuItem40->Index = 6;
			this->menuItem40->Text = S"-";
			// 
			// menuItem17
			// 
			this->menuItem17->Index = 7;
			this->menuItem17->Text = S"&Preferences..";
			this->menuItem17->Click += new System::EventHandler(this, menuItem17_Click);
			// 
			// menuItem4
			// 
			this->menuItem4->Index = 4;
			this->menuItem4->MdiList = true;
			System::Windows::Forms::MenuItem* __mcTemp__11[] = new System::Windows::Forms::MenuItem*[5];
			__mcTemp__11[0] = this->menuItem54;
			__mcTemp__11[1] = this->menuItem26;
			__mcTemp__11[2] = this->menuItem52;
			__mcTemp__11[3] = this->menuItem53;
			__mcTemp__11[4] = this->menuItem25;
			this->menuItem4->MenuItems->AddRange(__mcTemp__11);
			this->menuItem4->Text = S"&Windows";
			// 
			// menuItem54
			// 
			this->menuItem54->Index = 0;
			this->menuItem54->Text = S"Cascade";
			this->menuItem54->Click += new System::EventHandler(this, menuItem54_Click);
			// 
			// menuItem26
			// 
			this->menuItem26->Index = 1;
			this->menuItem26->Text = S"Tile Horizontal";
			this->menuItem26->Click += new System::EventHandler(this, menuItem26_Click);
			// 
			// menuItem52
			// 
			this->menuItem52->Index = 2;
			this->menuItem52->Text = S"Tile Vertical";
			this->menuItem52->Click += new System::EventHandler(this, menuItem52_Click);
			// 
			// menuItem53
			// 
			this->menuItem53->Index = 3;
			this->menuItem53->Text = S"Arrange";
			this->menuItem53->Click += new System::EventHandler(this, menuItem53_Click);
			// 
			// menuItem25
			// 
			this->menuItem25->Index = 4;
			this->menuItem25->Text = S"-";
			// 
			// menuItem5
			// 
			this->menuItem5->Index = 5;
			System::Windows::Forms::MenuItem* __mcTemp__12[] = new System::Windows::Forms::MenuItem*[9];
			__mcTemp__12[0] = this->menuItem24;
			__mcTemp__12[1] = this->menuItem58;
			__mcTemp__12[2] = this->menuItem51;
			__mcTemp__12[3] = this->menuItem29;
			__mcTemp__12[4] = this->menuItem50;
			__mcTemp__12[5] = this->menuItem30;
			__mcTemp__12[6] = this->menuItem49;
			__mcTemp__12[7] = this->menuItem23;
			__mcTemp__12[8] = this->menuItem21;
			this->menuItem5->MenuItems->AddRange(__mcTemp__12);
			this->menuItem5->Text = S"&Help";
			// 
			// menuItem24
			// 
			this->menuItem24->Index = 0;
			this->menuItem24->Text = S"&Online Documentation";
			this->menuItem24->Click += new System::EventHandler(this, menuItem24_Click);
			// 
			// menuItem58
			// 
			this->menuItem58->Index = 1;
			this->menuItem58->Text = S"&Contents";
			this->menuItem58->Click += new System::EventHandler(this, menuItem58_Click);
			// 
			// menuItem51
			// 
			this->menuItem51->Index = 2;
			this->menuItem51->Text = S"-";
			// 
			// menuItem29
			// 
			this->menuItem29->Index = 3;
			this->menuItem29->Text = S"&Package Studio Homepage";
			this->menuItem29->Click += new System::EventHandler(this, menuItem29_Click);
			// 
			// menuItem50
			// 
			this->menuItem50->Index = 4;
			this->menuItem50->Text = S"VIPLib &Homepage";
			this->menuItem50->Click += new System::EventHandler(this, menuItem50_Click);
			// 
			// menuItem30
			// 
			this->menuItem30->Index = 5;
			this->menuItem30->Text = S"&mmLab - DIT";
			this->menuItem30->Click += new System::EventHandler(this, menuItem30_Click_1);
			// 
			// menuItem49
			// 
			this->menuItem49->Index = 6;
			this->menuItem49->Text = S"&eWorld ReSearch";
			this->menuItem49->Click += new System::EventHandler(this, menuItem49_Click);
			// 
			// menuItem23
			// 
			this->menuItem23->Index = 7;
			this->menuItem23->Text = S"-";
			// 
			// menuItem21
			// 
			this->menuItem21->Index = 8;
			this->menuItem21->Text = S"about &Package Studio..";
			this->menuItem21->Click += new System::EventHandler(this, menuItem21_Click);
			// 
			// statusBar1
			// 
			this->statusBar1->Location = System::Drawing::Point(0, 400);
			this->statusBar1->Name = S"statusBar1";
			this->statusBar1->Size = System::Drawing::Size(688, 22);
			this->statusBar1->TabIndex = 1;
			this->statusBar1->Text = S"Welcome VIPLib Package Studio...";
			// 
			// helpProvider1
			// 
			this->helpProvider1->HelpNamespace = S"reference\\vipPS.chm";
			// 
			// vipPKStudio
			// 
			this->AutoScaleBaseSize = System::Drawing::Size(6, 15);
			this->ClientSize = System::Drawing::Size(688, 422);
			this->Controls->Add(this->statusBar1);
			this->Icon = (__try_cast<System::Drawing::Icon *  >(resources->GetObject(S"$this.Icon")));
			this->IsMdiContainer = true;
			this->Menu = this->mainMenu1;
			this->Name = S"vipPKStudio";
			this->Text = S"VIPLib Package Studio";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->Closing += new System::ComponentModel::CancelEventHandler(this, vipPKStudio_Closing);
			this->Load += new System::EventHandler(this, vipPKStudio_Load);
			this->ResumeLayout(false);

		}
//
void LoadTypes(String* xmlFile);
void LoadGroups(String* xmlFile);
void LoadNames(String* pathFile);
bool loadVIPLibRootDirectory();
String* findVIPLibRootDirectory(String *);

	private: System::Void menuItem7_Click(System::Object *  sender, System::EventArgs *  e)
			 {
				 this->Close();
			 }

	private: System::Void vipPKStudio_Load(System::Object *  sender, System::EventArgs *  e);
	private: System::Void vipPKStudio_Closing(System::Object *  sender, System::ComponentModel::CancelEventArgs *  e);

private: System::Void menuItem15_Click(System::Object *  sender, System::EventArgs *  e);
private: System::Void menuItem11_Click(System::Object *  sender, System::EventArgs *  e);
private: System::Void menuItem16_Click(System::Object *  sender, System::EventArgs *  e);
private: System::Void menuItem17_Click(System::Object *  sender, System::EventArgs *  e);
private: System::Void menuItem21_Click(System::Object *  sender, System::EventArgs *  e);
private: System::Void menuItem27_Click(System::Object *  sender, System::EventArgs *  e);
private: System::Void menuItem33_Click(System::Object *  sender, System::EventArgs *  e);
private: System::Void menuItem34_Click(System::Object *  sender, System::EventArgs *  e);
private: System::Void menuItem41_Click(System::Object *  sender, System::EventArgs *  e);
private: System::Void menuItem44_Click(System::Object *  sender, System::EventArgs *  e);
private: System::Void menuItem45_Click(System::Object *  sender, System::EventArgs *  e);
private: System::Void menuItem46_Click(System::Object *  sender, System::EventArgs *  e);
private: System::Void menuItem48_Click(System::Object *  sender, System::EventArgs *  e);
private: System::Void menuItem47_Click(System::Object *  sender, System::EventArgs *  e);
private: System::Void menuItem14_Click(System::Object *  sender, System::EventArgs *  e);



private: System::Void menuItem54_Click(System::Object *  sender, System::EventArgs *  e)
		 {	this->LayoutMdi(System::Windows::Forms::MdiLayout::Cascade);	}
private: System::Void menuItem26_Click(System::Object *  sender, System::EventArgs *  e)
		 {	this->LayoutMdi(System::Windows::Forms::MdiLayout::TileHorizontal);	}
private: System::Void menuItem52_Click(System::Object *  sender, System::EventArgs *  e)
		 {	this->LayoutMdi(System::Windows::Forms::MdiLayout::TileVertical);	}
private: System::Void menuItem53_Click(System::Object *  sender, System::EventArgs *  e)
		 {	this->LayoutMdi(System::Windows::Forms::MdiLayout::ArrangeIcons);	}

private: System::Void menuItem24_Click(System::Object *  sender, System::EventArgs *  e)
		 {	System::Diagnostics::Process::Start(S"http://mmlab.science.unitn.it/projects/vipPS/docs/");	}

private: System::Void menuItem29_Click(System::Object *  sender, System::EventArgs *  e)
		 {	 System::Diagnostics::Process::Start(S"http://mmlab.science.unitn.it/projects/vipPS/");	 }
private: System::Void menuItem50_Click(System::Object *  sender, System::EventArgs *  e)
		 {	 System::Diagnostics::Process::Start(S"http://mmlab.science.unitn.it/projects/VIPLib/");	 }
private: System::Void menuItem30_Click_1(System::Object *  sender, System::EventArgs *  e)
		 {	System::Diagnostics::Process::Start(S"http://mmlab.science.unitn.it");	}
private: System::Void menuItem49_Click(System::Object *  sender, System::EventArgs *  e)
		 {	System::Diagnostics::Process::Start(S"http://www.ewgate.net/research/"); }

private: System::Void menuItem57_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 menuItem57->Checked = !menuItem57->Checked; statusBar1->Visible = menuItem57->Checked;
		 }

private: System::Void menuItem56_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 //menuItem56->Checked = !menuItem56->Checked; toolBar1->Visible = menuItem56->Checked;
		 }

private: System::Void menuItem58_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 Help::ShowHelp(this, helpProvider1->HelpNamespace);
		 }




};
}
