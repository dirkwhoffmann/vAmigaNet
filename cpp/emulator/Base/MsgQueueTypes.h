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

enum_long(MSG_TYPE)
{
    MSG_NONE = 0,
    
    // Message queue
    MSG_REGISTER,
    
    // Emulator state
    MSG_CONFIG,
    MSG_POWER_ON,
    MSG_POWER_OFF,
    MSG_RUN,
    MSG_PAUSE,
    MSG_STEP,
    MSG_RESET,
    MSG_HALT,
    MSG_ABORT,
    MSG_WARP_ON,
    MSG_WARP_OFF,
    MSG_DEBUG_ON,
    MSG_DEBUG_OFF,
    MSG_MUTE_ON,
    MSG_MUTE_OFF,
    MSG_POWER_LED_ON,
    MSG_POWER_LED_DIM,
    MSG_POWER_LED_OFF,

    // Retro shell
    MSG_CLOSE_CONSOLE,
    MSG_UPDATE_CONSOLE,
    MSG_SCRIPT_DONE,
    MSG_SCRIPT_PAUSE,
    MSG_SCRIPT_ABORT,
    MSG_SCRIPT_WAKEUP,

    // Amiga
    MSG_VIDEO_FORMAT,

    // CPU
    MSG_OVERCLOCKING,
    MSG_BREAKPOINT_UPDATED,
    MSG_BREAKPOINT_REACHED,
    MSG_WATCHPOINT_UPDATED,
    MSG_WATCHPOINT_REACHED,
    MSG_CATCHPOINT_UPDATED,
    MSG_CATCHPOINT_REACHED,
    MSG_SWTRAP_REACHED,
    MSG_CPU_HALT,
    
    // Copper
    MSG_COPPERBP_REACHED,
    MSG_COPPERBP_UPDATED,
    MSG_COPPERWP_REACHED,
    MSG_COPPERWP_UPDATED,

    // Denise
    MSG_VIEWPORT,
    
    // Memory
    MSG_MEM_LAYOUT,
        
    // Floppy drives
    MSG_DRIVE_CONNECT,
    MSG_DRIVE_DISCONNECT,
    MSG_DRIVE_SELECT,
    MSG_DRIVE_READ,
    MSG_DRIVE_WRITE,
    MSG_DRIVE_LED_ON,
    MSG_DRIVE_LED_OFF,
    MSG_DRIVE_MOTOR_ON,
    MSG_DRIVE_MOTOR_OFF,
    MSG_DRIVE_STEP,
    MSG_DRIVE_POLL,
    MSG_DISK_INSERT,
    MSG_DISK_EJECT,
    MSG_DISK_SAVED,
    MSG_DISK_UNSAVED,
    MSG_DISK_PROTECT,
    MSG_DISK_UNPROTECT,

    // Hard drive controllers
    MSG_HDC_CONNECT,
    MSG_HDC_DISCONNECT,
    MSG_HDC_STATE,
    
    // Hard drives
    MSG_HDR_STEP,
    MSG_HDR_READ,
    MSG_HDR_WRITE,
    MSG_HDR_IDLE,
    
    // Keyboard
    MSG_CTRL_AMIGA_AMIGA,
    
    // Mouse
    MSG_SHAKING,
    
    // Ports
    MSG_SER_IN,
    MSG_SER_OUT,

    // Snapshots
    MSG_AUTO_SNAPSHOT_TAKEN,
    MSG_USER_SNAPSHOT_TAKEN,
    MSG_SNAPSHOT_RESTORED,

    // Screen recording
    MSG_RECORDING_STARTED,
    MSG_RECORDING_STOPPED,
    MSG_RECORDING_ABORTED,
        
    // DMA Debugging
    MSG_DMA_DEBUG_ON,
    MSG_DMA_DEBUG_OFF,

    // Remote server
    MSG_SRV_STATE,
    MSG_SRV_RECEIVE,
    MSG_SRV_SEND
};
typedef MSG_TYPE MsgType;

#ifdef __cplusplus
struct MsgTypeEnum : util::Reflection<MsgTypeEnum, MsgType>
{
    static constexpr long minVal = 0;
    static constexpr long maxVal = MSG_SRV_SEND;
    static bool isValid(auto val) { return val >= minVal && val <= maxVal; }

