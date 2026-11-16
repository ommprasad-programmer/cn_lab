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

void encode_polar_manchester(const char *binary_string) {
    printf("\n--- Polar Manchester Encoding (IEEE 802.3) ---\n");
    printf("Mapping rule: '0' -> High to Low (+V, -V), '1' -> Low to High (-V, +V)\n");
    printf("Bit stream: ");
    for (int index = 0; binary_string[index] != '\0'; index++) {
        printf("%12c ", binary_string[index]);
    }
    printf("\nFirst half: ");
    for (int index = 0; binary_string[index] != '\0'; index++) {
        if (binary_string[index] == '0') {
            printf("%12s ", "+V");
        } else {
            printf("%12s ", "-V");
        }
    }
    printf("\nSecond half:");
    for (int index = 0; binary_string[index] != '\0'; index++) {
        if (binary_string[index] == '0') {
            printf("%12s ", "-V");
        } else {
            printf("%12s ", "+V");
        }
    }
    printf("\nTransition: ");
    for (int index = 0; binary_string[index] != '\0'; index++) {
        if (binary_string[index] == '0') {
            printf("%12s ", "High->Low");
        } else {
            printf("%12s ", "Low->High");
        }
    }
    printf("\n");
}

void encode_differential_manchester(const char *binary_string) {
    printf("\n--- Differential Manchester Encoding ---\n");
    printf("Mapping rule: '0' -> Transition at start, '1' -> No transition at start\n");
    printf("Every bit period has an inversion at the midpoint.\n");
    printf("Initial reference level: +V\n");

    int current_level = 1;

    printf("Bit stream: ");
    for (int index = 0; binary_string[index] != '\0'; index++) {
        printf("%12c ", binary_string[index]);
    }

    printf("\nFirst half: ");
    for (int index = 0; binary_string[index] != '\0'; index++) {
        if (binary_string[index] == '0') {
            current_level = -current_level;
        }
        if (current_level == 1) {
            printf("%12s ", "+V");
        } else {
            printf("%12s ", "-V");
        }
        current_level = -current_level;
    }

    current_level = 1;
    printf("\nSecond half:");
    for (int index = 0; binary_string[index] != '\0'; index++) {
        if (binary_string[index] == '0') {
            current_level = -current_level;
        }
        current_level = -current_level;
        if (current_level == 1) {
            printf("%12s ", "+V");
        } else {
            printf("%12s ", "-V");
        }
    }

    printf("\nStart Trans:");
    for (int index = 0; binary_string[index] != '\0'; index++) {
        if (binary_string[index] == '0') {
            printf("%12s ", "Transition");
        } else {
            printf("%12s ", "No Trans");
        }
    }
    printf("\n");
}

int main(void) {
    char binary_string[256];

    printf("===============================================================\n");
    printf("  Polar Manchester and Differential Manchester Line Coding     \n");
    printf("===============================================================\n");
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
    encode_polar_manchester(binary_string);
    encode_differential_manchester(binary_string);

    return 0;
}
