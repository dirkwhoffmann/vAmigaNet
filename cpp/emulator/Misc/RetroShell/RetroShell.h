// -----------------------------------------------------------------------------
// This file is part of vAmiga
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the GNU General Public License v3
//
// See https://www.gnu.org for license information
// -----------------------------------------------------------------------------

#pragma once

#include "RetroShellTypes.h"
#include "SubComponent.h"
#include "Interpreter.h"
#include "TextStorage.h"
#include <sstream>
#include <fstream>

namespace vamiga {

class RetroShell : public SubComponent {

    friend class RshServer;
    friend class Interpreter;
    
    // The command interpreter (parses commands typed into the console window)
    Interpreter interpreter;

    
    //
    // Text storage
    //
    
    // The text storage
    TextStorage storage;

    // History buffer storing old input strings and cursor positions
    std::vector<std::pair<string,isize>> history;
    
    // The currently active input string
    isize ipos = 0;

    
    //
    // User input
    //
    
    // Input line
    string input;

    // Input prompt
    string prompt = "vAmiga% ";

    // Cursor position
    isize cursor = 0;
    
    // Indicates if TAB was the most recently pressed key
    bool tabPressed = false;

    
    //
    // Scripts
    //
    
    // The currently processed script
    std::stringstream script;
    
    // The script line counter (first line = 1)
    isize scriptLine = 0;

    // Wake up cycle for interrupted scripts
    Cycle wakeUp = INT64_MAX;

    
    //
    // Initializing
    //
    
public:
    
    RetroShell(Amiga& ref);

    
    //
    // Methods from CoreObject
    //
    
private:
    
    const char *getDescription() const override { return "RetroShell"; }
    void _dump(Category category, std::ostream& os) const override { }
    
    
    //
    // Methods from CoreComponent
    //
    
private:
    
    void _initialize() override;
    void _reset(bool hard) override { }
    void _pause() override;
    isize _size() override { return 0; }
    u64 _checksum() override { return 0; }
    isize _load(const u8 *buffer) override {return 0; }
    isize _save(u8 *buffer) override { return 0; }


    //
    // Working with the text storage
    //

public:

    // Prints a message
    RetroShell &operator<<(char value);
    RetroShell &operator<<(const string &value);
    RetroShell &operator<<(int value);
    RetroShell &operator<<(long value);
    RetroShell &operator<<(std::stringstream &stream);

    // Returns the prompt
    const string &getPrompt();

    // Updates the prompt according to the current shell mode
    void updatePrompt();
    
    // Returns the contents of the whole storage as a single C string
    const char *text();

    // Moves the cursor forward to a certain column
    void tab(isize pos);

    // Assigns an additional output stream
    void setStream(std::ostream &os);

    // Clears the console window
    void clear();

    // Prints the welcome message
    void welcome();

    // Prints the help line
    void printHelp();

    // Prints a state summary (used by the debug shell)
    void printState();

private:

    // Marks the text storage as dirty
    void needsDisplay();

    
    //
    // Managing user input
    //

public:

    // Returns the size of the current user-input string
    isize inputLength() { return (isize)input.length(); }
    
    // Presses a key or a series of keys
    void press(RetroShellKey key, bool shift = false);
    void press(char c);
    void press(const string &s);
    
    // Returns the cursor position relative to the line end
    isize cursorRel();
    

    //
    // Working with the history buffer
    //

public:
    
    isize historyLength() { return (isize)history.size(); }


    
    //
    // Executing commands
    //
    
public:
    
    // Main entry point for executing commands that were typed in by the user
    void execUserCommand(const string &command);

    // Executes a command
    void exec(const string &command) throws;

    // Executes a shell script
    void execScript(std::ifstream &fs) throws;
    void execScript(const string &contents) throws;

    // Continues a previously interrupted script
    void continueScript() throws;

private:

    // Prints a textual description of an error in the console
    void describe(const std::exception &exception);

    // Prints a help message for a given command string
    void help(const string &command);
    
    
    //
    // Command handlers
    //
    
public:
    
    void dump(CoreObject &component, std::vector <Category> categories);
    void dump(CoreObject &component, Category category);

private:

    void _dump(CoreObject &component, Category category);

    
    //
    // Performing periodic events
    //
    
public:
    
    void eofHandler();
};

}
