/*
PR3_2_HammingCode.c:
Program to implement the Hamming Code "C (7,4)" error detection and correction technique.
*/

#include <stdio.h>

// Function to calculate and return parity bits: r0, r1, r2
void calculateParityBits(int a[4], int r[3])
{
    r[0] = (a[0] + a[1] + a[2]) % 2; // r0 = a0 + a1 + a2
    r[1] = (a[1] + a[2] + a[3]) % 2; // r1 = a1 + a2 + a3
    r[2] = (a[0] + a[1] + a[3]) % 2; // r2 = a0 + a1 + a3
}

// Function to form the 7-bit codeword
void createCodeword(int a[4], int r[3], int code[7])
{
    code[0] = r[0];
    code[1] = r[1];
    code[2] = r[2];
    code[3] = a[0];
    code[4] = a[1];
    code[5] = a[2];
    code[6] = a[3];
}

// Function to introduce an error at a given position (0-6)
void introduceError(int code[7], int position)
{
    if (position >= 0 && position < 7)
    {
        code[position] ^= 1; // Flip the bit
    }
}

// Function to detect and correct a single-bit error using syndrome bits
int detectAndCorrect(int code[7])
{
    int s[3];
    s[0] = (code[3] + code[4] + code[5] + code[0]) % 2; // s0
    s[1] = (code[4] + code[5] + code[6] + code[1]) % 2; // s1
    s[2] = (code[3] + code[4] + code[6] + code[2]) % 2; // s2

    int errorPosition = (s[2] << 2) | (s[1] << 1) | s[0]; // Binary to decimal

    if (errorPosition != 0)
    {
        printf("\nError detected at bit position: %d\n", errorPosition);
        code[errorPosition - 1] ^= 1; // Correct the error
    }
    else
    {
        printf("\nNo error detected.\n");
    }

    return errorPosition;
}

// Function to display a 7-bit code
void displayCode(int code[7])
{
    for (int i = 0; i < 7; i++)
    {
        printf("%d ", code[i]);
    }
    printf("\n");
}

int main()
{
    int data[4], parity[3], code[7];
    int errorBit;

    printf("\nEnter 4-bit dataword (a0 a1 a2 a3): ");
    for (int i = 0; i < 4; i++)
    {
        scanf("%d", &data[i]);
    }

    calculateParityBits(data, parity);
    createCodeword(data, parity, code);

    printf("\nEncoded 7-bit codeword (r0 r1 r2 a0 a1 a2 a3): ");
    displayCode(code);

    printf("\nEnter bit position to introduce error (1-7, 0 for no error): ");
    scanf("%d", &errorBit);
    if (errorBit != 0)
    {
        introduceError(code, errorBit - 1);
        printf("\nCodeword with error: ");
        displayCode(code);
    }

    printf("\n\n--- Receiver Side ---\n");
    int corrected = detectAndCorrect(code);
    printf("\nCorrected Codeword: ");
    displayCode(code);

    printf("\n");
    return 0;
}
