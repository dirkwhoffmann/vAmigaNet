import { AnimatedFloat } from '$lib/Utils/AnimatedFloat';
import { HBLANK_CNT, VBLANK_CNT, HPOS_CNT_PAL } from '$lib/constants';
import { VPOS_CNT_PAL, VPOS_CNT_NTSC } from '$lib/constants';
import { TPP, HPIXELS, VPIXELS } from '$lib/constants';

export interface Rectangle {
	x: number;
	y: number;
	w: number;
	h: number;
}

export class TextureRect {
	x1 = new AnimatedFloat(0.1);
	y1 = new AnimatedFloat(0.1);
	x2 = new AnimatedFloat(0.9);
	y2 = new AnimatedFloat(0.9);

	// Texture sizes
	texW = TPP * HPIXELS;
	texH = VPIXELS;

	// Normalizes into the range (0,0) - (1,1)
	normalize(rect: Rectangle): Rectangle {
		return {
			x: rect.x / this.texW,
			y: rect.y / this.texH,
			w: rect.w / this.texW,
			h: rect.h / this.texH
		};
	}

	// Returns the entire texture area (including HBLANK and VBLANK)
	entire(): Rectangle {
		return { x: 0, y: 0, w: this.texW, h: this.texH };
	}
	entireNormalized(): Rectangle {
		return this.normalize(this.entire());
	}

	// Returns the largest visibile texture area (excluding HBLANK and VBLANK)
	largestVisible(): Rectangle {
		const pal = true; // $agnus.isPAL

		const x1 = 4 * TPP * HBLANK_CNT;
		const x2 = 4 * TPP * HPOS_CNT_PAL;
		const y1 = VBLANK_CNT;
		const y2 = pal ? VPOS_CNT_PAL : VPOS_CNT_NTSC;

		return { x: x1, y: y1, w: x2 - x1, h: y2 - y1 };
	}
	largestVisibleNormalized(): Rectangle {
		return this.normalize(this.largestVisible());
	}

	// Returns the visible texture area based on the zoom and center parameters
	visible(hZoom: number, vZoom: number, hCenter: number, vCenter: number): Rectangle {
		// Determine zoom factors
		// var hZoom = renderer.config.hZoom
		// var vZoom = renderer.config.vZoom

		/*
            switch renderer.config.zoom {
    
            case 1: hZoom = 1.0; vZoom = 0.27; break;       // Narrow
            case 2: hZoom = 0.747; vZoom = 0.032; break;    // Wide
            case 3: hZoom = 0; vZoom = 0; break;            // Extreme
            default: break
            }
         */

		/*
		 *       aw <--------- maxWidth --------> dw
		 *    ah |-----|---------------------|-----|
		 *     ^ |     bw                   cw     |
		 *     | -  bh *<----- width  ------>*     -
		 *     | |     ^                     ^     |
		 *     | |     |                     |     |
		 *     | |   height                height  |
		 *     | |     |                     |     |
		 *     | |     v                     v     |
		 *     | -  ch *<----- width  ------>*     -
		 *     v |                                 |
		 *    dh |-----|---------------------|-----|
		 *
		 *      aw/ah - dw/dh = largest posible texture cutout
		 *      bw/bh - cw/ch = currently used texture cutout
		 */

		const largest = this.largestVisible();

		const hscale = 1.0 - 0.2 * hZoom;
		const vscale = 1.0 - 0.2 * vZoom;
		const width = hscale * largest.w;
		const height = vscale * largest.h;

		/* AUTO SHIFT NOT SUPPORTED YET
            if (renderer.parent.config.center == 1 {
                
                bw = x1 - 0.5 * (width - (x2 - x1))
                bw = max(bw, largest.minX)
                bw = min(bw, largest.maxX - width)
                debug(.events, "AutoShift x: \(bw)")
    
                bh = y1 - 0.5 * (height - (y2 - y1))
                bh = max(bh, largest.minY)
                bh = min(bh, largest.maxY - height)
                debug(.events, "AutoShift y: \(bh)")
    
            } else {
                
                bw = largest.minX + CGFloat(renderer.config.hCenter) * (largest.width - width)
                bh = largest.minY + CGFloat(renderer.config.vCenter) * (largest.height - height)
            }
            */
		const bw = largest.x + hCenter * (largest.w - width);
		const bh = largest.y + vCenter * (largest.h - height);

		return { x: bw, y: bh, w: width, h: height };
	}

	visibleNormalized(hZoom: number, vZoom: number, hCenter: number, vCenter: number): Rectangle {
		return this.normalize(this.visible(hZoom, vZoom, hCenter, vCenter));
	}

	animates(): boolean {
		return this.x1.animates() || this.y1.animates() || this.x2.animates() || this.y2.animates();
	}

	zoomIn(): void {
		/*
        const x1 = HBLANK_CNT;
        const y1 = VBLANK_CNT + 4;
        const x2 = HPOS_CNT_PAL;
        const y2 = VPOS_CNT_PAL; // pal ? VPOS_CNT_PAL : VPOS_CNT_NTSC
        this.x1.set(x1 / HPOS_CNT);
        this.y1.set(y1 / VPOS_CNT);
        this.x2.set(x2 / HPOS_CNT);
        this.y2.set(y2 / VPOS_CNT);
        */

		this.x1.set(0.188);
		this.y1.set(0.106);
		this.x2.set(0.188 + 0.733);
		this.y2.set(0.106 + 0.867);

		/*        
        this.x1.set(0.5);
        this.y1.set(0.0);
        this.x2.set(1.0);
        this.y2.set(1.0);
        */
	}

	zoomOut(): void {
		this.x1.set(0.0);
		this.y1.set(0.0);
		this.x2.set(1.0);
		this.y2.set(1.0);
	}

	move(): void {
		this.x1.move();
		this.y1.move();
		this.x2.move();
		this.y2.move();
	}
}
