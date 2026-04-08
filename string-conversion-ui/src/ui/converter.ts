import { convertText } from "../api/wordCaseApi";

async function onConvertClick() {
  const text = (document.getElementById("inputText") as HTMLInputElement).value;

  const choice = parseInt(
    (document.getElementById("choice") as HTMLSelectElement).value
  );

  const result = await convertText({ text, choice });

  document.getElementById("output")!.textContent = result.output;
}

// expose to HTML
(window as any).onConvertClick = onConvertClick;