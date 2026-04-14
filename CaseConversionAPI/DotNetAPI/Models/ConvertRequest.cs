/**************************************************************************************************
 * File        : ConvertRequest.cs
 *
 * Copyright   : (c) 2016–2026 nitishhsinghh. All rights reserved.
 *               This material may be reproduced for teaching and learning purposes only.
 *               It is not to be used in industry or for commercial purposes.
 *
 * Class       : ConvertRequest
 *
 * Description : Data transfer object (DTO) representing the request payload for
 *               string conversion operations. Encapsulates input text and the
 *               selected conversion strategy identifier.
 *
 * Notes       : - Consumed by WordCaseController POST endpoint.
 *               - Serves as the API contract for client-to-server communication.
 *
 * Revision History:
 * ------------------------------------------------------------------------------------------------
 * Version     Date        Author          Description
 * ------------------------------------------------------------------------------------------------
 * 1.0         2026-04-11  Nitish Singh    Initial implementation of request model
 *
 **************************************************************************************************/

using StringConversionAPI.Models;
namespace StringConversionAPI.Models
{
    public class ConvertRequest
    {
        public string Text { get; set; } = string.Empty;
        public int Choice { get; set; }
    }
}