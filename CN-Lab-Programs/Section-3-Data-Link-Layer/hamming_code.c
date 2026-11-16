#include <stdio.h>
#include <stdbool.h>

int main(void) {
    int data[4];
    int codeword[8];
    int received[8];

    printf("============================================================\n");
    printf("     Hamming (7,4) Error Detection and Correction Code      \n");
    printf("============================================================\n");

    printf("Enter 4 data bits (space-separated, e.g. 1 0 1 1): ");
    for (int i = 0; i < 4; i++) {
        if (scanf("%d", &data[i]) != 1 || (data[i] != 0 && data[i] != 1)) {
            printf("Error: Data bits must be 0 or 1.\n");
            return 1;
        }
    }

    int d1 = data[0];
    int d2 = data[1];
    int d3 = data[2];
    int d4 = data[3];

    int p1 = d1 ^ d2 ^ d4;
    int p2 = d1 ^ d3 ^ d4;
    int p4 = d2 ^ d3 ^ d4;

    codeword[1] = p1;
    codeword[2] = p2;
    codeword[3] = d1;
    codeword[4] = p4;
    codeword[5] = d2;
    codeword[6] = d3;
    codeword[7] = d4;

    printf("\n--- Transmitter Side ---\n");
    printf("Data bits: d1=%d, d2=%d, d3=%d, d4=%d\n", d1, d2, d3, d4);
    printf("Calculated Parity bits: p1=%d, p2=%d, p4=%d\n", p1, p2, p4);
    printf("Bit positions:   1  2  3  4  5  6  7\n");
    printf("Bit labels:     p1 p2 d1 p4 d2 d3 d4\n");
    printf("Codeword bits:   ");
    for (int i = 1; i <= 7; i++) {
        printf("%d  ", codeword[i]);
    }
    printf("\n");

    for (int i = 1; i <= 7; i++) {
        received[i] = codeword[i];
    }

    printf("\n--- Transmission Channel Simulation ---\n");
    printf("Introduce single-bit error? (1 for Yes, 0 for No): ");
    int choice = 0;
    if (scanf("%d", &choice) != 1) {
        printf("Error: Invalid choice.\n");
        return 1;
    }

    if (choice == 1) {
        int error_pos = 0;
        printf("Enter bit position to flip (1 to 7): ");
        if (scanf("%d", &error_pos) != 1 || error_pos < 1 || error_pos > 7) {
            printf("Error: Bit position must be between 1 and 7.\n");
            return 1;
        }
        received[error_pos] = 1 - received[error_pos];
        printf("Bit at position %d flipped.\n", error_pos);
    }

    printf("Received Codeword: ");
    for (int i = 1; i <= 7; i++) {
        printf("%d ", received[i]);
    }
    printf("\n");

    printf("\n--- Receiver Side Error Detection & Correction ---\n");
    int s1 = received[1] ^ received[3] ^ received[5] ^ received[7];
    int s2 = received[2] ^ received[3] ^ received[6] ^ received[7];
    int s4 = received[4] ^ received[5] ^ received[6] ^ received[7];

    int error_syndrome = s4 * 4 + s2 * 2 + s1;
    printf("Calculated Syndrome: s4=%d, s2=%d, s1=%d (Syndrome value: %d)\n", s4, s2, s1, error_syndrome);

    if (error_syndrome == 0) {
        printf("Result: No error detected. Data received correctly.\n");
    } else {
        printf("Result: Error detected at bit position %d!\n", error_syndrome);
        received[error_syndrome] = 1 - received[error_syndrome];
        printf("Corrected Codeword: ");
        for (int i = 1; i <= 7; i++) {
            printf("%d ", received[i]);
        }
        printf("\n");
    }

    printf("Decoded Data Bits (d1, d2, d3, d4): %d %d %d %d\n",
           received[3], received[5], received[6], received[7]);

    return 0;
}
