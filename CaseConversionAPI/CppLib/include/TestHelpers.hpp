/*********************************************************************/
/* $Header: TestHelpers.hpp                                          */
/*                                                                   */
/* Copyright (c) 2016-2026 nitishhsinghh. All rights reserved.       */
/* This material may be reproduced for teaching and learning         */
/* purposes only. It is not to be used in industry or for            */
/* commercial purposes.                                              */
/*                                                                   */
/* Class       - TestHelpers                                         */
/*                                                                   */
/* Description - Provides helper utilities for logging string        */
/*               conversion results during testing.                  */
/*                                                                   */
/* Notes       - Contains inline helper functions for test output.   */
/*                                                                   */
/* $Log: TestHelpers.hpp                                             */
/*                                                                   */
/*  Revision 1.0  2026/04/11  Nitish Singh                           */
/*  Initial implementation of test helper utilities.                 */
/*********************************************************************/

#ifndef TEST_HELPERS_HPP
#define TEST_HELPERS_HPP

/*********************************************************************/
/* Dependencies                                                      */
/*********************************************************************/
#include <string>
#include <iostream>

/**
 * @brief Logs the result of a string conversion.
 *
 * Example:
 * Input  : "HELLO"
 * Output : "hello"
 */
inline void logConversion(const std::string& name,
                          const std::string& input,
                          const std::string& output)
{
    std::cout << "[" << name << "] Input: \"" << input
              << "\" => Output: \"" << output << "\"" << std::endl;
}

#endif // TEST_HELPERS_HPP