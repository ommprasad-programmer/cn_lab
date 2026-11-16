#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_FRAMES 50

typedef struct {
    int frame_id;
    char data[32];
    bool is_acknowledged;
    bool is_buffered_at_receiver;
} Frame;

int main(void) {
    int window_size = 0;
    int total_frames = 0;
    int lost_frame_id = -1;
    Frame frames[MAX_FRAMES];

    printf("============================================================\n");
    printf("       Selective Repeat Automatic Repeat Request (ARQ)      \n");
    printf("============================================================\n");

    printf("Enter window size (N): ");
    if (scanf("%d", &window_size) != 1 || window_size <= 0 || window_size > MAX_FRAMES) {
        printf("Error: Invalid window size.\n");
        return 1;
    }

    printf("Enter total number of frames to send (1 to %d): ", MAX_FRAMES);
    if (scanf("%d", &total_frames) != 1 || total_frames <= 0 || total_frames > MAX_FRAMES) {
        printf("Error: Invalid number of frames.\n");
        return 1;
    }

    for (int i = 0; i < total_frames; i++) {
        frames[i].frame_id = i + 1;
        frames[i].is_acknowledged = false;
        frames[i].is_buffered_at_receiver = false;
        printf("Enter data for Frame %d: ", i + 1);
        if (scanf("%31s", frames[i].data) != 1) {
            printf("Error reading frame data.\n");
            return 1;
        }
    }

    printf("Enter frame ID to simulate packet loss (-1 for no loss): ");
    if (scanf("%d", &lost_frame_id) != 1) {
        printf("Error reading lost frame choice.\n");
        return 1;
    }

    int send_base = 0;
    bool loss_simulated = false;
    int total_transmissions = 0;

    printf("\n--- Starting Selective Repeat Transmission ---\n");

    while (send_base < total_frames) {
        int window_end = send_base + window_size;
        if (window_end > total_frames) {
            window_end = total_frames;
        }

        printf("\nSender Window: [Frames %d to %d]\n", send_base + 1, window_end);

        for (int i = send_base; i < window_end; i++) {
            if (!frames[i].is_acknowledged) {
                total_transmissions++;
                printf("  -> Transmitting Frame %d ('%s')...", frames[i].frame_id, frames[i].data);

                if (!loss_simulated && frames[i].frame_id == lost_frame_id) {
                    printf(" [PACKET LOST]\n");
                    loss_simulated = true;
                } else {
                    printf(" [Received at Receiver]\n");
                    frames[i].is_buffered_at_receiver = true;
                }
            }
        }

        for (int i = send_base; i < window_end; i++) {
            if (frames[i].is_buffered_at_receiver && !frames[i].is_acknowledged) {
                frames[i].is_acknowledged = true;
                printf("  <- ACK received for Frame %d\n", frames[i].frame_id);
            } else if (!frames[i].is_buffered_at_receiver) {
                printf("  ! NAK / Timeout triggered for lost Frame %d\n", frames[i].frame_id);
                printf("  -> Retransmitting ONLY Frame %d ('%s')...\n", frames[i].frame_id, frames[i].data);
                total_transmissions++;
                frames[i].is_buffered_at_receiver = true;
                frames[i].is_acknowledged = true;
                printf("  <- ACK received for retransmitted Frame %d\n", frames[i].frame_id);
            }
        }

        while (send_base < total_frames && frames[send_base].is_acknowledged) {
            send_base++;
        }
    }

    printf("\n============================================================\n");
    printf("All %d frames successfully transmitted and received!\n", total_frames);
    printf("Total transmissions: %d\n", total_transmissions);
    printf("============================================================\n");

    return 0;
}
