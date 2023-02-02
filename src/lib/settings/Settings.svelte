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

<div class="font-sofia-semi text-white bg-gray-500/75 w-screen h-screen p-2 overflow-scroll">
	<div class="mt-4 p-4">
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
				on:select={cpuRevAction}
				selectedTag={cpuRevision}
				name="CPU"
				values={[
					{ name: '68000', id: $proxy.CPU_68000 },
					{ name: '68010', id: $proxy.CPU_68010 },
					{ name: '68EC020', id: $proxy.CPU_68EC020 }
				]}
			/>
			<ConfigItem
				on:select={cpuSpeedAction}
				selectedTag={cpuSpeed}
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
			/>
		</ConfigSection>
		<ConfigSection name="Custom Chipset">
			<ConfigItem
				on:select={agnusRevAction}
				selectedTag={agnusRevision}
				name="Agnus Revision"
				locked={power}
				values={[
					{ name: 'Early OCS', id: $proxy.AGNUS_OCS_OLD },
					{ name: 'OCS', id: $proxy.AGNUS_OCS },
					{ name: 'ECS (1MB)', id: $proxy.AGNUS_ECS_1MB },
					{ name: 'ECS (2MB)', id: $proxy.AGNUS_ECS_2MB }
				]}
			/>
			<ConfigItem
				on:select={deniseRevAction}
				selectedTag={deniseRevision}
				name="Denise Revision"
				locked={power}
				values={[
					{ name: 'OCS', id: $proxy.DENISE_OCS },
					{ name: 'ECS', id: $proxy.DENISE_ECS }
				]}
			/>
			<ConfigItem
				on:select={rtcModelAction}
				selectedTag={rtcModel}
				name="Real-time Clock"
				locked={power}
				values={[
					{ name: 'NONE', id: $proxy.RTC_NONE },
					{ name: 'OKI', id: $proxy.RTC_OKI },
					{ name: 'RICOH', id: $proxy.RTC_RICOH }
				]}
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
		-->
	</div>
</div>
