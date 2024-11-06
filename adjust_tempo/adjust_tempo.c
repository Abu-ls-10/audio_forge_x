#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HEADER_SIZE 44

void adjust_tempo(FILE *input, FILE *output, float tempo_factor) {
    if (tempo_factor <= 0) {
        fprintf(stderr, "Error: Tempo factor must be positive.\n");
        return;
    }

    // Read the WAV header
    unsigned char header[HEADER_SIZE];
    fread(header, sizeof(unsigned char), HEADER_SIZE, input);

    // Get original data size from header (Subchunk2Size)
    int data_size = *(int *)&header[40];
    short num_channels = *(short *)&header[22];
    short bits_per_sample = *(short *)&header[34];
    int sample_rate = *(int *)&header[24];
    int bytes_per_sample = bits_per_sample / 8 * num_channels;

    // Calculate new data size
    int new_data_size = (int)(data_size / tempo_factor);
    int new_num_samples = new_data_size / bytes_per_sample;

    // Adjust WAV header to reflect new data size and file size
    *(int *)&header[4] = new_data_size + HEADER_SIZE - 8; // ChunkSize
    *(int *)&header[40] = new_data_size; // Subchunk2Size

    // Write updated header to output
    fwrite(header, sizeof(unsigned char), HEADER_SIZE, output);

    // Buffer to store input samples
    unsigned char *buffer = malloc(data_size);
    fread(buffer, sizeof(unsigned char), data_size, input);

    // Write adjusted audio samples to output
    for (int i = 0; i < new_num_samples; i++) {
        int index = (int)(i * tempo_factor) * bytes_per_sample;
        if (index + bytes_per_sample <= data_size) {
            fwrite(&buffer[index], sizeof(unsigned char), bytes_per_sample, output);
        }
    }

    free(buffer);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s input.wav output.wav tempo_factor\n", argv[0]);
        return 1;
    }

    FILE *input = fopen(argv[1], "rb");
    if (input == NULL) {
        perror("Error opening input file");
        return 1;
    }

    FILE *output = fopen(argv[2], "wb");
    if (output == NULL) {
        perror("Error opening output file");
        fclose(input);
        return 1;
    }

    float tempo_factor = atof(argv[3]);
    adjust_tempo(input, output, tempo_factor);

    fclose(input);
    fclose(output);
    return 0;
}
