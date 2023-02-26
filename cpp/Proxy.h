#include <emscripten.h>
#include <emscripten/wasm_worker.h>
#include <emscripten/bind.h>

#include "config.h"
#include "Amiga.h"
#include "DMSFile.h"
#include "EXEFile.h"

using namespace emscripten;
using namespace vamiga;

typedef struct
{
    u32 crc32;
    string title;
    string version;
    string released;
    string model;
    bool isAros;
    bool isDiag;
    bool isCommodore;
    bool isHyperion;
    bool isPatched;
    bool isUnknown;
} RomInfo;

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

void save(VAError &error)
{
    errorCode = error.data;
    what = error.what();
}

void processMsg(const void *amiga, long id, int data1, int data2, int data3, int data4);

struct EnumProxy
{
    EnumProxy(){};

    string ErrorCodeKey(int value)
    {
        printf("ErrorCodeKey\n");
        return ErrorCodeEnum::key(value);
    }
    string MsgTypeKey(int value) { return MsgTypeEnum::key(value); }
    string RetroShellKey(int value) { return RetroShellKeyEnum::key(value); }
};

struct AmigaProxy
{
    AmigaProxy();

    Buffer<float> leftChannel;
    Buffer<float> rightChannel;

    // Handling exceptions
    int errorCode() { return ::errorCode; }
    string what() { return ::what; }

    // Configuring
    void configure(int option, int value);
    void configureDrive(int option, int id, int value);
    int getConfig(int option);
    int getDriveConfig(int option, int id);

    // Managing state
    void hardReset() { amiga->hardReset(); }
    void softReset() { amiga->softReset(); }
    bool poweredOn() { return amiga->isPoweredOn(); }
    bool poweredOff() { return amiga->isPoweredOff(); }
    bool isRunning() { return amiga->isRunning(); }
    bool isPaused() { return amiga->isPaused(); }
    // - (void)isReady:(ExceptionWrapper *)ex;
    void powerOn();
    void powerOff();
    void run();
    void pause();
    void halt() { amiga->halt(); }
    void stopAndGo() { amiga->stopAndGo(); }
    void inWarpMode() { amiga->inWarpMode(); }
    void warpOn() { amiga->warpOn(); }
    void warpOff() { amiga->warpOff(); }

    u32 cpuLoad() { return u32(amiga->getCpuLoad() * 100.0); }
    void setSampleRate(unsigned sample_rate);
    void updateAudio(int offset);
    u32 leftChannelBuffer();
    u32 rightChannelBuffer();
    u32 audioFillLevel();

    // Handling media files
    int getFileType(const string &blob);
    
    // Juggling disks
    bool insertDisk(const string &blob, u32 len, u8 drive);

    // Experimental (didn't manage to get it working)
    string getExceptionMessage(intptr_t exceptionPtr);
};

struct CPUProxy
{
    CPUProxy();

    u32 getClock() const;
};

struct AgnusProxy
{
    AgnusProxy();

    u32 frameCount() const;

    void scheduleGUITimerAbs(u32 frames, u32 payload);
    void scheduleGUITimerRel(u32 frames, u32 payload);

};

struct DeniseProxy
{
    DeniseProxy();

    // Textures
    TextureWrapper getEmulatorTexture();
    u32 noise() const;
};

struct JoystickProxy
{
    int joystick;

    JoystickProxy(int joystick);

    void trigger(int action);
};

struct KeyboardProxy
{
    KeyboardProxy();

    void pressKey(u8 keycode);
    void releaseKey(u8 keycode);
};

struct MemoryProxy
{
    MemoryProxy();

    RomInfo analyzeRom(const string &blob, u32 len);

    bool hasRom() const;
    bool hasExt() const;

    bool loadRom(const string &blob, u32 len);
    bool loadExt(const string &blob, u32 len);

    void deleteRom();
    void deleteWom();
    void deleteExt();

    u32 romFingerprint() const;
};

struct MouseProxy
{
    int mouse;

    MouseProxy(int mouse);

    bool detectShakeAbs(double x, double y);
    bool detectShakeRel(double x, double y);
    void setXY(double x, double y);
    void setDxDy(double x, double y);
    void trigger(int action);
};

struct DiskControllerProxy
{
    DiskControllerProxy();

    bool isSpinning() const { return amiga->paula.diskController.spinning(); }
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