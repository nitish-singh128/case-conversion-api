export interface ConvertRequest {
  text: string;
  choice: number;
}

export interface ConvertResponse {
  input: string;
  choice: number;
  output: string;
}

export async function convertText(
  request: ConvertRequest
): Promise<ConvertResponse> {
  const response = await fetch(
    "http://localhost:5000/api/WordCase/convert",
    {
      method: "POST",
      headers: {
        "Content-Type": "application/json"
      },
      body: JSON.stringify(request)
    }
  );

  if (!response.ok) {
    throw new Error("Failed to call REST API");
  }

  return await response.json();
}