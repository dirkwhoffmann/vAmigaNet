//
// Enums
//

export enum Opt
{
	// General options
	WARP_MODE,
	THEME ,
	CANVAS_BORDER ,
	SHAKING
}

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

export interface ActionEvent {
	tag: number;
	value: number;
}

export interface KeySet {
	[key: string]: number;
}

export interface KeyMap {
	[key: string]: number;
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

//
// Experimental
//

export class MenuItem {
	title = '';
	tag = 0;
	isEnabled = true;
	isHidden = false;
	isSelected = false;
	isSeparator = false;

	constructor(title: string, tag: number) {
		this.title = title;
		this.tag = tag;
	}
}

export class MenuSeparator extends MenuItem {
	constructor() {
		super('', 0);
	}
}
