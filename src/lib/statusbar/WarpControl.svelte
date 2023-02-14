<script lang="ts">
	import StatusIcon from './StatusIcon.svelte';
	import { proxy, amiga, cpu, agnus, warp, warpMode } from '$lib/stores';

    function iconUrl(warpMode: number, warp: boolean) {
		switch (warpMode) {
			case 0: // Auto
				return warp ? 'icons/warp-auto-on.png' : 'icons/warp-auto-off.png';
			case 1: // Off
				return 'icons/warp-never.png';
			case 2: // On
				return 'icons/warp-always.png';
			default:
				return '';
		}
	}
    $: src = iconUrl($warpMode, $warp);

	function action(e: MouseEvent) {
		e.preventDefault();
        $warpMode = ($warpMode + 1) % 3; 
        $proxy.updateWarp();

	}
</script>

<StatusIcon {src} on:click={action}></StatusIcon>
