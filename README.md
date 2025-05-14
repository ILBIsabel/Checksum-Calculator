# Checksum-Calculator

A C program that calculates the checksum of a given text file using 8-bit, 16-bit, or 32-bit checksums. The program reads the input file, processes its content, and outputs the formatted text along with the computed checksum.

The purpose of this program is to demonstrate how data integrity can be verified using basic checksum algorithms. It reads an input file, breaks the content into equal-sized chunks (based on the selected checksum size), sums the values, and outputs the result in hexadecimal. It also ensures the input is properly padded to allow uniform block processing.

# Features
Supports three checksum sizes: 8-bit, 16-bit, and 32-bit

Formats input file into lines of exactly 80 characters

Automatically pads content with 'X' characters if needed

Includes line feed characters (\n) in the checksum computation

# Displays

Formatted input file content

Calculated checksum

Total number of characters processed (including padding)

Detects and reports invalid checksum sizes

# Input Format
The program accepts a plain text file containing standard ASCII characters. It can include letters, numbers, punctuation, whitespace, and line breaks. The newline character (\n, ASCII 0x0A) is treated as a valid input character and contributes to the checksum.

# Output Format
After processing, the output will show the content of the file printed in lines of 80 characters per row. If the last line contains fewer than 80 characters, it is still printed, and padding is applied if necessary based on the checksum size.

Finally, the program prints a summary line in this format:

<checksum_size> bit checksum is <checksum_value> for all <char_count> chars

# How to Compile and Run

To compile the program:

gcc -o pa02 pa02.c

To execute:

./pa02 <input_file> <checksum_size>

<checksum_size>: The selected checksum size (8, 16, or 32 bits).
<checksum_value>: The computed checksum value in hexadecimal.
<char_count>: The total number of characters processed, including padding.

# Running the Test Script
To run the provided test script and verify your implementation against expected output, use the following command:

bash pa02Xtest-1.sh pa02.c

This will compile and test your program using sample test cases.
