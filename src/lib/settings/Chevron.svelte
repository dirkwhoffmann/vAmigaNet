<script lang="ts">
	import FaChevronDown from 'svelte-icons/fa/FaChevronDown.svelte';
</script>

<div class="flex w-full items-center justify-between">
	<div class="flex grow border-0 justify-center">
		<slot />
	</div>
	<div class="h-4">
		<FaChevronDown />
	</div>
</div>
