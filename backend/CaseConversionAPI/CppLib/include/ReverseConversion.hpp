/*********************************************************************/
/* $Header: ReverseConversion.hpp                                    */
/*                                                                   */
/* Copyright (c) 2016-2026 nitishhsinghh. All rights reserved.       */
/* This material may be reproduced for teaching and learning         */
/* purposes only. It is not to be used in industry or for            */
/* commercial purposes.                                              */
/*                                                                   */
/* Class       - ReverseConversion                                   */
/*                                                                   */
/* Description - Reverses all characters in the input string.        */
/*                                                                   */
/* Notes       - Implements IStringConversion interface.             */
/*                                                                   */
/* $Log: ReverseConversion.hpp                                       */
/*                                                                   */
/*  Revision 1.0  2026/04/11  Nitish Singh                           */
/*  Initial implementation of ReverseConversion class.               */
/*********************************************************************/

#ifndef REVERSECONVERSION_HPP
#define REVERSECONVERSION_HPP

/*********************************************************************/
/* Dependencies                                                      */
/*********************************************************************/
#include "IStringConversion.hpp"
#include <string>

/**
 * @class ReverseConversion
 * @brief Concrete implementation of IStringConversion that reverses a string.
 *
 * Example:
 * Input  : "Hello"
 * Output : "olleH"
 */
class ReverseConversion : public IStringConversion {
public:
  /**
   * @brief Reverses the input string.
   * @param input The string to be reversed.
   * @return A new string with characters in reverse order.
   */
  std::string convert(const std::string &input) const override;
};

#endif // REVERSECONVERSION_HPP