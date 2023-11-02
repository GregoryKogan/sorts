cmake_minimum_required(VERSION 3.24)
project(sorts)

set(CMAKE_CXX_STANDARD 20)

if (WIN32)
    # Forcing MSVC to use utf-8 encoding
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif(WIN32)

if (DEFINED EMSCRIPTEN)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../../public)

    add_executable(
        sorts
        src/sdl2_app/main.cpp

        src/sdl2_app/messaging/messaging.hpp
        src/sdl2_app/messaging/messaging.cpp

        src/sdl2_app/Application.hpp
        src/sdl2_app/Application.cpp
        src/sdl2_app/Sketch/Sketch.hpp
        src/sdl2_app/Sketch/Sketch.cpp

        src/libs/exception_lib/exception_lib.hpp
        src/libs/exception_lib/exception_lib.cpp
        src/libs/exception_lib/IO/colored_logs.hpp
        src/libs/exception_lib/IO/colored_logs.cpp
        src/libs/exception_lib/exceptions/BaseException.hpp
        src/libs/exception_lib/exceptions/BaseException.cpp
        src/libs/exception_lib/exceptions/AssertionFailedException/AssertionFailedException.hpp
        src/libs/exception_lib/exceptions/AssertionFailedException/AssertionFailedException.cpp
        src/libs/exception_lib/exceptions/EmptyContainerException/EmptyContainerException.hpp
        src/libs/exception_lib/exceptions/EmptyContainerException/EmptyContainerException.cpp
        src/libs/exception_lib/exceptions/EmptyPointerException/EmptyPointerException.hpp
        src/libs/exception_lib/exceptions/EmptyPointerException/EmptyPointerException.cpp
        src/libs/exception_lib/exceptions/IndexOutOfRangeException/IndexOutOfRangeException.hpp
        src/libs/exception_lib/exceptions/IndexOutOfRangeException/IndexOutOfRangeException.cpp
        src/libs/exception_lib/exceptions/InvalidArgumentException/InvalidArgumentException.hpp
        src/libs/exception_lib/exceptions/InvalidArgumentException/InvalidArgumentException.cpp
        src/libs/exception_lib/exceptions/ZeroReferenceDecrementException/ZeroReferenceDecrementException.hpp
        src/libs/exception_lib/exceptions/ZeroReferenceDecrementException/ZeroReferenceDecrementException.cpp
        src/libs/exception_lib/exceptions/OutOfComparisonsException/OutOfComparisonsException.hpp
        src/libs/exception_lib/exceptions/OutOfComparisonsException/OutOfComparisonsException.cpp
        src/libs/exception_lib/exceptions/OutOfSwapsException/OutOfSwapsException.hpp
        src/libs/exception_lib/exceptions/OutOfSwapsException/OutOfSwapsException.cpp

        src/sorts/smart_sequences/smart_pointers/ControlBlock/ControlBlock.hpp
        src/sorts/smart_sequences/smart_pointers/ControlBlock/ControlBlock.hh
        src/sorts/smart_sequences/smart_pointers/SharedPtr/SharedPtr.hpp
        src/sorts/smart_sequences/smart_pointers/SharedPtr/SharedPtr.hh
        src/sorts/smart_sequences/smart_pointers/UniquePtr/UniquePtr.hpp
        src/sorts/smart_sequences/smart_pointers/UniquePtr/UniquePtr.hh
        src/sorts/smart_sequences/smart_pointers/WeakPtr/WeakPtr.hpp
        src/sorts/smart_sequences/smart_pointers/WeakPtr/WeakPtr.hh

        src/sorts/smart_sequences/data_structures/SmartPtrDynamicArray/SmartPtrDynamicArray.hpp
        src/sorts/smart_sequences/data_structures/SmartPtrDynamicArray/SmartPtrDynamicArray.hh
        src/sorts/smart_sequences/data_structures/SmartPtrLinkedList/SmartPtrLinkedList.hpp
        src/sorts/smart_sequences/data_structures/SmartPtrLinkedList/SmartPtrLinkedList.hh

        src/sorts/smart_sequences/sequences/SmartPtrSequence.hpp
        src/sorts/smart_sequences/sequences/SmartPtrArraySequence/SmartPtrArraySequence.hpp
        src/sorts/smart_sequences/sequences/SmartPtrArraySequence/SmartPtrArraySequence.hh
        src/sorts/smart_sequences/sequences/SmartPtrLinkedListSequence/SmartPtrLinkedListSequence.hpp
        src/sorts/smart_sequences/sequences/SmartPtrLinkedListSequence/SmartPtrLinkedListSequence.hh

        src/sorts/sorters/BaseSorter.hpp
        src/sorts/sorters/BaseSorter.hh
        src/sorts/sorters/BubbleSorter/BubbleSorter.hpp
        src/sorts/sorters/BubbleSorter/BubbleSorter.hh
        src/sorts/sorters/SelectionSorter/SelectionSorter.hpp
        src/sorts/sorters/SelectionSorter/SelectionSorter.hh   
        src/sorts/sorters/InsertionSorter/InsertionSorter.hpp
        src/sorts/sorters/InsertionSorter/InsertionSorter.hh
    )

    target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

    if (NOT MSVC)
        target_compile_options(${PROJECT_NAME} PUBLIC "-O2")
    endif()

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
    add_executable(
        test
        src/tests/test.cpp

        src/libs/exception_lib/exception_lib.hpp
        src/libs/exception_lib/exception_lib.cpp
        src/libs/exception_lib/IO/colored_logs.hpp
        src/libs/exception_lib/IO/colored_logs.cpp
        src/libs/exception_lib/exceptions/BaseException.hpp
        src/libs/exception_lib/exceptions/BaseException.cpp
        src/libs/exception_lib/exceptions/AssertionFailedException/AssertionFailedException.hpp
        src/libs/exception_lib/exceptions/AssertionFailedException/AssertionFailedException.cpp
        src/libs/exception_lib/exceptions/EmptyContainerException/EmptyContainerException.hpp
        src/libs/exception_lib/exceptions/EmptyContainerException/EmptyContainerException.cpp
        src/libs/exception_lib/exceptions/EmptyPointerException/EmptyPointerException.hpp
        src/libs/exception_lib/exceptions/EmptyPointerException/EmptyPointerException.cpp
        src/libs/exception_lib/exceptions/IndexOutOfRangeException/IndexOutOfRangeException.hpp
        src/libs/exception_lib/exceptions/IndexOutOfRangeException/IndexOutOfRangeException.cpp
        src/libs/exception_lib/exceptions/InvalidArgumentException/InvalidArgumentException.hpp
        src/libs/exception_lib/exceptions/InvalidArgumentException/InvalidArgumentException.cpp
        src/libs/exception_lib/exceptions/ZeroReferenceDecrementException/ZeroReferenceDecrementException.hpp
        src/libs/exception_lib/exceptions/ZeroReferenceDecrementException/ZeroReferenceDecrementException.cpp
        src/libs/exception_lib/exceptions/OutOfComparisonsException/OutOfComparisonsException.hpp
        src/libs/exception_lib/exceptions/OutOfComparisonsException/OutOfComparisonsException.cpp
        src/libs/exception_lib/exceptions/OutOfSwapsException/OutOfSwapsException.hpp
        src/libs/exception_lib/exceptions/OutOfSwapsException/OutOfSwapsException.cpp

        src/libs/test_lib/test_lib.hpp
        src/libs/test_lib/test_lib.cpp
        src/libs/test_lib/tests/Test.hpp
        src/libs/test_lib/tests/Test.cpp
        src/libs/test_lib/tests/Tester.hpp
        src/libs/test_lib/tests/Tester.cpp
        src/libs/test_lib/tests/TestSuite.hpp
        src/libs/test_lib/tests/TestSuite.cpp

        src/sorts/smart_sequences/smart_pointers/ControlBlock/ControlBlock.hpp
        src/sorts/smart_sequences/smart_pointers/ControlBlock/ControlBlock.hh
        src/sorts/smart_sequences/smart_pointers/SharedPtr/SharedPtr.hpp
        src/sorts/smart_sequences/smart_pointers/SharedPtr/SharedPtr.hh
        src/sorts/smart_sequences/smart_pointers/UniquePtr/UniquePtr.hpp
        src/sorts/smart_sequences/smart_pointers/UniquePtr/UniquePtr.hh
        src/sorts/smart_sequences/smart_pointers/WeakPtr/WeakPtr.hpp
        src/sorts/smart_sequences/smart_pointers/WeakPtr/WeakPtr.hh

        src/sorts/smart_sequences/data_structures/SmartPtrDynamicArray/SmartPtrDynamicArray.hpp
        src/sorts/smart_sequences/data_structures/SmartPtrDynamicArray/SmartPtrDynamicArray.hh
        src/sorts/smart_sequences/data_structures/SmartPtrLinkedList/SmartPtrLinkedList.hpp
        src/sorts/smart_sequences/data_structures/SmartPtrLinkedList/SmartPtrLinkedList.hh

        src/sorts/smart_sequences/sequences/SmartPtrSequence.hpp
        src/sorts/smart_sequences/sequences/SmartPtrArraySequence/SmartPtrArraySequence.hpp
        src/sorts/smart_sequences/sequences/SmartPtrArraySequence/SmartPtrArraySequence.hh
        src/sorts/smart_sequences/sequences/SmartPtrLinkedListSequence/SmartPtrLinkedListSequence.hpp
        src/sorts/smart_sequences/sequences/SmartPtrLinkedListSequence/SmartPtrLinkedListSequence.hh

        src/sorts/sorters/BaseSorter.hpp
        src/sorts/sorters/BaseSorter.hh
        src/sorts/sorters/BubbleSorter/BubbleSorter.hpp
        src/sorts/sorters/BubbleSorter/BubbleSorter.hh
        src/sorts/sorters/SelectionSorter/SelectionSorter.hpp
        src/sorts/sorters/SelectionSorter/SelectionSorter.hh

        src/tests/SharedPtr_tests/SharedPtr_tests.hpp
        src/tests/SharedPtr_tests/SharedPtr_tests.cpp
        src/tests/UniquePtr_tests/UniquePtr_tests.hpp
        src/tests/UniquePtr_tests/UniquePtr_tests.cpp
        src/tests/WeakPtr_tests/WeakPtr_tests.hpp
        src/tests/WeakPtr_tests/WeakPtr_tests.cpp

        src/tests/SmartPtrArraySequence_tests/SmartPtrArraySequence_tests.hpp
        src/tests/SmartPtrArraySequence_tests/SmartPtrArraySequence_tests.cpp
        src/tests/SmartPtrDynamicArray_tests/SmartPtrDynamicArray_tests.hpp
        src/tests/SmartPtrDynamicArray_tests/SmartPtrDynamicArray_tests.cpp
        src/tests/SmartPtrLinkedList_tests/SmartPtrLinkedList_tests.hpp
        src/tests/SmartPtrLinkedList_tests/SmartPtrLinkedList_tests.cpp
        src/tests/SmartPtrLinkedListSequence_tests/SmartPtrLinkedListSequence_tests.hpp
        src/tests/SmartPtrLinkedListSequence_tests/SmartPtrLinkedListSequence_tests.cpp

        src/tests/BubbleSorter_tests/BubbleSorter_tests.hpp
        src/tests/BubbleSorter_tests/BubbleSorter_tests.cpp
        src/tests/SelectionSorter_tests/SelectionSorter_tests.hpp
        src/tests/SelectionSorter_tests/SelectionSorter_tests.cpp
    )

    set(extra_flags "")
    if (NOT MSVC)
        set(extra_flags "-mconsole")
    endif()

    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS})
    target_link_libraries(test ${SDL2_LIBRARIES})
endif()