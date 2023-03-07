<script lang="ts">
    import { onMount } from 'svelte';
    import { MenuItem, Opt, RenderMode } from '$lib/types';
    import { config, proxy } from '$lib/stores';
    import type { ActionEvent } from '$lib/types';
    import { fade } from 'svelte/transition';
    import ConfigSection from './ConfigSection.svelte';
    import ConfigItem from '$lib/Settings/ConfigItem.svelte';

    onMount(() => {
        update();
    });

    function update()
    {
    }

    function renderModeAction(event: CustomEvent<ActionEvent>)
    {
        $config.set(Opt.RENDER_MODE, event.detail.value);
        update();
    }

    function paletteAction(event: CustomEvent<ActionEvent>)
    {
        $config.set(Opt.PALETTE, event.detail.value);
        update();
    }

    function brightnessAction(event: CustomEvent<ActionEvent>)
    {
        $config.set(Opt.BRIGHTNESS, event.detail.value);
        update();
    }

    function contrastAction(event: CustomEvent<ActionEvent>)
    {
        $config.set(Opt.CONTRAST, event.detail.value);
        update();
    }

    function saturationAction(event: CustomEvent<ActionEvent>)
    {
        $config.set(Opt.SATURATION, event.detail.value);
        update();
    }

    function flickerAction(event: CustomEvent<ActionEvent>)
    {
        $config.set(Opt.FLICKER_WEIGHT, event.detail.value);
        update();
    }
</script>

<div in:fade>
    <ConfigSection name="WebGL">
        <ConfigItem
                name="Render Mode"
                items={[
				new MenuItem('Smooth', RenderMode.smooth),
				new MenuItem('Pixelated', RenderMode.pixelated)
			]}
                selectedTag={$config.getNum(Opt.RENDER_MODE)}
                on:select={renderModeAction}
        />
    </ConfigSection>
    <ConfigSection name="Colors">
        <ConfigItem
                name="Palette"
                items={[
				new MenuItem('Color', $proxy.PALETTE_COLOR),
				new MenuItem('Black and White', $proxy.PALETTE_BLACK_WHITE),
				new MenuItem('Paper White', $proxy.PALETTE_PAPER_WHITE),
				new MenuItem('Green', $proxy.PALETTE_GREEN),
				new MenuItem('Amber', $proxy.PALETTE_AMBER),
				new MenuItem('Sepia', $proxy.PALETTE_SEPIA)
			]}
                selectedTag={$config.getNum(Opt.PALETTE)}
                on:select={paletteAction}
        />
        <ConfigItem
                name="Brightness"
                min={0}
                max={100}
                tag={$proxy.OPT_BRIGHTNESS}
                selectedTag={$config.getNum(Opt.BRIGHTNESS)}
                on:select={brightnessAction}
        />
        <ConfigItem
                name="Contrast"
                min={0}
                max={100}
                tag={$proxy.OPT_CONTRAST}
                selectedTag={$config.getNum(Opt.CONTRAST)}
                on:select={contrastAction}
        />
        <ConfigItem
                name="Saturation"
                min={0}
                max={100}
                tag={$proxy.OPT_SATURATION}
                selectedTag={$config.getNum(Opt.SATURATION)}
                on:select={saturationAction}
        />
    </ConfigSection>
    <ConfigSection name="Interlace">
        <ConfigItem
                name="Flicker Weight"
                min={0}
                max={100}
                tag={1000}
                selectedTag={$config.getNum(Opt.FLICKER_WEIGHT)}
                on:select={flickerAction}
        />
    </ConfigSection>
</div>
