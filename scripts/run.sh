#!/bin/bash
# ==========================================================
# run.sh — execute the compiled C++ program with size limit
# ==========================================================

# --- COLOR CONFIGURATION ---
RED='\033[31m'
GREEN='\033[32m'
YELLOW='\033[33m'
RESET='\033[0m'

# --- CHECK PARAMETERS ---
if [ -z "$1" ]; then
    echo -e "${RED}[ERROR]${RESET} No executable name provided (e.g., ./run.sh main)."
    exit 1
fi

# --- SMART PATH SETUP ---
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$SCRIPT_DIR/.." || exit 1

# Extract executable name
EXE_NAME=$(basename -- "$1")
EXE_NAME="${EXE_NAME%.*}"

EXE_PATH="./executables/$EXE_NAME"
INPUT_NAME="input.in"
OUTPUT_NAME="output.out"

# --- LIMITS ---
MAX_BYTES=10485760 # 10MB limit
LIMIT_EXCEEDED=0

# --- VERIFY EXECUTABLE ---
if [ ! -f "$EXE_PATH" ]; then
    echo -e "${RED}[ERROR]${RESET} Executable not found at: $EXE_PATH"
    echo -e "${YELLOW}[DEBUG]${RESET} Looking in: $(pwd)/executables"
    exit 1
fi

chmod +x "$EXE_PATH"
rm -f "$OUTPUT_NAME"

# Ensure input.in exists
if [ ! -f "$INPUT_NAME" ]; then
    touch "$INPUT_NAME"
fi

# --- EXECUTION ---
echo -e "${YELLOW}[INFO]${RESET} Running $EXE_NAME..."

"$EXE_PATH" < "$INPUT_NAME" > "$OUTPUT_NAME" 2>&1 &
PID=$!

# --- MONITOR LOOP (ONLY SIZE) ---
while kill -0 $PID 2>/dev/null; do
    if [ -f "$OUTPUT_NAME" ]; then
        SIZE=$(stat -c%s "$OUTPUT_NAME" 2>/dev/null || echo 0)
        if [ "$SIZE" -gt "$MAX_BYTES" ]; then
            LIMIT_EXCEEDED=1
            echo -e "${RED}[SIZE LIMIT]${RESET} Output exceeded 10MB. Killing..."
            kill -9 $PID 2>/dev/null
            break
        fi
    fi
    sleep 0.2
done

wait $PID 2>/dev/null

# --- FINAL TRUNCATION ---
if [ -f "$OUTPUT_NAME" ]; then
    FINAL_SIZE=$(stat -c%s "$OUTPUT_NAME" 2>/dev/null || echo 0)
    if [ "$FINAL_SIZE" -gt "$MAX_BYTES" ]; then
        truncate -s "$MAX_BYTES" "$OUTPUT_NAME"
        LIMIT_EXCEEDED=1
    fi
fi

# --- DISPLAY LOGIC ---
echo ""
if [ "$LIMIT_EXCEEDED" -eq 1 ]; then
    echo -e "${RED}[WARNING]${RESET} Output file was truncated (10MB limit)."
    echo -e "${RED}[INFO]${RESET} Console display skipped to prevent lag."
else
    echo -e "${YELLOW}--- Program Output ---${RESET}"
    echo ""
    cat "$OUTPUT_NAME" 2>/dev/null
    echo -e "\n"
    echo -e "${GREEN}[SUCCESS]${RESET} Program finished successfully."
fi

echo -e "${GREEN}[INFO]${RESET} Output saved to: \"$(pwd)/$OUTPUT_NAME\""

exit 0