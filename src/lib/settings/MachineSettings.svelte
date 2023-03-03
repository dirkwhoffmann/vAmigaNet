<script lang="ts">
	import { onMount } from 'svelte';
	import type { ActionEvent } from '$lib/types';
	import { Opt } from "$lib/types";
	import ConfigSection from './ConfigSection.svelte';
	import ConfigItem from '$lib/Settings/ConfigItem.svelte';
	import { amiga, config, proxy } from '$lib/stores';
	import { poweredOn, romcrc } from '$lib/stores';
	import { fade } from 'svelte/transition';
	import { browser } from '$app/environment';
	import { liveQuery } from 'dexie';
	import { db, type RomEntry } from '$lib/Db/db';
	import { MenuItem } from '$lib/types';

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
	}

	//
	// Action functions
	//

	function cpuRevAction(event: CustomEvent<ActionEvent>) {
		$config.set(Opt.CPU_REVISION, event.detail.value);
		update();
	}

	function cpuSpeedAction(event: CustomEvent<ActionEvent>) {
		$config.set(Opt.CPU_SPEED, event.detail.value);
		update();
	}

	function agnusRevAction(event: CustomEvent<ActionEvent>) {
		$config.set(Opt.AGNUS_REVISION, event.detail.value);
		update();
	}

	function deniseRevAction(event: CustomEvent<ActionEvent>) {
		$config.set(Opt.DENISE_REVISION, event.detail.value);
		update();
	}

	function rtcModelAction(event: CustomEvent<ActionEvent>) {
		$config.set(Opt.RTC_MODEL, event.detail.value);
		update();
	}

	function chipRamAction(event: CustomEvent<ActionEvent>) {
		$config.set(Opt.CHIP_RAM, event.detail.value);
		update();
	}

	function slowRamAction(event: CustomEvent<ActionEvent>) {
		$config.set(Opt.SLOW_RAM, event.detail.value);
		update();
	}

	function fastRamAction(event: CustomEvent<ActionEvent>) {
		$config.set(Opt.FAST_RAM, event.detail.value);
		update();
	}

	function bankMapAction(event: CustomEvent<ActionEvent>) {
		$config.set(Opt.BANK_MAP, event.detail.value);
		update();
	}

	function initPatternAction(event: CustomEvent<ActionEvent>) {
		$config.set(Opt.INIT_PATTERN, event.detail.value);
		update();
	}

	function unmappedAction(event: CustomEvent<ActionEvent>) {
		$config.set(Opt.UNMAPPED, event.detail.value);
		update();
	}

	function slowRamMirrorAction(event: CustomEvent<ActionEvent>) {
		$config.set(Opt.SLOW_RAM_MIRROR, event.detail.value);
		update();
	}

	function slowRamDelayAction(event: CustomEvent<ActionEvent>) {
		$config.set(Opt.SLOW_RAM_DELAY, event.detail.value);
		update();
	}

	function df0Action(event: CustomEvent<ActionEvent>) {
		$config.set(Opt.DF0, event.detail.value);
		update();
	}

	function df1Action(event: CustomEvent<ActionEvent>) {
		$config.set(Opt.DF1, event.detail.value);
		update();
	}

	function df2Action(event: CustomEvent<ActionEvent>) {
		$config.set(Opt.DF2, event.detail.value);
		update();
	}

	function df3Action(event: CustomEvent<ActionEvent>) {
		$config.set(Opt.DF3, event.detail.value);
		update();
	}
</script>

