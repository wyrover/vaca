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

#include "Vaca/FindFiles.h"
#include "Vaca/String.h"

using namespace Vaca;

FindFiles::FindFiles(const String& pattern)
{
  m_pattern = pattern;
  m_handle = NULL;
}

FindFiles::~FindFiles()
{
  if (m_handle)
    FindClose(m_handle);
 }

bool FindFiles::next()
{
  if (!m_handle) {
    m_handle = FindFirstFile(m_pattern.c_str(), &m_data);
    return m_handle ? true: false;
  }
  else {
    return FindNextFile(m_handle, &m_data) ? true: false; 
  }
}

String FindFiles::getFileName() const
{
    return m_data.cFileName;
}

String FindFiles::getFullFileName() const
{
  return file_path(m_pattern) / m_data.cFileName;
}

bool FindFiles::isFile() const
{
    return m_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ? false: true;
}

bool FindFiles::isDirectory() const
{
  return m_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ? true: false;
}
