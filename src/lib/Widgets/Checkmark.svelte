<script lang="ts">
	export let enabled: boolean;
	export let visible: boolean;
</script>

{#if enabled}
	<div class="w-4">{@html visible ? '&#10003' : ''}</div>
{/if}
