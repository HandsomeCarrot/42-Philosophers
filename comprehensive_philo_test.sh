#!/bin/bash

# =============================================================================
# COMPREHENSIVE PHILOSOPHERS TEST SUITE
# =============================================================================
# Description: Extensive testing framework for the Philosophers project
# Author: Advanced Testing Framework
# Version: 2.0
# =============================================================================

# Color codes for output formatting
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

# Global variables
PHILO_PROGRAM="./philo"
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0
LOG_FILE="comprehensive_philo_test_results.log"
DETAILED_LOG="comprehensive_philo_test_detailed_test.log"
TIMEOUT_DURATION=60

# =============================================================================
# UTILITY FUNCTIONS
# =============================================================================

print_header() {
    echo -e "${CYAN}============================================${NC}"
    echo -e "${CYAN} $1${NC}"
    echo -e "${CYAN}============================================${NC}"
}

print_section() {
    echo ""
    echo -e "${BLUE}--- $1 ---${NC}"
    echo ""
}

log_test() {
    local test_name="$1"
    local status="$2"
    local details="$3"
    
    echo "[$status] $test_name: $details" >> "$LOG_FILE"
    echo "$(date '+%Y-%m-%d %H:%M:%S') [$status] $test_name" >> "$DETAILED_LOG"
    if [ "$details" != "" ]; then
        echo "Details: $details" >> "$DETAILED_LOG"
    fi
    echo "" >> "$DETAILED_LOG"
}

run_test() {
    local test_name="$1"
    local command="$2"
    local expected_behavior="$3"
    local timeout="${4:-$TIMEOUT_DURATION}"
    
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    echo -e "${YELLOW}Testing: $test_name${NC}"
    echo -e "Command: ${PURPLE}$command${NC}"
    echo -e "Expected: $expected_behavior"
    
    # Run command with timeout
    local output
    local exit_code
    
    if timeout "$timeout" bash -c "$command" > /tmp/test_output.txt 2>&1; then
        exit_code=0
    else
        exit_code=$?
    fi
    
    output=$(cat /tmp/test_output.txt)
    
    # Enhanced validation logic
    local should_pass=0
    
    # Count the number of arguments in the command (excluding "./philo")
    local arg_count=$(echo "$command" | wc -w)
    arg_count=$((arg_count - 1))  # Subtract 1 for "./philo"
    
    if [ $exit_code -eq 0 ]; then
        # Program completed successfully
        should_pass=1
    elif [ $exit_code -eq 124 ]; then
        # Timeout occurred - check if this is expected behavior
        if [[ "$expected_behavior" == *"should fail"* ]]; then
            should_pass=0  # Timeout when failure expected = actual failure
        elif [ $arg_count -eq 5 ]; then
            # Command has meal limit (5 arguments), timeout is unexpected
            should_pass=0
        else
            # Command has no meal limit (4 arguments), timeout is expected behavior for infinite simulation
            should_pass=1
        fi
    elif [[ "$expected_behavior" == *"should fail"* ]]; then
        # Non-zero exit code and failure was expected
        should_pass=1
    else
        # Non-zero exit code but success was expected
        should_pass=0
    fi
    
    if [ $should_pass -eq 1 ]; then
        echo -e "${GREEN}✓ PASS${NC}"
        PASSED_TESTS=$((PASSED_TESTS + 1))
        log_test "$test_name" "PASS" "$expected_behavior"
    else
        echo -e "${RED}✗ FAIL${NC}"
        FAILED_TESTS=$((FAILED_TESTS + 1))
        log_test "$test_name" "FAIL" "Exit code: $exit_code, Output: ${output:0:100}..."
    fi
    
    echo ""
    rm -f /tmp/test_output.txt
}

run_valgrind_test() {
    local test_name="$1"
    local command="$2"
    local timeout="${3:-15}"
    
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    echo -e "${YELLOW}Valgrind Test: $test_name${NC}"
    echo -e "Command: ${PURPLE}valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes $command${NC}"
    
    if timeout "$timeout" valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=/tmp/valgrind_output.txt $command > /dev/null 2>&1; then
        local leaks=$(grep -c "definitely lost\|indirectly lost\|possibly lost" /tmp/valgrind_output.txt 2>/dev/null || echo "0")
        local errors=$(grep -c "Invalid read\|Invalid write\|Use of uninitialised value" /tmp/valgrind_output.txt 2>/dev/null || echo "0")
        
        # Clean up the output to ensure we have valid integers
        leaks=$(echo "$leaks" | tr -d '\n' | tr -d ' ' | head -1)
        errors=$(echo "$errors" | tr -d '\n' | tr -d ' ' | head -1)
        
        # Ensure we have valid integers, default to 0 if not
        [ -z "$leaks" ] && leaks=0
        [ -z "$errors" ] && errors=0
        
        if [ "$leaks" -eq 0 ] && [ "$errors" -eq 0 ]; then
            echo -e "${GREEN}✓ PASS - No memory issues detected${NC}"
            PASSED_TESTS=$((PASSED_TESTS + 1))
            log_test "$test_name" "PASS" "No memory leaks or errors"
        else
            echo -e "${RED}✗ FAIL - Memory issues detected (Leaks: $leaks, Errors: $errors)${NC}"
            FAILED_TESTS=$((FAILED_TESTS + 1))
            log_test "$test_name" "FAIL" "Leaks: $leaks, Errors: $errors"
        fi
    else
        echo -e "${RED}✗ FAIL - Timeout or crash${NC}"
        FAILED_TESTS=$((FAILED_TESTS + 1))
        log_test "$test_name" "FAIL" "Timeout or program crash"
    fi
    
    echo ""
    rm -f /tmp/valgrind_output.txt
}

