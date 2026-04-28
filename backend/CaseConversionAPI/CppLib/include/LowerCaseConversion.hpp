/*********************************************************************/
/* $Header: LowerCaseConversion.hpp                                  */
/*                                                                   */
/* Copyright (c) 2016-2026 nitishhsinghh. All rights reserved.       */
/* This material may be reproduced for teaching and learning         */
/* purposes only. It is not to be used in industry or for            */
/* commercial purposes.                                              */
/*                                                                   */
/* Class       - LowerCaseConversion                                 */
/*                                                                   */
/* Description - Converts all alphabetic characters in a string to   */
/*               lowercase.                                          */
/*                                                                   */
/* Notes       - Implements IStringConversion interface.             */
/*                                                                   */
/* $Log: LowerCaseConversion.hpp                                     */
/*                                                                   */
/*  Revision 1.0  2026/04/11  Nitish Singh                           */
/*  Initial implementation of LowerCaseConversion class.             */
/*********************************************************************/

#ifndef LOWERCASECONVERSION_HPP
#define LOWERCASECONVERSION_HPP

/*********************************************************************/
/* Dependencies                                                      */
/*********************************************************************/

#include "IStringConversion.hpp"
#include <algorithm>
#include <cctype>

/**
 * @class LowerCaseConversion
 * @brief Concrete implementation of IStringConversion that converts strings to
 * lowercase.
 *
 * Example:
 * Input  : "HELLO WORLD"
 * Output : "hello world"
 */
class LowerCaseConversion : public IStringConversion {
public:
  /**
   * @brief Converts the input string to lowercase.
   * @param input The string to convert.
   * @return A new string where all alphabetic characters are lowercase.
   */
  std::string convert(const std::string &input) const override;
};

#endif // LOWERCASECONVERSION_HPP