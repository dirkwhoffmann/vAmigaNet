//
// Enums
//

export enum Opt
{
	//
	// General options
	//

	WARP_MODE = 'WARP_MODE',
	THEME = 'THEME',
	CANVAS_BORDER = 'CANVAS_BORDER',
	SHAKING = 'SHAKING',

	//
	// Machine settings
	//

	CPU_REVISION = 'CPU_REVISION',
	CPU_SPEED = 'CPU_SPEED',
	AGNUS_REVISION = 'AGNUS_REVISION',
	DENISE_REVISION = 'DENISE_REVISION',
	RTC_MODEL = 'RTC_MODEL',
	CHIP_RAM = 'CHIP_RAM',
	SLOW_RAM = 'SLOW_RAM',
	FAST_RAM = 'FAST_RAM',
	BANK_MAP = 'BANK_MAP',
	INIT_PATTERN = 'INIT_PATTERN',
	UNMAPPED = 'UNMAPPED',
	SLOW_RAM_MIRROR = 'SLOW_RAM_MIRROR',
	SLOW_RAM_DELAY = 'SLOW_RAM_DELAY',
	DF0 = 'DF0',
	DF1 = 'DF1',
	DF2 = 'DF2',
	DF3 = 'DF3',

	//
	// Audio settings
	//

	AUDVOL0 = 'AUDVOL0',
	AUDVOL1 = 'AUDVOL1',
	AUDVOL2 = 'AUDVOL2',
	AUDVOL3 = 'AUDVOL3',
	AUDVOLL = 'AUDVOLL',
	AUDVOLR = 'AUDVOLR',
	STEP_VOLUME = 'STEP_VOLUME',
	POLL_VOLUME = 'POLL_VOLUME',
	INSERT_VOLUME = 'INSERT_VOLUME',
	EJECT_VOLUME = 'EJECT_VOLUME',

	//
	// Video settings
	//

	RENDER_MODE = 'RENDER_MODE',
	FLICKER_WEIGHT = 'FLICKER_WEIGHT',
	PALETTE = 'PALETTE',
	BRIGHTNESS = 'BRIGHTNESS',
	CONTRAST = 'CONTRAST',
	SATURATION = 'SATURATION'
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
