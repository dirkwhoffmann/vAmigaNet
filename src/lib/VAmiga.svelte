<script lang="ts">
	import { onMount } from 'svelte';
	import {
        vAmiga, 
        enums, 
        amiga, 
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

	onMount(() => {
		console.log('VAmiga: onMount()');

		$vAmiga.processMsg = processMsg;
	});

	export function onRuntimeInitialized() {
		console.log('Creating proxies...');

		$enums = new $vAmiga.EnumProxy();
		$amiga = new $vAmiga.AmigaProxy();
		$retroShell = new $vAmiga.RetroShellProxy();
	}

	function processMsg(id: number, d1: number, d2: number, d3: number, d4: number) {
		console.log(`Message: ${$enums.MsgTypeKey(id)}(${d1}, ${d2}, ${d3}, ${d4})`);

		switch (id) {
			case $vAmiga.MSG_NONE:
				$MsgNone++;
				break;

			case $vAmiga.MSG_REGISTER:
				$MsgRegister++;
				break;

			case $vAmiga.MSG_CONFIG:
				$MsgConfig++;
				break;

			case $vAmiga.MSG_POWER_ON:
				$MsgPowerOn++;
				break;

			case $vAmiga.MSG_POWER_OFF:
				$MsgPowerOff++;
				break;

			case $vAmiga.MSG_RUN:
				$MsgRun++;
				break;

			case $vAmiga.MSG_PAUSE:
				$MsgPause++;
				break;

			case $vAmiga.MSG_STEP:
				$MsgStep++;
				break;

			case $vAmiga.MSG_RESET:
				$MsgReset++;
				break;

			case $vAmiga.MSG_HALT:
				$MsgHalt++;
				break;

			case $vAmiga.MSG_ABORT:
				$MsgAbort++;
				break;

			case $vAmiga.MSG_WARP_ON:
				$MsgWarpOn++;
				break;

			case $vAmiga.MSG_WARP_OFF:
				$MsgWarpOff++;
				break;

			case $vAmiga.MSG_DEBUG_ON:
				$MsgDebugOn++;
				break;

			case $vAmiga.MSG_DEBUG_OFF:
				$MsgDebugOff++;
				break;

			case $vAmiga.MSG_MUTE_ON:
				$MsgMuteOn++;
				break;

			case $vAmiga.MSG_MUTE_OFF:
				$MsgMuteOff++;
				break;

			case $vAmiga.MSG_POWER_LED_ON:
				$MsgPowerLedOn++;
				break;

			case $vAmiga.MSG_POWER_LED_DIM:
				$MsgPowerLedDim++;
				break;

			case $vAmiga.MSG_POWER_LED_OFF:
				$MsgPowerLedOff++;
				break;

			case $vAmiga.MSG_CLOSE_CONSOLE:
				$MsgCloseConsole++;
				break;

			case $vAmiga.MSG_UPDATE_CONSOLE:
				$MsgUpdateConsole++;
				break;

			case $vAmiga.MSG_SCRIPT_DONE:
				$MsgScriptDone++;
				break;

			case $vAmiga.MSG_SCRIPT_PAUSE:
				$MsgScriptPause++;
				break;

			case $vAmiga.MSG_SCRIPT_ABORT:
				$MsgScriptAbort++;
				break;

			case $vAmiga.MSG_SCRIPT_WAKEUP:
				$MsgScriptWakeup++;
				break;

			case $vAmiga.MSG_VIDEO_FORMAT:
				$MsgVideoFormat++;
				break;

			case $vAmiga.MSG_OVERCLOCKING:
				$MsgOverclocking++;
				break;

			case $vAmiga.MSG_BREAKPOINT_REACHED:
				$MsgBreakpointReached++;
				break;

			case $vAmiga.MSG_BREAKPOINT_UPDATED:
				$MsgBreakpointUpdated++;
				break;

			case $vAmiga.MSG_WATCHPOINT_REACHED:
				$MsgWatchpointReached++;
				break;

			case $vAmiga.MSG_WATCHPOINT_UPDATED:
				$MsgWatchpointUpdated++;
				break;

			case $vAmiga.MSG_CATCHPOINT_REACHED:
				$MsgCatchpointReached++;
				break;

			case $vAmiga.MSG_CATCHPOINT_UPDATED:
				$MsgCatchpointUpdated++;
				break;

			case $vAmiga.MSG_SWTRAP_REACHED:
				$MsgSwTrapReached++;
				break;

			case $vAmiga.MSG_CPU_HALT:
				$MsgCpuHalt++;
				break;

			case $vAmiga.MSG_COPPERBP_REACHED:
				$MsgCopperBpReached++;
				break;

			case $vAmiga.MSG_COPPERBP_UPDATED:
				$MsgCopperBpUpdated++;
				break;

			case $vAmiga.MSG_COPPERWP_REACHED:
				$MsgCopperWpReached++;
				break;

			case $vAmiga.MSG_COPPERWP_UPDATED:
				$MsgCopperWpUpdated++;
				break;

			case $vAmiga.MSG_VIEWPORT:
				$MsgViewport++;
				break;

			case $vAmiga.MSG_MEM_LAYOUT:
				$MsgMemLayout++;
				break;

			case $vAmiga.MSG_DRIVE_CONNECT:
				$MsgDriveConnect++;
				break;

			case $vAmiga.MSG_DRIVE_DISCONNECT:
				$MsgDriveDisconnect++;
				break;

			case $vAmiga.MSG_DRIVE_SELECT:
				$MsgDriveSelect++;
				break;

			case $vAmiga.MSG_DRIVE_READ:
				$MsgDriveRead++;
				break;

			case $vAmiga.MSG_DRIVE_WRITE:
				$MsgDriveWrite++;
				break;

			case $vAmiga.MSG_DRIVE_LED_ON:
				$MsgDriveLedOn++;
				break;

			case $vAmiga.MSG_DRIVE_LED_OFF:
				$MsgDriveLedOff++;
				break;

			case $vAmiga.MSG_DRIVE_MOTOR_ON:
				$MsgDriveMotorOn++;
				break;

			case $vAmiga.MSG_DRIVE_MOTOR_OFF:
				$MsgDriveMotorOff++;
				break;

			case $vAmiga.MSG_DRIVE_STEP:
				$MsgDriveStep++;
				break;

			case $vAmiga.MSG_DRIVE_POLL:
				$MsgDrivePoll++;
				break;

			case $vAmiga.MSG_DISK_INSERT:
				$MsgDiskInsert++;
				break;

			case $vAmiga.MSG_DISK_EJECT:
				$MsgDiskEject++;
				break;

			case $vAmiga.MSG_DISK_SAVED:
				$MsgDiskSaved++;
				break;

			case $vAmiga.MSG_DISK_UNSAVED:
				$MsgDiskUnsaved++;
				break;

			case $vAmiga.MSG_DISK_PROTECT:
				$MsgDiskProtect++;
				break;

			case $vAmiga.MSG_DISK_UNPROTECT:
				$MsgDiskUnprotect++;
				break;

			case $vAmiga.MSG_HDC_CONNECT:
				$MsgHdcConnect++;
				break;

			case $vAmiga.MSG_HDC_DISCONNECT:
				$MsgHdcDisconnect++;
				break;

			case $vAmiga.MSG_HDC_STATE:
				$MsgHdcState++;
				break;

			case $vAmiga.MSG_HDR_STEP:
				$MsgHdrStep++;
				break;

			case $vAmiga.MSG_HDR_READ:
				$MsgHdrRead++;
				break;

			case $vAmiga.MSG_HDR_WRITE:
				$MsgHdrWrite++;
				break;

			case $vAmiga.MSG_HDR_IDLE:
				$MsgHdrIdle++;
				break;

			case $vAmiga.MSG_CTRL_AMIGA_AMIGA:
				$MsgCtrlAmigaAmiga++;
				break;

			case $vAmiga.MSG_SHAKING:
				$MsgShaking++;
				break;

			case $vAmiga.MSG_SER_IN:
				$MsgSerIn++;
				break;

			case $vAmiga.MSG_SER_OUT:
				$MsgSerOut++;
				break;

			case $vAmiga.MSG_AUTO_SNAPSHOT_TAKEN:
				$MsgAutoSnapshotTaken++;
				break;

			case $vAmiga.MSG_USER_SNAPSHOT_TAKEN:
				$MsgUserSnapshotTaken++;
				break;

			case $vAmiga.MSG_SNAPSHOT_RESTORED:
				$MsgSnapshotRestored++;
				break;

			case $vAmiga.MSG_RECORDING_STARTED:
				$MsgRecordingStarted++;
				break;

			case $vAmiga.MSG_RECORDING_STOPPED:
				$MsgRecordingStopped++;
				break;

			case $vAmiga.MSG_RECORDING_ABORTED:
				$MsgRecordingAborted++;
				break;

			case $vAmiga.MSG_DMA_DEBUG_ON:
				$MsgDmaDebugOn++;
				break;

			case $vAmiga.MSG_DMA_DEBUG_OFF:
				$MsgDmaDebugOff++;
				break;

			case $vAmiga.MSG_SRV_STATE:
				$MsgSrvState++;
				break;

			case $vAmiga.MSG_SRV_RECEIVE:
				$MsgSrvReceive++;
				break;

			case $vAmiga.MSG_SRV_SEND:
				$MsgSrvSend++;
				break;

			default:
				break;
		}
	}
</script>
