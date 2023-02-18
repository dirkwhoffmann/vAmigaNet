// See https://kit.svelte.dev/docs/types#app
// for information about these interfaces
// and what to do when importing types

import Proxy from '$lib/Proxy.svelte';

declare namespace App {
	// interface Error {}
	// interface Locals {}
	// interface PageData {}
	// interface Platform {}
}

declare global {
	interface DataBaseItem {
		url: string;
		title: string;
		subtitle: string;
		description: string;
		adf: string[];
		memory: number[];
		aros: boolean;
		locked: boolean;
	}

	interface Window {
		Module: Proxy;
	}
}

export {};
