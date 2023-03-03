<script lang="ts">
    import { fade } from 'svelte/transition';
    import { Opt } from "$lib/types";
    import { config } from '$lib/stores';
    import { MenuItem, Theme } from '$lib/types';
    import ConfigSection from './ConfigSection.svelte';
    import ConfigItem from '$lib/Settings/ConfigItem.svelte';
</script>

<div in:fade>
    <ConfigSection name="Warp mode">
        <ConfigItem
                name="Enable warp mode"
                selectedTag={$config.getNum(Opt.WARP_MODE)}
                on:select={(e) => $config.setNum(Opt.WARP_MODE, Number(e.detail.value))}
                items={[
				new MenuItem('During Disk Accesses', 0),
				new MenuItem('Never', 1),
				new MenuItem('Always', 2)
			]}
        />
    </ConfigSection>
    <ConfigSection name="Appearance">
        <ConfigItem
                name="Color theme"
                selectedTag={$config.getNum(Opt.THEME)}
                on:select={(e) => $config.setNum(Opt.THEME, e.detail.value)}
                items={[
				new MenuItem('Default', Theme.default),
				new MenuItem('Light', Theme.light),
				new MenuItem('Dark', Theme.dark),
				new MenuItem('Coffee', Theme.coffee),
				new MenuItem('Cupcake', Theme.cupcake),
				new MenuItem('Forest', Theme.forest),
				new MenuItem('Aqua', Theme.aqua),
				new MenuItem('Garden', Theme.garden),
				new MenuItem('Pastel', Theme.pastel)
			]}
        />
        <ConfigItem
                name="Draw Canvas Border"
                selectedTag={$config.getNum(Opt.CANVAS_BORDER)}
                on:select={(e) => $config.setNum(Opt.CANVAS_BORDER, e.detail.value)}
                items={[new MenuItem('Yes', 1), new MenuItem('No', 0)]}
        />
    </ConfigSection>
    <ConfigSection name="Peripherals">
        <ConfigItem
                name="Release Mouse by Shaking"
                selectedTag={$config.getNum(Opt.SHAKING)}
                on:select={(e) => $config.setNum(Opt.SHAKING, e.detail.value)}
                items={[new MenuItem('Yes', 1), new MenuItem('No', 0)]}
        />
    </ConfigSection>
</div>
