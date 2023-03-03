//
// Enums
//

export enum Opt
{

	//
	// General options
	//

	WARP_MODE,
	THEME ,
	CANVAS_BORDER ,
	SHAKING,

	//
	// Machine settings
	//

	CPU_REVISION,
	CPU_SPEED,
	AGNUS_REVISION,
	DENISE_REVISION,
	RTC_MODEL,
	CHIP_RAM,
	SLOW_RAM,
	FAST_RAM,
	BANK_MAP,
	INIT_PATTERN,
	UNMAPPED,
	SLOW_RAM_MIRROR,
	SLOW_RAM_DELAY,
	DF0,
	DF1,
	DF2,
	DF3,
	HD0,

	//
	// Audio settings
	//

	AUDVOL0,
	AUDVOL1,
	AUDVOL2,
	AUDVOL3,
	AUDVOLL,
	AUDVOLR,
	STEP_VOLUME,
	POLL_VOLUME,
	INSERT_VOLUME,
	EJECT_VOLUME,

	//
	// Video settings
	//

	RENDER_MODE,
	FLICKER_WEIGHT,
	PALETTE,
	BRIGHTNESS,
	CONTRAST,
	SATURATION
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
