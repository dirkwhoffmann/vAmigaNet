<svelte:options accessors={true}/>

<script lang="ts">

	export let title = '???';
	export let src = '';
	export let active = false;

</script>

<div class="">
	<div class="p-1">
		<img class="rounded border-solid border-gray-700 border-2" {src} alt={title} />
	</div>
	<div class="p-1">
		<!-- <div class="font-josefin text-xl bg-gray-700 rounded justify-center p-1"> -->
		<div class="font-josefin text-xl justify-center">
			{#if active}
			<div class="flex justify-center text-white">{title}</div>
			{:else}
			<div class="flex justify-center text-gray-400">{title}</div>
			{/if}
		</div>
	</div>
</div>
