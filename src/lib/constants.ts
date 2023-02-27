import type { KeyMap } from "$lib/types";

export const TPP                = 1;

export const CLK_FREQUENCY_PAL  = 28375160;
export const CLK_FREQUENCY_NTSC = 28636360;

export const VPOS_CNT_PAL_LF    = 313;
export const VPOS_CNT_PAL_SF    = 312;
export const VPOS_MAX_PAL_LF    = 312;
export const VPOS_MAX_PAL_SF    = 311;
export const VPOS_CNT_PAL       = VPOS_CNT_PAL_LF;
export const VPOS_MAX_PAL       = VPOS_MAX_PAL_LF;

export const VPOS_CNT_NTSC_LF   = 263;
export const VPOS_CNT_NTSC_SF   = 262;
export const VPOS_MAX_NTSC_LF   = 262;
export const VPOS_MAX_NTSC_SF   = 261;
export const VPOS_CNT_NTSC      = VPOS_CNT_NTSC_LF;
export const VPOS_MAX_NTSC      = VPOS_MAX_NTSC_LF;

export const VPOS_CNT           = VPOS_CNT_PAL;
export const VPOS_MAX           = VPOS_MAX_PAL;

export const HPOS_CNT_PAL       = 227;
export const HPOS_MAX_PAL       = 226;

export const HPOS_CNT_NTSC_LL   = 228;
export const HPOS_CNT_NTSC_SL   = 227;
export const HPOS_MAX_NTSC_LL   = 227;
export const HPOS_MAX_NTSC_SL   = 226;
export const HPOS_CNT_NTSC      = HPOS_CNT_NTSC_LL;
export const HPOS_MAX_NTSC      = HPOS_MAX_NTSC_LL;

export const HPOS_MAX           = HPOS_MAX_NTSC_LL;
export const HPOS_CNT           = HPOS_CNT_NTSC_LL;

export const VPIXELS            = 313;
export const HPIXELS            = 912;

export const HBLANK_MIN         = 0x12;
export const HBLANK_MAX         = 0x23;
export const HBLANK_CNT         = 0x12;

export const VBLANK_MIN         = 0x00;
export const VBLANK_MAX         = 0x19;
export const VBLANK_CNT         = 0x1A;

export const AMIGA_KEYS: KeyMap = {
    'Escape':         0x45,
    'F1':             0x50,
    'F2':             0x51,
    'F3':             0x52,
    'F4':             0x53,
    'F5':             0x54,
    'F6':             0x55,
    'F7':             0x56,
    'F8':             0x57,
    'F9':             0x58,
    'F10':            0x59,
    'F11':            0x66, //Left Amiga
    'F12':            0x67, //Right Amiga
    'Backquote':      0x00,
    'Digit1':         0x01,
    'Digit2':         0x02,
    'Digit3':         0x03,
    'Digit4':         0x04,
    'Digit5':         0x05,
    'Digit6':         0x06,
    'Digit7':         0x07,
    'Digit8':         0x08,
    'Digit9':         0x09,
    'Digit0':         0x0a,
    'Minus':          0x0b,
    'Equal':          0x0c,
    'Backspace':      0x41,
    'Tab':            0x42,
    'KeyQ':           0x10,
    'KeyW':           0x11,
    'KeyE':           0x12,
    'KeyR':           0x13,
    'KeyT':           0x14,
    'KeyY':           0x15,
    'KeyU':           0x16,
    'KeyI':           0x17,
    'KeyO':           0x18,
    'KeyP':           0x19,
    'BracketLeft':    0x1a,
    'BracketRight':   0x1b,
    'Backslash':      0x0d,
    'CapsLock':       0x62,
    'KeyA':           0x20,
    'KeyS':           0x21,
    'KeyD':           0x22,
    'KeyF':           0x23,
    'KeyG':           0x24,
    'KeyH':           0x25,
    'KeyJ':           0x26,
    'KeyK':           0x27,
    'KeyL':           0x28,
    'Semicolon':      0x29,
    'Quote':          0x2a,
    'Enter':          0x44,
    'ShiftLeft':      0x60,
    'KeyZ':           0x31,
    'KeyX':           0x32,
    'KeyC':           0x33,
    'KeyV':           0x34,
    'KeyB':           0x35,
    'KeyN':           0x36,
    'KeyM':           0x37,
    'Comma':          0x38,
    'Period':         0x39,
    'Slash':          0x3a,
    'ShiftRight':     0x61,
    'ControlLeft':    0x63,
    'AltLeft':        0x64,
    'MetaLeft':       0x66, //Left Amiga
    'Space':          0x40,
    'AltRight':       0x65,
    'MetaRight':      0x67, //Right Amiga
    'ControlRight':   0x63,
    'Delete':         0x46,
    'End':            0x5f, //Help
    'PageDown':       0x45, //Esc
    'ArrowUp':        0x4c,
    'ArrowDown':      0x4d,
    'ArrowRight':     0x4e,
    'ArrowLeft':      0x4f,
    'NumpadDivide':   0x5c,
    'NumpadMultiply': 0x5d,
    'NumpadSubtract': 0x4a,
    'Numpad7':        0x3d,
    'Numpad8':        0x3e,
    'Numpad9':        0x3f,
    'NumpadAdd':      0x5e,
    'Numpad4':        0x2d,
    'Numpad5':        0x2e,
    'Numpad6':        0x2f,
    'Numpad1':        0x1d,
    'Numpad2':        0x1e,
    'Numpad3':        0x1f,
    'NumpadEnter':    0x43,
    'Numpad0':        0x0f,
    'NumpadDecimal':  0x3c
  };

  export const CRC32 = {
    'Aros':           1062194186,
    'Kick12':         2798523958,
    'Kick13':         3304125791,
    'DiagROM':        2231503309
  };
