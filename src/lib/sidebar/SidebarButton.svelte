<script lang="ts">
	import { createEventDispatcher } from 'svelte';
	export let item = { id: '', icon: '' };
	export let alt = 'Icon';
	export let enabled = true;
	export let opacity = '';
	export let toggle = false;
	export let highlighted = false; 

	let state = false;
	const dispatch = createEventDispatcher<{select:{sender:string, state:boolean}}>();

	$: bgcolor = enabled ? (highlighted ? 'bg-blue-300' : 'bg-gray-500') : 'bg-gray-500';
	$: activeStyle = 'active:bg-blue-300';
	$: hoverStyle = enabled ? 'hover:{blue} hover:scale-100' : '';

	function click(e: Event) {
		e.preventDefault();
		state = toggle ? !state : true; 
		console.log("toggle = ", toggle);
		dispatch('select', { sender: (e.target as HTMLElement).id, state: state });
	}
</script>

<div class="">
	<button
		type="button"
		class="p-1 w-10 rounded-lg text-white {activeStyle} {bgcolor} {hoverStyle} {opacity}"
		id={item.id}
		on:click={click}
	>
		<img class="" id={item.id} src={item.icon} {alt} />
	</button>
</div>
