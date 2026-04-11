/*********************************************************************/
/* $Header: UpperCaseConversion.hpp                                  */
/*                                                                   */
/* Copyright (c) 2016-2026 nitishhsinghh. All rights reserved.       */
/* This material may be reproduced for teaching and learning         */
/* purposes only. It is not to be used in industry or for            */
/* commercial purposes.                                              */
/*                                                                   */
/* Class       - UpperCaseConversion                                 */
/*                                                                   */
/* Description - Concrete implementation of IStringConversion that   */
/*               converts characters in a string to uppercase.       */
/*                                                                   */
/* Notes       - Non-alphabetic characters remain unchanged.         */
/*                                                                   */
/* $Log: UpperCaseConversion.hpp                                     */
/*                                                                   */
/*  Revision 1.0  2026/04/11  Nitish Singh                           */
/*  Initial implementation of UpperCaseConversion class.             */
/*********************************************************************/

#ifndef UPPERCASECONVERSION_HPP
#define UPPERCASECONVERSION_HPP

/*********************************************************************/
/* Dependencies                                                      */
/*********************************************************************/
#include "IStringConversion.hpp"
#include <string>

/**
 * @class UpperCaseConversion
 * @brief Converts a string to uppercase.
 *
 * Example:
 * Input  : "Hello World!"
 * Output : "HELLO WORLD!"
 */
class UpperCaseConversion : public IStringConversion {
public:
    /**
     * @brief Converts the input string to uppercase.
     * @param input The string to convert.
     * @return Converted string in uppercase.
     */
    std::string convert(const std::string& input) const override;
};

#endif // UPPERCASECONVERSION_HPP