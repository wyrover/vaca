// Vaca - Visual Application Components Abstraction
// Copyright (c) 2005-2010 David Capello
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
// * Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in
//   the documentation and/or other materials provided with the
//   distribution.
// * Neither the name of the author nor the names of its contributors
//   may be used to endorse or promote products derived from this
//   software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
// COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
// OF THE POSSIBILITY OF SUCH DAMAGE.

#include "Vaca/Application.h"
#include "Vaca/Debug.h"
#include "Vaca/Frame.h"
#include "Vaca/Timer.h"
#include "Vaca/Graphics.h"
#include "Vaca/Font.h"

#ifndef NDEBUG
#include "Vaca/System.h"
#endif

using namespace Vaca;

HINSTANCE Application::m_HINSTANCE = NULL;
Application* Application::m_instance = NULL;
std::vector<String> Application::m_args;

/**
   Initializes the variables of the Application class.

   @win32
     It calls @msdn{CoInitialize} and @msdn{InitCommonControls}.
   @endwin32

   @see run
*/
Application::Application()
  : Thread()
{
  assert(Application::m_HINSTANCE == NULL);
  assert(Application::m_instance == NULL);

  CoInitialize(NULL);

  Application::m_HINSTANCE = ::GetModuleHandle(NULL);
  Application::m_instance = this;

  INITCOMMONCONTROLSEX icce;
  icce.dwSize = sizeof(INITCOMMONCONTROLSEX);
  icce.dwICC = 0
    | ICC_WIN95_CLASSES
    | ICC_BAR_CLASSES
    | ICC_COOL_CLASSES
    ;

  InitCommonControlsEx(&icce);

  VACA_TRACE("Application started\n");
}

/**
   Finishes the application.

   @win32
     It calls @msdn{CoUninitialize}.
   @endwin32
*/
Application::~Application()
{
  assert(Application::m_HINSTANCE != NULL);
  assert(Application::m_instance == this);

  Timer::stop_timer_thread();

  Application::m_HINSTANCE = NULL;
  Application::m_instance = NULL;

#ifndef NDEBUG
  Referenceable::showLeaks();
#endif

  VACA_TRACE("Application finished\n");

  // close the log file
  details::removeAllThreadData();
  details::closeLogFile();

  CoUninitialize();

#ifdef MEMORY_LEAK_DETECTOR
  atexit(check_leaks);
#endif
}

size_t Application::getArgc()
{
  return m_args.size();
}

const String& Application::getArgv(size_t i)
{
  return m_args[i];
}

/**
   Returns the parameters in the command line.

   @c Application::getArgs()[0] is the name of the executable file.
*/
const std::vector<String>& Application::getArgs()
{
  return m_args;
}

void Application::setArgs(const std::vector<String>& args)
{
  m_args = args;
}

/**
   Returns the Application's singleton.

   A program using Vaca must have one instance of Applicaton or a
   class derived from it.
*/
Application* Application::getInstance()
{
  return m_instance;
}

/**
   Returns the Win32's @c HINSTANCE.

   @win32
     HINSTANCE handles are specific of Windows.
   @endwin32

   @internal
*/
HINSTANCE Application::getHandle()
{
  return Application::m_HINSTANCE;
}

/**
   Changes the priority of the process respecting to all other
   processes currently running on the operating system.

   @see Thread#setThreadPriority
*/
void Application::setProcessPriority(ProcessPriority priority)
{
  int nPriority;
  switch (priority) {
    case ProcessPriority::Idle:     nPriority = IDLE_PRIORITY_CLASS; break;
    case ProcessPriority::Normal:   nPriority = NORMAL_PRIORITY_CLASS; break;
    case ProcessPriority::High:     nPriority = HIGH_PRIORITY_CLASS; break;
    case ProcessPriority::RealTime: nPriority = REALTIME_PRIORITY_CLASS; break;
    default:
      assert(false);	      // TODO throw invalid argument exception
      return;
  }
  ::SetPriorityClass(::GetCurrentProcess(), nPriority);
}

/**
   The common way to start the application.

   You should call this member function from @e WinMain,
   using the Application instance.

   The work of this routine is really simple: it calls #main and then
   CurrentThread#doMessageLoop. You can make your own class derived from
   Application and override #main so you can customized the
   initialization (e.g. show a Frame).

   Example:
   @code
   int VACA_MAIN()
   {
     Application app;
     Frame frm("My frame");
     frm.setVisible(true);
     app.run();
     return 0;
   }
   @endcode

   The same example with a variation:
   @code
   class MyApp : public Application
   {
     Frame frm;
   public:
     MyApp() : frm("My frame") { }

     virtual void main() {
       frm.setVisible(true);
     }
   };
   int VACA_MAIN()
   {
     MyApp app;
     app.run();
     return 0;
   }
   @endcode

   @see CurrentThread#doMessageLoop
*/
void Application::run()
{
  main();
  CurrentThread::doMessageLoop();
}

/**
   The application entry point.

   After calling #run, #main is executed and when it finishes, the
   CurrentThread#doMessageLoop is automatically invoked (to process
   messages for visible @link Frame frames@endlink).
*/
void Application::main()
{
  // do nothing
}
