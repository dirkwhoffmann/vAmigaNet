<script lang="ts">
    import { fade } from 'svelte/transition';
    import { MenuItem, Opt } from "$lib/types";
    import { config } from '$lib/stores';
    import ConfigSection from './ConfigSection.svelte';
    import ConfigItem from '$lib/Settings/ConfigItem.svelte';
</script>

<div in:fade>
    <ConfigSection name="Blitter">
        <ConfigItem
                name="Accuracy"
                items={[
                    new MenuItem('Low', 0),
				    new MenuItem('Medium', 1),
				    new MenuItem('High', 2)
				    ]}
                on:select={(e) => $config.setNum(Opt.BLITTER_ACCURACY, e.detail.value)}
                selectedTag={$config.getNum(Opt.BLITTER_ACCURACY)}
        />
    </ConfigSection>
    <ConfigSection name="Chipset Features">
        <ConfigItem
                name="Emulate TOD Bug"
                items={[
                    new MenuItem('Yes', 1),
                    new MenuItem('No', 0)
                    ]}
                on:select={(e) => $config.setNum(Opt.TODBUG, e.detail.value)}
                selectedTag={$config.getNum(Opt.TODBUG)}
        />
        <ConfigItem
                name="Emulate Dropped Register Writes"
                items={[
                    new MenuItem('Yes', 1),
                    new MenuItem('No', 0)
                    ]}
                on:select={(e) => $config.setNum(Opt.PTR_DROPS, e.detail.value)}
                selectedTag={$config.getNum(Opt.PTR_DROPS)}
        />
    </ConfigSection>
    <ConfigSection name="Timing">
        <ConfigItem
                name="Sync CIA Accesses With E-Clock"
                items={[
                    new MenuItem('Yes', 1),
                    new MenuItem('No', 0)
                    ]}
                on:select={(e) => $config.setNum(Opt.ECLOCK_SYNCING, e.detail.value)}
                selectedTag={$config.getNum(Opt.ECLOCK_SYNCING)}
        />
    </ConfigSection>
    <ConfigSection name="Floppy Drives">
        <ConfigItem
                name="Drive Speed"
                items={[
				    new MenuItem('Original', 1),
				    new MenuItem('Accelerated (2 x)', 2),
				    new MenuItem('Accelerated (4 x)', 4),
				    new MenuItem('Accelerated (8 x)', 8),
				    new MenuItem('Infinite', -1),
			    ]}
                on:select={(e) => $config.setNum(Opt.DRIVE_SPEED, e.detail.value)}
                selectedTag={$config.getNum(Opt.DRIVE_SPEED)}
        />
    </ConfigSection>
    <ConfigSection name="Sprites">
        <ConfigItem
                name="Sprite-Sprite Collision Detection"
                items={[
                    new MenuItem('Yes', 1),
                    new MenuItem('No', 0)
                    ]}
                on:select={(e) => $config.setNum(Opt.CLX_SPR_SPR, e.detail.value)}
                selectedTag={$config.getNum(Opt.CLX_SPR_SPR)}
        />
        <ConfigItem
                name="Sprite-Playfield Collision Detection"
                items={[
                    new MenuItem('Yes', 1),
                    new MenuItem('No', 0)
                    ]}
                on:select={(e) => $config.setNum(Opt.CLX_SPR_PLF, e.detail.value)}
                selectedTag={$config.getNum(Opt.CLX_SPR_PLF)}
        />
        <ConfigItem
                name="Playfield-Playfield Collision Detection"
                items={[
                    new MenuItem('Yes', 1),
                    new MenuItem('No', 0)
                    ]}
                on:select={(e) => $config.setNum(Opt.CLX_PLF_PLF, e.detail.value)}
                selectedTag={$config.getNum(Opt.CLX_PLF_PLF)}
        />
    </ConfigSection>
    <ConfigSection name="Keyboard">
        <ConfigItem
                name="Transmit Keycodes Bit by Bit"
                items={[
                    new MenuItem('Yes', 1),
                    new MenuItem('No', 0)
                    ]}
                on:select={(e) => $config.setNum(Opt.ACCURATE_KEYBOARD, e.detail.value)}
                selectedTag={$config.getNum(Opt.ACCURATE_KEYBOARD)}
                tag={1}
        />
    </ConfigSection>
</div>
