<script lang="ts">
    import { fade } from 'svelte/transition';
    import { Layer } from "$lib/types";
    import { config, layer } from "$lib/stores";
    import ConfigCategory from '$lib/Settings/ConfigCategory.svelte';
    import GeneralSettings from '$lib/Settings/GeneralSettings.svelte';
    import MachineSettings from '$lib/Settings/MachineSettings.svelte';
    import CompSettings from '$lib/Settings/CompSettings.svelte';
    import VideoSettings from '$lib/Settings/VideoSettings.svelte';
    import AudioSettings from '$lib/Settings/AudioSettings.svelte';

    // The currently active tab
    let active = 'GENERAL';

    // Persists all settings of the current pane in client-side storage
    function saveAction()
    {
        switch (active) {
            case 'GENERAL':
                $config.saveGeneralSettings();
                break;
            case 'MACHINE':
                $config.saveMachineSettings();
                break;
            case 'COMPATIBILITY':
                $config.saveCompatibilitySettings();
                break;
            case 'AUDIO':
                $config.saveAudioSettings();
                break;
            case 'VIDEO':
                $config.saveVideoSettings();
                break;
        }
    }

    // Reverts all settings of the current pane to their default values
    function resetAction()
    {
        switch (active) {
            case 'GENERAL':
                $config.restoreGeneralDefaults();
                break;
            case 'MACHINE':
                $config.restoreMachineDefaults();
                break;
            case 'COMPATIBILITY':
                $config.restoreCompatibilityDefaults();
                break;
            case 'AUDIO':
                $config.restoreAudioDefaults();
                break;
            case 'VIDEO':
                $config.restoreVideoDefaults();
                break;
        }
    }
</script>

{#if $layer === Layer.settings}
    <div
            class="absolute top-0 left-0 w-full h-full flex overflow-auto text-base-content"
            transition:fade
    >
        <div class="w-16 mr-1"></div>
        <div class="bg-base-100 opacity-100 bg-opacity-80 mt-0 p-4 grow h-full overflow-auto">
            <div class="font-sofia-extra">
                <div class="flex border-0 border-red-500 justify-between">
                    <div class="text-5xl">SETTINGS</div>
                </div>
                <div class="flex border-0 border-red-500 justify-between">
                    <div class="float space-x-4 mb-6 border-0">
                        <ConfigCategory name="GENERAL" {active} on:click={() => (active = 'GENERAL')}/>
                        <ConfigCategory name="MACHINE" {active} on:click={() => (active = 'MACHINE')}/>
                        <ConfigCategory name="COMPATIBILITY" {active} on:click={() => (active = 'COMPATIBILITY')}/>
                        <ConfigCategory name="VIDEO" {active} on:click={() => (active = 'VIDEO')}/>
                        <ConfigCategory name="AUDIO" {active} on:click={() => (active = 'AUDIO')}/>
                    </div>
                    <div class="flex justify-between mb-6 border-0 w-[18rem]">
                        <button class="btn btn-outline text-2xl font-normal w-[8.5rem]" on:click={saveAction}>Save
                        </button>
                        <button class="btn btn-outline text-2xl font-normal w-[8.5rem]" on:click={resetAction}>Reset
                        </button>
                    </div>
                </div>
            </div>
            {#if active === 'GENERAL'}
                <GeneralSettings/>
            {:else if active === 'MACHINE'}
                <MachineSettings/>
            {:else if active === 'COMPATIBILITY'}
                <CompSettings/>
            {:else if active === 'VIDEO'}
                <VideoSettings/>
            {:else if active === 'AUDIO'}
                <AudioSettings/>
            {/if}
        </div>
    </div>
{/if}