    static const char *prefix() { return "MSG"; }
    static const char *key(MsgType value)
    {
        switch (value) {
                
            case MSG_NONE:                  return "NONE";
            case MSG_REGISTER:              return "REGISTER";

            case MSG_CONFIG:                return "CONFIG";
            case MSG_POWER_ON:              return "POWER_ON";
            case MSG_POWER_OFF:             return "POWER_OFF";
            case MSG_RUN:                   return "RUN";
            case MSG_PAUSE:                 return "PAUSE";
            case MSG_STEP:                  return "STEP";
            case MSG_RESET:                 return "RESET";
            case MSG_HALT:                  return "HALT";
            case MSG_ABORT:                 return "ABORT";
            case MSG_WARP_ON:               return "WARP_ON";
            case MSG_WARP_OFF:              return "WARP_OFF";
            case MSG_DEBUG_ON:              return "DEBUG_ON";
            case MSG_DEBUG_OFF:             return "DEBUG_OFF";
            case MSG_MUTE_ON:               return "MUTE_ON";
            case MSG_MUTE_OFF:              return "MUTE_OFF";
            case MSG_POWER_LED_ON:          return "POWER_LED_ON";
            case MSG_POWER_LED_DIM:         return "POWER_LED_DIM";
            case MSG_POWER_LED_OFF:         return "POWER_LED_OFF";

            case MSG_CLOSE_CONSOLE:         return "CLOSE_CONSOLE";
            case MSG_UPDATE_CONSOLE:        return "UPDATE_CONSOLE";
            case MSG_SCRIPT_DONE:           return "SCRIPT_DONE";
            case MSG_SCRIPT_PAUSE:          return "SCRIPT_PAUSE";
            case MSG_SCRIPT_ABORT:          return "SCRIPT_ABORT";
            case MSG_SCRIPT_WAKEUP:         return "MSG_SCRIPT_WAKEUP";

            case MSG_VIDEO_FORMAT:          return "VIDEO_FORMAT";
                
            case MSG_OVERCLOCKING:          return "OVERCLOCKING";
            case MSG_BREAKPOINT_UPDATED:    return "BREAKPOINT_UPDATED";
            case MSG_BREAKPOINT_REACHED:    return "BREAKPOINT_REACHED";
            case MSG_WATCHPOINT_UPDATED:    return "WATCHPOINT_UPDATED";
            case MSG_WATCHPOINT_REACHED:    return "WATCHPOINT_REACHED";
            case MSG_CATCHPOINT_UPDATED:    return "CATCHPOINT_UPDATED";
            case MSG_CATCHPOINT_REACHED:    return "CATCHPOINT_REACHED";
            case MSG_SWTRAP_REACHED:        return "SWTRAP_REACHED";
            case MSG_CPU_HALT:              return "CPU_HALT";

            case MSG_COPPERBP_REACHED:      return "COPPERBP_REACHED";
            case MSG_COPPERBP_UPDATED:      return "COPPERBP_UPDATED";
            case MSG_COPPERWP_REACHED:      return "COPPERWP_REACHED";
            case MSG_COPPERWP_UPDATED:      return "COPPERWP_UPDATED";
                
            case MSG_VIEWPORT:              return "VIEWPORT";
                
            case MSG_MEM_LAYOUT:            return "MEM_LAYOUT";
                    
            case MSG_DRIVE_CONNECT:         return "DRIVE_CONNECT";
            case MSG_DRIVE_DISCONNECT:      return "DRIVE_DISCONNECT";
            case MSG_DRIVE_SELECT:          return "DRIVE_SELECT";
            case MSG_DRIVE_READ:            return "DRIVE_READ";
            case MSG_DRIVE_WRITE:           return "DRIVE_WRITE";
            case MSG_DRIVE_LED_ON:          return "DRIVE_LED_ON";
            case MSG_DRIVE_LED_OFF:         return "DRIVE_LED_OFF";
            case MSG_DRIVE_MOTOR_ON:        return "DRIVE_MOTOR_ON";
            case MSG_DRIVE_MOTOR_OFF:       return "DRIVE_MOTOR_OFF";
            case MSG_DRIVE_STEP:            return "DRIVE_STEP";
            case MSG_DRIVE_POLL:            return "DRIVE_POLL";
            case MSG_DISK_INSERT:           return "DISK_INSERT";
            case MSG_DISK_EJECT:            return "DISK_EJECT";
            case MSG_DISK_SAVED:            return "DISK_SAVED";
            case MSG_DISK_UNSAVED:          return "DISK_UNSAVED";
            case MSG_DISK_PROTECT:          return "DISK_PROTECT";
            case MSG_DISK_UNPROTECT:        return "DISK_UNPROTECT";

            case MSG_HDC_CONNECT:           return "HDC_CONNECT";
            case MSG_HDC_DISCONNECT:        return "HDC_DISCONNECT";
            case MSG_HDC_STATE:             return "HDC_STATE";
                
            case MSG_HDR_STEP:              return "HDR_STEP";
            case MSG_HDR_READ:              return "HDR_READ";
            case MSG_HDR_WRITE:             return "HDR_WRITE";
            case MSG_HDR_IDLE:              return "HDR_IDLE";
                
            case MSG_CTRL_AMIGA_AMIGA:      return "CTRL_AMIGA_AMIGA";

            case MSG_SHAKING:               return "SHAKING";

            case MSG_SER_IN:                return "SER_IN";
            case MSG_SER_OUT:               return "SER_OUT";

            case MSG_AUTO_SNAPSHOT_TAKEN:   return "AUTO_SNAPSHOT_TAKEN";
            case MSG_USER_SNAPSHOT_TAKEN:   return "USER_SNAPSHOT_TAKEN";
            case MSG_SNAPSHOT_RESTORED:     return "SNAPSHOT_RESTORED";
                
            case MSG_RECORDING_STARTED:     return "RECORDING_STARTED";
            case MSG_RECORDING_STOPPED:     return "RECORDING_STOPPED";
            case MSG_RECORDING_ABORTED:     return "RECORDING_ABORTED";
                                
            case MSG_DMA_DEBUG_ON:          return "DMA_DEBUG_ON";
            case MSG_DMA_DEBUG_OFF:         return "DMA_DEBUG_OFF";
                                
            case MSG_SRV_STATE:             return "SRV_STATE";
            case MSG_SRV_RECEIVE:           return "SRV_RECEIVE";
            case MSG_SRV_SEND:              return "SRV_SEND";
        }
        return "???";
    }
};
#endif


//
// Structures
//

typedef struct
{
    MsgType type;

    /* The payload of a message consists of up to four (signed) 32-bit values.
     * We avoid the usage of 64-bit types inside this structure to make it
     * easily processable by JavaScript (web ports).
     */
    i32 data1;
    i32 data2;
    i32 data3;
    i32 data4;
}
Message;


//
// Signatures
//

typedef void Callback(const void *, long, i32, i32, i32, i32);
