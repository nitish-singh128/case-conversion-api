/*********************************************************************/
/* $File: main.cpp                                                 */
/*                                                                   */
/* Copyright (c) 2016-2026 nitishhsinghh. All rights reserved.       */
/* This material may be reproduced for teaching and learning         */
/* purposes only. It is not to be used in industry or for            */
/* commercial purposes.                                              */
/*                                                                   */
/* Class       - main                                                */
/*                                                                   */
/* Description : Console application for local testing of string     */
/*               conversion engine. Uses ProcessString dispatcher.   */
/*               Accepts user input and conversion choice, then      */
/*               displays the converted result.                      */
/*                                                                   */
/* Notes       : Uses ProcessString dispatcher                       */
/*               Demonstrates runtime selection of conversions       */
/*                                                                   */
/* $Log: main.cpp                                                    */
/*                                                                   */
/*  Revision 1.0  2026/04/11  Nitish Singh                           */
/*  Initial implementation of console test application.              */
/*********************************************************************/

/*********************************************************************/
/* Dependencies                                                      */
/*********************************************************************/
#include <iostream>
#include "ProcessString.hpp"

int main()
{
    std::string input;

    std::cout << "Enter string: ";
    std::getline(std::cin, input);

    std::cout << "1: Alternating, 2: Capitalize, 3: Lower, 4: Upper, "
                 "5: Sentence, 6: Toggle, 7: Reverse, 8: RemoveVowels, "
                 "9: RemoveSpaces, 10: InvertWords, 11: SnakeCase, "
                 "12: KebabCase, 13: LeetSpeak\n";

    int choice;
    std::cin >> choice;

    std::string result = processString(input, choice);

    std::cout << "Result: " << result << std::endl;

    return 0;
}