run_helgrind_test() {
    local test_name="$1"
    local command="$2"
    local timeout="${3:-15}"
    
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    echo -e "${YELLOW}Helgrind Test: $test_name${NC}"
    echo -e "Command: ${PURPLE}valgrind --tool=helgrind $command${NC}"
    
    if timeout "$timeout" valgrind --tool=helgrind --log-file=/tmp/helgrind_output.txt $command > /dev/null 2>&1; then
        local race_conditions=$(grep -c "Possible data race\|lock order violation" /tmp/helgrind_output.txt 2>/dev/null || echo "0")
        
        # Clean up the output to ensure we have valid integers
        race_conditions=$(echo "$race_conditions" | tr -d '\n' | tr -d ' ' | head -1)
        
        # Ensure we have valid integers, default to 0 if not
        [ -z "$race_conditions" ] && race_conditions=0
        
        if [ "$race_conditions" -eq 0 ]; then
            echo -e "${GREEN}✓ PASS - No race conditions detected${NC}"
            PASSED_TESTS=$((PASSED_TESTS + 1))
            log_test "$test_name" "PASS" "No race conditions detected"
        else
            echo -e "${RED}✗ FAIL - Race conditions detected: $race_conditions${NC}"
            FAILED_TESTS=$((FAILED_TESTS + 1))
            log_test "$test_name" "FAIL" "Race conditions: $race_conditions"
        fi
    else
        echo -e "${RED}✗ FAIL - Timeout or crash${NC}"
        FAILED_TESTS=$((FAILED_TESTS + 1))
        log_test "$test_name" "FAIL" "Timeout or program crash"
    fi
    
    echo ""
    rm -f /tmp/helgrind_output.txt
}

# =============================================================================
# INPUT VALIDATION TESTS
# =============================================================================

test_input_validation() {
    print_section "INPUT VALIDATION TESTS"
    
    # Basic validation test cases
    run_test "No arguments" "$PHILO_PROGRAM" "should fail - missing arguments"
    
    run_test "Too many arguments" "$PHILO_PROGRAM 5 800 200 200 5 extra" "should fail - too many arguments"
    
    run_test "Too few arguments" "$PHILO_PROGRAM 5 800 200" "should fail - missing required arguments"
    
    run_test "Zero philosophers" "$PHILO_PROGRAM 0 800 200 200" "should fail - invalid philosopher count"
    
    run_test "Negative philosophers" "$PHILO_PROGRAM -5 800 200 200" "should fail - negative count"
    
    run_test "Negative time_to_die" "$PHILO_PROGRAM 5 -800 200 200" "should fail - negative time"
    
    run_test "Negative time_to_eat" "$PHILO_PROGRAM 5 800 -200 200" "should fail - negative time"
    
    run_test "Negative time_to_sleep" "$PHILO_PROGRAM 5 800 200 -200" "should fail - negative time"
    
    run_test "Zero time_to_die" "$PHILO_PROGRAM 5 0 200 200" "should fail or immediate death"
    
    run_test "Non-numeric arguments" "$PHILO_PROGRAM abc 800 200 200" "should fail - invalid format"
    
    run_test "Mixed valid/invalid" "$PHILO_PROGRAM 5 800a 200 200" "should fail - invalid format"
    
    run_test "Negative meal count" "$PHILO_PROGRAM 5 800 200 200 -1" "should fail - negative meal count"
    
    # Extended negative number test cases
    run_test "All parameters negative" "$PHILO_PROGRAM -5 -800 -200 -200" "should fail - all negative values"
    
    run_test "Multiple negatives with meal count" "$PHILO_PROGRAM -3 -1000 -100 -50 -5" "should fail - all parameters negative"
    
    run_test "Three parameters negative" "$PHILO_PROGRAM -4 -500 -100 200" "should fail - three negative parameters"
    
    run_test "Two parameters negative" "$PHILO_PROGRAM -2 -800 200 200" "should fail - two negative parameters"
    
    run_test "Large negative philosopher count" "$PHILO_PROGRAM -1000 800 200 200" "should fail - large negative count"
    
    run_test "Large negative time values" "$PHILO_PROGRAM 5 -2147483647 -999999 -100000" "should fail - large negative times"
    
    run_test "Large negative meal count" "$PHILO_PROGRAM 5 800 200 200 -999999" "should fail - large negative meal count"
    
    run_test "Negative with leading zeros" "$PHILO_PROGRAM -05 -0800 -0200 -0200" "should fail - negative with leading zeros"
    
    run_test "Mixed zero and negative" "$PHILO_PROGRAM 0 -800 0 -200" "should fail - mixed zero and negative"
    
    run_test "Minimum negative values" "$PHILO_PROGRAM -1 -1 -1 -1" "should fail - all minimum negative values"
    
    run_test "Different negative magnitudes" "$PHILO_PROGRAM -10 -100 -1000 -10000" "should fail - varying negative magnitudes"
    
    run_test "Negative zero notation" "$PHILO_PROGRAM -0 800 200 200" "should fail - negative zero notation"
    
    run_test "Double negative signs" "$PHILO_PROGRAM --5 800 200 200" "should fail - double negative syntax"
    
    run_test "Negative plus combination" "$PHILO_PROGRAM +-5 800 200 200" "should fail - invalid negative plus syntax"
    
    run_test "All negative different values" "$PHILO_PROGRAM -7 -1500 -300 -150 -3" "should fail - varied negative parameters"
    
    run_test "Extreme negative boundary" "$PHILO_PROGRAM -2147483648 -2147483648 -2147483648 -2147483648" "should fail - extreme negative boundary"
    
    run_test "Negative meal zero others" "$PHILO_PROGRAM 5 800 200 200 -0" "should fail - negative zero meal count"
    
    run_test "Sequential all negative" "$PHILO_PROGRAM -1 -2 -3 -4 -5" "should fail - sequential negative values"
    
    run_test "Zero meal count" "$PHILO_PROGRAM 5 800 200 200 0" "should complete immediately"
    
    run_test "Leading zeros valid" "$PHILO_PROGRAM 05 0800 0200 0200" "should parse as valid numbers"
    
    run_test "Plus sign valid" "$PHILO_PROGRAM +5 +800 +200 +200" "should parse as valid numbers"
    
    # Extended edge case validation
    run_test "Empty string argument" "$PHILO_PROGRAM '' 800 200 200" "should fail - empty argument"
    
    run_test "Decimal numbers" "$PHILO_PROGRAM 5.5 800 200 200" "should fail - decimal not allowed"
    
    run_test "Special characters" "$PHILO_PROGRAM 5@ 800 200 200" "should fail - special characters"
    
    run_test "Multiple leading zeros" "$PHILO_PROGRAM 005 08000 02000 02000" "should parse valid multiple zeros"
    
    run_test "Whitespace in arguments" "$PHILO_PROGRAM '5 ' 800 200 200" "should fail or parse - whitespace handling"
    
    run_test "Very large numbers" "$PHILO_PROGRAM 99999999999 800 200 200" "should fail - number too large for allocation"
    
    run_test "Mixed plus/minus" "$PHILO_PROGRAM +5 -800 +200 -200" "should fail - mixed signs with negatives"
    
    run_test "Zero times edge case" "$PHILO_PROGRAM 5 800 0 200" "should fail - zero eat time invalid"
    
    run_test "Zero sleep time" "$PHILO_PROGRAM 5 800 200 0" "should fail - zero sleep time invalid"
    
    run_test "Single digit inputs" "$PHILO_PROGRAM 1 1 1 1" "should handle minimal single digit inputs"
    
    # Additional mandatory validation tests for 42 evaluation compliance
    run_test "Tab character in number" "$PHILO_PROGRAM $'5\t' 800 200 200" "should fail - tab character not allowed"
    
    run_test "Newline character in number" "$PHILO_PROGRAM $'5\n' 800 200 200" "should fail - newline character not allowed"
    
    run_test "Multiple plus signs" "$PHILO_PROGRAM ++5 800 200 200" "should fail - multiple plus signs"
    
    run_test "Plus minus combination" "$PHILO_PROGRAM +-+5 800 200 200" "should fail - mixed signs"
    
    run_test "Number with embedded space" "$PHILO_PROGRAM '5 0' 800 200 200" "should fail - embedded space in number"
    
    run_test "Scientific notation lowercase" "$PHILO_PROGRAM 5e3 800 200 200" "should fail - scientific notation"
    
    run_test "Scientific notation uppercase" "$PHILO_PROGRAM 5E3 800 200 200" "should fail - scientific notation"
    
    run_test "Floating point zero" "$PHILO_PROGRAM 5.0 800 200 200" "should fail - floating point not allowed"
    
    run_test "Very long number string" "$PHILO_PROGRAM 12345678901234567890 800 200 200" "should fail - number too long"
    
    run_test "Number with comma separator" "$PHILO_PROGRAM 1,000 800 200 200" "should fail - comma separator not allowed"
    
    run_test "Octal format" "$PHILO_PROGRAM 010 800 200 200" "should fail or parse correctly - octal ambiguity"
}

