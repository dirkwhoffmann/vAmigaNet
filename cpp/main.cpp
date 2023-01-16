#include <emscripten.h>
#include <emscripten/wasm_worker.h>
#include <cstdlib>
#include <stdio.h>
#include <exception>

#include "config.h"
#include "Amiga.h"

using namespace vamiga;

Amiga *amiga = nullptr;

/*
void run_in_worker()
{
  while (1) {

    printf(">>>> Hello from wasm worker thread!\n");
    throw std::runtime_error("run_in_worker");

    sleep(1);
  }
}
*/

void processMsg(const void *amiga, long id, int data1, int data2, int data3, int data4)
{
  printf("MSG %s: %x %x %x %x\n", MsgTypeEnum::key(id), data1, data2, data3, data4);
}

/*
void *thread_callback(void *arg)
{
  sleep(1);
  printf("Inside the thread: %d\n", *(int *)arg);
  return NULL;
}
*/

int main(int argc, char *argv[])
{
  printf("Entering main()\n");

  printf("  Constructing Amiga...\n");
  amiga = new Amiga();

  printf("  Adding listener...\n");
  amiga->msgQueue.setListener(amiga, &processMsg);

  printf("  Launching emulator thread...\n");
  amiga->launch();

  printf("  Configuring...\n");
  amiga->configure(OPT_AUDVOLL, 100);
  amiga->configure(OPT_AUDVOLR, 100);
  amiga->configure(OPT_AUDVOL, 0, 100);
  amiga->configure(OPT_AUDPAN, 0, 0);

  amiga->configure(OPT_CHIP_RAM, 512);
  amiga->configure(OPT_SLOW_RAM, 512);
  amiga->configure(OPT_AGNUS_REVISION, AGNUS_OCS);

  printf("Exiting main()\n");
  return EXIT_SUCCESS;
}

extern "C" void pressUp()
{
  printf("pressUp()\n");
}

extern "C" void pressDown()
{
  printf("pressDown()\n");
}

extern "C" void pressLeft()
{
  printf("pressLeft()\n");
}

extern "C" void pressRight()
{
  printf("pressRight()\n");
}

extern "C" void pressKey(char c)
{
  printf("pressChar(%d)\n", c);
}