<script lang="ts">
    import { onMount } from 'svelte';
    import { fade } from 'svelte/transition';
    import { Opt } from "$lib/types";
    import { config } from '$lib/stores';
    import type { ActionEvent } from '$lib/types';
    import { MenuItem, Theme } from '$lib/types';
    import ConfigSection from './ConfigSection.svelte';
    import ConfigItem from '$lib/Settings/ConfigItem.svelte';

    onMount(() => {
        update();
    });

    function update()
    {
    }

    function warpAction(event: CustomEvent<ActionEvent>)
    {
        console.log('warpAction', event.detail.value);
        $config.set(Opt.WARP_MODE, event.detail.value);
    }

    function themeAction(event: CustomEvent<ActionEvent>)
    {
        console.log('themeAction', event.detail.value);
        $config.set(Opt.THEME, event.detail.value);
        update();
    }

    function borderAction(event: CustomEvent<ActionEvent>)
    {
        $config.set(Opt.CANVAS_BORDER, event.detail.value == 1 ? 'true' : 'false');
        update();
    }

    function shakingAction(event: CustomEvent<ActionEvent>)
    {
        console.log('shakingAction');
        $config.set(Opt.SHAKING, event.detail.value == 1 ? 'true' : 'false');
        update();
    }
</script>

<div in:fade>
    <ConfigSection name="Warp mode">
        <ConfigItem
                name="Enable warp mode"
                selectedTag={$config.getNum(Opt.WARP_MODE)}
                on:select={warpAction}
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
                on:select={themeAction}
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
                on:select={borderAction}
                items={[new MenuItem('Yes', 1), new MenuItem('No', 0)]}
        />
    </ConfigSection>
    <ConfigSection name="Peripherals">
        <ConfigItem
                name="Release Mouse by Shaking"
                selectedTag={$config.getNum(Opt.SHAKING)}
                on:select={shakingAction}
                items={[new MenuItem('Yes', 1), new MenuItem('No', 0)]}
        />
    </ConfigSection>
</div>
