#!/bin/bash

# Make sure Emscripten is installed and activated
# source ~/emsdk/emsdk_env.sh

echo "Building P_Lang WebAssembly..."

emcc plang_compiler_wasm.c \
    -o docs/plang. js \
    -s WASM=1 \
    -s EXPORTED_FUNCTIONS='["_init_compiler", "_run_plang", "_clear_output", "_get_output", "_malloc", "_free"]' \
    -s EXPORTED_RUNTIME_METHODS='["ccall", "cwrap", "allocateUTF8", "UTF8ToString"]' \
    -s ALLOW_MEMORY_GROWTH=1 \
    -s MODULARIZE=0 \
    -O2

echo "Build complete!  Files generated in docs/"
echo "  - docs/plang.js"
echo "  - docs/plang.wasm"