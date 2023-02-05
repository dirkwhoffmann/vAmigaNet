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
</script>

<div class="absolute top-0 left-0 h-full w-full flex overflow-scroll" transition:fade>
	<div class="w-16 mr-1"></div>
	<!--<div class="border-2 border-red-500 bg-gray-500/75 grow h-full">Hallo</div>-->
	<!--
	<div class="bg-gray-500/75 border-2 border-green-500 w-full h-screen p-2 overflow-scroll">
	-->
		<div class="bg-gray-500/75 mt-0 p-4 grow h-full overflow-scroll">
			<div class="font-sofia-extra">
				<div class="text-5xl">SETTINGS</div>
				<div class="float space-x-4 mb-6">
					<ConfigCategory name="HARDWARE" />
					<ConfigCategory name="MEMORY" />
					<ConfigCategory name="PERIPHERALS" />
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

			<!--
		<ConfigSection name="Memory">
			<ConfigItem name="Chip RAM" />
			<ConfigItem name="Slow RAM" />
			<ConfigItem name="Fast RAM" />
			<ConfigItem name="Memory Layout" />
			<ConfigItem name="Memory Startup Pattern" />
			<ConfigItem name="Unmapped Area" />
			<ConfigItem name="Unmapped Area" />
			<ConfigItem name="Emulate Slow RAM Mirror" />
			<ConfigItem name="Emulate Slow RAM Bus Delays" />
		</ConfigSection>
	</div>
		-->
	</div>
	</div>
