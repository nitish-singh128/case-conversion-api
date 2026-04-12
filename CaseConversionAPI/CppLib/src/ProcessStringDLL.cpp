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

extern "C" {


//===================================================================
//#region Helper Utilities
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

//#endregion


//===================================================================
//#region Conversion Mapping
//===================================================================

/**
 * @brief Maps external conversion choice to internal type
 */
static bool mapConversionType(ConversionChoice choice, ConversionType& type) {

    switch (choice) {

        case ConversionChoice::Alternating:   type = ConversionType::Alternating; return true;
        case ConversionChoice::Capitalize:    type = ConversionType::Capitalize;  return true;
        case ConversionChoice::Lower:         type = ConversionType::Lower;       return true;
        case ConversionChoice::Upper:         type = ConversionType::Upper;       return true;
        case ConversionChoice::Sentence:      type = ConversionType::Sentence;    return true;
        case ConversionChoice::Toggle:        type = ConversionType::Toggle;      return true;
        case ConversionChoice::Reverse:       type = ConversionType::Reverse;     return true;
        case ConversionChoice::RemoveVowels:  type = ConversionType::RemoveVowels;return true;
        case ConversionChoice::RemoveSpaces:  type = ConversionType::RemoveSpaces;return true;
        case ConversionChoice::InvertWords:   type = ConversionType::InvertWords; return true;
        case ConversionChoice::SnakeCase:     type = ConversionType::SnakeCase;   return true;
        case ConversionChoice::KebabCase:     type = ConversionType::KebabCase;   return true;
        case ConversionChoice::LeetSpeak:     type = ConversionType::LeetSpeak;   return true;

        default:
            return false;
    }
}

//#endregion


//===================================================================
//#region Exported DLL API
//===================================================================

/**
 * @brief Main DLL entry point for C# string conversion
 */
API const char* processStringDLL(const char* input, int choiceInt) {

    if (!input)
        return nullptr;

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
 */
API void freeString(char* str) {
    free(str);
}

//#endregion

} // extern "C"