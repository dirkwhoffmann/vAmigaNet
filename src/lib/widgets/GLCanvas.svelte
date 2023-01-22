<svelte:options accessors={true} />

<script lang="ts">
	import { vAmiga, amiga } from '$lib/stores';
	import { VPIXELS, HPIXELS, TPP } from '$lib/constants';
	import { onMount } from 'svelte';

	export let enableDrawing = false;

	// Reference to the canvas element
	let canvas: HTMLCanvasElement;

	// Texture sizes
	const lfTextureSize = { width: HPIXELS * TPP, height: VPIXELS };
	const sfTextureSize = { width: HPIXELS * TPP, height: VPIXELS };
	const mergeTextureSize = { width: 2 * HPIXELS, height: 2 * VPIXELS };

	// Textures
	let lfTexture: WebGLTexture;
	let sfTexture: WebGLTexture;
	let mergeTexture: WebGLTexture;

	// Buffers
	let vertexCoordBuffer: WebGLBuffer;
	let textureCoordBuffer: WebGLBuffer;

	// Shaders
	let vertexShader: WebGLShader;
	let fragmentShader: WebGLShader;
	let shaderProgram: WebGLProgram;

	let fsScript: HTMLScriptElement;
	let vsScript: HTMLScriptElement;

	//
	let uSampler: WebGLUniformLocation;

	// DEPRECATED
	let texture: WebGLTexture;

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
     varying highp vec2 vTextureCoord;
     uniform sampler2D uSampler;
     void main() {
         gl_FragColor = texture2D(uSampler, vTextureCoord);    
     }
   `;

	let gl: WebGL2RenderingContext;

	function init() {
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

		// Clear buffer
		gl.clearColor(0.0, 0.0, 0.0, 1.0);
		gl.clear(gl.COLOR_BUFFER_BIT);

		// Build ressources
		/*
		vertexShader = buildShader(gl.VERTEX_SHADER, vsSource)!;
 		fragmentShader = buildShader(gl.FRAGMENT_SHADER, fsSource)!;
		buildShaderProgram();
		*/
		shaderProgram = compileProgram(vsSource, fsSource);
		texture = createTexture();

		const vCoords = new Float32Array([1.0, 1.0, -1.0, 1.0, 1.0, -1.0, -1.0, -1.0]);
		vertexCoordBuffer = createBuffer(vCoords);
		setAttribute(shaderProgram, 'aVertexPosition');

		const tCoords = new Float32Array([1.0, 1.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0]);
		textureCoordBuffer = createBuffer(tCoords);
		setAttribute(shaderProgram, 'aTextureCoord');

		// Flip y axis to get the image right
		gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, true);

		//
		uSampler = gl.getUniformLocation(shaderProgram, 'uSampler')!;
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

		const texture = gl.createTexture()!;
		gl.bindTexture(gl.TEXTURE_2D, texture);
		gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.CLAMP_TO_EDGE);
		gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, gl.CLAMP_TO_EDGE);
		gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);
		gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);
		gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, HPIXELS, VPIXELS, 0, gl.RGBA, gl.UNSIGNED_BYTE, null);

		return texture;
	}

	function createBuffer(values: Float32Array) {
		console.log('createBuffer()');

		const buffer = gl.createBuffer()!;
		gl.bindBuffer(gl.ARRAY_BUFFER, buffer);
		gl.bufferData(gl.ARRAY_BUFFER, values, gl.STATIC_DRAW);

		return buffer;
	}

	/*
	function buildShader(type: GLenum, source: string) {
		console.log('buildShader(' + type + ')');
		const shader = gl.createShader(type)!;
		gl.shaderSource(shader, source);
		gl.compileShader(shader);

		if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
			throw new Error(`Shader compile error: ${gl.getShaderInfoLog(shader)}`);
		}
		return shader;
	}

	function buildShaderProgram() {
		console.log('buildShaderProgram()');
		shaderProgram = gl.createProgram()!;
		gl.attachShader(shaderProgram, vertexShader);
		gl.attachShader(shaderProgram, fragmentShader);
		gl.linkProgram(shaderProgram);

		if (!gl.getProgramParameter(shaderProgram, gl.LINK_STATUS)) {
			throw new Error(`Shader link error: ${gl.getProgramInfoLog(shaderProgram)}`);
		}
	}
	*/

	/*
	function buildBuffers() {
		// Setup vertex coordinate buffer
		vertexCoordBuffer = gl.createBuffer()!;
		gl.bindBuffer(gl.ARRAY_BUFFER, vertexCoordBuffer);
		const positions = [1.0, 1.0, -1.0, 1.0, 1.0, -1.0, -1.0, -1.0];
		gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(positions), gl.STATIC_DRAW);
		setAttribute(shaderProgram, 'aVertexPosition');

		// Setup texture coordinate buffer
		textureCoordBuffer = gl.createBuffer()!;
		gl.bindBuffer(gl.ARRAY_BUFFER, textureCoordBuffer);
		const textureCoordinates = [1.0, 1.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0];
		gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(textureCoordinates), gl.STATIC_DRAW);
		setAttribute(shaderProgram, 'aTextureCoord');

		// Flip y axis to get the image right
		gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, true);
	}
	*/
	/*
	function buildTextures() {
		console.log('buildTextures()');
		texture = gl.createTexture()!;
		gl.bindTexture(gl.TEXTURE_2D, texture);
		gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.CLAMP_TO_EDGE);
		gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, gl.CLAMP_TO_EDGE);
		gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);
		gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);
		gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, HPIXELS, VPIXELS, 0, gl.RGBA, gl.UNSIGNED_BYTE, null);
	}
	*/

	function drawScene() {
		// Start with a clean buffer
		gl.clearColor(0.0, 1.0, 0.0, 1.0);
		gl.clear(gl.COLOR_BUFFER_BIT);

		// Select the shader program
		gl.useProgram(shaderProgram);

		// Select texture unit 0
		gl.activeTexture(gl.TEXTURE0);

		// Bind the texture to texture unit 0
		gl.bindTexture(gl.TEXTURE_2D, texture);

		// Tell the shader we bound the texture to texture unit 0
		gl.uniform1i(uSampler, 0);

		// Draw rectangle
		gl.drawArrays(gl.TRIANGLE_STRIP, 0, 4);
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
			let pixels = $amiga.pixelBuffer();

			const w = 912;
			const h = 313;

			const tex = new Uint8Array($vAmiga.HEAPU8.buffer, pixels, w * h * 4);
			gl.activeTexture(gl.TEXTURE0);
			gl.texSubImage2D(gl.TEXTURE_2D, 0, 0, 0, w, h, gl.RGBA, gl.UNSIGNED_BYTE, tex);
			gl.drawArrays(gl.TRIANGLE_STRIP, 0, 4);
		} else {
			console.log('Skipping draw: Store not yet initialized');
		}
	}

	onMount(() => {
		console.log('GLCanvas: onMount()');

		init();

		console.log('getLocation');

		drawScene();
		console.log('onMount:Done');

		//if we get the context start rendering every VSync
		window.requestAnimationFrame(drawAnimationFrame);
	});
</script>

<canvas bind:this={canvas} class="w-full h-full" tabindex="-1" />
