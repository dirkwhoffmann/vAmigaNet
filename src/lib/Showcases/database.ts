import type { DataBaseItem } from '$lib/types';
import { WarpMode } from '$lib/types';
import { CRC32 } from '$lib/constants';

export const demos: DataBaseItem[] = [
	{
		url: 'batmanrises',
		title: 'Batman Rises',
		subtitle: 'The Batman Group',
		description:
			'Batman Rises is a demo released in December 2022 at Posadas Party Autumn Edition. It quickly caught public attention and is considered by many to be one of the best demos ever made for the Commodore Amiga.',
		adf: ['BatmanRises1.adf', 'BatmanRises2.adf'],
		memory: [1024, 512, 0],
		roms: [CRC32.Aros],
		warp: WarpMode.never
	},
	{
		url: 'stateart',
		title: 'State of the Art',
		subtitle: 'Spaceballs',
		description:
			'This demo has been released in December 1992. It ranked 1st in the Party 1992 Amiga Demo Competiton.',
		adf: ['StateArt.adf'],
		memory: [512, 512, 0],
		roms: [CRC32.Aros],
		warp: WarpMode.never
	},
	{
		url: 'rinkadink',
		title: 'Rink a Dink - Redux',
		subtitle: 'Lemon',
		description:
			'This demo has been released by Lemon at Revision 2013 and has become extremely popular over time. We have used it since the early days of vAmiga to extensively test the emulator.',
		adf: ['RinkADink.adf'],
		memory: [512, 512, 0],
		roms: [CRC32.Aros],
		warp: WarpMode.never
	},
	{
		url: 'desertdreams',
		title: 'Desert Dreams',
		subtitle: 'Kefrens',
		description:
			'This demo was released in April 1993. It ranked 1st in the Gathering 1993 Amiga Demo Competition.',
		adf: ['DesertDream1.adf', 'DesertDream2.adf'],
		memory: [1024, 512, 0],
		roms: [CRC32.Aros],
		warp: WarpMode.never
	},
	{
		url: 'inebriation',
		title: 'Absolute Inebriation',
		subtitle: 'Virtual Dreams & Fairlight',
		description:
			'This demo was released in December of 1992. It was the first production of Virtual Dreams, a Finnish-based Amiga demo group. The group reached their breakthrough in their time spent as the demo section of Fairlight.',
		adf: ['AbsoluteInebriation1.adf'],
		memory: [512, 512, 0],
		roms: [CRC32.Aros],
		warp: WarpMode.never
	},
	{
		url: 'eon',
		title: 'Eon',
		subtitle: 'The Black Lotus',
		description:
			'This demo is one of the best ever created for the Commodore Amiga. It shows impressively what the machine is capable of when its potential is exploited to the max.',
		adf: ['Eon1.adf'],
		memory: [512, 512, 0],
		roms: [CRC32.Kick12, CRC32.Kick13],
		warp: WarpMode.never
	},
	{
		url: '3ddemo',
		title: '3D Demo II',
		subtitle: 'Anarchy',
		description:
			'This demo was relased in December 1992. It ranked 2nd in the party 1992 Amiga demo competition.',
		adf: ['3Ddemo2.adf'],
		memory: [1024, 512, 0],
		roms: [CRC32.Kick12, CRC32.Kick13],
		warp: WarpMode.never
	},
	{
		url: 'sushiboyz',
		title: 'Sushi Boyz',
		subtitle: 'Ghostown',
		description:
			'This demo was relased in April 2015. It ranked 1st in the revision 2015 Amiga demo competition.',
		adf: ['Sushiboyz.adf'],
		memory: [1024, 512, 0],
		roms: [CRC32.Kick12, CRC32.Kick13],
		warp: WarpMode.never
	},
	{
		url: 'kyrios',
		title: 'Mental Scrollover',
		subtitle: 'Kyrios',
		description:
			'This demo was relased in August 1990. I have used it many times for testing vAmiga and have grown to love it over time.',
		adf: ['Kyrios.adf'],
		memory: [1024, 512, 0],
		roms: [CRC32.Kick12, CRC32.Kick13],
		warp: WarpMode.never
	}
];

