/*********************************************************************/
/* $Header: RemoveSpacesConversion.hpp                               */
/*                                                                   */
/* Copyright (c) 2016-2026 nitishhsinghh. All rights reserved.       */
/* This material may be reproduced for teaching and learning         */
/* purposes only. It is not to be used in industry or for            */
/* commercial purposes.                                              */
/*                                                                   */
/* Class       - RemoveSpacesConversion                              */
/*                                                                   */
/* Description - Removes all spaces from the input string.           */
/*                                                                   */
/* Notes       - Implements IStringConversion interface.             */
/*                                                                   */
/* $Log: RemoveSpacesConversion.hpp                                  */
/*                                                                   */
/*  Revision 1.0  2026/04/11  Nitish Singh                           */
/*  Initial implementation of RemoveSpacesConversion class.          */
/*********************************************************************/

#ifndef REMOVESPACECONVERSION_HPP
#define REMOVESPACECONVERSION_HPP

/*********************************************************************/
/* Dependencies                                                      */
/*********************************************************************/
#include "IStringConversion.hpp"
#include <string>

/**
 * @class RemoveSpacesConversion
 * @brief Concrete implementation of IStringConversion that removes spaces.
 *
 * Example:
 * Input  : "Hello World Example"
 * Output : "HelloWorldExample"
 */
class RemoveSpacesConversion : public IStringConversion {
public:
  /**
   * @brief Converts the input string by removing all spaces.
   * @param input The original string to convert.
   * @return A new string with all spaces removed.
   */
  std::string convert(const std::string &input) const override;
};

#endif // REMOVESPACECONVERSION_HPP