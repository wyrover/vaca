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

#ifndef VACA_COMMAND_H
#define VACA_COMMAND_H

#include "Vaca/base.h"
#include "Vaca/NonCopyable.h"
#include "Vaca/Signal.h"

#include <vector>

namespace Vaca {

/**
   A command, action or function of the application.

   @see CommandId
*/
class VACA_DLL Command : private NonCopyable
{
  CommandId m_id;

public:
  Command(CommandId id);
  virtual ~Command();

  CommandId getId() const { return m_id; }

  virtual void execute() = 0;

  virtual bool isEnabled() { return true; }
  virtual bool isChecked() { return false; }
};

/**
   Specialization of Command class to handle the
   Command#execute and Command#isEnabled
   as @link page_mess_signals signals@endlink.
*/
class SignalCommand : public Command
{
public:

  /**
     Creates a new SignalCommand without slots in signals.

     \param id
       Command ID that will be handled by this SignalCommand.
   */
  SignalCommand(CommandId id) : Command(id) { }

  /**
     Creates a new SignalCommand with the specified functor .

     \param id
       Command ID that will be handled by this SignalCommand.

     \param f
       Functor to be called when the command is executed.
   */
  template<typename F>
  SignalCommand(CommandId id, const F& f) : Command(id) {
    Execute.connect(f);
  }

  /**
     Creates a new SignalCommand with the specified functor .

     \param id
       Command ID that will be handled by this SignalCommand.

     \param m
       Member function of the T class to be called when the command is executed.

     \param t
       Instance of T class to be used when the member function is called.
   */
  template<class T>
  SignalCommand(CommandId id, void (T::*m)(), T* t) : Command(id) {
    Execute.connect(m, t);
  }

  virtual ~SignalCommand() { }

  virtual void execute() { Execute(); }

  virtual bool isEnabled() {
    return Enabled(true);	// true by default
  }

  virtual bool isChecked() {
    return Checked(false);	// false by default
  }

  Signal0<void> Execute;
  Signal0<bool> Enabled;
  Signal0<bool> Checked;
};

/**
   An object that contains commands (Application).
*/
class VACA_DLL CommandsClient
{
  std::vector<Command*> m_commands;

public:
  CommandsClient();
  virtual ~CommandsClient();

  void addCommand(Command* cmd);
  Command* removeCommand(Command* cmd);
  Command* getCommandById(CommandId id) const;
};

} // namespace Vaca

#endif // VACA_COMMAND_H
