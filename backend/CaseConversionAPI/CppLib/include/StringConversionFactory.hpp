/*********************************************************************/
/* $Header: StringConversionFactory.hpp                              */
/*                                                                   */
/* Copyright (c) 2016-2026 nitishhsinghh. All rights reserved.       */
/* This material may be reproduced for teaching and learning         */
/* purposes only. It is not to be used in industry or for            */
/* commercial purposes.                                              */
/*                                                                   */
/* Class       - StringConversionFactory                             */
/*                                                                   */
/* Description - Factory class for creating string conversion        */
/*               strategy objects.                                   */
/*                                                                   */
/* Notes       - Returns appropriate IStringConversion implementation*/
/*               based on ConversionType.                            */
/*                                                                   */
/* $Log: StringConversionFactory.hpp                                 */
/*                                                                   */
/*  Revision 1.0  2026/04/11  Nitish Singh                           */
/*  Initial implementation of StringConversionFactory class.         */
/*********************************************************************/

#ifndef STRINGCONVERSIONFACTORY_HPP
#define STRINGCONVERSIONFACTORY_HPP

/*********************************************************************/
/* Dependencies                                                      */
/*********************************************************************/
#include "IStringConversion.hpp"
#include <memory>

/**
 * @enum ConversionType
 * @brief Defines types of string conversions available.
 */
enum class ConversionType {
  Lower,
  Upper,
  Capitalize,
  Sentence,
  Toggle,
  Alternating,
  Reverse,
  RemoveVowels,
  RemoveSpaces,
  InvertWords,
  SnakeCase,
  KebabCase,
  LeetSpeak
};

/**
 * @class StringConversionFactory
 * @brief Factory class to create IStringConversion objects.
 *
 * Example:
 * Input  : ConversionType::Upper
 * Output : "HELLO"
 */
class StringConversionFactory {
public:
  /**
   * @brief Creates a string conversion object based on ConversionType.
   * @param type The type of conversion to create.
   * @return Unique pointer to conversion object.
   */
  static std::unique_ptr<IStringConversion> create(ConversionType type);
};

#endif // STRINGCONVERSIONFACTORY_HPP