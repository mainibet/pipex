#!/bin/bash

# ANSI color codes
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'  # For the count summary
NC='\033[0m'      # No Color

# Set your pipex program path
PIPE_X="./pipex"

# Test cases (add more as needed)
TEST_CASES=(
    "infile 'ls -l' 'wc -l' outfile"
    "infile 'grep a1' 'wc -w' outfile"
    # ... more tests ...
)

# Initialize pass/fail counters
PASS_COUNT=0
FAIL_COUNT=0

# Print initial test summary
echo -e "${YELLOW}Total tests: ${#TEST_CASES[@]}${NC}"

# Function to run a test case and check the output
run_test() {
    local test_case="$1"
    local expected_output_file="expected_output.txt"
    local actual_output_file="actual_output.txt"

    # ... (Input file handling - same as before) ...

    # Get the expected output
    eval "< $input_file $(echo "$test_case" | cut -d' ' -f2-4) > $expected_output_file"

    # Run your pipex program and capture the output
    eval "$PIPE_X $test_case > $actual_output_file"

    # Compare the outputs
    if diff -q $expected_output_file $actual_output_file > /dev/null; then
        echo -e "Test case '$test_case': ${GREEN}PASSED${NC}"
        PASS_COUNT=$((PASS_COUNT + 1))
    else
        echo -e "Test case '$test_case': ${RED}FAILED${NC}"
        diff $expected_output_file $actual_output_file
        FAIL_COUNT=$((FAIL_COUNT + 1))
    fi

    # ... (Clean up temporary files and exit status check - same as before) ...
    echo "" # New line

}

# Run all test cases
for test_case in "${TEST_CASES[@]}"; do
    run_test "$test_case"
done

# Print final test summary
TOTAL_TESTS=$((PASS_COUNT + FAIL_COUNT))
echo -e "${YELLOW}Test Summary:${NC}"
echo -e "${GREEN}Passed: $PASS_COUNT${NC}"
echo -e "${RED}Failed: $FAIL_COUNT${NC}"
echo -e "${YELLOW}Total: $TOTAL_TESTS${NC}"
