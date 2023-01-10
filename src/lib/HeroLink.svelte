<script lang="ts">
    export let href:string
</script>

<a class="flex-col" {href}>
    <div class="flex h-16 mt-4 justify-center text-gray-300">
        <slot name="icon" />
    </div>
    <div class="flex mb-4 text-center text-xl text-gray-300">
        <slot name="description"/>
    </div>
</a>
