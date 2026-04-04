/*********************************************************************/
/* $Header: ProcessStringDLL.hpp                                     */
/*                                                                   */
/* Copyright (c) 2016-2026 nitishhsinghh. All rights reserved.       */
/* This material may be reproduced for teaching and learning         */
/* purposes only. It is not to be used in industry or for            */
/* commercial purposes.                                              */
/*                                                                   */
/* Description - Header for ProcessStringDLL.dll                     */
/*               Declares exported function for C# interop.          */
/*********************************************************************/

#pragma once

#ifdef _WIN32
    #ifdef PROCESSSTRING_EXPORTS
        #define PROCESSSTRING_API __declspec(dllexport)
    #else
        #define PROCESSSTRING_API __declspec(dllimport)
    #endif
#else
    #define PROCESSSTRING_API
#endif

extern "C" {

/**
 * C-style exported function for C# interop
 * @param input C-string input
 * @param choice integer conversion choice
 * @return C-string result (valid until next call)
 */
PROCESSSTRING_API const char* processStringDLL(const char* input, int choice);

} // extern "C"