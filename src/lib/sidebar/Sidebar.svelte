<script lang="ts">
	import { createEventDispatcher } from 'svelte';
	import SidebarItem from '$lib/sidebar/SidebarItem.svelte';
	import SidebarButton from '$lib/sidebar/SidebarButton.svelte';
	import { Sidebar } from 'flowbite-svelte';
	import { fly, fade, slide, scale } from 'svelte/transition';

	let expanded = false;
	let sel = '';

	const dispatch = createEventDispatcher();

	function expand() {
		console.log('expand = ' + expanded);
		expanded = !expanded;
	}

	function select(e: Event) {
		e.preventDefault();
		sel = sel == e.target!.id ? "" : e.target!.id;
        console.log('sel = ' + sel);
		dispatch('select', { sender: sel });
	}
</script>

<div class="z-50 absolute top-0 left-0 p-4">
	<button class=""
		><img class="h-10" src="va-icon.png" alt="vAmiga Icon" on:click={expand} /></button
	>
	{#if expanded}
		<div transition:fade={{ duration: 200 }}>
			<!--<div transition:fly={{ y:-15 }} class="flex">-->
			<!--<div transition:slide>-->
			<div class="flex flex-col space-y-2">
				<div>
					<SidebarItem icon="icons/settingsIcon.png" expanded={sel == 'control'}>
						<div><SidebarButton id="control" on:click={select} icon="icons/pauseIcon.png" /></div>
						<div slot="subitems">
							<SidebarButton id="pause" on:click={select} icon="icons/pauseIcon.png" />
							<SidebarButton id="reset" on:click={select} icon="icons/resetIcon.png" />
							<SidebarButton id="power" on:click={select} icon="icons/powerIcon.png" />
						</div>
					</SidebarItem>
				</div>
				<div><SidebarButton id="settings" on:click={select} icon="icons/settingsIcon.png" /></div>
				<div><SidebarButton id="shell" on:click={select} icon="icons/retroShellIcon.png" /></div>
				<div><SidebarButton id="monitor" on:click={select} icon="icons/monitorIcon.png" /></div>
			</div>
		</div>
	{/if}
</div>
