<script lang="ts">
	import { darkTheme } from '$lib/stores';

	export let style = 'h-full object-scale-down';
    export let src = '';
    export let alt = 'Icon';

	$: invert = $darkTheme ? 'invert' : '';
</script>

<img class="{style} {invert}" {src} {alt} />
