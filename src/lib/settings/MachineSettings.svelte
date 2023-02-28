<script lang="ts">
	import { onMount } from 'svelte';
	import ConfigSection from './ConfigSection.svelte';
	import ConfigItem from '$lib/Settings/ConfigItem.svelte';
	import { proxy, amiga, memory } from '$lib/stores';
	import { poweredOn, romcrc } from '$lib/stores';
	import { fade } from 'svelte/transition';
	import { browser } from '$app/environment';
	import { liveQuery } from 'dexie';
	import { db, type RomEntry } from '$lib/Db/db';
	import type { ActionEvent } from '$lib/types';

	let kickstart: number;
	let kickName = '';
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
	$: romValues = stripNames($roms as RomEntry[]);
	function stripNames(entries: RomEntry[]) {
		console.log('stripRoms', entries);
		let result = [{ name: 'None', id: 0 }];
		if (entries) {
			entries.forEach((rom: RomEntry) => {
				result.push({ name: rom.title, id: rom.crc32 });
			});
		}
		return result;
	}

	$: console.log('romcrc = ' + $romcrc);
	$: console.log('rom db = ' + $roms);
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
	}

	//
	// Action functions
	//

	async function kickstartAction(event: CustomEvent<ActionEvent>) {
		$proxy.installRom(event.detail.value);
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

<div in:fade>
	<ConfigSection name="CPU">
		<ConfigItem
			name="CPU"
			values={[
				{ name: '68000', id: $proxy.CPU_68000 },
				{ name: '68010', id: $proxy.CPU_68010 },
				{ name: '68EC020', id: $proxy.CPU_68EC020 }
			]}
			selectedTag={cpuRevision}
			on:select={cpuRevAction}
		/>
		<ConfigItem
			name="Frequency"
			values={[
				{ name: '7 Mhz', id: 0 },
				{ name: '14 Mhz', id: 2 },
				{ name: '21 Mhz', id: 3 },
				{ name: '28 Mhz', id: 4 },
				{ name: '35 Mhz', id: 5 },
				{ name: '42 Mhz', id: 6 },
				{ name: '84 Mhz', id: 12 }
			]}
			selectedTag={cpuSpeed}
			on:select={cpuSpeedAction}
		/>
	</ConfigSection>
	<ConfigSection name="Custom Chipset">
		<ConfigItem
			name="Agnus Revision"
			values={[
				{ name: 'Early OCS', id: $proxy.AGNUS_OCS_OLD },
				{ name: 'OCS', id: $proxy.AGNUS_OCS },
				{ name: 'ECS (1MB)', id: $proxy.AGNUS_ECS_1MB },
				{ name: 'ECS (2MB)', id: $proxy.AGNUS_ECS_2MB }
			]}
			selectedTag={agnusRevision}
			on:select={agnusRevAction}
			locked={power}
		/>
		<ConfigItem
			name="Denise Revision"
			values={[
				{ name: 'OCS', id: $proxy.DENISE_OCS },
				{ name: 'ECS', id: $proxy.DENISE_ECS }
			]}
			selectedTag={deniseRevision}
			on:select={deniseRevAction}
			locked={power}
		/>
		<ConfigItem
			name="Real-time Clock"
			values={[
				{ name: 'NONE', id: $proxy.RTC_NONE },
				{ name: 'OKI', id: $proxy.RTC_OKI },
				{ name: 'RICOH', id: $proxy.RTC_RICOH }
			]}
			selectedTag={rtcModel}
			on:select={rtcModelAction}
			locked={power}
		/>
	</ConfigSection>
	<ConfigSection name="Memory">
		<ConfigItem
			name="Chip RAM"
			values={[
				{ name: '256 KB', id: 256 },
				{ name: '512 KB', id: 512 },
				{ name: '1024 KB', id: 1024 },
				{ name: '2048 KB', id: 2048 }
			]}
			selectedTag={chipRam}
			on:select={chipRamAction}
			locked={power}
		/>
		<ConfigItem
			name="Slow RAM"
			values={[
				{ name: '0 KB', id: 0 },
				{ name: '512 KB', id: 512 },
				{ name: '1 MB', id: 1024 },
				{ name: '1.5 MB', id: 1536 }
			]}
			selectedTag={slowRam}
			on:select={slowRamAction}
			locked={power}
		/>
		<ConfigItem
			name="Fast RAM"
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
			selectedTag={fastRam}
			on:select={fastRamAction}
			locked={power}
		/>
		<ConfigItem
			name="Memory Layout"
			values={[
				{ name: 'Amiga 500', id: $proxy.BANK_MAP_A500 },
				{ name: 'Amiga 1000', id: $proxy.BANK_MAP_A1000 },
				{ name: 'Amiga 2000A', id: $proxy.BANK_MAP_A2000A },
				{ name: 'Amiga 2000B', id: $proxy.BANK_MAP_A2000B }
			]}
			selectedTag={bankMap}
			on:select={bankMapAction}
		/>
		<ConfigItem
			name="Memory Startup Pattern"
			values={[
				{ name: 'All Zeroes', id: $proxy.RAM_INIT_ALL_ZEROES },
				{ name: 'All Ones', id: $proxy.RAM_INIT_ALL_ONES },
				{ name: 'Random', id: $proxy.RAM_INIT_RANDOMIZED }
			]}
			selectedTag={initPattern}
			on:select={initPatternAction}
		/>
		<ConfigItem
			name="Unmapped Memory Area"
			values={[
				{ name: 'Floating', id: $proxy.UNMAPPED_FLOATING },
				{ name: 'All Zeroes', id: $proxy.UNMAPPED_ALL_ZEROES },
				{ name: 'All Ones', id: $proxy.UNMAPPED_ALL_ONES }
			]}
			selectedTag={unmapped}
			on:select={unmappedAction}
		/>
		<ConfigItem
			name="Emulate Slow RAM Mirror"
			values={[
				{ name: 'Yes', id: 1 },
				{ name: 'No', id: 0 }
			]}
			selectedTag={slowRamMirror}
			on:select={slowRamMirrorAction}
		/>
		<ConfigItem
			name="Emulate Slow RAM Bus Delays"
			values={[
				{ name: 'Yes', id: 1 },
				{ name: 'No', id: 0 }
			]}
			selectedTag={slowRamDelay}
			on:select={slowRamDelayAction}
		/>
	</ConfigSection>
	<ConfigSection name="Floppy Drives">
		<ConfigItem
			name="DF0"
			values={[{ name: 'Internal Drive', id: 1 }]}
			tag={0}
			selectedTag={df0}
			on:select={dfAction}
		/>
		<ConfigItem
			name="DF1"
			values={[
				{ name: 'None', id: 0 },
				{ name: 'A1010', id: 1 }
			]}
			tag={1}
			selectedTag={df1}
			on:select={dfAction}
			locked={power}
		/>
		<ConfigItem
			name="DF2"
			values={[
				{ name: 'None', id: 0 },
				{ name: 'A1010', id: 1 }
			]}
			tag={2}
			selectedTag={df2}
			on:select={dfAction}
			locked={power || df1 == 0}
		/>
		<ConfigItem
			name="DF3"
			values={[
				{ name: 'None', id: 0 },
				{ name: 'A1010', id: 1 }
			]}
			tag={3}
			selectedTag={df3}
			on:select={dfAction}
			locked={power || df2 == 0}
		/>
	</ConfigSection>
</div>
