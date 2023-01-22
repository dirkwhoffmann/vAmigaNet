<script lang="ts">
	import { onMount } from 'svelte';
	import * as mat4 from 'gl-matrix/mat4';

	// Reference to the canvas element
	let canvas: HTMLCanvasElement;
	let texture: WebGLTexture;

	const vsSource = `
    attribute vec4 aVertexPosition;
    attribute vec2 aTextureCoord;

    uniform mat4 uModelViewMatrix;
    uniform mat4 uProjectionMatrix;

    varying highp vec2 vTextureCoord;

    void main() {
      gl_Position = uProjectionMatrix * uModelViewMatrix * aVertexPosition;
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

	let gl: WebGLRenderingContext;

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

	function initBuffers() {
		const positionBuffer = initPositionBuffer();
		const textureCoordBuffer = initTextureBuffer();

		return {
			position: positionBuffer,
			textureCoord: textureCoordBuffer
		};
	}

	function initPositionBuffer() {
		// Create a buffer for the square's positions.
		const positionBuffer = gl.createBuffer();

		// Select the positionBuffer as the one to apply buffer
		// operations to from here out.
		gl.bindBuffer(gl.ARRAY_BUFFER, positionBuffer);

		// Canvas coordinates (UR, UL, LR, LL)
		const positions = [1.0, 1.0, -1.0, 1.0, 1.0, -1.0, -1.0, -1.0];

		// Now pass the list of positions into WebGL to build the
		// shape. We do this by creating a Float32Array from the
		// JavaScript array, then use it to fill the current buffer.
		gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(positions), gl.STATIC_DRAW);

		return positionBuffer;
	}

	function createEmulatorTexture() {
		const t = gl.createTexture()!;

		const w = 912;
		const h = 313;
		const bytes = w * h * 4;
		console.log('Texture size: ' + h + ' x ' + w);
		let pixels = new Uint8Array(bytes);

		for (let y = 0; y < h; y++) {
			for (let x = 0; x < w; x++) {
				if (((y >> 3) & 1) == ((x >> 3) & 1)) {
					pixels[4 * (y * w + x) + 0] = 100;
					pixels[4 * (y * w + x) + 1] = 100;
					pixels[4 * (y * w + x) + 2] = 100;
					pixels[4 * (y * w + x) + 3] = 255;
				} else {
					pixels[4 * (y * w + x) + 0] = 0;
					pixels[4 * (y * w + x) + 1] = 0;
					pixels[4 * (y * w + x) + 2] = 0;
					pixels[4 * (y * w + x) + 3] = 255;
				}
			}
		}

		gl.bindTexture(gl.TEXTURE_2D, t);

		gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.CLAMP_TO_EDGE);
		gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T, gl.CLAMP_TO_EDGE);
		gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);
		gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);

		gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, w, h, 0, gl.RGBA, gl.UNSIGNED_BYTE, pixels);
		return t;
	}

	function initTextureBuffer() {
		const textureCoordBuffer = gl.createBuffer();
		gl.bindBuffer(gl.ARRAY_BUFFER, textureCoordBuffer);

		const textureCoordinates = [
			1.0, 1.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0 // (UR, UL, LR, LL)
		];

		gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(textureCoordinates), gl.STATIC_DRAW);

		return textureCoordBuffer;
	}

	function drawScene(programInfo, buffers) {
		// tell webgl how to pull out the texture coordinates from buffer
		function setTextureAttribute(buffers, programInfo) {
			const num = 2; // every coordinate composed of 2 values
			const type = gl.FLOAT; // the data in the buffer is 32-bit float
			const normalize = false; // don't normalize
			const stride = 0; // how many bytes to get from one set to the next
			const offset = 0; // how many bytes inside the buffer to start from
			gl.bindBuffer(gl.ARRAY_BUFFER, buffers.textureCoord);
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

		gl.clearColor(0.0, 1.0, 0.0, 1.0);
		gl.clearDepth(1.0); // Clear everything
		gl.enable(gl.DEPTH_TEST); // Enable depth testing
		gl.depthFunc(gl.LEQUAL); // Near things obscure far things

		// Clear the canvas before we start drawing on it.

		gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

		// Create a perspective matrix, a special matrix that is
		// used to simulate the distortion of perspective in a camera.
		// Our field of view is 45 degrees, with a width/height
		// ratio that matches the display size of the canvas
		// and we only want to see objects between 0.1 units
		// and 100 units away from the camera.

		const fieldOfView = (45 * Math.PI) / 180; // in radians
		const aspect = gl.canvas.clientWidth / gl.canvas.clientHeight;
		const zNear = 0.1;
		const zFar = 100.0;
		const projectionMatrix = mat4.create();

		// note: glmatrix.js always has the first argument
		// as the destination to receive the result.
		mat4.perspective(projectionMatrix, fieldOfView, aspect, zNear, zFar);

		// Set the drawing position to the "identity" point, which is
		// the center of the scene.
		const modelViewMatrix = mat4.create();

		// Now move the drawing position a bit to where we want to
		// start drawing the square.
		mat4.translate(
			modelViewMatrix, // destination matrix
			modelViewMatrix, // matrix to translate
			[-0.0, 0.0, -6.0]
		); // amount to translate

		// Tell WebGL how to pull out the positions from the position
		// buffer into the vertexPosition attribute.
		setPositionAttribute(gl, buffers, programInfo);
		setTextureAttribute(buffers, programInfo);

		// Tell WebGL to use our program when drawing
		gl.useProgram(programInfo.program);

		// Set the shader uniforms
		gl.uniformMatrix4fv(programInfo.uniformLocations.projectionMatrix, false, projectionMatrix);
		gl.uniformMatrix4fv(programInfo.uniformLocations.modelViewMatrix, false, modelViewMatrix);

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
	function setPositionAttribute(gl, buffers, programInfo) {
		const numComponents = 2; // pull out 2 values per iteration
		const type = gl.FLOAT; // the data in the buffer is 32bit floats
		const normalize = false; // don't normalize
		const stride = 0; // how many bytes to get from one set of values to the next
		// 0 = use type and numComponents above
		const offset = 0; // how many bytes inside the buffer to start from
		gl.bindBuffer(gl.ARRAY_BUFFER, buffers.position);
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

	onMount(() => {
		console.log('onMount()');
		gl = canvas.getContext('webgl');
		if (gl) {
			console.log('Graphics context created');

			console.log('Set clearColor');
			gl.clearColor(0.0, 1.0, 0.0, 1.0);

			console.log('Clear context');
			gl.clear(gl.COLOR_BUFFER_BIT);

			console.log('Calling createTexture');
			texture = createEmulatorTexture()!;
			// gl.pixelStorei(gl.UNPACK_FLIP_Y_WEBGL, true);

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
					projectionMatrix: gl.getUniformLocation(shaderProgram, 'uProjectionMatrix'),
					modelViewMatrix: gl.getUniformLocation(shaderProgram, 'uModelViewMatrix'),
					uSampler: gl.getUniformLocation(shaderProgram, 'uSampler')
				}
			};

			const buffers = initBuffers();
			drawScene(programInfo, buffers);
			console.log('onMount:Done');
		}
	});
</script>

<div>
	<canvas bind:this={canvas} class="" width="724" height="568" tabindex="-1" />
</div>
