cmake_minimum_required(VERSION 3.14)
project(ProcessStringDLL LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -----------------------------
# Include directories
# -----------------------------
include_directories(include)


# ---------------------------
# GoogleTest Setup
# ---------------------------
include(FetchContent)

# Force GoogleTest to use the same runtime on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)


FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/main.zip
)

# Make GoogleTest available
FetchContent_MakeAvailable(googletest)

enable_testing()

# -----------------------------
# Build the static library first
# -----------------------------
add_library(StringConversionLib STATIC
    src/AlternatingCaseConversion.cpp
    src/CapitalizeWordsConversion.cpp
    src/Client.cpp
    src/InvertWordsConversion.cpp
    src/KebabCaseConversion.cpp
    src/LeetSpeakConversion.cpp
    src/LowerCaseConversion.cpp
    src/ProcessString.cpp
    src/RemoveSpacesConversion.cpp
    src/RemoveVowelsConversion.cpp
    src/ReverseConversion.cpp
    src/SentenceCaseConversion.cpp
    src/SnakeCaseConversion.cpp
    src/StringConversionFactory.cpp
    src/ToggleCaseConversion.cpp
    src/UpperCaseConversion.cpp    
)

# static library to be used in shared library
set_target_properties(StringConversionLib PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_include_directories(StringConversionLib PUBLIC include)

# -----------------------------
# DLL target: ProcessStringDLL
# -----------------------------
add_library(ProcessStringDLL SHARED
    src/ProcessStringDLL.cpp
)

# Export macro for Windows DLL
target_compile_definitions(ProcessStringDLL PRIVATE PROCESSSTRING_EXPORTS)

# Link the DLL with the static library
target_link_libraries(ProcessStringDLL PRIVATE StringConversionLib)

# DLL output folder
set_target_properties(ProcessStringDLL PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

# -----------------------------
# DLL Tests
# -----------------------------
add_executable(ProcessStringDLLTests
    ../tests/CppTests/AdvStrTestDLL.cpp
)

# Link against DLL + gtest
target_link_libraries(ProcessStringDLLTests
    PRIVATE
    ProcessStringDLL
    gtest
    gtest_main
)

# Include headers
target_include_directories(ProcessStringDLLTests PRIVATE include)

# Register test
add_test(NAME DLLTests COMMAND ProcessStringDLLTests)