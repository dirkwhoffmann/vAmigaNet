<script lang="ts">
	import { createEventDispatcher } from 'svelte';
	import SidebarItem from '$lib/sidebar/SidebarItem.svelte';
	import SidebarButton from '$lib/sidebar/SidebarButton.svelte';
	import { Sidebar } from 'flowbite-svelte';
	import { fly, fade, slide, scale } from 'svelte/transition';

	let expanded = false;
	let sel = '';
	let duration = 200;

	const dispatch = createEventDispatcher();

	function expand() {
		sel = '';
		console.log('expand = ' + expanded);
		expanded = !expanded;
	}

	function select(e: Event) {
		e.preventDefault();
		sel = sel == e.target!.id ? '' : e.target!.id;
		console.log('sel = ' + sel);
		dispatch('select', { sender: sel });
	}
</script>

{#if expanded}
	<div
		class="absolute top-0 left-0 h-screen bg-gray-500/40 flex flex-col w-14"
		transition:fade={{ duration }}
	/>
{/if}
<div class="z-50 absolute top-0 left-0 p-2 flex flex-col space-y-1">
	<div><SidebarButton id="vamiga" on:click={expand} icon="icons/vamigaIcon.png" /></div>
	{#if expanded}
		<div class="z-50 relative space-y-1" transition:fade={{ duration }}>
			<SidebarItem icon="icons/settingsIcon.png" expanded={sel == 'control'}>
				<div class="border-0">
					<SidebarButton id="control" on:click={select} icon="icons/controlIcon.png" />
				</div>
				<div slot="subitems" class="border-0 flex space-x-1 mx-1">
					<div class="border-0">
						<SidebarButton id="pause" on:click={select} icon="icons/pauseIcon.png" />
					</div>
					<div class="border-0">
						<SidebarButton id="reset" on:click={select} icon="icons/resetIcon.png" />
					</div>
					<div class="border-0">
						<SidebarButton id="power" on:click={select} icon="icons/powerIcon.png" />
					</div>
				</div>
			</SidebarItem>
			<div><SidebarButton id="settings" on:click={select} icon="icons/settingsIcon.png" /></div>
			<div><SidebarButton id="shell" on:click={select} icon="icons/retroShellIcon.png" /></div>
			<div><SidebarButton id="monitor" on:click={select} icon="icons/monitorIcon.png" /></div>
            <SidebarItem icon="icons/settingsIcon.png" expanded={sel == 'layout'}>
				<div class="border-0">
					<SidebarButton id="layout" on:click={select} icon="icons/layoutIcon.png" />
				</div>
				<div slot="subitems" class="border-0 flex space-x-1 mx-1">
					<div class="border-0">
						<SidebarButton id="aspect" on:click={select} icon="icons/layoutAspectIcon.png" />
					</div>
					<div class="border-0">
						<SidebarButton id="fit" on:click={select} icon="icons/layoutFitIcon.png" />
					</div>
					<div class="border-0">
						<SidebarButton id="full" on:click={select} icon="icons/layoutFullIcon.png" />
					</div>
				</div>
			</SidebarItem>
		</div>
	{/if}
</div>
