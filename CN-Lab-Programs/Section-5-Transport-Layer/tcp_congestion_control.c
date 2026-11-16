#include <stdio.h>
#include <stdbool.h>

#define MAX_ROUNDS 50

int main(void) {
    int total_rounds = 0;
    int initial_ssthresh = 16;
    int loss_round = -1;
    int loss_type = 1;

    printf("============================================================\n");
    printf("         TCP Congestion Control Simulation (Tahoe / Reno)   \n");
    printf("============================================================\n");

    printf("Enter number of transmission rounds (1 to %d, e.g. 20): ", MAX_ROUNDS);
    if (scanf("%d", &total_rounds) != 1 || total_rounds < 1 || total_rounds > MAX_ROUNDS) {
        printf("Error: Invalid number of rounds.\n");
        return 1;
    }

    printf("Enter initial Slow Start Threshold (ssthresh in MSS, e.g. 16): ");
    if (scanf("%d", &initial_ssthresh) != 1 || initial_ssthresh < 2) {
        printf("Error: Initial ssthresh must be at least 2.\n");
        return 1;
    }

    printf("Enter round number where packet loss occurs (or -1 for no loss, e.g. 10): ");
    if (scanf("%d", &loss_round) != 1) {
        printf("Error reading loss round.\n");
        return 1;
    }

    if (loss_round > 0) {
        printf("Select Loss Event Type:\n");
        printf("  1. Triple Duplicate ACKs (TCP Reno - Fast Retransmit / Fast Recovery)\n");
        printf("  2. Timeout (TCP Tahoe - Drop to cwnd = 1)\n");
        printf("Enter choice (1 or 2): ");
        if (scanf("%d", &loss_type) != 1 || (loss_type != 1 && loss_type != 2)) {
            printf("Error: Invalid choice. Defaulting to 1 (Reno).\n");
            loss_type = 1;
        }
    }

    int cwnd = 1;
    int ssthresh = initial_ssthresh;
    int cwnd_history[MAX_ROUNDS + 1];

    printf("\n====================================================================================\n");
    printf("%-8s %-12s %-14s %-24s %-20s\n", "Round", "cwnd (MSS)", "ssthresh (MSS)", "Phase", "Event");
    printf("====================================================================================\n");

    for (int round = 1; round <= total_rounds; round++) {
        cwnd_history[round] = cwnd;
        const char *phase_str = (cwnd < ssthresh) ? "Slow Start" : "Congestion Avoidance";
        const char *event_str = "Normal ACK";

        if (round == loss_round) {
            if (loss_type == 1) {
                event_str = "3 Dup ACKs (Reno Loss)";
                printf("%-8d %-12d %-14d %-24s %-20s\n", round, cwnd, ssthresh, phase_str, event_str);

                ssthresh = cwnd / 2;
                if (ssthresh < 2) ssthresh = 2;
                cwnd = ssthresh;
            } else {
                event_str = "Timeout (Tahoe Loss)";
                printf("%-8d %-12d %-14d %-24s %-20s\n", round, cwnd, ssthresh, phase_str, event_str);

                ssthresh = cwnd / 2;
                if (ssthresh < 2) ssthresh = 2;
                cwnd = 1;
            }
            continue;
        }

        printf("%-8d %-12d %-14d %-24s %-20s\n", round, cwnd, ssthresh, phase_str, event_str);

        if (cwnd < ssthresh) {
            cwnd = cwnd * 2;
            if (cwnd > ssthresh && (cwnd / 2) < ssthresh) {
                cwnd = ssthresh;
            }
        } else {
            cwnd = cwnd + 1;
        }
    }

    printf("====================================================================================\n");
    printf("\n--- Congestion Window (cwnd) ASCII Graph Progression ---\n");
    for (int round = 1; round <= total_rounds; round++) {
        printf("R%2d (%2d MSS): ", round, cwnd_history[round]);
        for (int b = 0; b < cwnd_history[round]; b++) {
            printf("#");
        }
        printf("\n");
    }
    printf("------------------------------------------------------------------------------------\n");

    return 0;
}
