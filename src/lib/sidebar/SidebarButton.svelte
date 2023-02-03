<script lang="ts">
	import { createEventDispatcher } from 'svelte';
	// export let disabled = false;
	// export let bgcolor = 'bg-gray-300';
	export let hasIcon = false;
	export let active = false;
	export let icon = '';
	export let id = '';
	export let alt = 'Icon';
	export let opacity = '';
	export let highlighted = false;

    const dispatch = createEventDispatcher();

	$: bgcolor = highlighted ? 'bg-gray-100' : 'bg-gray-300';

	function click(e: Event) {
		e.preventDefault();
		console.log('click!');
		dispatch('select', { sender: e.target!.id });
	}
</script>

<button
	type="button"
	class="border-0 p-1 w-10 rounded-lg {bgcolor} text-white hover:bg-gray-100 hover:scale-100 {opacity}"
	class:hasIcon
	{id}
	on:click={click}
	class:active
>
	<img class="" {id} src={icon} {alt} />
</button>