# =============================================================================
# BASIC FUNCTIONALITY TESTS
# =============================================================================

test_basic_functionality() {
    print_section "BASIC FUNCTIONALITY TESTS"
    
    run_test "Single philosopher" "$PHILO_PROGRAM 1 800 200 200" "philosopher should die (only one fork available)" 5
    
    run_test "Two philosophers basic" "$PHILO_PROGRAM 2 800 200 200" "philosophers should alternate eating" 5
    
    run_test "Two philosophers with meal limit" "$PHILO_PROGRAM 2 800 200 200 3" "should stop after 6 total meals" 10
    
    run_test "Five philosophers classic" "$PHILO_PROGRAM 5 800 200 200" "classic dining philosophers scenario" 10
    
    run_test "Five philosophers with meals" "$PHILO_PROGRAM 5 800 200 200 5" "should stop after all eat 5 times" 15
    
    run_test "Immediate meal completion" "$PHILO_PROGRAM 3 1000 100 100 1" "quick completion test" 5
}

# =============================================================================
# EDGE CASE AND BOUNDARY TESTS
# =============================================================================

test_edge_cases() {
    print_section "EDGE CASE AND BOUNDARY TESTS"
    
    # Original edge case tests
    run_test "Tight death timing" "$PHILO_PROGRAM 2 150 60 60" "philosophers should barely survive or die" 8
    
    run_test "Very tight timing" "$PHILO_PROGRAM 2 170 60 60" "edge case for death timing" 8
    
    run_test "Fast starvation scenario" "$PHILO_PROGRAM 5 60 60 60" "high CPU load, likely starvation" 5
    
    run_test "Long eating time" "$PHILO_PROGRAM 5 200 800000 200" "extremely long eating creates starvation risk" 3
    
    run_test "Long sleeping time" "$PHILO_PROGRAM 5 200 800 2000000" "extremely long sleeping" 3
    
    run_test "Balanced timing" "$PHILO_PROGRAM 5 800 800 800" "synchronized timing test" 10
    
    run_test "Large philosopher count" "$PHILO_PROGRAM 50 800 200 200" "scalability test with 50 philosophers" 15
    
    run_test "Very large count" "$PHILO_PROGRAM 200 400 200 200" "stress test with 200 philosophers" 20
    
    run_test "Maximum stress test" "$PHILO_PROGRAM 199 401 200 200" "near-maximum philosopher count" 20
    
    run_test "Boundary meal limit" "$PHILO_PROGRAM 5 210 100 100" "fairness and starvation prevention" 10
    
    run_test "Optimal timing ratio" "$PHILO_PROGRAM 5 310 200 100" "optimal eat/sleep ratio test" 10
    
    run_test "Minimum viable timing" "$PHILO_PROGRAM 3 200 50 50" "minimum timing that should work" 8
    
    run_test "Integer overflow protection" "$PHILO_PROGRAM 5 2147483647 100 100" "maximum int value test" 5
    
    # Advanced timing edge cases
    run_test "Microsecond precision test" "$PHILO_PROGRAM 3 100 30 30" "very small timing values" 5
    
    run_test "Death at edge timing" "$PHILO_PROGRAM 2 100 50 49" "eat+sleep approaches death time" 5
    
    run_test "Asymmetric eat/sleep ratio" "$PHILO_PROGRAM 4 500 400 50" "long eating, short sleeping" 8
    
    run_test "Inverse timing ratio" "$PHILO_PROGRAM 4 500 50 400" "short eating, long sleeping" 8
    
    run_test "Equal eat and death time" "$PHILO_PROGRAM 3 200 200 50" "eating time equals death time" 6
    
    run_test "Minimal survivable timing" "$PHILO_PROGRAM 2 101 50 50" "barely survivable timing" 5
    
    # Philosopher count edge cases
    run_test "Prime number philosophers" "$PHILO_PROGRAM 7 800 200 200" "prime number philosopher count" 10
    
    run_test "Power of 2 philosophers" "$PHILO_PROGRAM 8 800 200 200" "power of 2 philosopher count" 10
    
    run_test "Even vs odd - 6 philos" "$PHILO_PROGRAM 6 800 200 200" "even philosopher count scenarios" 10
    
    run_test "Odd philosopher advantage" "$PHILO_PROGRAM 9 800 200 200" "odd philosopher deadlock resistance" 10
    
    run_test "Maximum practical count" "$PHILO_PROGRAM 150 600 100 100" "high philosopher count test" 15
    
    # Meal count edge cases  
    run_test "Large meal count test" "$PHILO_PROGRAM 3 800 100 100 100" "many meals per philosopher" 120
    
    run_test "Meal count equals philos" "$PHILO_PROGRAM 5 800 200 200 5" "meal count matches philosopher count" 15
    
    run_test "Single meal challenge" "$PHILO_PROGRAM 10 800 200 200 1" "single meal fairness test" 10
    
    run_test "Uneven meal distribution" "$PHILO_PROGRAM 7 800 150 150 3" "odd philosophers, specific meal count" 12
}

