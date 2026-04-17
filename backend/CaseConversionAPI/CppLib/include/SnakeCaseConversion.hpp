/*********************************************************************/
/* $Header: SnakeCaseConversion.hpp                                  */
/*                                                                   */
/* Copyright (c) 2016-2026 nitishhsinghh. All rights reserved.       */
/* This material may be reproduced for teaching and learning         */
/* purposes only. It is not to be used in industry or for            */
/* commercial purposes.                                              */
/*                                                                   */
/* Class       - SnakeCaseConversion                                 */
/*                                                                   */
/* Description - Converts input string to snake_case format.         */
/*                                                                   */
/* Notes       - Implements IStringConversion interface.             */
/*                                                                   */
/* $Log: SnakeCaseConversion.hpp                                     */
/*                                                                   */
/*  Revision 1.0  2026/04/11  Nitish Singh                           */
/*  Initial implementation of SnakeCaseConversion class.             */
/*********************************************************************/

#ifndef SNAKECASECONVERSION_HPP
#define SNAKECASECONVERSION_HPP

/*********************************************************************/
/* Dependencies                                                      */
/*********************************************************************/
#include "IStringConversion.hpp"
#include <string>

/**
 * @class SnakeCaseConversion
 * @brief Concrete implementation of IStringConversion that converts to
 * snake_case.
 *
 * Example:
 * Input  : "Hello World Example"
 * Output : "hello_world_example"
 */
class SnakeCaseConversion : public IStringConversion {
public:
  /**
   * @brief Converts the input string to snake_case.
   * @param input The original string to convert.
   * @return A new string in snake_case format.
   */
  std::string convert(const std::string &input) const override;
};

#endif // SNAKECASECONVERSION_HPP