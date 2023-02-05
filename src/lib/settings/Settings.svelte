<script lang="ts">
	import {
		Button,
		Dropdown,
		DropdownItem,
		DropdownDivider,
		DropdownHeader,
		Chevron,
		A
	} from 'flowbite-svelte';
	import { onMount } from 'svelte';
	import ConfigCategory from '$lib/settings/ConfigCategory.svelte';
	import ConfigSection from './ConfigSection.svelte';
	import ConfigItem from '$lib/settings/ConfigItem.svelte';
	import { proxy } from '$lib/stores';
	import { amiga } from '$lib/stores';
	import { fade } from 'svelte/transition';

	let power: boolean;
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

	onMount(() => {
		update();
	});

	function update() {
		power = $amiga.poweredOn;
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
	}

	function cpuRevAction(event) {
		$amiga.configure($proxy.OPT_CPU_REVISION, event.detail.text);
		update();
	}

	function cpuSpeedAction(event) {
		$amiga.configure($proxy.OPT_CPU_OVERCLOCKING, event.detail.text);
		update();
	}

	function agnusRevAction(event) {
		$amiga.configure($proxy.OPT_AGNUS_REVISION, event.detail.text);
		update();
	}

	function deniseRevAction(event) {
		$amiga.configure($proxy.OPT_DENISE_REVISION, event.detail.text);
		update();
	}

	function rtcModelAction(event) {
		$amiga.configure($proxy.OPT_RTC_MODEL, event.detail.text);
		update();
	}

	function chipRamAction(event) {
		$amiga.configure($proxy.OPT_CHIP_RAM, event.detail.text);
		update();
	}

	function slowRamAction(event) {
		$amiga.configure($proxy.OPT_SLOW_RAM, event.detail.text);
		update();
	}

	function fastRamAction(event) {
		$amiga.configure($proxy.OPT_FAST_RAM, event.detail.text);
		update();
	}

	function bankMapAction(event) {
		$amiga.configure($proxy.OPT_BANKMAP, event.detail.text);
		update();
	}

	function initPatternAction(event) {
		$amiga.configure($proxy.OPT_RAM_INIT_PATTERN, event.detail.text);
		update();
	}

	function unmappedAction(event) {
		$amiga.configure($proxy.OPT_UNMAPPING_TYPE, event.detail.text);
		update();
	}

	function slowRamMirrorAction(event) {
		$amiga.configure($proxy.OPT_SLOW_RAM_MIRROR, event.detail.text);
		update();
	}

	function slowRamDelayAction(event) {
		$amiga.configure($proxy.OPT_SLOW_RAM_DELAY, event.detail.text);
		update();
	}

</script>

<div class="absolute top-0 left-0 w-full h-full mt-1 flex overflow-scroll" transition:fade>
	<div class="w-16 mr-1" />
	<div class="bg-gray-500/75 mt-0 p-4 grow h-full overflow-scroll">
		<div class="font-sofia-extra">
			<div class="text-5xl">SETTINGS</div>
			<div class="float space-x-4 mb-6">
				<ConfigCategory name="MACHINE" />
				<ConfigCategory name="VIDEO" />
				<ConfigCategory name="AUDIO" />
			</div>
		</div>
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
	</div>
</div>
