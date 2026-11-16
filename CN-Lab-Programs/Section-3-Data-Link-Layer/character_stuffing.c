#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void stuff_characters(const char *data, char flag_char, char esc_char, char *stuffed_frame) {
    int write_index = 0;
    stuffed_frame[write_index++] = flag_char;

    for (int i = 0; data[i] != '\0'; i++) {
        if (data[i] == flag_char || data[i] == esc_char) {
            stuffed_frame[write_index++] = esc_char;
        }
        stuffed_frame[write_index++] = data[i];
    }

    stuffed_frame[write_index++] = flag_char;
    stuffed_frame[write_index] = '\0';
}

bool destuff_characters(const char *stuffed_frame, char flag_char, char esc_char, char *destuffed_data) {
    int length = strlen(stuffed_frame);
    if (length < 2 || stuffed_frame[0] != flag_char || stuffed_frame[length - 1] != flag_char) {
        return false;
    }

    int write_index = 0;
    for (int i = 1; i < length - 1; i++) {
        if (stuffed_frame[i] == esc_char) {
            i++;
            if (i >= length - 1) {
                return false;
            }
            destuffed_data[write_index++] = stuffed_frame[i];
        } else {
            destuffed_data[write_index++] = stuffed_frame[i];
        }
    }
    destuffed_data[write_index] = '\0';
    return true;
}

int main(void) {
    char original_data[256];
    char flag_char;
    char esc_char;
    char stuffed_frame[1024];
    char destuffed_data[256];

    printf("============================================================\n");
    printf("        Character (Byte) Stuffing and Destuffing            \n");
    printf("============================================================\n");

    printf("Enter Flag character (e.g. F): ");
    if (scanf(" %c", &flag_char) != 1) {
        printf("Error reading flag character.\n");
        return 1;
    }

    printf("Enter Escape character (e.g. E): ");
    if (scanf(" %c", &esc_char) != 1) {
        printf("Error reading escape character.\n");
        return 1;
    }

    if (flag_char == esc_char) {
        printf("Error: Flag and Escape characters must be distinct.\n");
        return 1;
    }

    printf("Enter payload data string: ");
    if (scanf("%255s", original_data) != 1) {
        printf("Error reading payload data.\n");
        return 1;
    }

    stuff_characters(original_data, flag_char, esc_char, stuffed_frame);

    bool destuff_status = destuff_characters(stuffed_frame, flag_char, esc_char, destuffed_data);

    printf("\n--- Results ---\n");
    printf("Original Data:   %s\n", original_data);
    printf("Flag Character:  '%c'\n", flag_char);
    printf("ESC Character:   '%c'\n", esc_char);
    printf("Stuffed Frame:   %s\n", stuffed_frame);

    if (destuff_status) {
        printf("Destuffed Data:  %s\n", destuffed_data);
        if (strcmp(original_data, destuffed_data) == 0) {
            printf("Verification:    Success (Destuffed data matches original perfectly)\n");
        } else {
            printf("Verification:    Mismatch detected!\n");
        }
    } else {
        printf("Error during destuffing frame framing.\n");
    }

    return 0;
}
