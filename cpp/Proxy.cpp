#include "Proxy.h"
#include <cstdlib>
#include <stdio.h>
#include <exception>

void processMsg(const void *amiga, long id, int data1, int data2, int data3, int data4)
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

bool AmigaProxy::hasRom() const
{
    return amiga->mem.hasRom();
}

bool AmigaProxy::hasExt() const
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

void RetroShellProxy::pressUp()
{
    printf("pressUp()\n");
}

void RetroShellProxy::pressDown()
{
    printf("pressDown()\n");
}

void RetroShellProxy::pressLeft()
{
    printf("pressLeft()\n");
}

void RetroShellProxy::pressRight()
{
    printf("pressRight()\n");
}

EMSCRIPTEN_BINDINGS(vamiga)
{
    class_<RetroShellProxy>("RetroShellProxy")
        .constructor<>()
        .function("pressUp", &RetroShellProxy::pressUp)
        .function("pressDown", &RetroShellProxy::pressDown)
        .function("pressLeft", &RetroShellProxy::pressLeft)
        .function("pressRight", &RetroShellProxy::pressRight);
}