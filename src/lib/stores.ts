import { writable, type Writable } from 'svelte/store';
import { Layer } from '$lib/types'
import type { KeySet } from '$lib/types';
import type { RomEntry } from './Db/db';

// Gateway to the WASM backend
export const proxy: any = writable();
export const initialized = writable(false);

// Proxies
export const agnus: any = writable();
export const amiga: any = writable();
export const cpu: any = writable();
export const denise: any = writable();
export const df0: any = writable();
export const df1: any = writable();
export const df2: any = writable();
export const df3: any = writable();
export const diskController: any = writable();
export const enums: any = writable();
export const hd0: any = writable();
export const hd1: any = writable();
export const hd2: any = writable();
export const hd3: any = writable();
export const joystick1: any = writable();
export const joystick2: any = writable();
export const keyboard: any = writable();
export const memory: any = writable();
export const mouse1: any = writable();
export const mouse2: any = writable();
export const paula: any = writable();
export const retroShell: any = writable();

// Global components
export const audio: any = writable();
export const config: any = writable();
export const gamepadManager: any = writable();

// Theming
export const darkTheme = writable(true);
export const invert = writable('invert');

// Settings (move to settings store?!)

// Control ports (connected devices)
export const port1 = writable(1);
export const port2 = writable(0);

// Emulation keysets
export const keyset1: Writable<KeySet> = writable();
export const keyset2: Writable<KeySet> = writable();

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
export const dragType = writable('');

// Emulator state
export const poweredOn = writable(false);
export const running = writable(false);
export const warp = writable(false);
export const warpMode = writable(0);
export const track = writable(false);
export const muted = writable(false);
export const halted = writable(false);
export const debugDma = writable(false);
export const dfConnected = writable([false,false,false,false]);
export const dfHasDisk = writable([false,false,false,false]);
export const dfMotor = writable([false,false,false,false]);
export const dfWriting = writable([false,false,false,false]);
export const dfUnsaved = writable([false,false,false,false]);
export const dfProtected = writable([false,false,false,false]);
export const dfCylinder = writable([0,0,0,0]);
export const hdConnected = writable([false,false,false,false]);
export const hdReading = writable([false,false,false,false]);
export const hdWriting = writable([false,false,false,false]);
export const hdUnsaved = writable([false,false,false,false]);
export const hdCylinder = writable([0,0,0,0]);

// Kickstarts
export const kickstarts: Writable<RomEntry[]> = writable([]); 
export const romcrc = writable(0);

// Error state
export const errno = writable(0);
export const what = writable('');

// Message counters
export const MsgNone = writable(0);
export const MsgConfig = writable(0);
export const MsgPower = writable(0);
export const MsgRun = writable(0);
export const MsgPause = writable(0);
export const MsgStep = writable(0);
export const MsgReset = writable(0);
export const MsgShutdown = writable(0);
export const MsgAbort = writable(0);
export const MsgWarp = writable(0);
export const MsgTrack = writable(0);
export const MsgMute = writable(0);
export const MsgPowerLedOn = writable(0);
export const MsgPowerLedDim = writable(0);
export const MsgPowerLedOff = writable(0);
export const MsgConsoleClose = writable(0);
export const MsgConsoleUpdate = writable(0);
export const MsgConsoleDebugger = writable(0);
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
export const MsgDriveSelect = writable(0);
export const MsgDriveRead = writable(0);
export const MsgDriveWrite = writable(0);
export const MsgDriveLed = writable(0);
export const MsgDriveMotor = writable(0);
export const MsgDriveStep = writable(0);
export const MsgDrivePoll = writable(0);
export const MsgDiskInsert = writable(0);
export const MsgDiskEject = writable(0);
export const MsgDiskProtected = writable(0);
export const MsgHdcConnect = writable(0);
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
export const MsgDmaDebug = writable(0);
export const MsgSrvState = writable(0);
export const MsgSrvReceive = writable(0);
export const MsgSrvSend = writable(0);
export const MsgAlarm = writable(0);
