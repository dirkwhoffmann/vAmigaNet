<script lang="ts">
	import { createEventDispatcher } from 'svelte';
	export let item = { id: '', icon: '' };
	export let alt = 'Icon';
	export let enabled = true;
	export let opacity = '';
	export let toggle = false; 

	let state = false; 
	const dispatch = createEventDispatcher();

	$: bgcolor = enabled ? (state ? 'bg-blue-300' : 'bg-gray-300') : 'bg-gray-500';
	$: hoverStyle = enabled ? 'hover:bg-blue-300 hover:scale-100' : '';

	function click(e: Event) {
		e.preventDefault();
		state = toggle ? !state : true; 
		console.log("toggle = ", toggle);
		dispatch('select', { sender: e.target!.id, state: state });
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
