import { AnimatedFloat } from "$lib/utils/AnimatedFloat";
import { HBLANK_CNT, VBLANK_CNT, HPOS_CNT_PAL, VPOS_CNT_PAL, VPOS_CNT_NTSC, TPP } from '$lib/constants';
import { HPOS_CNT, VPOS_CNT } from '$lib/constants';

export class TextureRect {

    x1 = new AnimatedFloat(0.1);
    y1 = new AnimatedFloat(0.1);
    x2 = new AnimatedFloat(0.9);
    y2 = new AnimatedFloat(0.9);

    animates(): boolean {
        return this.x1.animates() || this.y1.animates() || this.x2.animates() || this.y2.animates();
    }

    zoomIn(): void {
        console.log("zoomIn");
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
       
        this.x1.set(0.18894736623554872);
        this.y1.set(0.10633885841210426);
        this.x2.set(0.18894736623554872 + 0.7333333442608515);
        this.y2.set(0.10633885841210426 + 0.8674185119878751);
        /*
        this.x1.set(0.5);
        this.y1.set(0.0);
        this.x2.set(1.0);
        this.y2.set(0.5);
        */

        console.log("New rect: " + this.x1.target + ", " + this.y1.target + ", " + this.x2.target + ", " + this.y2.target);
    }

    zoomOut(): void {
        console.log("zoomOut");
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
