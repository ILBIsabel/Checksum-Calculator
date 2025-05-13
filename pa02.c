#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINE_LENGTH_MAXIMUM 80

//All of the function prototypes that will be used for the checksum calculations and the bitmask computations
void checkSumFileContent(const char *filename, int checkSumSize);
void checkSumCalculations(int checkSumSize, const char *inputString, unsigned long *checksum);
unsigned long bitMaskComputation(const char *inputString, int checkSumSize);

//Open the file, if not exit
void checkSumFileContent(const char *filename, int checkSumSize){
    FILE *fileInput = fopen(filename, "r");
    if(fileInput == 0){
        printf("Could not open the file.\n");
        return;
    }

//Initialize
int characterValue = 0;
int characterCnt = 0;
int size_of_word = checkSumSize / 8;
unsigned long checksum = 0;
char *inputChar = malloc(size_of_word + 1);

int i = 0;
int j = 0;

//Read the file and data one character by character
while((characterValue = fgetc(fileInput)) != EOF) {   //Not equal to the end of file
    inputChar[i] = (char)characterValue;
    i++;
    characterCnt++;

    //Print the character 
    putchar(characterValue);
    j++;

    //Add a newline after reaching the maximum of 80 characters per row
    if (j == LINE_LENGTH_MAXIMUM) {
        printf("\n");
        j = 0;
    }

    //Process and compute the checksum once enough characters are collected for a word
    if (i == size_of_word) {
        inputChar[i] = '\0';      //Null-terminate, this is officially marking the end of the string
        checkSumCalculations(checkSumSize, inputChar, &checksum);   
        i = 0;   
    }
}

//Work with the characters that are leftover, if they do not aligned with the size_of_word
if (i > 0) {
    //Add padding 'X' if needed 
    while (i < size_of_word) {
        inputChar[i++] = 'X';
        characterCnt++;
        putchar('X');  //Print that padding character 'X'
        j++;

        //Continue keeping up with the maximum line length of 80 characters per row 
        if (j == LINE_LENGTH_MAXIMUM) { 
                printf("\n");
                j = 0;
        }
    }
    
    //Null-terminate, this is officially marking the end of the string
    inputChar[i] = '\0';
    checkSumCalculations(checkSumSize, inputChar, &checksum);  
}

//If the last line doesn't reach and has less than 80 characters, add a newline 
if (j > 0 && j != LINE_LENGTH_MAXIMUM) {
    printf("\n");
}

//Print the checksum line
printf("%2d bit checksum is %8lx for all %4d chars\n", checkSumSize, checksum, characterCnt);

free(inputChar);

//Close the file
fclose(fileInput);
}

//Function that computes and updates the checksum by adding the value to the checksum, making sure it is within the bit size
void checkSumCalculations(int checkSumSize, const char *inputString, unsigned long *checksum) {
    unsigned long numericValue = bitMaskComputation(inputString, checkSumSize / 8);
    *checksum = (*checksum + numericValue) % (1UL << checkSumSize);
}

//Function that deals with the bitwise shifts and ASCII values as a result of turning characters into integers
unsigned long bitMaskComputation(const char *inputString, int size_of_word) {
    unsigned long accumulatedCharacters = 0;

    //Iterates each character and shifts the bits/bytes to make the integer
    for (int i = 0; i < size_of_word; i++) {
        accumulatedCharacters = (accumulatedCharacters<< 8) | (unsigned char)inputString[i];
    }

    return accumulatedCharacters;
}


//Main function with two command-line arguments for the input file and the checksum size (8, 16, or 32 bits)
int main(int argc, char *argv[]) {

    //Ensures there are a correct number of arguments being passed, two command-line arguments
    if (argc != 3) {
        printf("Invalid number of command-line arguments being passed.\n");
        return 1;
    }

    //The first argument that will get the input file name
    const char *inputFileName = argv[1];

    //The second argument that will get the checksum bit size 
    int checkSumBitSize = atoi(argv[2]);

    //Validate the checksum size, if it is not 8, 16, or 32 bits then print out this message indicating the value is wrong
    if (checkSumBitSize != 8 && checkSumBitSize != 16 && checkSumBitSize != 32) {
        fprintf(stderr, "Valid checksum sizes are 8, 16, or 32\n");
        return 1;
    }

    //Add an empty line before printing the actual characters (prevents that 0a1 error)
    printf("\n");

    //Compute the checksum for the given input file and its size
    checkSumFileContent(inputFileName, checkSumBitSize);

    return 0;
}