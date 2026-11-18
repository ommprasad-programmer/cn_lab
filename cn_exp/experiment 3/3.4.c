/*
PR3_4_BitStuffing.c:
Program to implement the data link layer framing method: Bit stuffing and destuffing.
*/

#include <stdio.h>
#include <string.h>

#define MAX 200

// Function to perform bit stuffing
void bitStuff(const char* input, char* stuffed)
{
    int count = 0, j = 0;
    for (int i = 0; input[i] != '\0'; i++)
    {
        if (input[i] == '1')
        {
            count++;
        }
        else
        {
            count = 0;
        }

        stuffed[j++] = input[i];

        if (count == 5)
        {
            stuffed[j++] = '0'; // Insert stuffed 0
            count = 0;
        }
    }
    stuffed[j] = '\0';
}

// Function to perform bit destuffing
void bitDestuff(const char* stuffed, char* destuffed)
{
    int count = 0, j = 0;
    for (int i = 0; stuffed[i] != '\0'; i++)
    {
        if (stuffed[i] == '1')
        {

            count++;
        }
        else
        {
            count = 0;
        }

        destuffed[j++] = stuffed[i];

        if (count == 5)
        {
            i++; // Skip stuffed 0
            count = 0;
        }
    }
    destuffed[j] = '\0';
}

int main()
{
    char input[MAX], stuffed[MAX], destuffed[MAX];

    printf("\nEnter binary data (e.g., 0111111010): ");
    scanf("%s", input);

    bitStuff(input, stuffed);
    printf("\n\nStuffed Data: %s\n", stuffed);

    bitDestuff(stuffed, destuffed);
    printf("Destuffed Data: %s\n", destuffed);

    printf("\n");
    return 0;
}
