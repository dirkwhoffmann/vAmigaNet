export class AnimatedFloat {

    current = 0.0;
    target = 0.0;
    deltaStep = 0.0;

    constructor(value = 0.0) {
        this.current = value;
    }

    animates() {
        return this.current != this.target;
    }

    clamped() {
        return this.current < 0.0 ? 0.0 : this.current > 1.0 ? 1.0 : this.current;
    }

    set(value: number, deltaStep = 0.05) {
        this.target = value;
        this.deltaStep = deltaStep;
    }

    move() {
        if (Math.abs(this.current - this.target) < Math.abs(this.deltaStep)) {
            this.current = this.target;
        } else {
            this.current += this.deltaStep;
        }
    }

    sayHi() {
        console.log("current = " + this.current);
    }
}
