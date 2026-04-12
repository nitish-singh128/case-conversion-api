/*********************************************************************/
/* $File: SentenceCaseConversion.cpp                               */
/*                                                                   */
/* Copyright (c) 2016-2026 nitishhsinghh. All rights reserved.       */
/* This material may be reproduced for teaching and learning         */
/* purposes only. It is not to be used in industry or for            */
/* commercial purposes.                                              */
/*                                                                   */
/* Class       - SentenceCaseConversion                              */
/*                                                                   */
/* Description - Converts input string to sentence case by           */
/*               capitalizing the first character and converting     */
/*               the remaining characters to lowercase.              */
/*                                                                   */
/* Notes       - Reuses LowerCaseConversion and UpperCaseConversion  */
/*               Handles empty input safely                          */
/*                                                                   */
/* $Log: SentenceCaseConversion.cpp                                  */
/*                                                                   */
/*  Revision 1.0  2026/04/11  Nitish Singh                           */
/*  Initial implementation of SentenceCaseConversion.                */
/*********************************************************************/

/*********************************************************************/
/* Dependencies                                                      */
/*********************************************************************/
#include "SentenceCaseConversion.hpp"
#include "LowerCaseConversion.hpp"
#include "UpperCaseConversion.hpp"

std::string SentenceCaseConversion::convert(const std::string& input) const {
    if (input.empty())
        return input;

    LowerCaseConversion lowerConv;
    UpperCaseConversion upperConv;

    // Step 1: convert entire string to lowercase
    std::string result = lowerConv.convert(input);

    bool capitalizeNext = true;

    for (size_t i = 0; i < result.size(); ++i) {
        char& c = result[i];

        if (std::isalpha(static_cast<unsigned char>(c))) {
            if (capitalizeNext) {
                std::string temp(1, c);
                c = upperConv.convert(temp)[0];
                capitalizeNext = false;
            }
        }

        if (c == '.' || c == '!' || c == '?') {
            capitalizeNext = true;
        }
    }

    return result;
}