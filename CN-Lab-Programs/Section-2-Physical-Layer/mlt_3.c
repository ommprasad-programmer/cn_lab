#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_valid_binary(const char *binary_string) {
    if (binary_string == NULL || strlen(binary_string) == 0) {
        return false;
    }
    for (int index = 0; binary_string[index] != '\0'; index++) {
        if (binary_string[index] != '0' && binary_string[index] != '1') {
            return false;
        }
    }
    return true;
}

void encode_mlt_3(const char *binary_string) {
    int length = strlen(binary_string);
    int current_level = 0;
    int previous_nonzero = -1;

    printf("\n--- MLT-3 (Multi-Level Transmit 3-Levels) Encoding ---\n");
    printf("Rule: '0' -> No change. '1' -> Transition between [0 -> +V -> 0 -> -V -> 0]\n");
    printf("Initial state: 0V, previous non-zero reference: -V\n\n");

    printf("%-10s %-12s %-16s %-16s\n", "Bit #", "Bit Value", "Previous Level", "Output Level");
    printf("------------------------------------------------------------\n");

    for (int index = 0; index < length; index++) {
        int old_level = current_level;
        if (binary_string[index] == '1') {
            if (current_level != 0) {
                current_level = 0;
            } else {
                if (previous_nonzero == -1) {
                    current_level = 1;
                    previous_nonzero = 1;
                } else {
                    current_level = -1;
                    previous_nonzero = -1;
                }
            }
        }

        const char *old_str = (old_level == 1) ? "+V" : (old_level == -1 ? "-V" : "0V");
        const char *new_str = (current_level == 1) ? "+V" : (current_level == -1 ? "-V" : "0V");

        printf("%-10d %-12c %-16s %-16s\n", index + 1, binary_string[index], old_str, new_str);
    }

    printf("------------------------------------------------------------\n");
    printf("Encoded signal levels: ");
    current_level = 0;
    previous_nonzero = -1;
    for (int index = 0; index < length; index++) {
        if (binary_string[index] == '1') {
            if (current_level != 0) {
                current_level = 0;
            } else {
                if (previous_nonzero == -1) {
                    current_level = 1;
                    previous_nonzero = 1;
                } else {
                    current_level = -1;
                    previous_nonzero = -1;
                }
            }
        }
        if (current_level == 1) printf("+V ");
        else if (current_level == -1) printf("-V ");
        else printf("0V ");
    }
    printf("\n");
}

int main(void) {
    char binary_string[256];

    printf("==================================================\n");
    printf("             MLT-3 Line Coding Simulation         \n");
    printf("==================================================\n");
    printf("Enter binary string (0s and 1s only): ");

    if (scanf("%255s", binary_string) != 1) {
        printf("Error: Failed to read input.\n");
        return 1;
    }

    if (!is_valid_binary(binary_string)) {
        printf("Error: Input contains invalid characters. Only '0' and '1' are allowed.\n");
        return 1;
    }

    printf("\nInput Binary String: %s (Length = %lu)\n", binary_string, (unsigned long)strlen(binary_string));
    encode_mlt_3(binary_string);

    return 0;
}
