#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HEADER_SIZE 44

int shift_pitch(const char *src_file_name, const char *dest_file_name, float pitch_factor) {
    FILE *src_file, *dest_file;

    FILE *input = fopen(src_file_name, "rb");
    if (input == NULL) {
        perror("Error opening input file");
        return 1;
    }

    FILE *output = fopen(dest_file_name, "wb");
    if (output == NULL) {
        perror("Error opening output file");
        fclose(input);
        return 1;
    }

    if (pitch_factor <= 0) {
        fprintf(stderr, "Error: Pitch factor must be positive.\n");
        return 0;
    }

    // Read the WAV header
    unsigned char header[HEADER_SIZE];
    fread(header, sizeof(unsigned char), HEADER_SIZE, input);

    // Adjust sample rate in the header
    int sample_rate = *(int *)&header[24];
    int new_sample_rate = (int)(sample_rate * pitch_factor);
    *(int *)&header[24] = new_sample_rate;
    *(int *)&header[28] = new_sample_rate * (*(short *)&header[32]);

    // Write modified header to output
    fwrite(header, sizeof(unsigned char), HEADER_SIZE, output);

    // Copy audio data directly (same duration, adjusted pitch)
    unsigned char buffer[1024];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, sizeof(unsigned char), sizeof(buffer), input)) > 0) {
        fwrite(buffer, sizeof(unsigned char), bytesRead, output);
    }

    fclose(input);
    fclose(output);

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s input.wav output.wav pitch_factor\n", argv[0]);
        return 1;
    }

    float pitch_factor = atof(argv[3]);
    shift_pitch(argv[1], argv[2], pitch_factor);
    return 0;
}
