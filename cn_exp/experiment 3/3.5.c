/*
PR3_5_GoBackNARQ.c:
Program to simulate the Go-Back-N Automatic Repeat Request (REQ) Protocol
where the sliding window size and the number of frames are given by the user
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int windowSize, numFrames, base = 0, nextSeqNum = 0;
    int receivedFrames = 0; // Keep track of successfully received frames
    int corruptedFrames = 0; // Keep track of corrupted frames

    printf("\nEnter the window size: ");
    scanf("%d", &windowSize);

    printf("Enter the number of frames: ");
    scanf("%d", &numFrames);
    printf("\n");

    srand(time(NULL)); // Seed the random number generator

    while (base < numFrames)
    {
        // Sender side: Send frames within the window
        for (int i = 0; i < windowSize && nextSeqNum < numFrames; i++)
        {
            printf("Sending frame: %d\n", nextSeqNum);
            nextSeqNum++;
        }

        // Simulate frame reception (with potential errors)
        for (int i = base; i < nextSeqNum; i++)
        {
            int random_number = rand() % 10; // Generate a random number (0-9)

            // Simulate a corrupted frame (10% chance of corruption)
            if (random_number == 0)
            {
                printf("Frame %d corrupted!\n", i);
                corruptedFrames++;
            }
            else
            {
                printf("Frame %d received successfully\n", i);
                receivedFrames++;

                // Simulate cumulative acknowledgement
                if (receivedFrames == base + 1)
                {
                  base++; // Move the window forward
                  receivedFrames = 0; // Reset counter
                }
            }
        }
        if (corruptedFrames > 0)
        {
            printf("Go-Back-N: Retransmitting from frame %d\n", base);
            nextSeqNum = base; // Reset the next sequence number to base
            corruptedFrames = 0;
        }
    }

    printf("\nAll frames sent and acknowledged.\n\n");
    return 0;
}
