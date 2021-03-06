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

#ifndef VACA_LINKLABEL_H
#define VACA_LINKLABEL_H

#include "Vaca/base.h"
#include "Vaca/CustomLabel.h"

namespace Vaca {

/**
   A link to Internet (or whatever you want).
*/
class VACA_DLL LinkLabel : public CustomLabel
{
  enum State {
    Outside,
    Inside,
    Hover
  };

  State m_state;
  String m_url;
  Font m_underlineFont;
  Image* m_image;

public:

  struct VACA_DLL Styles {
    static const Style Default;
  };

  LinkLabel(const String& urlOrText, Widget* parent, Style style = Styles::Default);
  LinkLabel(const String& url, const String& text, Widget* parent, Style style = Styles::Default);
  LinkLabel(const String& url, Image& image, Widget* parent, Style style = Styles::Default);
  virtual ~LinkLabel();

  virtual void setFont(Font font);

  virtual Color getLinkColor();
  virtual Color getHoverColor();

  Signal1<void, Event&> Click; ///< @see onClick

protected:

  // Events
  virtual void onPreferredSize(PreferredSizeEvent& ev);
  virtual void onPaint(PaintEvent& ev);
  virtual void onMouseEnter(MouseEvent& ev);
  virtual void onMouseMove(MouseEvent& ev);
  virtual void onMouseLeave(MouseEvent& ev);
  virtual void onMouseDown(MouseEvent& ev);
  virtual void onSetCursor(SetCursorEvent& ev);
//   virtual void onResize(ResizeEvent& ev);
  virtual void onFocusEnter(FocusEvent& ev);
  virtual void onFocusLeave(FocusEvent& ev);
  virtual void onKeyDown(KeyEvent& ev);

  // New events
  virtual void onClick(Event& ev);

private:

  void init(String text, Image* image = NULL);
  void click();
  void updateFont(const Font& font);
  Rect getLinkBounds(Graphics& g);

};

} // namespace Vaca

#endif // VACA_LINKLABEL_H
