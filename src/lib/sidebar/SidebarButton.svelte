<script lang="ts">
	import { createEventDispatcher } from 'svelte';
	export let item = { id: '', icon: '' };
	export let alt = 'Icon';
	export let enabled = true;
	export let opacity = '';
	export let toggle = false;
	export let active = false; 

	let state = false;
	const dispatch = createEventDispatcher<{select:{sender:string, state:boolean}}>();

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
		class="btn btn-primary p-1.5 w-12 {active ? 'btn-active' : ''}"
		id={item.id}
		on:click={click}
	>
		<img class="" id={item.id} src={item.icon} {alt} />
	</button>
</div>
