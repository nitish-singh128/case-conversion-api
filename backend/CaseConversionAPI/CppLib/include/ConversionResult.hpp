/*********************************************************************/
/* $Header: ConversionResult.hpp                                     */
/*                                                                   */
/* Copyright (c) 2016-2026 nitishhsinghh. All rights reserved.       */
/* This material may be reproduced for teaching and learning         */
/* purposes only. It is not to be used in industry or for            */
/* commercial purposes.                                              */
/*                                                                   */
/* Class       - ConversionResult                                    */
/*                                                                   */
/* Description - RAII wrapper for managing string conversion results */
/*               across the native ABI boundary. Ensures strict      */
/*               ownership semantics using Rule of 5.                */
/*                                                                   */
/* Notes       - Implements deep copy semantics for safety.          */
/*             - Supports move semantics for high-performance        */
/*               transfers without heap duplication.                 */
/*             - Designed to integrate with C-style ABI contracts    */
/*               (malloc/free ownership model).                      */
/*                                                                   */
/* $Log: ConversionResult.hpp                                        */
/*                                                                   */
/*  Revision 1.0  2026/04/30  Nitish Singh                           */
/*  Initial implementation with full Rule of 5 support.              */
/*                                                                   */
/*********************************************************************/

#ifndef CONVERSION_RESULT_HPP
#define CONVERSION_RESULT_HPP

/*********************************************************************/
/* Dependencies                                                      */
/*********************************************************************/

#include <cstring>
#include <utility>

/**
 * @class ConversionResult
 * @brief RAII wrapper for string conversion results.
 *
 * Encapsulates a dynamically allocated C-style string and ensures
 * deterministic memory management across ABI boundaries.
 *
 * Example:
 * ConversionResult result("HELLO");
 * const char* output = result.get_c_str(); // Safe access
 */
class ConversionResult {
private:
    /// Pointer to heap-allocated C-style string
    char* data;

public:
    /**
     * @brief Constructs a ConversionResult from input string.
     * @param input Null-terminated C-string to copy.
     */
    explicit ConversionResult(const char* input);

    /**
     * @brief Destructor releases allocated memory.
     */
    ~ConversionResult();

    /*****************************************************************/
    /* Rule of 5: Copy Semantics                                     */
    /*****************************************************************/

    /**
     * @brief Copy constructor (deep copy).
     * @param other Source object to copy from.
     */
    ConversionResult(const ConversionResult& other);

    /**
     * @brief Copy assignment operator (deep copy).
     * @param other Source object to assign from.
     * @return Reference to current object.
     */
    ConversionResult& operator=(const ConversionResult& other);

    /*****************************************************************/
    /* Rule of 5: Move Semantics (Performance Optimization)           */
    /*****************************************************************/

    /**
     * @brief Move constructor (transfers ownership).
     * @param other Source object to move from.
     */
    ConversionResult(ConversionResult&& other) noexcept;

    /**
     * @brief Move assignment operator (transfers ownership).
     * @param other Source object to move from.
     * @return Reference to current object.
     */
    ConversionResult& operator=(ConversionResult&& other) noexcept;

    /**
     * @brief Returns the underlying C-style string.
     * @return Pointer to null-terminated string.
     */
    [[nodiscard]] const char* get_c_str() const;
};

#endif // CONVERSION_RESULT_HPP