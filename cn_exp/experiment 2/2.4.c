/*
PR2_4_MLT3Encoding.c:
Program to implement the MLT-3 (Multiline Transition, Three Level) line coding technique.
*/

#include <stdio.h>
#include <string.h>

// Function to perform MLT-3 encoding
void mlt3Encode(const char *data_stream)
{
    int current_level = 0; // Current signal level is set to 0V (-V, 0V, and +V are represented as -1, 0, or +1 respectively)
    int last_nonzero_level = -1; // Last non-zero level is set to -V
    int i;

    printf("\nMLT-3 Encoded Signal: ");

    for (i = 0; i < strlen(data_stream); i++)
    {
        char next_bit = data_stream[i];

        if (next_bit == '0')
        {
            // If the next bit is 0, there is no transition
            current_level = current_level;

            // Print the values of current_level as 0V, -V, or +V.
            if (current_level == 0)
            {
                printf("| 0V ");
            }
            else if (current_level == -1)
            {
                printf("| -V ");
            }
            else // if current_level is +1)
            {
                printf("| +V ");
            }
        }
        else if (next_bit == '1')
        {
            // If the next bit is 1
            if (current_level == 0)
            {
                // If current level is 0, transition to the opposite of the last non-zero level
                current_level = -last_nonzero_level;
                last_nonzero_level = current_level; // Update last_nonzero_level

                // Print the values of current_level as 0V, -V, or +V.
                if (current_level == 0)
                {
                    printf("| 0V ");
                }
                else if (current_level == -1)
                {
                    printf("| -V ");
                }
                else // if current_level is +1)
                {
                    printf("| +V ");
                }
            }
            else
            {
                // If current level is not 0, transition to 0
                current_level = 0;
                printf("| 0V ");
            }
        }
        else
        {
            printf("Invalid input character.\n\n");
            return;
        }
    }
    printf("|\n\n");
}

int main()
{
    char data_stream[100];

    printf("\nEnter the binary data stream (e.g., 1011001): ");
    scanf("%s", data_stream);

    mlt3Encode(data_stream);

    return 0;
}
