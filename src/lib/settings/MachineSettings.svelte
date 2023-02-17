<script lang="ts">
	import { onMount } from 'svelte';
	import ConfigSection from './ConfigSection.svelte';
	import ConfigItem from '$lib/settings/ConfigItem.svelte';
	import { proxy, amiga, memory } from '$lib/stores';
	import { poweredOn } from '$lib/stores';
	import { fade } from 'svelte/transition';
	import type { ActionEvent } from '$lib/settings/Settings.svelte';
	import { browser } from '$app/environment';
	import { liveQuery } from 'dexie';
	import { db, type RomEntry } from '$lib/db/db';

	let kickstart: number;
	let cpuRevision: number;
	let cpuSpeed: number;
	let agnusRevision: number;
	let deniseRevision: number;
	let rtcModel: number;
	let chipRam: number;
	let slowRam: number;
	let fastRam: number;
	let bankMap: number;
	let initPattern: number;
	let unmapped: number;
	let slowRamMirror: number;
	let slowRamDelay: number;
	let df0: number;
	let df1: number;
	let df2: number;
	let df3: number;
	let hd0: number;

	let roms = liveQuery(() => (browser ? db.roms.toArray() : []));
	let romValues = [{ name: '', id: 0 }];
	$: {
		console.log("Computing romValues ******");
		romValues = [{ name: 'None', id: 0 }];
		if ($roms) {
			$roms.forEach((rom: RomEntry) => {
				romValues.push({ name: rom.title, id: rom.crc32 });
			});
		}
 		update();
	}
	$: console.log('romValues = ', romValues);

	$: power = $poweredOn;

	onMount(() => {
		update();
	});

	function update() {
		// power = $amiga.poweredOn;
		cpuRevision = $amiga.getConfig($proxy.OPT_CPU_REVISION);
		cpuSpeed = $amiga.getConfig($proxy.OPT_CPU_OVERCLOCKING);
		agnusRevision = $amiga.getConfig($proxy.OPT_AGNUS_REVISION);
		deniseRevision = $amiga.getConfig($proxy.OPT_DENISE_REVISION);
		rtcModel = $amiga.getConfig($proxy.OPT_RTC_MODEL);
		chipRam = $amiga.getConfig($proxy.OPT_CHIP_RAM);
		slowRam = $amiga.getConfig($proxy.OPT_SLOW_RAM);
		fastRam = $amiga.getConfig($proxy.OPT_FAST_RAM);
		bankMap = $amiga.getConfig($proxy.OPT_BANKMAP);
		initPattern = $amiga.getConfig($proxy.OPT_RAM_INIT_PATTERN);
		unmapped = $amiga.getConfig($proxy.OPT_UNMAPPING_TYPE);
		slowRamMirror = $amiga.getConfig($proxy.OPT_SLOW_RAM_MIRROR);
		slowRamDelay = $amiga.getConfig($proxy.OPT_SLOW_RAM_DELAY);
		df0 = $amiga.getDriveConfig($proxy.OPT_DRIVE_CONNECT, 0);
		df1 = $amiga.getDriveConfig($proxy.OPT_DRIVE_CONNECT, 1);
		df2 = $amiga.getDriveConfig($proxy.OPT_DRIVE_CONNECT, 2);
		df3 = $amiga.getDriveConfig($proxy.OPT_DRIVE_CONNECT, 3);
		kickstart = $memory.romFingerprint();
		console.log("kickstart CRC = ", kickstart);
	}

	function kickstartAction(event: CustomEvent<ActionEvent>) {
		// $amiga.configure($proxy.OPT_CPU_REVISION, event.detail.value);
		console.log('kickstartAction');
		update();
	}

	function cpuRevAction(event: CustomEvent<ActionEvent>) {
		$amiga.configure($proxy.OPT_CPU_REVISION, event.detail.value);
		update();
	}

	function cpuSpeedAction(event: CustomEvent<ActionEvent>) {
		$amiga.configure($proxy.OPT_CPU_OVERCLOCKING, event.detail.value);
		update();
	}

	function agnusRevAction(event: CustomEvent<ActionEvent>) {
		$amiga.configure($proxy.OPT_AGNUS_REVISION, event.detail.value);
		update();
	}

	function deniseRevAction(event: CustomEvent<ActionEvent>) {
		$amiga.configure($proxy.OPT_DENISE_REVISION, event.detail.value);
		update();
	}

	function rtcModelAction(event: CustomEvent<ActionEvent>) {
		$amiga.configure($proxy.OPT_RTC_MODEL, event.detail.value);
		update();
	}

	function chipRamAction(event: CustomEvent<ActionEvent>) {
		$amiga.configure($proxy.OPT_CHIP_RAM, event.detail.value);
		update();
	}

	function slowRamAction(event: CustomEvent<ActionEvent>) {
		$amiga.configure($proxy.OPT_SLOW_RAM, event.detail.value);
		update();
	}

	function fastRamAction(event: CustomEvent<ActionEvent>) {
		$amiga.configure($proxy.OPT_FAST_RAM, event.detail.value);
		update();
	}

	function bankMapAction(event: CustomEvent<ActionEvent>) {
		$amiga.configure($proxy.OPT_BANKMAP, event.detail.value);
		update();
	}

	function initPatternAction(event: CustomEvent<ActionEvent>) {
		$amiga.configure($proxy.OPT_RAM_INIT_PATTERN, event.detail.value);
		update();
	}

	function unmappedAction(event: CustomEvent<ActionEvent>) {
		$amiga.configure($proxy.OPT_UNMAPPING_TYPE, event.detail.value);
		update();
	}

	function slowRamMirrorAction(event: CustomEvent<ActionEvent>) {
		$amiga.configure($proxy.OPT_SLOW_RAM_MIRROR, event.detail.value);
		update();
	}

	function slowRamDelayAction(event: CustomEvent<ActionEvent>) {
		$amiga.configure($proxy.OPT_SLOW_RAM_DELAY, event.detail.value);
		update();
	}

	function dfAction(event: CustomEvent<ActionEvent>) {
		console.log('dfAction: ' + event.detail.tag + ', ' + event.detail.value);
		if (event.detail.value) {
			for (let i = 1; i <= event.detail.tag; i++) {
				$amiga.configureDrive($proxy.OPT_DRIVE_CONNECT, i, 1);
			}
		} else {
			for (let i = event.detail.tag; i <= 4; i++) {
				$amiga.configureDrive($proxy.OPT_DRIVE_CONNECT, i, 0);
			}
		}
		update();
	}
