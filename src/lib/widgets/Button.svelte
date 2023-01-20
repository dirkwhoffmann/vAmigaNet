<script>
	export let disabled = false;
	export let label = '';
	export let img = '';
	export let pad = 'm-4';
	export let width = 'w-max';
</script>

<button class="items-center" on:click>
	<div class="bg-blue-300 hover:bg-blue-500 text-gray-800 rounded-md flex items-center h-12 w-max">
		{#if $$slots.default}
			<div class="justify-center h-full aspect-square p-1.5 {label != '' ? '-mr-2' : ''}">
				<slot />
			</div>
		{/if}
		{#if label != ''}
			<div class="font-sofia-semi text-xl {pad} {width}">
				{label}
			</div>
		{/if}
		{#if img != ''}
			<img class="flex h-full p-1.5" src={img} alt="Icon">
		{/if}
	</div>
</button>
