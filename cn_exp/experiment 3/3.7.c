/*
PR3_7_CSMACD.c:
Program to simulate the CSMA/CD (Carrier Sense Multiple Access with Collision Detection) protocol.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h> // For sleep/usleep simulation functions

#define MAX_ATTEMPTS 5

int main()
{
    int attempts = 0;
    int backoff_time;

    // Seed the random number generator
    srand(time(NULL));

    printf("\n--- CSMA/CD Protocol Simulation ---\n");
    printf("Node is preparing to transmit data over the shared channel...\n\n");

    while (attempts < MAX_ATTEMPTS)
    {
        attempts++;
        printf("Attempt %d:\n", attempts);
        printf("-> Sensing carrier... Channel appears IDLE. Starting transmission...\n");

        // Simulate simultaneous transmission from another node (0 = collision, 1 = clean line)
        int collision = rand() % 2;

        if (collision == 1)
        {
            // Collision detected
            printf("!!! CRITICAL: Collision detected during transmission !!!\n");
            printf("-> Sending Jamming Signal to alert all network stations...\n");

            if (attempts == MAX_ATTEMPTS)
            {
                printf("\nAbort: Maximum transmission attempts (%d) exceeded. Line is too congested.\n\n", MAX_ATTEMPTS);
                return 1;
            }

            // Binary Exponential Backoff Algorithm simulation
            // Backoff range increases exponentially with each failed attempt: 2^attempts
            int max_range = 1 << attempts;
            backoff_time = rand() % max_range;

            printf("-> Backoff Algorithm: Waiting for a random interval of %d time slots...\n\n", backoff_time);

            // Simulate the wait time (using standard loop or small sleep)
            for (volatile int w = 0; w < backoff_time * 1000000; w++)
                ;
        }
        else
        {
            // Successful transmission
            printf("=> SUCCESS: Data packet transmitted completely without any collisions!\n");
            printf("=> Channel frame transfer sequence finished.\n\n");
            return 0;
        }
    }

    return 0;
}
