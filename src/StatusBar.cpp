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

#include "Vaca/StatusBar.h"
#include "Vaca/WidgetClass.h"
#include "Vaca/PreferredSizeEvent.h"
#include "Vaca/LayoutEvent.h"

using namespace Vaca;

StatusBar::StatusBar(Widget* parent, Style style)
  : Widget(WidgetClassName(STATUSCLASSNAME), parent, style)
{
}

StatusBar::~StatusBar()
{
}

/**
   A status bar is arranged by a Frame, but doesn't depend of the
   current Layout manager in that Frame.
*/
bool StatusBar::isLayoutFree() const
{
  return true;
}

void StatusBar::onPreferredSize(PreferredSizeEvent& ev)
{
  ev.setPreferredSize(0, 24);
}

void StatusBar::onLayout(LayoutEvent& ev)
{
  Rect rc = ev.getBounds();
  Size pref = getPreferredSize();

  setBounds(Rect(rc.x, rc.y+rc.h-pref.h, rc.w, pref.h));

  rc.h -= pref.h;
  ev.setBounds(rc);

  Widget::onLayout(ev);
}
