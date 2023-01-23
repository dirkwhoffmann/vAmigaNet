#include <emscripten.h>
#include <emscripten/wasm_worker.h>
#include <emscripten/bind.h>

#include "config.h"
#include "Amiga.h"

using namespace emscripten;
using namespace vamiga;

typedef struct
{
    u32 frameNr;
    u32 data;
    bool currLof;
    bool prevLof;
} TextureWrapper;

Amiga *amiga = nullptr;

long errorCode;
string what;

typedef struct
{
    u32 left;
    u32 right;
} AudioBuffers;

void save(VAError &error)
{
    errorCode = error.data;
    what = error.what();
}

void processMsg(const void *amiga, long id, int data1, int data2, int data3, int data4);

struct EnumProxy
{
    EnumProxy(){};

    string MsgTypeKey(int value) { return MsgTypeEnum::key(value); }
    string RetroShellKey(int value) { return RetroShellKeyEnum::key(value); }
};

struct AmigaProxy
{
    AmigaProxy();

    Buffer<float> leftChannel;
    Buffer<float> rightChannel;

    // Exception handling
    int errorCode() { return ::errorCode; }
    string what() { return ::what; }

    // State
    void hardReset() { amiga->hardReset(); }
    void softReset() { amiga->softReset(); }

    bool poweredOn() { return amiga->isPoweredOn(); }
    bool poweredOff() { return amiga->isPoweredOff(); }
    bool isRunning() { return amiga->isRunning(); }
    bool isPaused() { return amiga->isPaused(); }
    // - (void)isReady:(ExceptionWrapper *)ex;
    void powerOn() { amiga->powerOn(); }
    void powerOff() { amiga->powerOff(); }
    void run() { amiga->run(); }
    void pause() { amiga->pause(); }
    void halt() { amiga->halt(); }

    // Audio
    AudioBuffers createAudioBuffers(i32 size);
    void copyAudioBuffers();

    // DEPRECATED
    u32 pixelBuffer();
};

struct DeniseProxy
{
    DeniseProxy();

    // Textures
    TextureWrapper getEmulatorTexture();
    u32 noise() const;
};

struct MemoryProxy
{
    MemoryProxy();

    bool hasRom() const;
    bool hasExt() const;
    bool loadRom(const string &blob, u32 len);
    bool loadExt(const string &blob, u32 len);
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