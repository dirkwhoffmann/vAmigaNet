// -----------------------------------------------------------------------------
// This file is part of vAmiga
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the GNU General Public License v3
//
// See https://www.gnu.org for license information
// -----------------------------------------------------------------------------

#include "config.h"
#include "Command.h"
#include <algorithm>
#include <utility>

namespace vamiga {

std::vector<string> Command::groups;

void
Command::newGroup(const string &description, const string &postfix)
{
    groups.push_back(description.empty() ? "" : description + postfix);
}

void
Command::add(const std::vector<string> &tokens,
             const string &help)
{
    add(tokens, help, nullptr);
}

void
Command::add(const std::vector<string> &tokens,
             const string &help,
             std::function<void (Arguments&, long)> func, long param)
{
    add(tokens, { }, { }, help, func, param);
}

void
Command::add(const std::vector<string> &tokens,
             const std::vector<string> &arguments,
             const string &help,
             std::function<void (Arguments&, long)> func, long param)
{
    add(tokens, arguments, { }, help, func, param);
}

void
Command::add(const std::vector<string> &tokens,
             const std::vector<string> &requiredArgs,
             const std::vector<string> &optionalArgs,
             const string &help,
             std::function<void (Arguments&, long)> func, long param)
{
    assert(!tokens.empty());

    // Traverse the node tree
    Command *cmd = seek(std::vector<string> { tokens.begin(), tokens.end() - 1 });
    assert(cmd != nullptr);

    // Create the instruction
    Command d;
    d.name = tokens.back();
    d.fullName = (cmd->fullName.empty() ? "" : cmd->fullName + " ") + tokens.back();
    d.group = isize(groups.size()) - 1;
    d.requiredArgs = requiredArgs;
    d.optionalArgs = optionalArgs;
    d.help = help;
    d.callback = func;
    d.param = param;
    d.hidden = help.empty() || help.at(0) == '*';

    // Register the instruction
    cmd->subCommands.push_back(d);
}

const Command *
Command::seek(const string& token) const
{
    for (auto &it : subCommands) {
        if (it.name == token) return &it;
    }
    return nullptr;
}

Command *
Command::seek(const string& token)
{
    return const_cast<Command *>(std::as_const(*this).seek(token));
}

const Command *
Command::seek(const std::vector<string> &tokens) const
{
    const Command *result = this;
    
    for (auto &it : tokens) {
        if ((result = result->seek(it)) == nullptr) break;
    }
    
    return result;
}

Command *
Command::seek(const std::vector<string> &tokens)
{
    return const_cast<Command *>(std::as_const(*this).seek(tokens));
}

std::vector<const Command *>
Command::filterPrefix(const string& prefix) const
{
    std::vector<const Command *> result;
    
    for (auto &it : subCommands) {
        
        if (it.hidden) continue;
        if (it.name.substr(0, prefix.size()) == prefix) result.push_back(&it);
    }

    return result;
}

string
Command::autoComplete(const string& token)
{
    string result = token;
    
    auto matches = filterPrefix(token);
    if (!matches.empty()) {
        
        const Command *first = matches.front();
        for (auto i = token.size(); i < first->name.size(); i++) {
            
            for (auto m: matches) {
                if (m->name.size() <= i || m->name[i] != first->name[i]) {
                    return result;
                }
            }
            result += first->name[i];
        }
    }
    return result;
}

string
Command::usage() const
{
    string arguments;

    if (subCommands.empty()) {

        string required;
        string optional;

        for (isize i = 0; i < minArgs(); i++) {

            required += requiredArgs[i];
            required += " ";
        }
        for (isize i = 0; i < optArgs(); i++) {

            optional += optionalArgs[i];
            optional + " ";
        }
        if (optional != "") optional = "[ " + optional + "]";

        arguments = required + optional;

    } else {

        // Collect all sub-commands
        isize count = 0;
        for (auto &it : subCommands) {

            if (it.hidden) continue;

            if (it.name != "") {

                if (count++) arguments += " | ";
                arguments += it.name;
            }
        }
        if (count > 1) {
            arguments = "{" + arguments + "}";
        }
        if (seek("") && arguments != "") {
            arguments = "[ " + arguments + " ]";
        }
    }

    return fullName + " " + arguments;
}

}
