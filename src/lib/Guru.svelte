<script lang="ts">
	import { proxy, enums, what, errno } from '$lib/stores';
	$: initialized = $proxy != undefined;

	let active = false;
	let border = true;
	$: if ($errno && initialized && !active) {
		active = true;
		setInterval(() => {
			border = !border;
		}, 800);
	}
	$: borderColor = border ? 'border-red-600' : 'border-black';
</script>

{#if active}
	<div class="relative flex justify-center bg-black text-red-600 border-[10px] {borderColor}">
		<div
			class="h-24 w-full border-none flex flex-col justify-center text-lg font-azeret text-center"
		>
			<p class="p-1">
				Emulator failure. Uncaught exception {$errno} ({$enums.ErrorCodeKey($errno)})
			</p>
			<p class="p-1">{$what}</p>
		</div>
	</div>
{/if}
