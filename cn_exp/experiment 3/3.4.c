/*
PR3_4_BitStuffing.c:
Program to implement the data link layer framing method: Bit stuffing and destuffing.
*/

#include <stdio.h>
#include <string.h>

void bitStuff(const char *input, char *stuffed)
{
    int count = 0;
    int j = 0;

    // Starting flag sequence: 01111110
    strcpy(stuffed, "01111110");
    j = 8;

    for (int i = 0; i < strlen(input); i++)
    {
        stuffed[j++] = input[i];

        if (input[i] == '1')
        {
            count++;
        }
        else
        {
            count = 0;
        }

        // Stuff a '0' after 5 consecutive '1's
        if (count == 5)
        {
            stuffed[j++] = '0';
            count = 0;
        }
    }

    // Ending flag sequence: 01111110
    strcat(stuffed, "01111110");
}

void bitDestuff(const char *stuffed, char *destuffed)
{
    int count = 0;
    int j = 0;
    int len = strlen(stuffed);

    // Skip the starting flag (first 8 bits) and ending flag (last 8 bits)
    for (int i = 8; i < len - 8; i++)
    {
        destuffed[j++] = stuffed[i];

        if (stuffed[i] == '1')
        {
            count++;
        }
        else
        {
            count = 0;
        }

        // If 5 consecutive '1's are detected, skip the next bit (which is the stuffed '0')
        if (count == 5)
        {
            i++;
            count = 0;
        }
    }
    destuffed[j] = '\0';
}

int main()
{
    char input[100], stuffed[200], destuffed[100];

    printf("\nEnter the binary data stream to be transmitted: ");
    scanf("%s", input);

    bitStuff(input, stuffed);
    printf("\nStuffed Frame (with flags): %s\n", stuffed);

    bitDestuff(stuffed, destuffed);
    printf("Destuffed Data:             %s\n\n", destuffed);

    return 0;
}
