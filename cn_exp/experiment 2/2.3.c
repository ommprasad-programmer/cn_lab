/*
PR2_3_2B1QEncoding.c:
Program to implement the 2B1Q (Two-Binary One-Quaternary) Multilevel line coding technique.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to perform 2B1Q encoding
void encode2B1Q(const char *binary_input, int *quaternary_output, int *output_len)
{
    int input_len = strlen(binary_input);
    *output_len = 0;
    char previous_level = '+'; // Initially previous level is assumed to be +ve
    int i, j;

    // Ensure input characters are binary
    for (i = 0; i < input_len; i++)
    {
        if(binary_input[i]!='0' && binary_input[i]!='1')
        {
            fprintf(stderr, "\nError! Invalid character in binary input string (must be '0' or '1').\n\n");
            *output_len = 0; // Indicate an error
            return;
        }
    }

    // Ensure input length is even for di-bit processing
    if (input_len % 2 != 0)
    {
        fprintf(stderr, "\nError! Binary input string length must be even for 2B1Q encoding.\n\n");
        return;
    }

    // Allocate memory for quaternary output (half the size of binary input)
    *output_len = input_len / 2;
    // Note: quaternary_output is expected to be allocated by the caller or passed as a pointer to a pre-allocated array.
    // For simplicity in this example, we'll assume it's pre-allocated or dynamically allocated within main.


    for (i = 0, j = 0; i < input_len; i += 2, j++)
    {
        // Extract dibit (two binary bits)
        char bit1 = binary_input[i];
        char bit2 = binary_input[i+1];

        // Apply 2B1Q mapping
        if (previous_level == '+' && bit1 == '0' && bit2 == '0')
        {
            quaternary_output[j] = +1;
            previous_level = '+'; // Update previous level based on current level
        }
        else if (previous_level == '+' && bit1 == '0' && bit2 == '1')
        {
            quaternary_output[j] = +3;
            previous_level = '+';
        }
        else if (previous_level == '+' && bit1 == '1' && bit2 == '0')
        {
            quaternary_output[j] = -1;
            previous_level = '-';
        }
        else if (previous_level == '+' && bit1 == '1' && bit2 == '1')
        {
            quaternary_output[j] = -3;
            previous_level = '-';
        }
        else if (previous_level == '-' && bit1 == '0' && bit2 == '0')
        {
            quaternary_output[j] = -1;
            previous_level = '-'; // Update previous level based on current level
        }
        else if (previous_level == '-' && bit1 == '0' && bit2 == '1')
        {
            quaternary_output[j] = -3;
            previous_level = '-';
        }
        else if (previous_level == '-' && bit1 == '1' && bit2 == '0')
        {
            quaternary_output[j] = +1;
            previous_level = '+';
        }
        else if (previous_level == '-' && bit1 == '1' && bit2 == '1')
        {
            quaternary_output[j] = +3;
            previous_level = '+';
        }
    }
}

int main()
{
    char binary_data[100]; // Max 99 characters + null terminator
    int quaternary_encoded[50]; // Max 50 quaternary symbols
    int output_length;

    printf("\nEnter a binary string (of even length): ");
    scanf("%s", binary_data);

    encode2B1Q(binary_data, quaternary_encoded, &output_length);

    if (output_length > 0)
    {
        printf("\n2B1Q Encoded Output: ");
        for (int i = 0; i < output_length; i++)
        {
            printf("| %+d ", quaternary_encoded[i]);
        }
        printf("|\n\n");
    }
    return 0;
}
