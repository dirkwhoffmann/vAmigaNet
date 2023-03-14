<script lang="ts">
    export let shadow = true;
</script>

<div class="pointer-events-none">
    {#if shadow}
        <div class="z-50 absolute bottom-0 left-0 w-full h-32 bg-gradient-to-b from-transparent to-black"></div>
    {/if}
    <div class="z-50 absolute bottom-0 right-0 p-4">
        <div class="z-50 flex justify-end">
            <button class=""><img class="h-11" src="va-icon.png" alt="vAmiga Icon"/></button>
            <div class="font-sofia-extra text-3xl px-3 pt-1 text-white">vAmiga.net</div>
        </div>
    </div>
</div>