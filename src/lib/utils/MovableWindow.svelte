<script lang="ts">
    import Movable from '$lib/Utils/Movable.svelte';
    export let hide=false;
    export let x=100;
    export let y=250;
</script>


<Movable free_positioning={true} css_class="z-50 rounded-md flex flex-col w-96 {hide?'hidden':''}"  {x} {y}>
    <div slot="title" class="bg-blue-600 flex justify-between p-3" style="border-top-left-radius: 15px;border-top-right-radius: 15px;">
        <div class="text-lg"><slot name="title"></slot></div>
        <button class="px-2" on:click={()=>hide=true}>&#120;</button>
    </div>
    <div slot="body" class="bg-gray-300 text-slate-700 h-42 p-4" style="border-bottom-left-radius: 15px;border-bottom-right-radius: 15px;">
        <div class="flex flex-col justify-between">
            <slot name="body"></slot>
            <div class="flex justify-end"><slot name="buttons"></slot></div>
        </div>
    </div>
</Movable>