<script lang="ts">
    import { createEventDispatcher } from 'svelte';
    import { Layer } from '$lib/types';
    import SidebarButton from '$lib/Sidebar/SidebarButton.svelte';
    import SidebarSection from '$lib/Sidebar/SidebarSection.svelte';
    import { fade } from 'svelte/transition';
    import { debugDma, layer, layout, port1, port2, poweredOn, running, showSidebar } from '$lib/stores';
    import SidebarPad from '$lib/Sidebar/SidebarPad.svelte';

    let sel = '';
    let duration = 200;

    const dispatch = createEventDispatcher<{ select: { sender: string; state: boolean } }>();

    function select(event: CustomEvent<{ sender: string; state: boolean }>)
    {
        event.preventDefault();

        const sender = event.detail.sender;
        const state = event.detail.state;
        sel = sender == sel ? '' : sender;
        console.log('sender: ', sender, ' state: ', state);
        dispatch('select', {sender: sender, state: state});
    }

    const portIcons = [
        'icons/device-none.png',
        'icons/device-mouse.png',
        'icons/device-keyset-1.png',
        'icons/device-keyset-2.png',
        'icons/device-usb-1.png',
        'icons/device-usb-2.png'
    ]

    const power = {id: 'power', icon: 'icons/powerIcon.png'};
    const pause = {id: 'pause', icon: 'icons/pauseIcon.png'};
    const reset = {id: 'reset', icon: 'icons/resetIcon.png'};
    const settings = {id: 'settings', icon: 'icons/settingsIcon.png'};
    const port1Button = {id: 'port1', icon: 'icons/device-none.png'};
    const port2Button = {id: 'port2', icon: 'icons/device-none.png'};
    const port1Items = [
        {id: 'empty1', icon: portIcons[0]},
        {id: 'mouse1', icon: portIcons[1]},
        {id: 'keyset11', icon: portIcons[2]},
        {id: 'keyset12', icon: portIcons[3]},
        {id: 'gamepad11', icon: portIcons[4]}
    ];
    const port2Items = [
        {id: 'empty2', icon: portIcons[0]},
        {id: 'mouse2', icon: portIcons[1]},
        {id: 'keyset21', icon: portIcons[2]},
        {id: 'keyset22', icon: portIcons[3]},
        {id: 'gamepad21', icon: portIcons[4]}
    ];
    const shell = {id: 'shell', icon: 'icons/retroShellIcon.png'};
    const monitor = {id: 'monitor', icon: 'icons/monitorIcon.png'};
    const layoutButton = {id: 'layout', icon: 'icons/layoutIcon.png'};
    const layoutItems = [
        {id: 'aspect', icon: 'icons/layoutAspectIcon.png'},
        {id: 'fit', icon: 'icons/layoutFitIcon.png'},
        {id: 'full', icon: 'icons/layoutFullIcon.png'}
    ];

    $: port1Button.icon = portIcons[$port1];
    $: port2Button.icon = portIcons[$port2];
    $: layoutButton.icon =
        $layout == 'full'
            ? 'icons/layoutFullIcon.png'
            : $layout == 'aspect'
                ? 'icons/layoutAspectIcon.png'
                : 'icons/layoutFitIcon.png';

    $: if ($running) {
        pause.icon = 'icons/pauseIcon.png';
    } else {
        pause.icon = 'icons/runIcon.png';
    }
</script>

{#if $showSidebar}
    <div transition:fade={{ duration }} class="">
        <div class="absolute top-0 left-0 bg-base-100 bg-opacity-80 flex flex-col w-16 items-center z-40">
            <div class="flex flex-col space-y-1.5 w-[48px] mt-1.5 mb-2 border-0">
                <SidebarButton on:select={select} item={power}/>
                {#if $poweredOn}
                    <SidebarButton on:select={select} item={pause}/>
                    <SidebarButton on:select={select} item={reset}/>
                {/if}
                <SidebarPad/>

                <SidebarSection
                        on:select={select}
                        expanded={sel === 'port1'}
                        item={port1Button}
                        subitems={port1Items}
                />
                <SidebarSection
                        on:select={select}
                        expanded={sel === 'port2'}
                        item={port2Button}
                        subitems={port2Items}
                />
                <SidebarPad/>

                <SidebarButton on:select={select} item={settings} active={$layer === Layer.settings}/>
                <SidebarButton on:select={select} item={shell} active={$layer === Layer.shell}/>
                <SidebarPad/>
                {#if $poweredOn}
                    <SidebarSection
                            on:select={select}
                            expanded={sel === 'layout'}
                            item={layoutButton}
                            subitems={layoutItems}
                    />
                    <SidebarButton on:select={select} item={monitor} active={$debugDma}/>
                {/if}
            </div>
        </div>
    </div>
{/if}