</script>

<div transition:fade>
	<ConfigSection name="Roms">
		<ConfigItem
			name="Kickstart"
			selection={kickstart}
			on:select={kickstartAction}
			values={romValues}
		/>
	</ConfigSection>
	<ConfigSection name="CPU">
		<ConfigItem
			name="CPU"
			selection={cpuRevision}
			on:select={cpuRevAction}
			values={[
				{ name: '68000', id: $proxy.CPU_68000 },
				{ name: '68010', id: $proxy.CPU_68010 },
				{ name: '68EC020', id: $proxy.CPU_68EC020 }
			]}
		/>
		<ConfigItem
			name="Frequency"
			selection={cpuSpeed}
			on:select={cpuSpeedAction}
			values={[
				{ name: '7 Mhz', id: 0 },
				{ name: '14 Mhz', id: 2 },
				{ name: '21 Mhz', id: 3 },
				{ name: '28 Mhz', id: 4 },
				{ name: '35 Mhz', id: 5 },
				{ name: '42 Mhz', id: 6 },
				{ name: '84 Mhz', id: 12 }
			]}
		/>
	</ConfigSection>
	<ConfigSection name="Custom Chipset">
		<ConfigItem
			name="Agnus Revision"
			selection={agnusRevision}
			on:select={agnusRevAction}
			locked={power}
			values={[
				{ name: 'Early OCS', id: $proxy.AGNUS_OCS_OLD },
				{ name: 'OCS', id: $proxy.AGNUS_OCS },
				{ name: 'ECS (1MB)', id: $proxy.AGNUS_ECS_1MB },
				{ name: 'ECS (2MB)', id: $proxy.AGNUS_ECS_2MB }
			]}
		/>
		<ConfigItem
			name="Denise Revision"
			selection={deniseRevision}
			on:select={deniseRevAction}
			values={[
				{ name: 'OCS', id: $proxy.DENISE_OCS },
				{ name: 'ECS', id: $proxy.DENISE_ECS }
			]}
			locked={power}
		/>
		<ConfigItem
			name="Real-time Clock"
			selection={rtcModel}
			on:select={rtcModelAction}
			values={[
				{ name: 'NONE', id: $proxy.RTC_NONE },
				{ name: 'OKI', id: $proxy.RTC_OKI },
				{ name: 'RICOH', id: $proxy.RTC_RICOH }
			]}
			locked={power}
		/>
	</ConfigSection>
	<ConfigSection name="Memory">
		<ConfigItem
			name="Chip RAM"
			selection={chipRam}
			on:select={chipRamAction}
			values={[
				{ name: '256 KB', id: 256 },
				{ name: '512 KB', id: 512 },
				{ name: '1024 KB', id: 1024 },
				{ name: '2048 KB', id: 2048 }
			]}
			locked={power}
		/>
		<ConfigItem
			name="Slow RAM"
			selection={slowRam}
			on:select={slowRamAction}
			values={[
				{ name: '0 KB', id: 0 },
				{ name: '512 KB', id: 512 },
				{ name: '1 MB', id: 1024 },
				{ name: '1.5 MB', id: 1536 }
			]}
			locked={power}
		/>
		<ConfigItem
			name="Fast RAM"
			selection={fastRam}
			on:select={fastRamAction}
			values={[
				{ name: '0 KB', id: 0 },
				{ name: '64 KB', id: 64 },
				{ name: '128 KB', id: 128 },
				{ name: '256 KB', id: 256 },
				{ name: '512 KB', id: 512 },
				{ name: '1 MB', id: 1024 },
				{ name: '2 MB', id: 2048 },
				{ name: '4 MB', id: 4096 },
				{ name: '8 MB', id: 8192 }
			]}
			locked={power}
		/>
		<ConfigItem
			name="Memory Layout"
			selection={bankMap}
			on:select={bankMapAction}
			values={[
				{ name: 'Amiga 500', id: $proxy.BANK_MAP_A500 },
				{ name: 'Amiga 1000', id: $proxy.BANK_MAP_A1000 },
				{ name: 'Amiga 2000A', id: $proxy.BANK_MAP_A2000A },
				{ name: 'Amiga 2000B', id: $proxy.BANK_MAP_A2000B }
			]}
		/>
		<ConfigItem
			name="Memory Startup Pattern"
			selection={initPattern}
			on:select={initPatternAction}
			values={[
				{ name: 'All Zeroes', id: $proxy.RAM_INIT_ALL_ZEROES },
				{ name: 'All Ones', id: $proxy.RAM_INIT_ALL_ONES },
				{ name: 'Random', id: $proxy.RAM_INIT_RANDOMIZED }
			]}
		/>
		<ConfigItem
			name="Unmapped Memory Area"
			selection={unmapped}
			on:select={unmappedAction}
			values={[
				{ name: 'Floating', id: $proxy.UNMAPPED_FLOATING },
				{ name: 'All Zeroes', id: $proxy.UNMAPPED_ALL_ZEROES },
				{ name: 'All Ones', id: $proxy.UNMAPPED_ALL_ONES }
			]}
		/>
		<ConfigItem
			name="Emulate Slow RAM Mirror"
			selection={slowRamMirror}
			on:select={slowRamMirrorAction}
			values={[
				{ name: 'Yes', id: 1 },
				{ name: 'No', id: 0 }
			]}
		/>
		<ConfigItem
			name="Emulate Slow RAM Bus Delays"
			selection={slowRamDelay}
			on:select={slowRamDelayAction}
			values={[
				{ name: 'Yes', id: 1 },
				{ name: 'No', id: 0 }
			]}
		/>
	</ConfigSection>
	<ConfigSection name="Floppy Drives">
		<ConfigItem
			name="DF0"
			tag={0}
			selection={df0}
			on:select={dfAction}
			values={[{ name: 'Internal Drive', id: 1 }]}
		/>
		<ConfigItem
			name="DF1"
			tag={1}
			selection={df1}
			on:select={dfAction}
			values={[
				{ name: 'None', id: 0 },
				{ name: 'A1010', id: 1 }
			]}
			locked={power}
		/>
		<ConfigItem
			name="DF2"
			tag={2}
			selection={df2}
			on:select={dfAction}
			values={[
				{ name: 'None', id: 0 },
				{ name: 'A1010', id: 1 }
			]}
			locked={power || df1 == 0}
		/>
		<ConfigItem
			name="DF3"
			tag={3}
			selection={df3}
			on:select={dfAction}
			values={[
				{ name: 'None', id: 0 },
				{ name: 'A1010', id: 1 }
			]}
			locked={power || df2 == 0}
		/>
	</ConfigSection>
</div>
