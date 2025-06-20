#!/bin/bash

# # Generate input
./generate > input.in

# Run 'main' and 'slowMain' with input.in, output to respective files
./main < input.in > output.out
./slowMain < input.in > slowOutput.out

# # Compare output.txt and slowOutput.out
if ! cmp -s output.out slowOutput.out; then
    echo "Files are different"
    exit 1
else
    echo "Files are the same"
fi

# # Run './z_diff_test_linux.sh' if the above comparison is successful
./z_diff_test_linux.sh
