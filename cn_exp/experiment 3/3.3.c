/*
PR3_3_CharacterStuffing.c:
Program to implement the data link layer framing method: Character stuffing and destuffing.
*/

#include <stdio.h>
#include <string.h>

#define MAX 100
#define FLAG '#'
#define ESC '\\'

// Function to perform character stuffing
void stuffData(const char *input, char *stuffed)
{
    int j = 0;
    stuffed[j++] = FLAG; // Starting flag
    for (int i = 0; i < strlen(input); i++)
    {
        if (input[i] == FLAG || input[i] == ESC)
        {
            stuffed[j++] = ESC; // Add escape before reserved character
        }
        stuffed[j++] = input[i];
    }
    stuffed[j++] = FLAG; // Ending flag
    stuffed[j] = '\0';
}

// Function to perform character destuffing
void destuffData(const char *stuffed, char *destuffed)
{
    int j = 0;
    for (int i = 1; i < strlen(stuffed) - 1; i++)
    { // skip boundary flags
        if (stuffed[i] == ESC)
        {
            i++; // Skip escape and take next character as-is
        }
        destuffed[j++] = stuffed[i];
    }
    destuffed[j] = '\0';
}

int main()
{
    char input[MAX], stuffed[MAX * 2], destuffed[MAX];

    printf("\nCharacter used for starting and ending flag: %c", FLAG);
    printf("\nCharacter used for escape character: %c", ESC);

    printf("\n\nEnter the characters to be transmitted (without spaces): ");
    scanf("%s", input);

    stuffData(input, stuffed);
    printf("\nStuffed Frame: %s\n", stuffed);

    destuffData(stuffed, destuffed);
    printf("Destuffed Data: %s\n", destuffed);

    printf("\n");
    return 0;
}
