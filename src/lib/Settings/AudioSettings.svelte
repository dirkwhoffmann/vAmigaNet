<script lang="ts">
	import { fade } from 'svelte/transition';
	import { MenuItem, Opt } from '$lib/types';
	import { config, proxy } from '$lib/stores';
	import ConfigSection from './ConfigSection.svelte';
	import ConfigItem from './ConfigItem.svelte';

</script>

<div in:fade>
	<ConfigSection name="Sound Synthesis">
		<ConfigItem
				name="Interpolation Method"
				items={[
                    new MenuItem('None', 0),
                    new MenuItem('Nearest', 1),
                    new MenuItem('Linear', 2),
                    ]}
				on:select={(e) => $config.setNum(Opt.SAMPLING_METHOD, e.detail.value)}
				selectedTag={$config.getNum(Opt.SAMPLING_METHOD)}
		/>
		<ConfigItem
				name="Audio Filter"
				items={[
                    new MenuItem('None', 0),
                    new MenuItem('A500', 1),
                    new MenuItem('A1000', 2),
                    new MenuItem('A1200', 3),
                    new MenuItem('Legacy Filter', 4),
                    new MenuItem('Low-pass only', 5),
                    new MenuItem('LED filter only', 6),
                    new MenuItem('High-pass only', 7),
                    ]}
				on:select={(e) => $config.set(Opt.FILTER_TYPE, e.detail.value)}
				selectedTag={$config.get(Opt.FILTER_TYPE)}
		/>
	</ConfigSection>
	<ConfigSection name="Speakers">
		<ConfigItem
			name="Left Speaker Volume"
			tag={$proxy.OPT_AUDVOLL}
			selectedTag={$config.get(Opt.AUDVOLL)}
			on:select={(e) => $config.set(Opt.AUDVOLL, e.detail.value)}
			min={0}
			max={100}
		/>
		<ConfigItem
			name="Right Speaker Volume"
			tag={$proxy.OPT_AUDVOLR}
			selectedTag={$config.get(Opt.AUDVOLR)}
			on:select={(e) => $config.set(Opt.AUDVOLR, e.detail.value)}
			min={0}
			max={100}
		/>
		<ConfigItem
			name="Paula Channel 0 Volume"
			tag={0}
			selectedTag={$config.get(Opt.AUDVOL0)}
			on:select={(e) => $config.set(Opt.AUDVOL0, e.detail.value)}
			min={0}
			max={100}
		/>
		<ConfigItem
			name="Paula Channel 1 Volume"
			tag={1}
			selectedTag={$config.get(Opt.AUDVOL1)}
			on:select={(e) => $config.set(Opt.AUDVOL1, e.detail.value)}
			min={0}
			max={100}
		/>
		<ConfigItem
			name="Paula Channel 2 Volume"
			tag={2}
			selectedTag={$config.get(Opt.AUDVOL2)}
			on:select={(e) => $config.set(Opt.AUDVOL2, e.detail.value)}
			min={0}
			max={100}
		/>
		<ConfigItem
			name="Paula Channel 3 Volume"
			tag={3}
			selectedTag={$config.get(Opt.AUDVOL3)}
			on:select={(e) => $config.set(Opt.AUDVOL3, e.detail.value)}
			min={0}
			max={100}
		/>
	</ConfigSection>
	<ConfigSection name="Drive Sounds">
		<ConfigItem
			name="Head Step Volume"
			tag={$proxy.OPT_STEP_VOLUME}
			selectedTag={$config.get(Opt.STEP_VOLUME)}
			on:select={(e) => $config.set(Opt.STEP_VOLUME, e.detail.value)}
			min={0}
			max={100}
		/>
		<ConfigItem
			name="Poll Disk Volume"
			tag={$proxy.OPT_POLL_VOLUME}
			selectedTag={$config.get(Opt.POLL_VOLUME)}
			on:select={(e) => $config.set(Opt.POLL_VOLUME, e.detail.value)}
			min={0}
			max={100}
		/>
		<ConfigItem
			name="Insert Disk Volume"
			tag={$proxy.OPT_INSERT_VOLUME}
			selectedTag={$config.get(Opt.INSERT_VOLUME)}
			on:select={(e) => $config.set(Opt.INSERT_VOLUME, e.detail.value)}
			min={0}
			max={100}
		/>
		<ConfigItem
			name="Eject Disk Volume"
			tag={$proxy.OPT_EJECT_VOLUME}
			selectedTag={$config.get(Opt.EJECT_VOLUME)}
			on:select={(e) => $config.set(Opt.EJECT_VOLUME, e.detail.value)}
			min={0}
			max={100}
		/>
	</ConfigSection>
</div>
