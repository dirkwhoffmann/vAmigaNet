<script lang="ts">
    import {amiga } from '$lib/stores';
	import { onMount } from 'svelte';
    import { RingBuffer } from './RingBuffer';

    const audioContext = new AudioContext();
    let audio_connected=false;
    let soundbuffer_slots=[];


    let connect_audio_processor = async () => {
        if(audioContext.state === 'suspended') {
            await audioContext.resume();  
        }
        if(audio_connected==true)
            return; 
        if(audioContext.state === 'suspended') {
            return;  
        }
        audio_connected=true;
        
        $amiga.wasm_set_sample_rate(audioContext.sampleRate);

        console.log("try connecting audioprocessor...");
        if(audioContext.audioWorklet==undefined)
        {
            console.error("audioContext.audioWorklet == undefined");
            return;
        }
        
        await audioContext.audioWorklet.addModule('js/vAmiga_audioprocessor.js');
        let worklet_node = new AudioWorkletNode(audioContext, 'vAmiga_audioprocessor', {
            outputChannelCount: [2],
            numberOfInputs: 0,
            numberOfOutputs: 1
        });

        let init_sound_buffer=function(){
            console.log("get wasm sound buffer adresses");
            let sound_buffer_address = $amiga.wasm_get_sound_buffer_address();
            soundbuffer_slots=[];
            for(let slot=0;slot<16;slot++)
            {
                soundbuffer_slots.push(
                    new Float32Array(window.Module.HEAPF32.buffer, sound_buffer_address+(slot*2048)*4, 2048));
            }
        }
        init_sound_buffer();

        let empty_shuttles=new RingBuffer(16);
        worklet_node.port.onmessage = (msg) => {
            //direct c function calls with preceeding Module._ are faster than cwrap
            let samples=$amiga.wasm_copy_into_sound_buffer();
            let shuttle = msg.data;
            if(samples<1024)
            {
                if(shuttle!="empty")
                {
                    empty_shuttles.write(shuttle);
                }
                return;
            }
            let slot=0;
            while(samples>=1024)
            {
                if(shuttle == null || shuttle=="empty")
                {
                    if(!empty_shuttles.isEmpty())
                    {
                        shuttle = empty_shuttles.read();
                    }
                    else
                    {
                    return;
                    }
                }
                let wasm_buffer_slot = soundbuffer_slots[slot++];
                if(wasm_buffer_slot.byteLength==0)
                {//slot can be detached when wasm had grown memory, adresses are wrong then so lets reinit
                    init_sound_buffer();
                    wasm_buffer_slot = soundbuffer_slots[slot-1];
                }
                shuttle.set(wasm_buffer_slot);
                worklet_node.port.postMessage(shuttle, [shuttle.buffer]);
                shuttle=null;
                samples-=1024;
            }            
        };
        worklet_node.port.onmessageerror = (msg) => {
            console.log("audio processor error:"+msg);
        };
        worklet_node.connect(audioContext.destination);        
    }


    //when app is going to background
    //window.addEventListener('blur', pause);

    //when app is coming to foreground again, reconnect audio if it has been 'suspended' in the meantime
    window.addEventListener('focus', async ()=>{ 
        try { await connect_audio_processor(); } catch(e){ console.error(e);}
    });

    audioContext.onstatechange = () => {
        let state = audioContext.state;
        console.error(`audioContext.state=${state}`);
        if(state==='suspended'){
            //in case we did go suspended reinstall the unlock events
            document.removeEventListener('click',click_unlock_WebAudio);
            document.addEventListener('click',click_unlock_WebAudio, false);

            //iOS safari does not bubble click events on canvas so we add this extra event handler here
            let canvas=document.getElementById('canvas');
//            canvas.removeEventListener('touchstart',touch_unlock_WebAudio);
//            canvas.addEventListener('touchstart',touch_unlock_WebAudio,false);        
        }
        else if(state === 'running') {
            //if it runs we dont need the unlock handlers, has no effect when handler already removed 
            document.removeEventListener('click',click_unlock_WebAudio);
//            document.getElementById('canvas').removeEventListener('touchstart',touch_unlock_WebAudio);
        }
    }


    let click_unlock_WebAudio=async function() {
        try { await connect_audio_processor(); } catch(e){ console.error(e);}
    }
    let touch_unlock_WebAudio=async function() {
        try { await connect_audio_processor(); } catch(e){ console.error(e);}
    }    
/*
document.addEventListener('click',click_unlock_WebAudio, false);

//iOS safari does not bubble click events on canvas so we add this extra event handler here
document.getElementById('canvas').addEventListener('touchstart',touch_unlock_WebAudio,false);
*/

    onMount(() => {
        //console.log("creating audio buffers");
        //let audio_buffers = $amiga.createAudioBuffers(4096);
        //console.error(audio_buffers);
       // $amiga.copyAudioBuffers();
        
	});


</script>
<button on:click={click_unlock_WebAudio}>unlock audio</button>