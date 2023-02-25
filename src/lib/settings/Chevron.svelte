<script lang="ts">
	import FaChevronDown from 'svelte-icons/fa/FaChevronDown.svelte';
</script>

<div class="flex w-full items-center justify-between">
	<div class="flex grow justify-center">
		<slot />
	</div>
	<div class="w-4 h-4">
		<FaChevronDown />
	</div>
</div>
