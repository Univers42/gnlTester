#!/bin/bash

# Create directories if they don't exist
mkdir -p test_cases expected_output outputs

echo "Creating test files..."

# Create simple test files
echo -n "This is a line without newline" > test_cases/no_newline.txt
echo "This is a line with newline" > test_cases/one_line.txt
printf "Line 1\nLine 2\nLine 3\n" > test_cases/multi_lines.txt
echo -n "" > test_cases/empty.txt
echo "X" > test_cases/1char.txt
printf "This is a really long line that continues for quite some time without any breaks or newline characters whatsoever and is designed to test buffer handling capabilities when dealing with long continuous strings of text without natural breaks. It's important to ensure that your get_next_line implementation can correctly parse and return such lengthy content without any issues." > test_cases/giant_line.txt
echo -n "01234567890123456789012345678901234567890" > test_cases/41_no_nl
printf "0123456789012345678901234567890123456789\n0" > test_cases/41_with_nl
echo -n "012345678901234567890123456789012345678901" > test_cases/42_no_nl
printf "01234567890123456789012345678901234567890\n1" > test_cases/42_with_nl
echo -n "0123456789012345678901234567890123456789012" > test_cases/43_no_nl
printf "012345678901234567890123456789012345678901\n2" > test_cases/43_with_nl
printf "Line with exactly ten characters around the 10-character mark\nAnother line that's just a bit longer\nShort\n" > test_cases/lines_around_10.txt
printf "01234567890123456789012345678901234567890\n987654321098765432109876543210987654321098\n0123456789012345678901234567890123456789012\n987654321098765432109876543210987654321098\n01234567890123456789012345678901234567890" > test_cases/multiple_line_no_nl
printf "9876543210987654321098765432109876543210\n01234567890123456789012345678901234567890\n987654321098765432109876543210987654321098\n01234567890123456789012345678901234567890\n9876543210987654321098765432109876543210\n" > test_cases/multiple_line_with_nl
printf "\n\n\n\n\n" > test_cases/multiple_nl.txt
printf "\n\n\n\n\n" > test_cases/multiple_nlx5
printf "\n" > test_cases/nl
echo "Single line, no newline" > test_cases/one_line_no_nl.txt
printf "\n" > test_cases/only_nl.txt
printf "Line 1\n\nLine 3\n\n\nLine 6\n" > test_cases/variable_nls.txt

# Copy tests to expected outputs with the same content
cp -R test_cases/* expected_output/

echo "Test files creation complete!"
echo "Created $(ls test_cases | wc -l) test files and expected outputs."