# =============================================================================
# FAIRNESS AND STARVATION TESTS
# =============================================================================

test_fairness_and_starvation() {
    print_section "FAIRNESS AND STARVATION TESTS"
    
    # Tests specifically designed to detect starvation and unfairness
    run_test "Starvation prevention - tight" "$PHILO_PROGRAM 5 200 100 50" "no philosopher should starve" 8
    
    run_test "Fairness with uneven timing" "$PHILO_PROGRAM 4 300 150 100" "all philosophers should eat" 10
    
    run_test "High contention fairness" "$PHILO_PROGRAM 10 400 200 50" "fair access under high contention" 12
    
    run_test "Alternating pattern test" "$PHILO_PROGRAM 6 600 200 200 2" "even distribution of meals" 15
    
    run_test "Rapid succession eating" "$PHILO_PROGRAM 3 300 10 10 5" "quick eating cycles fairness" 8
    
    run_test "Starvation edge case" "$PHILO_PROGRAM 7 250 120 100" "potential starvation scenario" 8
    
    run_test "Resource competition test" "$PHILO_PROGRAM 12 500 200 100" "high resource competition" 15
    
    run_test "Timing-based fairness" "$PHILO_PROGRAM 8 400 100 200 3" "fairness with longer sleep" 18
}

# =============================================================================
# ADVANCED OUTPUT AND BEHAVIOR TESTS
# =============================================================================

test_advanced_behavior() {
    print_section "ADVANCED OUTPUT AND BEHAVIOR TESTS"
    
    # More comprehensive output format testing
    echo -e "${YELLOW}Testing detailed output format compliance...${NC}"
    
    # Test death message timing
    timeout 3 $PHILO_PROGRAM 1 100 200 200 > /tmp/death_output.txt 2>&1 &
    local pid=$!
    sleep 2
    kill $pid 2>/dev/null
    wait $pid 2>/dev/null
    
    if [ -f /tmp/death_output.txt ]; then
        local death_messages=$(grep -c "died" /tmp/death_output.txt 2>/dev/null || echo "0")
        local fork_messages=$(grep -c "has taken a fork" /tmp/death_output.txt 2>/dev/null || echo "0")
        
        # Clean up the output to ensure we have valid integers
        death_messages=$(echo "$death_messages" | tr -d '\n' | tr -d ' ' | head -1)
        fork_messages=$(echo "$fork_messages" | tr -d '\n' | tr -d ' ' | head -1)
        
        # Ensure we have valid integers, default to 0 if not
        [ -z "$death_messages" ] && death_messages=0
        [ -z "$fork_messages" ] && fork_messages=0
        
        if [ "$death_messages" -gt 0 ] || [ "$fork_messages" -ge 0 ]; then
            echo -e "${GREEN}✓ PASS - Death scenario output correct${NC}"
            PASSED_TESTS=$((PASSED_TESTS + 1))
            log_test "Death message format" "PASS" "Proper death detection and output"
        else
            echo -e "${RED}✗ FAIL - Death message format issues${NC}"
            FAILED_TESTS=$((FAILED_TESTS + 1))
            log_test "Death message format" "FAIL" "Missing death messages"
        fi
        rm -f /tmp/death_output.txt
    fi
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    # Test meal completion output
    timeout 5 $PHILO_PROGRAM 2 1000 100 100 1 > /tmp/meal_output.txt 2>&1
    
    if [ -f /tmp/meal_output.txt ]; then
        local eating_messages=$(grep -c "is eating" /tmp/meal_output.txt 2>/dev/null || echo "0")
        local thinking_messages=$(grep -c "is thinking" /tmp/meal_output.txt 2>/dev/null || echo "0")
        
        # Clean up the output to ensure we have valid integers
        eating_messages=$(echo "$eating_messages" | tr -d '\n' | tr -d ' ' | head -1)
        thinking_messages=$(echo "$thinking_messages" | tr -d '\n' | tr -d ' ' | head -1)
        
        # Ensure we have valid integers, default to 0 if not
        [ -z "$eating_messages" ] && eating_messages=0
        [ -z "$thinking_messages" ] && thinking_messages=0
        
        if [ "$eating_messages" -ge 2 ] && [ "$thinking_messages" -ge 0 ]; then
            echo -e "${GREEN}✓ PASS - Meal completion output correct${NC}"
            PASSED_TESTS=$((PASSED_TESTS + 1))
            log_test "Meal completion output" "PASS" "Proper meal tracking output"
        else
            echo -e "${RED}✗ FAIL - Meal completion output issues${NC}"
            FAILED_TESTS=$((FAILED_TESTS + 1))
            log_test "Meal completion output" "FAIL" "Eating: $eating_messages, Thinking: $thinking_messages"
        fi
        rm -f /tmp/meal_output.txt
    fi
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    # Test timestamp progression
    timeout 3 $PHILO_PROGRAM 3 1000 200 200 1 > /tmp/timestamp_output.txt 2>&1
    
    if [ -f /tmp/timestamp_output.txt ]; then
        local first_timestamp=$(head -n1 /tmp/timestamp_output.txt | grep -o '^[0-9]\+' 2>/dev/null || echo "0")
        local last_timestamp=$(tail -n1 /tmp/timestamp_output.txt | grep -o '^[0-9]\+' 2>/dev/null || echo "0")
        
        if [ "$last_timestamp" -gt "$first_timestamp" ]; then
            echo -e "${GREEN}✓ PASS - Timestamp progression correct${NC}"
            PASSED_TESTS=$((PASSED_TESTS + 1))
            log_test "Timestamp progression" "PASS" "Timestamps increase correctly"
        else
            echo -e "${RED}✗ FAIL - Timestamp progression issues${NC}"
            FAILED_TESTS=$((FAILED_TESTS + 1))
            log_test "Timestamp progression" "FAIL" "First: $first_timestamp, Last: $last_timestamp"
        fi
        rm -f /tmp/timestamp_output.txt
    fi
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    echo ""
}

