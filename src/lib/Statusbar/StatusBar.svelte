<script lang="ts">
	import { createEventDispatcher } from 'svelte';
	import DeviceInfo from '$lib/Statusbar/DeviceInfo.svelte';
	import Speedometer from '$lib/Statusbar/Speedometer.svelte';
	import BarBox from '$lib/Statusbar/BarBox.svelte';
	import {
		dfConnected,
		dfHasDisk,
		dfCylinder,
		dfMotor,
		dfWriting,
		dfUnsaved,
		dfProtected,
		warp,
		debugMode,
		halted,
		muted,
		audio,
		amiga
	} from '$lib/stores';
	import StatusIcon from './StatusIcon.svelte';
	import WarpControl from './WarpControl.svelte';

	let speedometer: Speedometer;

	$: muteIcon = $muted || $warp; 
	$: debugIcon = $debugMode; 
	$: haltIcon = $halted; 

	const dispatch = createEventDispatcher<{ push: { sender: string } }>();
	const bg = 'bg-gradient-to-t from-primary to-primary/80';

	export function update(animationFrame: number, now: DOMHighResTimeStamp) {
		if (speedometer) {
			speedometer.update(animationFrame, now);
		}
	}

	function toggleSidebar(e: Event) {
		e.preventDefault();
		$audio.setup();
		dispatch('push', { sender: (e.target as HTMLElement).id });
	}

	function ejectAction(nr: number) {
		console.log("eject ", nr);
		$amiga.ejectDisk(nr);
	}


	function read_file_stream(file)
	{
		return new Promise(async (resolve, reject)=>{
			try{
				var fileReader=new FileReader();
				fileReader.onload = function(){
					resolve(new Uint8Array(this.result));
				}
				fileReader.readAsArrayBuffer(file);

			} catch(e)
			{
				reject(e);
			}



		});
	}
	async function read_file(e){
		let file=e.target.files[0];
		let u8 = await read_file_stream(file) as Uint8Array;
		$amiga.insertDisk(u8, u8.length, insertInDriveNr);
		inputFile.value="";
	}


	let inputFile:HTMLInputElement;
	let insertInDriveNr=0;

	function insertFile(nr:number){
		insertInDriveNr=nr;
		inputFile.click()
	}



</script>

<input bind:this={inputFile} type="file" class="hidden" on:change={read_file}>
<div class="z-50 relative flex h-8 mb-1 {bg}">
	<BarBox>
		<button
			type="button"
			class="flex w-16 h-full justify-center"
			id="vamigaButton"
			on:click={toggleSidebar}
		>
			<img class="h-full" src="icons/vamigaIcon.png" alt="vAmiga Icon" />
		</button>
	</BarBox>
	<div class="border-0 border-red-500 flex grow">
		{#each Array(4) as _, i}
			{#if $dfConnected[i]}
				<DeviceInfo
					disk={$dfHasDisk[i]}
					cyl={$dfCylinder[i]}
					motor={$dfMotor[i]}
					writing={$dfWriting[i]}
					unsaved={$dfUnsaved[i]}
					wp={$dfProtected[i]}
					on:select={(e) => {if(e.detail.value==1) ejectAction(i); else insertFile(i);}}
				/>
			{/if}
		{/each}
	</div>
	{#if haltIcon}
		<StatusIcon src="icons/halt.png" />
	{/if}
	{#if debugIcon}
		<StatusIcon src="icons/debug.png" />
	{/if}
	{#if muteIcon}
		<StatusIcon src="icons/mute.png" />
	{/if}
	<WarpControl />
	<Speedometer bind:this={speedometer} />
</div>
