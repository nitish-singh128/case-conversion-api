/***************************************************************************************************
 * File        : ProcessStringDLL.cpp
 *
 * Copyright   : (c) 2016–2026 nitishhsinghh. All rights reserved.
 *               This material may be reproduced for teaching and learning purposes only.
 *               It is not to be used in industry or for commercial purposes.
 *
 * Class       : ProcessStringDLL
 *
 * Description : DLL wrapper exposing C++ string conversion engine for C# P/Invoke interoperability.
 *               Delegates calls to the core ProcessString dispatcher.
 *
 * Notes       : Interop layer between native C++ and .NET API.
 *
 /***************************************************************************************************
 * Revision History
 * -------------------------------------------------------------------------------------------------
 * Version   Date         Author         Description
 * --------  -----------  -------------  -----------------------------------------------------------
 * 1.0       2026/04/11   Nitish Singh   Initial implementation of DLL interop wrapper.
 * 1.1       2026/04/12   Nitish Singh   Refactored for maintainability and safety.
 * 1.2       2026/04/13   Nitish Singh   Added 5MB security gate to prevent buffer overflow.
 * 1.3       2026/04/18   Nitish Singh   Applied clang-format for code quality.
 * 1.4       2026/04/18   Nitish Singh   Added traceId for distributed tracing (OpenTelemetry).
 * 1.5       2026/04/28   Nitish Singh   Reformatted header for alignment and consistency.
 * 1.6       2026/04/28   Nitish Singh   Hardened DLL API with exception safety, deterministic
 *                                      error handling, constexpr limits, and improved memory safety.
 ***************************************************************************************************/

/***************************************************************************************************
 * Dependencies
 * -------------------------------------------------------------------------------------------------
 * External and internal headers required for ProcessStringDLL implementation.
 ***************************************************************************************************/

// 1. Corresponding header FIRST
#include "ProcessStringDLL.hpp"   

// 2. Project headers
#include "Client.hpp"
#include "ConversionTypeEnum.hpp"
#include "ProcessString.hpp"
#include "StringConversionFactory.hpp"

// 3. Standard library headers
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>

//===================================================================
// Constrants: 5 MB Buffer Limit
//===================================================================

/*
 *  Note: The 5 MB buffer limit is an arbitrary choice to prevent excessive
 * memory usage in the DLL. In a production scenario, you may want to implement
 * a more robust solution for handling large inputs, such as streaming
 * processing or dynamic buffer resizing. For the purposes of this example, we
 * will simply return an error message if the input exceeds this limit.
 */

namespace {
constexpr size_t MAX_INPUT_SIZE = 5 * 1024 * 1024; // 5 MB
}

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

/**
 * @brief Safe wrapper to always return a valid error string
 */
static const char* safeError(const char* msg) {
    char* err = allocateCString(msg);
    return err ? err : "FATAL_ALLOCATION_FAILURE";
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
API const char* processStringDLL(const char* input, int choiceInt,
                                 const char* traceId) {
    
    //===== Input Validation and Security Gate =====

    try {
        if (!input) {
            return safeError("ERROR_NULL_INPUT");
        }

        size_t inputLength = std::strlen(input);

        if (inputLength > MAX_INPUT_SIZE) {
            return safeError("ERROR_BUFFER_OVERFLOW_LIMIT_5MB");
        }
        
        ConversionChoice choice = static_cast<ConversionChoice>(choiceInt);
        ConversionType type;

        if (!mapConversionType(choice, type)) {

            std::cout << "Received invalid conversion choice: " << choiceInt << std::endl;
            // Explicit check for negative choices before mapping
            if (choiceInt < 0) {
                return safeError("ERROR_NEGATIVE_CONVERSION_CHOICE");
            } 
            else {
                return safeError("ERROR_INVALID_CONVERSION_CHOICE");
            }
              
        }

        Client client;

        if (traceId) {
          client.setTraceId(traceId);
        }

        client.setStrategy(StringConversionFactory::create(type));

        std::string result = client.execute(std::string(input));

        // Note: allocateCString returns nullptr on allocation failure, which is handled by safeError
        char* output = allocateCString(result);
        if (!output) {
            return safeError("FATAL_ALLOCATION_FAILURE");
        }

        return output;

    } catch (const std::exception& e) {
        return safeError("ERROR_INTERNAL_EXCEPTION_STD");
    }
    catch (...) {
        return safeError("ERROR_INTERNAL_EXCEPTION_UNKNOWN");
    }
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