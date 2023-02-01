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
	import ConfigRow from '$lib/settings/ConfigRow.svelte';
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
			<ConfigRow name="Revision" />
			<ConfigRow name="Speed" />
		</ConfigSection>
		<ConfigSection name="Custom Chipset">
			<ConfigRow name="Agnus Revision" />
			<ConfigRow name="Denise Revision" />
			<ConfigRow name="Real-Time Clock" />
		</ConfigSection>
		<ConfigSection name="Memory">
			<ConfigRow name="Chip RAM" />
			<ConfigRow name="Slow RAM" />
			<ConfigRow name="Fast RAM" />
			<ConfigRow name="Memory Layout" />
			<ConfigRow name="Memory Startup Pattern" />
			<ConfigRow name="Unmapped Area" />
			<ConfigRow name="Unmapped Area" />
			<ConfigRow name="Emulate Slow RAM Mirror" />
			<ConfigRow name="Emulate Slow RAM Bus Delays" />
		</ConfigSection>
	</div>
</div>
