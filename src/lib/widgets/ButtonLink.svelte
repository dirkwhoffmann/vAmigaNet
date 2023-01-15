<script>
	export let disabled = false
    export let href = ''
	export let color = 'var(--accent-text)'
	export let style = ''
	export let bg = 'var(--accent)'	
	export let hasIcon = false
	export let title = ''
	export let cssVar = 'unset'
</script>

<button class="bg-blue-800 hover:bg-blue-700 text-white font-bold py-2 px-8 rounded">
    <slot />
</button>
