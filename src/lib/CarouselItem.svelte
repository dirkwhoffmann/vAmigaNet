<script lang="ts">
	export let title = '???';
	export let src = '';
	export let alt = 'Item';
</script>

<div class="border-none border-4 rounded-lg border-gray-600">
	<div class="bg-black">
		<img class="object-fill" {src} {alt} />
		<div>
			<div class="absolute top-10 left-10">
				<div class="font-sofia-extra text-7xl">Defender of the Crown</div>
				<div class="font-sofia-semi text-2xl pb-10">Cinemaware (1986)</div>
				<div class="flex font-josefin text-lg w-1/3 pb-10">
					Defender of the Crown is a strategy computer game designed by Kellyn Beck. It was
					Cinemaware's first game, and was originally released for the Commodore Amiga in 1986,
					setting a new standard for graphic quality in home computer games.
				</div>
				<button class="bg-blue-800 hover:bg-blue-700 text-white font-bold py-2 px-8 rounded"
					>Play</button>
			</div>
		</div>
	</div>
</div>
