<script lang="ts">
    import { createEventDispatcher } from "svelte";
    export function open(){
        inputFile.click();        
    }
    const dispatch = createEventDispatcher<{ loaded: { file: Uint8Array } }>();

    function read_file_stream(file:File)
    {
        return new Promise(async (resolve, reject)=>{
            try{
                var fileReader=new FileReader();
                fileReader.onload = function(e:Event){
                    resolve(new Uint8Array(this.result as ArrayBuffer));
                }
                fileReader.readAsArrayBuffer(file);

            } catch(e)
            {
                reject(e);
            }



        });
    }
    async function read_file(e:Event){
        if(inputFile.files != null && inputFile.files.length>0)
        {
            let file=inputFile.files[0];
            let u8 = await read_file_stream(file) as Uint8Array;
            dispatch('loaded', { file: u8 });
        }
        inputFile.value="";
    }

    let inputFile:HTMLInputElement;
</script>

<input bind:this={inputFile} type="file" class="hidden" on:change={read_file}>