<script lang="ts">
	export let title = '???';
	export let subtitle = '???';
	export let src = '';
</script>

<div class="">
	<div class="p-1">
		<img class="rounded border-solid border-gray-700 border-2" {src} alt={title} />
	</div>
	<div class="p-1">
		<!-- <div class="font-josefin text-xl bg-gray-700 rounded justify-center p-1"> -->
		<div class="font-josefin text-xl justify-center">
			<div class="flex justify-center text-gray-400">{title}</div>
			<!-- <div class="flex justify-center text-xs text-gray-400 -mt-1">{subtitle}</div> -->
		</div>
	</div>
</div>
