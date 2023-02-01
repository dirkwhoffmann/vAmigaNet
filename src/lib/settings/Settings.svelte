<script lang="ts">
	import {
		Button,
		Dropdown,
		DropdownItem,
		DropdownDivider,
		DropdownHeader,
		Chevron
	} from 'flowbite-svelte';
	import ConfigCategory from '$lib/settings/ConfigCategory.svelte';
	import ConfigSection from './ConfigSection.svelte';
	import ConfigItem from '$lib/settings/ConfigItem.svelte';
	import { proxy } from '$lib/stores';

	function cpuAction(event) {
		console.log('CPU: ' + event.detail.text);
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
			<ConfigItem on:select={cpuAction}
				name="CPU"
				values={[
					{ name: '68000', id: $proxy.CPU_68000 },
					{ name: '68010', id: $proxy.CPU_68010 },
					{ name: '68EC020', id: $proxy.CPU_68EC020 }
				]}
			/>
			<ConfigItem
				name="Frequency"
				values={[
					{ name: '7 Mhz', id: 0 },
					{ name: '14 Mhz', id: 1 },
					{ name: '21 Mhz', id: 2 },
					{ name: '28 Mhz', id: 3 },
					{ name: '35 Mhz', id: 4 },
					{ name: '42 Mhz', id: 5 },
					{ name: '84 Mhz', id: 6 },
				]}
			/>
		</ConfigSection>
		<ConfigSection name="Custom Chipset">
			<ConfigItem
				name="Agnus Revision"
				values={[
					{ name: 'Early OCS', id: 0 },
					{ name: 'OCS', id: 1 },
					{ name: 'ECS (1MB)', id: 2 },
					{ name: 'ECS (2MB)', id: 3 }
				]}
			/>
			<ConfigItem
				name="Denise Revision"
				values={[
					{ name: 'OCS', id: 0 },
					{ name: 'ECS', id: 1 }
				]}
			/>
			<ConfigItem name="Real-Time Clock" />
		</ConfigSection>
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
</div>
