/**
 *  @brief   MAIN
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


#include "stdafx.h"
#include "vipPKStudio.h"
#include "splashForm.h"
#include <windows.h>

using namespace System::Threading;
using namespace System::Windows::Forms;
using namespace vipPS;

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
	Thread::CurrentThread->ApartmentState = ApartmentState::STA;
	splashForm::newInstance();
	Thread* InstanceCaller = new Thread(new ThreadStart(0, splashForm::runInstance));
	InstanceCaller->Start();
	Thread::Sleep(3000);
	Application::Run(new vipPKStudio());
	return 0;
}
