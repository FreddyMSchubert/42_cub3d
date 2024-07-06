#!/bin/bash

# Check if a file name was provided
if [ "$#" -ne 1 ]; then
  echo "Usage: $0 filename"
  exit 1
fi

# Initialize variables
input_file="$1"
start_processing=false

# Initialize counts for each special character
declare -i count_H=0
declare -i count_V=0
declare -i count_K=0
declare -i count_w=0
declare -i count_f=0
declare -i count_e=0
declare -i count_a=0
declare -i count_q=0
declare -i count_d=0
declare -i count_r=0
declare -i count_s=0
declare -i count_u=0
declare -i count_i=0
declare -i count_o=0
declare -i count_p=0
declare -i count_h=0
declare -i count_B=0

# Read the file line by line
while IFS= read -r line; do
  # Start processing lines after the line starting with '>'
  if [[ "$line" == ">"* ]]; then
    start_processing=true
    continue
  fi

  # Skip lines until the grid starts
  if [ "$start_processing" = true ]; then
    # Iterate through each character in the line
    for (( i=0; i<${#line}; i++ )); do
      char="${line:$i:1}"
      # Count characters that are not space, 0, 1, G, N, S, E, W
      case "$char" in
        H) count_H=$((count_H + 1)) ;;
        V) count_V=$((count_V + 1)) ;;
        K) count_K=$((count_K + 1)) ;;
        w) count_w=$((count_w + 1)) ;;
        f) count_f=$((count_f + 1)) ;;
        e) count_e=$((count_e + 1)) ;;
        a) count_a=$((count_a + 1)) ;;
        q) count_q=$((count_q + 1)) ;;
        d) count_d=$((count_d + 1)) ;;
        r) count_r=$((count_r + 1)) ;;
        s) count_s=$((count_s + 1)) ;;
        u) count_u=$((count_u + 1)) ;;
        i) count_i=$((count_i + 1)) ;;
        o) count_o=$((count_o + 1)) ;;
        p) count_p=$((count_p + 1)) ;;
        h) count_h=$((count_h + 1)) ;;
        B) count_B=$((count_B + 1)) ;;
      esac
    done
  fi
done < "$input_file"

# Display the counts of special characters
echo "Counts of special characters:"
echo "H: $count_H"
echo "V: $count_V"
echo "K: $count_K"
echo "w: $count_w"
echo "f: $count_f"
echo "e: $count_e"
echo "a: $count_a"
echo "q: $count_q"
echo "d: $count_d"
echo "r: $count_r"
echo "s: $count_s"
echo "u: $count_u"
echo "i: $count_i"
echo "o: $count_o"
echo "p: $count_p"
echo "h: $count_h"
echo "B: $count_B"

# before
# ORBS
#	fire 1
#	water 1
#	air 1
# BLIGHTS
#	earth 1

# ORBS
#	fire 1
#	water 1
#	air 1
# BLIGHTS
#	earth 1
