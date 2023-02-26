<svelte:options accessors={true} />

<script lang="ts">
	import type { DataBaseItem } from '$lib/types';
	import { onMount } from 'svelte';
	import { WarpMode } from '$lib/types';
	import {
		proxy,
		audio,
		agnus,
		amiga,
		cpu,
		denise,
		diskController,
		enums,
		joystick1,
		joystick2,
		keyboard,
		memory,
		mouse1,
		mouse2,
		retroShell,
		MsgNone,
		MsgRegister,
		MsgConfig,
		MsgPowerOn,
		MsgPowerOff,
		MsgRun,
		MsgPause,
		MsgStep,
		MsgReset,
		MsgShutdown,
		MsgAbort,
		MsgWarpOn,
		MsgWarpOff,
		MsgDebugOn,
		MsgDebugOff,
		MsgMuteOn,
		MsgMuteOff,
		MsgPowerLedOn,
		MsgPowerLedDim,
		MsgPowerLedOff,
		MsgCloseConsole,
		MsgUpdateConsole,
		MsgScriptDone,
		MsgScriptPause,
		MsgScriptAbort,
		MsgScriptWakeup,
		MsgVideoFormat,
		MsgOverclocking,
		MsgBreakpointReached,
		MsgBreakpointUpdated,
		MsgWatchpointReached,
		MsgWatchpointUpdated,
		MsgCatchpointReached,
		MsgCatchpointUpdated,
		MsgSwTrapReached,
		MsgCpuHalt,
		MsgCopperBpReached,
		MsgCopperBpUpdated,
		MsgCopperWpReached,
		MsgCopperWpUpdated,
		MsgViewport,
		MsgMemLayout,
		MsgDriveConnect,
		MsgDriveDisconnect,
		MsgDriveSelect,
		MsgDriveRead,
		MsgDriveWrite,
		MsgDriveLedOn,
		MsgDriveLedOff,
		MsgDriveMotorOn,
		MsgDriveMotorOff,
		MsgDriveStep,
		MsgDrivePoll,
		MsgDiskInsert,
		MsgDiskEject,
		MsgDiskSaved,
		MsgDiskUnsaved,
		MsgDiskProtect,
		MsgDiskUnprotect,
		MsgHdcConnect,
		MsgHdcDisconnect,
		MsgHdcState,
		MsgHdrStep,
		MsgHdrRead,
		MsgHdrWrite,
		MsgHdrIdle,
		MsgCtrlAmigaAmiga,
		MsgShaking,
		MsgSerIn,
		MsgSerOut,
		MsgAutoSnapshotTaken,
		MsgUserSnapshotTaken,
		MsgSnapshotRestored,
		MsgRecordingStarted,
		MsgRecordingStopped,
		MsgRecordingAborted,
		MsgDmaDebugOn,
		MsgDmaDebugOff,
		MsgSrvState,
		MsgSrvReceive,
		MsgSrvSend
	} from '$lib/stores';
	import {
		initialized,
		poweredOn,
		running,
		warpMode,
		warp,
		muted,
		halted,
		debugMode,
		romcrc
	} from '$lib/stores';
	import {
		dfConnected,
		dfHasDisk,
		dfMotor,
		dfWriting,
		dfUnsaved,
		dfCylinder,
		dfProtected
	} from '$lib/stores';
	import { debugDma, keyset1, keyset2 } from '$lib/stores';
	import { db, type RomEntry } from '$lib/Db/db';
	import { AMIGA_KEYS } from './constants';

	onMount(() => {
		console.log('Proxy: onMount()');

		// Prepare to receive messages
		$proxy.processMsg = processMsg;
	});

	export async function runShowcase(showcase: DataBaseItem) {
		await $audio.setup();
		try {
			console.log('Showcase:', showcase.title);
			$amiga.powerOff();
			if (showcase.requiredRom) {
				console.log('Installing Rom:', showcase.requiredRom);
				$proxy.installRom(showcase.requiredRom);
			}
			console.log('Configuring CHIP:', showcase.memory[0]);
			$amiga.configure($proxy.OPT_CHIP_RAM, showcase.memory[0]);
			console.log('Configuring SLOW:', showcase.memory[1]);
			$amiga.configure($proxy.OPT_SLOW_RAM, showcase.memory[1]);
			console.log('Configuring FAST:', showcase.memory[2]);
			$amiga.configure($proxy.OPT_FAST_RAM, showcase.memory[2]);
			for (let i = 0; i < showcase.adf.length; i++) {
				console.log('Inserting disk ' + i + ':', showcase.adf[i]);
				await insert(showcase.adf[i], i);
			}
			console.log('Configuring warp mode: ' + showcase.warp);
			$warpMode = showcase.warp;

			$amiga.run();

			// Set GUI timer to manage disk changes
			if (showcase.title == 'Absolute Inebriation') {
				console.log("Scheduling disk change (inebriation)");
				$agnus.scheduleGUITimerAbs(100, 42);
			}
			if (showcase.title == 'Eon') {
				console.log("Scheduling disk change (eon)");
				$agnus.scheduleGUITimerAbs(100, 42);
			}

		} catch (exception) {
			console.log('CATCHED ' + exception);
			throw exception;
			// console.error($amiga.getExceptionMessage(exception));
		}
	}

	export function reportException() {
		console.error('Exception ' + $amiga.errorCode() + ': ' + $amiga.what());
	}

	export async function insert(name: string, drive: number) {
		try {
			console.log('Fetching adf/' + name);
			let response = await fetch('adf/' + name);
			let blob = await response.arrayBuffer();
			let uint8View = new Uint8Array(blob);
			console.log('Calling $amiga.insertDisk');
			$amiga.insertDisk(uint8View, blob.byteLength, drive);
		} catch (exc) {
			reportException();
		}
	}

	export async function installRom(crc32: number) {
		if (crc32 == 0) {
			$memory.deleteRom();
			$memory.deleteExt();
			$romcrc = crc32;
			return true;
		}
		try {
			const item = await db.roms.get(crc32);
			if (!item) {
				return false;
			}

			if (item?.rom) {
				$memory.loadRom(item!.rom, item!.rom!.length);
				$romcrc = crc32;
			} else {
				$memory.deleteRom();
			}
			if (item?.ext) {
				$memory.loadExt(item!.ext, item!.ext!.length);
			} else {
				$memory.deleteExt();
			}
			console.log('Rom added', item?.title);
			return true;
		} catch (error) {
			console.log(`installRom failed: `, error);
			return false;
		}
	}

	export async function installRoms(crcs: [number]) {
		for (const crc of crcs) {
			console.log('Trying to install ROM', crc);
			const success = await installRom(crc);
			if (success) {
				console.log('SUCCESS.');
				return true;
			} else {
				console.log('FAILED.');
			}
		}
		return false;
	}

	export async function installAros() {
		installRom(1062194186);
	}

	export async function installDiagRom() {
		installRom(2231503309);
	}

	$: updateWarp($warpMode);
	export function updateWarp(warpMode: WarpMode) {
		if (!$amiga) return;

		let newWarp = false;
		switch (warpMode) {
			case WarpMode.auto:
				newWarp = $diskController.isSpinning();
				break;
			case WarpMode.never:
				newWarp = false;
				break;
			case WarpMode.always:
				newWarp = true;
				break;
		}
		if (newWarp) {
			$amiga.warpOn();
		} else {
			$amiga.warpOff();
		}
	}

	export function onRuntimeInitialized() {
		console.log('Creating proxies...');
		$agnus = new $proxy.AgnusProxy();
		$amiga = new $proxy.AmigaProxy();
		$cpu = new $proxy.CPUProxy();
		$denise = new $proxy.DeniseProxy();
		$diskController = new $proxy.DiskControllerProxy();
		$enums = new $proxy.EnumProxy();
		$joystick1 = new $proxy.JoystickProxy(1);
		$joystick2 = new $proxy.JoystickProxy(2);
		$keyboard = new $proxy.KeyboardProxy();
		$memory = new $proxy.MemoryProxy();
		$mouse1 = new $proxy.MouseProxy(1);
		$mouse2 = new $proxy.MouseProxy(2);
		$retroShell = new $proxy.RetroShellProxy();

		console.log('Configuring the emulator...');

		// Apply some default settings
		$amiga.configure($proxy.OPT_AGNUS_REVISION, $proxy.AGNUS_ECS_2MB);

		$keyset1 = {
			ArrowLeft: $proxy.PULL_LEFT,
			ArrowRight: $proxy.PULL_RIGHT,
			ArrowUp: $proxy.PULL_UP,
			ArrowDown: $proxy.PULL_DOWN,
			ControlRight: $proxy.PRESS_FIRE,
			Space: $proxy.PRESS_FIRE
		};

		$keyset2 = {
			KeyS: $proxy.PULL_LEFT,
			KeyD: $proxy.PULL_RIGHT,
			KeyE: $proxy.PULL_UP,
			KeyX: $proxy.PULL_DOWN,
			KeyC: $proxy.RELEASE_FIRE
		};

		(async () => {
			console.log('Installing Roms...');

			// Install AROS
			const defaultRoms = [
				3304125791, // Kickstart 1.3
				2798523958, // Kickstart 1.2
				3283989056, // Kickstart 2.04
				1062194186 // Aros
			];

			$proxy.installRoms(defaultRoms);

			console.log('Initialization completed');
			$initialized = true;
		})();

		// Trigger an exception (for debugging, only)
		// $amiga.configure($proxy.OPT_AGNUS_REVISION, 42);
	}

	function processMsg(id: number, d1: number, d2: number, d3: number, d4: number) {
		// console.log(`Message: ${$enums.MsgTypeKey(id)}(${d1}, ${d2}, ${d3}, ${d4})`);

		switch (id) {
			case $proxy.MSG_NONE:
				$MsgNone++;
				break;

			case $proxy.MSG_REGISTER:
				$MsgRegister++;
				break;

			case $proxy.MSG_CONFIG:
				$MsgConfig++;
				break;

			case $proxy.MSG_POWER_ON:
				$MsgPowerOn++;
				$poweredOn = true;
				break;

			case $proxy.MSG_POWER_OFF:
				$MsgPowerOff++;
				$poweredOn = false;
				$running = false;
				break;

			case $proxy.MSG_RUN:
				$MsgRun++;
				$running = true;
				break;

			case $proxy.MSG_PAUSE:
				$MsgPause++;
				$running = false;
				break;

			case $proxy.MSG_STEP:
				$MsgStep++;
				break;

			case $proxy.MSG_RESET:
				$MsgReset++;
				updateWarp($warpMode);
				$halted = false;
				break;

			case $proxy.MSG_SHUTDOWN:
				$MsgShutdown++;
				break;

			case $proxy.MSG_ABORT:
				$MsgAbort++;
				break;

			case $proxy.MSG_WARP_ON:
				$MsgWarpOn++;
				$warp = true;
				break;

			case $proxy.MSG_WARP_OFF:
				$MsgWarpOff++;
				$warp = false;
				break;

			case $proxy.MSG_DEBUG_ON:
				$MsgDebugOn++;
				console.log('debug mode on');
				$debugMode = true;
				break;

			case $proxy.MSG_DEBUG_OFF:
				$MsgDebugOff++;
				console.log('debug mode off');
				$debugMode = false;
				break;

			case $proxy.MSG_MUTE_ON:
				$MsgMuteOn++;
				$muted = true;
				break;

			case $proxy.MSG_MUTE_OFF:
				$MsgMuteOff++;
				$muted = false;
				break;

			case $proxy.MSG_POWER_LED_ON:
				$MsgPowerLedOn++;
				break;

			case $proxy.MSG_POWER_LED_DIM:
				$MsgPowerLedDim++;
				break;

			case $proxy.MSG_POWER_LED_OFF:
				$MsgPowerLedOff++;
				break;

			case $proxy.MSG_CLOSE_CONSOLE:
				$MsgCloseConsole++;
				break;

			case $proxy.MSG_UPDATE_CONSOLE:
				$MsgUpdateConsole++;
				break;

			case $proxy.MSG_SCRIPT_DONE:
				$MsgScriptDone++;
				break;

			case $proxy.MSG_SCRIPT_PAUSE:
				$MsgScriptPause++;
				break;

			case $proxy.MSG_SCRIPT_ABORT:
				$MsgScriptAbort++;
				break;

			case $proxy.MSG_SCRIPT_WAKEUP:
				$MsgScriptWakeup++;
				break;

			case $proxy.MSG_VIDEO_FORMAT:
				$MsgVideoFormat++;
				break;

			case $proxy.MSG_OVERCLOCKING:
				$MsgOverclocking++;
				break;

			case $proxy.MSG_BREAKPOINT_REACHED:
				$MsgBreakpointReached++;
				break;

			case $proxy.MSG_BREAKPOINT_UPDATED:
				$MsgBreakpointUpdated++;
				break;

			case $proxy.MSG_WATCHPOINT_REACHED:
				$MsgWatchpointReached++;
				break;

			case $proxy.MSG_WATCHPOINT_UPDATED:
				$MsgWatchpointUpdated++;
				break;

			case $proxy.MSG_CATCHPOINT_REACHED:
				$MsgCatchpointReached++;
				break;

			case $proxy.MSG_CATCHPOINT_UPDATED:
				$MsgCatchpointUpdated++;
				break;

			case $proxy.MSG_SWTRAP_REACHED:
				$MsgSwTrapReached++;
				break;

			case $proxy.MSG_CPU_HALT:
				$MsgCpuHalt++;
				$halted = true;
				break;

			case $proxy.MSG_COPPERBP_REACHED:
				$MsgCopperBpReached++;
				break;

			case $proxy.MSG_COPPERBP_UPDATED:
				$MsgCopperBpUpdated++;
				break;

			case $proxy.MSG_COPPERWP_REACHED:
				$MsgCopperWpReached++;
				break;

			case $proxy.MSG_COPPERWP_UPDATED:
				$MsgCopperWpUpdated++;
				break;

			case $proxy.MSG_VIEWPORT:
				$MsgViewport++;
				break;

			case $proxy.MSG_MEM_LAYOUT:
				$MsgMemLayout++;
				break;

			case $proxy.MSG_DRIVE_CONNECT:
				$MsgDriveConnect++;
				$dfConnected[d1] = true;
				break;

			case $proxy.MSG_DRIVE_DISCONNECT:
				$MsgDriveDisconnect++;
				$dfConnected[d1] = false;
				break;

			case $proxy.MSG_DRIVE_SELECT:
				$MsgDriveSelect++;
				break;

			case $proxy.MSG_DRIVE_READ:
				$MsgDriveRead++;
				break;

			case $proxy.MSG_DRIVE_WRITE:
				$MsgDriveWrite++;
				$dfWriting[d1] = d2 == 1;
				break;

			case $proxy.MSG_DRIVE_LED_ON:
				$MsgDriveLedOn++;
				break;

			case $proxy.MSG_DRIVE_LED_OFF:
				$MsgDriveLedOff++;
				break;

			case $proxy.MSG_DRIVE_MOTOR_ON:
				$MsgDriveMotorOn++;
				$dfMotor[d1] = true;
				updateWarp($warpMode);
				break;

			case $proxy.MSG_DRIVE_MOTOR_OFF:
				$MsgDriveMotorOff++;
				$dfMotor[d1] = false;
				updateWarp($warpMode);
				break;

			case $proxy.MSG_DRIVE_STEP:
				$MsgDriveStep++;
				$dfCylinder[d1] = d2;
				$audio.playStepSound(d3, d4);
				break;

			case $proxy.MSG_DRIVE_POLL:
				$MsgDrivePoll++;
				$dfCylinder[d1] = d2;
				$audio.playStepSound(d3, d4);
				break;

			case $proxy.MSG_DISK_INSERT:
				$MsgDiskInsert++;
				$dfHasDisk[d1] = true;
				$audio.playInsertSound(d3, d4);
				break;

			case $proxy.MSG_DISK_EJECT:
				$MsgDiskEject++;
				$dfHasDisk[d1] = false;
				$audio.playEjectSound(d3, d4);
				break;

			case $proxy.MSG_DISK_SAVED:
				$MsgDiskSaved++;
				$dfUnsaved[d1] = false;
				break;

			case $proxy.MSG_DISK_UNSAVED:
				$MsgDiskUnsaved++;
				$dfUnsaved[d1] = true;
				break;

			case $proxy.MSG_DISK_PROTECT:
				$MsgDiskProtect++;
				$dfProtected[d1] = true;
				break;

			case $proxy.MSG_DISK_UNPROTECT:
				$MsgDiskUnprotect++;
				$dfProtected[d1] = false;
				break;

			case $proxy.MSG_HDC_CONNECT:
				$MsgHdcConnect++;
				break;

			case $proxy.MSG_HDC_DISCONNECT:
				$MsgHdcDisconnect++;
				break;

			case $proxy.MSG_HDC_STATE:
				$MsgHdcState++;
				break;

			case $proxy.MSG_HDR_STEP:
				$MsgHdrStep++;
				break;

			case $proxy.MSG_HDR_READ:
				$MsgHdrRead++;
				break;

			case $proxy.MSG_HDR_WRITE:
				$MsgHdrWrite++;
				break;

			case $proxy.MSG_HDR_IDLE:
				$MsgHdrIdle++;
				break;

			case $proxy.MSG_CTRL_AMIGA_AMIGA:
				$MsgCtrlAmigaAmiga++;
				break;

			case $proxy.MSG_SHAKING:
				console.log('MSG_SHAKING');
				$MsgShaking++;
				break;

			case $proxy.MSG_SER_IN:
				// console.log("SER_IN: ", String.fromCharCode(d1 & 0xFF));
				$MsgSerIn++;
				break;

			case $proxy.MSG_SER_OUT:
				// console.log("SER_OUT: ", String.fromCharCode(d1 & 0xFF));
				$MsgSerOut++;
				break;

			case $proxy.MSG_AUTO_SNAPSHOT_TAKEN:
				$MsgAutoSnapshotTaken++;
				break;

			case $proxy.MSG_USER_SNAPSHOT_TAKEN:
				$MsgUserSnapshotTaken++;
				break;

			case $proxy.MSG_SNAPSHOT_RESTORED:
				$MsgSnapshotRestored++;
				updateWarp($warpMode);
				break;

			case $proxy.MSG_RECORDING_STARTED:
				$MsgRecordingStarted++;
				break;

			case $proxy.MSG_RECORDING_STOPPED:
				$MsgRecordingStopped++;
				break;

			case $proxy.MSG_RECORDING_ABORTED:
				$MsgRecordingAborted++;
				break;

			case $proxy.MSG_DMA_DEBUG_ON:
				$MsgDmaDebugOn++;
				$debugDma = true;
				break;

			case $proxy.MSG_DMA_DEBUG_OFF:
				$MsgDmaDebugOff++;
				$debugDma = false;
				break;

			case $proxy.MSG_SRV_STATE:
				$MsgSrvState++;
				break;

			case $proxy.MSG_SRV_RECEIVE:
				$MsgSrvReceive++;
				break;

			case $proxy.MSG_SRV_SEND:
				$MsgSrvSend++;
				break;

			case $proxy.MSG_GUI_EVENT:
				console.log("MSG_GUI_EVENT received");
				break;

			default:
				break;
		}
	}
</script>
