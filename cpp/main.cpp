#include <stdio.h>
#include <emscripten.h>
#include <cstdlib>

unsigned counter=0;
int main()
{
  printf("Hello I am the vAmiga hull 3!\n");
  return EXIT_SUCCESS;
}

extern "C" unsigned wasm_get_cpu_cycles()
{
  printf("wasm_get_cpu_cycles()= %u\n", counter);
  return counter++;
}
