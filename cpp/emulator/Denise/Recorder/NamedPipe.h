// -----------------------------------------------------------------------------
// This file is part of vAmiga
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the GNU General Public License v3
//
// See https://www.gnu.org for license information
// -----------------------------------------------------------------------------

#pragma once

#include "Types.h"

namespace vamiga {

class NamedPipe {
    
    int pipe = -1;
    string name;
    
public:
    
    bool create(const string &name);
    bool open();
    bool isOpen();
    bool close();
    isize write(u8 *buffer, isize length);
};

}
