#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CHANNELS 10
#define MAX_DATA_LEN 100

int main(void) {
    int channel_count = 0;
    char channel_data[MAX_CHANNELS][MAX_DATA_LEN];
    int max_length = 0;

    printf("============================================================\n");
    printf("        Synchronous Time Division Multiplexing (TDM)        \n");
    printf("============================================================\n");

    printf("Enter number of input channels (1 to %d): ", MAX_CHANNELS);
    if (scanf("%d", &channel_count) != 1 || channel_count < 1 || channel_count > MAX_CHANNELS) {
        printf("Error: Invalid number of channels. Must be between 1 and %d.\n", MAX_CHANNELS);
        return 1;
    }

    for (int i = 0; i < channel_count; i++) {
        printf("Enter data for Channel %d: ", i + 1);
        if (scanf("%99s", channel_data[i]) != 1) {
            printf("Error reading data for Channel %d.\n", i + 1);
            return 1;
        }
        int len = strlen(channel_data[i]);
        if (len > max_length) {
            max_length = len;
        }
    }

    printf("\n--- Channel Summary ---\n");
    for (int i = 0; i < channel_count; i++) {
        printf("Channel %d Data: %s (Length: %lu)\n", i + 1, channel_data[i], (unsigned long)strlen(channel_data[i]));
    }
    printf("Total Frames Required: %d (Padding symbol '-' for idle slots)\n\n", max_length);

    printf("--- TDM Frame Allocation ---\n");
    printf("%-10s ", "Frame #");
    for (int i = 0; i < channel_count; i++) {
        printf("Slot(CH%d) ", i + 1);
    }
    printf("Combined Frame Payload\n");
    printf("----------------------------------------------------------------------\n");

    for (int frame_idx = 0; frame_idx < max_length; frame_idx++) {
        printf("%-10d ", frame_idx + 1);
        char frame_payload[MAX_CHANNELS + 1];
        int payload_idx = 0;

        for (int ch = 0; ch < channel_count; ch++) {
            char slot_char = '-';
            if (frame_idx < (int)strlen(channel_data[ch])) {
                slot_char = channel_data[ch][frame_idx];
            }
            printf("   %-8c", slot_char);
            frame_payload[payload_idx++] = slot_char;
        }
        frame_payload[payload_idx] = '\0';
        printf(" [%s]\n", frame_payload);
    }

    printf("----------------------------------------------------------------------\n");
    printf("Multiplexed Bit/Character Stream: ");
    for (int frame_idx = 0; frame_idx < max_length; frame_idx++) {
        for (int ch = 0; ch < channel_count; ch++) {
            char slot_char = '-';
            if (frame_idx < (int)strlen(channel_data[ch])) {
                slot_char = channel_data[ch][frame_idx];
            }
            printf("%c", slot_char);
        }
        if (frame_idx < max_length - 1) {
            printf(" | ");
        }
    }
    printf("\n");

    return 0;
}
