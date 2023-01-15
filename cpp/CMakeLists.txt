cmake_minimum_required(VERSION 3.16)

project(vAmiga C CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS False)

add_executable(vAmiga main.cpp)

target_compile_options(vAmiga PRIVATE -sWASM_WORKERS)
target_compile_options(vAmiga PRIVATE -Wall -Werror)
target_compile_options(vAmiga PRIVATE -Wno-unused-parameter)
target_compile_options(vAmiga PRIVATE -O3 -mnontrapping-fptoint -fwasm-exceptions)
target_compile_options(vAmiga PRIVATE -Wfatal-errors)

add_subdirectory("emulator" "vAmigaCore")
target_link_libraries(vAmiga vAmigaCore)

# Emscripten linker settings
set(LF_MEM   "-s INITIAL_MEMORY=320MB -s TOTAL_STACK=32MB -s ALLOW_MEMORY_GROWTH=1")
set(LF_OPTI  "-O0 -mnontrapping-fptoint -fwasm-exceptions")
set(LF_EXPORTS "-s EXPORTED_RUNTIME_METHODS=['cwrap','ccall'] -s EXPORTED_FUNCTIONS=\"['_free','_main']\"")
set(LF_OTHER  "-sWASM_WORKERS -s DISABLE_DEPRECATED_FIND_EVENT_TARGET_BEHAVIOR=1  -s LLD_REPORT_UNDEFINED -s ASSERTIONS=0 -s GL_ASSERTIONS=0")

set_target_properties(vAmiga PROPERTIES LINK_FLAGS "${LF_OPTI} ${LF_MEM} ${LF_EXPORTS} ${LF_OTHER}" )
set(CMAKE_EXECUTABLE_SUFFIX ".js")

set(PUBLISH_FOLDER "${CMAKE_SOURCE_DIR}/../static")

# Run a local webserver
add_custom_target(run
	COMMAND ${CMAKE_COMMAND} -E copy vAmiga.* ${PUBLISH_FOLDER}
	COMMAND ${CMAKE_COMMAND} -E chdir .. python3 -m http.server 8080
	DEPENDS vAmiga
)

# Publish complete build to a gh-pages folder
add_custom_target(static
	COMMAND ${CMAKE_COMMAND} -E copy vAmiga.* ${PUBLISH_FOLDER}
    DEPENDS vAmiga
)
