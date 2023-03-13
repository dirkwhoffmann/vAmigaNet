// -----------------------------------------------------------------------------
// This file is part of vAmiga
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the GNU General Public License v3
//
// See https://www.gnu.org for license information
// -----------------------------------------------------------------------------

#pragma once

#include "MsgQueueTypes.h"
#include "SubComponent.h"
#include "RingBuffer.h"

namespace vamiga {

class MsgQueue : public SubComponent {

    // Ring buffer storing all pending messages
    util::RingBuffer <Message, 512> queue;

    // The registered listener
    const void *listener = nullptr;
    
    // The registered callback function
    Callback *callback = nullptr;
    
    
    //
    // Constructing
    //

    using SubComponent::SubComponent;
    
    
    //
    // Methods from CoreObject
    //
    
private:
    
    const char *getDescription() const override { return "MsgQueue"; }
    void _dump(Category category, std::ostream& os) const override { }
    
    
    //
    // Methods from CoreComponent
    //
    
private:
    
    void _reset(bool hard) override { };
    isize _size() override { return 0; }
    u64 _checksum() override { return 0; }
    isize _load(const u8 *buffer) override { return 0; }
    isize _save(u8 *buffer) override { return 0; }
    
    
    //
    // Managing the queue
    //
    
public:
    
    // Registers a listener together with it's callback function
    void setListener(const void *listener, Callback *func);

    // Sends a message
    void put(const Message &msg);
    void put(MsgType type, i64 payload = 0);
    void put(MsgType type, CpuMsg payload);
    void put(MsgType type, DriveMsg payload);
    void put(MsgType type, HdcMsg payload);
    void put(MsgType type, ScriptMsg payload);
    void put(MsgType type, ViewportMsg payload);

    // Reads a message
    bool get(Message &msg);
};

}
