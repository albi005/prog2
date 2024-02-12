#!/bin/sh

# https://chat.openai.com/c/b07ea232-50b2-4b9c-aaa9-2f263506af5b

# Check if an argument was provided
if [ "$#" -ne 1 ]; then
  echo "Usage: $0 <directory_name>"
  exit 1
fi

# Store the first command-line argument as the directory name
directory_name="$1"

# Check if the specified directory exists
if [ ! -d "./$directory_name" ]; then
  echo "Directory '$directory_name' does not exist."
  exit 1
fi

# Create a ZIP file with the same name as the directory
(cd "$directory_name" && zip -r "$directory_name.zip" ./*.c ./*.h)

# Check if the ZIP file was created successfully
if [ $? -eq 0 ]; then
  echo "ZIP file '$directory_name/$directory_name.zip' created successfully."
else
  echo "Failed to create ZIP file."
fi
