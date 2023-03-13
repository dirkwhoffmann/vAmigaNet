<script lang="ts">
    import { MenuItem } from '$lib/types';
    import { darkTheme, invert, poweredOn } from '$lib/stores';
    import BarBox from './BarBox.svelte';
    import Menu from '$lib/Widgets/Menu.svelte';

    export let cyl = 0;
    export let reading = false;
    export let writing = false;
    export let unsaved = false;

    const gray = '';
    const green = 'bg-gradient-to-b from-green-700 to-green-500';
    const red = 'bg-gradient-to-b from-red-700 to-red-500';

    $: driveIcon = 'icons/hard-drive.png';
    $: src = driveIcon;
    $: bg = reading ? green : writing ? red : gray;
    $: opc = unsaved ? 'opacity-40' : 'opacity-70';
    $: textcol = $darkTheme ? 'text-gray-300' : 'text-black';

    let tag = 0;
    let items = [new MenuItem('Attach', 0)];

    $: update($poweredOn);
    function update(power: boolean) {

        items[0].isEnabled = !power;
        items[0] = items[0];
    }
</script>

<Menu {items} {tag} listStyle="menu menu-compact rounded p-0 text-sm w-32" on:select>
    <BarBox {bg}>
        <img
                class="border-0 pr-1 py-1.5 h-full object-scale-down {$invert} {opc}"
                {src}
                alt="Floppy icon"
        />
        <div class="border-0 w-6 items-center pl-1 text-left leading-none text-sm {textcol}">
            {cyl}
        </div>
    </BarBox>
</Menu>