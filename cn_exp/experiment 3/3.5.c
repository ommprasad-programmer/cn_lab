/*
PR3_5_GoBackN.c:
Program to simulate the Go-Back-N Automatic Repeat Request (ARQ) protocol.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int total_frames, window_size;
    int sent = 0, ack = 0;

    // Seed for random frame loss simulation
    srand(time(NULL));

    printf("\n--- Go-Back-N ARQ Simulation ---\n");
    printf("Enter the total number of frames to send: ");
    scanf("%d", &total_frames);
    printf("Enter the window size: ");
    scanf("%d", &window_size);

    printf("\n--- Transmission Started ---\n");

    while (ack < total_frames)
    {
        // Transmit frames within the active window limits
        for (int i = sent; i < ack + window_size && i < total_frames; i++)
        {
            printf("Sender: Sending Frame %d\n", i);
            sent++;
        }

        // Simulate network behavior for the oldest unacknowledged frame
        // Generates a random value: 0 for loss/timeout, 1 for successful receipt
        int success = rand() % 2;

        if (success == 0)
        {
            printf("\n!!! Timeout: No ACK received for Frame %d !!!\n", ack);
            printf("Go-Back-N Action: Retransmitting window starting from Frame %d\n\n", ack);
            // Roll back sender pointer to retransmit everything after the lost frame
            sent = ack;
        }
        else
        {
            printf("Receiver: Received Frame %d successfully\n", ack);
            printf("Receiver: Sent ACK %d\n\n", ack + 1);
            ack++; // Slide the window forward
        }
    }

    printf("--- All %d frames successfully transmitted and acknowledged! ---\n\n", total_frames);
    return 0;
}
