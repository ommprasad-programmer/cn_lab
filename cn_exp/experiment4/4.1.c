/*
PR4_1_IPv4AddressValidationAndClassIdentification.c:
Program that validates if the entered string is a valid IPv4 address (e.g., 192.168.1.256
is invalid), and determine its class (A, B, C, D, or E) if the address is a valid one
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to check if a string represents a valid number between 0 and 255
int is_valid_octet(char *str)
{
    int len = strlen(str);

    if (len == 0 || len > 3)
        return 0;

    for (int i = 0; i < len; i++)
    {
        if (!isdigit(str[i]))
            return 0;
    }

    int num = atoi(str);
    if (num < 0 || num > 255)
        return 0;

    return 1;
}

// Function to validate IPv4 address
int validate_ip(char *ip, int *first_octet)
{
    char ip_copy[20];
    strncpy(ip_copy, ip, sizeof(ip_copy));
    ip_copy[sizeof(ip_copy) - 1] = '\0';

    char *token;
    int count = 0;

    token = strtok(ip_copy, ".");
    while (token != NULL)
    {
        if (!is_valid_octet(token))
            return 0;

        if (count == 0)
            *first_octet = atoi(token);

        count++;
        token = strtok(NULL, ".");
    }

    return count == 4;
}

// Determine IP class based on first octet
char get_ip_class(int first_octet)
{
    if (first_octet >= 1 && first_octet <= 126)
        return 'A';
    else if (first_octet >= 128 && first_octet <= 191)
        return 'B';
    else if (first_octet >= 192 && first_octet <= 223)
        return 'C';
    else if (first_octet >= 224 && first_octet <= 239)
        return 'D';
    else if (first_octet >= 240 && first_octet <= 254)
        return 'E';
    else
        return 'U'; // Unknown
}

int main()
{
    char ip[20];
    int first_octet = -1;

    printf("\nEnter an IPv4 address: ");
    scanf("%19s", ip);

    if (validate_ip(ip, &first_octet))
    {
        char ip_class = get_ip_class(first_octet);
        printf("Valid IPv4 address.\n");

        if (ip_class != 'U')
            printf("IP Address Class: %c\n", ip_class);
        else
            printf("IP Address Class: Unknown\n");
    }
    else
    {
        printf("Invalid IPv4 address.\n");
    }

    printf("\n");
    return 0;
}
