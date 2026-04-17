/*********************************************************************/
/* $File: Client.cpp                                               */
/*                                                                   */
/* Copyright (c) 2016-2026 nitishhsinghh. All rights reserved.       */
/* This material may be reproduced for teaching and learning         */
/* purposes only. It is not to be used in industry or for            */
/* commercial purposes.                                              */
/*                                                                   */
/* Class       - Client                                              */
/*                                                                   */
/* Description - Maintains and executes string conversion strategy   */
/*               using the Strategy design pattern.                  */
/*                                                                   */
/* Notes       - Uses unique_ptr for strategy ownership              */
/*               Returns original input if strategy not set          */
/*                                                                   */
/* $Log: Client.cpp                                                  */
/*                                                                   */
/*  Revision 1.0  2026/04/11  Nitish Singh                           */
/*  Initial implementation of Client class.                          */
/*********************************************************************/

/*********************************************************************/
/* Dependencies                                                      */
/*********************************************************************/
#include "Client.hpp"

void Client::setStrategy(std::unique_ptr<IStringConversion> s) {
  strategy = std::move(s);
}

std::string Client::execute(const std::string &input) const {
  if (!strategy) {
    return input;
  }

  return strategy->convert(input);
}