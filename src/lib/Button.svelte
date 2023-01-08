<script lang="ts">
	export let disabled = false
	export let color = 'var(--accent-text)'
	export let style = ''
	export let bg = 'var(--accent)'	
	export let hasIcon = false
	export let cssVar = 'unset'
	export let active = false
	export let title = ""
</script>

<button
	type="button"
	class="btn"
	class:hasIcon
	{title}
	{disabled}
	on:click
	class:active
>
	<slot />
</button>
