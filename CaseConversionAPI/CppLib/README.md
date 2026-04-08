# Case Conversion API

A C++ library and application for converting strings into various cases, including Alternating, Capitalize, Lower, Upper, Sentence, Toggle, Reverse, RemoveVowels, RemoveSpaces, InvertWords, SnakeCase, KebabCase, and LeetSpeak.

## Features

- Modular C++ library for string conversions
- Main application to interactively test conversions
- Unit tests using GoogleTest framework
- Supports multiple conversion strategies

## Project Structure

```Bash

CaseConversionAPI/
├── CppLib/
│ ├── include/ # Header files
│ ├── src/ # Source files
│ ├── tests/CppTests/ # GoogleTest unit tests
│ ├── CMakeLists.txt
│ └── run.sh # Script to build and run app/tests
└── README.md

```

## Running the Application

A convenient script `run.sh` is provided to build the project and run both the main application and tests.

### Steps

1.Make the script executable** (only need to do this once):

```bash
cd CaseConversionAPI/CppLib
chmod +x run.sh
```

2.Run the application and tests

```Bash
./run.sh
```

This script will:

- Create the build directory if it doesn’t exist
- Configure and build the project using CMake
- Run the main application (app)
- Run all unit tests (runTests)

## Running manually

Alternatively, you can run manually:

```Bash
mkdir -p build
cd build
cmake ..
cmake --build . --config Release

# Run the application
./app

# Run unit tests
./runTests
```

## Main Application Usage

When running the app:

```Bash
Enter string: hello world
1: Alternating, 2: Capitalize, 3: Lower, 4: Upper, 5: Sentence, 6: Toggle, 7: Reverse, 8: RemoveVowels, 9: RemoveSpaces, 10: InvertWords, 11: SnakeCase, 12: KebabCase, 13: LeetSpeak
```

- Enter the string you want to convert
- Enter the choice number corresponding to the conversion strategy
- Result will be printed on the console

Running Tests

Unit tests are built with GoogleTest. Running ./runTests will execute all test suites and display results:

```Bash
[==========] Running 34 tests from 19 test suites.
[  PASSED  ] 34 tests.
```

## Git Setup and .gitignore

To properly manage this project with Git:

1. **Initialize Git** (if not already initialized):

```bash
git init
```

2.Add the remote repository (replace with your repo URL):

```Bash
git remote add origin https://github.com/nitishhsinghhh/case-conversion-api.git
```

3.Create a .gitignore file in the root of the project:

```Bash
touch .gitignore
```

4.Add common C++ / CMake ignore rules. Example contents:

```Bash
# Build directories
/build/
/bin/
/lib/

# CMake files
CMakeFiles/
CMakeCache.txt
cmake_install.cmake
Makefile

# OS-specific files
.DS_Store
Thumbs.db

# IDE files
*.vcxproj*
*.sln
*.user
*.idea/
*.vscode/
```

5.Stage and commit changes:

```Bash
git add .
git commit -m "Add project files and .gitignore"
```

6.Push to remote repository:

```Bash
git push -u origin main
```

After this, Git will ignore all the files and folders specified in .gitignore, keeping your repository clean and only tracking source and configuration files.
