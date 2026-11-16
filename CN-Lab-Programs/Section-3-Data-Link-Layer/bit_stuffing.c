#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_valid_binary(const char *str) {
    if (str == NULL || strlen(str) == 0) return false;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] != '0' && str[i] != '1') return false;
    }
    return true;
}

void stuff_bits(const char *input, char *stuffed) {
    int consecutive_ones = 0;
    int write_idx = 0;

    for (int i = 0; input[i] != '\0'; i++) {
        stuffed[write_idx++] = input[i];
        if (input[i] == '1') {
            consecutive_ones++;
            if (consecutive_ones == 5) {
                stuffed[write_idx++] = '0';
                consecutive_ones = 0;
            }
        } else {
            consecutive_ones = 0;
        }
    }
    stuffed[write_idx] = '\0';
}

void destuff_bits(const char *stuffed, char *destuffed) {
    int consecutive_ones = 0;
    int write_idx = 0;

    for (int i = 0; stuffed[i] != '\0'; i++) {
        destuffed[write_idx++] = stuffed[i];
        if (stuffed[i] == '1') {
            consecutive_ones++;
            if (consecutive_ones == 5) {
                if (stuffed[i + 1] == '0') {
                    i++;
                }
                consecutive_ones = 0;
            }
        } else {
            consecutive_ones = 0;
        }
    }
    destuffed[write_idx] = '\0';
}

int main(void) {
    char original_data[256];
    char stuffed_data[512];
    char destuffed_data[512];
    const char *flag_sequence = "01111110";

    printf("============================================================\n");
    printf("              Bit Stuffing and Destuffing Simulation        \n");
    printf("============================================================\n");

    printf("Enter binary string (e.g. 0111111011111001): ");
    if (scanf("%255s", original_data) != 1 || !is_valid_binary(original_data)) {
        printf("Error: Input must contain only binary digits ('0' and '1').\n");
        return 1;
    }

    stuff_bits(original_data, stuffed_data);
    destuff_bits(stuffed_data, destuffed_data);

    printf("\n--- Results ---\n");
    printf("Original Data:       %s (Length: %lu)\n", original_data, (unsigned long)strlen(original_data));
    printf("Stuffed Payload:     %s (Length: %lu)\n", stuffed_data, (unsigned long)strlen(stuffed_data));
    printf("Framed Transmission: %s %s %s\n", flag_sequence, stuffed_data, flag_sequence);
    printf("Destuffed Data:      %s (Length: %lu)\n", destuffed_data, (unsigned long)strlen(destuffed_data));

    if (strcmp(original_data, destuffed_data) == 0) {
        printf("Verification:        Success (Destuffed bit stream matches original data)\n");
    } else {
        printf("Verification:        Mismatch detected!\n");
    }

    return 0;
}
