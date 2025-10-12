#!/bin/bash

# ==================================================
# This script runs generate, main, slowMain, and
# compares their outputs. Works with parent folder.
# ==================================================

# Save script directory (so we can use relative paths reliably)
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

# Paths to executables
GENERATE="$SCRIPT_DIR/generate"
MAIN="$SCRIPT_DIR/../main"
SLOW_MAIN="$SCRIPT_DIR/../slowMain"
Z_DIFF="$SCRIPT_DIR/z_diff_test_linux.sh"

# Output/input files
INPUT="$SCRIPT_DIR/input.in"
OUTPUT="$SCRIPT_DIR/output.out"
SLOW_OUTPUT="$SCRIPT_DIR/slowOutput.out"

# --- Generate input ---
"$GENERATE" > "$INPUT"

# --- Run main programs ---
"$MAIN" < "$INPUT" > "$OUTPUT"
"$SLOW_MAIN" < "$INPUT" > "$SLOW_OUTPUT"

# --- Compare outputs ---
if ! cmp -s "$OUTPUT" "$SLOW_OUTPUT"; then
    echo "[ERROR] Files are different"
    exit 1
else
    echo "[INFO] Files are the same"
fi

# --- Run z_diff_test_linux.sh ---
"$Z_DIFF"