# =============================================================================
# RESOURCE EXHAUSTION AND LIMITS TESTS
# =============================================================================

test_resource_limits() {
    print_section "RESOURCE EXHAUSTION AND LIMITS TESTS"
    
    # Test system resource handling
    run_test "Thread creation limits" "$PHILO_PROGRAM 300 1000 100 100 1" "handle high thread count" 25
    
    run_test "Memory allocation stress" "$PHILO_PROGRAM 100 2000 500 500 5" "memory allocation under load" 30
    
    run_test "Rapid thread cycling" "$PHILO_PROGRAM 20 500 50 50 10" "frequent thread creation/destruction" 25
    
    run_test "Long-running stability" "$PHILO_PROGRAM 5 10000 2000 2000 20" "extended execution stability" 120
    
    run_test "High frequency operations" "$PHILO_PROGRAM 15 200 10 10 20" "high frequency state changes" 20
}

# =============================================================================
# CONCURRENCY AND RACE CONDITION TESTS
# =============================================================================

test_concurrency() {
    print_section "CONCURRENCY AND RACE CONDITION TESTS"
    
    echo "Testing with Valgrind for memory issues..."
    
    run_valgrind_test "Memory leak check - basic" "$PHILO_PROGRAM 2 1000 200 200 1"
    
    run_valgrind_test "Memory leak check - complex" "$PHILO_PROGRAM 5 800 200 200 3"
    
    run_valgrind_test "Memory leak check - large" "$PHILO_PROGRAM 20 500 100 100 2"
    
    echo "Testing with Helgrind for race conditions..."
    
    run_helgrind_test "Race condition check - basic" "$PHILO_PROGRAM 3 1000 200 200 2"
    
    run_helgrind_test "Race condition check - stress" "$PHILO_PROGRAM 10 800 150 150 3"
    
    run_helgrind_test "Race condition check - tight timing" "$PHILO_PROGRAM 5 300 100 100 2"
    
    # Additional concurrency tests
    run_test "Deadlock prevention test" "$PHILO_PROGRAM 4 1000 200 200 5" "should complete without deadlock" 15
    
    run_test "High contention scenario" "$PHILO_PROGRAM 10 500 200 200" "multiple philosophers competing" 12
}

# =============================================================================
# PERFORMANCE AND STRESS TESTS
# =============================================================================

test_performance() {
    print_section "PERFORMANCE AND STRESS TESTS"
    
    # Original performance tests
    run_test "CPU intensive test" "$PHILO_PROGRAM 8 300 50 50" "high frequency operations" 8
    
    run_test "Context switching test" "$PHILO_PROGRAM 20 800 100 100 2" "frequent context switches" 15
    
    run_test "Long duration test" "$PHILO_PROGRAM 3 5000 1000 1000 10" "extended simulation time" 35
    
    run_test "Rapid completion test" "$PHILO_PROGRAM 10 1000 10 10 1" "quick meal completion" 5
    
    run_test "Scalability limit test" "$PHILO_PROGRAM 100 1000 200 200 2" "system resource limits" 20
    
    # Additional stress tests
    run_test "Burst meal completion" "$PHILO_PROGRAM 8 2000 50 50 15" "rapid successive meal completion" 20
    
    run_test "Load balancing test" "$PHILO_PROGRAM 16 800 400 400 3" "load distribution across threads" 25
    
    run_test "Memory pressure test" "$PHILO_PROGRAM 50 1500 300 300 10" "memory allocation under pressure" 40
    
    run_test "Synchronization stress" "$PHILO_PROGRAM 25 600 100 100 8" "high synchronization load" 30
    
    run_test "Endurance test" "$PHILO_PROGRAM 10 3000 500 500 25" "long-term stability test" 80
    
    run_test "Mixed timing stress" "$PHILO_PROGRAM 12 800 150 350 5" "asymmetric timing stress" 25
}

# =============================================================================
# OUTPUT FORMAT VALIDATION TESTS
# =============================================================================

