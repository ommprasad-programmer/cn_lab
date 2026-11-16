#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DEFAULT_IP_HEADER 20
#define MAX_FRAGMENTS 100

typedef struct {
    int fragment_index;
    int header_length;
    int payload_length;
    int total_length;
    int offset;
    int more_fragments;
} Fragment;

int main(void) {
    int total_packet_size = 0;
    int mtu = 0;
    int header_size = DEFAULT_IP_HEADER;

    printf("============================================================\n");
    printf("         IPv4 Fragmentation and Reassembly Simulation       \n");
    printf("============================================================\n");

    printf("Enter Total Packet Size in bytes (including 20-byte IP header, e.g. 4000): ");
    if (scanf("%d", &total_packet_size) != 1 || total_packet_size <= header_size) {
        printf("Error: Packet size must be greater than IP header size (%d bytes).\n", header_size);
        return 1;
    }

    printf("Enter MTU (Maximum Transmission Unit) in bytes (e.g. 1500): ");
    if (scanf("%d", &mtu) != 1 || mtu <= header_size) {
        printf("Error: MTU must be strictly greater than IP header size (%d bytes).\n", header_size);
        return 1;
    }

    int original_payload_size = total_packet_size - header_size;
    int max_payload_per_fragment = ((mtu - header_size) / 8) * 8;

    if (max_payload_per_fragment <= 0) {
        printf("Error: MTU is too small to carry even 8 bytes of fragment data.\n");
        return 1;
    }

    printf("\n--- Original Packet Parameters ---\n");
    printf("Total Size:       %d bytes\n", total_packet_size);
    printf("Header Size:      %d bytes\n", header_size);
    printf("Payload Data:     %d bytes\n", original_payload_size);
    printf("MTU:              %d bytes\n", mtu);
    printf("Max Payload/Frag: %d bytes (aligned to 8-byte boundary)\n", max_payload_per_fragment);

    Fragment fragments[MAX_FRAGMENTS];
    int fragment_count = 0;
    int bytes_remaining = original_payload_size;
    int current_byte_offset = 0;

    while (bytes_remaining > 0) {
        if (fragment_count >= MAX_FRAGMENTS) {
            printf("Error: Exceeded maximum allowed fragments.\n");
            return 1;
        }

        int current_payload = (bytes_remaining > max_payload_per_fragment) ? max_payload_per_fragment : bytes_remaining;
        int mf_flag = (bytes_remaining > max_payload_per_fragment) ? 1 : 0;

        fragments[fragment_count].fragment_index = fragment_count + 1;
        fragments[fragment_count].header_length = header_size;
        fragments[fragment_count].payload_length = current_payload;
        fragments[fragment_count].total_length = current_payload + header_size;
        fragments[fragment_count].offset = current_byte_offset / 8;
        fragments[fragment_count].more_fragments = mf_flag;

        current_byte_offset += current_payload;
        bytes_remaining -= current_payload;
        fragment_count++;
    }

    printf("\n--- Generated IPv4 Fragments (%d Fragments) ---\n", fragment_count);
    printf("%-8s %-12s %-14s %-14s %-10s %-8s\n",
           "Frag #", "Total Len", "Header Len", "Payload Len", "Offset", "MF Flag");
    printf("----------------------------------------------------------------------\n");

    for (int i = 0; i < fragment_count; i++) {
        printf("%-8d %-12d %-14d %-14d %-10d %-8d\n",
               fragments[i].fragment_index,
               fragments[i].total_length,
               fragments[i].header_length,
               fragments[i].payload_length,
               fragments[i].offset,
               fragments[i].more_fragments);
    }
    printf("----------------------------------------------------------------------\n");

    printf("\n--- Reassembly Simulation at Destination ---\n");
    int reassembled_payload = 0;
    bool reassembly_valid = true;
    int expected_offset = 0;

    for (int i = 0; i < fragment_count; i++) {
        printf("Received Fragment %d: Offset=%d (Byte %d), Payload=%d bytes, MF=%d\n",
               fragments[i].fragment_index, fragments[i].offset,
               fragments[i].offset * 8, fragments[i].payload_length, fragments[i].more_fragments);

        if (fragments[i].offset != expected_offset) {
            reassembly_valid = false;
        }

        reassembled_payload += fragments[i].payload_length;
        expected_offset += fragments[i].payload_length / 8;
    }

    int reassembled_total = reassembled_payload + header_size;
    printf("\nReassembled Payload Size: %d bytes\n", reassembled_payload);
    printf("Reassembled Total Size:   %d bytes\n", reassembled_total);

    if (reassembly_valid && reassembled_total == total_packet_size) {
        printf("Reassembly Status: SUCCESS! Packet reconstructed perfectly.\n");
    } else {
        printf("Reassembly Status: FAILED! Mismatch in reassembled size or offset.\n");
    }

    return 0;
}
