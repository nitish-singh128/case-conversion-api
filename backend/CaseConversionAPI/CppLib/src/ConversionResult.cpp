/*********************************************************************/
/* $File: ConversionResult.cpp                                       */
/*                                                                   */
/* Copyright (c) 2016-2026 nitishhsinghh. All rights reserved.       */
/* This material may be reproduced for teaching and learning         */
/* purposes only. It is not to be used in industry or for            */
/* commercial purposes.                                              */
/*                                                                   */
/* Class       - ConversionResult                                    */
/*                                                                   */
/* Description - Implements RAII-based ownership model for           */
/*               dynamically allocated C-style strings.              */
/*               Provides deep copy and move semantics for safe      */
/*               transfer across ABI boundaries.                     */
/*                                                                   */
/* Notes       - Ensures deterministic memory cleanup via delete[]   */
/*             - Designed for interoperability with managed runtimes */
/*             - Null-safe handling across all operations            */
/*                                                                   */
/* $Log: ConversionResult.cpp                                        */
/*                                                                   */
/* Revision 1.0  2026/04/30  Nitish Singh                            */
/* Initial implementation with full Rule of 5 support.               */
/*                                                                   */
/*********************************************************************/

/*********************************************************************/
/* Dependencies                                                      */
/*********************************************************************/

#include "ConversionResult.hpp"

/*********************************************************************/
/* Constructor                                                       */
/*********************************************************************/

ConversionResult::ConversionResult(const char* input) {
    if (input) {
        data = new char[std::strlen(input) + 1];
        std::strcpy(data, input);
    } else {
        data = nullptr;
    }
}

/*********************************************************************/
/* Destructor                                                        */
/*********************************************************************/

ConversionResult::~ConversionResult() {
    delete[] data;
}

/*********************************************************************/
/* Copy Constructor                                                  */
/*********************************************************************/

ConversionResult::ConversionResult(const ConversionResult& other) {
    if (other.data) {
        data = new char[std::strlen(other.data) + 1];
        std::strcpy(data, other.data);
    } else {
        data = nullptr;
    }
}

/*********************************************************************/
/* Copy Assignment                                                   */
/*********************************************************************/

ConversionResult& ConversionResult::operator=(const ConversionResult& other) {
    if (this != &other) {
        delete[] data;

        if (other.data) {
            data = new char[std::strlen(other.data) + 1];
            std::strcpy(data, other.data);
        } else {
            data = nullptr;
        }
    }
    return *this;
}

/*********************************************************************/
/* Move Constructor                                                  */
/*********************************************************************/

ConversionResult::ConversionResult(ConversionResult&& other) noexcept
    : data(other.data) {
    other.data = nullptr;
}

/*********************************************************************/
/* Move Assignment                                                   */
/*********************************************************************/

ConversionResult& ConversionResult::operator=(ConversionResult&& other) noexcept {
    if (this != &other) {
        delete[] data;
        data = other.data;
        other.data = nullptr;
    }
    return *this;
}

/*********************************************************************/
/* Accessor                                                          */
/*********************************************************************/

const char* ConversionResult::get_c_str() const {
    return data;
}