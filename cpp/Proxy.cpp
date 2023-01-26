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
// Structures
//

EMSCRIPTEN_BINDINGS(Structures)
{
    value_object<TextureWrapper>("TextureWrapper")
        .field("frameNr", &TextureWrapper::frameNr)
        .field("data", &TextureWrapper::data)
        .field("currLof", &TextureWrapper::currLof)
        .field("prevLof", &TextureWrapper::prevLof);
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

    amiga->configure(OPT_CHIP_RAM, 1024);
    amiga->configure(OPT_SLOW_RAM, 512);
    amiga->configure(OPT_AGNUS_REVISION, AGNUS_OCS);

    amiga->configure(OPT_DRIVE_CONNECT, 1, true);
}

void AmigaProxy::configure(int option, int value)
{
    try
    {
        amiga->configure((Option)option, (i64)value);
    }
    catch (VAError &err)
    {
        save(err);
        throw;
    }
}

void AmigaProxy::configureDrive(int option, int id, int value)
{
    try
    {
        amiga->configure((Option)option, (i64)id, (i64)value);
    }
    catch (VAError &err)
    {
        save(err);
        throw;
    }
}

void AmigaProxy::updateAudio(int offset)
{
    assert(offset == 0 || offset == 1024); 
        
    float *left = leftChannel + offset; 
    float *right = rightChannel + offset;
    amiga->paula.muxer.copy(left, right, 1024); 
}

/*
AudioBuffers AmigaProxy::createAudioBuffers(i32 size)
{
    assert(leftChannel.size == 0);
    assert(rightChannel.size == 0);

    leftChannel.alloc(size);
    rightChannel.alloc(size);

    printf("Left channel buffer: %ld at %p\n", leftChannel.size, leftChannel.ptr);
    printf("Right channel buffer: %ld at %p\n", rightChannel.size, rightChannel.ptr);

    return AudioBuffers{(u32)leftChannel.ptr, (u32)rightChannel.ptr};
}

void AmigaProxy::copyAudioBuffers()
{
    assert(leftChannel.size && leftChannel.size == rightChannel.size);
    amiga->paula.muxer.copy(leftChannel.ptr, rightChannel.ptr, leftChannel.size);
}
*/
void AmigaProxy::wasm_set_sample_rate(unsigned sample_rate)
{
    printf("set paula.muxer to freq= %d\n", sample_rate);
    amiga->host.setSampleRate(sample_rate);
    printf("amiga.host.getSampleRate()==%f\n", amiga->host.getSampleRate());
}

float sound_buffer[16384 * 2];
u32 AmigaProxy::wasm_get_sound_buffer_address()
{
  return (u32)sound_buffer;
}
int sum_samples=0;
unsigned AmigaProxy::wasm_copy_into_sound_buffer()
{
  auto count=amiga->paula.muxer.stream.count();
  
  auto copied_samples=0;
  for(unsigned ipos=1024;ipos<=count;ipos+=1024)
  {
    amiga->paula.muxer.copy(
    sound_buffer+copied_samples,
     sound_buffer+copied_samples+1024, 
     1024); 
    copied_samples+=1024*2;
//  printf("fillLevel (%lf)",wrapper->amiga->paula.muxer.stream.fillLevel());
  }
  sum_samples += copied_samples/2; 

/*  printf("copyMono[%d]: ", 16);
  for(int i=0; i<16; i++)
  {
    //printf("%hhu,",stream[i]);
    printf("%f,",sound_buffer[i]);
  }
  printf("\n"); 
*/
  return copied_samples/2;
}

