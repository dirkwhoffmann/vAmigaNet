<script lang="ts">

</script>

<button class="flex flex-col items-center" on:click>
	<div class="border-none w-16 h-16 flex mt-4 justify-center text-gray-300">
		<slot name="icon" />
	</div>
	<div class="border-none flex mb-4 font-josefin text-xl text-gray-300">
		<slot name="description" />
	</div>
</button>
