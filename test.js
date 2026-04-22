import http from 'k6/http';
import { check } from 'k6';

export const options = {
  vus: 10,
  iterations: 2000,
};

export default function () {
  const url = 'http://host.docker.internal/api/WordCase/convert';
  
  // This matches your C# anonymous object: new { text = "...", choice = 1 }
  const payload = JSON.stringify({
    text: "Soak_Test_Data",
    choice: 1
  });

  const params = {
    headers: { 'Content-Type': 'application/json' },
  };

  const res = http.post(url, payload, params);

  check(res, {
    'status is 200': (r) => r.status === 200,
    'has content': (r) => r.body.length > 0,
  });
}