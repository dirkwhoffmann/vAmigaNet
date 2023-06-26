<script lang="ts">
    import { onMount } from 'svelte';
    import { fade } from 'svelte/transition';
    import { goto } from '$app/navigation';
    import DiGrails from 'svelte-icons/di/DiGrails.svelte';
    import FaGithub from 'svelte-icons/fa/FaGithub.svelte';
    import FaMicrochip from 'svelte-icons/fa/FaMicrochip.svelte';
    import GiBatMask from 'svelte-icons/gi/GiBatMask.svelte';
    import MdPowerSettingsNew from 'svelte-icons/md/MdPowerSettingsNew.svelte';
    import GoLaw from 'svelte-icons/go/GoLaw.svelte';
    import { Layer } from '$lib/types';
    import MainPageLink from '$lib/Widgets/MainPageLink.svelte';
    import Impressum from '$lib/Impressum.svelte';
    import RomViewer from '$lib/RomViewer.svelte';
    import Showcases from '$lib/Showcases/Showcases.svelte';
    import { demos } from '$lib/Showcases/database';
    import { amiga, audio, layer, poweredOn, proxy, showSidebar } from '$lib/stores';

    let debug = ''; // 'border-2';
    let showRomViewer = false;
    let showImpressum = false;

    $: if (($layer === Layer.kickstart)) {
        showRomViewer = true;
    }

    onMount(() => {

        // Prefetch some images
        new Image().src = "footage/3ddemo-small.jpg"
        new Image().src = "footage/batmanrises-small.jpg"
        new Image().src = "footage/celtic-small.jpg"
        new Image().src = "footage/china-small.jpg"
        new Image().src = "footage/defender-small.jpg"
        new Image().src = "footage/desertdreams-small.jpg"
        new Image().src = "footage/diagrom-small.jpg"
        new Image().src = "footage/eon-small.jpg"
        new Image().src = "footage/inebriation-small.jpg"
        new Image().src = "footage/kyrios-small.jpg"
        new Image().src = "footage/paccer-small.jpg"
        new Image().src = "footage/rinkadink-small.jpg"
        new Image().src = "footage/sdi-small.jpg"
        new Image().src = "footage/stateart-small.jpg"
        new Image().src = "footage/sysinfo-small.jpg"
        new Image().src = "footage/testkit-small.jpg"
        new Image().src = "footage/traprunner-small.jpg"
    });

    async function switchOn()
    {
        await $audio.setup();
        $amiga.run();
    }

    async function runDemo()
    {
        await $audio.setup();
        $proxy.runShowcase(demos[0]);
    }

    function gotoGitHub()
    {
        goto('https://dirkwhoffmann.github.io/vAmiga');
    }

    async function openShowcases()
    {
        await $audio.setup();
        $layer = $layer === Layer.showcases ? Layer.none : Layer.showcases;
        $showSidebar = false;
    }

    async function openRoms()
    {
        await $audio.setup();
        showRomViewer = true;
    }

    function openImpressum()
    {
        showImpressum = true;
    }
</script>

{#if !$poweredOn}

    <div class="modal" class:modal-open={showRomViewer}>
        <div class="modal-box h-2/3 w-2/3 max-w-none">
            <RomViewer bind:show={showRomViewer}/>
        </div>
    </div>

    <div class="modal" class:modal-open={showImpressum}>
        <div class="modal-box">
            <Impressum bind:show={showImpressum}/>
        </div>
    </div>

    <div class="h-full flex flex-col {debug}" transition:fade>
        <div in:fade={{ duration: 2000 }}>
            <div class="absolute h-full blur-sm">
                <div class="h-full w-screen bg-gradient-to-t from-primary to-secondary"/>
            </div>
            <div class="absolute h-full blur-sm">
                <img class="h-full w-screen object-fill opacity-60" src="matrix.jpg" alt="Background"/>
            </div>
        <!--
        <div class="absolute h-full">
            <img class="h-full w-screen object-fill" src="splash-bg.jpg" alt="Background"/>
        </div>
        -->
        </div>
        {#if $layer === Layer.showcases}
            <Showcases/>
        {:else}
            <div
                    in:fade
                    class="relative bg-transparent grow flex flex-col items-center justify-center {debug}"
            >
                {#if $layer === Layer.none}
                    <div class={debug}>
                        <div class="rounded flex justify-center">
                            <img class="h-24 p-2 mt-3" src="va-icon.png" alt="vAmiga Icon"/>
                            <div class="p-6 text-white">
                                <div class="flex">
                                    <div class="font-sofia-extra text-7xl mr-2">
                                        vAmiga<span class="opacity-75">.net</span>
                                    </div>
                                </div>
                                <div class="font-sofia-semi text-xl pl-2 pb-10">Version 1.0</div>
                                <div class="flex space-x-5">
                                    <div class="tooltip tooltip-primary" data-tip="Power On">
                                        <button class="btn btn-outline btn-square p-1.5" on:click={switchOn}>
                                            <MdPowerSettingsNew/>
                                        </button>
                                    </div>
                                    <div class="tooltip tooltip-primary" data-tip="Run Demo">
                                        <button class="btn btn-outline btn-square p-1.5" on:click={runDemo}>
                                            <GiBatMask/>
                                        </button>
                                    </div>
                                    <div class="tooltip tooltip-primary" data-tip="Visit GitHub">
                                        <button class="btn btn-outline btn-square p-1.5" on:click={gotoGitHub}>
                                            <FaGithub/>
                                        </button>
                                    </div>
                                </div>
                            </div>
                        </div>
                    </div>
                {/if}
            </div>
        {/if}
        <div class="relative flex justify-center align-middle bg-gray-900/50 space-x-8 {debug}">
            <!--
                <MainPageLink href="#learnmore">
                    <div slot="icon"><FaBookOpen /></div>
                    <div slot="description">Learn more</div>
                </MainPageLink>
                -->
            <MainPageLink on:click={openRoms}>
                <div slot="icon" class="p-1.5">
                    <FaMicrochip/>
                </div>
                <div slot="description">Kickstart</div>
            </MainPageLink>
            <MainPageLink on:click={openShowcases}>
                <div slot="icon">
                    <DiGrails/>
                </div>
                <div slot="description">Showcases</div>
            </MainPageLink>
            <MainPageLink on:click={openImpressum}>
                <div slot="icon">
                    <GoLaw/>
                </div>
                <div slot="description">Impressum</div>
            </MainPageLink>
            <!--
            <MainPageLink on:click={openImpressum}>
                <div slot="icon" class="p-1.5">
                    <FaGithub/>
                </div>
                <div slot="description">GitHub</div>
            </MainPageLink>
            -->
        </div>
    </div>
{/if}