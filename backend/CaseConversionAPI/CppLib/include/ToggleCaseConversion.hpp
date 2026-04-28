/*********************************************************************/
/* $Header: ToggleCaseConversion.hpp                                 */
/*                                                                   */
/* Copyright (c) 2016-2026 nitishhsinghh. All rights reserved.       */
/* This material may be reproduced for teaching and learning         */
/* purposes only. It is not to be used in industry or for            */
/* commercial purposes.                                              */
/*                                                                   */
/* Class       - ToggleCaseConversion                                */
/*                                                                   */
/* Description - Concrete implementation of IStringConversion that   */
/*               toggles the case of each character in a string.     */
/*                                                                   */
/* Notes       - Lowercase becomes uppercase and vice versa.         */
/*               Non-alphabetic characters remain unchanged.         */
/*                                                                   */
/* $Log: ToggleCaseConversion.hpp                                    */
/*                                                                   */
/*  Revision 1.0  2026/04/11  Nitish Singh                           */
/*  Initial implementation of ToggleCaseConversion class.            */
/*********************************************************************/

#ifndef TOGGLECASECONVERSION_HPP
#define TOGGLECASECONVERSION_HPP

/*********************************************************************/
/* Dependencies                                                      */
/*********************************************************************/

#include "IStringConversion.hpp"
#include <string>

/**
 * @class ToggleCaseConversion
 * @brief Converts a string by toggling character case.
 *
 * Example:
 * Input  : "HeLLo"
 * Output : "hEllO"
 */
class ToggleCaseConversion : public IStringConversion {
public:
  /**
   * @brief Toggles the case of each character in the input string.
   * @param input The string to convert.
   * @return Converted string with toggled case.
   */
  std::string convert(const std::string &input) const override;
};

#endif // TOGGLECASECONVERSION_HPP