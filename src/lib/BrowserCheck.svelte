<script lang="ts">
	import MyButton from '$lib/widgets/MyButton.svelte';

	let isSafari = window.safari !== undefined;
	let showWarning = false; // isSafari

	function close() {
		console.log('close');
		isSafari = false;
	}
</script>

{#if showWarning}
	<div class="absolute top-0 left-0 h-screen w-screen flex justify-center items-center">
		<div
			class="relative w-2/3 flex flex-col py-4 justify-center bg-gray-700 text-gray-300 border-2 border-gray-300 rounded-xl font-josefin"
		>
			<!-- Header -->
			<div class="w-full text-center text-3xl font-semibold text-white">Incompatible Browser</div>
			<hr class="h-px my-4 bg-gray-200 border-0 dark:bg-gray-700" />

			<!-- Main -->
			<div
				class="grow overflow-auto px-4 border-blue-500 text-center flex flex-col items-center justify-center"
			>
				<div>
					<p>
						vAmiga Online makes use of web audio features that are not fully supported by your
						browser. Please revisit this site in Chrome or Firefox.
					</p>
					<div class="w-full flex justify-center p-4">
						<img class="p-1 h-32" src={'img/chrome-logo.png'} alt="Chrome logo" />
						<img class="p-1 h-32" src={'img/firefox-logo.png'} alt="Firefox logo" />
					</div>
				</div>
			</div>

			<!-- Footer -->
			<hr class="h-px my-4 bg-gray-200 border-0 dark:bg-gray-700" />
			<div class="w-full flex justify-center">
				<MyButton on:click={close} label="Close" />
			</div>
		</div>
	</div>
{/if}
