/*********************************************************************/
/* $Header: ProcessStringDLL.hpp                                     */
/*                                                                   */
/* Copyright (c) 2016-2026 nitishhsinghh. All rights reserved.       */
/* This material may be reproduced for teaching and learning         */
/* purposes only. It is not to be used in industry or for            */
/* commercial purposes.                                              */
/*                                                                   */
/* File        - ProcessStringDLL.hpp                                */
/*                                                                   */
/* Description - Declares exported DLL function for string           */
/*               conversion used for C# interop.                     */
/*                                                                   */
/* Notes       - Provides C-style interface for unmanaged access.    */
/*                                                                   */
/* $Log: ProcessStringDLL.hpp                                        */
/*                                                                   */
/*  Revision 1.0  2026/04/11  Nitish Singh                           */
/*  Initial implementation of DLL export interface.                  */
/*********************************************************************/

#ifndef PROCESSSTRINGDLL_HPP
#define PROCESSSTRINGDLL_HPP

/*********************************************************************/
/* Dependencies                                                      */
/*********************************************************************/

#ifdef _WIN32
  #ifdef PROCESSSTRING_EXPORTS
    #define API __declspec(dllexport)
  #else
    #define API __declspec(dllimport)
  #endif
#else
  #define API
#endif

extern "C" {

    /**
     * @brief C-style exported function for C# interop.
     *
     * @param input  C-string input.
     * @param choice Integer conversion choice.
     * @return C-string result (valid until next call).
     */
    API const char* processStringDLL(const char* input, int choice);
    API void freeString(char* str);

} // extern "C"

#endif // PROCESSSTRINGDLL_HP