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

using namespace Vaca;

void configure_frame(Frame& frame);
void configure_editor(TextEdit& edit, Font& normalFont, Font& hotFont, int preferredWidth);
void configure_num_editor(TextEdit& edit);
void configure_buttons(Button& ok, Button& cancel);
void filter_num_keys(KeyEvent& ev);
void msg_ok(Widget* owner);

int VACA_MAIN()
{
  Application application;

  // creates a Dialog that looks like a Frame
  Dialog frame(L"Like a script", NULL,
	       Dialog::Styles::Default
	       + Frame::Styles::Resizable
	       + Frame::Styles::Minimizable
	       + Frame::Styles::Maximizable);

  Label firstNameLabel(L"First name:", &frame);
  Label lastNameLabel(L"Last name:", &frame);
  Label ageLabel(L"Age:", &frame);
  TextEdit firstName(L"", &frame);
  TextEdit lastName(L"", &frame);
  TextEdit age(L"", &frame, TextEdit::Styles::Default +
			    TextEdit::Styles::RightAligned);
  Button ok(L"&OK", &frame);
  Button cancel(L"&Cancel", &frame);
  Font font1(L"Courier New", 10);
  Font font2(L"Courier New", 10, FontStyle::Bold);

  try {
    frame.setLayout(Bix::parse(L"Y[XY[%,fx%;%,fx%;%,fxX[%,fX[]]],X[f,exX[%,%]]]",
			       &firstNameLabel, &firstName,
			       &lastNameLabel, &lastName,
			       &ageLabel, &age,
			       &ok, &cancel));
  } catch (ParseException &e) {
    MsgBox::show(&frame, L"Bix::parse Error",
		 convert_to<String>(e.what()));
    return 0;
  }

  configure_frame(frame);
  configure_editor(firstName, font1, font2, 256);
  configure_editor(lastName, font1, font2, 256);
  configure_editor(age, font1, font2, 64);
  configure_num_editor(age);
  configure_buttons(ok, cancel);

  frame.setSize(frame.getPreferredSize());
  frame.center();
  frame.setVisible(true);

  application.run();
  return 0;
}

struct limit_frame_resizing
{
  Frame* f;
  limit_frame_resizing(Frame* f) : f(f) { }
  void operator()(CardinalDirection dir, Rect& rc) {
    Rect bounds = f->getBounds();
    rc = Rect(rc.x, bounds.y, rc.w, bounds.h);
  }
};

void configure_frame(Frame &frame)
{
  frame.Resizing.connect(limit_frame_resizing(&frame));
}

void configure_editor(TextEdit &edit, Font &normalFont, Font &hotFont, int preferredWidth)
{
  edit.FocusEnter.connect(Bind(&Widget::setFont, &edit, hotFont));
  edit.FocusLeave.connect(Bind(&Widget::setFont, &edit, normalFont));

  edit.MouseEnter.connect(Bind(&Widget::setBgColor, &edit, Color(255, 255, 190)));
  edit.MouseLeave.connect(Bind(&Widget::setBgColor, &edit, Color::White));
  edit.MouseEnter.connect(Bind(&Widget::invalidate, &edit, true));
  edit.MouseLeave.connect(Bind(&Widget::invalidate, &edit, true));

  edit.setFont(normalFont);
  edit.setPreferredSize(Size(preferredWidth, edit.getPreferredSize().h));
}

void configure_num_editor(TextEdit &edit)
{
  edit.KeyDown.connect(&filter_num_keys);
}

void configure_buttons(Button& ok, Button& cancel)
{
  ok.Click.connect(Bind<void>(&msg_ok, ok.getParent()));
  ok.Click.connect(Bind(&Widget::setVisible, ok.getParent(), false));
  cancel.Click.connect(Bind(&Widget::setVisible, cancel.getParent(), false));
}

void filter_num_keys(KeyEvent &ev)
{
  if ((ev.getCharCode() != 0) &&
      !(ev.getCharCode() >= '0' && ev.getCharCode() <= '9') &&
      (ev.getCharCode() >= ' ')) {
    ev.consume();
  }
}

void msg_ok(Widget* owner)
{
  MsgBox::show(owner, L"OK", L"You press the OK button");
}
