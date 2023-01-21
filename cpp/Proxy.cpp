#include "Proxy.h"
#include <cstdlib>
#include <stdio.h>
#include <exception>

void processMsg(const void *amiga, long id, int d1, int d2, int d3, int d4)
{
    // Reroute call to JavaScript
    MAIN_THREAD_ASYNC_EM_ASM({ self.Module.processMsg($0, $1, $2, $3, $4); }, id, d1, d2, d3, d4);
}

//
// Enum Proxy
//

EMSCRIPTEN_BINDINGS(EnumProxy)
{
    class_<EnumProxy>("EnumProxy")
        .constructor<>()
        .function("MsgTypeKey", &EnumProxy::MsgTypeKey)
        .function("RetroShellKey", &EnumProxy::RetroShellKey);
}

//
// Amiga Proxy
//

AmigaProxy::AmigaProxy()
{
    printf("AmigaProxy()\n");

    printf("Constructing Amiga...\n");
    amiga = new Amiga();

    printf("Adding listener...\n");
    amiga->msgQueue.setListener(amiga, &processMsg);

    printf("Launching emulator thread...\n");
    amiga->launch();

    printf("Configuring...\n");
    amiga->configure(OPT_AUDVOLL, 100);
    amiga->configure(OPT_AUDVOLR, 100);
    amiga->configure(OPT_AUDVOL, 0, 100);
    amiga->configure(OPT_AUDPAN, 0, 0);

    amiga->configure(OPT_CHIP_RAM, 512);
    amiga->configure(OPT_SLOW_RAM, 512);
    amiga->configure(OPT_AGNUS_REVISION, AGNUS_OCS);
}

string 
AmigaProxy::helloAmiga()
{
    return "Hello, vAmiga";
}

string
AmigaProxy::getExceptionMessage(intptr_t exceptionPtr)
{
    printf("Ptr = %ld\n", exceptionPtr);
    return string(reinterpret_cast<std::exception *>(exceptionPtr)->what());
}

EMSCRIPTEN_BINDINGS(AmigaProxy)
{
    class_<AmigaProxy>("AmigaProxy")
        .constructor<>()
        .function("helloAmiga", &AmigaProxy::helloAmiga)
        .function("getExceptionMessage", &AmigaProxy::getExceptionMessage);
}

//
// Memory proxy
//

MemoryProxy::MemoryProxy()
{
    printf("MemoryProxy()\n");
}

bool MemoryProxy::hasRom() const
{
    return amiga->mem.hasRom();
}

bool MemoryProxy::hasExt() const
{
    return amiga->mem.hasExt();
}

bool MemoryProxy::loadRom(string blob, u32 len)
{
    try
    {
        printf("in loadRom\n");
        amiga->mem.loadRom((u8 *)blob.data(), len);
        printf("Exiting...\n");
        return amiga->mem.hasRom();
    }
    catch (VAError &err)
    {
        printf("VAError: %s\n", err.what());
        throw;
    }
}

EMSCRIPTEN_BINDINGS(MemoryProxy)
{
    class_<MemoryProxy>("MemoryProxy")
        .constructor<>()
        .function("loadRom", &MemoryProxy::loadRom)
        .property("hasRom", &MemoryProxy::hasRom)
        .property("hasExt", &MemoryProxy::hasExt);
}

//
// RetroShell proxy
//

RetroShellProxy::RetroShellProxy()
{
    printf("RetroShellProxy()\n");
}

string RetroShellProxy::getText()
{
    return amiga->retroShell.text();
}

void RetroShellProxy::press(RetroShellKey key)
{
    amiga->retroShell.press(key);
}

void RetroShellProxy::pressKey(char c)
{
    amiga->retroShell.press(c);
}

void RetroShellProxy::pressShiftReturn()
{
    amiga->retroShell.press(RSKEY_RETURN, true);
}

