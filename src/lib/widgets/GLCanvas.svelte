<svelte:options accessors={true} />

<script lang="ts">
	import { vAmiga, amiga, denise } from '$lib/stores';
	import { VPIXELS, HPIXELS, TPP } from '$lib/constants';
	import { onMount } from 'svelte';

	// Reference to the canvas element
	let canvas: HTMLCanvasElement;

	// Texture sizes
	const lfTextureSize = { width: HPIXELS * TPP, height: VPIXELS };
	const sfTextureSize = { width: HPIXELS * TPP, height: VPIXELS };
	const mergeTextureSize = { width: 2 * HPIXELS, height: 2 * VPIXELS };

	// Buffers
	let vertexCoordBuffer: WebGLBuffer;
	let textureCoordBuffer: WebGLBuffer;

	// Shaders
	let shaderProgram: WebGLProgram;

	// Textures
	let lfTexture: WebGLTexture;
	let sfTexture: WebGLTexture;

	// Uniforms
	let lweight: WebGLUniformLocation;
	let sweight: WebGLUniformLocation;
	let sfSampler: WebGLUniformLocation;
	let lfSampler: WebGLUniformLocation;

	const vsSource = `
    	attribute vec4 aVertexPosition;
    	attribute vec2 aTextureCoord;
    	varying highp vec2 vTextureCoord;
    	void main() {
    		gl_Position = aVertexPosition;
    	vTextureCoord = aTextureCoord;
    	}
   	`;

	const fsSource = `		
		precision mediump float;
    
		varying highp vec2 vTextureCoord;
    	uniform sampler2D u_lfSampler;
    	uniform sampler2D u_sfSampler;
		uniform float u_lweight;
		uniform float u_sweight;
    	void main() {

			float y = floor(gl_FragCoord.y);
			float w;
			vec4 texel;

			if (mod(y, 2.0) == 0.0) {
				w = u_sweight;
				texel = texture2D(u_sfSampler, vTextureCoord);
			} else {
				w = u_lweight;
				texel = texture2D(u_lfSampler, vTextureCoord);
			}
    		gl_FragColor = texel * vec4(w, w, w, 1.0);    
    	}
   `;

	let gl: WebGL2RenderingContext;

	function initWebGL() {
		// General WebGL options
		const options = {
			alpha: true,
			antialias: true,
			depth: false,
			preserveDrawingBuffer: false,
			stencil: false
		};

		// Only proceed if WebGL2 is supported
		if (!(canvas.getContext('webgl2', options) instanceof WebGL2RenderingContext)) {
			throw new Error('vAmiga Online needs WebGL2 to run.');
		}

		// Store the context for further use
		gl = canvas.getContext('webgl2', options) as WebGL2RenderingContext;
		gl.disable(gl.BLEND);
		gl.disable(gl.DEPTH_TEST);
		gl.disable(gl.SCISSOR_TEST);
		gl.disable(gl.STENCIL_TEST);

		// Start with a clean buffer
		gl.clearColor(0.0, 0.0, 0.0, 1.0);
		gl.clear(gl.COLOR_BUFFER_BIT);

		// Create the shader program
		shaderProgram = compileProgram(vsSource, fsSource);

		// Setup the vertex coordinate buffer
		const vCoords = new Float32Array([1.0, 1.0, -1.0, 1.0, 1.0, -1.0, -1.0, -1.0]);
		vertexCoordBuffer = createBuffer(vCoords);
		setAttribute(shaderProgram, 'aVertexPosition');

		// Setup the texture coordinate buffer
		const tCoords = new Float32Array([1.0, 1.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0]);
		textureCoordBuffer = createBuffer(tCoords);
		setAttribute(shaderProgram, 'aTextureCoord');

		// Flip y axis to get the image right
		gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, true);

		// Select the active shader program
		gl.useProgram(shaderProgram);
		lweight = gl.getUniformLocation(shaderProgram, 'u_lweight');
		sweight = gl.getUniformLocation(shaderProgram, 'u_sweight');

		// Create textures
		lfTexture = createTexture();
		sfTexture = createTexture();

		gl.activeTexture(gl.TEXTURE0);
		gl.bindTexture(gl.TEXTURE_2D, lfTexture);
		lfSampler = gl.getUniformLocation(shaderProgram, 'u_lfSampler')!;
		gl.uniform1i(lfSampler, 0);
		gl.uniform1f(lweight, 1.0);

		gl.activeTexture(gl.TEXTURE1);
		gl.bindTexture(gl.TEXTURE_2D, sfTexture);
		sfSampler = gl.getUniformLocation(shaderProgram, 'u_sfSampler')!;
		gl.uniform1i(sfSampler, 1);
		gl.uniform1f(sweight, 1.0);
	}

	function compileProgram(vSource: string, fSource: string) {
		console.log('compile()');

		const vert = compileShader(gl.VERTEX_SHADER, vSource);
		const frag = compileShader(gl.FRAGMENT_SHADER, fSource);
		const prog = gl.createProgram()!;

		gl.attachShader(prog, vert);
		gl.attachShader(prog, frag);
		gl.linkProgram(prog);

		if (!gl.getProgramParameter(prog, gl.LINK_STATUS)) {
			throw new Error(`Shader link error: ${gl.getProgramInfoLog(prog)}`);
		}
		return prog;
	}

	function compileShader(type: number, source: string) {
		console.log('compileShader()');

		const shader = gl.createShader(type)!;
		gl.shaderSource(shader, source);
		gl.compileShader(shader);

		if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
			throw new Error(`Shader compile error: ${gl.getShaderInfoLog(shader)}`);
		}
		return shader;
	}

	function createTexture() {
		console.log('createTexture()');

		const w = HPIXELS;
		const h = VPIXELS;
		let pixels = new Uint8Array(HPIXELS * VPIXELS * 4);
		for (let y = 0; y < h; y++) {
			for (let x = 0; x < w; x++) {
				if (((y >> 3) & 1) == ((x >> 3) & 1)) {
					pixels[4 * (y * w + x) + 0] = 255;
					pixels[4 * (y * w + x) + 1] = 0;
					pixels[4 * (y * w + x) + 2] = 0;
					pixels[4 * (y * w + x) + 3] = 255;
				} else {
					pixels[4 * (y * w + x) + 0] = 255;
					pixels[4 * (y * w + x) + 1] = 255;
					pixels[4 * (y * w + x) + 2] = 0;
					pixels[4 * (y * w + x) + 3] = 255;
				}
			}
		}

		const texture = gl.createTexture()!;
		gl.bindTexture(gl.TEXTURE_2D, texture);
		gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.CLAMP_TO_EDGE);
		gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, gl.CLAMP_TO_EDGE);
		gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);
		gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);
		gl.texImage2D(
			gl.TEXTURE_2D,
			0,
			gl.RGBA,
			HPIXELS,
			VPIXELS,
			0,
			gl.RGBA,
			gl.UNSIGNED_BYTE,
			pixels
		);

		return texture;
	}

	function createBuffer(values: Float32Array) {
		console.log('createBuffer()');

		const buffer = gl.createBuffer()!;
		gl.bindBuffer(gl.ARRAY_BUFFER, buffer);
		gl.bufferData(gl.ARRAY_BUFFER, values, gl.STATIC_DRAW);

		return buffer;
	}

	function setAttribute(program: WebGLProgram, attribute: string) {
		const a = gl.getAttribLocation(program, attribute);
		gl.enableVertexAttribArray(a);
		gl.vertexAttribPointer(a, 2, gl.FLOAT, false, 0, 0);
	}

	function drawAnimationFrame(now: DOMHighResTimeStamp) {
		if ($amiga != undefined) {
			draw();
		}
		window.requestAnimationFrame(drawAnimationFrame);
	}

	let weight = 0.75;

	function draw() {
		if ($amiga != undefined) {
			updateTexture();
			gl.useProgram(shaderProgram);
			gl.uniform1f(lweight, 1.0 - weight);
			weight = 0.75 - weight;
			gl.uniform1f(sweight, 1.0 - weight);

			gl.drawArrays(gl.TRIANGLE_STRIP, 0, 4);
		} else {
			console.log('Skipping draw: Store not yet initialized');
		}
	}

	function updateTexture() {
		const w = HPIXELS;
		const h = VPIXELS;

		if ($amiga.poweredOff()) {
			const noise = $denise.noise();
			const tex = new Uint8Array($vAmiga.HEAPU8.buffer, noise, w * h * 4);
			gl.activeTexture(gl.TEXTURE0);
			gl.texSubImage2D(gl.TEXTURE_2D, 0, 0, 0, w, h, gl.RGBA, gl.UNSIGNED_BYTE, tex);
			gl.activeTexture(gl.TEXTURE1);
			gl.texSubImage2D(gl.TEXTURE_2D, 0, 0, 0, w, h, gl.RGBA, gl.UNSIGNED_BYTE, tex);
		} else {
			const frame = $denise.getEmulatorTexture();
			const tex = new Uint8Array($vAmiga.HEAPU8.buffer, frame.data, w * h * 4);
			gl.activeTexture(gl.TEXTURE0);
			gl.texSubImage2D(gl.TEXTURE_2D, 0, 0, 0, w, h, gl.RGBA, gl.UNSIGNED_BYTE, tex);
			gl.activeTexture(gl.TEXTURE1);
			gl.texSubImage2D(gl.TEXTURE_2D, 0, 0, 0, w, h, gl.RGBA, gl.UNSIGNED_BYTE, tex);

		}
	}

	onMount(() => {
		console.log('GLCanvas: onMount()');
		initWebGL();
		window.requestAnimationFrame(drawAnimationFrame);
	});
</script>

<canvas bind:this={canvas} class="w-full h-full" tabindex="-1" />
