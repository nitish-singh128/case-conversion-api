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
PROCESSSTRING_API const char* processStringDLL(const char* input, int choice) {
    static std::string result;
    if (!input) return nullptr;

    Client client;
    ConversionType type;

    switch (choice) {
        case 1:  type = ConversionType::Alternating;   break;
        case 2:  type = ConversionType::Capitalize;    break;
        case 3:  type = ConversionType::Lower;         break;
        case 4:  type = ConversionType::Upper;         break;
        case 5:  type = ConversionType::Sentence;      break;
        case 6:  type = ConversionType::Toggle;        break;
        case 7:  type = ConversionType::Reverse;       break;
        case 8:  type = ConversionType::RemoveVowels;  break;
        case 9:  type = ConversionType::RemoveSpaces;  break;
        case 10: type = ConversionType::InvertWords;   break;
        case 11: type = ConversionType::SnakeCase;     break;
        case 12: type = ConversionType::KebabCase;     break;
        case 13: type = ConversionType::LeetSpeak;     break;
        default: return input; // fallback if choice is invalid
    }

    client.setStrategy(StringConversionFactory::create(type));
    result = client.execute(std::string(input));
    return result.c_str();
}

} // extern "C"