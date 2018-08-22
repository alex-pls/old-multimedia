#include "stdafx.h"
#include "Form1.h"
#include "splashForm.h"
#include <windows.h>

using namespace System::Threading;
using namespace System::Windows::Forms;
using namespace vipWS3;

__gc class CSingleInstance
 {
	private:

		Mutex* m_mutex;

	public:

		CSingleInstance(String* mutexName)
		 {
			m_mutex = new Mutex(false, mutexName);
		 }

		~CSingleInstance()
		 {
			m_mutex->ReleaseMutex();
		 }

		bool isRunning()
		 {
			return !m_mutex->WaitOne(10, true);
		 }
 };


int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
//	CSingleInstance* si = new CSingleInstance("{VIPLib-WORKSHOP-05101-2005-e5n793jf932}");
//	if ( si->isRunning() )
//	 {
//		 MessageBox::Show("You are allowed to open only one instance of VIPLib WorkShop", "VIPLib WorkShop");
//		 return 1;
//	 }


	Thread::CurrentThread->ApartmentState = ApartmentState::STA;
	Thread* InstanceCaller = new Thread(new ThreadStart(0, splashForm::newInstance));
	InstanceCaller->Start();
//	Thread::Sleep(2000);
	Application::Run(new Form1());
	return 0;
}



/*
void Form1::FormLoad(Object *Sender, EventArgs *Args)
{
	childForm *OC = new childForm();
	OC->MdiParent = this;
	OC->Show();
}
*/


