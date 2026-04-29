/*********************************************************************/
/* $File: SnakeCaseConversion.cpp                                    */
/*                                                                   */
/* Copyright (c) 2016-2026 nitishhsinghh. All rights reserved.       */
/* This material may be reproduced for teaching and learning         */
/* purposes only. It is not to be used in industry or for            */
/* commercial purposes.                                              */
/*                                                                   */
/* Class       - SnakeCaseConversion                                 */
/*                                                                   */
/* Description - Converts input string to snake_case format by       */
/*               replacing spaces with underscores and converting    */
/*               all characters to lowercase.                        */
/*                                                                   */
/* Notes       - Reuses LowerCaseConversion                          */
/*               Multiple spaces converted to multiple underscores   */
/*                                                                   */
/* $Log: SnakeCaseConversion.cpp                                     */
/*                                                                   */
/*  Revision 1.0  2026/04/11  Nitish Singh                           */
/*  Initial implementation of SnakeCaseConversion.                   */
/*********************************************************************/

/*********************************************************************/
/* Dependencies                                                      */
/*********************************************************************/
#include "SnakeCaseConversion.hpp"
#include "LowerCaseConversion.hpp"

ConversionResult SnakeCaseConversion::convert(const std::string &input) const {
  LowerCaseConversion lowerConv;

  std::string lower = ConversionResult(lowerConv.convert(input)).get_c_str();
  std::string result;

  for (char ch : lower) {
    if (ch == ' ')
      result += '_';
    else
      result += ch;
  }
  return ConversionResult(result.c_str());
}