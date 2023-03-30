// -----------------------------------------------------------------------------
// This file is part of vAmiga
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the GNU General Public License v3
//
// See https://www.gnu.org for license information
// -----------------------------------------------------------------------------

#pragma once

#include "CoreComponentTypes.h"
#include "CoreObject.h"
#include "Serialization.h"
#include "Concurrency.h"
#include <vector>

namespace vamiga {

/* The following macro can be utilized to prevent multiple threads to enter the
 * same code block. It mimics the behaviour of the well known Java construct
 * 'synchronized(this) { }'. To secure a code-block, use the following syntax:
 *
 *     { SYNCHRONIZED <commands> }
 *
 * To prevent concurrent execution of a single static function, use:
 *
 *     { STATIC_SYNCHRONIZED <commands> }
 */
#define SYNCHRONIZED util::AutoMutex _am(mutex);
#define STATIC_SYNCHRONIZED static std::mutex m; std::lock_guard<std::mutex> lock(m);

struct NoCopy
{
    NoCopy() { };
    NoCopy(NoCopy const&) = delete;
};

struct NoAssign
{
    NoAssign() { };
    NoAssign& operator=(NoAssign const&) = delete;
};

class CoreComponent : public CoreObject, NoCopy, NoAssign {

protected:
    
    // Set to false to silence all debug messages for this component
    bool verbose = true;

    // Sub components
    std::vector<CoreComponent *> subComponents;

    /* Mutex for implementing the 'synchronized' macro. The macro can be used
     * to prevent multiple threads to enter the same code block. It mimics the
     * behaviour of the well known Java construct 'synchronized(this) { }'.
     */
    mutable util::ReentrantMutex mutex;


    //
    // Initializing
    //
    
public:
    
    /* Initializes the component and it's subcomponents. The initialization
     * procedure is initiated once, in the constructor of the Amiga class. By
     * default, a component enters it's initial configuration. Custom actions
     * can be performed by implementing the _initialize() delegation function.
     */
    void initialize();
    virtual void _initialize() { resetConfig(); }
    
    /* Resets the component and it's subcomponents. Two reset modes are
     * distinguished:
     *
     *     hard: A hard reset restores the initial state. It resets the Amiga
     *           from an emulator point of view.
     *
     *     soft: A soft reset emulates a reset inside the virtual Amiga. It is
     *           used to emulate the RESET instruction of the CPU.
     */
    void reset(bool hard);
    virtual void _reset(bool hard) = 0;

    
    //
    // Controlling the state (see Thread class for details)
    //
    
public:
    
    virtual bool isPoweredOff() const = 0;
    virtual bool isPoweredOn() const = 0;
    virtual bool isPaused() const = 0;
    virtual bool isRunning() const = 0;
    virtual bool isSuspended() const = 0;
    virtual bool isHalted() const = 0;

    virtual void suspend() = 0;
    virtual void resume() = 0;

    // Throws an exception if the emulator is not ready to power on
    virtual void isReady() const throws;

protected:
    
    void powerOn();
    void powerOff();
    void run();
    void pause();
    void halt();
    void warpOn();
    void warpOff();
    void trackOn();
    void trackOff();
    
    void powerOnOff(bool value) { value ? powerOn() : powerOff(); }
    void warpOnOff(bool value) { value ? warpOn() : warpOff(); }
    void trackOnOff(bool value) { value ? trackOn() : trackOff(); }

private:
    
    virtual void _isReady() const throws { }
    virtual void _powerOn() { }
    virtual void _powerOff() { }
    virtual void _run() { }
    virtual void _pause() { }
    virtual void _halt() { }
    virtual void _warpOn() { }
    virtual void _warpOff() { }
    virtual void _trackOn() { }
    virtual void _trackOff() { }
    
    
    //
    // Configuring
    //

public:
    
    // Initializes all configuration items with their default values
    virtual void resetConfig() { };


    //
    // Analyzing
    //
    
public:
    
    /* Collects information about the component and it's subcomponents. Many
     * components contain an info variable of a class specific type (e.g.,
     * CPUInfo, MemoryInfo, ...). These variables contain the information shown
     * in the GUI's inspector window and are updated by calling this function.
     * Note: Because this function accesses the internal emulator state with
     * many non-atomic operations, it must not be called on a running emulator.
     * To carry out inspections while the emulator is running, set up an
     * inspection target via Amiga::setInspectionTarget().
     */
    void inspect() const;
    virtual void _inspect() const { }

    /* Base method for building the class specific getInfo() methods. When the
     * emulator is running, the result of the most recent inspection is
     * returned. If the emulator isn't running, the function first updates the
     * cached values in order to return up-to-date results.
     */
    template<class T> T getInfo(T &cachedValues) const {
        
        {   SYNCHRONIZED
            
            if (!isRunning()) inspect();
            return cachedValues;
        }
    }
    
    //
    // Serializing
    //
    
    // Returns the size of the internal state in bytes
    isize size();
    virtual isize _size() = 0;
    
    // Computes a checksum for this component
    u64 checksum();
    virtual u64 _checksum() = 0;

    // Loads the internal state from a memory buffer
    virtual isize load(const u8 *buf) throws;
    virtual isize _load(const u8 *buf) = 0;
    virtual void didLoad();
    virtual void _didLoad() { };

    // Saves the internal state to a memory buffer
    virtual isize save(u8 *buf);
    virtual isize _save(u8 *buf) = 0;
    virtual void didSave();
    virtual void _didSave() { };

    /* Delegation methods called inside load() or save(). Some components
     * override these methods to add custom behavior if not all elements can be
     * processed by the default implementation.
     */
    virtual isize willLoadFromBuffer(const u8 *buf) throws { return 0; }
    virtual isize didLoadFromBuffer(const u8 *buf) throws { return 0; }
    virtual isize willSaveToBuffer(u8 *buf) {return 0; }
    virtual isize didSaveToBuffer(u8 *buf) { return 0; }
};

//
// Standard implementations of _reset, _size, _checksum, _load, and _save
//

#define RESET_SNAPSHOT_ITEMS(hard) \
util::SerResetter resetter; \
applyToResetItems(resetter, hard);

#define COMPUTE_SNAPSHOT_SIZE \
util::SerCounter counter; \
applyToPersistentItems(counter); \
applyToResetItems(counter); \
return counter.count;

#define COMPUTE_SNAPSHOT_CHECKSUM \
util::SerChecker checker; \
applyToPersistentItems(checker); \
applyToResetItems(checker); \
return checker.hash;

#define LOAD_SNAPSHOT_ITEMS \
util::SerReader reader(buffer); \
applyToPersistentItems(reader); \
applyToResetItems(reader); \
return (isize)(reader.ptr - buffer);

#define SAVE_SNAPSHOT_ITEMS \
util::SerWriter writer(buffer); \
applyToPersistentItems(writer); \
applyToResetItems(writer); \
return (isize)(writer.ptr - buffer);

}
