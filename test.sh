#!/bin/bash

# # Generate input
./generate > input.txt

# Run 'main' and 'second' with input.txt, output to respective files
./main < input.txt > output.txt
./second < input.txt > second_output.txt

# # Compare output.txt and second_output.txt
if ! cmp -s output.txt second_output.txt; then
    echo "Files are different"
    exit 1
else
    echo "Files are the same"
fi

# # Run './test' if the above comparison is successful
./test.sh