EMSCRIPTEN_BINDINGS(RetroShellProxy)
{
    class_<RetroShellProxy>("RetroShellProxy")
        .constructor<>()
        .function("getText", &RetroShellProxy::getText)
        .function("getCursorRel", &RetroShellProxy::getCursorRel)
        .function("pressUp", &RetroShellProxy::pressUp)
        .function("pressDown", &RetroShellProxy::pressDown)
        .function("pressLeft", &RetroShellProxy::pressLeft)
        .function("pressRight", &RetroShellProxy::pressRight)
        .function("pressHome", &RetroShellProxy::pressHome)
        .function("pressEnd", &RetroShellProxy::pressEnd)
        .function("pressBackspace", &RetroShellProxy::pressBackspace)
        .function("pressDelete", &RetroShellProxy::pressDelete)
        .function("pressCut", &RetroShellProxy::pressCut)
        .function("pressReturn", &RetroShellProxy::pressReturn)
        .function("pressTab", &RetroShellProxy::pressTab)
        .function("pressShiftReturn", &RetroShellProxy::pressShiftReturn)
        .function("pressKey", &RetroShellProxy::pressKey);
}

EMSCRIPTEN_BINDINGS(Keys)
{
    constant("MSG_NONE", (int)MSG_NONE);
    constant("MSG_REGISTER", (int)MSG_REGISTER);
    constant("MSG_CONFIG", (int)MSG_CONFIG);
    constant("MSG_POWER_ON", (int)MSG_POWER_ON);
    constant("MSG_POWER_OFF", (int)MSG_POWER_OFF);
    constant("MSG_RUN", (int)MSG_RUN);
    constant("MSG_PAUSE", (int)MSG_PAUSE);
    constant("MSG_STEP", (int)MSG_STEP);
    constant("MSG_RESET", (int)MSG_RESET);
    constant("MSG_HALT", (int)MSG_HALT);
    constant("MSG_ABORT", (int)MSG_ABORT);
    constant("MSG_WARP_ON", (int)MSG_WARP_ON);
    constant("MSG_WARP_OFF", (int)MSG_WARP_OFF);
    constant("MSG_DEBUG_ON", (int)MSG_DEBUG_ON);
    constant("MSG_DEBUG_OFF", (int)MSG_DEBUG_OFF);
    constant("MSG_MUTE_ON", (int)MSG_MUTE_ON);
    constant("MSG_MUTE_OFF", (int)MSG_MUTE_OFF);
    constant("MSG_POWER_LED_ON", (int)MSG_POWER_LED_ON);
    constant("MSG_POWER_LED_DIM", (int)MSG_POWER_LED_DIM);
    constant("MSG_POWER_LED_OFF", (int)MSG_POWER_LED_OFF);
    constant("MSG_CLOSE_CONSOLE", (int)MSG_CLOSE_CONSOLE);
    constant("MSG_UPDATE_CONSOLE", (int)MSG_UPDATE_CONSOLE);
    constant("MSG_SCRIPT_DONE", (int)MSG_SCRIPT_DONE);
    constant("MSG_SCRIPT_PAUSE", (int)MSG_SCRIPT_PAUSE);
    constant("MSG_SCRIPT_ABORT", (int)MSG_SCRIPT_ABORT);
    constant("MSG_SCRIPT_WAKEUP", (int)MSG_SCRIPT_WAKEUP);
    constant("MSG_VIDEO_FORMAT", (int)MSG_VIDEO_FORMAT);
    constant("MSG_OVERCLOCKING", (int)MSG_OVERCLOCKING);
    constant("MSG_BREAKPOINT_UPDATED", (int)MSG_BREAKPOINT_UPDATED);
    constant("MSG_BREAKPOINT_REACHED", (int)MSG_BREAKPOINT_REACHED);
    constant("MSG_WATCHPOINT_UPDATED", (int)MSG_WATCHPOINT_UPDATED);
    constant("MSG_WATCHPOINT_REACHED", (int)MSG_WATCHPOINT_REACHED);
    constant("MSG_CATCHPOINT_UPDATED", (int)MSG_CATCHPOINT_UPDATED);
    constant("MSG_CATCHPOINT_REACHED", (int)MSG_CATCHPOINT_REACHED);
    constant("MSG_SWTRAP_REACHED", (int)MSG_SWTRAP_REACHED);
    constant("MSG_CPU_HALT", (int)MSG_CPU_HALT);
    constant("MSG_COPPERBP_REACHED", (int)MSG_COPPERBP_REACHED);
    constant("MSG_COPPERBP_UPDATED", (int)MSG_COPPERBP_UPDATED);
    constant("MSG_COPPERWP_REACHED", (int)MSG_COPPERWP_REACHED);
    constant("MSG_COPPERWP_UPDATED", (int)MSG_COPPERWP_UPDATED);
    constant("MSG_VIEWPORT", (int)MSG_VIEWPORT);
    constant("MSG_MEM_LAYOUT", (int)MSG_MEM_LAYOUT);
    constant("MSG_DRIVE_CONNECT", (int)MSG_DRIVE_CONNECT);
    constant("MSG_DRIVE_DISCONNECT", (int)MSG_DRIVE_DISCONNECT);
    constant("MSG_DRIVE_SELECT", (int)MSG_DRIVE_SELECT);
    constant("MSG_DRIVE_READ", (int)MSG_DRIVE_READ);
    constant("MSG_DRIVE_WRITE", (int)MSG_DRIVE_WRITE);
    constant("MSG_DRIVE_LED_ON", (int)MSG_DRIVE_LED_ON);
    constant("MSG_DRIVE_LED_OFF", (int)MSG_DRIVE_LED_OFF);
    constant("MSG_DRIVE_MOTOR_ON", (int)MSG_DRIVE_MOTOR_ON);
    constant("MSG_DRIVE_MOTOR_OFF", (int)MSG_DRIVE_MOTOR_OFF);
    constant("MSG_DRIVE_STEP", (int)MSG_DRIVE_STEP);
    constant("MSG_DRIVE_POLL", (int)MSG_DRIVE_POLL);
    constant("MSG_DISK_INSERT", (int)MSG_DISK_INSERT);
    constant("MSG_DISK_EJECT", (int)MSG_DISK_EJECT);
    constant("MSG_DISK_SAVED", (int)MSG_DISK_SAVED);
    constant("MSG_DISK_UNSAVED", (int)MSG_DISK_UNSAVED);
    constant("MSG_DISK_PROTECT", (int)MSG_DISK_PROTECT);
    constant("MSG_DISK_UNPROTECT", (int)MSG_DISK_UNPROTECT);
    constant("MSG_HDC_CONNECT", (int)MSG_HDC_CONNECT);
    constant("MSG_HDC_DISCONNECT", (int)MSG_HDC_DISCONNECT);
    constant("MSG_HDC_STATE", (int)MSG_HDC_STATE);
    constant("MSG_HDR_STEP", (int)MSG_HDR_STEP);
    constant("MSG_HDR_READ", (int)MSG_HDR_READ);
    constant("MSG_HDR_WRITE", (int)MSG_HDR_WRITE);
    constant("MSG_HDR_IDLE", (int)MSG_HDR_IDLE);
    constant("MSG_CTRL_AMIGA_AMIGA", (int)MSG_CTRL_AMIGA_AMIGA);
    constant("MSG_SHAKING", (int)MSG_SHAKING);
    constant("MSG_SER_IN", (int)MSG_SER_IN);
    constant("MSG_SER_OUT", (int)MSG_SER_OUT);
    constant("MSG_AUTO_SNAPSHOT_TAKEN", (int)MSG_AUTO_SNAPSHOT_TAKEN);
    constant("MSG_USER_SNAPSHOT_TAKEN", (int)MSG_USER_SNAPSHOT_TAKEN);
    constant("MSG_SNAPSHOT_RESTORED", (int)MSG_SNAPSHOT_RESTORED);
    constant("MSG_RECORDING_STARTED", (int)MSG_RECORDING_STARTED);
    constant("MSG_RECORDING_STOPPED", (int)MSG_RECORDING_STOPPED);
    constant("MSG_RECORDING_ABORTED", (int)MSG_RECORDING_ABORTED);
    constant("MSG_DMA_DEBUG_ON", (int)MSG_DMA_DEBUG_ON);
    constant("MSG_DMA_DEBUG_OFF", (int)MSG_DMA_DEBUG_OFF);
    constant("MSG_SRV_STATE", (int)MSG_SRV_STATE);
    constant("MSG_SRV_RECEIVE", (int)MSG_SRV_RECEIVE);
    constant("MSG_SRV_SEND", (int)MSG_SRV_SEND);
}
