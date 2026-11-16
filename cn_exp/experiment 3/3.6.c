/*
PR3_6_SelectiveRepeat.c:
Program to simulate the Selective-Repeat Automatic Repeat Request (ARQ) protocol.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int total_frames, window_size;

    // Seed the random number generator for frame loss simulation
    srand(time(NULL));

    printf("\n--- Selective-Repeat ARQ Simulation ---\n");
    printf("Enter the total number of frames to send: ");
    scanf("%d", &total_frames);
    printf("Enter the window size: ");
    scanf("%d", &window_size);

    int *frame_status = (int *)calloc(total_frames, sizeof(int)); // 0 = unsent/lost, 1 = ACK received
    int base = 0;

    printf("\n--- Transmission Started ---\n");

    while (base < total_frames)
    {
        // Step 1: Send all unacknowledged frames currently within the window
        for (int i = base; i < base + window_size && i < total_frames; i++)
        {
            if (frame_status[i] == 0)
            {
                printf("Sender: Transmitting Frame %d\n", i);
            }
        }
        printf("\n");

        // Step 2: Check delivery status for each frame in the current window
        for (int i = base; i < base + window_size && i < total_frames; i++)
        {
            if (frame_status[i] == 0)
            {
                // Simulate frame delivery status (0 = lost/timeout, 1 = successful ACK)
                int success = rand() % 2;

                if (success == 1)
                {
                    printf("Receiver: Frame %d received properly -> Sent ACK %d\n", i, i + 1);
                    frame_status[i] = 1; // Mark as successfully acknowledged
                }
                else
                {
                    printf("!!! Timeout: NAK generated or ACK missing for Frame %d !!!\n", i);
                }
            }
        }

        // Step 3: Slide the window base forward past all consecutively acknowledged frames
        while (base < total_frames && frame_status[base] == 1)
        {
            base++;
        }

        printf("\n--- Sliding window base forward. Current Base Frame: %d ---\n\n", base);
    }

    printf("--- Success: All %d frames successfully transmitted and acknowledged! ---\n\n", total_frames);
    free(frame_status);
    return 0;
}
