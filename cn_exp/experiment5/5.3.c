/*
PR5_3_TCPCongestionControl.c:
Program to simulate TCP Congestion Control (Slow Start and Congestion Avoidance profiles).
*/

#include <stdio.h>

int main()
{
    int total_rounds;
    int cwnd = 1;      // Initial Congestion Window starts at 1 Maximum Segment Size (MSS)
    int ssthresh = 16; // Initial Slow Start Threshold limits
    int drop_round;

    printf("\n=== Simulation of TCP Congestion Control Algorithm ===\n");
    printf("Enter the total simulation runtime rounds to execute: ");
    scanf("%d", &total_rounds);
    printf("Enter a specific execution round to introduce a Packet Drop Timeout (e.g., 7): ");
    scanf("%d", &drop_round);

    printf("\nStarting state conditions initialized: cwnd = %d MSS | ssthresh = %d\n", cwnd, ssthresh);
    printf("-----------------------------------------------------------------------\n");
    printf("Round\tCongestion Window (cwnd)\tssthresh\tActive Engine Phase\n");
    printf("-----------------------------------------------------------------------\n");

    for (int round = 1; round <= total_rounds; round++)
    {
        // Output evaluation variables map at beginning of each phase interval
        printf("%d\t%d MSS\t\t\t%d\t\t", round, cwnd, ssthresh);

        if (cwnd < ssthresh)
        {
            printf("Slow Start (Exponential)\n");
        }
        else
        {
            printf("Congestion Avoidance (Linear)\n");
        }

        // Evaluate network anomalies when reaching the simulated drop index window
        if (round == drop_round)
        {
            printf("\n[!] NETWORK EVENT: Packet Timeout/Drop detected in Round %d [!]\n", round);
            ssthresh = cwnd / 2;
            if (ssthresh < 2)
                ssthresh = 2; // Floor limits baseline protection
            cwnd = 1;         // Reset to slow start baseline configurations
            printf("Action Taken: ssthresh updated to %d, cwnd window dropped to %d MSS.\n\n", ssthresh, cwnd);
            continue;
        }

        // Growth dynamics computation based on threshold state
        if (cwnd < ssthresh)
        {
            cwnd = cwnd * 2; // Slow Start: double window size per round
        }
        else
        {
            cwnd = cwnd + 1; // Congestion Avoidance: increments linearly by 1 per round
        }
    }
    printf("-----------------------------------------------------------------------\n\n");

    return 0;
}