void AmigaProxy::insertDisk(const string &blob, u32 len, u8 drive)
{
    printf("insertDisk(%d)\n", drive);
    try
    {
        std::stringstream stream;
        stream.write((const char *)blob.data(), len);

        if (ADFFile::isCompatible(stream))
        {
            ADFFile adf{(u8 *)blob.data(), (isize)len};
            amiga->df[drive]->swapDisk(std::make_unique<FloppyDisk>(adf));
        }

        if (EXEFile::isCompatible(stream))
        {
            EXEFile exe{(u8 *)blob.data(), (isize)len};
            amiga->df[drive]->swapDisk(std::make_unique<FloppyDisk>(exe));
        }

        if (DMSFile::isCompatible(stream))
        {
            DMSFile dms{(u8 *)blob.data(), (isize)len};
            amiga->df[drive]->swapDisk(std::make_unique<FloppyDisk>(dms));
        }
    }
    catch (VAError &err)
    {
        save(err);
        throw;
    }
}

EMSCRIPTEN_BINDINGS(AmigaProxy)
{
    class_<AmigaProxy>("AmigaProxy")
        .constructor<>()
        .function("errorCode", &AmigaProxy::errorCode)

        .function("wasm_get_sound_buffer_address", &AmigaProxy::wasm_get_sound_buffer_address)
        .function("wasm_copy_into_sound_buffer", &AmigaProxy::wasm_copy_into_sound_buffer)
        .function("wasm_set_sample_rate", &AmigaProxy::wasm_set_sample_rate)

//        .function("createAudioBuffers", &AmigaProxy::createAudioBuffers)
//        .function("copyAudioBuffers", &AmigaProxy::copyAudioBuffers)
        .function("what", &AmigaProxy::what)

        .function("configure", &AmigaProxy::configure)
        .function("configureDrive", &AmigaProxy::configureDrive)

        .function("hardReset", &AmigaProxy::hardReset)
        .function("softReset", &AmigaProxy::softReset)

        .function("poweredOn", &AmigaProxy::poweredOn)
        .function("poweredOff", &AmigaProxy::poweredOff)
        .function("isRunning", &AmigaProxy::isRunning)
        .function("isPaused", &AmigaProxy::isPaused)
        // isReady
        .function("powerOn", &AmigaProxy::powerOn)
        .function("powerOff", &AmigaProxy::powerOff)
        .function("run", &AmigaProxy::run)
        .function("pause", &AmigaProxy::pause)
        .function("halt", &AmigaProxy::halt)

        .function("insertDisk", &AmigaProxy::insertDisk)

        .function("updateAudio", &AmigaProxy::updateAudio)
        .function("leftChannelBuffer", &AmigaProxy::leftChannelBuffer)
        .function("rightChannelBuffer", &AmigaProxy::rightChannelBuffer);
}

//
// Denise proxy
//

DeniseProxy::DeniseProxy()
{
    printf("DeniseProxy()\n");
}

u32 DeniseProxy::noise() const
{
    return (u32)amiga->denise.pixelEngine.getNoise();
}

TextureWrapper DeniseProxy::getEmulatorTexture()
{
    TextureWrapper result;

    auto &buffer = amiga->denise.pixelEngine.getStableBuffer();

    result.frameNr = (u32)buffer.nr;
    result.currLof = buffer.lof;
    result.prevLof = buffer.prevlof;
    result.data = (u32)buffer.pixels.ptr;

    return result;
}

