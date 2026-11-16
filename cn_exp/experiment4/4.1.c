/*
PR4_1_IPv4ValidationAndClass.c:
Program to implement IPv4 Address Validation and Class Identification.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to validate if the string is a valid IPv4 address
int isValidIPv4(const char *ip_str, int octets[])
{
    int dot_count = 0;
    int len = strlen(ip_str);

    // Quick structural check
    for (int i = 0; i < len; i++)
    {
        if (ip_str[i] == '.')
            dot_count++;
        else if (!isdigit(ip_str[i]))
            return 0;
    }
    if (dot_count != 3)
        return 0;

    // Parse out octets safely
    char temp_str[30];
    strcpy(temp_str, ip_str);
    char *token = strtok(temp_str, ".");
    int i = 0;

    while (token != NULL)
    {
        if (i >= 4)
            return 0;
        int val = atoi(token);
        if (val < 0 || val > 255)
            return 0;
        octets[i++] = val;
        token = strtok(NULL, ".");
    }
    return (i == 4);
}

int main()
{
    char ip_str[30];
    int octets[4];

    printf("\n=== IPv4 Address Validation and Class Identification ===\n");
    printf("Enter an IPv4 Address (e.g., 192.168.1.10): ");
    scanf("%s", ip_str);

    if (!isValidIPv4(ip_str, octets))
    {
        printf("\nResult: Invalid IPv4 Address format.\n\n");
        return 1;
    }

    printf("\nResult: Valid IPv4 Address parsed successfully as: %d.%d.%d.%d\n", octets[0], octets[1], octets[2], octets[3]);
    printf("Class Identification: ");

    // Determine network class bounds based on the first octet
    if (octets[0] >= 1 && octets[0] <= 126)
    {
        printf("Class A\n");
        printf("Default Subnet Mask: 255.0.0.0\n");
        printf("Network ID portion: %d.0.0.0\n", octets[0]);
        printf("Host ID portion: 0.%d.%d.%d\n", octets[1], octets[2], octets[3]);
    }
    else if (octets[0] == 127)
    {
        printf("Class A (Loopback/Reserved Address)\n");
    }
    else if (octets[0] >= 128 && octets[0] <= 191)
    {
        printf("Class B\n");
        printf("Default Subnet Mask: 255.255.0.0\n");
        printf("Network ID portion: %d.%d.0.0\n", octets[0], octets[1]);
        printf("Host ID portion: 0.0.%d.%d\n", octets[2], octets[3]);
    }
    else if (octets[0] >= 192 && octets[0] <= 223)
    {
        printf("Class C\n");
        printf("Default Subnet Mask: 255.255.255.0\n");
        printf("Network ID portion: %d.%d.%d.0\n", octets[0], octets[1], octets[2]);
        printf("Host ID portion: 0.0.0.%d\n", octets[3]);
    }
    else if (octets[0] >= 224 && octets[0] <= 239)
    {
        printf("Class D (Multicast Addressing - No network/host separation)\n");
    }
    else if (octets[0] >= 240 && octets[0] <= 255)
    {
        printf("Class E (Experimental/Reserved - No network/host separation)\n");
    }
    else
    {
        printf("Unknown Class\n");
    }
    printf("\n");
    return 0;
}
