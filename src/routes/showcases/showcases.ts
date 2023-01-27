import { get } from 'svelte/store';
import { proxy, amiga } from '$lib/stores';
import type Proxy from '$lib/Proxy.svelte';

const myAmiga: any = get(amiga);
const myProxy: Proxy = get(proxy);

export class Showcase {

	// Title and subtitle
	title = "";
	subtitle = "";

	// Textual description
	description = "";

	// URL pointing to the artwork
	url = "";

	// Indicates if this showcase can run
	isLocked(): boolean {
		return false;
	}

	// Prepares the emulator to run this showcase
	setupEmulator(): void {
		console.log('setupEmulator()');
	}
}

export class RinkADink extends Showcase {
	setupEmulator(): void {
		super.setupEmulator();
		console.log('Setting up Rink a Dink...');
        myAmiga.powerOff();   
        myProxy.startUp();
        //         amiga.configure()
	}   
}
