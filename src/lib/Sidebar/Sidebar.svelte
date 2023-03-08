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

    const power = {id: 'power', icon: 'icons/powerIcon.png'};
    const pause = {id: 'pause', icon: 'icons/pauseIcon.png'};
    const reset = {id: 'reset', icon: 'icons/resetIcon.png'};
    const settings = {id: 'settings', icon: 'icons/settingsIcon.png'};
    const port1Button = {id: 'port1', icon: 'icons/device-none.png'};
    const port2Button = {id: 'port2', icon: 'icons/device-none.png'};
    const port1Items = [
        {id: 'empty1', icon: 'icons/device-none.png'},
        {id: 'mouse1', icon: 'icons/device-mouse.png'},
        {id: 'keyset11', icon: 'icons/device-keyset-1.png'},
        {id: 'keyset12', icon: 'icons/device-keyset-2.png'}
    ];
    const port2Items = [
        {id: 'empty2', icon: 'icons/device-none.png'},
        {id: 'mouse2', icon: 'icons/device-mouse.png'},
        {id: 'keyset21', icon: 'icons/device-keyset-1.png'},
        {id: 'keyset22', icon: 'icons/device-keyset-2.png'}
    ];
    const shell = {id: 'shell', icon: 'icons/retroShellIcon.png'};
    const monitor = {id: 'monitor', icon: 'icons/monitorIcon.png'};
    const layoutButton = {id: 'layout', icon: 'icons/layoutIcon.png'};
    const layoutItems = [
        {id: 'aspect', icon: 'icons/layoutAspectIcon.png'},
        {id: 'fit', icon: 'icons/layoutFitIcon.png'},
        {id: 'full', icon: 'icons/layoutFullIcon.png'}
    ];

    $: {
        switch ($port1) {
            case 1:
                port1Button.icon = 'icons/device-mouse.png';
                break;
            case 2:
                port1Button.icon = 'icons/device-keyset-1.png';
                break;
            case 3:
                port1Button.icon = 'icons/device-keyset-2.png';
                break;
            default:
                port1Button.icon = 'icons/device-none.png';
                break;
        }
    }

    $: {
        switch ($port2) {
            case 1:
                port2Button.icon = 'icons/device-mouse.png';
                break;
            case 2:
                port2Button.icon = 'icons/device-keyset-1.png';
                break;
            case 3:
                port2Button.icon = 'icons/device-keyset-2.png';
                break;
            default:
                port2Button.icon = 'icons/device-none.png';
                break;
        }
    }

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
                        expanded={sel == 'port1'}
                        item={port1Button}
                        subitems={port1Items}
                />
                <SidebarSection
                        on:select={select}
                        expanded={sel == 'port2'}
                        item={port2Button}
                        subitems={port2Items}
                />
                <SidebarPad/>

                <SidebarButton on:select={select} item={settings} active={$layer == Layer.settings}/>
                <SidebarButton on:select={select} item={shell} active={$layer == Layer.shell}/>
                <SidebarPad />
                {#if $poweredOn}
                    <SidebarSection
                            on:select={select}
                            expanded={sel == 'layout'}
                            item={layoutButton}
                            subitems={layoutItems}
                    />
                    <SidebarButton on:select={select} item={monitor} active={$debugDma}/>
                {/if}
            </div>
        </div>
    </div>
{/if}