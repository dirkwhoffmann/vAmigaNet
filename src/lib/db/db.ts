import Dexie, { type Table } from 'dexie';

export interface RomEntry {
	crc32: number;
	title: string;
    version: string;
    released: string;
    model: string;
    isAros: boolean;
    isDiag: boolean;
    isCommodore: boolean;
    isHyperion: boolean;
    isPatched: boolean;
    isUnknown: boolean;
    rom: Uint8Array | null;
    ext: Uint8Array | null;
    extStart: number;
}

export interface OptEntry {
    key: string;
    value: string;
}

export class MySubClassedDexie extends Dexie {
	roms!: Table<RomEntry>;
    opts!: Table<OptEntry>;

	constructor() {
		super('myDatabase');
		this.version(3).stores({
			roms: 'crc32, title',
            opts: 'key'
		});
	}
}

export const db = new MySubClassedDexie();
