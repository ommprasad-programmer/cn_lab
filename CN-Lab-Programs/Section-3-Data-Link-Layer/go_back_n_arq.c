#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void) {
    int window_size = 0;
    int total_frames = 0;
    int corrupted_frame = -1;

    printf("============================================================\n");
    printf("         Go-Back-N Automatic Repeat Request (ARQ)           \n");
    printf("============================================================\n");

    printf("Enter window size (N): ");
    if (scanf("%d", &window_size) != 1 || window_size <= 0) {
        printf("Error: Window size must be a positive integer.\n");
        return 1;
    }

    printf("Enter total number of frames to send: ");
    if (scanf("%d", &total_frames) != 1 || total_frames <= 0) {
        printf("Error: Total frames must be a positive integer.\n");
        return 1;
    }

    printf("Enter frame number to simulate loss/corruption (-1 for no loss): ");
    if (scanf("%d", &corrupted_frame) != 1) {
        printf("Error: Invalid input.\n");
        return 1;
    }

    int send_base = 1;
    int total_transmissions = 0;
    bool error_simulated = false;

    printf("\n--- Starting Transmission Simulation ---\n");

    while (send_base <= total_frames) {
        int window_end = send_base + window_size - 1;
        if (window_end > total_frames) {
            window_end = total_frames;
        }

        printf("\nCurrent Sender Window: [");
        for (int i = send_base; i <= window_end; i++) {
            printf("%d%s", i, (i == window_end) ? "" : ", ");
        }
        printf("]\n");

        int failed_frame = -1;
        for (int i = send_base; i <= window_end; i++) {
            total_transmissions++;
            printf("  -> Sending Frame %d...", i);

            if (!error_simulated && i == corrupted_frame) {
                printf(" [LOST / CORRUPTED]\n");
                failed_frame = i;
                error_simulated = true;
                break;
            } else {
                printf(" [Received successfully]\n");
            }
        }

        if (failed_frame != -1) {
            printf("! Timer expired waiting for ACK of Frame %d.\n", failed_frame);
            printf("! Go-Back-N triggered: Discarding unacknowledged frames. Retransmitting from Frame %d.\n", failed_frame);
            send_base = failed_frame;
        } else {
            for (int i = send_base; i <= window_end; i++) {
                printf("  <- Cumulative ACK received for Frame %d\n", i);
            }
            send_base = window_end + 1;
        }
    }

    printf("\n============================================================\n");
    printf("All %d frames transmitted and acknowledged successfully!\n", total_frames);
    printf("Total frame transmissions (including retransmissions): %d\n", total_transmissions);
    printf("============================================================\n");

    return 0;
}
