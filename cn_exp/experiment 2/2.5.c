/*
PR2_5_SynchronousTDM.c:
Program to implement Synchronous Time Division Multiplexing (TDM) technique.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int numChannels, frameSize;
    printf("\nSynchronous TDM Simulation");
    printf("\n==========================\n\n");
    printf("Enter the number of channels: ");
    scanf("%d", &numChannels);

    printf("Enter the frame size (max. number of characters per channel): ");
    scanf("%d", &frameSize);

    // Dynamically allocate memory for input data
    char **data = (char **)malloc(numChannels * sizeof(char *));
    for (int i = 0; i < numChannels; i++) {
        data[i] = (char *)malloc((frameSize + 1) * sizeof(char));
    }

    // Input data for each channel
    printf("\n--- Input Phase ---\n");
    for (int i = 0; i < numChannels; i++) {
        printf("Enter data for channel %d (max %d characters without any space, or '-' for empty): ", i + 1, frameSize);
        scanf("%s", data[i]);
        data[i][frameSize] = '\0'; // Ensure null-termination
    }

    // Simulate synchronous transmission
    printf("\n--- Transmitting Frames (Round-Robin Schedule) ---\n");
    printf("Time Slot Order: ");
    for (int i = 0; i < numChannels; i++) {
        printf("CH%d ", i + 1);
    }
    printf("\n\n");

    for (int f = 0; f < frameSize; f++) {
        printf("Frame %d: ", f + 1);
        for (int c = 0; c < numChannels; c++) {
            if (f < strlen(data[c])) {
                printf("%c  ", data[c][f]);
            } else {
                printf("-  ");
            }
        }
        printf("\n");
    }

    // Clean up
    for (int i = 0; i < numChannels; i++) {
        free(data[i]);
    }
    free(data);

    printf("\n");
    return 0;
}
