/*********************************************************************/
/* $Header: SentenceCaseConversion.hpp                               */
/*                                                                   */
/* Copyright (c) 2016-2026 nitishhsinghh. All rights reserved.       */
/* This material may be reproduced for teaching and learning         */
/* purposes only. It is not to be used in industry or for            */
/* commercial purposes.                                              */
/*                                                                   */
/* Class       - SentenceCaseConversion                              */
/*                                                                   */
/* Description - Converts input string to sentence case.             */
/*                                                                   */
/* Notes       - Implements IStringConversion interface.             */
/*                                                                   */
/* $Log: SentenceCaseConversion.hpp                                  */
/*                                                                   */
/*  Revision 1.0  2026/04/11  Nitish Singh                           */
/*  Initial implementation of SentenceCaseConversion class.          */
/*********************************************************************/

#ifndef SENTENCECASECONVERSION_HPP
#define SENTENCECASECONVERSION_HPP

/*********************************************************************/
/* Dependencies                                                      */
/*********************************************************************/
#include "IStringConversion.hpp"
#include <string>

/**
 * @class SentenceCaseConversion
 * @brief Concrete implementation of IStringConversion that converts to sentence case.
 *
 * Example:
 * Input  : "hELLO WORLD"
 * Output : "Hello world"
 */
class SentenceCaseConversion : public IStringConversion {
public:
    /**
     * @brief Converts the input string to sentence case.
     * @param input The string to convert.
     * @return The converted string with first letter capitalized.
     */
    std::string convert(const std::string& input) const override;
};

#endif // SENTENCECASECONVERSION_HPP