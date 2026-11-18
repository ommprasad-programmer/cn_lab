/*
PR3_6_SelectiveRepeatAQR.c:
Program to simulate the Selective-Repeat ARQ protocol where the numbers of frames and frame
data is given by the user.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h> // Required for sleep()

#define WINDOW_SIZE 4
#define MAX_FRAMES 10

// Structure to represent a frame
typedef struct
{
    int seq_num;
    int data;
    bool acknowledged;
} Frame;

// Function to simulate packet loss (randomly)
bool simulate_packet_loss()
{
    // Simulate a 20% chance of packet loss
    return (rand() % 100) < 20;
}

// Function to simulate acknowledgment reception (randomly)
bool simulate_ack_loss()
{
    // Simulate a 10% chance of ack loss
    return (rand() % 100) < 10;
}

// Function to send frames
void send_frames(Frame buffer[], int base, int next_seq_num, int num_frames)
{
    int i;
    printf("\nSending frames:\n");
    for (i = base; i < base + WINDOW_SIZE && i < num_frames; i++)
    {
        if (!buffer[i].acknowledged)
        {
            printf("  - Frame %d (Seq Num: %d, Data: %d)\n", i, buffer[i].seq_num, buffer[i].data);
            if (simulate_packet_loss())
            {
                printf("    * Frame %d lost in transit!\n", i);
            }
            else
            {
                // Simulate receiving acknowledgment
                sleep(1); // Simulate propagation delay
                if (!simulate_ack_loss())
                {
                    printf("    - Acknowledgment for Frame %d received.\n", i);
                    buffer[i].acknowledged = true;
                }
                else
                {
                    printf("    * Acknowledgment for Frame %d lost.\n", i);
                }
            }
        }
    }
}


// Function to simulate the receiver
void receiver(Frame buffer[], int num_frames)
{
    int i;
    printf("\nReceiver:\n");
    for (i = 0; i < num_frames; i++)
    {
        if (!buffer[i].acknowledged)
        {
            if (simulate_packet_loss())
            {
                printf("  - Frame %d lost in transit.\n", i);
            }
            else
            {
                sleep(1); // Simulate processing delay
                printf("  - Received Frame %d (Seq Num: %d, Data: %d)\n", i, buffer[i].seq_num, buffer[i].data);
                if (!simulate_ack_loss())
                {
                    printf("    - Acknowledgment for Frame %d sent.\n", i);
                    buffer[i].acknowledged = true;
                }
                else
                {
                    printf("    * Acknowledgment for Frame %d lost.\n", i);
                }
            }
        }
    }
}


int main()
{
    Frame buffer[MAX_FRAMES];
    int num_frames, i;
    int base = 0;
    int next_seq_num = 0;

    srand(time(NULL)); // Seed the random number generator

    printf("\nEnter the number of frames to transmit (<= %d): ", MAX_FRAMES);
    scanf("%d", &num_frames);

    if (num_frames <= 0 || num_frames > MAX_FRAMES)
    {
        printf("Invalid number of frames.\n");
        return 1;
    }

    // Input frame data from the user
    for (i = 0; i < num_frames; i++)
    {
        buffer[i].seq_num = next_seq_num++;
        printf("Enter data for frame %d: ", i);
        scanf("%d", &buffer[i].data);
        buffer[i].acknowledged = false;
    }

    // Simulate Selective Repeat ARQ
    while (base < num_frames)
    {
        send_frames(buffer, base, next_seq_num, num_frames);

        // Simulate the receiver
        receiver(buffer, num_frames);

        // Slide the window
        while (base < num_frames && buffer[base].acknowledged)
        {
            base++;
        }
    }

    printf("\nAll frames successfully transmitted and acknowledged.\n");

    printf("\n");
    return 0;
}