export const games: DataBaseItem[] = [
	{
		url: 'traprunner',
		title: 'Trap Runner',
		subtitle: 'Night Owl Design',
		description:
			'Trap Runner is a classic platform game with few twists. Mind traps, obstacles and monsters. Collect items to increase your score, gain extra lives or fulfil one of the special missions. Two of four levels a world have a mission to accomplish. The game runs on any OCS/ECS Amiga, with 1MB RAM from Kickstart 1.2 onwards.',
		adf: ['TrapRunner.adf'],
		memory: [512, 512, 8192],
		roms: [CRC32.Aros],
		warp: WarpMode.never
	},
	{
		url: 'celtic',
		title: 'Celtic Heart',
		subtitle: 'Night Owl Design',
		description:
			'This game was written in the beginning of 2019, largely based on the Trap Runner engine. It has a medieval setting, where you are playing the celtic knight Eric on his task to save the kingdom from an evil force.',
		adf: ['CelticHeart.adf'],
		memory: [512, 512, 8192],
		roms: [CRC32.Aros],
		warp: WarpMode.never
	},
	{
		url: 'paccer',
		title: 'Paccer',
		subtitle: 'Dirk W. Hoffmann',
		description:
			'This game is a Pac-Man clone that was originally released on Fish Disk 223. I implemented this game myself many years ago on my Amiga 500 with the Aztec C compiler and DPaint. Unfortunately, I lost the source code when my parents cleaned up their attic. Luckily, the game survived on the Internet.',
		adf: ['Paccer.adf'],
		memory: [512, 512, 0],
		roms: [CRC32.Kick12, CRC32.Kick13],
		warp: WarpMode.never
	},
	{
		url: 'china',
		title: 'China Challenge II',
		subtitle: 'Dirk W. Hoffmann',
		description:
			'This game is a Mahjong clone which I implemented myself many years ago. The original version was released on Fish Disk 312. This version is a slightly improved sequel that was published on Fish Disk 444.',
		adf: ['ChinaChallengeII.adf'],
		memory: [512, 512, 0],
		roms: [CRC32.Kick12, CRC32.Kick13],
		warp: WarpMode.never
	},
	{
		url: 'defender',
		title: 'Defender of the Crown',
		subtitle: 'Cinemaware',
		description:
			"Defender of the Crown is a strategy computer game designed by Kellyn Beck. It was Cinemaware's first game, and was originally released for the Commodore Amiga in 1986, setting a new standard for graphic quality in home computer games.",
		adf: ['DefenderOfTheCrown1.adf', 'DefenderOfTheCrown2.adf'],
		memory: [512, 512, 0],
		roms: [CRC32.Kick12, CRC32.Kick13],
		warp: WarpMode.never
	}
];

export const tools: DataBaseItem[] = [
	{
		url: 'sysinfo',
		title: 'Sysinfo 4.4',
		subtitle: 'Nic Wilson, Tobias Geijersson',
		description:
			'Sysinfo is a shareware program written completely in Assembler for the Motorola 68k equipped Amiga computers to benchmark system performance. Sysinfo shows which version of system software is present in ROM, which hardware is present, and which operating mode the hardware uses.',
		adf: ['SysInfo.adf'],
		memory: [1024, 512, 0],
		roms: [CRC32.Aros],
		warp: WarpMode.never
	},
	{
		url: 'testkit',
		title: 'Amiga Test Kit',
		subtitle: 'Keir Fraser',
		description:
			'The Amiga Test Kit is a software-based solution for testing various components of a Commodore Amiga.',
		adf: ['AmigaTestKit.adf'],
		memory: [512, 512, 0],
		roms: [CRC32.Kick12, CRC32.Kick13],
		warp: WarpMode.never
	},
	{
		url: 'diagrom',
		title: 'Amiga DiagROM',
		subtitle: 'John Hertell',
		description:
			'The Amiga Diagnostic ROM is a hardware-based solution for testing Amiga hardware. On real machines, the Diagnostic ROM is used as a replacement for the Kickstart ROM on the motherboard. After powering on, the Amiga boots into a diagnostic menu. The ROM offers various test routines for checking different components.',
		adf: [],
		memory: [512, 512, 0],
		roms: [CRC32.DiagROM],
		warp: WarpMode.never
	}
];
