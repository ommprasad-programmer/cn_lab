#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STATIONS 10
#define MAX_COLLISIONS 10

typedef struct {
    int id;
    char frame_data[64];
    bool completed;
    int collision_count;
    int backoff_slots;
    bool aborted;
} Station;

int main(void) {
    int station_count = 0;
    Station stations[MAX_STATIONS];
    unsigned int random_seed = 42;

    printf("============================================================\n");
    printf("     CSMA/CD with Binary Exponential Backoff Simulation     \n");
    printf("============================================================\n");

    printf("Enter number of stations (2 to %d): ", MAX_STATIONS);
    if (scanf("%d", &station_count) != 1 || station_count < 2 || station_count > MAX_STATIONS) {
        printf("Error: Station count must be between 2 and %d.\n", MAX_STATIONS);
        return 1;
    }

    printf("Enter random seed for simulation (e.g. 42 for reproducible run): ");
    if (scanf("%u", &random_seed) != 1) {
        printf("Error reading random seed.\n");
        return 1;
    }
    srand(random_seed);

    for (int i = 0; i < station_count; i++) {
        stations[i].id = i + 1;
        stations[i].completed = false;
        stations[i].aborted = false;
        stations[i].collision_count = 0;
        stations[i].backoff_slots = 0;

        printf("Enter frame data for Station %d: ", i + 1);
        if (scanf("%63s", stations[i].frame_data) != 1) {
            printf("Error reading frame data.\n");
            return 1;
        }
    }

    printf("\n--- Starting CSMA/CD Simulation ---\n");

    int time_slot = 0;
    int remaining = station_count;

    while (remaining > 0 && time_slot < 100) {
        time_slot++;
        printf("\n[Time Slot %d]\n", time_slot);

        int ready_indices[MAX_STATIONS];
        int ready_count = 0;

        for (int i = 0; i < station_count; i++) {
            if (!stations[i].completed && !stations[i].aborted) {
                if (stations[i].backoff_slots > 0) {
                    stations[i].backoff_slots--;
                    printf("  Station %d: Carrier sensed busy/backing off (Remaining wait: %d slots)\n",
                           stations[i].id, stations[i].backoff_slots);
                } else {
                    printf("  Station %d: Carrier sensed IDLE. Attempting transmission of '%s'...\n",
                           stations[i].id, stations[i].frame_data);
                    ready_indices[ready_count++] = i;
                }
            }
        }

        if (ready_count == 1) {
            int winner = ready_indices[0];
            stations[winner].completed = true;
            remaining--;
            printf("  >>> SUCCESS: Station %d successfully transmitted frame '%s' without collision.\n",
                   stations[winner].id, stations[winner].frame_data);
        } else if (ready_count > 1) {
            printf("  !!! COLLISION DETECTED among %d stations: ", ready_count);
            for (int r = 0; r < ready_count; r++) {
                printf("Station %d ", stations[ready_indices[r]].id);
            }
            printf("\n  Jamming signal broadcasted.\n");

            for (int r = 0; r < ready_count; r++) {
                int idx = ready_indices[r];
                stations[idx].collision_count++;
                if (stations[idx].collision_count > MAX_COLLISIONS) {
                    stations[idx].aborted = true;
                    remaining--;
                    printf("  Station %d: Exceeded maximum collision limit (%d). Transmission ABORTED.\n",
                           stations[idx].id, MAX_COLLISIONS);
                } else {
                    int k = stations[idx].collision_count;
                    if (k > 10) k = 10;
                    int max_range = (1 << k);
                    stations[idx].backoff_slots = rand() % max_range;
                    printf("  Station %d: Collision #%d. Backoff range [0, %d]. Selected wait: %d slots.\n",
                           stations[idx].id, stations[idx].collision_count, max_range - 1, stations[idx].backoff_slots);
                }
            }
        } else {
            printf("  Channel idle. All active stations in backoff state.\n");
        }
    }

    printf("\n============================================================\n");
    printf("                  CSMA/CD Final Report                      \n");
    printf("============================================================\n");
    printf("%-10s %-15s %-12s %-15s\n", "Station", "Frame Data", "Collisions", "Final Status");
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < station_count; i++) {
        const char *status_str = stations[i].completed ? "SUCCESS" : (stations[i].aborted ? "ABORTED" : "PENDING");
        printf("%-10d %-15s %-12d %-15s\n",
               stations[i].id, stations[i].frame_data, stations[i].collision_count, status_str);
    }
    printf("------------------------------------------------------------\n");

    return 0;
}
