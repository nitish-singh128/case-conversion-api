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
/*********************************************************************/


/*********************************************************************/
/* Dependencies                                                      */
/*********************************************************************/

#include "ProcessString.hpp"
#include "Client.hpp"
#include "StringConversionFactory.hpp"
#include "ConversionTypeEnum.hpp"

#include <string>
#include <cstring>
#include <cstdlib>

#include "ProcessStringDLL.hpp"

//===================================================================
// Constrants: 2 MB Buffer Limit
//===================================================================

/*
*  Note: The 2 MB buffer limit is an arbitrary choice to prevent excessive memory usage in the DLL.
*  In a production scenario, you may want to implement a more robust solution for handling large inputs,
*  such as streaming processing or dynamic buffer resizing. For the purposes of this example, 
*  we will simply return an error message if the input exceeds this limit.
*
*  Secruity Gate: 2MB Buffer Limit
*  Prevents Heap Exhaustion attacks and protects the Dcoker sidecar's
*  memory footprint from malicious or accidental large inputs. 
*  This is a common best practice for C-style APIs that allocate memory based on input size.
*/

#define MAX_INPUT_SIZE (2 * 1024 * 1024) // 2 MB


//===================================================================
// Helper Utilities (internal, not exported - C++ only)
//===================================================================

/**
 * @brief Allocates a C-string from std::string (heap memory)
 */
static char* allocateCString(const std::string& str) {
    char* output = (char*)malloc(str.size() + 1);
    if (!output) return nullptr;

    strcpy(output, str.c_str());
    return output;
}

//===================================================================
// Conversion Mapping (Internal - C++ only)
//===================================================================

/**
 * @brief Maps external conversion choice to internal type
 */
static bool mapConversionType(ConversionChoice choice, ConversionType& type) {

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
*   Important Notes on DLL API Design:
*   1. C-style interface: Extern "C" is used to prevent name
*      mangling and ensure compatibility with C# P/Invoke. 
*      Ensures the exported function has a predictable name and calling convention.
*      (e.g., "ProcessStringDLL" instead of a mangled C++ name like "_Z15ProcessStringDLLPKc").
*
*   2. Memory management: The DLL allocates memory for the output
*      string, and the caller (C#) is responsible for freeing it
*      using the provided freeString function. This is a common pattern
*      for C-style interop where the callee allocates memory and the
*      caller is responsible for freeing it.
*
*   3. Input validation: The function checks for null input and handles
*      invalid conversion choices gracefully by returning a copy of the
*      original string. This ensures that the API is robust and does not
*      crash on invalid input.
*
*   4. Enum mapping: The mapConversionType function isolates the logic for
*      mapping external conversion choices (from C#) to internal types
*      used by the C++ engine. This separation of concerns improves maintainability.
*
/*
*   Why this is required:
*   The C++ string conversion engine is designed with modern C++ features
*   and patterns (e.g., unique_ptr, std::string, strategy pattern).
*   However, C# cannot directly call C++ functions that use these features
*   due to differences in memory management and calling conventions.
*   By providing a C-style interface (processStringDLL), we create a bridge
*   that allows C# to leverage the powerful C++ engine while maintaining a simple and safe API contract.
*
*   This design allows us to keep the core C++ code clean and modern, while still providing interoperability with C#. 
*   It also ensures that we can handle memory management correctly across the language boundary, which is crucial for 
*   preventing leaks and crashes.
*
*
*   Note:
*     - Only C-style types (e.g., const char*) are used in the exported function signature to ensure compatibility with C#.
*     - The function returns a newly allocated C-string that the caller must free using freeString to avoid memory leaks.
*     - The internal logic of the function delegates to the existing C++ string conversion engine, ensuring that we do 
*        not duplicate code and maintain a single source of truth for conversion
*        logic.
*     - Helper functions (allocateCString and mapConversionType) are defined as static and are not exposed outside this file, 
*       keeping the API surface clean.
*/
extern "C" {

/**
 * @brief Main DLL entry point for C# string conversion
 */
API const char* processStringDLL(const char* input, int choiceInt) {

    // Fundamental safety check
    if (!input)
        return nullptr;

    size_t inputLength = std::strlen(input);

    // Check for input size limit
    if (inputLength > MAX_INPUT_SIZE) {
        // Deterministic error string that the .NET layer can identify
        return allocateCString("ERROR_BUFFER_OVERFLOW_LIMIT_2MB");
    }

    Client client;
    ConversionChoice choice =
        static_cast<ConversionChoice>(choiceInt);

    ConversionType type;

    // Map external choice → internal conversion type
    if (!mapConversionType(choice, type)) {
        return allocateCString(std::string(input));
    }

    // Set strategy
    client.setStrategy(
        StringConversionFactory::create(type)
    );

    // Execute conversion pipeline
    std::string result =
        client.execute(std::string(input));

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
API void freeString(char* str) {
    free(str);
}

} // extern "C"