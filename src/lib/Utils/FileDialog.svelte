<script lang="ts">

    let fileDialog: HTMLInputElement;
    let promiseResolve;
    let promiseReject;

    export function open()
    {
        // Open file dialog
        fileDialog.click();

        return new Promise(function (resolve, reject) {
            promiseResolve = resolve;
            promiseReject = reject;
        });
    }

    async function okAction()
    {
        if (fileDialog.files?.length > 0) {
            let file = fileDialog.files![0];
            let u8 = await readFileStream(file) as Uint8Array;
            promiseResolve(u8);
        } else {
            promiseReject();
        }

        fileDialog.value = "";
    }

    function readFileStream(file: File)
    {
        return new Promise(async (resolve, reject) => {
            try {
                let fileReader = new FileReader();
                fileReader.onload = function (e: Event) {
                    resolve(new Uint8Array(this.result as ArrayBuffer));
                }
                fileReader.readAsArrayBuffer(file);

            } catch (e) {
                reject(e);
            }
        });
    }
</script>

<input bind:this={fileDialog} type="file" class="hidden" on:change={okAction}>