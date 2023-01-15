// -----------------------------------------------------------------------------
// This file is part of vAmiga
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the GNU General Public License v3
//
// See https://www.gnu.org for license information
// -----------------------------------------------------------------------------

#include "config.h"
#include "Parser.h"

namespace util {

bool
parseBool(string& token)
{
    if (token == "1" || token == "true" || token == "yes") return true;
    if (token == "0" || token == "false" || token == "no") return false;

    throw ParseBoolError(token);
}

bool
parseOnOff(string& token)
{
    if (token == "on") return true;
    if (token == "off") return false;

    throw ParseOnOffError(token);
}

long
parseNum(string& token)
{
    long result;

    // Replace leading '$' by '0x'
    if (!token.empty() && token[0] == '$') token = "0x" + token.erase(0, 1);
    
    try { result = stol(token, nullptr, 0); }
    catch (std::exception&) { throw ParseNumError(token); }

    return result;
}

}