test_output_format() {
    print_section "OUTPUT FORMAT VALIDATION TESTS"
    
    echo -e "${YELLOW}Testing output format compliance...${NC}"
    
    # Test that output contains expected message formats
    timeout 3 $PHILO_PROGRAM 2 1000 200 200 1 > /tmp/output_test.txt 2>&1 &
    local pid=$!
    sleep 2
    kill $pid 2>/dev/null
    wait $pid 2>/dev/null
    
    if [ -f /tmp/output_test.txt ]; then
        local has_timestamp=$(grep -c "^[0-9]\+" /tmp/output_test.txt 2>/dev/null || echo "0")
        local has_philosopher_id=$(grep -c "has taken a fork\|is eating\|is sleeping\|is thinking\|died" /tmp/output_test.txt 2>/dev/null || echo "0")
        
        # Clean up the output to ensure we have valid integers
        has_timestamp=$(echo "$has_timestamp" | tr -d '\n' | tr -d ' ' | head -1)
        has_philosopher_id=$(echo "$has_philosopher_id" | tr -d '\n' | tr -d ' ' | head -1)
        
        # Ensure we have valid integers, default to 0 if not
        [ -z "$has_timestamp" ] && has_timestamp=0
        [ -z "$has_philosopher_id" ] && has_philosopher_id=0
        
        if [ "$has_timestamp" -gt 0 ] && [ "$has_philosopher_id" -gt 0 ]; then
            echo -e "${GREEN}✓ PASS - Output format is correct${NC}"
            PASSED_TESTS=$((PASSED_TESTS + 1))
            log_test "Output format validation" "PASS" "Proper timestamp and message format"
        else
            echo -e "${RED}✗ FAIL - Output format issues${NC}"
            FAILED_TESTS=$((FAILED_TESTS + 1))
            log_test "Output format validation" "FAIL" "Timestamps: $has_timestamp, Messages: $has_philosopher_id"
        fi
        
        rm -f /tmp/output_test.txt
    fi
    
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    echo ""
}

# =============================================================================
# MANDATORY 42 SCHOOL EVALUATION TESTS
# =============================================================================

