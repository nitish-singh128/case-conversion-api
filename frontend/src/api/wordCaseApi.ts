/**
 * @file        wordCaseApi.ts
 * @summary     Frontend Service Layer for the Word Case Conversion API.
 * @description Provides a type-safe interface for communicating with the 
 * .NET/C++ backend engine. Handles request serialization, 
 * transport via Fetch API, and response deserialization.
 * * @copyright   (c) 2016–2026 nitishhsinghh. All rights reserved.
 * This material is intended for pedagogical purposes.
 * * @version     1.0.0
 * @author      Nitish Singh
 * @lastMachine 2026-04-14
 */

/**
 * Represents the structured request for the conversion engine.
 */
export interface ConvertRequest {
  /** The raw text to be processed. */
  text: string;
  /** The integer ID corresponding to a specific C++ strategy. */
  choice: number;
}

/**
 * Represents the normalized response from the API Gateway.
 */
export interface ConvertResponse {
  /** The original input text. */
  input: string;
  /** The strategy ID utilized for processing. */
  choice: number;
  /** The resulting string after native transformation. */
  output: string;
}

/**
 * Dispatches a transformation request to the Backend API.
 * * @async
 * @param {ConvertRequest} request - The payload containing text and strategy ID.
 * @returns {Promise<ConvertResponse>} A promise resolving to the processed result.
 * @throws {Error} If the network request fails or returns a non-200 status.
 * * @example
 * const result = await convertText({ text: "hello", choice: 4 });
 * console.log(result.output); // "HELLO"
 */
export async function convertText(
  request: ConvertRequest
): Promise<ConvertResponse> {
  const API_ENDPOINT = "http://localhost:5000/api/WordCase/convert";

  const response = await fetch(API_ENDPOINT, {
    method: "POST",
    headers: {
      "Content-Type": "application/json",
      "Accept": "application/json"
    },
    body: JSON.stringify(request)
  });

  if (!response.ok) {
    // Note: In production, consider logging to a 
    // telemetry service (e.g., Sentry or Azure Application Insights) here.
    throw new Error(`API Error: ${response.status} - ${response.statusText}`);
  }

  return await response.json();
}