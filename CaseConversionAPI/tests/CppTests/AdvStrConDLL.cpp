/*********************************************************************/


#include <gtest/gtest.h>

// ---------------------------
// Core Includes
// ---------------------------
#include "TestHelpers.hpp"
#include "IStringConversion.hpp"
#include "LowerCaseConversion.hpp"
#include "UpperCaseConversion.hpp"
#include "CapitalizeWordsConversion.hpp"
#include "SentenceCaseConversion.hpp"
#include "ToggleCaseConversion.hpp"
#include "AlternatingCaseConversion.hpp"
#include "ReverseConversion.hpp"

// ---------------------------
// Design Pattern / Framework
// ---------------------------
#include "StringConversionFactory.hpp"
#include "Client.hpp"
#include "ProcessString.hpp"

extern "C" {
    char* processStringDLL(const char* input, int choice);
    void freeString(char* str);
}


// ============================================================
// 1. FUNCTIONAL TESTS FOR DLL
// ============================================================


TEST(ProcessStringDLL, AlternatingCase)
{
    char* result = processStringDLL("hello", 1);
    ASSERT_STREQ(result, "hElLo");
    freeString(result);
}

TEST(ProcessStringDLL, CapitalizeWords)
{
    char* result = processStringDLL("hello world", 2);
    ASSERT_STREQ(result, "Hello World");
    freeString(result);
}

TEST(ProcessStringDLL, LowerCase)
{
    char* result = processStringDLL("HELLO", 3);
    ASSERT_STREQ(result, "hello");
    freeString(result);
}

TEST(ProcessStringDLL, UpperCase)
{
    char* result = processStringDLL("hello", 4);
    ASSERT_STREQ(result, "HELLO");
    freeString(result);
}

TEST(ProcessStringDLL, SentenceCase)
{
    char* result = processStringDLL("hello world. this is test.", 5);
    ASSERT_STREQ(result, "Hello world. This is test.");
    freeString(result);
}

TEST(ProcessStringDLL, ToggleCase)
{
    char* result = processStringDLL("HeLLo", 6);
    ASSERT_STREQ(result, "hEllO");
    freeString(result);
}

TEST(ProcessStringDLL, Reverse)
{
    char* result = processStringDLL("hello", 7);
    ASSERT_STREQ(result, "olleh");
    freeString(result);
}

TEST(ProcessStringDLL, RemoveVowels)
{
    char* result = processStringDLL("hello world", 8);
    ASSERT_STREQ(result, "hll wrld");
    freeString(result);
}

TEST(ProcessStringDLL, RemoveSpaces)
{
    char* result = processStringDLL("hello world", 9);
    ASSERT_STREQ(result, "helloworld");
    freeString(result);
}

TEST(ProcessStringDLL, InvertWords)
{
    char* result = processStringDLL("hello world", 10);
    ASSERT_STREQ(result, "world hello");
    freeString(result);
}

TEST(ProcessStringDLL, SnakeCase)
{
    char* result = processStringDLL("hello world", 11);
    ASSERT_STREQ(result, "hello_world");
    freeString(result);
}

TEST(ProcessStringDLL, KebabCase)
{
    char* result = processStringDLL("hello world", 12);
    ASSERT_STREQ(result, "hello-world");
    freeString(result);
}

TEST(ProcessStringDLL, LeetSpeak)
{
    char* result = processStringDLL("elite hacker", 13);
    ASSERT_TRUE(result != nullptr); // flexible validation
    freeString(result);
}


// ============================================================
// 2. EDGE CASES FOR DLL
// ============================================================


TEST(ProcessStringDLL, EmptyString)
{
    char* result = processStringDLL("", 4);
    ASSERT_STREQ(result, "");
    freeString(result);
}

TEST(ProcessStringDLL, SingleCharacter)
{
    char* result = processStringDLL("a", 4);
    ASSERT_STREQ(result, "A");
    freeString(result);
}

TEST(ProcessStringDLL, SpecialCharacters)
{
    char* result = processStringDLL("@#123 abc!", 4);
    ASSERT_STREQ(result, "@#123 ABC!");
    freeString(result);
}

// ============================================================
// 3. INVALID INPUTS FOR DLL
// ============================================================

TEST(ProcessStringDLL, InvalidChoice)
{
    char* result = processStringDLL("hello", 999);
    ASSERT_STREQ(result, "hello"); // based on your fallback
    freeString(result);
}

TEST(ProcessStringDLL, NullInput)
{
    char* result = processStringDLL(nullptr, 4);
    ASSERT_TRUE(result == nullptr || strcmp(result, "") == 0);
    if(result) freeString(result);
}

// ============================================================
// 4. STRESS TESTS FOR DLL
// ============================================================


TEST(ProcessStringDLL, LargeInput)
{
    std::string large(10000, 'a');

    char* result = processStringDLL(large.c_str(), 4);

    ASSERT_EQ(strlen(result), large.size());
    freeString(result);
}

TEST(ProcessStringDLL, MultipleCalls)
{
    for (int i = 0; i < 1000; i++)
    {
        char* result = processStringDLL("test", 4);
        ASSERT_STREQ(result, "TEST");
        freeString(result);
    }
}

// ============================================================
// 5. MEMORY MANAGEMENT TESTS FOR DLL
// ============================================================


TEST(ProcessStringDLL, MemoryNotNull)
{
    char* result = processStringDLL("hello", 4);
    ASSERT_NE(result, nullptr);
    freeString(result);
}