/*
PR4_5_IP_Fragmentation.c:
Program to simulate IPv4 Fragmentation & Reassembly.
*/

#include <stdio.h>

int main()
{
    int packet_id, total_length, mtu, header_size = 20;

    printf("\n=== IPv4 Fragmentation and Reassembly Simulator ===\n");
    printf("Enter Unique Identification Number (Packet ID): ");
    scanf("%d", &packet_id);
    printf("Enter Total Packet Length (bytes, including 20-byte IP header): ");
    scanf("%d", &total_length);
    printf("Enter Maximum Transmission Unit (MTU size in bytes): ");
    scanf("%d", &mtu);

    if (mtu <= header_size)
    {
        printf("Error: MTU size configuration is too small for standard IP headers.\n");
        return 1;
    }

    int payload_total = total_length - header_size;
    int max_fragment_payload = mtu - header_size;

    // Fragment payloads (except the last one) must be multiples of 8 bytes
    max_fragment_payload = (max_fragment_payload / 8) * 8;

    printf("\n--- Generated Fragment Metadata Output ---\n");
    printf("------------------------------------------------------------------------\n");
    printf("Frag #\tTotal Len\tHeader\tPayload\tOffset\tMF Flag\n");
    printf("------------------------------------------------------------------------\n");

    int offset = 0;
    int bytes_remaining = payload_total;
    int frag_count = 0;

    while (bytes_remaining > 0)
    {
        frag_count++;
        int current_payload = (bytes_remaining > max_fragment_payload) ? max_fragment_payload : bytes_remaining;
        int current_total = current_payload + header_size;
        int mf_flag = (bytes_remaining > max_fragment_payload) ? 1 : 0;

        printf("%d\t%d\t\t%d\t%d\t%d\t%d\n", frag_count, current_total, header_size, current_payload, offset, mf_flag);

        bytes_remaining -= current_payload;
        offset += (current_payload / 8); // Offset unit is scaled by 8 bytes
    }
    printf("------------------------------------------------------------------------\n");
    printf("Reassembly Sequence Status: Success. Reconstructed %d payloads into original packet layout.\n\n", frag_count);

    return 0;
}
