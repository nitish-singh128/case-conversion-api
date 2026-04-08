# String Conversion UI

Frontend for the Word Case API using React + Vite.

## Getting Started

### 1. Install dependencies

Make sure you have [Node.js](https://nodejs.org/) installed (v18+ recommended).

```bash
npm install
```

### 2. Run the development server

````Bash
npm run dev
```

This will launch the app at:

```Bash
http://localhost:5173/
```

### 3. Connect to the backend

```Bash
dotnet clean # Clears the output of the previous build.
dotnet build    # Compiles the project and its dependencies into binary files
dotnet run  # Runs the application directly from the source code.
```

The frontend calls the backend at http://localhost:5000/api/WordCase/convert.


