/*********************************************************************/
/* $File: ProcessStringDLL.cpp                                       */
/*                                                                   */
/* Copyright (c) 2016-2026 nitishhsinghh. All rights reserved.      */
/* This material may be reproduced for teaching and learning        */
/* purposes only. It is not to be used in industry or for           */
/* commercial purposes.                                             */
/*                                                                   */
/* Class       - ProcessStringDLL                                   */
/*                                                                   */
/* Description - DLL wrapper exposing C++ string conversion engine  */
/*               for C# P/Invoke interoperability. Delegates calls  */
/*               to core ProcessString dispatcher.                  */
/*                                                                   */
/* Notes       - Interop layer between native C++ and .NET API      */
/*                                                                   */
/* $Log: ProcessStringDLL.cpp                                       */
/*                                                                   */
/*  Revision 1.0  2026/04/11  Nitish Singh                          */
/*  Initial implementation of DLL interop wrapper.                  */
/*                                                                   */
/*  Revision 1.1  2026/04/12  Nitish Singh                          */
/*  Refactored DLL wrapper for improved maintainability and safety. */
/*  Changes include:                                                 */
/*   - Introduced helper function allocateCString() for memory      */
/*     allocation and centralised C-string conversion logic.        */
/*   - Added mapConversionType() to isolate enum mapping logic.     */
/*   - Improved fallback handling to ensure safe memory allocation   */
/*     instead of returning raw input pointer.                      */
/*   - Restructured file using logical regions for clarity          */
/*     (Helper Utilities, Conversion Mapping, Exported API).        */
/*   - Reduced code duplication and improved readability.           */
/*                                                                   */
/*  Revision 1.2  2026/04/13  Nitish Singh                          */
/*  Added security gate to prevent buffer overflow attacks by enforcing */
/*  a 5 MB input size limit. This protects the DLL and the hosting      */
/*  process from malicious or accidental large inputs. If the input     */
/*  exceeds this limit, the function returns a deterministic error string */
/*  that the .NET layer can identify and handle appropriately.         */
/*  Revision 1.3  2026/04/18  Nitish Singh                          */
/*  Code Qualty clang-formatted                                      */
/*********************************************************************/

/*********************************************************************/
/* Dependencies                                                      */
/*********************************************************************/

#include "Client.hpp"
#include "ConversionTypeEnum.hpp"
#include "ProcessString.hpp"
#include "StringConversionFactory.hpp"

#include <cstdlib>
#include <cstring>
#include <string>

#include "ProcessStringDLL.hpp"

//===================================================================
// Constrants: 5 MB Buffer Limit
//===================================================================

/*
 *  Note: The 2 MB buffer limit is an arbitrary choice to prevent excessive
 * memory usage in the DLL. In a production scenario, you may want to implement
 * a more robust solution for handling large inputs, such as streaming
 * processing or dynamic buffer resizing. For the purposes of this example, we
 * will simply return an error message if the input exceeds this limit.
 *
 *  Secruity Gate: 2MB Buffer Limit
 *  Prevents Heap Exhaustion attacks and protects the Dcoker sidecar's
 *  memory footprint from malicious or accidental large inputs.
 *  This is a common best practice for C-style APIs that allocate memory based
 * on input size.
 */

#define MAX_INPUT_SIZE (5 * 1024 * 1024) // 5 MB

//===================================================================
// Helper Utilities (internal, not exported - C++ only)
//===================================================================

/**
 * @brief Allocates a C-string from std::string (heap memory)
 */
static char *allocateCString(const std::string &str) {
  char *output = static_cast<char *>(std::malloc(str.size() + 1));
  if (!output)
    return nullptr;

  std::memcpy(output, str.c_str(), str.size() + 1);
  return output;
}

//===================================================================
// Conversion Mapping (Internal - C++ only)
//===================================================================

/**
 * @brief Maps external conversion choice to internal type
 */
static bool mapConversionType(ConversionChoice choice, ConversionType &type) {

  switch (choice) {

  case ConversionChoice::Alternating:
    type = ConversionType::Alternating;
    return true;
  case ConversionChoice::Capitalize:
    type = ConversionType::Capitalize;
    return true;
  case ConversionChoice::Lower:
    type = ConversionType::Lower;
    return true;
  case ConversionChoice::Upper:
    type = ConversionType::Upper;
    return true;
  case ConversionChoice::Sentence:
    type = ConversionType::Sentence;
    return true;
  case ConversionChoice::Toggle:
    type = ConversionType::Toggle;
    return true;
  case ConversionChoice::Reverse:
    type = ConversionType::Reverse;
    return true;
  case ConversionChoice::RemoveVowels:
    type = ConversionType::RemoveVowels;
    return true;
  case ConversionChoice::RemoveSpaces:
    type = ConversionType::RemoveSpaces;
    return true;
  case ConversionChoice::InvertWords:
    type = ConversionType::InvertWords;
    return true;
  case ConversionChoice::SnakeCase:
    type = ConversionType::SnakeCase;
    return true;
  case ConversionChoice::KebabCase:
    type = ConversionType::KebabCase;
    return true;
  case ConversionChoice::LeetSpeak:
    type = ConversionType::LeetSpeak;
    return true;

  default:
    return false;
  }
}

//===================================================================
// Exported DLL API (Extern "C" for C# interop)
//===================================================================

/*
 * Important Notes on DLL API Design:
 *
 * 1. C-style interface: Extern "C" prevents name mangling.
 * 2. Memory management: Caller must free allocated memory.
 * 3. Input validation: Handles null and invalid inputs safely.
 * 4. Enum mapping: Keeps conversion logic isolated.
 *
 * Why this is required:
 *
 * The C++ engine uses modern constructs (std::string, strategy pattern),
 * which are not directly compatible with C# interop.
 *
 * This wrapper provides a stable C-style bridge for safe interop.
 *
 * Notes:
 * - Only C-style types (const char*) are exposed
 * - Caller must free memory using freeString()
 * - Core logic remains in C++ engine (single source of truth)
 */

extern "C" {

/**
 * @brief Main DLL entry point for C# string conversion
 */
API const char *processStringDLL(const char *input, int choiceInt) {

  if (!input) {
    return nullptr;
  }

  size_t inputLength = std::strlen(input);

  if (inputLength > MAX_INPUT_SIZE) {
    return allocateCString("ERROR_BUFFER_OVERFLOW_LIMIT_2MB");
  }

  Client client;
  ConversionChoice choice = static_cast<ConversionChoice>(choiceInt);

  ConversionType type;

  if (!mapConversionType(choice, type)) {
    return allocateCString(std::string(input));
  }

  client.setStrategy(StringConversionFactory::create(type));

  std::string result = client.execute(std::string(input));

  return allocateCString(result);
}

/**
 * @brief Frees memory allocated by processStringDLL
 *
 * Important: C# must call this to avoid memory leaks since DLL allocates
 * memory on the heap.
 *
 * This is a common pattern for C-style interop where the callee allocates
 * memory and the caller is responsible for freeing it.
 *
 */
API void freeString(char *str) { free(str); }

} // extern "C"