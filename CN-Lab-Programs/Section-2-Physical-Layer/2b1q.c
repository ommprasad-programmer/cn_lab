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

int get_2b1q_level(char first_bit, char second_bit, int previous_level) {
    if (previous_level > 0) {
        if (first_bit == '0' && second_bit == '0') return 1;
        if (first_bit == '0' && second_bit == '1') return 3;
        if (first_bit == '1' && second_bit == '0') return -1;
        if (first_bit == '1' && second_bit == '1') return -3;
    } else {
        if (first_bit == '0' && second_bit == '0') return -1;
        if (first_bit == '0' && second_bit == '1') return -3;
        if (first_bit == '1' && second_bit == '0') return 1;
        if (first_bit == '1' && second_bit == '1') return 3;
    }
    return 1;
}

void encode_2b1q(const char *binary_string) {
    int length = strlen(binary_string);
    int previous_level = 1;

    printf("\n--- 2B1Q (Two-Binary One-Quaternary) Encoding ---\n");
    printf("Initial previous signal level: +1V\n\n");
    printf("%-10s %-12s %-16s %-16s\n", "Dibit #", "Bit Pair", "Previous Level", "Output Level");
    printf("------------------------------------------------------------\n");

    for (int index = 0; index < length; index += 2) {
        char first_bit = binary_string[index];
        char second_bit = binary_string[index + 1];
        int next_level = get_2b1q_level(first_bit, second_bit, previous_level);

        printf("%-10d %c%c         %+2dV             %+2dV\n",
               (index / 2) + 1, first_bit, second_bit, previous_level, next_level);

        previous_level = next_level;
    }

    printf("------------------------------------------------------------\n");
    printf("Quaternary sequence: ");
    previous_level = 1;
    for (int index = 0; index < length; index += 2) {
        int next_level = get_2b1q_level(binary_string[index], binary_string[index + 1], previous_level);
        printf("%+dV ", next_level);
        previous_level = next_level;
    }
    printf("\n");
}

int main(void) {
    char binary_string[256];

    printf("==================================================\n");
    printf("        2B1Q Multilevel Line Coding               \n");
    printf("==================================================\n");
    printf("Enter binary string (length must be even, 0s and 1s only): ");

    if (scanf("%255s", binary_string) != 1) {
        printf("Error: Failed to read input.\n");
        return 1;
    }

    if (!is_valid_binary(binary_string)) {
        printf("Error: Input contains invalid characters. Only '0' and '1' are allowed.\n");
        return 1;
    }

    if (strlen(binary_string) % 2 != 0) {
        printf("Error: 2B1Q requires an even number of bits (pairs of 2 bits).\n");
        return 1;
    }

    printf("\nInput Binary String: %s (Length = %lu bits, %lu dibits)\n",
           binary_string, (unsigned long)strlen(binary_string), (unsigned long)strlen(binary_string) / 2);

    encode_2b1q(binary_string);

    return 0;
}
