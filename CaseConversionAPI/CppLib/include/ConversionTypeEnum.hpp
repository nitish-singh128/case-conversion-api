/*********************************************************************/
/* $Header: ConversionTypeEnum.hpp                                   */
/*                                                                   */
/* Copyright (c) 2016-2026 nitishhsinghh. All rights reserved.       */
/* This material may be reproduced for teaching and learning         */
/* purposes only. It is not to be used in industry or for            */
/* commercial purposes.                                              */
/*                                                                   */
/* Enum        - ConversionChoice                                    */
/*                                                                   */
/* Description - Enumerates supported string conversion strategies   */
/*               used by the C++ conversion engine and exposed       */
/*               through the DLL interface.                         */
/*                                                                   */
/* Notes       - Values map directly to integer choices passed       */
/*               into processStringDLL for conversion selection.     */
/*                                                                   */
/* $Log: ConversionTypeEnum.hpp                                      */
/*********************************************************************/

#ifndef CONVERSIONTYPEENUM_HPP
#define CONVERSIONTYPEENUM_HPP

/*********************************************************************/
/* Dependencies                                                      */
/*********************************************************************/

/**
 * @enum ConversionChoice
 * @brief Enumerates supported string conversion strategies.
 *
 * Each enum value corresponds to a conversion type that can be
 * selected by passing its integer value to processStringDLL.
 */
enum class ConversionChoice : int {
    Alternating   = 1,  ///< Alternating Case
    Capitalize    = 2,  ///< Capitalize Words
    Lower         = 3,  ///< Lower Case
    Upper         = 4,  ///< Upper Case
    Sentence      = 5,  ///< Sentence Case
    Toggle        = 6,  ///< Toggle Case
    Reverse       = 7,  ///< Reverse String
    RemoveVowels  = 8,  ///< Remove Vowels
    RemoveSpaces  = 9,  ///< Remove Spaces
    InvertWords   = 10, ///< Invert Words
    SnakeCase     = 11, ///< Snake Case
    KebabCase     = 12, ///< Kebab Case
    LeetSpeak     = 13  ///< Leet Speak
};

#endif // CONVERSIONTYPEENUM_HPP
