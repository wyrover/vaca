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

#ifndef VACA_WIN32_H
#define VACA_WIN32_H

#include "Vaca/base.h"

#ifndef VACA_ON_WINDOWS
  #error You cannot use this header file outside Windows platform.
#endif

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace Vaca {

  template<> VACA_DLL POINT convert_to(const Point& pt);
  template<> VACA_DLL Point convert_to(const POINT& pt);
  template<> VACA_DLL Point convert_to(const POINTS& pt);
  template<> VACA_DLL SIZE convert_to(const Size& sz);
  template<> VACA_DLL Size convert_to(const SIZE& sz);
  template<> VACA_DLL RECT convert_to(const Rect& rc);
  template<> VACA_DLL Rect convert_to(const RECT& rc);

  template<> VACA_DLL COLORREF convert_to(const Color& color);
  template<> VACA_DLL Color convert_to(const COLORREF& colorref);

  template<> VACA_DLL HPEN convert_to(const Pen& pen);
  template<> VACA_DLL HBRUSH convert_to(const Brush& brush);

}

#endif // VACA_WIN32_H
