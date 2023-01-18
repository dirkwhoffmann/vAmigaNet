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

class AmigaProxy
{
public:
    AmigaProxy();

    bool hasRom() const;
    bool hasExt() const;
};

class RetroShellProxy
{
public:
    RetroShellProxy();

    string getText();     
    void press(RetroShellKey key);
    void sayHello();
    void pressKey(int c);
    void pressUp() { pressKey(RSKEY_UP); }
    void pressDown() { pressKey(RSKEY_DOWN); }
    void pressLeft() { pressKey(RSKEY_LEFT); }
    void pressRight() { pressKey(RSKEY_RIGHT); }
    void pressHome() { pressKey(RSKEY_HOME); }
    void pressEnd() { pressKey(RSKEY_END); }
    void pressBackspace() { pressKey(RSKEY_BACKSPACE); }
    void pressDelete() { pressKey(RSKEY_DEL); }
    void pressCut() { pressKey(RSKEY_CUT); }
    void pressReturn() { pressKey(RSKEY_RETURN); }
    void pressTab() { pressKey(RSKEY_TAB); }
    void pressShiftReturn();
};