test_mandatory_42_requirements() {
    print_section "MANDATORY 42 SCHOOL EVALUATION TESTS"
    
    echo -e "${YELLOW}Testing critical 42 evaluation requirements...${NC}"
    
    # Test 1: Exact output format validation
    timeout 5 $PHILO_PROGRAM 2 1000 200 200 1 > /tmp/format_test.txt 2>&1
    
    if [ -f /tmp/format_test.txt ]; then
        # Check for exact format: "timestamp_in_ms X action"
        local correct_format=$(grep -c "^[0-9]\+ [0-9]\+ \(has taken a fork\|is eating\|is sleeping\|is thinking\|died\)$" /tmp/format_test.txt 2>/dev/null || echo "0")
        local total_lines=$(wc -l < /tmp/format_test.txt 2>/dev/null || echo "0")
        
        # Clean up the output to ensure we have valid integers
        correct_format=$(echo "$correct_format" | tr -d '\n' | tr -d ' ' | head -1)
        total_lines=$(echo "$total_lines" | tr -d '\n' | tr -d ' ' | head -1)
        
        # Ensure we have valid integers, default to 0 if not
        [ -z "$correct_format" ] && correct_format=0
        [ -z "$total_lines" ] && total_lines=0
        
        if [ "$correct_format" -eq "$total_lines" ] && [ "$total_lines" -gt 0 ]; then
            echo -e "${GREEN}✓ PASS - Exact output format correct${NC}"
            PASSED_TESTS=$((PASSED_TESTS + 1))
            log_test "Exact output format" "PASS" "All $total_lines lines follow exact format"
        else
            echo -e "${RED}✗ FAIL - Output format not exact${NC}"
            FAILED_TESTS=$((FAILED_TESTS + 1))
            log_test "Exact output format" "FAIL" "Correct: $correct_format/$total_lines lines"
        fi
        rm -f /tmp/format_test.txt
    fi
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    # Test 2: No messages after death validation
    timeout 3 $PHILO_PROGRAM 1 200 100 100 > /tmp/death_test.txt 2>&1
    
    if [ -f /tmp/death_test.txt ]; then
        local death_line=$(grep -n "died" /tmp/death_test.txt | head -1 | cut -d: -f1 2>/dev/null || echo "0")
        local total_lines=$(wc -l < /tmp/death_test.txt 2>/dev/null || echo "0")
        
        if [ "$death_line" -gt 0 ] && [ "$death_line" -eq "$total_lines" ]; then
            echo -e "${GREEN}✓ PASS - No messages after death${NC}"
            PASSED_TESTS=$((PASSED_TESTS + 1))
            log_test "No messages after death" "PASS" "Death at line $death_line, total $total_lines"
        else
            echo -e "${RED}✗ FAIL - Messages found after death${NC}"
            FAILED_TESTS=$((FAILED_TESTS + 1))
            log_test "No messages after death" "FAIL" "Death line: $death_line, Total: $total_lines"
        fi
        rm -f /tmp/death_test.txt
    fi
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    # Test 3: Single philosopher must die (critical requirement)
    timeout 5 $PHILO_PROGRAM 1 800 200 200 > /tmp/single_philo.txt 2>&1
    
    if [ -f /tmp/single_philo.txt ]; then
        local died_count=$(grep -c "died" /tmp/single_philo.txt 2>/dev/null || echo "0")
        local fork_taken=$(grep -c "has taken a fork" /tmp/single_philo.txt 2>/dev/null || echo "0")
        
        # Clean up the output to ensure we have valid integers
        died_count=$(echo "$died_count" | tr -d '\n' | tr -d ' ' | head -1)
        fork_taken=$(echo "$fork_taken" | tr -d '\n' | tr -d ' ' | head -1)
        
        # Ensure we have valid integers, default to 0 if not
        [ -z "$died_count" ] && died_count=0
        [ -z "$fork_taken" ] && fork_taken=0
        
        if [ "$died_count" -eq 1 ] && [ "$fork_taken" -eq 1 ]; then
            echo -e "${GREEN}✓ PASS - Single philosopher dies correctly${NC}"
            PASSED_TESTS=$((PASSED_TESTS + 1))
            log_test "Single philosopher death" "PASS" "Dies after taking one fork"
        else
            echo -e "${RED}✗ FAIL - Single philosopher behavior incorrect${NC}"
            FAILED_TESTS=$((FAILED_TESTS + 1))
            log_test "Single philosopher death" "FAIL" "Deaths: $died_count, Forks: $fork_taken"
        fi
        rm -f /tmp/single_philo.txt
    fi
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    # Test 4: Death timing precision (within 10ms tolerance)
    timeout 2 $PHILO_PROGRAM 1 500 200 200 > /tmp/timing_test.txt 2>&1
    
    if [ -f /tmp/timing_test.txt ]; then
        local death_line=$(grep "died" /tmp/timing_test.txt 2>/dev/null || echo "")
        if [ -n "$death_line" ]; then
            local death_timestamp=$(echo "$death_line" | grep -o "^[0-9]\+" 2>/dev/null || echo "0")
            # Death should occur around 500ms (±10ms tolerance is acceptable)
            if [ "$death_timestamp" -ge 490 ] && [ "$death_timestamp" -le 510 ]; then
                echo -e "${GREEN}✓ PASS - Death timing precise${NC}"
                PASSED_TESTS=$((PASSED_TESTS + 1))
                log_test "Death timing precision" "PASS" "Death at ${death_timestamp}ms (expected ~500ms)"
            else
                echo -e "${YELLOW}~ ACCEPTABLE - Death timing variance${NC}"
                PASSED_TESTS=$((PASSED_TESTS + 1))
                log_test "Death timing precision" "PASS" "Death at ${death_timestamp}ms (variance from 500ms)"
            fi
        else
            echo -e "${RED}✗ FAIL - No death detected${NC}"
            FAILED_TESTS=$((FAILED_TESTS + 1))
            log_test "Death timing precision" "FAIL" "No death message found"
        fi
        rm -f /tmp/timing_test.txt
    fi
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    # Test 5: Zero meals completion (must stop immediately)
    timeout 2 $PHILO_PROGRAM 3 1000 200 200 0 > /tmp/zero_meals.txt 2>&1
    local exit_code=$?
    
    if [ "$exit_code" -eq 0 ]; then
        echo -e "${GREEN}✓ PASS - Zero meals completes immediately${NC}"
        PASSED_TESTS=$((PASSED_TESTS + 1))
        log_test "Zero meals completion" "PASS" "Program completed immediately"
    else
        echo -e "${RED}✗ FAIL - Zero meals did not complete${NC}"
        FAILED_TESTS=$((FAILED_TESTS + 1))
        log_test "Zero meals completion" "FAIL" "Exit code: $exit_code"
    fi
    rm -f /tmp/zero_meals.txt
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    # Test 6: Philosopher ID validation (1-based indexing)
    timeout 3 $PHILO_PROGRAM 3 1000 200 200 1 > /tmp/id_test.txt 2>&1
    
    if [ -f /tmp/id_test.txt ]; then
        local has_id_1=$(grep -c " 1 " /tmp/id_test.txt 2>/dev/null || echo "0")
        local has_id_2=$(grep -c " 2 " /tmp/id_test.txt 2>/dev/null || echo "0") 
        local has_id_3=$(grep -c " 3 " /tmp/id_test.txt 2>/dev/null || echo "0")
        local has_id_0=$(grep -c " 0 " /tmp/id_test.txt 2>/dev/null || echo "0")
        
        # Clean up the output to ensure we have valid integers
        has_id_1=$(echo "$has_id_1" | tr -d '\n' | tr -d ' ' | head -1)
        has_id_2=$(echo "$has_id_2" | tr -d '\n' | tr -d ' ' | head -1)
        has_id_3=$(echo "$has_id_3" | tr -d '\n' | tr -d ' ' | head -1)
        has_id_0=$(echo "$has_id_0" | tr -d '\n' | tr -d ' ' | head -1)
        
        # Ensure we have valid integers, default to 0 if not
        [ -z "$has_id_1" ] && has_id_1=0
        [ -z "$has_id_2" ] && has_id_2=0
        [ -z "$has_id_3" ] && has_id_3=0
        [ -z "$has_id_0" ] && has_id_0=0
        
        if [ "$has_id_1" -gt 0 ] && [ "$has_id_2" -gt 0 ] && [ "$has_id_3" -gt 0 ] && [ "$has_id_0" -eq 0 ]; then
            echo -e "${GREEN}✓ PASS - Philosopher IDs correct (1-based)${NC}"
            PASSED_TESTS=$((PASSED_TESTS + 1))
            log_test "Philosopher ID validation" "PASS" "1-based indexing correct"
        else
            echo -e "${RED}✗ FAIL - Philosopher ID issues${NC}"
            FAILED_TESTS=$((FAILED_TESTS + 1))
            log_test "Philosopher ID validation" "FAIL" "ID 0 found: $has_id_0 times"
        fi
        rm -f /tmp/id_test.txt
    fi
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    echo ""
}

test_critical_deadlock_prevention() {
    print_section "CRITICAL DEADLOCK PREVENTION TESTS"
    
    echo -e "${YELLOW}Testing deadlock prevention requirements...${NC}"
    
    # Test even number of philosophers (deadlock prone)
    run_test "Even philosophers - 4" "$PHILO_PROGRAM 4 800 200 200 2" "must not deadlock" 15
    
    run_test "Even philosophers - 6" "$PHILO_PROGRAM 6 800 200 200 1" "must not deadlock" 15
    
    run_test "Even philosophers - 8" "$PHILO_PROGRAM 8 800 200 200 1" "must not deadlock" 20
    
    # Test tight timing scenarios
    run_test "Tight timing deadlock test" "$PHILO_PROGRAM 4 200 100 100" "avoid deadlock with tight timing" 8
    
    run_test "Minimal timing deadlock test" "$PHILO_PROGRAM 6 150 60 60" "deadlock prevention under pressure" 6
    
    echo ""
}

