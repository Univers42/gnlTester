#!/bin/bash

echo "Checking directory structure..."
mkdir -p test_cases expected_output outputs

echo "Checking test files..."
if [ -d "test_cases" ]; then
    count=$(ls test_cases | wc -l)
    echo "Found $count files in test_cases directory"
else
    echo "test_cases directory not found!"
fi

if [ -d "expected_output" ]; then
    count=$(ls expected_output | wc -l)
    echo "Found $count files in expected_output directory"
else
    echo "expected_output directory not found!"
fi

echo "Checking get_next_line files..."
if [ -f "../get_next_line.c" ]; then
    echo "get_next_line.c found!"
else
    echo "get_next_line.c not found in parent directory!"
fi

if [ -f "../get_next_line.h" ]; then
    echo "get_next_line.h found!"
else
    echo "get_next_line.h not found in parent directory!"
fi

exit 0
