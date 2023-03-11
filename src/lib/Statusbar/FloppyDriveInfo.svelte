<script lang="ts">
	import { darkTheme, invert } from '$lib/stores';
	import BarBox from './BarBox.svelte';
	import Menu from '$lib/Widgets/Menu.svelte';
	import { MenuItem } from '$lib/types';

	export let cyl = 0;
	export let disk = true;
	export let motor = false;
	export let writing = false;
	export let unsaved = false;
	export let wp = false;

	const gray = '';
	const green = 'bg-gradient-to-b from-green-700 to-green-500';
	const red = 'bg-gradient-to-b from-red-700 to-red-500';

	$: diskIcon = wp ? 'icons/disk-protected.png' : 'icons/disk.png';
	$: driveIcon = 'icons/floppy-drive.png';
	$: src = disk ? diskIcon : driveIcon;
	$: bg = motor ? (writing ? red : green) : gray;
	$: opc = unsaved ? 'opacity-40' : 'opacity-70';
	$: textcol = $darkTheme ? 'text-gray-300' : 'text-black';

	let tag = 0;
	let items = [new MenuItem('Insert', 0), new MenuItem('Eject',1)];

	$: update(disk);
	function update(hasDisk: boolean) {
		items[0].isEnabled = !hasDisk;
		items[0] = items[0];

		items[1].isEnabled = hasDisk;
		items[1]=items[1];
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