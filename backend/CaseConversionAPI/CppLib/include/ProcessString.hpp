/*********************************************************************/
/* $Header: ProcessString.hpp                                        */
/*                                                                   */
/* Copyright (c) 2016-2026 nitishhsinghh. All rights reserved.       */
/* This material may be reproduced for teaching and learning         */
/* purposes only. It is not to be used in industry or for            */
/* commercial purposes.                                              */
/*                                                                   */
/* File        - ProcessString.hpp                                   */
/*                                                                   */
/* Description - Provides a client interface function to process a   */
/*               string using a chosen conversion strategy.          */
/*                                                                   */
/* Notes       - Uses Client and factory to select appropriate       */
/*               conversion implementation.                          */
/*                                                                   */
/* $Log: ProcessString.hpp                                           */
/*                                                                   */
/*  Revision 1.0  2026/04/11  Nitish Singh                           */
/*  Initial implementation of processString interface.               */
/*********************************************************************/

#ifndef PROCESSSTRING_HPP
#define PROCESSSTRING_HPP

/*********************************************************************/
/* Dependencies                                                      */
/*********************************************************************/

#include <string>

/**
 * @brief Processes a string using the specified conversion strategy.
 *
 * Example:
 * Input  : ("Hello World", 3)
 * Output : "hello world"
 */
std::string processString(const std::string &input, int choice);

#endif // PROCESSSTRING_HPP