<script lang="ts">
	import { createEventDispatcher } from 'svelte';
	import { darkTheme } from '$lib/stores';
	export let item = { id: '', icon: '' };
	export let alt = 'Icon';
	export let toggle = false;
	export let active = false;

	let state = false;
	const dispatch = createEventDispatcher<{ select: { sender: string; state: boolean } }>();

	function click(e: Event) {
		e.preventDefault();
		state = toggle ? !state : true;
		console.log('toggle = ', toggle);
		dispatch('select', { sender: (e.target as HTMLElement).id, state: state });
	}
</script>

<button
	type="button"
	class="btn btn-primary btn-square p-1.5 {active ? 'btn-active' : ''}"
	on:click={click}
>
	<img class="{$darkTheme ? 'invert' : ''}" id={item.id} src={item.icon} {alt} />
</button>
