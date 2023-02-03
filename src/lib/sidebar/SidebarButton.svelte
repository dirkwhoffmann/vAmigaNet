<script lang="ts">
	export let disabled = false;
	export let bgcolor = 'bg-gray-300';
	export let hasIcon = false;
	export let active = false;
	export let title = '';
	export let icon = '';
	export let id = '';
	export let alt = 'Icon';
</script>

<button
	type="button"
	class="p-2 w-10 rounded-lg {bgcolor} p-1 text-white hover:bg-gray-100 hover:scale-100"
	class:hasIcon
	{id}
	{title}
	{disabled}
	on:click
	class:active
>
	<img class="" {id} src={icon} {alt} />
	<slot />
</button>
