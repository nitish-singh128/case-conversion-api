cmake_minimum_required(VERSION 3.14)
project(ProcessStringDLL LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# CMakeLists.txt
include(CMakeListsLocalApp.txt)

# -----------------------------
# Include directories
# -----------------------------
include_directories(include)

# -----------------------------
# DLL target: ProcessStringDLL
# -----------------------------
add_library(ProcessStringDLL SHARED
    src/ProcessStringDLL.cpp
)

# Define export macro for Windows DLL
target_compile_definitions(ProcessStringDLL PRIVATE PROCESSSTRING_EXPORTS)

# DLL output folder
set_target_properties(ProcessStringDLL PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

# Optional: add version info or other properties here