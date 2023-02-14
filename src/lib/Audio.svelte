<script lang="ts">

    import { proxy, amiga } from '$lib/stores';

    let audioContext: AudioContext | null = null;
	let insertSound: AudioBuffer | null = null;
	let ejectSound: AudioBuffer | null = null;
	let stepSound: AudioBuffer | null = null;
	let clickSound: AudioBuffer | null = null;

    export async function setup() {
		if (audioContext != null) {
			console.log('Audio context already initialized');
            /*
            if (audioContext.state === 'suspended') {
				audioContext.resume();
			}
            */
			return;
		}
		audioContext = new AudioContext();
		audioContext.onstatechange = () => console.log('Audio Context: state = ' + audioContext?.state);
		let gainNode = audioContext.createGain();
		gainNode.gain.value = 0.15;
		gainNode.connect(audioContext.destination);

		$amiga.setSampleRate(audioContext.sampleRate);
		await audioContext.audioWorklet.addModule('js/audio-processor.js');
		const audioNode = new AudioWorkletNode(audioContext, 'audio-processor', {
			outputChannelCount: [2],
			processorOptions: {
				pointers: [$amiga.leftChannelBuffer(), $amiga.rightChannelBuffer()],
				buffer: $proxy.HEAPF32.buffer,
				length: 2048
			}
		});
		audioNode.port.onmessage = (e) => {
			$amiga.updateAudio(e.data);
		};
		audioNode.connect(audioContext.destination);
		if (audioContext.state === 'suspended') {
			audioContext.resume();
		}

		loadSounds();
	}
	
	async function loadSounds() {
		if (insertSound == null) insertSound = await loadSound('sounds/insert.mp3');
		if (ejectSound == null) ejectSound = await loadSound('sounds/eject.mp3');
		if (stepSound == null) stepSound = await loadSound('sounds/step.mp3');
		if (clickSound == null) clickSound = await loadSound('sounds/stephd.mp3');
	}

	export function playInsertSound() { playAudioBuffer(insertSound); }
	export function playEjectSound() { playAudioBuffer(ejectSound); }
	export function playStepSound() { playAudioBuffer(stepSound); }
	export function playClickSound() { playAudioBuffer(clickSound); }

	async function playAudioBuffer(audio_buffer: AudioBuffer | null) {
		if (audio_buffer == null) {
			return;
		}
		/*
		if (parallel_playing > 2 && audio_buffer == audio_df_step) {
			//not more than 3 stepper sounds at the same time
			return;
		}
		*/
		const source = audioContext!.createBufferSource();
		source.buffer = audio_buffer;

		let gain_node = audioContext!.createGain();
		gain_node.gain.value = 0.2;
		gain_node.connect(audioContext!.destination);

		source.addEventListener('ended', () => {
			// parallel_playing--;
		});

		source.connect(gain_node);
		// parallel_playing++;
		source.start();
	};

	async function loadSound(url: string) {
		console.log("load_sound: url = " + url);
		let response = await fetch(url);
		let buffer = await response.arrayBuffer();
		let audio_buffer = await audioContext!.decodeAudioData(buffer);
		return audio_buffer;
	}

</script>
