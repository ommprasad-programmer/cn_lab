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

void perform_xor(char *dividend, const char *divisor, int start_index) {
    int divisor_length = strlen(divisor);
    for (int i = 0; i < divisor_length; i++) {
        dividend[start_index + i] = (dividend[start_index + i] == divisor[i]) ? '0' : '1';
    }
}

void compute_crc(const char *data, const char *generator, char *remainder) {
    int data_len = strlen(data);
    int gen_len = strlen(generator);
    char augmented_data[512];

    strcpy(augmented_data, data);
    for (int i = 0; i < gen_len - 1; i++) {
        augmented_data[data_len + i] = '0';
    }
    augmented_data[data_len + gen_len - 1] = '\0';

    int total_len = strlen(augmented_data);
    for (int i = 0; i <= total_len - gen_len; i++) {
        if (augmented_data[i] == '1') {
            perform_xor(augmented_data, generator, i);
        }
    }

    strncpy(remainder, augmented_data + data_len, gen_len - 1);
    remainder[gen_len - 1] = '\0';
}

bool check_syndrome(const char *received_codeword, const char *generator) {
    int codelen = strlen(received_codeword);
    int gen_len = strlen(generator);
    char temp[512];

    strcpy(temp, received_codeword);
    for (int i = 0; i <= codelen - gen_len; i++) {
        if (temp[i] == '1') {
            perform_xor(temp, generator, i);
        }
    }

    for (int i = codelen - gen_len + 1; i < codelen; i++) {
        if (temp[i] != '0') {
            return false;
        }
    }
    return true;
}

int main(void) {
    char data[256];
    char generator[64];
    char remainder[64];
    char codeword[512];
    char received_codeword[512];

    printf("============================================================\n");
    printf("         Cyclic Redundancy Check (CRC) Simulation           \n");
    printf("============================================================\n");

    printf("Enter data bits (binary string): ");
    if (scanf("%255s", data) != 1 || !is_valid_binary(data)) {
        printf("Error: Invalid binary data bits.\n");
        return 1;
    }

    printf("Enter generator polynomial bits (e.g. 10001000000100001 for CRC-16-CCITT or 1101): ");
    if (scanf("%63s", generator) != 1 || !is_valid_binary(generator) || generator[0] != '1') {
        printf("Error: Generator must start with '1' and contain only binary characters.\n");
        return 1;
    }

    if (strlen(generator) > strlen(data) + 1) {
        printf("Error: Generator polynomial length cannot exceed data length + 1.\n");
        return 1;
    }

    compute_crc(data, generator, remainder);

    strcpy(codeword, data);
    strcat(codeword, remainder);

    printf("\n--- Transmitter Side ---\n");
    printf("Original Data:       %s\n", data);
    printf("Generator:           %s\n", generator);
    printf("Computed CRC (FCS):  %s\n", remainder);
    printf("Transmitted Codeword: %s\n", codeword);

    printf("\n--- Receiver Side & Error Simulation ---\n");
    printf("Do you want to simulate a transmission error? (1 for Yes, 0 for No): ");
    int introduce_error = 0;
    if (scanf("%d", &introduce_error) != 1) {
        printf("Error reading option.\n");
        return 1;
    }

    strcpy(received_codeword, codeword);
    if (introduce_error == 1) {
        int error_pos = 0;
        printf("Enter bit position to invert (1 to %lu): ", (unsigned long)strlen(received_codeword));
        if (scanf("%d", &error_pos) != 1 || error_pos < 1 || error_pos > (int)strlen(received_codeword)) {
            printf("Error: Invalid bit position.\n");
            return 1;
        }
        received_codeword[error_pos - 1] = (received_codeword[error_pos - 1] == '0') ? '1' : '0';
        printf("Injected error at position %d.\n", error_pos);
    }

    printf("Received Codeword:   %s\n", received_codeword);
    bool is_valid = check_syndrome(received_codeword, generator);

    if (is_valid) {
        printf("Result: Remainder is 0. Data accepted without errors!\n");
    } else {
        printf("Result: Non-zero remainder detected. Data is corrupted and discarded!\n");
    }

    return 0;
}
