// -----------------------------------------------------------------------------
// This file is part of vAmiga
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the GNU General Public License v3
//
// See https://www.gnu.org for license information
// -----------------------------------------------------------------------------

#pragma once

#include "Aliases.h"
#include "Reflection.h"

//
// Enumerations
//

enum_long(SERVER_TYPE)
{
    SERVER_SER,
    SERVER_RSH,
    SERVER_GDB
};
typedef SERVER_TYPE ServerType;

#ifdef __cplusplus
struct ServerTypeEnum : util::Reflection<ServerTypeEnum, ServerType>
{
    static constexpr long minVal = 0;
    static constexpr long maxVal = SERVER_GDB;
    static bool isValid(auto val) { return val >= minVal && val <= maxVal; }
    
    static const char *prefix() { return "SERVER"; }
    static const char *key(ServerType value)
    {
        switch (value) {
                
            case SERVER_SER:    return "SER";
            case SERVER_RSH:    return "RSH";
            case SERVER_GDB:    return "GDB";
        }
        return "???";
    }
};
#endif
