#!/bin/bash
# ==========================================================
# build.sh — build the currently open C++ file with colors
# ==========================================================

# --- CONFIGURE G++ PATH ---
GPP="g++"

# --- ANSI COLOR CODES ---
RED='\033[31m'
GREEN='\033[32m'
YELLOW='\033[33m'
CYAN='\033[36m'
RESET='\033[0m'

# --- EXPECT FILE PATH FROM ARGUMENT ---
if [ -z "$1" ]; then
    echo -e "${RED}[ERROR]${RESET} No file path provided."
    exit 1
fi

SRC="$1"

# --- EXTRACT FILE INFO ---
FILENAME=$(basename -- "$SRC")       # e.g., main.cpp
FILENAME_NOEXT="${FILENAME%.*}"      # e.g., main
FILEDIR=$(dirname -- "$SRC")         # Path to the file's directory

# --- SETUP EXECUTABLES DIRECTORY ---
OUTDIR="$FILEDIR/executables"
mkdir -p "$OUTDIR"

OUT_EXE="$OUTDIR/$FILENAME_NOEXT"

# --- KILL PREVIOUS INSTANCE ---
pkill -x "$FILENAME_NOEXT" >/dev/null 2>&1

# --- CALCULATE SOURCE FILE SIZE ---
BYTES=$(stat -c%s "$SRC")
KBYTES=$(awk "BEGIN {printf \"%.2f\", $BYTES/1024}")

# --- BUILD COMMAND ---
echo -e "${CYAN}[INFO]${RESET} Building \"$SRC\""
echo -e "${YELLOW}[SIZE]${RESET} Source file size: $KBYTES KB"
echo "..."

"$GPP" \
  -fdiagnostics-color=always \
  -g \
  -DActivateDebug \
  -DActivateTimings \
  -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wfloat-equal -Wuninitialized \
  "$SRC" -o "$OUT_EXE"

# --- CHECK RESULT ---
if [ $? -ne 0 ]; then
    echo -e "${RED}[ERROR]${RESET} Build failed!"
    exit 1
else
    echo -e "${GREEN}[SUCCESS]${RESET} Build succeeded: \"$OUT_EXE\""
fi