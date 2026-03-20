#!/bin/bash
# ==========================================================
# diff_test.sh — continuously run and compare two solutions
# ==========================================================

# Path to your executables relative to the project root
EXEDIR="./executables"

# Move to parent folder (the project root)
cd .. || exit 1

# --- RUN TOOLS ---
# We point to the executables folder. 
# Note: Ensure these have execute permissions (chmod +x)
"$EXEDIR/generator" > input.in
"$EXEDIR/professional" < input.in > output.out
"$EXEDIR/slowSolution" < input.in > slowSolutionOutput.out

# --- COMPARE ---
# -w ignores whitespace; -q could be used if you only want to know if they differ
diff -w output.out slowSolutionOutput.out

# Check exit code of 'diff'
if [ $? -ne 0 ]; then
    echo -e "\033[31m[ERROR]\033[0m Differences found! Check input.in for the test case."
    exit 1
fi

# --- LOOP ---
echo -e "\033[32m[PASS]\033[0m Outputs match. Restarting test..."

# Move back to the scripts folder to restart the cycle
cd scripts || exit 1

# 'exec' replaces the current shell process with a new one to prevent PID exhaustion
exec ./diff_test.sh