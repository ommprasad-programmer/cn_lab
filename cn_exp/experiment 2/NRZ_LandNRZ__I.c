/*
PR2_1_NRZLAndNRZIEncoding.c:
Program to implement Polar NRZ-L (Non-Return to Zero Level) and Polar NRZ-I (Non-Return to Zero Invert) line coding techniques.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to check invalid characters in the binary input data
void invaidCharCheck(const char *binaryData)
{
    int i;
    for (i = 0; i < strlen(binaryData); i++)
    {
        if (binaryData[i] != '0' && binaryData[i] != '1')
        {
            printf("\nInvalid character in binary input data.\n\n");
            exit(0);
        }
    }
    printf("\n");
}

// Function to simulate NRZ-L encoding
void nrzLevel(const char *binaryData)
{
    int i;
    printf("NRZ-L Encoding: ");
    for (i = 0; i < strlen(binaryData); i++)
    {
        if (binaryData[i] == '0')
        {
            printf("| + "); // Represent '0' with a positive level
        }
        else // If binary data is '1'
        {
            printf("| - ");  // Represent '1' with a negative level
        }
    }
    printf("|\n");
}

// Function to simulate NRZ-I encoding
void nrzInvert(const char *binaryData)
{
    printf("\nNRZ-I Encoding: ");
    int currentLevel = 0; // 0 for positive, 1 for negative (arbitrary starting point)
    int i;

    for (i = 0; i < strlen(binaryData); i++)
    {
        if (binaryData[i] == '1')
        {
            currentLevel = 1 - currentLevel; // Invert level for '1'
        }
        // For '0', the level remains the same

        if (currentLevel == 1)
        {
            printf("| - ");
        }
        else
        {
            printf("| + ");
        }
    }
    printf("|\n\n");
}

int main(void)
{
    char binaryInput[100];

    printf("\n");
    printf("Enter binary data (e.g., 1011001): ");
    scanf("%s", binaryInput);

    invaidCharCheck(binaryInput);
    nrzLevel(binaryInput);
    nrzInvert(binaryInput);

    return 0;
}
