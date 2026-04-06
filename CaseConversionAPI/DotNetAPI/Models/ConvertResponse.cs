/*********************************************************************/
/* $Header: ConvertResponse.cs                                       */
/*                                                                   */
/* Copyright (c) 2016-2026 nitishhsinghh. All rights reserved.       */
/* This material may be reproduced for teaching and learning         */
/* purposes only. It is not to be used in industry or for            */
/* commercial purposes.                                              */
/*                                                                   */
/* Class       - ConvertResponse                                     */
/*                                                                   */
/* Description - Response model returned by the REST API containing  */
/*               original input, conversion choice, and converted    */
/*               output string.                                      */
/*                                                                   */
/* Notes       - Used by WordCaseController                          */
/*               Encapsulates API response payload                   */
/*                                                                   */
/* $Log: ConvertResponse.cs                                          */
/*********************************************************************/

namespace StringConversionAPI.Models
{
    public class ConvertResponse
    {
        public string Input { get; set; } = string.Empty;
        public int Choice { get; set; }
        public string Output { get; set; } = string.Empty;
    }
}