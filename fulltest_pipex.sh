#!/bin/bash

# ANSI color codes
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'  # For the count summary
NC='\033[0m'      # No Color

# Set your pipex program path
PIPE_X="./pipex"

# Test cases (add more as needed)
# Format: "file1 cmd1 cmd2 outfile"
TEST_CASES=(
    "file1 'grep apple' 'wc -l' output1.txt"
    "file1 'echo Hello World' 'cat' output2.txt"
    "file1 'cat' 'wc -w' output3.txt"
    "file1 'echo \"New line:\"' 'cat' output4.txt"
    "file1 'head -n 2' 'rev' output5.txt"
    "file1 'echo \"Number:\"' 'grep 42' output6.txt"
    "file1 'tail -n 1' 'tr a-z A-Z' output7.txt"
    "file1 'grep test' 'awk \"{print \$2}\"' output8.txt"
    "file1 'cat' 'wc -l' output9.txt"
    "file1 'grep apple' 'wc -l' output10.txt"
    "file1 'tr a-z A-Z' 'rev' output11.txt"
    "file1 'sort' 'uniq' output12.txt"
    "file1 'sort' 'uniq' output13.txt"
    "file1 'cat' 'wc -m' output14.txt"
    "file1 'awk \"{print \$2}\"' 'sort -n' output15.txt"
    "file1 'tac' 'cat' output16.txt"
    "file1 'grep error' 'wc -l' output17.txt"
    "file1 'sed \"s/C/Python/\"' 'cat' output18.txt"
)

# Initialize pass/fail counters
PASS_COUNT=0
FAIL_COUNT=0

# Function to compare the output of the pipex program with expected output
compare_output() {
    expected_output=$1
    actual_output=$2
    if [[ "$expected_output" == "$actual_output" ]]; then
        echo -e "${GREEN}PASS${NC}"
        PASS_COUNT=$((PASS_COUNT+1))
    else
        echo -e "${RED}FAIL${NC}"
        FAIL_COUNT=$((FAIL_COUNT+1))
    fi
}

# Print initial test summary
echo -e "${YELLOW}Starting tests...${NC}"

# Loop through test cases and run them
for test_case in "${TEST_CASES[@]}"; do
    # Extract parts of the test case
    IFS="'" read -r file1 cmd1 cmd2 outfile <<< "$test_case"
    echo -e "\nRunning test: $test_case"

    # Prepare the input file (file1)
    echo "Preparing input file: $file1"
    if [ "$file1" == "file1" ]; then
        case $outfile in
            "output1.txt") echo -e "apple\nbanana\napple" > file1.txt ;;  # Find Word Count
            "output2.txt") echo -e "" > file1.txt ;;  # Echo to Cat
            "output3.txt") echo -e "Hello\n42\nWorld" > file1.txt ;;  # Count Words
            "output4.txt") echo -e "This is a test" > file1.txt ;;  # Prefix New Line
            "output5.txt") echo -e "One\nTwo\nThree" > file1.txt ;;  # Reverse Lines
            "output6.txt") echo -e "42 is cool" > file1.txt ;;  # Echo and Search
            "output7.txt") echo -e "Line1\nLine2\nLine3" > file1.txt ;;  # Uppercase Last Line
            "output8.txt") echo -e "Hello World\nPipex test" > file1.txt ;;  # Extract Second Word
            "output9.txt") echo -e "Hello World\nTest line\nAnother line" > file1.txt ;;  # Basic Test
            "output10.txt") echo -e "apple\nbanana\ncherry\napple\nbanana" > file1.txt ;;  # Filter Words
            "output11.txt") echo -e "hello world" > file1.txt ;;  # Convert Case
            "output12.txt") echo -e "dog\ncat\nelephant\nant" > file1.txt ;;  # Sort Words
            "output13.txt") echo -e "apple\napple\nbanana\nbanana\ncherry" > file1.txt ;;  # Remove Duplicates
            "output14.txt") echo -e "abcdefg\n12345" > file1.txt ;;  # Count Characters
            "output15.txt") echo -e "John 25\nAnna 30\nMike 22" > file1.txt ;;  # Extract Columns
            "output16.txt") echo -e "one\ntwo\nthree" > file1.txt ;;  # Reverse Order
            "output17.txt") echo -e "error: failed\nsuccess\nerror: timeout" > file1.txt ;;  # Find Specific Pattern
            "output18.txt") echo -e "I love C programming" > file1.txt ;;  # Replace Text
        esac
    fi

    # Run the pipex command and capture its output
    $PIPE_X file1.txt "$cmd1" "$cmd2" $outfile > output.txt 2>&1
    actual_output=$(cat output.txt)

    # Run the same shell pipeline and capture expected output
    eval "$cmd1 < file1.txt | $cmd2 > $outfile"
    expected_output=$(cat $outfile)

    # Compare the outputs
    compare_output "$expected_output" "$actual
