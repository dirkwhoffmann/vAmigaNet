import Dexie, { type Table } from 'dexie';

export interface Friend {
	id?: number;
	name: string;
	age: number;
}

export interface RomEntry {
	id?: number;
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
    extStart: number;
}

export class MySubClassedDexie extends Dexie {
	friends!: Table<Friend>;
	roms!: Table<RomEntry>;

	constructor() {
		super('myDatabase');
		this.version(3).stores({
			friends: '++id, name, age', // Primary key and indexed props
			roms: '++id, title, crc32'
		});
	}
}

export const db = new MySubClassedDexie();
