import { writable } from 'svelte/store';

/**
 * the vAmiga object is the Module of the emsdk is setup in +layout.svelte onmount()
 * the emsdk doc says...
 * Module is a global JavaScript object with attributes that Emscripten-generated code calls at various points in its execution.
 * Developers can provide an implementation of Module to control the execution of code. For example, to define how notification messages from Emscripten are displayed, developers implement the Module.print attribute.
 * When an Emscripten application starts up it looks at the values on the Module object and applies them. Note that changing the values after startup will not work in general.
 */
export const vAmiga:any = writable({});
export const proxy:any = writable({});
export const retroShell:any = writable({});