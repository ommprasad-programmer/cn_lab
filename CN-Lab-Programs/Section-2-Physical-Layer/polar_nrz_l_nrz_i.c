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

void encode_nrz_l(const char *binary_string) {
    printf("\n--- Polar NRZ-L (Non-Return-to-Zero Level) ---\n");
    printf("Mapping rule: '0' -> +V, '1' -> -V\n");
    printf("Bit stream: ");
    for (int index = 0; binary_string[index] != '\0'; index++) {
        printf("%6c ", binary_string[index]);
    }
    printf("\nVoltages:   ");
    for (int index = 0; binary_string[index] != '\0'; index++) {
        if (binary_string[index] == '0') {
            printf("%6s ", "+V");
        } else {
            printf("%6s ", "-V");
        }
    }
    printf("\n");
}

void encode_nrz_i(const char *binary_string) {
    printf("\n--- Polar NRZ-I (Non-Return-to-Zero Invert) ---\n");
    printf("Mapping rule: '1' -> Invert level, '0' -> Keep previous level\n");
    printf("Initial reference level: +V\n");
    printf("Bit stream: ");
    for (int index = 0; binary_string[index] != '\0'; index++) {
        printf("%6c ", binary_string[index]);
    }
    printf("\nVoltages:   ");
    int current_level = 1;
    for (int index = 0; binary_string[index] != '\0'; index++) {
        if (binary_string[index] == '1') {
            current_level = -current_level;
        }
        if (current_level == 1) {
            printf("%6s ", "+V");
        } else {
            printf("%6s ", "-V");
        }
    }
    printf("\n");
}

int main(void) {
    char binary_string[256];

    printf("==================================================\n");
    printf("   Polar NRZ-L and NRZ-I Line Coding Simulation   \n");
    printf("==================================================\n");
    printf("Enter binary input string (0s and 1s only): ");

    if (scanf("%255s", binary_string) != 1) {
        printf("Error: Failed to read input.\n");
        return 1;
    }

    if (!is_valid_binary(binary_string)) {
        printf("Error: Input contains invalid characters. Only '0' and '1' are allowed.\n");
        return 1;
    }

    printf("\nInput Binary String: %s\n", binary_string);
    encode_nrz_l(binary_string);
    encode_nrz_i(binary_string);

    return 0;
}
