/*********************************************************************/
/* File: ConvertRequest.cs                                           */
/*                                                                   */
/* Copyright (c) 2016-2026 nitishhsinghh. All rights reserved.       */
/* This material may be reproduced for teaching and learning         */
/* purposes only. It is not to be used in industry or for            */
/* commercial purposes.                                              */
/*                                                                   */
/* Class       - ConvertRequest                                      */
/*                                                                   */
/* Description - Model representing the request payload for          */
/*               string conversion operations. Contains input        */
/*               text and conversion choice selected by the user.    */
/*                                                                   */
/* Notes       - Used by WordCaseController POST endpoint.           */
/*                                                                   */
/* $Log: ConvertRequest.cs                                           */
/* 1.0  11-Apr-2026  Nitish Singh                                    */
/*      Initial revision.                                            */
/*********************************************************************/

using StringConversionAPI.Models;
namespace StringConversionAPI.Models
{
    public class ConvertRequest
    {
        public string Text { get; set; } = string.Empty;
        public int Choice { get; set; }
    }
}