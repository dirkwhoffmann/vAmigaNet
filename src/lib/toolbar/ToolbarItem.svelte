<script lang="ts">
	export let disabled = false
	export let bgcolor = "bg-gray-300"
	export let style = ''
	export let bg = 'var(--accent)'	
	export let hasIcon = false
	export let cssVar = 'unset'
	export let active = false
	export let title = ""
	export let iconName = ""

	let count = 0;

	function click() {
		count += 1;
	}
</script>

<button
	type="button"
	class="flex-none mx-px w-8 rounded {bgcolor} p-1.5 text-white hover:shadow-lg hover:text-gray-200 hover:scale-110"
	class:hasIcon
	{title}
	{disabled}
	on:click={click}
	class:active>
	<img class="" src="{iconName}.png" alt="Power Icon"/>
	<slot />
</button>
