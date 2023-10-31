cmake_minimum_required(VERSION 3.24)
project(sorts)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../../public)

if (WIN32)
    # Forcing MSVC to use utf-8 encoding
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif(WIN32)

add_executable(
    sorts
    src/main.cpp

    src/messaging/messaging.hpp
    src/messaging/messaging.cpp

    src/Application.hpp
    src/Application.cpp
    src/Sketch/Sketch.hpp
    src/Sketch/Sketch.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

if (NOT MSVC)
    target_compile_options(${PROJECT_NAME} PUBLIC "-O2")
endif()

if (DEFINED EMSCRIPTEN)
    #set(CMAKE_EXECUTABLE_SUFFIX ".html")
    add_compile_definitions("__EMSCRIPTEN__")
    target_link_options(${PROJECT_NAME} PRIVATE
        "-sMODULARIZE=1"
        "-sEXPORT_NAME='Main'"
        "-sINVOKE_RUN=0"
        "-sDISABLE_DEPRECATED_FIND_EVENT_TARGET_BEHAVIOR=0"
        "-sEXPORTED_FUNCTIONS=['_main']"
        "-sEXPORTED_RUNTIME_METHODS=['callMain', 'ccall', 'cwrap', 'UTF8ToString']"
        "-sFORCE_FILESYSTEM=1"
        "-sUSE_SDL=2"
        "-sALLOW_MEMORY_GROWTH=1" 
        "-sTOTAL_MEMORY=256MB"
        "-sASYNCIFY"
        "-O3"
    )
else()

    set(extra_flags "")
    if (NOT MSVC)
        set(extra_flags "-mconsole")
    endif()

    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS})
    target_link_libraries(flow ${SDL2_LIBRARIES})
endif()