export class AnimatedFloat {
	current = 0.0;
	target = 0.0;
	deltaStep = 0.005;

	constructor(value = 0.0) {
		this.current = value;
		this.target = value;
	}

	animates() {
		return this.current != this.target;
	}

	clamped() {
		return this.current < 0.0 ? 0.0 : this.current > 1.0 ? 1.0 : this.current;
	}

	set(value: number, steps = 25) {
		this.target = value;
		this.deltaStep = Math.abs(this.target - this.current) / steps;
	}

	move() {
		if (this.current + this.deltaStep <= this.target) {
			this.current += this.deltaStep;
		} else if (this.current - this.deltaStep >= this.target) {
			this.current -= this.deltaStep;
		} else {
			this.current = this.target;
		}
	}
}
