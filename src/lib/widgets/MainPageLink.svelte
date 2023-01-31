<script lang="ts">
	export let href: string;
</script>

<a class="flex flex-col items-center" {href}>
		<div class="border-none w-20 h-20 flex mt-4 justify-center text-gray-300">
			<slot name="icon" />
		</div>
		<div class="border-none flex mb-4 font-josefin text-xl text-gray-300">
			<slot name="description" />
		</div>
</a>
