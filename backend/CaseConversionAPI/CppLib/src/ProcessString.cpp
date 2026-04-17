/*********************************************************************/
/* $File: ProcessString.cpp                                        */
/*                                                                   */
/* Copyright (c) 2016-2026 nitishhsinghh. All rights reserved.       */
/* This material may be reproduced for teaching and learning         */
/* purposes only. It is not to be used in industry or for            */
/* commercial purposes.                                              */
/*                                                                   */
/* Class       - ProcessString                                       */
/*                                                                   */
/* Description - Core dispatcher selecting conversion strategies     */
/*               using Factory and Strategy design patterns.         */
/*               Shared by DLL and CLI applications.                 */
/*                                                                   */
/* Notes       - Uses Strategy and Factory design patterns           */
/*               Returns original input for invalid choice           */
/*                                                                   */
/* $Log: ProcessString.cpp                                           */
/*                                                                   */
/*  Revision 1.0  2026/04/11  Nitish Singh                           */
/*  Initial implementation of ProcessString dispatcher.              */
/*                                                                   */
/*  Revision 1.1  2026/04/12  Nitish Singh                           */
/*  Added code quality changes.                                      */
/*********************************************************************/

/*********************************************************************/
/* Dependencies                                                      */
/*********************************************************************/
#include "ProcessString.hpp"
#include "Client.hpp"
#include "StringConversionFactory.hpp"
#include "ConversionTypeEnum.hpp"

static ConversionType mapChoiceToType(ConversionChoice choice) {
    switch (choice) {
        case ConversionChoice::Alternating:
            return ConversionType::Alternating;
        case ConversionChoice::Capitalize:
            return ConversionType::Capitalize;
        case ConversionChoice::Lower:
            return ConversionType::Lower;
        case ConversionChoice::Upper:
            return ConversionType::Upper;
        case ConversionChoice::Sentence:
            return ConversionType::Sentence;
        case ConversionChoice::Toggle:
            return ConversionType::Toggle;
        case ConversionChoice::Reverse:
            return ConversionType::Reverse;
        case ConversionChoice::RemoveVowels:
            return ConversionType::RemoveVowels;
        case ConversionChoice::RemoveSpaces:
            return ConversionType::RemoveSpaces;
        case ConversionChoice::InvertWords:
            return ConversionType::InvertWords;
        case ConversionChoice::SnakeCase:
            return ConversionType::SnakeCase;
        case ConversionChoice::KebabCase:
            return ConversionType::KebabCase;
        case ConversionChoice::LeetSpeak:
            return ConversionType::LeetSpeak;
        default:
            return ConversionType::Lower;  // safe fallback
    }
}

std::string processString(const std::string& input, int choiceInt) {
    Client client;

    ConversionChoice choice =
        static_cast<ConversionChoice>(choiceInt);

    // Map enum to ConversionType
    ConversionType type = mapChoiceToType(choice);

    client.setStrategy(
        StringConversionFactory::create(type)
    );

    return client.execute(input);
}