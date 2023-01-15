cmake_minimum_required(VERSION 3.16)

project(vAmiga C CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS False)

add_executable(vAmiga main.cpp)


target_compile_options(vAmiga PRIVATE -s USE_SDL=2)
target_compile_options(vAmiga PRIVATE -Wall -Werror)
target_compile_options(vAmiga PRIVATE -Wno-unused-parameter)
target_compile_options(vAmiga PRIVATE -O3 -mnontrapping-fptoint -fwasm-exceptions)
target_compile_options(vAmiga PRIVATE -Wfatal-errors)

add_subdirectory("emulator" "vAmigaCore")
target_link_libraries(vAmiga vAmigaCore)

# Emscripten linker settings
set(LF_MEM   "-s INITIAL_MEMORY=320MB -s TOTAL_STACK=32MB -s ALLOW_MEMORY_GROWTH=1")
set(LF_OPTI  "-O3 -mnontrapping-fptoint -fwasm-exceptions")
# set(LF_SHELL "--shell-file ../shell.html")
set(LF_SDL2  "-s USE_SDL=2 -s USE_WEBGL2=1 -s MAX_WEBGL_VERSION=2")
set(LF_EXPORTS "-s EXPORTED_RUNTIME_METHODS=['cwrap','ccall'] -s EXPORTED_FUNCTIONS=\"['_free','_main']\"")
set(LF_OTHER  "-s DISABLE_DEPRECATED_FIND_EVENT_TARGET_BEHAVIOR=1  -s LLD_REPORT_UNDEFINED -s ASSERTIONS=0 -s GL_ASSERTIONS=0")

set_target_properties(vAmiga PROPERTIES LINK_FLAGS "${LF_SHELL} ${LF_OPTI} ${LF_MEM} ${LF_SDL2} ${LF_EXPORTS} ${LF_OTHER}" )
set(CMAKE_EXECUTABLE_SUFFIX ".html")


# Run local webserver
add_custom_target(run
    COMMAND ${CMAKE_COMMAND} -E copy vAmiga.html ../index.html
    COMMAND ${CMAKE_COMMAND} -E copy vAmiga.js ..
    COMMAND ${CMAKE_COMMAND} -E copy vAmiga.wasm ..
    COMMAND ${CMAKE_COMMAND} -E chdir .. python3 -m http.server 8080
	DEPENDS vAmiga
)


# Publish complete build to a gh-pages folder
set(PUBLISH_FOLDER "../../vAmigaWeb.github.io")
add_custom_target(publish
	COMMAND ${CMAKE_COMMAND} -E rm -rf ${PUBLISH_FOLDER}/roms
	COMMAND ${CMAKE_COMMAND} -E rm -rf ${PUBLISH_FOLDER}/sounds
	COMMAND ${CMAKE_COMMAND} -E rm -rf ${PUBLISH_FOLDER}/css
	COMMAND ${CMAKE_COMMAND} -E rm -rf ${PUBLISH_FOLDER}/js
	COMMAND ${CMAKE_COMMAND} -E rm -rf ${PUBLISH_FOLDER}/img
	COMMAND ${CMAKE_COMMAND} -E rm -f  ${PUBLISH_FOLDER}/vC64.*
	COMMAND ${CMAKE_COMMAND} -E rm -f  ${PUBLISH_FOLDER}/*.js
	COMMAND ${CMAKE_COMMAND} -E rm -f  ${PUBLISH_FOLDER}/*.json
	COMMAND ${CMAKE_COMMAND} -E rm -f  ${PUBLISH_FOLDER}/index.html
	COMMAND ${CMAKE_COMMAND} -E rm -f  ${PUBLISH_FOLDER}/run.html
	COMMAND ${CMAKE_COMMAND} -E copy vAmiga.html ${PUBLISH_FOLDER}/index.html
    COMMAND ${CMAKE_COMMAND} -E copy vAmiga.js ${PUBLISH_FOLDER}
	COMMAND ${CMAKE_COMMAND} -E copy vAmiga.wasm ${PUBLISH_FOLDER}
	COMMAND ${CMAKE_COMMAND} -E copy_directory ../js ${PUBLISH_FOLDER}/js
	COMMAND ${CMAKE_COMMAND} -E copy_directory ../css ${PUBLISH_FOLDER}/css
	COMMAND ${CMAKE_COMMAND} -E copy_directory ../img ${PUBLISH_FOLDER}/img
	COMMAND ${CMAKE_COMMAND} -E copy_directory ../roms ${PUBLISH_FOLDER}/roms
	COMMAND ${CMAKE_COMMAND} -E copy_directory ../sounds ${PUBLISH_FOLDER}/sounds
	COMMAND ${CMAKE_COMMAND} -E copy ../run.html ${PUBLISH_FOLDER}
	COMMAND ${CMAKE_COMMAND} -E copy ../sw.js ${PUBLISH_FOLDER}
	COMMAND ${CMAKE_COMMAND} -E copy ../manifest.json ${PUBLISH_FOLDER}
	DEPENDS vAmiga
)

set(UAT_FOLDER "../../uat")
add_custom_target(uat
	COMMAND ${CMAKE_COMMAND} -E rm -rf ${UAT_FOLDER}/sounds
	COMMAND ${CMAKE_COMMAND} -E rm -rf ${UAT_FOLDER}/roms
	COMMAND ${CMAKE_COMMAND} -E rm -rf ${UAT_FOLDER}/css
	COMMAND ${CMAKE_COMMAND} -E rm -rf ${UAT_FOLDER}/js
	COMMAND ${CMAKE_COMMAND} -E rm -rf ${UAT_FOLDER}/img
	COMMAND ${CMAKE_COMMAND} -E rm -f  ${UAT_FOLDER}/vC64.*
	COMMAND ${CMAKE_COMMAND} -E rm -f  ${UAT_FOLDER}/*.js
	COMMAND ${CMAKE_COMMAND} -E rm -f  ${UAT_FOLDER}/index.html
	COMMAND ${CMAKE_COMMAND} -E rm -f  ${UAT_FOLDER}/run.html
	COMMAND ${CMAKE_COMMAND} -E copy vAmiga.html ${UAT_FOLDER}/index.html
    COMMAND ${CMAKE_COMMAND} -E copy vAmiga.js ${UAT_FOLDER}
	COMMAND ${CMAKE_COMMAND} -E copy vAmiga.wasm ${UAT_FOLDER}
	COMMAND ${CMAKE_COMMAND} -E copy_directory ../js ${UAT_FOLDER}/js
	COMMAND ${CMAKE_COMMAND} -E copy_directory ../css ${UAT_FOLDER}/css
	COMMAND ${CMAKE_COMMAND} -E copy_directory ../img ${UAT_FOLDER}/img
	COMMAND ${CMAKE_COMMAND} -E copy_directory ../roms ${UAT_FOLDER}/roms
	COMMAND ${CMAKE_COMMAND} -E copy_directory ../sounds ${UAT_FOLDER}/sounds
	COMMAND ${CMAKE_COMMAND} -E copy ../run.html ${UAT_FOLDER}
	COMMAND ${CMAKE_COMMAND} -E copy ../sw.js ${UAT_FOLDER}
	DEPENDS vAmiga
)
