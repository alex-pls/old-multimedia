#include "StdAfx.h"
#include "statsForm.h"
#include "Form1.h"


namespace vipWS3
{
System::Void statsForm::statsForm_Load(System::Object *  sender, System::EventArgs *  e)
 {
	button1_Click(sender, e);
 }

System::Void statsForm::statsForm_Closing(System::Object *  sender, System::ComponentModel::CancelEventArgs *  e)
 {
	e->Cancel = true;
	this->Visible = false;
 }
System::Void statsForm::statsForm_Closed(System::Object *  sender, System::EventArgs *  e)
 {
	static_cast<Form1*>(this->MdiParent)->updateChildFormsList();
 }




System::Void statsForm::button1_Click(System::Object *  sender, System::EventArgs *  e)
 {
	switch(tabControl1->SelectedIndex)
	 {
	  case 0:	// system
		{
			this->Cursor = Cursors::WaitCursor;
			TreeNode* tn_sys1 = new TreeNode(S"OS");
			tn_sys1->Nodes->Add( String::Concat(S"Platform:  ", S"unknown") );
			tn_sys1->Nodes->Add( String::Concat(S"Monitor Size:  ", SystemInformation::PrimaryMonitorSize.ToString() ) );

			TreeNode* tn_sys2 = new TreeNode(S"WorkShop");
			tn_sys2->Nodes->Add( String::Format(S"Allocated Memory:  {0} bytes", Convert::ToString(GC::GetTotalMemory(false)) ) );
			tn_sys2->Nodes->Add( String::Format(S"Allocated Windows:  {0}", this->MdiParent->MdiChildren->Count.ToString()  ) );


			tVsystem->Nodes->Clear();
			tVsystem->Nodes->Add( tn_sys1 );
			tVsystem->Nodes->Add( tn_sys2 );
			tVsystem->Refresh();

			this->Cursor = Cursors::Default;
			break;
		}
	  case 1:	//
		{
			lBprocess->Items->Clear();
			lBthread->Items->Clear();
//			p = Process::GetProcesses();

//			for (int i=0; i < p GetLenght(0); i++)
//			 {
//				 lBprocess->Items->Add( String::Format("{0} [hC: {1}, tC: {2}]" p[i]->ProcessName, p[i]->HandleCount, p[i]->Threads->Count );
//			 }


			//

			break;
		}

	  case 2:	//
		{
			//
			break;
		}

	  case 3:	//
		{
			//
			break;
		}

	  case 4:	// process and threads
		{

			//
			break;
		}


	 }
 }




/*



static ProcessThread [] GetProcessThreads(int nProcID)
{
	try
   {
      Process* proc = Process.GetProcessById (nProcID);
      ProcessThread [] threads = proc.Threads;
      return threads;
   }
   catch (Exception* e)
   {
      Console.WriteLine (e.Message);
      return NULL;
   }







*/







}