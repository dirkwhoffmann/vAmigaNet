<svelte:options accessors={true} />

<script lang="ts">
	import { vAmiga, amiga, denise } from '$lib/stores';
	import { VPIXELS, HPIXELS, TPP } from '$lib/constants';
	import { onMount } from 'svelte';

	// Reference to the canvas element
	let canvas: HTMLCanvasElement;

	// The rendering context of the canvas
	let gl: WebGL2RenderingContext;

	// Indicates whether the recently drawn frames were long or short frames
	let currLOF = true;
	let prevLOF = true;

	// Frame counter
	let frameNr = 0;

	// Variable used to emulate interlace flickering
	let flickerCnt = 0;

	// Textures
	let lfTexture: WebGLTexture;
	let sfTexture: WebGLTexture;
	let mergeTexture: WebGLTexture;

	// The merge shader for rendering the merge texture
	let mergeShaderProgram: WebGLProgram;
	let lfWeight: WebGLUniformLocation;
	let sfWeight: WebGLUniformLocation;
	let sfSampler: WebGLUniformLocation;
	let lfSampler: WebGLUniformLocation;

	// The main shader for drawing the final texture on the canvas 
	let mainShaderProgram: WebGLProgram;
	let sampler: WebGLUniformLocation;

	const vertexShaderSource = `
    	attribute vec4 aVertexPosition;
    	attribute vec2 aTextureCoord;
    	varying highp vec2 vTextureCoord;
    	void main() {
    		gl_Position = aVertexPosition;
    		vTextureCoord = aTextureCoord;
    	}
   	`;

	const mergeShaderSource = `		
		precision mediump float;

		varying highp vec2 vTextureCoord;
	   	uniform sampler2D u_lfSampler;
	   	uniform sampler2D u_sfSampler;
		uniform float u_lweight;
		uniform float u_sweight;

		void main()
		{
		    vec2 coord = vTextureCoord * vec2(912.0, 626.0);
			vec2 coord2 = vec2(floor(coord.x), floor(coord.y));
			float w; 

			vec4 color;
		    if (mod(coord2.y, 2.0) == 0.0) {
		        // color = vec4(1.0, 0.0, 0.0, 1.0); 
				color = texture2D(u_lfSampler, vTextureCoord);
				w = u_lweight;
		    } else {
		        // color = vec4(1.0, 1.0, 0.0, 1.0); 
				color = texture2D(u_sfSampler, vTextureCoord);
				w = u_sweight;
		    }

		    gl_FragColor = color * vec4(w, w, w, 1.0);
		}
   `;

	const mainShaderSource = `		
		precision mediump float;
    
		varying highp vec2 vTextureCoord;
    	uniform sampler2D sampler;
    	void main() {
			gl_FragColor = texture2D(sampler, vTextureCoord);
			/*
			vec2 coord = vec2(floor(gl_FragCoord.x), floor(gl_FragCoord.y));
		    if (mod(coord.y, 2.0) == 0.0) {
		        gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
		    } else {
		        gl_FragColor = vec4(1.0, 1.0, 0.0, 1.0);
		    }
			*/
    	}
   `;

	function initWebGL() {
		// General WebGL options
		const options = {
			alpha: false,
			antialias: false,
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

		// Create the shader programs
		mergeShaderProgram = compileProgram(vertexShaderSource, mergeShaderSource);
		mainShaderProgram = compileProgram(vertexShaderSource, mainShaderSource);

		// Setup the vertex coordinate buffer
		const vCoords = new Float32Array([1.0, 1.0, -1.0, 1.0, 1.0, -1.0, -1.0, -1.0]);
		createBuffer(vCoords);
		setAttribute(mainShaderProgram, 'aVertexPosition');
		setAttribute(mergeShaderProgram, 'aVertexPosition');

		// Setup the texture coordinate buffer
		const tCoords = new Float32Array([1.0, 1.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0]);
		createBuffer(tCoords);
		setAttribute(mainShaderProgram, 'aTextureCoord');
		setAttribute(mergeShaderProgram, 'aTextureCoord');

		// Flip y axis to get the image right
		gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, true);

		// Bind uniforms
		gl.useProgram(mergeShaderProgram);
		lfWeight = gl.getUniformLocation(mergeShaderProgram, 'u_lweight')!;
		sfWeight = gl.getUniformLocation(mergeShaderProgram, 'u_sweight')!;
		lfSampler = gl.getUniformLocation(mergeShaderProgram, 'u_lfSampler')!;
		sfSampler = gl.getUniformLocation(mergeShaderProgram, 'u_sfSampler')!;
		gl.uniform1i(lfSampler, 0);
		gl.uniform1i(sfSampler, 1);

		gl.useProgram(mainShaderProgram);
		sampler = gl.getUniformLocation(mainShaderProgram, 'sampler')!;
		gl.uniform1i(sampler, 0);

		// Create textures
		lfTexture = createTexture(HPIXELS, VPIXELS);
		sfTexture = createTexture(HPIXELS, VPIXELS);
		mergeTexture = createTexture(HPIXELS, 2 * VPIXELS);

	}

	function resizeCanvasToDisplaySize() {
		// Lookup the size the browser is displaying the canvas
		const displayWidth = canvas.clientWidth;
		const displayHeight = canvas.clientHeight;

		// Check if the canvas size matches
		const needResize = canvas.width !== displayWidth || canvas.height !== displayHeight;

		// Rectify the canvas size if not 
		if (needResize) {
			canvas.width = displayWidth;
			canvas.height = displayHeight;
			console.log("Resizing canvas to " + displayWidth + " x " + displayHeight);
		}
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

	function createTexture(width: number, height: number) {
		console.log('createTexture()');

		/*
		let pixels = new Uint8Array(width * height * 4);
		for (let y = 0; y < height; y++) {
			for (let x = 0; x < width; x++) {
				if (((y >> 3) & 1) == ((x >> 3) & 1)) {
					pixels[4 * (y * width + x) + 0] = 255;
					pixels[4 * (y * width + x) + 1] = 0;
					pixels[4 * (y * width + x) + 2] = 0;
					pixels[4 * (y * width + x) + 3] = 255;
				} else {
					pixels[4 * (y * width + x) + 0] = 255;
					pixels[4 * (y * width + x) + 1] = 255;
					pixels[4 * (y * width + x) + 2] = 0;
					pixels[4 * (y * width + x) + 3] = 255;
				}
			}
		}
		*/

		const texture = gl.createTexture()!;
		gl.bindTexture(gl.TEXTURE_2D, texture);
		gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.CLAMP_TO_EDGE);
		gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, gl.CLAMP_TO_EDGE);
		gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);
		gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);
		gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, width, height, 0, gl.RGBA, gl.UNSIGNED_BYTE, null);

		return texture;
	}

	function createBuffer(values: Float32Array) {
		console.log('createBuffer()');

		const buffer = gl.createBuffer()!;
		gl.bindBuffer(gl.ARRAY_BUFFER, buffer);
		gl.bufferData(gl.ARRAY_BUFFER, values, gl.STATIC_DRAW);
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

	function draw() {
		if ($amiga != undefined) {

			// Rectify canvas size if needed
			resizeCanvasToDisplaySize();

			// Get the latest half-picture from the emulator
			updateTexture();

			// Merge half-pictures
			createMergeTexture();

			// Render to final texture to the canvas
			renderFinalTexture();
		} else {
			console.log('Skipping draw: Store not yet initialized');
		}
	}

	function updateTexture() {
		const w = HPIXELS;
		const h = VPIXELS;

		if ($amiga.poweredOff()) {
			// Get the noise texture
			const noise = $denise.noise();

			// Ensure that the merge shader is used
			prevLOF = currLOF;
			currLOF = !prevLOF;

			// Update the GPU texture
			const tex = new Uint8Array($vAmiga.HEAPU8.buffer, noise, w * h * 4);
			if (currLOF) {
				gl.activeTexture(gl.TEXTURE0);
				gl.bindTexture(gl.TEXTURE_2D, lfTexture);
				gl.texSubImage2D(gl.TEXTURE_2D, 0, 0, 0, w, h, gl.RGBA, gl.UNSIGNED_BYTE, tex);
			} else {
				gl.activeTexture(gl.TEXTURE1);
				gl.bindTexture(gl.TEXTURE_2D, sfTexture);
				gl.texSubImage2D(gl.TEXTURE_2D, 0, 0, 0, w, h, gl.RGBA, gl.UNSIGNED_BYTE, tex);
			}
		} else {
			// Get the emulator texture
			const frame = $denise.getEmulatorTexture();

			// Store the LOF bits
			prevLOF = frame.prevLof;
			currLOF = frame.currLof;

			// Check for duplicate frames or frame drops
			if (frame.frameNr != frameNr + 1) {
				console.log('Frame sync mismatch: ' + frameNr + ' -> ' + frame.frameNr);

				// Return immediately if we alredy have this texture
				if (frame.frameNr == frameNr) return;
			}
			frameNr = frame.frameNr;

			// Update the GPU texture
			const tex = new Uint8Array($vAmiga.HEAPU8.buffer, frame.data, w * h * 4);
			if (currLOF) {
				gl.activeTexture(gl.TEXTURE0);
				gl.bindTexture(gl.TEXTURE_2D, lfTexture);
				gl.texSubImage2D(gl.TEXTURE_2D, 0, 0, 0, w, h, gl.RGBA, gl.UNSIGNED_BYTE, tex);
			} else {
				gl.activeTexture(gl.TEXTURE1);
				gl.bindTexture(gl.TEXTURE_2D, sfTexture);
				gl.texSubImage2D(gl.TEXTURE_2D, 0, 0, 0, w, h, gl.RGBA, gl.UNSIGNED_BYTE, tex);
			}
		}
	}

	function createMergeTexture() {
		if (currLOF == prevLOF) {
			if (currLOF) {
				// Case 1: Non-interlace mode, two long frames in a row
				gl.useProgram(mergeShaderProgram);
				gl.uniform1f(lfWeight, 1.0);
				gl.uniform1f(sfWeight, 1.0);
				gl.uniform1i(lfSampler, 0);
				gl.uniform1i(sfSampler, 0);
			} else {
				// Case 2: Non-interlace mode, two short frames in a row
				gl.useProgram(mergeShaderProgram);
				gl.uniform1f(lfWeight, 1.0);
				gl.uniform1f(sfWeight, 1.0);
				gl.uniform1i(lfSampler, 1);
				gl.uniform1i(sfSampler, 1);
			}
		} else {
			// Case 3: Interlace mode, long frame followed by a short frame
			gl.useProgram(mergeShaderProgram);
			gl.uniform1i(lfSampler, 1);
			gl.uniform1i(sfSampler, 0);

			const weight = 0.5; // TODO: USE OPTION PARAMETER

			if (weight) {
				gl.useProgram(mergeShaderProgram);
				gl.uniform1f(lfWeight, flickerCnt % 4 >= 2 ? 1.0 : weight);
				gl.uniform1f(sfWeight, flickerCnt % 4 >= 2 ? weight : 1.0);
				flickerCnt += 1;
			}
		}

		const fb = gl.createFramebuffer();
		gl.activeTexture(gl.TEXTURE0);
		gl.bindTexture(gl.TEXTURE_2D, lfTexture);
		gl.activeTexture(gl.TEXTURE1);
		gl.bindTexture(gl.TEXTURE_2D, sfTexture);
		gl.bindFramebuffer(gl.FRAMEBUFFER, fb);
		gl.viewport(0, 0, HPIXELS, 2 * VPIXELS);
		gl.framebufferTexture2D(gl.FRAMEBUFFER, gl.COLOR_ATTACHMENT0, gl.TEXTURE_2D, mergeTexture, 0);
		gl.drawArrays(gl.TRIANGLE_STRIP, 0, 4);
	}

	function renderFinalTexture() {
		// Render to the canvas instead of the framebuffer
		gl.bindFramebuffer(gl.FRAMEBUFFER, null);
		gl.viewport(0, 0, gl.canvas.width, gl.canvas.height);
		gl.activeTexture(gl.TEXTURE0);
		gl.bindTexture(gl.TEXTURE_2D, mergeTexture);
		gl.useProgram(mainShaderProgram);
		gl.drawArrays(gl.TRIANGLE_STRIP, 0, 4);
	}

	onMount(() => {
		console.log('GLCanvas: onMount()');
		initWebGL();
		window.requestAnimationFrame(drawAnimationFrame);
	});
</script>

<canvas bind:this={canvas} style="image-rendering: pixelated" class="w-full h-full" tabindex="-1" />
<!-- <canvas bind:this={canvas} style="image-rendering: pixelated" tabindex="-1" />-->
