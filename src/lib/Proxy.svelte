<svelte:options accessors={true}/>

<script lang="ts">
	import { onMount } from 'svelte';
	import { goto } from '$app/navigation';
	import {
		proxy,
		enums,
		amiga,
		denise,
		memory,
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
		MsgHalt,
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
	import { poweredOn, running } from '$lib/stores';

	export let audioContext: AudioContext | null = null;

	onMount(() => {
		console.log('Proxy: onMount()');

		// Prepare to receive messages
		$proxy.processMsg = processMsg;
	});

	export async function setupAudio() {
		if (audioContext != null) {
			console.log('Audio context already initialized');
			console.log(`audioContext=${audioContext.state}`);
			if(audioContext.state==="suspended")
			{
				audioContext.resume();
			}			
			return;
		}
		audioContext = new AudioContext();
		let gainNode = audioContext.createGain();
		gainNode.gain.value = 0.2;
		gainNode.connect(audioContext.destination);
		
	    console.log("After createGain: " + audioContext.state);
		const sampleRate = audioContext.sampleRate;
		console.log('Sample rate = ' + sampleRate);
		console.log('Channels: ', audioContext.destination.channelCount);
		$amiga.setSampleRate(audioContext.sampleRate);
		console.log('Adding audio processor...');
		await audioContext.audioWorklet.addModule('js/audio-processor.js');
		console.log('Creating audio node...');
		const audioNode = new AudioWorkletNode(audioContext, 'audio-processor', {
			outputChannelCount: [2]
		});
		audioNode.port.onmessage = (e) => {
			let offset = e.data as number;
			$amiga.updateAudio(e.data);
		};
		audioNode.connect(audioContext.destination);
		const buffers = [$amiga.leftChannelBuffer(), $amiga.rightChannelBuffer()];
		audioNode.port.postMessage({
			cmd: 'bind',
			pointers: buffers,
			buffer: $proxy.HEAPF32.buffer,
			length: 1024
		});
		console.log("State in setup: " + audioContext.state);
		if(audioContext.state==="suspended")
		{	console.log(audioContext.state);
			audioContext.resume();
			audioContext.onstatechange = () => console.log("onstatechange: " + audioContext.state);
		}			
		console.log(`audioContext=${audioContext.state}`);
	}

	export async function runShowcase(showcase: DataBaseItem) {
		console.log('Setting up audio...');
		await setupAudio();

		try {
			console.log('Running ' + showcase.title + '...');
			$amiga.powerOff();
			console.log('Configuring CHIP: ' + showcase.memory[0]);
			$amiga.configure($proxy.OPT_CHIP_RAM, showcase.memory[0]);
			console.log('Configuring SLOW: ' + showcase.memory[1]);
			$amiga.configure($proxy.OPT_SLOW_RAM, showcase.memory[1]);
			console.log('Configuring FAST: ' + showcase.memory[2]);
			$amiga.configure($proxy.OPT_FAST_RAM, showcase.memory[2]);
			for (let i = 0; i < showcase.adf.length; i++) {
				console.log('Inserting disk ' + i + ': ' + showcase.adf[i]);
				await insert(showcase.adf[i], i);
			}
			$amiga.run();
		} catch (exception) {
			console.log('CATCHED' + exception);
			// console.error($amiga.getExceptionMessage(exception));
		}
		goto('/emulator');
	}

	function reportException() {
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

	export async function startUp() {
		console.log('VAmiga: startUp()');

		try {
			// Load AROS ROM
			let response = await fetch('roms/aros-svn55696-rom.bin');
			let blob = await response.arrayBuffer();
			let uint8View = new Uint8Array(blob);
			$memory.loadRom(uint8View, blob.byteLength);

			// Load AROS extension ROM
			response = await fetch('roms/aros-svn55696-ext.bin');
			blob = await response.arrayBuffer();
			uint8View = new Uint8Array(blob);
			$memory.loadExt(uint8View, blob.byteLength);
		} catch (exc) {
			reportException();
		}
	}

	export function onRuntimeInitialized() {
		console.log('Creating proxies...');

		$enums = new $proxy.EnumProxy();
		$amiga = new $proxy.AmigaProxy();
		$denise = new $proxy.DeniseProxy();
		$memory = new $proxy.MemoryProxy();
		$retroShell = new $proxy.RetroShellProxy();

		// Initiate the launch procedure
		startUp();
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
				break;

			case $proxy.MSG_HALT:
				$MsgHalt++;
				break;

			case $proxy.MSG_ABORT:
				$MsgAbort++;
				break;

			case $proxy.MSG_WARP_ON:
				$MsgWarpOn++;
				break;

			case $proxy.MSG_WARP_OFF:
				$MsgWarpOff++;
				break;

			case $proxy.MSG_DEBUG_ON:
				$MsgDebugOn++;
				break;

			case $proxy.MSG_DEBUG_OFF:
				$MsgDebugOff++;
				break;

			case $proxy.MSG_MUTE_ON:
				$MsgMuteOn++;
				break;

			case $proxy.MSG_MUTE_OFF:
				$MsgMuteOff++;
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
				break;

			case $proxy.MSG_DRIVE_DISCONNECT:
				$MsgDriveDisconnect++;
				break;

			case $proxy.MSG_DRIVE_SELECT:
				$MsgDriveSelect++;
				break;

			case $proxy.MSG_DRIVE_READ:
				$MsgDriveRead++;
				break;

			case $proxy.MSG_DRIVE_WRITE:
				$MsgDriveWrite++;
				break;

			case $proxy.MSG_DRIVE_LED_ON:
				$MsgDriveLedOn++;
				break;

			case $proxy.MSG_DRIVE_LED_OFF:
				$MsgDriveLedOff++;
				break;

			case $proxy.MSG_DRIVE_MOTOR_ON:
				$MsgDriveMotorOn++;
				break;

			case $proxy.MSG_DRIVE_MOTOR_OFF:
				$MsgDriveMotorOff++;
				break;

			case $proxy.MSG_DRIVE_STEP:
				$MsgDriveStep++;
				break;

			case $proxy.MSG_DRIVE_POLL:
				$MsgDrivePoll++;
				break;

			case $proxy.MSG_DISK_INSERT:
				$MsgDiskInsert++;
				break;

			case $proxy.MSG_DISK_EJECT:
				$MsgDiskEject++;
				break;

			case $proxy.MSG_DISK_SAVED:
				$MsgDiskSaved++;
				break;

			case $proxy.MSG_DISK_UNSAVED:
				$MsgDiskUnsaved++;
				break;

			case $proxy.MSG_DISK_PROTECT:
				$MsgDiskProtect++;
				break;

			case $proxy.MSG_DISK_UNPROTECT:
				$MsgDiskUnprotect++;
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
				$MsgShaking++;
				break;

			case $proxy.MSG_SER_IN:
				$MsgSerIn++;
				break;

			case $proxy.MSG_SER_OUT:
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
				break;

			case $proxy.MSG_DMA_DEBUG_OFF:
				$MsgDmaDebugOff++;
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

			default:
				break;
		}
	}
</script>
