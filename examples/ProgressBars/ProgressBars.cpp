// Vaca - Visual Application Components Abstraction
// Copyright (c) 2005-2009 David Capello
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

#include <Vaca/Vaca.h>
#include "../resource.h"

using namespace Vaca;

// To control a progress bar that can be paused, it's a little tricky:
// We need a state-machine and to use a custom loop (see "The Loop"
// below) to pump the message queue while we do the "real work"
class MainFrame : public Dialog
{
  // possible states
  enum State {
    WaitingToWork,
    Working,
    Paused,
    WorkDone,
    Aborting
  };

  ProgressBar m_progressBar1;	// normal progress bar
  ProgressBar m_progressBar2;	// smooth progress bar
  ProgressBar m_progressBar3;	// marquee progress bar
  Button m_start;
  Button m_close;
  State m_state;			// current state

public:

  MainFrame()
    : Dialog(L"ProgressBars")
    , m_progressBar1(this)
    , m_progressBar2(this, ProgressBar::Styles::Default +
			   ProgressBar::Styles::Smooth)
    , m_progressBar3(this, ProgressBar::Styles::Default +
			   ProgressBar::Styles::Marquee)
    , m_start(L"Start", this)
    , m_close(L"Close", this)
  {
    // a box layout manager with vertical orientation and no-homogeneous
    setLayout(new BoxLayout(Orientation::Vertical, false));

    // set the ranges of the progress bars
    m_progressBar1.setRange(0, 100);
    m_progressBar2.setRange(0, 100);
    m_progressBar3.setMarquee(0);

    // the "Start" button is the default one
    m_start.setDefault(true);

    // call "onStart" when the "Start" button is pressed
    m_start.Click.connect(Bind(&MainFrame::onStart, this));

    // the Dialog::onCancel generates an onClose event
    m_close.Click.connect(Bind(&MainFrame::onCancel, this));

    // the application is waiting to work (the user should press the
    // "Start" button)
    m_state = WaitingToWork;

    // set the size of the Frame
    setSize(Size(256, getPreferredSize().h));
    center();
  }

protected:

  // when the "Start/Pause/Continue/Restart" button is pressed...
  void onStart()
  {
    switch (m_state) {

      // The user pressed Start/Continue...
      case WaitingToWork:
      case Paused: {
	m_state = Working;
	m_start.setText(L"Pause"); // convert the button to "Pause"...
	m_progressBar3.setMarquee(100);

	// this is "The Loop", where the real work is done
	do {
	  // when we pump the message queue, we can get events like onClose()
	  CurrentThread::pumpMessageQueue();

	  // work done
	  if (m_progressBar1.getValue() == m_progressBar1.getMaximum()) {
	    m_state = WorkDone;
	    m_start.setText(L"Restart"); // convert the button to "Restart"
	  }
	  else {
	    m_progressBar1.addValue(1);
	    m_progressBar2.addValue(1);

	    // in our case, the "real work" is sleep :) ...but for
	    // your application this could be "loading a file"...
	    Sleep(100);
	  }

	  // still working?
	} while (m_state == Working);

	// aborting work? hide the frame...
	if (m_state == Aborting)
	  setVisible(false);

	m_progressBar3.setMarquee(0);
	break;
      }

      // The user pressed Pause...
      case Working:
	m_state = Paused;
	m_start.setText(L"Continue"); // convert the button to "Continue"
	break;

      // The user pressed Restart...
      case WorkDone:
	// restart progress bars
	m_progressBar1.setValue(m_progressBar1.getMinimum());
	m_progressBar2.setValue(m_progressBar2.getMinimum());
	m_progressBar3.setMarquee(0);
	m_start.setText(L"Start"); // convert the button to "Start"
	m_state = WaitingToWork;
	break;

      case Aborting:
	assert(false);		// impossible
	break;
    }
  }

  virtual void onClose(CloseEvent &ev)
  {
    Dialog::onClose(ev);

    // work in progress? (we are in "The Loop")
    if (m_state == Working) {
      // display a warning message
      if (MsgBox::show(this, L"Warning",
		       L"The application is working.\r\n"
		       L"Do you really want to close it?",
		       MsgBox::Type::YesNo,
		       MsgBox::Icon::Warning, 2) == MsgBox::Result::Yes) {
	// the user really want to close the window, abort the work
	m_state = Aborting;
      }

      // cancel the close event, don't hide the Dialog
      ev.cancel();
    }
    // need more time?
    else if (m_state == Paused) {
      // display a warning message
      if (MsgBox::show(this, L"Warning",
		       L"The application is paused, but doesn't finish its work.\r\n"
		       L"Do you really want to close it?",
		       MsgBox::Type::YesNo,
		       MsgBox::Icon::Warning, 2) == MsgBox::Result::Yes) {
	// hide the dialog... (not canceling the event)
      }
      else
	// cancel the close event, don't hide the Dialog
	ev.cancel();
    }
    else {
      // the work is done (or never start), hide the Dialog... (not canceling the event)
    }
  }

};

//////////////////////////////////////////////////////////////////////

int VACA_MAIN()
{
  Application app;
  MainFrame frm;
  frm.setIcon(ResourceId(IDI_VACA));
  frm.setVisible(true);
  app.run();
  return 0;
}
