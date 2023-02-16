<script>
	import FriendAdder from './db/FriendAdder.svelte';
	import FriendList from './db/FriendList.svelte';
    import MyButton from './widgets/MyButton.svelte';

    let show = false; 

    function close() {
		console.log('close');
		show = false;
	}

</script>

{#if show}
<div class="absolute top-0 left-0 h-screen w-screen flex justify-center items-center">
	<div
		class="relative w-2/3 flex flex-col py-4 justify-center bg-gray-700 text-gray-300 border-2 border-gray-300 rounded-xl font-josefin"
	>
		<!-- Header -->
		<div class="w-full text-center text-3xl font-semibold text-white">Database experiments</div>
		<hr class="h-px my-4 bg-gray-200 border-0 dark:bg-gray-700" />

		<!-- Main -->
		<div>
			<FriendAdder />

			<h2>Result</h2>
			<FriendList />
		</div>

		<!-- Footer -->
		<hr class="h-px my-4 bg-gray-200 border-0 dark:bg-gray-700" />
		<div class="w-full flex justify-center">
			<MyButton on:click={close} label="Close" />
		</div>
	</div>
</div>
{/if}