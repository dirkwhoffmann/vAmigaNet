<script lang="ts">
	export let name = '';
	export let active = ''; 
</script>

<button on:click class="btn btn-ghost p-0 font-thin {active == name ? 'btn-active' : ''}"
	><div class="text-3xl">{name}</div></button
>
<!--
<button on:click class="p-0"
	><div class="text-3xl">{name}</div></button
>
-->