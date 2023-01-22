<script lang="ts">
	import '../../app.css';
	import { onMount } from 'svelte';
	import { fade } from 'svelte/transition';
	import { goto } from '$app/navigation';
	import Button from '$lib/widgets/Button.svelte';
	import RetroShell from '$lib/RetroShell.svelte';
	import FaAngleLeft from 'svelte-icons/fa/FaAngleLeft.svelte';
	import { vAmiga } from '$lib/stores';

	import * as mat4 from 'gl-matrix/mat4';
	
	let showShell = false;
	let canvas: HTMLCanvasElement;
	let gl: CanvasRenderingContext2D;

	// Vertex shader program
	const vsSource = `
    attribute vec4 aVertexPosition;
    uniform mat4 uModelViewMatrix;
    uniform mat4 uProjectionMatrix;
    void main() {
      gl_Position = uProjectionMatrix * uModelViewMatrix * aVertexPosition;
    }
  `;

	const fsSource = `
    void main() {
      gl_FragColor = vec4(1.0, 1.0, 0.0, 1.0);
    }
  `;

	function loadShader(gl, type, source) {
		console.log('loadShader');
		const shader = gl.createShader(type);

		// Send the source to the shader object

		gl.shaderSource(shader, source);

		// Compile the shader program

		gl.compileShader(shader);

		// See if it compiled successfully

		if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS)) {
			alert(`An error occurred compiling the shaders: ${gl.getShaderInfoLog(shader)}`);
			gl.deleteShader(shader);
			return null;
		}

		return shader;
	}

	function initShaderProgram(gl, vsSource, fsSource) {
		console.log('Load shaders');
		const vertexShader = loadShader(gl, gl.VERTEX_SHADER, vsSource);
		const fragmentShader = loadShader(gl, gl.FRAGMENT_SHADER, fsSource);

		// Create the shader program

		console.log('Create programs');
		const shaderProgram = gl.createProgram();
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

		return shaderProgram;
	}

	function initBuffers(gl) {
		const positionBuffer = initPositionBuffer(gl);

		return {
			position: positionBuffer
		};
	}

	function initPositionBuffer(gl) {
		// Create a buffer for the square's positions.
		const positionBuffer = gl.createBuffer();

		// Select the positionBuffer as the one to apply buffer
		// operations to from here out.
		gl.bindBuffer(gl.ARRAY_BUFFER, positionBuffer);

		// Now create an array of positions for the square.
		const positions = [1.0, 1.0, -1.0, 1.0, 1.0, -1.0, -1.0, -1.0];

		// Now pass the list of positions into WebGL to build the
		// shape. We do this by creating a Float32Array from the
		// JavaScript array, then use it to fill the current buffer.
		gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(positions), gl.STATIC_DRAW);

		return positionBuffer;
	}

	function drawScene(gl, programInfo, buffers) {
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

		// Tell WebGL to use our program when drawing
		gl.useProgram(programInfo.program);

		// Set the shader uniforms
		gl.uniformMatrix4fv(programInfo.uniformLocations.projectionMatrix, false, projectionMatrix);
		gl.uniformMatrix4fv(programInfo.uniformLocations.modelViewMatrix, false, modelViewMatrix);

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

	export { drawScene };

	let shaderProgram;
	let programInfo;

	onMount(() => {
		console.log('onMount()');
		gl = canvas.getContext('webgl');
		if (gl) {
			console.log('Graphics context created');

			console.log('Set clearColor');
			gl.clearColor(0.0, 1.0, 0.0, 1.0);

			console.log('Clear context');
			gl.clear(gl.COLOR_BUFFER_BIT);

			shaderProgram = initShaderProgram(gl, vsSource, fsSource);

			console.log('getLocation');
			const programInfo = {
				program: shaderProgram,
				attribLocations: {
					vertexPosition: gl.getAttribLocation(shaderProgram, 'aVertexPosition')
				},
				uniformLocations: {
					projectionMatrix: gl.getUniformLocation(shaderProgram, 'uProjectionMatrix'),
					modelViewMatrix: gl.getUniformLocation(shaderProgram, 'uModelViewMatrix')
				}
			};

			console.log('onMount:Done');

			const buffers = initBuffers(gl);
			drawScene(gl, programInfo, buffers);

			// window.requestAnimationFrame(do_animation_frame);
		}
	});

	function goBack() {
		console.log('goBack()');
		goto('/');
	}
	function openShell() {
		console.log('openShell()');
		showShell = !showShell;
	}

	let clipped_width = 912;
	let clipped_height = 313;

	function draw(now) {
		let pixels = $vAmiga.pixelBuffer();

		let image_data = gl.createImageData(clipped_width, clipped_height);
		image_data.data.set(pixels, 0);
		gl.putImageData(image_data, 0, 0);
	}

	let stop_request_animation_frame = false;
	function do_animation_frame(now) {
		draw(now);
		if (!stop_request_animation_frame) {
			window.requestAnimationFrame(do_animation_frame);
		}
	}
</script>

<body class="h-screen bg-black text-white">
	<title>vAmiga Online</title>

	<div class="h-screen flex flex-col">
		<div>
			<div class="z-30 w-screen bg-white/30 flex space-x-2 p-2">
				<Button on:click={goBack}><FaAngleLeft /></Button>
				<Button on:click={openShell} img="retroShellIcon.png" />
			</div>
		</div>
		<div class="relative w-full h-full">
			<canvas bind:this={canvas} class="" width="724" height="568" tabindex="-1" />
			{#if showShell}
				<div
					transition:fade
					class="absolute top-0 left-0 w-full h-full border-none border-red-500 flex-grow overflow-scroll"
				>
					<RetroShell />
				</div>
			{/if}
		</div>
	</div>
</body>
