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

<div class="relative flex {height}">
	<div class="flex w-14 {bg} justify-center">
		<button type="button" class="" id="vamigaButton" on:click={click}>
			<img class="{height} border-0" src="icons/vamigaIcon.png" alt="vAmiga Icon" />
		</button>
	</div>
	<div class="ml-0.5 {bg} grow" />
</div>
