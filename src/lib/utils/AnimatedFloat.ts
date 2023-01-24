export class AnimatedFloat {

    current = 0.0;
    target = 0.0;
    deltaStep = 0.0;

    constructor(value = 0.0) {
        this.current = value;
    }

    set(value = 0.0, deltaStep = 0.05) {

        this.target = value;
        this.deltaStep = deltaStep;
    }

    sayHi() {
        console.log("current = " + this.current);
    }

}