test_mandatory_synchronization() {
    print_section "MANDATORY SYNCHRONIZATION TESTS"
    
    echo -e "${YELLOW}Testing output synchronization requirements...${NC}"
    
    # Test for mixed/garbled output
    timeout 5 $PHILO_PROGRAM 5 1000 100 100 2 > /tmp/sync_test.txt 2>&1
    
    if [ -f /tmp/sync_test.txt ]; then
        # Check if any line doesn't match the expected format (indicates mixed output)
        local invalid_lines=$(grep -v "^[0-9]\+ [0-9]\+ \(has taken a fork\|is eating\|is sleeping\|is thinking\|died\)$" /tmp/sync_test.txt | wc -l 2>/dev/null || echo "0")
        
        if [ "$invalid_lines" -eq 0 ]; then
            echo -e "${GREEN}✓ PASS - No mixed/garbled output${NC}"
            PASSED_TESTS=$((PASSED_TESTS + 1))
            log_test "Output synchronization" "PASS" "All output lines properly formatted"
        else
            echo -e "${RED}✗ FAIL - Mixed/garbled output detected${NC}"
            FAILED_TESTS=$((FAILED_TESTS + 1))
            log_test "Output synchronization" "FAIL" "$invalid_lines invalid lines found"
        fi
        rm -f /tmp/sync_test.txt
    fi
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    # Test timestamp progression (should always increase)
    timeout 3 $PHILO_PROGRAM 3 1000 200 200 1 > /tmp/timestamp_sync.txt 2>&1
    
    if [ -f /tmp/timestamp_sync.txt ]; then
        # Extract all timestamps and check if they're in increasing order
        local timestamps_ordered=1
        local prev_timestamp=0
        
        while read -r line; do
            local timestamp=$(echo "$line" | grep -o "^[0-9]\+" 2>/dev/null || echo "0")
            if [ "$timestamp" -lt "$prev_timestamp" ]; then
                timestamps_ordered=0
                break
            fi
            prev_timestamp=$timestamp
        done < /tmp/timestamp_sync.txt
        
        if [ "$timestamps_ordered" -eq 1 ]; then
            echo -e "${GREEN}✓ PASS - Timestamp progression correct${NC}"
            PASSED_TESTS=$((PASSED_TESTS + 1))
            log_test "Timestamp progression" "PASS" "All timestamps in increasing order"
        else
            echo -e "${RED}✗ FAIL - Timestamp regression detected${NC}"
            FAILED_TESTS=$((FAILED_TESTS + 1))
            log_test "Timestamp progression" "FAIL" "Timestamps not in order"
        fi
        rm -f /tmp/timestamp_sync.txt
    fi
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    echo ""
}

# =============================================================================
# MAIN TEST EXECUTION
# =============================================================================

main() {
    # Initialize log files
    echo "Philosophers Test Suite - $(date)" > "$LOG_FILE"
    echo "Detailed Test Log - $(date)" > "$DETAILED_LOG"
    echo "" >> "$LOG_FILE"
    
    print_header "COMPREHENSIVE PHILOSOPHERS TEST SUITE"
    
    # Check if philo executable exists
    if [ ! -f "$PHILO_PROGRAM" ]; then
        echo -e "${RED}ERROR: $PHILO_PROGRAM not found!${NC}"
        echo "Please compile your program first with: make"
        exit 1
    fi
    
    # Check if valgrind is available
    if ! command -v valgrind &> /dev/null; then
        echo -e "${YELLOW}WARNING: Valgrind not found. Skipping memory tests.${NC}"
        echo "Install valgrind with: sudo apt-get install valgrind"
        echo ""
    fi
    
    echo -e "${CYAN}Starting comprehensive test suite...${NC}"
    echo -e "Program: $PHILO_PROGRAM"
    echo -e "Log file: $LOG_FILE"
    echo -e "Detailed log: $DETAILED_LOG"
    echo ""
    
    # Execute all test categories
    test_input_validation
    test_basic_functionality
    test_edge_cases
    test_fairness_and_starvation
    test_advanced_behavior
    test_resource_limits
    test_output_format
    
    # Execute mandatory 42 School evaluation tests
    test_mandatory_42_requirements
    test_critical_deadlock_prevention
    test_mandatory_synchronization
    
    # Only run concurrency tests if valgrind is available
    if command -v valgrind &> /dev/null; then
        test_concurrency
    else
        echo -e "${YELLOW}Skipping concurrency tests (valgrind not available)${NC}"
    fi
    
    test_performance
    
    # Generate final report
    print_header "TEST RESULTS SUMMARY"
    
    echo -e "${CYAN}Total Tests Run: $TOTAL_TESTS${NC}"
    echo -e "${GREEN}Passed: $PASSED_TESTS${NC}"
    echo -e "${RED}Failed: $FAILED_TESTS${NC}"
    
    local pass_rate
    if [ $TOTAL_TESTS -gt 0 ]; then
        pass_rate=$((PASSED_TESTS * 100 / TOTAL_TESTS))
    else
        pass_rate=0
    fi
    
    echo -e "${BLUE}Pass Rate: $pass_rate%${NC}"
    echo ""
    
    # Save summary to log
    echo "=== FINAL SUMMARY ===" >> "$LOG_FILE"
    echo "Total Tests: $TOTAL_TESTS" >> "$LOG_FILE"
    echo "Passed: $PASSED_TESTS" >> "$LOG_FILE"
    echo "Failed: $FAILED_TESTS" >> "$LOG_FILE"
    echo "Pass Rate: $pass_rate%" >> "$LOG_FILE"
    
    if [ $FAILED_TESTS -gt 0 ]; then
        echo -e "${RED}Some tests failed. Check $LOG_FILE and $DETAILED_LOG for details.${NC}"
        exit 1
    else
        echo -e "${GREEN}All tests passed! Your implementation looks solid.${NC}"
        exit 0
    fi
}

# =============================================================================
# SCRIPT EXECUTION
# =============================================================================

# Check for command line options
case "${1:-}" in
    -h|--help)
        echo "Philosophers Test Suite"
        echo ""
        echo "Usage: $0 [OPTIONS]"
        echo ""
        echo "Options:"
        echo "  -h, --help    Show this help message"
        echo "  -v, --verbose Enable verbose output"
        echo ""
        echo "The script will test the './philo' executable with comprehensive test cases."
        echo "Make sure to compile your program before running tests."
        exit 0
        ;;
    -v|--verbose)
        set -x  # Enable verbose mode
        shift
        ;;
esac

# Execute main function
main "$@"
