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

#ifndef VACA_MDI_H
#define VACA_MDI_H

#include "Vaca/base.h"
#include "Vaca/Frame.h"

namespace Vaca {

/**
   ID for the first MdiChild. These IDs are used internally by Win32
   and the MdiListMenu.
*/
#define VACA_FIRST_MDICHILD 0xff00

/**
   Represents the Win32 class used by MdiChild.
*/
class MdiChildClass : public WidgetClass
{
public:
  static WidgetClassName getClassName()
  { return WidgetClassName(L"Vaca.MdiChild"); }
};

/**
   Controls a child window for a MdiClient. Represent a Frame inside a
   MdiClient.
*/
class VACA_DLL MdiChild : public Register<MdiChildClass>, public Frame
{
  void initialize();

public:

  struct VACA_DLL Styles {
    static const Style Default;
  };

  MdiChild(const String& title, MdiClient* parent, Style style = Styles::Default);
  MdiChild(const String& title, MdiFrame* parent, Style style = Styles::Default);
  virtual ~MdiChild();

protected:
  // Reflected notifications
  // virtual bool onReflectedCommand(int id, int code, LRESULT& lResult);

  virtual bool wndProc(UINT message, WPARAM wParam, LPARAM lParam, LRESULT& lResult);
//   virtual LRESULT defWndProc(UINT message, WPARAM wParam, LPARAM lParam);

private:
//   virtual void destroyHWND(HWND hwnd);
};

/**
   Widget which its client area contains MdiChild windows.
*/
class VACA_DLL MdiClient : public Widget
{
public:

  struct VACA_DLL Styles {
    static const Style Default;
  };

  MdiClient(Widget* parent, Style style = Styles::Default);
  virtual ~MdiClient();

  void cascade();
  void tileHorizontal();
  void tileVertical();
  void arrangeIcons();

  MdiChild* getActive();
  void activate(MdiChild* mdiChild);
  void activateNext(MdiChild* mdiChild = NULL);
  void activatePrevious(MdiChild* mdiChild = NULL);

  MdiChild* getChildById(int wID);

  // void maximize(MdiChild* window);
  // void restore(MdiChild* window);

  virtual bool preTranslateMessage(Message& message);

private:
  virtual HWND createHandle(LPCTSTR className, Widget* parent, Style style);
};

/**
   Default implementation to use the MDI interface.

   You can use this kind of Frame when you want MDI applications.

   @win32
     It takes care of a MdiClient and uses the @msdn{DefFrameProc} of
     the Windows API as default message handler.
   @endwin32
*/
class VACA_DLL MdiFrame : public Frame
{
  friend class Frame;

private:

  MdiClient* m_mdiClient;

public:

  struct VACA_DLL Styles {
    static const Style Default;
  };

  MdiFrame(const String& title, Widget* parent = NULL, Style style = Styles::Default,
	   bool customMdiClient = false);
//   MdiFrame(Widget* parent, Style style = ChildStyle); // TODO ChildStyle???
  virtual ~MdiFrame();

  MdiClient* getMdiClient();
  MdiClient* setMdiClient(MdiClient* mdiClient);

  virtual MenuBar* setMenuBar(MenuBar* menubar);
  void refreshMenuBar();

protected:
  virtual bool wndProc(UINT message, WPARAM wParam, LPARAM lParam, LRESULT& lResult);
//   virtual LRESULT defWndProc(UINT message, WPARAM wParam, LPARAM lParam);
};


} // namespace Vaca

#endif // VACA_MDI_H
