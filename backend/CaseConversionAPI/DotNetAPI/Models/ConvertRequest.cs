/**************************************************************************************************
 * File         : ConvertRequest.cs
 *
 * Copyright    : (c) 2016–2026 nitishhsinghh. All rights reserved.
 **************************************************************************************************
 * Revision History:
 * ------------------------------------------------------------------------------------------------
 * Version     Date           Author           Description
 * ------------------------------------------------------------------------------------------------
 * 1.0         2026-04-11     Nitish Singh     Initial implementation of request model.
 * 1.1         2026-04-20     Nitish Singh     Changed Text to string? to resolve 400 errors 
 * on empty/null string test cases.
 **************************************************************************************************/

namespace StringConversionAPI.Models
{
    public class ConvertRequest
    {
        /// <summary>
        /// Input text. Marked nullable (?) to ensure .NET 8 allows empty strings 
        /// to pass through to the Service layer for custom validation.
        /// </summary>
        public string? Text { get; set; } = string.Empty;

        public int Choice { get; set; }
    }
}