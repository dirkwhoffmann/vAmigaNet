<script lang="ts">
	import { fade } from 'svelte/transition';
	import { MenuItem, Opt } from "$lib/types";
	import ConfigSection from './ConfigSection.svelte';
	import ConfigItem from '$lib/Settings/ConfigItem.svelte';
	import { config, poweredOn, proxy } from '$lib/stores';


</script>

<div in:fade>
	<ConfigSection name="CPU">
		<ConfigItem
			name="CPU"
			items={[
				new MenuItem('68000', $proxy.CPU_68000),
				new MenuItem('68010', $proxy.CPU_68010),
				new MenuItem('68020', $proxy.CPU_68EC020)
			]}
			selectedTag={$config.getNum(Opt.CPU_REVISION)}
			on:select={(e) => $config.setNum(Opt.CPU_REVISION, e.detail.value)}
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
			selectedTag={$config.getNum(Opt.CPU_SPEED)}
			on:select={(e) => $config.setNum(Opt.CPU_SPEED, e.detail.value)}
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
			selectedTag={$config.getNum(Opt.AGNUS_REVISION)}
			on:select={(e) => $config.setNum(Opt.AGNUS_REVISION, e.detail.value)}
			locked={$poweredOn}
		/>
		<ConfigItem
			name="Denise Revision"
			items={[
				new MenuItem('OCS', $proxy.DENISE_OCS),
				new MenuItem('ECS', $proxy.DENISE_ECS),
			]}
			selectedTag={$config.getNum(Opt.DENISE_REVISION)}
			on:select={(e) => $config.setNum(Opt.DENISE_REVISION, e.detail.value)}
			locked={$poweredOn}
		/>
		<ConfigItem
			name="Real-time Clock"
			items={[
				new MenuItem('NONE', $proxy.RTC_NONE),
				new MenuItem('OKI', $proxy.RTC_OKI),
				new MenuItem('RICOH', $proxy.RTC_RICOH),
			]}
			selectedTag={$config.getNum(Opt.RTC_MODEL)}
			on:select={(e) => $config.setNum(Opt.RTC_MODEL, e.detail.value)}
			locked={$poweredOn}
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
			selectedTag={$config.getNum(Opt.CHIP_RAM)}
			on:select={(e) => $config.setNum(Opt.CHIP_RAM, e.detail.value)}
			locked={$poweredOn}
		/>
		<ConfigItem
			name="Slow RAM"
			items={[
				new MenuItem('0 KB', 0),
				new MenuItem('512 KB', 512),
				new MenuItem('1 MB', 1024),
				new MenuItem('1.5 MB', 1536)
			]}
			selectedTag={$config.getNum(Opt.SLOW_RAM)}
			on:select={(e) => $config.setNum(Opt.SLOW_RAM, e.detail.value)}
			locked={$poweredOn}
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
			selectedTag={$config.getNum(Opt.FAST_RAM)}
			on:select={(e) => $config.setNum(Opt.FAST_RAM, e.detail.value)}
			locked={$poweredOn}
		/>
		<ConfigItem
			name="Memory Layout"
			items={[
				new MenuItem('Amiga 500', $proxy.BANK_MAP_A500),
				new MenuItem('Amiga 1000', $proxy.BANK_MAP_A1000),
				new MenuItem('Amiga 2000A', $proxy.BANK_MAP_A2000A),
				new MenuItem('Amiga 2000B', $proxy.BANK_MAP_A2000B),
			]}
			selectedTag={$config.getNum(Opt.BANK_MAP)}
			on:select={(e) => $config.setNum(Opt.BANK_MAP, e.detail.value)}
			locked={$poweredOn}
		/>
		<ConfigItem
			name="Memory Startup Pattern"
			items={[
				new MenuItem('All Zeroes', $proxy.RAM_INIT_ALL_ZEROES),
				new MenuItem('All Ones', $proxy.RAM_INIT_ALL_ONES),
				new MenuItem('Random', $proxy.RAM_INIT_RANDOMIZED)
			]}
			selectedTag={$config.getNum(Opt.INIT_PATTERN)}
			on:select={(e) => $config.setNum(Opt.INIT_PATTERN, e.detail.value)}
			locked={$poweredOn}
		/>
		<ConfigItem
			name="Unmapped Memory Area"
			items={[
				new MenuItem('Floating', $proxy.UNMAPPED_FLOATING),
				new MenuItem('All Zeroes', $proxy.UNMAPPED_ALL_ZEROES),
				new MenuItem('All Ones', $proxy.UNMAPPED_ALL_ONES)
			]}
			selectedTag={$config.getNum(Opt.UNMAPPED)}
			on:select={(e) => $config.setNum(Opt.UNMAPPED, e.detail.value)}
			locked={$poweredOn}
		/>
		<ConfigItem
			name="Emulate Slow RAM Mirror"
			items={[
				new MenuItem('Yes', 1),
				new MenuItem('No', 0)
			]}
			selectedTag={$config.getNum(Opt.SLOW_RAM_MIRROR)}
			on:select={(e) => $config.setNum(Opt.SLOW_RAM_MIRROR, e.detail.value)}
		/>
		<ConfigItem
			name="Emulate Slow RAM Bus Delays"
			items={[
				new MenuItem('Yes', 1),
				new MenuItem('No', 0)
			]}
			selectedTag={$config.getNum(Opt.SLOW_RAM_DELAY)}
			on:select={(e) => $config.setNum(Opt.SLOW_RAM_DELAY, e.detail.value)}
		/>
	</ConfigSection>
	<ConfigSection name="Floppy Drives">
		<ConfigItem
			name="DF0"
			items={[
				new MenuItem('Internal Drive', 1)
			]}
			tag={0}
			selectedTag={$config.getNum(Opt.DF0)}
			on:select={(e) => $config.setNum(Opt.DF0, e.detail.value)}
			locked={$poweredOn}
		/>
		<ConfigItem
			name="DF1"
			items={[
				new MenuItem('None', 0),
				new MenuItem('A1010', 1)
			]}
			tag={1}
			selectedTag={$config.getNum(Opt.DF1)}
			on:select={(e) => $config.setNum(Opt.DF1, e.detail.value)}
			locked={$poweredOn}
		/>
		<ConfigItem
			name="DF2"
			items={[
				new MenuItem('None', 0),
				new MenuItem('A1010', 1)
			]}
			tag={2}
			selectedTag={$config.getNum(Opt.DF2)}
			on:select={(e) => $config.setNum(Opt.DF2, e.detail.value)}
			locked={$poweredOn || !$config.getBool(Opt.DF1) }
		/>
		<ConfigItem
			name="DF3"
			items={[
				new MenuItem('None', 0),
				new MenuItem('A1010', 1)
			]}
			tag={3}
			selectedTag={$config.getNum(Opt.DF3)}
			on:select={(e) => $config.setNum(Opt.DF3, e.detail.value)}
			locked={$poweredOn || !$config.getBool(Opt.DF2) }
		/>
	</ConfigSection>
	<ConfigSection name="Hard Drives">
		<ConfigItem
				name="HD0"
				items={[
				new MenuItem('None', 0),
				new MenuItem('Zorro Board', 1)
			]}
				tag={0}
				selectedTag={$config.getNum(Opt.HD0)}
				on:select={(e) => $config.setNum(Opt.HD0, e.detail.value)}
				locked={$poweredOn}
		/>
		<ConfigItem
				name="HD1"
				items={[
				new MenuItem('None', 0),
				new MenuItem('Zorro Board', 1)
			]}
				tag={1}
				selectedTag={$config.getNum(Opt.HD1)}
				on:select={(e) => $config.setNum(Opt.HD1, e.detail.value)}
				locked={$poweredOn}
		/>
		<ConfigItem
				name="HD2"
				items={[
				new MenuItem('None', 0),
				new MenuItem('Zorro Board', 1)
			]}
				tag={2}
				selectedTag={$config.getNum(Opt.HD2)}
				on:select={(e) => $config.setNum(Opt.HD2, e.detail.value)}
				locked={$poweredOn}
		/>
		<ConfigItem
				name="HD3"
				items={[
				new MenuItem('None', 0),
				new MenuItem('Zorro Board', 1)
			]}
				tag={3}
				selectedTag={$config.getNum(Opt.HD3)}
				on:select={(e) => $config.setNum(Opt.HD3, e.detail.value)}
				locked={$poweredOn}
		/>
	</ConfigSection>
</div>
