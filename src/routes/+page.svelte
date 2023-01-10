<script lang="ts">
	import '../app.css';
	import { onMount } from 'svelte';
	import ButtonLink from '$lib/ButtonLink.svelte';
	import MainPageLink from '$lib/HeroLink.svelte';
	import GoDatabase from 'svelte-icons/go/GoDatabase.svelte';
	import Carousel2 from '$lib/Carousel2.svelte';
	import '@splidejs/svelte-splide/css';

	onMount(() => {
		console.log('onMount');
	});
</script>

<body class="h-screen bg-black text-white">
	<div class="bg-cover bg-transparent">
		<title> Welcome to vAmiga</title>

		<div class="flex flex-col h-screen">
			<div
				class="absolute flex flex-grow bg-splashscreen bg-cover h-screen w-screen brightness-[0.15]"
			/>
			<div
				class="relative bg-transparent flex flex-grow items-center justify-center border-none align-middle border-4 border-blue-500"
			>
				<div class="">
					<div class="flex justify-center text-5xl font-sofia-extra p-1 text-gray-100">vAmiga Online</div>
					<div class="flex justify-center text-3xl font-sofia-semi text-gray-400">
						Welcome to the world of friendly emulation
					</div>
					<div class="flex justify-center p-8">
						<ButtonLink
							href="/projects"
							color="var(--accent-text)"
							style="box-shadow: 0 3px 10px rgb(0 0 0 / 0.2);"
							title="Power On"
							>Power On
						</ButtonLink>
					</div>
				</div>
			</div>
			<div class="relative flex justify-center border-none align-middle bg-gray-500/50 border-4 border-red-500">
				<MainPageLink href="#showcases">
					<div slot="icon">
						<GoDatabase />
					</div>
					<div slot="description">Showcases</div>
				</MainPageLink>
			</div>
		</div>
		<div id ="showcases">
			<Carousel2 />
		</div>
	</div>
</body>
