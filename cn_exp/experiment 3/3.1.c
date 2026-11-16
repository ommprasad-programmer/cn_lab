/*
PR3_1_CRC.c:
Program to implement the Cyclic Redundancy Check (CRC) error detection method.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h> // For malloc and free

// Function to perform XOR operation on two binary strings
char *findXor(char *a, char *b)
{
    int n = strlen(b);
    char *result = (char *)malloc(sizeof(char) * n);
    if (result == NULL)
    {
        perror("\nMemory allocation failed");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i < n; i++)
    { // Skip the first bit for CRC division
        result[i - 1] = (a[i] == b[i]) ? '0' : '1';
    }
    result[n - 1] = '\0';
    return result;
}

// Function to perform Modulo-2 division (CRC division algorithm)
char *mod2div(char *dividend, char *divisor)
{
    int n_dividend = strlen(dividend);
    int n_divisor = strlen(divisor);

    char *temp_dividend = (char *)malloc(sizeof(char) * (n_dividend + 1));
    if (temp_dividend == NULL)
    {
        perror("\nMemory allocation failed");
        exit(EXIT_FAILURE);
    }
    strcpy(temp_dividend, dividend);

    for (int i = 0; i <= n_dividend - n_divisor; i++)
    {
        if (temp_dividend[i] == '1')
        {
            char *xor_result = findXor(&temp_dividend[i], divisor);
            for (int j = 0; j < n_divisor - 1; j++)
            {
                temp_dividend[i + 1 + j] = xor_result[j];
            }
            free(xor_result);
        }
    }

    char *remainder = (char *)malloc(sizeof(char) * (n_divisor));
    if (remainder == NULL)
    {
        perror("\nMemory allocation failed");
        exit(EXIT_FAILURE);
    }
    strncpy(remainder, &temp_dividend[n_dividend - n_divisor + 1], n_divisor - 1);
    remainder[n_divisor - 1] = '\0';
    free(temp_dividend);
    return remainder;
}

// Sender side: Encodes data by appending CRC checksum
char *encodeData(char *data, char *key)
{
    int n_key = strlen(key);
    int n_data = strlen(data);
    char *padded_data = (char *)malloc(sizeof(char) * (n_data + n_key));
    if (padded_data == NULL)
    {
        perror("\nMemory allocation failed");
        exit(EXIT_FAILURE);
    }
    strcpy(padded_data, data);
    for (int i = 0; i < n_key - 1; i++)
    {
        padded_data[n_data + i] = '0';
    }
    padded_data[n_data + n_key - 1] = '\0';

    char *remainder = mod2div(padded_data, key);
    char *encoded_data = (char *)malloc(sizeof(char) * (n_data + n_key));
    if (encoded_data == NULL)
    {
        perror("\nMemory allocation failed");
        exit(EXIT_FAILURE);
    }
    strcpy(encoded_data, data);
    strcat(encoded_data, remainder);
    free(padded_data);
    free(remainder);
    return encoded_data;
}

// Receiver side: Checks if received data has errors
int receiver(char *code, char *key)
{
    char *remainder = mod2div(code, key);
    int error_detected = 0;
    for (int i = 0; i < strlen(remainder); i++)
    {
        if (remainder[i] == '1')
        {
            error_detected = 1;
            break;
        }
    }
    free(remainder);
    return !error_detected; // Returns 1 if no error, 0 if error detected
}

int main()
{
    char data[100];
    char key[100];

    printf("\nEnter the data to be sent (in binary): ");
    scanf("%s", data);
    printf("Enter the pre-determined divisor (in binary): ");
    scanf("%s", key);

    printf("\n-- Sender Side --\n");
    printf("Data: %s\n", data);
    printf("Pre-determined divisor: %s\n", key);

    char *encoded_data = encodeData(data, key);
    printf("Codeword (Data + CRC): %s\n", encoded_data);

    printf("\n-- Receiver Side --\n");
    if (receiver(encoded_data, key))
    {
        printf("Data is correct (No errors detected)\n");
    }
    else
    {
        printf("Data is incorrect (Error detected)\n");
    }

    // Simulate an error
    printf("\nSimulating an error...\n");
    if (strlen(encoded_data) > 0)
    {
        encoded_data[0] = (encoded_data[0] == '0') ? '1' : '0'; // Flip the first bit
    }
    printf("Erroneous Received Data: %s\n", encoded_data);

    if (receiver(encoded_data, key))
    {
        printf("Data is correct (No errors detected)\n");
    }
    else
    {
        printf("Data is incorrect (Error detected)\n");
    }

    free(encoded_data); // Free dynamically allocated memory
    printf("\n");
    return 0;
}
