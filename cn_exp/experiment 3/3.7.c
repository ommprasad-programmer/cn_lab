/*
PR3_7_CSMACD.c:
Program to simulate the CSMA/CD protocol where the numbers of number of stations and data
to be sent by each station is given by the user.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define MAX_STATIONS 5
#define MAX_ATTEMPTS 10

// Simulates whether the medium is busy or free
int isMediumIdle()
{
    return rand() % 2; // 0 = busy, 1 = idle
}

// Simulates whether a collision occurs during transmission
int detectCollision()
{
    return rand() % 4 == 0; // 25% chance of collision
}

// Exponential Backoff delay (in seconds)
void backoff(int attempt)
{
    int k = (attempt < 10) ? attempt : 10;
    int r = rand() % (1 << k); // 2^k possibilities
    printf("    Waiting for %d units before retrying...\n", r);
    sleep(r % 3); // simulate backoff wait
}

void transmitFrame(int stationId, const char* frame)
{
    int attempts = 0;

    printf("\nStation %d attempting to transmit: \"%s\"\n", stationId, frame);

    while (attempts < MAX_ATTEMPTS)
    {
        if (isMediumIdle())
        {
            printf("  Medium is idle. Transmitting...\n");
            sleep(1); // Simulate transmission time

            if (detectCollision())
            {
                printf("  ** Collision detected! **\n");
                attempts++;
                backoff(attempts);
            }
            else
            {
                printf("  Frame \"%s\" transmitted successfully by Station %d.\n", frame, stationId);
                return;
            }
        }
        else
        {
            printf("  Medium is busy. Sensing again...\n");
            sleep(1);
        }
    }

    printf("  Transmission failed after %d attempts. Giving up.\n", MAX_ATTEMPTS);
}

int main() {
    srand(time(NULL));
    int numStations;
    char frames[MAX_STATIONS][100];

    printf("\nEnter number of stations (max %d): ", MAX_STATIONS);
    scanf("%d", &numStations);

    if (numStations <= 0 || numStations > MAX_STATIONS)
    {
        printf("Invalid number of stations.\n");
        return 1;
    }

    for (int i = 0; i < numStations; i++)
    {
        printf("Enter frame data for Station %d: ", i + 1);
        scanf("%s", frames[i]);
    }

    for (int i = 0; i < numStations; i++)
    {
        transmitFrame(i + 1, frames[i]);
    }

    printf("\nSimulation complete.\n\n");

    return 0;
}
