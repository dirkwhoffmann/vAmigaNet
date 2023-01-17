#include <emscripten.h>
#include <emscripten/wasm_worker.h>
#include <emscripten/bind.h>

#include "config.h"
#include "Amiga.h"

using namespace emscripten;
using namespace vamiga;

Amiga *amiga = nullptr;

void processMsg(const void *amiga, long id, int data1, int data2, int data3, int data4);

class AmigaProxy
{
public:
  AmigaProxy();
  bool hasRom() const;
  bool hasExt() const;
};

class RetroShellProxy
{
public:
  RetroShellProxy();
  void pressUp();
  void pressDown();
  void pressLeft();
  void pressRight();
};