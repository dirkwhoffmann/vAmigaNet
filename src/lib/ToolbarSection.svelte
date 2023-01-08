<script lang="ts">

import ToolbarItem from '$lib/ToolbarItem.svelte'
export var items: ToolbarItem[] = []; 

</script>

<div>
{#each items as item}
    <ToolbarItem />
{/each}
</div>
