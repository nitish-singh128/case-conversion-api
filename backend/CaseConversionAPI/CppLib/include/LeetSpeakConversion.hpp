/*********************************************************************/
/* $Header: LeetSpeakConversion.hpp                                  */
/*                                                                   */
/* Copyright (c) 2016-2026 nitishhsinghh. All rights reserved.       */
/* This material may be reproduced for teaching and learning         */
/* purposes only. It is not to be used in industry or for            */
/* commercial purposes.                                              */
/*                                                                   */
/* Class       - LeetSpeakConversion                                 */
/*                                                                   */
/* Description - Converts input string into leet speak (1337).       */
/*               Certain alphabetic characters are replaced with     */
/*               numbers or symbols.                                 */
/*                                                                   */
/* Notes       - Implements IStringConversion interface.             */
/*                                                                   */
/* $Log: LeetSpeakConversion.hpp                                     */
/*                                                                   */
/*  Revision 1.0  2026/04/11  Nitish Singh                           */
/*  Initial implementation of LeetSpeakConversion class.             */
/*********************************************************************/

#ifndef LEETSPEAKCONVERSION_HPP
#define LEETSPEAKCONVERSION_HPP

/*********************************************************************/
/* Dependencies                                                      */
/*********************************************************************/

#include "IStringConversion.hpp"
#include <string>

/**
 * @class LeetSpeakConversion
 * @brief Concrete implementation of IStringConversion that converts strings
 * into leet speak.
 *
 * Example:
 * Input  : "Hello World"
 * Output : "H3ll0 W0rld"
 */
class LeetSpeakConversion : public IStringConversion {
public:
  /**
   * @brief Converts the input string into leet speak.
   * @param input The string to convert.
   * @return The leet speak version of the input.
   */
  ConversionResult convert(const std::string &input) const override;
};

#endif // LEETSPEAKCONVERSION_HPP