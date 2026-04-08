/*********************************************************************/
/* $Header: ProcessStringDLL.cpp                                     */
/*                                                                   */
/* Copyright (c) 2016-2026 nitishhsinghh. All rights reserved.       */
/* This material may be reproduced for teaching and learning         */
/* purposes only. It is not to be used in industry or for            */
/* commercial purposes.                                              */
/*                                                                   */
/* Class       - ProcessStringDLL                                     */
/*                                                                   */
/* Description : DLL wrapper exposing C++ string conversion engine   */
/*               for C# P/Invoke interoperability. Delegates calls   */
/*               to core ProcessString dispatcher.                   */
/*                                                                   */
/* Notes       : Interop layer between native C++ and .NET API       */
/*                                                                   */
/*********************************************************************/

#include "ProcessString.hpp"
#include "Client.hpp"
#include "StringConversionFactory.hpp"
#include "ConversionTypeEnum.hpp"
#include <string>

#ifdef _WIN32
    #ifdef PROCESSSTRING_EXPORTS
        #define PROCESSSTRING_API __declspec(dllexport)
    #else
        #define PROCESSSTRING_API __declspec(dllimport)
    #endif
#else
    #define PROCESSSTRING_API
#endif

extern "C" {

/**
 * C-style exported function for C# interop
 * @param input C-string input
 * @param choice integer conversion choice
 * @return C-string result (valid until next call)
 */
PROCESSSTRING_API const char* processStringDLL(const char* input, int choiceInt) {
    static std::string result;
    if (!input) return nullptr;

    Client client;
    ConversionChoice choice = static_cast<ConversionChoice>(choiceInt);

    ConversionType type;
    switch (choice) {
        case ConversionChoice::Alternating:
            type = ConversionType::Alternating;
            break;

        case ConversionChoice::Capitalize:
            type = ConversionType::Capitalize;
            break;

        case ConversionChoice::Lower:
            type = ConversionType::Lower;
            break;

        case ConversionChoice::Upper:
            type = ConversionType::Upper;
            break;

        case ConversionChoice::Sentence:
            type = ConversionType::Sentence;
            break;

        case ConversionChoice::Toggle:
            type = ConversionType::Toggle;
            break;

        case ConversionChoice::Reverse:
            type = ConversionType::Reverse;
            break;

        case ConversionChoice::RemoveVowels:
            type = ConversionType::RemoveVowels;
            break;

        case ConversionChoice::RemoveSpaces:
            type = ConversionType::RemoveSpaces;
            break;

        case ConversionChoice::InvertWords:
            type = ConversionType::InvertWords;
            break;

        case ConversionChoice::SnakeCase:
            type = ConversionType::SnakeCase;
            break;

        case ConversionChoice::KebabCase:
            type = ConversionType::KebabCase;
            break;

        case ConversionChoice::LeetSpeak:
            type = ConversionType::LeetSpeak;
            break;

        default:
            return input; // fallback if invalid
    }

    client.setStrategy(StringConversionFactory::create(type));
    result = client.execute(std::string(input));
    return result.c_str();
}

} // extern "C"