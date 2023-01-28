<script lang="ts">
	import { createEventDispatcher } from 'svelte';

	export let disabled = false;
	export let bgcolor = 'bg-gray-300';
	export let style = '';
	export let bg = 'var(--accent)';
	export let hasIcon = false;
	export let cssVar = 'unset';
	export let active = false;
	export let title = '';
	export let icon = '';
	export let id = '';
</script>

<button
	type="button"
	class="flex-none mx-px w-8 rounded {bgcolor} p-1.5 text-white hover:bg-gray-100 hover:scale-100"
	class:hasIcon
	{id}
	{title}
	{disabled}
	on:click
	class:active
>
	<img class="" src="{icon}" alt="Power Icon" />
	<slot />
</button>
