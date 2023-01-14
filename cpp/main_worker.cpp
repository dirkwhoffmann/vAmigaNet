#include <emscripten/wasm_worker.h>
#include <stdio.h>

void run_in_worker()
{
  printf("Hello from wasm worker!\n");
}

int main()
{
  emscripten_wasm_worker_t worker = emscripten_malloc_wasm_worker(/*stack size: */1024);
  emscripten_wasm_worker_post_function_v(worker, run_in_worker);
}