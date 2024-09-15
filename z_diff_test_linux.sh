#!/bin/bash

# # Generate input
./generate > input.in

# Run 'main' and 'second' with input.in, output to respective files
./main < input.in > output.out
./second < input.in > second_output.out

# # Compare output.txt and second_output.out
if ! cmp -s output.out second_output.out; then
    echo "Files are different"
    exit 1
else
    echo "Files are the same"
fi

# # Run './test.sh' if the above comparison is successful
./z_diff_test_linux.sh
