<svelte:options accessors={true}/>

<script lang="ts">

	export let title = '???';
	export let src = '';
	export let active = false;

	$: textcol = active ? "text-white" : "text-gray-400";
	$: borderstyle = active ? "border-white border-2 brightness-125" : "border-gray-700 border-2 brightness-75";

</script>

<div class="">
	<div class="p-1">
		<img class="rounded border-solid {borderstyle}" {src} alt={title} />
	</div>
	<div class="p-1">
		<div class="font-josefin text-xl justify-center">
			<div class="flex justify-center {textcol}">{title}</div>
		</div>
	</div>
</div>
