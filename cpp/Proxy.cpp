#include "Proxy.h"
#include <cstdlib>
#include <stdio.h>
#include <exception>

void 
processMsg(const void *amiga, long id, int data1, int data2, int data3, int data4)
{
    printf("MSG %s: %x %x %x %x\n", MsgTypeEnum::key(id), data1, data2, data3, data4);
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

bool 
AmigaProxy::hasRom() const
{
    return amiga->mem.hasRom();
}

bool 
AmigaProxy::hasExt() const
{
    return amiga->mem.hasExt();
}

EMSCRIPTEN_BINDINGS(AmigaProxy)
{
    class_<AmigaProxy>("AmigaProxy")
        .constructor<>()
        .property("hasRom", &AmigaProxy::hasRom)
        .property("hasExt", &AmigaProxy::hasExt);
}

//
// RetroShell proxy
//

RetroShellProxy::RetroShellProxy()
{
    printf("RetroShellProxy()\n");
}

string
RetroShellProxy::getText()
{
    return amiga->retroShell.text();
}

void 
RetroShellProxy::press(RetroShellKey key)
{
    amiga->retroShell.press(key);    
}

void 
RetroShellProxy::pressKey(char c)
{
    printf("pressKey(%c)\n", c);
    amiga->retroShell.press(c);
}

void 
RetroShellProxy::pressShiftReturn()
{
    amiga->retroShell.press(RSKEY_RETURN, true);
}

EMSCRIPTEN_BINDINGS(RetroShellProxy)
{
    class_<RetroShellProxy>("RetroShellProxy")
        .constructor<>()
        .function("text", &RetroShellProxy::getText)
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

EMSCRIPTEN_BINDINGS(Enums) 
{
    constant("MSG_NONE", (int)MSG_NONE);
    constant("MSG_REGISTER", (int)MSG_REGISTER);
    constant("MSG_CONFIG",(int)MSG_CONFIG);
    constant("MSG_POWER_ON", (int)MSG_POWER_ON);
    constant("MSG_POWER_OFF", (int)MSG_POWER_OFF);
}
