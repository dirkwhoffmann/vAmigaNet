<script lang="ts">
	import { darkTheme } from '$lib/stores';

	export let src = '';

	function click(e: Event) {
		e.preventDefault();
	}
</script>

<button type="button" on:click>
	<img
		class="border-0 p-1.5 w-8 h-8 object-scale-down {$darkTheme ? 'invert' : ''} opacity-70"
		{src}
		alt="Status bar icon"
	/>
</button>
<slot />

<!--
<div class="flex h-8">
	<div class="flex w-8 h-full justify-center items-center">
		<button type="button" on:click>
            <img
				class="border-0 p-1.5 w-full h-full object-scale-down {$darkTheme ? 'invert' : ''} opacity-70"
				{src}
				alt="Status bar icon"
			/>
		</button>
		<slot />
	</div>
</div>
-->
