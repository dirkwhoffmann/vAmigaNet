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
#include <exception>

namespace util {

struct Exception : public std::exception {
    
    i64 data;
    string description;
    
    Exception(i64 d, const string &s) : data(d), description(s) { }
    Exception(i64 d) : data(d), description("") { }
    Exception(const string &s) : data(0), description(s) { }
    Exception() : data(0) { }
    
    const char *what() const throw() override { return description.c_str(); }
};

//
// Syntactic sugar
//

/* The following keyword is used for documentary purposes only. It is used to
 * mark all methods that use the exception mechanism to signal error conditions
 * instead of returning error codes. It is used in favor of classic throw
 * lists, since the latter cause the compiler to embed unwanted runtime checks
 * in the code.
 */
#define throws

}
