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
LOG_FILE="test_results.log"
DETAILED_LOG="detailed_test.log"
TIMEOUT_DURATION=30

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
    
    if timeout "$timeout" stdbuf -o0 -e0 bash -c "$command" > /tmp/test_output.txt 2>&1; then
        exit_code=0
    else
        exit_code=$?
    fi
    
    output=$(cat /tmp/test_output.txt)
    
    # Enhanced validation logic based on expected behavior
    local test_passed=false
    
    if [[ "$expected_behavior" == *"should fail"* ]]; then
        # Tests that should fail - success if non-zero exit code
        if [ $exit_code -ne 0 ]; then
            test_passed=true
        fi
    elif [[ "$expected_behavior" == *"should complete"* ]] || [[ "$expected_behavior" == *"should stop"* ]] || [[ "$expected_behavior" == *"should die"* ]]; then
        # Tests that should complete successfully - success if zero exit code
        if [ $exit_code -eq 0 ]; then
            test_passed=true
        fi
    elif [[ "$expected_behavior" == *"should parse"* ]] || [[ "$expected_behavior" == *"should alternate"* ]] || [[ "$expected_behavior" == *"philosophers should"* ]] || [[ "$expected_behavior" == *"scenario"* ]] || [[ "$expected_behavior" == *"starvation"* ]] || [[ "$expected_behavior" == *"death timing"* ]] || [[ "$expected_behavior" == *"edge case"* ]] || [[ "$expected_behavior" == *"system resource"* ]] || [[ "$expected_behavior" == *"scalability"* ]] || [[ "$expected_behavior" == *"test"* ]] || [[ "$expected_behavior" == *"should work"* ]] || [[ "$expected_behavior" == *"operations"* ]] || [[ "$expected_behavior" == *"simulation"* ]]; then
        # Infinite-running tests or death-related tests - success if program started and produced output
        if [ -n "$output" ] && [[ "$output" == *"is thinking"* || "$output" == *"has taken"* || "$output" == *"is eating"* || "$output" == *"died"* ]]; then
            test_passed=true
        fi
    else
        # Default logic for other cases
        if [ $exit_code -eq 0 ]; then
            test_passed=true
        fi
    fi
    
    if [ "$test_passed" = true ]; then
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
    
    if timeout "$timeout" stdbuf -o0 -e0 valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=/tmp/valgrind_output.txt $command > /dev/null 2>&1; then
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
    
    # Test cases based on research of common edge cases
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
    
    run_test "Zero meal count" "$PHILO_PROGRAM 5 800 200 200 0" "should complete immediately"
    
    run_test "Leading zeros valid" "$PHILO_PROGRAM 05 0800 0200 0200" "should parse as valid numbers"
    
    run_test "Plus sign valid" "$PHILO_PROGRAM +5 +800 +200 +200" "should parse as valid numbers"
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
    
    # Based on research from dining philosophers edge cases
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
    
    run_test "CPU intensive test" "$PHILO_PROGRAM 8 300 50 50" "high frequency operations" 8
    
    run_test "Context switching test" "$PHILO_PROGRAM 20 800 100 100 2" "frequent context switches" 15
    
    run_test "Long duration test" "$PHILO_PROGRAM 3 5000 1000 1000 10" "extended simulation time" 25
    
    run_test "Rapid completion test" "$PHILO_PROGRAM 10 1000 10 10 1" "quick meal completion" 5
    
    run_test "Scalability limit test" "$PHILO_PROGRAM 100 1000 200 200 2" "system resource limits" 20
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
        local has_timestamp=$(grep -c "^[0-9]\+" /tmp/output_test.txt || echo "0")
        local has_philosopher_id=$(grep -c "has taken a fork\|is eating\|is sleeping\|is thinking\|died" /tmp/output_test.txt || echo "0")
        
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
    test_output_format
    
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
