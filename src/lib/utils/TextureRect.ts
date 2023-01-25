import { AnimatedFloat } from "$lib/utils/AnimatedFloat";

export class TextureRect {

    x1 = new AnimatedFloat(0.1);
    y1 = new AnimatedFloat(0.1);
    x2 = new AnimatedFloat(0.9);
    y2 = new AnimatedFloat(0.9);

    animates(): boolean {
        return this.x1.animates() || this.y1.animates() || this.x2.animates() || this.y2.animates();
    }

    zoomIn(): void {
        /*
        let x1 = Int(4 * TPP * HBLANK_CNT)
        let x2 = Int(4 * TPP * HPOS_CNT_PAL)
        let y1 = Int(VBLANK_CNT)
        let y2 = pal ? Int(VPOS_CNT_PAL) : Int(VPOS_CNT_NTSC)
        return CGRect(x: x1, y: y1, width: x2 - x1, height: y2 - y1)
        */
        this.x1.set(0.1);
        this.y1.set(0.1);
        this.x2.set(0.9);
        this.y2.set(0.9);
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
