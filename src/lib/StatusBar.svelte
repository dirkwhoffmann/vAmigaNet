<script lang="ts">
	import { createEventDispatcher } from 'svelte';

	const height = 'h-8';
	const bg = 'bg-gradient-to-t from-gray-700 to-gray-600';
	const dispatch = createEventDispatcher();

	function click(e: Event) {
		e.preventDefault();
		dispatch('push', { sender: e.target!.id });
	}
</script>

<div class="z-50 relative flex {height}">
	<div class="w-16 mr-1 flex justify-center {bg}">
        
		<button type="button" class="flex w-16 justify-center" id="vamigaButton" on:click={click}>
			<img class="{height}" src="icons/vamigaIcon.png" alt="vAmiga Icon" />
		</button>
    
	</div>
	<div class="{bg} border-0 border-red-500 grow" />
</div>
