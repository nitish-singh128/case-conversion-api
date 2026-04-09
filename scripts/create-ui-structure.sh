#!/bin/bash

# Root folder
PROJECT_NAME="string-conversion-ui"

echo "Creating project structure..."

mkdir -p $PROJECT_NAME/src/api
mkdir -p $PROJECT_NAME/src/ui
mkdir -p $PROJECT_NAME/src/types

touch $PROJECT_NAME/src/api/wordCaseApi.ts
touch $PROJECT_NAME/src/ui/converter.ts
touch $PROJECT_NAME/src/types/models.ts
touch $PROJECT_NAME/src/main.ts
touch $PROJECT_NAME/src/style.css

touch $PROJECT_NAME/index.html
touch $PROJECT_NAME/package.json
touch $PROJECT_NAME/tsconfig.json
touch $PROJECT_NAME/vite.config.ts

echo "Project structure created successfully!"