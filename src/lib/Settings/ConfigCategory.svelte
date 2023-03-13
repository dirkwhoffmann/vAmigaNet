<script lang="ts">
    export let name = '';
    export let active = '';
    export let style = 'text-3xl';
</script>

<button on:click class="btn btn-ghost p-0 font-thin {active === name ? 'btn-active' : ''} {style}">
    {name}
</button>
