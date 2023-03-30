#include <emscripten.h>
#include <emscripten/wasm_worker.h>
#include <emscripten/bind.h>

#include "vamiga.h"

using namespace emscripten;
using namespace vamiga;

typedef struct
{
    bool valid;
    u32 type;
    u32 d1;
    u32 d2;
    u32 d3;
    u32 d4;
} EmuMsg;

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
} RomInfo;

typedef struct
{
    u32 frameNr;
    u32 data;
    bool currLof;
    bool prevLof;
} TextureWrapper;

Amiga *amiga = nullptr;


//
// Exception handling
//

long errorCode;
string what;

void save(VAError &error)
{
    errorCode = error.data;
    what = error.what();
}

#define TRY try {
#define CATCH } catch (VAError &err) { save(err); throw; }


//
// Proxies
//

struct AgnusProxy
{
    AgnusProxy() { };

    u32 frameCount() const { TRY return (u32)amiga->agnus.pos.frame; CATCH }
};

struct AmigaProxy
{
    AmigaProxy();

    Buffer<float> leftChannel;
    Buffer<float> rightChannel;

    // Handling messages
    Message readMessage();

    // Handling exceptions
    int errorCode() { return ::errorCode; }
    string what() { return ::what; }

    // Operating
    void launch() { TRY amiga->launch(); CATCH }
    void wakeUp() { TRY amiga->wakeUp(); CATCH }

    // Configuring
    void configure(int option, int value) { TRY amiga->configure((Option)option, (i64)value); CATCH }
    void configureId(int option, int id, int value) { TRY amiga->configure((Option)option, (i64)id, (i64)value); CATCH }
    void configureDrive(int option, int id, int value) { TRY amiga->configure((Option)option, (i64)id, (i64)value); CATCH } // DERPECATED
    int getConfig(int option) { TRY return (int)amiga->getConfigItem(option); CATCH }
    int getConfigId(int option, int id) { TRY return (int)amiga->getConfigItem(option, id); CATCH }
    int getDriveConfig(int option, int id) { TRY return (int)amiga->getConfigItem(option, id); CATCH } // DEPRECATED

    // Querying state
    void hardReset() { TRY amiga->hardReset(); CATCH }
    void softReset() { TRY amiga->softReset(); CATCH }
    bool poweredOn() { TRY return amiga->isPoweredOn(); CATCH }
    bool poweredOff() { TRY return amiga->isPoweredOff(); CATCH }
    bool isRunning() { TRY return amiga->isRunning(); CATCH }
    bool isPaused() { TRY return amiga->isPaused(); CATCH }
    bool isHalted() { TRY return amiga->isHalted(); CATCH }
    bool isWarping() { TRY return amiga->isWarping(); CATCH }
    bool isTracking() { TRY return amiga->isTracking(); CATCH }

    // Changing state
    void powerOn() { TRY amiga->powerOn(); CATCH }
    void powerOff() { TRY amiga->powerOff(); CATCH }
    void run() { TRY amiga->run(); CATCH }
    void pause() { TRY amiga->pause(); CATCH }
    void halt() { TRY amiga->halt(); CATCH }
    void stopAndGo() { TRY amiga->stopAndGo(); CATCH }
    void warpOn() { TRY amiga->warpOn(); CATCH }
    void warpOff() { TRY amiga->warpOff(); CATCH }

    // Analyzing
    u32 cpuLoad() { TRY return u32(amiga->getCpuLoad() * 100.0); CATCH }

    // Managing audio (TODO: MOVE TO PAULA PROXY?)
    u32 audioFillLevel() { TRY return u32(amiga->paula.muxer.getStats().fillLevel * 100.0); CATCH }
    void setSampleRate(unsigned sample_rate) { TRY amiga->host.setSampleRate(sample_rate); CATCH }
    void updateAudio(int offset);
    u32 leftChannelBuffer();
    u32 rightChannelBuffer();

    // Handling media files
    int getFileType(const string &blob);
    
    // Juggling disks
    bool insertDisk(const string &blob, u8 drive);
    void ejectDisk(u8 drive) { TRY amiga->df[drive]->ejectDisk(); CATCH }

    // Juggling hard drives
    bool attachHardDrive(const string &blob, u8 drive);
    void detachHardDrive(u8 drive) { TRY /* TODO */ CATCH }

    // Managing alarms
    void setAlarmAbs(int frames, int payload);
    void setAlarmRel(int frames, int payload);
};

struct CPUProxy
{
    CPUProxy() { };

    u32 getClock() const { TRY return (u32)amiga->cpu.getCpuClock(); CATCH }
};

struct DeniseProxy
{
    DeniseProxy() { };

    // Textures
    TextureWrapper getEmulatorTexture();
    u32 noise() const { TRY return (u32)amiga->denise.pixelEngine.getNoise(); CATCH }
};

struct DiskControllerProxy
{
    DiskControllerProxy();

    bool isSpinning() const { return amiga->paula.diskController.spinning(); }
    int getSelected() const { return amiga->paula.diskController.getSelected(); }
    int getState() const { return amiga->paula.diskController.getState(); }
};

struct DriveProxy
{
    int nr;

    DriveProxy(int nr) : nr(nr) { assert(nr >= 0 && nr <= 3); }

