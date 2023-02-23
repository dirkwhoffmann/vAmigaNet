<script lang="ts">
	export let bg = '';
</script>

<div class="flex h-8">
	<div class="flex w-16 h-full justify-center items-center {bg}">
		<slot />
	</div>
	<div class="h-full w-1 bg-black" />
</div>
