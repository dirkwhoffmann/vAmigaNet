#include <emscripten.h>
#include <emscripten/wasm_worker.h>
#include <emscripten/bind.h>
#include <cstdlib>
#include <stdio.h>
#include <exception>

#include "config.h"
#include "Amiga.h"

using namespace emscripten;
using namespace vamiga;

Amiga *amiga = nullptr;

float lerp(float a, float b, float t) {
    return (1 - t) * a + t * b;
}

EMSCRIPTEN_BINDINGS(my_module) {
    function("lerp", &lerp);
}

void processMsg(const void *amiga, long id, int data1, int data2, int data3, int data4)
{
  printf("MSG %s: %x %x %x %x\n", MsgTypeEnum::key(id), data1, data2, data3, data4);
}

class Proxy
{
public:
  Proxy()
  {
    printf("Entering Proxy()\n");

    printf("Constructing Amiga...\n");
    amiga = new Amiga();

    printf("Adding listener...\n");
    amiga->msgQueue.setListener(amiga, &processMsg);

    printf("Launching emulator thread...\n");
    amiga->launch();

    printf("Configuring...\n");
    amiga->configure(OPT_AUDVOLL, 100);
    amiga->configure(OPT_AUDVOLR, 100);
    amiga->configure(OPT_AUDVOL, 0, 100);
    amiga->configure(OPT_AUDPAN, 0, 0);

    amiga->configure(OPT_CHIP_RAM, 512);
    amiga->configure(OPT_SLOW_RAM, 512);
    amiga->configure(OPT_AGNUS_REVISION, AGNUS_OCS);

    printf("Exiting Proxy()\n");
  }

  bool hasRom() const
  {
    return amiga->mem.hasRom();
  }

  bool hasExt() const
  {
    return amiga->mem.hasExt();
  }

  void pressLeft()
  {
    printf("pressLeft()\n");
  }
};

int main(int argc, char *argv[])
{
  printf("main()\n");
  return EXIT_SUCCESS;
}

EMSCRIPTEN_BINDINGS(vamiga)
{
  class_<Proxy>("Proxy")
      .constructor<>()
      .property("hasRom", &Proxy::hasRom)
      .property("hasExt", &Proxy::hasExt)
      .function("pressLeft", &Proxy::pressLeft)
  ;
}