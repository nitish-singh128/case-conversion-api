/*********************************************************************/
/* $Header: Client.hpp                                               */
/*                                                                   */
/* Copyright (c) 2016-2026 nitishhsinghh. All rights reserved.       */
/* This material may be reproduced for teaching and learning         */
/* purposes only. It is not to be used in industry or for            */
/* commercial purposes.                                              */
/*                                                                   */
/* Class       - Client                                              */
/*                                                                   */
/* Description - Context class implementing Strategy design pattern  */
/*               to execute string conversion strategies.            */
/*                                                                   */
/* Notes       - Delegates conversion logic to IStringConversion     */
/*               implementations.                                    */
/*                                                                   */
/* $Log: Client.hpp                                                  */
/*                                                                   */
/*  Revision 1.0  2026/04/11  Nitish Singh                           */
/*  Initial implementation of Client context class.                  */
/*                                                                   */
/*  Revision 1.1  2026/04/12  Nitish Singh                           */
/*  Added trace ID functionality for distributed tracing.            */
/*********************************************************************/

#ifndef CLIENT_HPP
#define CLIENT_HPP

/*********************************************************************/
/* Dependencies                                                      */
/*********************************************************************/

#include "IStringConversion.hpp"
#include <memory>
#include <string>

/**
 * @class Client
 * @brief Context class for executing string conversion strategies.
 *
 * Example:
 * auto strategy = std::make_unique<LowerCaseConversion>();
 * Client client;
 * client.setStrategy(std::move(strategy));
 * ConversionResult result = client.execute("HELLO"); // "hello"
 */
class Client {
private:
  /// Pointer to the current string conversion strategy
  std::unique_ptr<IStringConversion> strategy;
  std::string traceId_; // For distributed tracing (OpenTelemetry)

public:
  /**
   * @brief Sets the current string conversion strategy.
   * @param s A unique pointer to an IStringConversion implementation.
   */
  void setStrategy(std::unique_ptr<IStringConversion> s);

  /**
   * @brief Executes the current strategy on the given input string.
   * @param input The string to convert.
   * @return The converted string according to the current strategy.
   *         Returns original input if no strategy is set.
   */
  ConversionResult execute(const std::string &input) const;

  void setTraceId(const std::string& traceId);
};

#endif // CLIENT_HPP