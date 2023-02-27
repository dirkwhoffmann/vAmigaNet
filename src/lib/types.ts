// 
// Enums
// 

export enum InputDevice {
	none,
	mouse,
	keyset1,
	keyset2
}
export enum Layer {
	none,
	dropzone,
	kickstart,
	settings,
	shell,
	showcases
}
export enum RenderMode {
	smooth,
	pixelated
}
export enum Theme {
	default,
	light,
	dark,
	coffee,
	cupcake,
	forest,
	aqua,
	garden,
	pastel
}
export enum WarpMode {
	auto,
	never,
	always
}

//
// Interfaces
//

export interface KeySet {
    [key: string] : number
}

export interface KeyMap {
    [key: string] : number
}

export interface DataBaseItem {
    url: string;
    title: string;
    subtitle: string;
    description: string;
    adf: string[];
    memory: number[];
    roms: number[];
    warp: WarpMode;
}