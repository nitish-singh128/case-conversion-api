/*********************************************************************/
/* $Header: KebabCaseConversion.hpp                                  */
/*                                                                   */
/* Copyright (c) 2016-2026 nitishhsinghh. All rights reserved.       */
/* This material may be reproduced for teaching and learning         */
/* purposes only. It is not to be used in industry or for            */
/* commercial purposes.                                              */
/*                                                                   */
/* Class       - KebabCaseConversion                                 */
/*                                                                   */
/* Description - Converts input string to kebab-case format. Words   */
/*               are separated by hyphens and all characters are     */
/*               lowercase.                                          */
/*                                                                   */
/* Notes       - Implements IStringConversion interface. Handles     */
/*               consecutive spaces and removes trailing hyphens.    */
/*                                                                   */
/* $Log: KebabCaseConversion.hpp                                     */
/*                                                                   */
/*  Revision 1.0  2026/04/11  Nitish Singh                           */
/*  Initial implementation of KebabCaseConversion class.             */
/*********************************************************************/

#ifndef KEBABCASECONVERSION_HPP
#define KEBABCASECONVERSION_HPP

/*********************************************************************/
/* Dependencies                                                      */
/*********************************************************************/
#include "IStringConversion.hpp"
#include <string>

/**
 * @class KebabCaseConversion
 * @brief Concrete implementation of IStringConversion that converts strings to kebab-case.
 *
 * Example:
 * Input  : "Hello World Example"
 * Output : "hello-world-example"
 */
class KebabCaseConversion : public IStringConversion {
public:
    /**
     * @brief Converts the input string to kebab-case.
     * @param input The string to convert.
     * @return The kebab-case version of the input.
     */
    std::string convert(const std::string& input) const override;
};

#endif // KEBABCASECONVERSION_HPP