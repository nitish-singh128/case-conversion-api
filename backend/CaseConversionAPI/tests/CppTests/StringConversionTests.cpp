/*********************************************************************/
/* File: StringConversionTests.cpp                                   */
/*                                                                   */
/* Copyright (c) 2016-2026 nitishhsinghh. All rights reserved.       */
/* This material may be reproduced for teaching and learning         */
/* purposes only. It is not to be used in industry or for            */
/* commercial purposes.                                              */
/*                                                                   */
/* Description : Unit tests for String Conversion library using      */
/*               Google Test framework. Covers basic conversions,    */
/*               advanced conversions, factory creation, strategy    */
/*               pattern behavior, processString API, and edge       */
/*               cases.                                              */
/*                                                                   */
/* Test Groups :                                                     */
/*               1. Basic conversion tests                           */
/*               2. Advanced conversion tests                        */
/*               3. Edge case tests                                  */
/*               4. Factory tests                                    */
/*               5. Client strategy tests                            */
/*               6. ProcessString integration tests                  */
/*               7. Logging tests                                    */
/*                                                                   */
/* Notes       : Requires GoogleTest and linked conversion library.  */
/*********************************************************************/

/*********************************************************************/
/* Dependencies                                                      */
/*********************************************************************/
#include <gtest/gtest.h>
#include <iostream>

// Core Interfaces
#include "Client.hpp"
#include "IStringConversion.hpp"
#include "ProcessString.hpp"
#include "StringConversionFactory.hpp"
#include "TestHelpers.hpp"

// Basic Conversions
#include "AlternatingCaseConversion.hpp"
#include "CapitalizeWordsConversion.hpp"
#include "LowerCaseConversion.hpp"
#include "ReverseConversion.hpp"
#include "SentenceCaseConversion.hpp"
#include "ToggleCaseConversion.hpp"
#include "UpperCaseConversion.hpp"

// Advanced Conversions
#include "InvertWordsConversion.hpp"
#include "KebabCaseConversion.hpp"
#include "LeetSpeakConversion.hpp"
#include "RemoveSpacesConversion.hpp"
#include "RemoveVowelsConversion.hpp"
#include "SnakeCaseConversion.hpp"

// Enmum for conversion choices
#include "ConversionTypeEnum.hpp"

//
// ======================================================
// 1. BASIC CONVERSION TESTS
// ======================================================
//

TEST(LowerCaseConversionTest, Basic) {
  LowerCaseConversion conv;
  EXPECT_EQ(conv.convert("HELLO"), "hello");
}

TEST(UpperCaseConversionTest, Basic) {
  UpperCaseConversion conv;
  EXPECT_EQ(conv.convert("hello"), "HELLO");
}

TEST(CapitalizeWordsConversionTest, Basic) {
  CapitalizeWordsConversion conv;
  EXPECT_EQ(conv.convert("hello world"), "Hello World");
}

TEST(SentenceCaseConversionTest, Basic) {
  SentenceCaseConversion conv;
  EXPECT_EQ(conv.convert("hELLO WORLD"), "Hello world");
}

TEST(ToggleCaseConversionTest, Basic) {
  ToggleCaseConversion conv;
  EXPECT_EQ(conv.convert("HeLLo"), "hEllO");
}

TEST(AlternatingCaseConversionTest, Basic) {
  AlternatingCaseConversion conv;
  EXPECT_EQ(conv.convert("hello world"), "HeLlO WoRlD");
}

TEST(ReverseConversionTest, Basic) {
  ReverseConversion conv;
  EXPECT_EQ(conv.convert("Hello"), "olleH");
  EXPECT_EQ(conv.convert("Hello World!"), "!dlroW olleH");
}

//
// ======================================================
// 2. ADVANCED CONVERSION TESTS
// ======================================================
//

TEST(InvertWordsConversionTest, Basic) {
  InvertWordsConversion conv;
  EXPECT_EQ(conv.convert("Hello World"), "olleH dlroW");
}

TEST(KebabCaseConversionTest, Basic) {
  KebabCaseConversion conv;
  EXPECT_EQ(conv.convert("Hello World Example"), "hello-world-example");
}

TEST(SnakeCaseConversionTest, Basic) {
  SnakeCaseConversion conv;
  EXPECT_EQ(conv.convert("Hello World Example"), "hello_world_example");
}

TEST(RemoveSpacesConversionTest, Basic) {
  RemoveSpacesConversion conv;
  EXPECT_EQ(conv.convert("Hello World"), "HelloWorld");
}

TEST(RemoveVowelsConversionTest, Basic) {
  RemoveVowelsConversion conv;
  EXPECT_EQ(conv.convert("Hello World"), "Hll Wrld");
}

TEST(LeetSpeakConversionTest, Basic) {
  LeetSpeakConversion conv;
  EXPECT_EQ(conv.convert("Hello"), "H3ll0");
  EXPECT_EQ(conv.convert("Testing"),
            "73571ng"); // ensure mapping matches implementation
}

//
// ======================================================
// 3. EDGE CASE TESTS
// ======================================================
//

TEST(EdgeCases, EmptyString) {
  LowerCaseConversion conv;
  EXPECT_EQ(conv.convert(""), "");
}

