<script lang="ts">

</script>

<div class="border-0 w-28 my-4 flex flex-col items-center justify-center">
<button class="flex flex-col items-center w-16 h-16 justify-center text-gray-300" on:click>
		<slot name="icon" />
</button>
	<div class="border-none flex font-josefin text-xl text-gray-300">
		<slot name="description" />
	</div>
</div>
