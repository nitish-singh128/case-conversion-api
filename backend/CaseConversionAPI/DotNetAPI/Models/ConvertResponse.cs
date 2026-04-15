/**************************************************************************************************
 * File        : ConvertResponse.cs
 *
 * Copyright   : (c) 2016–2026 nitishhsinghh. All rights reserved.
 *               This material may be reproduced for teaching and learning purposes only.
 *               It is not to be used in industry or for commercial purposes.
 *
 * Class       : ConvertResponse
 *
 * Description : Data transfer object (DTO) representing the response payload for
 *               string conversion operations. Encapsulates the original input,
 *               selected conversion strategy, and processed output string.
 *
 * Notes       : - Returned by WordCaseController endpoints.
 *               - Defines the API response contract for client consumption.
 *
 * Revision History:
 * ------------------------------------------------------------------------------------------------
 * Version     Date        Author          Description
 * ------------------------------------------------------------------------------------------------
 * 1.0         2026-04-11  Nitish Singh    Initial implementation of response model
 *
 **************************************************************************************************/

namespace StringConversionAPI.Models
{
    public class ConvertResponse
    {
        public string Input { get; set; } = string.Empty;
        public int Choice { get; set; }
        public string Output { get; set; } = string.Empty;
    }
}