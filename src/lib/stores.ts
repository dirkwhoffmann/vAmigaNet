import { writable, type Writable } from 'svelte/store';
import { Layer, WarpMode, Theme, RenderMode } from '$lib/types'
import type { KeySet } from '$lib/types';

// Gateway to the WASM backend
export const proxy: any = writable();

// Proxies
export const agnus: any = writable();
export const amiga: any = writable();
export const cpu: any = writable();
export const denise: any = writable();
export const diskController: any = writable();
export const enums: any = writable();
export const joystick1: any = writable();
export const joystick2: any = writable();
export const keyboard: any = writable();
export const memory: any = writable();
export const mouse1: any = writable();
export const mouse2: any = writable();
export const retroShell: any = writable();

// Global components
export const audio: any = writable();

// Theming
export const theme = writable(Theme.default);
export const darkTheme = writable(true);

// Settings (move to settings store?!)
export const renderMode = writable(RenderMode.smooth);
export const flickerWeight = writable(50);
export const warpMode = writable(WarpMode.auto);
export const texSampler = writable(1);
export const border = writable(0);
export const shaking = writable(1);

// Control ports (connected devices)
export const port1 = writable(1);
export const port2 = writable(0);

// Emulation keysets
export const keyset1: Writable<KeySet> = writable();
export const keyset2: Writable<KeySet> = writable();
// export const keyset1 = writable();
// export const keyset2 = writable();

// Layout
export const canvasWidth = writable(0);
export const canvasHeight = writable(0);
export const aspectWidth = writable(0);
export const aspectHeight = writable(0);

// GUI state
export const layout = writable('fit');
export const showSidebar = writable(false);
export const layer = writable(Layer.none);
export const showImpressum = writable(false); // DEPRECATED. USE layer
export const activeSlider = writable(0);

// Drag and Drop
export const dragItem: Writable<Uint8Array | null> = writable(null);

// Emulator state
export const wasmInitialized = writable(false);
export const initialized = writable(false);
export const poweredOn = writable(false);
export const running = writable(false);
export const warp = writable(false);
export const muted = writable(false);
export const halted = writable(false);
export const debugMode = writable(false);
export const debugDma = writable(false);
export const dfConnected = writable([false,false,false,false]);
export const dfHasDisk = writable([false,false,false,false]);
export const dfMotor = writable([false,false,false,false]);
export const dfWriting = writable([false,false,false,false]);
export const dfUnsaved = writable([false,false,false,false]);
export const dfProtected = writable([false,false,false,false]);
export const dfCylinder = writable([0,0,0,0]);
export const romcrc = writable(0);

// Error state
export const errno = writable(0);
export const what = writable('');

// Message counters
export const MsgNone = writable(0);
export const MsgRegister = writable(0);
export const MsgConfig = writable(0);
export const MsgPowerOn = writable(0);
export const MsgPowerOff = writable(0);
export const MsgRun = writable(0);
export const MsgPause = writable(0);
export const MsgStep = writable(0);
export const MsgReset = writable(0);
export const MsgHalt = writable(0);
export const MsgAbort = writable(0);
export const MsgWarpOn = writable(0);
export const MsgWarpOff = writable(0);
export const MsgDebugOn = writable(0);
export const MsgDebugOff = writable(0);
export const MsgMuteOn = writable(0);
export const MsgMuteOff = writable(0);
export const MsgPowerLedOn = writable(0);
export const MsgPowerLedDim = writable(0);
export const MsgPowerLedOff = writable(0);
export const MsgCloseConsole = writable(0);
export const MsgUpdateConsole = writable(0);
export const MsgScriptDone = writable(0);
export const MsgScriptPause = writable(0);
export const MsgScriptAbort = writable(0);
export const MsgScriptWakeup = writable(0);
export const MsgVideoFormat = writable(0);
export const MsgOverclocking = writable(0);
export const MsgBreakpointReached = writable(0);
export const MsgBreakpointUpdated = writable(0);
export const MsgWatchpointReached = writable(0);
export const MsgWatchpointUpdated = writable(0);
export const MsgCatchpointReached = writable(0);
export const MsgCatchpointUpdated = writable(0);
export const MsgSwTrapReached = writable(0);
export const MsgCpuHalt = writable(0);
export const MsgCopperBpReached = writable(0);
export const MsgCopperBpUpdated = writable(0);
export const MsgCopperWpReached = writable(0);
export const MsgCopperWpUpdated = writable(0);
export const MsgViewport = writable(0);
export const MsgMemLayout = writable(0);
export const MsgDriveConnect = writable(0);
export const MsgDriveDisconnect = writable(0);
export const MsgDriveSelect = writable(0);
export const MsgDriveRead = writable(0);
export const MsgDriveWrite = writable(0);
export const MsgDriveLedOn = writable(0);
export const MsgDriveLedOff = writable(0);
export const MsgDriveMotorOn = writable(0);
export const MsgDriveMotorOff = writable(0);
export const MsgDriveStep = writable(0);
export const MsgDrivePoll = writable(0);
export const MsgDiskInsert = writable(0);
export const MsgDiskEject = writable(0);
export const MsgDiskSaved = writable(0);
export const MsgDiskUnsaved = writable(0);
export const MsgDiskProtect = writable(0);
export const MsgDiskUnprotect = writable(0);
export const MsgHdcConnect = writable(0);
export const MsgHdcDisconnect = writable(0);
export const MsgHdcState = writable(0);
export const MsgHdrStep = writable(0);
export const MsgHdrRead = writable(0);
export const MsgHdrWrite = writable(0);
export const MsgHdrIdle = writable(0);
export const MsgCtrlAmigaAmiga = writable(0);
export const MsgShaking = writable(0);
export const MsgSerIn = writable(0);
export const MsgSerOut = writable(0);
export const MsgAutoSnapshotTaken = writable(0);
export const MsgUserSnapshotTaken = writable(0);
export const MsgSnapshotRestored = writable(0);
export const MsgRecordingStarted = writable(0);
export const MsgRecordingStopped = writable(0);
export const MsgRecordingAborted = writable(0);
export const MsgDmaDebugOn = writable(0);
export const MsgDmaDebugOff = writable(0);
export const MsgSrvState = writable(0);
export const MsgSrvReceive = writable(0);
export const MsgSrvSend = writable(0);
