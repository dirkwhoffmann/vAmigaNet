#include <emscripten.h>
#include <emscripten/wasm_worker.h>
#include <emscripten/bind.h>

#include "config.h"
#include "Amiga.h"

using namespace emscripten;
using namespace vamiga;

Amiga *amiga = nullptr;

void processMsg(const void *amiga, long id, int data1, int data2, int data3, int data4);

struct EnumProxy
{
    EnumProxy() { };

    string MsgTypeKey(int value) { return MsgTypeEnum::key(value); }
    string RetroShellKey(int value) { return RetroShellKeyEnum::key(value); }
};

struct AmigaProxy
{
    AmigaProxy();

    string helloAmiga();
    string getExceptionMessage(intptr_t exceptionPtr);
};

struct MemoryProxy
{
    MemoryProxy();

    bool hasRom() const;
    bool hasExt() const;
    bool loadRom(string blob, u32 len);
};

struct RetroShellProxy
{
    RetroShellProxy();

    string getText();
    int getCursorRel() { return (int)amiga->retroShell.cursorRel(); }
    void press(RetroShellKey key);
    void pressKey(char c);
    void pressUp() { amiga->retroShell.press(RSKEY_UP); }
    void pressDown() { amiga->retroShell.press(RSKEY_DOWN); }
    void pressLeft() { amiga->retroShell.press(RSKEY_LEFT); }
    void pressRight() { amiga->retroShell.press(RSKEY_RIGHT); }
    void pressHome() { amiga->retroShell.press(RSKEY_HOME); }
    void pressEnd() { amiga->retroShell.press(RSKEY_END); }
    void pressBackspace() { amiga->retroShell.press(RSKEY_BACKSPACE); }
    void pressDelete() { amiga->retroShell.press(RSKEY_DEL); }
    void pressCut() { amiga->retroShell.press(RSKEY_CUT); }
    void pressReturn() { amiga->retroShell.press(RSKEY_RETURN); }
    void pressTab() { amiga->retroShell.press(RSKEY_TAB); }
    void pressShiftReturn();
};