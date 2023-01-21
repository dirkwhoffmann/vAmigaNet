cmake_minimum_required(VERSION 3.16)

project(vAmiga C CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS False)

add_executable(vAmiga main.cpp Proxy.cpp)

target_compile_options(vAmiga PRIVATE -O1)
target_compile_options(vAmiga PRIVATE -sWASM_WORKERS)
target_compile_options(vAmiga PRIVATE -Wall -Werror -Wfatal-errors)
target_compile_options(vAmiga PRIVATE -Wno-unused-parameter)
target_compile_options(vAmiga PRIVATE -mnontrapping-fptoint -fwasm-exceptions)

add_subdirectory("emulator")
target_link_libraries(vAmiga vAmigaCore)

# Emscripten linker settings
set(LF_MEM "-sINITIAL_MEMORY=512MB -sTOTAL_STACK=32MB -sALLOW_MEMORY_GROWTH=0")
set(LF_OPTI "-O1 -mnontrapping-fptoint -fwasm-exceptions")
set(LF_EXPORTS "-lembind -sEXPORT_EXCEPTION_HANDLING_HELPERS")
set(LF_THREAD "-pthread -sPTHREAD_POOL_SIZE=1 -sWASM_WORKERS")
set(LF_DEBUG "-sASSERTIONS=0 -sGL_ASSERTIONS=0")
set(LF_OTHER "-sWASM_BIGINT -sDISABLE_DEPRECATED_FIND_EVENT_TARGET_BEHAVIOR=1 -sLLD_REPORT_UNDEFINED")

set_target_properties(vAmiga PROPERTIES LINK_FLAGS "${LF_MEM} ${LF_OPTI} ${LF_EXPORTS} ${LF_THREAD} ${LF_DEBUG} ${LF_OTHER}" )
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