<div in:fade>
	<ConfigSection name="CPU">
		<ConfigItem
			name="CPU"
			items={[
				new MenuItem('68000', $proxy.CPU_68000),
				new MenuItem('68010', $proxy.CPU_68010),
				new MenuItem('68EC020', $proxy.CPU_68EC020)
			]}
			selectedTag={$config.get(Opt.CPU_REVISION)}
			on:select={(e) => $config.set(Opt.CPU_REVISION, e.detail.value)}
		/>
		<ConfigItem
			name="Frequency"
			items={[
				new MenuItem('7 Mhz', 0),
				new MenuItem('14 Mhz', 2),
				new MenuItem('21 Mhz', 3),
				new MenuItem('28 Mhz', 4),
				new MenuItem('35 Mhz', 5),
				new MenuItem('42 Mhz', 6),
				new MenuItem('84 Mhz', 12),
			]}
			selectedTag={$config.get(Opt.CPU_SPEED)}
			on:select={(e) => $config.set(Opt.CPU_SPEED, e.detail.value)}
		/>
	</ConfigSection>
	<ConfigSection name="Custom Chipset">
		<ConfigItem
			name="Agnus Revision"
			items={[
				new MenuItem('Early OCS', $proxy.AGNUS_OCS_OLD),
				new MenuItem('OCS', $proxy.AGNUS_OCS),
				new MenuItem('ECS (1MB)', $proxy.AGNUS_ECS_1MB),
				new MenuItem('ECS (2MB)', $proxy.AGNUS_ECS_2MB)
			]}
			selectedTag={$config.get(Opt.AGNUS_REVISION)}
			on:select={(e) => $config.set(Opt.AGNUS_REVISION, e.detail.value)}
			locked={power}
		/>
		<ConfigItem
			name="Denise Revision"
			items={[
				new MenuItem('OCS', $proxy.DENISE_OCS),
				new MenuItem('ECS', $proxy.DENISE_ECS),
			]}
			selectedTag={$config.get(Opt.DENISE_REVISION)}
			on:select={(e) => $config.set(Opt.DENISE_REVISION, e.detail.value)}
			locked={power}
		/>
		<ConfigItem
			name="Real-time Clock"
			items={[
				new MenuItem('NONE', $proxy.RTC_NONE),
				new MenuItem('OKI', $proxy.RTC_OKI),
				new MenuItem('RICOH', $proxy.RTC_RICOH),
			]}
			selectedTag={$config.get(Opt.RTC_MODEL)}
			on:select={(e) => $config.set(Opt.RTC_MODEL, e.detail.value)}
			locked={power}
		/>
	</ConfigSection>
	<ConfigSection name="Memory">
		<ConfigItem
			name="Chip RAM"
			items={[
				new MenuItem('256 KB', 256),
				new MenuItem('512 KB', 512),
				new MenuItem('1024 KB', 1024),
				new MenuItem('2048 KB', 2048)
			]}
			selectedTag={$config.get(Opt.CHIP_RAM)}
			on:select={(e) => $config.set(Opt.CHIP_RAM, e.detail.value)}
			locked={power}
		/>
		<ConfigItem
			name="Slow RAM"
			items={[
				new MenuItem('0 KB', 0),
				new MenuItem('512 KB', 512),
				new MenuItem('1 MB', 1024),
				new MenuItem('1.5 MB', 1536)
			]}
			selectedTag={$config.get(Opt.SLOW_RAM)}
			on:select={(e) => $config.set(Opt.SLOW_RAM, e.detail.value)}
			locked={power}
		/>
		<ConfigItem
			name="Fast RAM"
			items={[
				new MenuItem('0 KB', 0),
				new MenuItem('64 KB', 64),
				new MenuItem('128 KB', 118),
				new MenuItem('256 KB', 256),
				new MenuItem('512 KB', 512),
				new MenuItem('1 MB', 1024),
				new MenuItem('2 MB', 2048),
				new MenuItem('4 MB', 4096),
				new MenuItem('8 MB', 8192)
			]}
			selectedTag={$config.get(Opt.FAST_RAM)}
			on:select={(e) => $config.set(Opt.FAST_RAM, e.detail.value)}
			locked={power}
		/>
		<ConfigItem
			name="Memory Layout"
			items={[
				new MenuItem('Amiga 500', $proxy.BANK_MAP_A500),
				new MenuItem('Amiga 1000', $proxy.BANK_MAP_A1000),
				new MenuItem('Amiga 2000A', $proxy.BANK_MAP_A2000A),
				new MenuItem('Amiga 2000B', $proxy.BANK_MAP_A2000B),
			]}
			selectedTag={$config.get(Opt.BANK_MAP)}
			on:select={(e) => $config.set(Opt.BANK_MAP, e.detail.value)}
		/>
		<ConfigItem
			name="Memory Startup Pattern"
			items={[
				new MenuItem('All Zeroes', $proxy.RAM_INIT_ALL_ZEROES),
				new MenuItem('All Ones', $proxy.RAM_INIT_ALL_ONES),
				new MenuItem('Random', $proxy.RAM_INIT_RANDOMIZED)
			]}
			selectedTag={$config.get(Opt.INIT_PATTERN)}
			on:select={(e) => $config.set(Opt.INIT_PATTERN, e.detail.value)}
		/>
		<ConfigItem
			name="Unmapped Memory Area"
			items={[
				new MenuItem('Floating', $proxy.UNMAPPED_FLOATING),
				new MenuItem('All Zeroes', $proxy.UNMAPPED_ALL_ZEROES),
				new MenuItem('All Ones', $proxy.UNMAPPED_ALL_ONES)
			]}
			selectedTag={$config.get(Opt.UNMAPPED)}
			on:select={(e) => $config.set(Opt.UNMAPPED, e.detail.value)}
		/>
		<ConfigItem
			name="Emulate Slow RAM Mirror"
			items={[
				new MenuItem('Yes', 1),
				new MenuItem('No', 0)
			]}
			selectedTag={$config.get(Opt.SLOW_RAM_MIRROR)}
			on:select={(e) => $config.set(Opt.SLOW_RAM_MIRROR, e.detail.value)}
		/>
		<ConfigItem
			name="Emulate Slow RAM Bus Delays"
			items={[
				new MenuItem('Yes', 1),
				new MenuItem('No', 0)
			]}
			selectedTag={$config.get(Opt.SLOW_RAM_DELAY)}
			on:select={(e) => $config.set(Opt.SLOW_RAM_DELAY, e.detail.value)}
		/>
	</ConfigSection>
	<ConfigSection name="Floppy Drives">
		<ConfigItem
			name="DF0"
			items={[
				new MenuItem('Internal Drive', 1)
			]}
			tag={0}
			selectedTag={$config.get(Opt.DF0)}
			on:select={(e) => $config.set(Opt.DF0, e.detail.value)}
		/>
		<ConfigItem
			name="DF1"
			items={[
				new MenuItem('None', 0),
				new MenuItem('A1010', 1)
			]}
			tag={1}
			selectedTag={$config.get(Opt.DF1)}
			on:select={(e) => $config.set(Opt.DF1, e.detail.value)}
			locked={power}
		/>
		<ConfigItem
			name="DF2"
			items={[
				new MenuItem('None', 0),
				new MenuItem('A1010', 1)
			]}
			tag={2}
			selectedTag={$config.get(Opt.DF2)}
			on:select={(e) => $config.set(Opt.DF2, e.detail.value)}
			locked={power || !$config.getBool(Opt.DF1) }
		/>
		<ConfigItem
			name="DF3"
			items={[
				new MenuItem('None', 0),
				new MenuItem('A1010', 1)
			]}
			tag={3}
			selectedTag={$config.get(Opt.DF3)}
			on:select={(e) => $config.set(Opt.DF3, e.detail.value)}
			locked={power || !$config.getBool(Opt.DF2) }
		/>
	</ConfigSection>
</div>
