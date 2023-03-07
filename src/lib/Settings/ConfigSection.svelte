<script lang="ts">
	export let name = '';
</script>

<div class="px-0 py-0.5">
	<div class="w-full flex">
		<div class="text-xl text-base-content">{name}</div>
	</div>
	<slot />
</div>
