<script lang="ts">
	import { darkTheme } from '$lib/stores';

	export let src = '';

	function click(e: Event) {
		e.preventDefault();
	}
</script>

<div class="flex h-8">
	<div class="flex w-8 h-full justify-center items-center">
		<button type="button" on:click>
            <img
				class="border-0 p-1.5 h-full object-scale-down {$darkTheme ? 'invert' : ''} opacity-70"
				{src}
				alt="Status bar icon"
			/>
		</button>
		<slot />
	</div>
	<!-- <div class="h-full w-1 bg-black" />-->
</div>
