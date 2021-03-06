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

#ifndef EDITOR_H
#define EDITOR_H

#include <Vaca/Vaca.h>
#include "Document.h"

using namespace Vaca;

// Document's view
class Editor : public Widget
{
  DocumentPtr m_doc;
  Font m_font;
  DocPos m_caret;
  bool m_caretVisible;
  Timer m_caretBlink;
  const DocPos max_length;
  
public:

  Editor(Widget* parent)
    : Widget(parent, Widget::Styles::Default |
		     Widget::Styles::Focusable)
    , m_doc(NULL)
    , m_font(L"Courier New", 24)
    , m_caret(0)
    , m_caretVisible(true)
    , m_caretBlink(750)
    , max_length(10)
  {
    setBgColor(Color::White);
    setDoubleBuffered(true);
    setFont(m_font);

    m_caretBlink.Tick.connect(&Editor::toggleCaretVisibility, this);
    m_caretBlink.start();

    setPreferredSize(Size(32*max_length, 32));
    requestFocus();
  }

  void setDocument(DocumentPtr doc) {
    m_doc = doc;
    m_caret = doc ? doc->size(): 0;
    makeCaretVisible();
  }

  void goBeginOfLine() {
    m_caret = 0;
    makeCaretVisible();
  }

  void goEndOfLine() {
    m_caret = m_doc->size();
    makeCaretVisible();
  }

  void goPreviousChar() {
    if (m_caret > 0)
      m_caret--;
    makeCaretVisible();
  }

  void goNextChar() {
    if (m_caret < m_doc->size())
      m_caret++;
    makeCaretVisible();
  }

  void removePreviousChar() {
    if (m_caret > 0)
      m_doc->remove(--m_caret, 1);
    makeCaretVisible();
  }

  void removeNextChar() {
    if (m_caret < m_doc->size())
      m_doc->remove(m_caret, 1);
    makeCaretVisible();
  }

  void writeChar(Char chr) {
    if (m_doc->size() < max_length)
      m_doc->add(m_caret++, chr);
    makeCaretVisible();
  }

protected:

  virtual void onPaint(PaintEvent& ev)
  {
    Graphics& g = ev.getGraphics();
    Rect rc(getClientBounds());
    Pen blackPen(Color::Black);
    Pen bluePen(Color::Blue);
    Pen grayPen(Color(192, 192, 192), 1, PenStyle::Dot);
    Size celBox(32, 32);
    Point origPt = rc.getCenter() - Point(celBox.w*max_length, celBox.h)/2;
    String tmp(1, L'\0');

    g.drawRoundRect(grayPen,
		    Rect(origPt, Size(celBox.w*max_length, celBox.h)),
		    Size(6, 6));
    if (m_doc) {
      for (DocPos i=0; i<m_doc->size(); ++i) {
	int x = origPt.x+i*celBox.w;

	g.drawRoundRect(blackPen,
			Rect(Point(x, origPt.y), celBox),
			Size(6, 6));

	tmp[0] = m_doc->at(i);

	g.drawString(tmp, Color::Black,
		     Point(x, origPt.y) + Point(celBox)/2 - Point(g.measureString(tmp))/2);
      }

      // draw the caret
      if (m_caretVisible) {
	int x = origPt.x + m_caret*celBox.w;
	g.drawLine(bluePen,
		   Point(x, origPt.y-8),
		   Point(x, origPt.y+celBox.h+8));
      }
    }
    else {
      g.drawString(L"No document", Color::Black, rc);
    }
  }

  virtual void onKeyDown(KeyEvent& ev)
  {
    Widget::onKeyDown(ev);

    if (m_doc) {
      switch (ev.getKeyCode()) {
	case Keys::Home: goBeginOfLine(); break;
	case Keys::End: goEndOfLine(); break;
	case Keys::Left: goPreviousChar(); break;
	case Keys::Right: goNextChar(); break;
	case Keys::Back: removePreviousChar(); break;
	case Keys::Delete: removeNextChar(); break;
	default:
	  if (ev.getCharCode() >= ' ') {
	    writeChar(ev.getCharCode());
	    break;
	  }
	  break;
      }
    }
  }

private:

  void toggleCaretVisibility()
  {
    m_caretVisible = !m_caretVisible;
    invalidate(true);
  }

  void makeCaretVisible()
  {
    m_caretVisible = true;
    m_caretBlink.start();	// restart timer
    invalidate(true);
  }
  
};

#endif // EDITOR_H
