/*********************************************************************/
/* $Header: RemoveVowelsConversion.hpp                               */
/*                                                                   */
/* Copyright (c) 2016-2026 nitishhsinghh. All rights reserved.       */
/* This material may be reproduced for teaching and learning         */
/* purposes only. It is not to be used in industry or for            */
/* commercial purposes.                                              */
/*                                                                   */
/* Class       - RemoveVowelsConversion                              */
/*                                                                   */
/* Description - Removes all vowels from the input string.           */
/*                                                                   */
/* Notes       - Implements IStringConversion interface.             */
/*                                                                   */
/* $Log: RemoveVowelsConversion.hpp                                  */
/*                                                                   */
/*  Revision 1.0  2026/04/11  Nitish Singh                           */
/*  Initial implementation of RemoveVowelsConversion class.          */
/*********************************************************************/

#ifndef REMOVEVOWELSCONVERSION_HPP
#define REMOVEVOWELSCONVERSION_HPP

/*********************************************************************/
/* Dependencies                                                      */
/*********************************************************************/
#include "IStringConversion.hpp"
#include <string>

/**
 * @class RemoveVowelsConversion
 * @brief Concrete implementation of IStringConversion that removes vowels.
 *
 * Example:
 * Input  : "Hello World"
 * Output : "Hll Wrld"
 */
class RemoveVowelsConversion : public IStringConversion {
public:
  /**
   * @brief Converts the input string by removing all vowels.
   * @param input The original string to convert.
   * @return A new string with all vowels removed.
   */
  std::string convert(const std::string &input) const override;
};

#endif // REMOVEVOWELSCONVERSION_HPP