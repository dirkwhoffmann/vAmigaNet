target_include_directories(vAmigaCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(vAmigaCore PRIVATE

)

add_subdirectory(Drive)
add_subdirectory(Mouse)
add_subdirectory(Joystick)
add_subdirectory(Keyboard)