EMSCRIPTEN_BINDINGS(DeniseProxy)
{
    class_<DeniseProxy>("DeniseProxy")
        .constructor<>()
        .function("noise", &DeniseProxy::noise)
        .function("getEmulatorTexture", &DeniseProxy::getEmulatorTexture);
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

bool MemoryProxy::loadRom(const string &blob, u32 len)
{
    try
    {
        amiga->mem.loadRom((u8 *)blob.c_str(), len);
        return amiga->mem.hasRom();
    }
    catch (VAError &err)
    {
        save(err);
        throw;
    }
}

bool MemoryProxy::loadExt(const string &blob, u32 len)
{
    try
    {
        amiga->mem.loadExt((u8 *)blob.c_str(), len);
        return amiga->mem.hasExt();
    }
    catch (VAError &err)
    {
        save(err);
        throw;
    }
}

EMSCRIPTEN_BINDINGS(MemoryProxy)
{
    class_<MemoryProxy>("MemoryProxy")
        .constructor<>()
        .function("loadRom", &MemoryProxy::loadRom)
        .function("loadExt", &MemoryProxy::loadExt)
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

EMSCRIPTEN_BINDINGS(Constants)
{
    constant("HPIXELS", (int)HPIXELS);
    constant("VPIXELS", (int)VPIXELS);
    constant("TPP", (int)TPP);
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
    constant("OPT_VIDEO_FORMAT", (int)OPT_VIDEO_FORMAT);
    constant("OPT_SYNC_MODE", (int)OPT_SYNC_MODE);
    constant("OPT_PROPOSED_FPS", (int)OPT_PROPOSED_FPS);
    constant("OPT_AGNUS_REVISION", (int)OPT_AGNUS_REVISION);
    constant("OPT_SLOW_RAM_MIRROR", (int)OPT_SLOW_RAM_MIRROR);
    constant("OPT_PTR_DROPS", (int)OPT_PTR_DROPS);
    constant("OPT_DENISE_REVISION", (int)OPT_DENISE_REVISION);
    constant("OPT_VIEWPORT_TRACKING", (int)OPT_VIEWPORT_TRACKING);
    constant("OPT_PALETTE", (int)OPT_PALETTE);
    constant("OPT_BRIGHTNESS", (int)OPT_BRIGHTNESS);
    constant("OPT_CONTRAST", (int)OPT_CONTRAST);
    constant("OPT_SATURATION", (int)OPT_SATURATION);
    constant("OPT_DMA_DEBUG_ENABLE", (int)OPT_DMA_DEBUG_ENABLE);
    constant("OPT_DMA_DEBUG_MODE", (int)OPT_DMA_DEBUG_MODE);
    constant("OPT_DMA_DEBUG_OPACITY", (int)OPT_DMA_DEBUG_OPACITY);
    constant("OPT_DMA_DEBUG_CHANNEL", (int)OPT_DMA_DEBUG_CHANNEL);
    constant("OPT_DMA_DEBUG_COLOR", (int)OPT_DMA_DEBUG_COLOR);
    constant("OPT_CPU_REVISION", (int)OPT_CPU_REVISION);
    constant("OPT_CPU_DASM_REVISION", (int)OPT_CPU_DASM_REVISION);
    constant("OPT_CPU_DASM_SYNTAX", (int)OPT_CPU_DASM_SYNTAX);
    constant("OPT_CPU_OVERCLOCKING", (int)OPT_CPU_OVERCLOCKING);
    constant("OPT_CPU_RESET_VAL", (int)OPT_CPU_RESET_VAL);
    constant("OPT_RTC_MODEL", (int)OPT_RTC_MODEL);
    constant("OPT_CHIP_RAM", (int)OPT_CHIP_RAM);
    constant("OPT_SLOW_RAM", (int)OPT_SLOW_RAM);
    constant("OPT_FAST_RAM", (int)OPT_FAST_RAM);
    constant("OPT_EXT_START", (int)OPT_EXT_START);
    constant("OPT_SAVE_ROMS", (int)OPT_SAVE_ROMS);
    constant("OPT_SLOW_RAM_DELAY", (int)OPT_SLOW_RAM_DELAY);
    constant("OPT_BANKMAP", (int)OPT_BANKMAP);
    constant("OPT_UNMAPPING_TYPE", (int)OPT_UNMAPPING_TYPE);
    constant("OPT_RAM_INIT_PATTERN", (int)OPT_RAM_INIT_PATTERN);
    constant("OPT_DRIVE_CONNECT", (int)OPT_DRIVE_CONNECT);
    constant("OPT_DRIVE_SPEED", (int)OPT_DRIVE_SPEED);
    constant("OPT_LOCK_DSKSYNC", (int)OPT_LOCK_DSKSYNC);
    constant("OPT_AUTO_DSKSYNC", (int)OPT_AUTO_DSKSYNC);
    constant("OPT_DRIVE_TYPE", (int)OPT_DRIVE_TYPE);
    constant("OPT_DRIVE_MECHANICS", (int)OPT_DRIVE_MECHANICS);
    constant("OPT_DRIVE_RPM", (int)OPT_DRIVE_RPM);
    constant("OPT_DISK_SWAP_DELAY", (int)OPT_DISK_SWAP_DELAY);
    constant("OPT_DRIVE_PAN", (int)OPT_DRIVE_PAN);
    constant("OPT_STEP_VOLUME", (int)OPT_STEP_VOLUME);
    constant("OPT_POLL_VOLUME", (int)OPT_POLL_VOLUME);
    constant("OPT_INSERT_VOLUME", (int)OPT_INSERT_VOLUME);
    constant("OPT_EJECT_VOLUME", (int)OPT_EJECT_VOLUME);
    constant("OPT_HDC_CONNECT", (int)OPT_HDC_CONNECT);
    constant("OPT_HDR_TYPE", (int)OPT_HDR_TYPE);
    constant("OPT_HDR_PAN", (int)OPT_HDR_PAN);
    constant("OPT_HDR_STEP_VOLUME", (int)OPT_HDR_STEP_VOLUME);
    constant("OPT_SERIAL_DEVICE", (int)OPT_SERIAL_DEVICE);
    constant("OPT_HIDDEN_BITPLANES", (int)OPT_HIDDEN_BITPLANES);
    constant("OPT_HIDDEN_SPRITES", (int)OPT_HIDDEN_SPRITES);
    constant("OPT_HIDDEN_LAYERS", (int)OPT_HIDDEN_LAYERS);
    constant("OPT_HIDDEN_LAYER_ALPHA", (int)OPT_HIDDEN_LAYER_ALPHA);
    constant("OPT_CLX_SPR_SPR", (int)OPT_CLX_SPR_SPR);
    constant("OPT_CLX_SPR_PLF", (int)OPT_CLX_SPR_PLF);
    constant(" OPT_CLX_PLF_PLF", (int)OPT_CLX_PLF_PLF);
    constant("OPT_BLITTER_ACCURACY", (int)OPT_BLITTER_ACCURACY);
    constant("OPT_CIA_REVISION", (int)OPT_CIA_REVISION);
    constant("OPT_TODBUG", (int)OPT_TODBUG);
    constant(" OPT_ECLOCK_SYNCING", (int)OPT_ECLOCK_SYNCING);
    constant("OPT_ACCURATE_KEYBOARD", (int)OPT_ACCURATE_KEYBOARD);
    constant("OPT_PULLUP_RESISTORS", (int)OPT_PULLUP_RESISTORS);
    constant("OPT_SHAKE_DETECTION", (int)OPT_SHAKE_DETECTION);
    constant("OPT_MOUSE_VELOCITY", (int)OPT_MOUSE_VELOCITY);
    constant("OPT_AUTOFIRE", (int)OPT_AUTOFIRE);
    constant("OPT_AUTOFIRE_BULLETS", (int)OPT_AUTOFIRE_BULLETS);
    constant("OPT_AUTOFIRE_DELAY", (int)OPT_AUTOFIRE_DELAY);
    constant("OPT_SAMPLING_METHOD", (int)OPT_SAMPLING_METHOD);
    constant("OPT_FILTER_TYPE", (int)OPT_FILTER_TYPE);
    constant("OPT_FILTER_ACTIVATION", (int)OPT_FILTER_ACTIVATION);
    constant("OPT_AUDPAN", (int)OPT_AUDPAN);
    constant("OPT_AUDVOL", (int)OPT_AUDVOL);
    constant("OPT_AUDVOLL", (int)OPT_AUDVOLL);
    constant("OPT_AUDVOLR", (int)OPT_AUDVOLR);
    constant("OPT_DIAG_BOARD", (int)OPT_DIAG_BOARD);
    constant("OPT_SRV_PORT", (int)OPT_SRV_PORT);
    constant("OPT_SRV_PROTOCOL", (int)OPT_SRV_PROTOCOL);
    constant("OPT_SRV_AUTORUN", (int)OPT_SRV_AUTORUN);
    constant("OPT_SRV_VERBOSE", (int)OPT_SRV_VERBOSE);
}
