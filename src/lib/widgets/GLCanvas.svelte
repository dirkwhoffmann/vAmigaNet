<svelte:options accessors={true} />

<script lang="ts">
	import { vAmiga, amiga } from '$lib/stores';
	import { VPIXELS, HPIXELS, TPP } from '$lib/constants.ts';
	import { onMount } from 'svelte';
	import * as mat4 from 'gl-matrix/mat4';

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

	function loadShader(type: GLenum, source: string) {
		console.log('Creating shader of type ' + type);
		const shader = gl.createShader(type);
		if (shader == null) {
			console.log("Can't create shader");
			return; // TODO: THROW EXCEPTION
		}

		console.log('Assign shader source');
		gl.shaderSource(shader, source);
		console.log('Compile shader');
		gl.compileShader(shader);

		if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
			alert(`An error occurred compiling the shaders: ${gl.getShaderInfoLog(shader)}`);
			gl.deleteShader(shader);
			return null;
		}

		console.log('Shader loaded');
		return shader;
	}

	function initShaderProgram() {
		console.log('Load shaders');
		const vertexShader = loadShader(gl.VERTEX_SHADER, vsSource);
		const fragmentShader = loadShader(gl.FRAGMENT_SHADER, fsSource);

		console.log('Create programs');
		const shaderProgram = gl.createProgram();
		if (shaderProgram == null) {
			console.log('Cannot create shader program');
			return;
		}

		console.log('Attach programs');
		gl.attachShader(shaderProgram, vertexShader);
		gl.attachShader(shaderProgram, fragmentShader);
		console.log('Link programs');
		gl.linkProgram(shaderProgram);

		// If creating the shader program failed, alert

		if (!gl.getProgramParameter(shaderProgram, gl.LINK_STATUS)) {
			alert(`Unable to initialize the shader program: ${gl.getProgramInfoLog(shaderProgram)}`);
			return null;
		}

		console.log('All shaders in place');
		return shaderProgram;
	}

	function buildBuffers() {
		// Setup vertex coordinate buffer
		vertexCoordBuffer = gl.createBuffer()!;
		gl.bindBuffer(gl.ARRAY_BUFFER, vertexCoordBuffer);
		const positions = [1.0, 1.0, -1.0, 1.0, 1.0, -1.0, -1.0, -1.0];
		gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(positions), gl.STATIC_DRAW);

		// Setup texture coordinate buffer
		textureCoordBuffer = gl.createBuffer()!;
		gl.bindBuffer(gl.ARRAY_BUFFER, textureCoordBuffer);
		const textureCoordinates = [1.0, 1.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0];
		gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(textureCoordinates), gl.STATIC_DRAW);

		// Flip y axis to get the image right
		gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, true);
	}

	function buildTextures() {
		console.log('buildTextures()');
		texture = gl.createTexture()!;
		let pixels = new Uint8Array(VPIXELS * HPIXELS * 4);
		gl.bindTexture(gl.TEXTURE_2D, texture);
		gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.CLAMP_TO_EDGE);
		gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, gl.CLAMP_TO_EDGE);
		gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);
		gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);

		gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, HPIXELS, VPIXELS, 0, gl.RGBA, gl.UNSIGNED_BYTE, null);
	}

	function drawScene(programInfo) {

		gl.clearColor(0.0, 1.0, 0.0, 1.0);
		gl.clearDepth(1.0); // Clear everything
		gl.enable(gl.DEPTH_TEST); // Enable depth testing
		gl.depthFunc(gl.LEQUAL); // Near things obscure far things

		// Clear the canvas before we start drawing on it.
		gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

		// Tell WebGL how to pull out the positions from the position
		// buffer into the vertexPosition attribute.
		setPositionAttribute(programInfo);
		setTextureAttribute(programInfo);

		// Tell WebGL to use our program when drawing
		gl.useProgram(programInfo.program);

		let unity = mat4.create();

		// Tell WebGL we want to affect texture unit 0
		gl.activeTexture(gl.TEXTURE0);

		// Bind the texture to texture unit 0
		gl.bindTexture(gl.TEXTURE_2D, texture);

		// Tell the shader we bound the texture to texture unit 0
		gl.uniform1i(programInfo.uniformLocations.uSampler, 0);

		{
			const offset = 0;
			const vertexCount = 4;
			gl.drawArrays(gl.TRIANGLE_STRIP, offset, vertexCount);
		}
	}

	// Tell WebGL how to pull out the positions from the position
	// buffer into the vertexPosition attribute.
	function setPositionAttribute(programInfo) {
		const numComponents = 2; // pull out 2 values per iteration
		const type = gl.FLOAT; // the data in the buffer is 32bit floats
		const normalize = false; // don't normalize
		const stride = 0; // how many bytes to get from one set of values to the next
		// 0 = use type and numComponents above
		const offset = 0; // how many bytes inside the buffer to start from
		gl.bindBuffer(gl.ARRAY_BUFFER, vertexCoordBuffer);
		gl.vertexAttribPointer(
			programInfo.attribLocations.vertexPosition,
			numComponents,
			type,
			normalize,
			stride,
			offset
		);
		gl.enableVertexAttribArray(programInfo.attribLocations.vertexPosition);
	}

	function setTextureAttribute(programInfo) {
			const num = 2; // every coordinate composed of 2 values
			const type = gl.FLOAT; // the data in the buffer is 32-bit float
			const normalize = false; // don't normalize
			const stride = 0; // how many bytes to get from one set to the next
			const offset = 0; // how many bytes inside the buffer to start from
			gl.bindBuffer(gl.ARRAY_BUFFER, textureCoordBuffer);
			gl.vertexAttribPointer(
				programInfo.attribLocations.textureCoord,
				num,
				type,
				normalize,
				stride,
				offset
			);
			gl.enableVertexAttribArray(programInfo.attribLocations.textureCoord);
		}

	function draw(now) {
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

	// let stop_request_animation_frame = false;
	function do_animation_frame(now) {
		if (enableDrawing) {
			draw(now);
			window.requestAnimationFrame(do_animation_frame);
		}
	}

	onMount(() => {
		console.log('GLCanvas: onMount()');

		// Only proceed if WebGL2 is supported
		if (!(canvas.getContext('webgl2') instanceof WebGL2RenderingContext)) {
			throw new Error('vAmiga Online needs WebGL2 to run.');
		}

		// Store the context for further use
		gl = canvas.getContext('webgl2')!;

		// Clear buffer
		gl.clearColor(0.0, 0.0, 0.0, 1.0);
		gl.clear(gl.COLOR_BUFFER_BIT);

		// Build ressources
		buildTextures();
		buildBuffers();

		console.log('Calling initShaderProgram');
		const shaderProgram = initShaderProgram();

		console.log('getLocation');
		const programInfo = {
			program: shaderProgram,
			attribLocations: {
				vertexPosition: gl.getAttribLocation(shaderProgram, 'aVertexPosition'),
				textureCoord: gl.getAttribLocation(shaderProgram, 'aTextureCoord')
			},
			uniformLocations: {
				uSampler: gl.getUniformLocation(shaderProgram, 'uSampler')
			}
		};

		drawScene(programInfo);
		console.log('onMount:Done');

		//if we get the context start rendering every VSync
		window.requestAnimationFrame(do_animation_frame);
	});
</script>

<canvas bind:this={canvas} class="w-full h-full" tabindex="-1" />