    bool isConnected() const { TRY return amiga->df[nr]->isConnected(); CATCH }
    bool hasDisk() const { TRY return amiga->df[nr]->hasDisk(); CATCH }
    bool hasModifiedDisk() const { TRY return amiga->df[nr]->hasModifiedDisk(); CATCH }
    bool hasUnmodifiedDisk() const { TRY return amiga->df[nr]->hasUnmodifiedDisk(); CATCH }
    bool hasProtectedDisk() const { TRY return amiga->df[nr]->hasProtectedDisk(); CATCH }
    bool hasUnprotectedDisk() const { TRY return amiga->df[nr]->hasUnprotectedDisk(); CATCH }
    int currentCyl() const { TRY return amiga->df[nr]->currentCyl(); CATCH }
    bool motor() const { TRY return amiga->df[nr]->getMotor(); CATCH }

    void markDiskAsModified() { TRY amiga->df[nr]->markDiskAsModified(); CATCH }
    void markDiskAsUnmodified() { TRY amiga->df[nr]->markDiskAsUnmodified(); CATCH }
    void toggleWriteProtection() { TRY amiga->df[nr]->toggleWriteProtection(); CATCH }
};

struct EnumProxy
{
    EnumProxy() { };

    string ErrorCodeKey(int value)
    {
        printf("ErrorCodeKey\n");
        return ErrorCodeEnum::key(value);
    }
    string MsgTypeKey(int value) { return MsgTypeEnum::key(value); }
    string RetroShellKey(int value) { return RetroShellKeyEnum::key(value); }
};

struct HardDriveProxy
{
    int nr;

    HardDriveProxy(int nr) : nr(nr) { assert(nr >= 0 && nr <= 3); }

    bool isConnected() const { TRY return amiga->hd[nr]->isConnected(); CATCH }
    bool isReading() const { TRY return amiga->hd[nr]->getState() == HDR_STATE_READING; CATCH }
    bool isWriting() const { TRY return amiga->hd[nr]->getState() == HDR_STATE_WRITING; CATCH }
    int currentCyl() const { TRY return amiga->hd[nr]->currentCyl(); CATCH }
    int state() const { TRY return (int)amiga->hd[nr]->getState(); CATCH }
};

struct JoystickProxy
{
    int joystick;

    JoystickProxy(int joystick) : joystick(joystick) { assert(joystick == 1 || joystick == 2); }
    ControlPort &port() { return joystick == 1 ? amiga->controlPort1 : amiga->controlPort2; }

    void trigger(int action) { port().joystick.trigger(action); }
};

struct KeyboardProxy
{
    KeyboardProxy() { };

    void pressKey(u8 keycode) { TRY amiga->keyboard.pressKey(keycode); CATCH }
    void releaseKey(u8 keycode) { TRY amiga->keyboard.releaseKey(keycode); CATCH }
};

struct MemoryProxy
{
    MemoryProxy() { };

    RomInfo analyzeRom(const string &blob, u32 len);

    bool hasRom() const { TRY return amiga->mem.hasRom(); CATCH }
    bool hasExt() const { TRY return amiga->mem.hasExt(); CATCH }

    bool loadRom(const string &blob, u32 len);
    bool loadExt(const string &blob, u32 len);

    void deleteRom() { TRY amiga->mem.deleteRom(); CATCH }
    void deleteWom() { TRY amiga->mem.deleteWom(); CATCH }
    void deleteExt() { TRY amiga->mem.deleteExt(); CATCH }

    u32 romFingerprint() const { TRY return amiga->mem.romFingerprint(); CATCH }
};

struct MouseProxy
{
    int mouse;

    MouseProxy(int mouse) : mouse(mouse) { assert(mouse == 1 || mouse == 2); }
    ControlPort &port() { return mouse == 1 ? amiga->controlPort1 : amiga->controlPort2; }

    bool detectShakeAbs(double x, double y) { return port().mouse.detectShakeXY(x, y); }
    bool detectShakeRel(double x, double y) { return port().mouse.detectShakeDxDy(x, y); }
    void setXY(double x, double y) { port().mouse.setXY(x, y); }
    void setDxDy(double x, double y) { port().mouse.setDxDy(x, y); }
    void trigger(int action) { port().mouse.trigger((GamePadAction)action); }
};

struct PaulaProxy
{
    PaulaProxy() { };

    bool isMuted() const { TRY return amiga->paula.muxer.isMuted(); CATCH };
};

struct RetroShellProxy
{
    RetroShellProxy() { };

    string getText() { TRY return amiga->retroShell.text(); CATCH };
    int getCursorRel() { TRY return (int)amiga->retroShell.cursorRel(); CATCH }
    void press(RetroShellKey key) { TRY amiga->retroShell.press(key); CATCH }
    void pressKey(char c) { TRY amiga->retroShell.press(c); CATCH }
    void pressUp() { TRY amiga->retroShell.press(RSKEY_UP); CATCH }
    void pressDown() { TRY amiga->retroShell.press(RSKEY_DOWN); CATCH }
    void pressLeft() { TRY amiga->retroShell.press(RSKEY_LEFT); CATCH }
    void pressRight() { TRY amiga->retroShell.press(RSKEY_RIGHT); CATCH }
    void pressHome() { TRY amiga->retroShell.press(RSKEY_HOME); CATCH }
    void pressEnd() { TRY amiga->retroShell.press(RSKEY_END); CATCH }
    void pressBackspace() { TRY amiga->retroShell.press(RSKEY_BACKSPACE); CATCH }
    void pressDelete() { TRY amiga->retroShell.press(RSKEY_DEL); CATCH }
    void pressCut() { TRY amiga->retroShell.press(RSKEY_CUT); CATCH }
    void pressReturn() { TRY amiga->retroShell.press(RSKEY_RETURN); CATCH }
    void pressTab() { TRY amiga->retroShell.press(RSKEY_TAB); CATCH }
    void pressShiftReturn() { TRY amiga->retroShell.press(RSKEY_RETURN, true); CATCH }
};