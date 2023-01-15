#include <emscripten.h>
#include <emscripten/wasm_worker.h>
#include <cstdlib>
#include <stdio.h>

#include "config.h"
#include "Amiga.h"

using namespace vamiga;

Amiga *amiga = nullptr;

void processMsg(const void *amiga, long id, int data1, int data2, int data3, int data4)
{
    printf("MSG %s: %x %x %x %x\n", MsgTypeEnum::key(id), data1, data2, data3, data4);
}


void run_in_worker()
{
  printf(">>>> Hello from wasm worker thread!\n");
}

int main(int argc, char *argv[])
{
    emscripten_wasm_worker_t worker = emscripten_malloc_wasm_worker(/*stack size: */1024);
    emscripten_wasm_worker_post_function_v(worker, run_in_worker);


    printf("Constructing Amiga instance...\n");
    amiga = new Amiga();

    printf("Adding listener...\n");
    amiga->msgQueue.setListener(amiga, &processMsg);

    printf("Configuring...\n");
    amiga->configure(OPT_AUDVOLL, 100);
    amiga->configure(OPT_AUDVOLR, 100);
    amiga->configure(OPT_AUDVOL, 0, 100);
    amiga->configure(OPT_AUDPAN, 0, 0);

    amiga->configure(OPT_CHIP_RAM, 512);
    amiga->configure(OPT_SLOW_RAM, 512);
    amiga->configure(OPT_AGNUS_REVISION, AGNUS_OCS);

    return EXIT_SUCCESS;
}
