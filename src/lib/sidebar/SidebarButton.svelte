<script lang="ts">
	import { createEventDispatcher } from 'svelte';
	export let item = { id: '', icon: '' };
	export let alt = 'Icon';
	export let enabled = true;
	export let highlighted = false;
	export let opacity = '';

	const dispatch = createEventDispatcher();

	$: bgcolor = enabled ? (highlighted ? 'bg-gray-100' : 'bg-gray-300') : 'bg-gray-500';
	$: hoverStyle = enabled ? 'hover:bg-gray-100 hover:scale-100' : '';

	function click(e: Event) {
		e.preventDefault();
		dispatch('select', { sender: e.target!.id });
	}
</script>

<div class="">
	<button
		type="button"
		class="p-1 w-10 rounded-lg text-white active:bg-white {bgcolor} {hoverStyle} {opacity}"
		id={item.id}
		on:click={click}
	>
		<img class="" id={item.id} src={item.icon} {alt} />
	</button>
</div>
