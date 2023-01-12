<script lang="ts">
	export let title = '???';
	export let src = '';
</script>

<div class="">
	<div class="p-1"><img class="rounded border-solid border-gray-700 border-2" {src} alt={title} /></div>
	<div class="p-1"><div class="bg-gray-700 rounded flex justify-center p-1">{title}</div></div>
</div>