TEST(EdgeCases, OnlySpaces) {
  RemoveSpacesConversion conv;
  EXPECT_EQ(conv.convert("   "), "");
}

TEST(EdgeCases, NumbersOnly) {
  UpperCaseConversion conv;
  EXPECT_EQ(conv.convert("12345"), "12345");
}

TEST(EdgeCases, SpecialCharacters) {
  ReverseConversion conv;
  EXPECT_EQ(conv.convert("!@#$"), "$#@!");
}

TEST(EdgeCases, OnlyVowels) {
  RemoveVowelsConversion conv;
  EXPECT_EQ(conv.convert("aeiouAEIOU"), "");
}

TEST(EdgeCases, NoVowels) {
  RemoveVowelsConversion conv;
  EXPECT_EQ(conv.convert("bcdfg"), "bcdfg");
}

TEST(LeetSpeakConversionTest, EdgeCases) {
  LeetSpeakConversion conv;
  EXPECT_EQ(conv.convert(""), "");
  EXPECT_EQ(conv.convert("123"), "123");
}

//
// ======================================================
// 4. FACTORY TESTS
// ======================================================
//

TEST(FactoryTest, CreatesLowerCase) {
  auto conv = StringConversionFactory::create(ConversionType::Lower);
  ASSERT_NE(conv, nullptr);
  EXPECT_EQ(conv->convert("HELLO"), "hello");
}

TEST(FactoryTest, CreatesUpperCase) {
  auto conv = StringConversionFactory::create(ConversionType::Upper);
  ASSERT_NE(conv, nullptr);
  EXPECT_EQ(conv->convert("hello"), "HELLO");
}

TEST(FactoryTest, CreatesReverse) {
  auto conv = StringConversionFactory::create(ConversionType::Reverse);
  ASSERT_NE(conv, nullptr);
  EXPECT_EQ(conv->convert("Hello"), "olleH");
}

//
// ======================================================
// 5. CLIENT (STRATEGY PATTERN) TESTS
// ======================================================
//

TEST(ClientTest, ExecutesStrategy) {
  Client client;

  client.setStrategy(StringConversionFactory::create(ConversionType::Lower));
  EXPECT_EQ(client.execute("HELLO"), "hello");

  client.setStrategy(StringConversionFactory::create(ConversionType::Toggle));
  EXPECT_EQ(client.execute("AbC"), "aBc");

  client.setStrategy(StringConversionFactory::create(ConversionType::Reverse));
  EXPECT_EQ(client.execute("Hello"), "olleH");
}

TEST(ClientTest, NoStrategySet) {
  Client client;
  EXPECT_EQ(client.execute("Hello"), "Hello");
}

//
// ======================================================
// 6. PROCESS STRING TESTS
// ======================================================
//

TEST(ProcessStringTest, BasicFlow) {
  EXPECT_EQ(processString("hello world",
                          static_cast<int>(ConversionChoice::Alternating)),
            "HeLlO WoRlD");
  EXPECT_EQ(processString("hello world",
                          static_cast<int>(ConversionChoice::Capitalize)),
            "Hello World");
  EXPECT_EQ(processString("Hello", static_cast<int>(ConversionChoice::Lower)),
            "hello");
  EXPECT_EQ(processString("Hello", static_cast<int>(ConversionChoice::Upper)),
            "HELLO");
  EXPECT_EQ(processString("hELLO wORLD",
                          static_cast<int>(ConversionChoice::Sentence)),
            "Hello world");
  EXPECT_EQ(processString("HeLLo", static_cast<int>(ConversionChoice::Toggle)),
            "hEllO");
  EXPECT_EQ(processString("Hello", static_cast<int>(ConversionChoice::Reverse)),
            "olleH");
}

TEST(ProcessStringTest, AdvancedChoices) {
  EXPECT_EQ(processString("Hello World",
                          static_cast<int>(ConversionChoice::RemoveVowels)),
            "Hll Wrld");
  EXPECT_EQ(processString("Hello World",
                          static_cast<int>(ConversionChoice::RemoveSpaces)),
            "HelloWorld");
  EXPECT_EQ(processString("Hello World",
                          static_cast<int>(ConversionChoice::InvertWords)),
            "olleH dlroW");
  EXPECT_EQ(processString("Hello World",
                          static_cast<int>(ConversionChoice::SnakeCase)),
            "hello_world");
  EXPECT_EQ(processString("Hello World",
                          static_cast<int>(ConversionChoice::KebabCase)),
            "hello-world");
  EXPECT_EQ(
      processString("Test", static_cast<int>(ConversionChoice::LeetSpeak)),
      "7357");
}

TEST(ProcessStringTest, InvalidChoice) {
  EXPECT_EQ(processString("Hello", 99), "hello"); // invalid choice falls back
}

//
// ======================================================
// 7. LOGGING TESTS (OPTIONAL)
// ======================================================
//

TEST(LoggingTest, ConversionLogging) {
  std::string input = "TeSt";
  ToggleCaseConversion conv;

  std::string result = conv.convert(input);
  logConversion("ToggleCase", input, result);

  EXPECT_EQ(result, "tEsT");
}