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

#ifndef VACA_SYSTEM_H
#define VACA_SYSTEM_H

#include "Vaca/base.h"
#include "Vaca/Rect.h"
#include "Vaca/Keys.h"

#include <vector>
#include <shlobj.h>

namespace Vaca {

/**
   Class to access to operating system information.

   It is more like a namespace than a class, because all member
   functions are static.
*/
class VACA_DLL System
{
public:

  static void println(String line);
  static void printf(LPCTSTR fmt, ...);
  static void print(String buf);

  static String getCurrentDirectory();
  static String getWindowsDirectory();
  static String getShellFolderPath(int folderCsidl, bool create);

  static ImageList getImageList();
  static ImageList getSmallImageList();
  static int getFileImageIndex(const String& fileName, bool smallImage);

  static Size getScreenSize();
  static Rect getWorkAreaBounds();

  static Color getColor(int index);

  static bool getKeyState(Keys::Type);
  static Point getCursorPos();
  static void setCursorPos(const Point& pt);

  static String getUserName();
  static String getFriendlyUserName();

  //static int getWheelScrollLines();

};

} // namespace Vaca

#endif // VACA_SYSTEM_H
