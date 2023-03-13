<script lang="ts">
    import { createEventDispatcher } from 'svelte';
    import GoInfo from 'svelte-icons/go/GoInfo.svelte';
    import GiPadlock from 'svelte-icons/gi/GiPadlock.svelte';
    import type { ActionEvent, MenuItem } from '$lib/types';
    import Slider from '$lib/Widgets/Slider.svelte';
    import Menu from '$lib/Widgets/Menu.svelte';
    import Chevron from "$lib/Widgets/Chevron.svelte";

    export let name = '';
    export let min = 0;
    export let max = 0;
    export let locked = false;
    export let info = false;
    export let tag = 0;
    export let selectedTag = 0;

    export let items: MenuItem[] = [];

    const dispatcher = createEventDispatcher<{ select: ActionEvent }>();
    const infoDispatcher = createEventDispatcher<{ info: ActionEvent }>();

    $: opac = locked ? 'opacity-50' : '';

    const infoAction = (e: Event) => {
        e.preventDefault();
        infoDispatcher('info', {tag: tag, value: selectedTag});
    };

    $: displayName = displayedName(selectedTag);

    function displayedName(selectedTag: number): string
    {
        for (const item of items) {
            if (item.tag == selectedTag) return item.title;
        }
        return '???';
    }

    $: updateSelected(selectedTag);

    function updateSelected(sel: number)
    {
        items.forEach(function (item) {
            item.isSelected = item.tag == sel;
        });
        items = items;
    }

    function selectAction(event: CustomEvent<ActionEvent>)
    {
        selectedTag = event.detail.value;
        dispatcher('select', {tag: tag, value: selectedTag});
    }
</script>

<div class="py-0.5 px-0">
    <div class="w-full flex text-xl space-x-1 justify-between items-center">
        <div class="border-0 bg-primary w-full h-12 flex grow overflow-hidden">
            <div
                    class="w-full border-0 text-xl {opac} text-primary-content flex items-center justify-between"
            >
                <div class="border-0 mx-2 flex grow overflow-hidden whitespace-nowrap">{name}</div>
            </div>
        </div>
        <div
                class="border-0 bg-primary w-20 h-12 flex items-center justify-center {locked
				? ''
				: 'hidden'}"
        >
            <button class="h-7 w-7 text-primary-content {opac}">
                <GiPadlock/>
            </button>
        </div>
        <div
                class="border-0 bg-primary w-20 h-12 flex items-center justify-center {info ? '' : 'hidden'}"
        >
            <button class="h-7 w-7 text-primary-content {opac}" on:click={infoAction}>
                <GoInfo/>
            </button>
        </div>
        <div class="border-0 bg-primary h-12">
            {#if min === max}
                <Menu isEnabled={!locked} {items} listStyle="w-[18rem] bg-accent text-accent-content"
                      on:select={selectAction}>
                    {#if locked}
                        <button class="btn btn-primary {opac} w-[18rem] border-0 rounded-none text-xl font-normal"
                        >{displayName}</button>
                    {:else}
                        <button class="btn btn-primary w-[18rem] border-0 rounded-none text-xl font-normal"
                        >
                            <Chevron>{displayName}</Chevron>
                        </button
                        >
                    {/if}
                </Menu>
            {:else}
                <Slider {min} {max} {locked} {tag} value={selectedTag} on:select>
                    <button class="btn btn-primary {opac} w-[18rem] border-0 rounded-none text-xl font-normal"
                    >{selectedTag}</button>
                </Slider>
            {/if}
        </div>
    </div>
</div>
