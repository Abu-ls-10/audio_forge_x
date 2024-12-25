#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HEADER_SIZE 44

void adjust_tempo(const char *input_filename, const char *output_filename, float tempo_factor) {
    if (tempo_factor <= 0) {
        fprintf(stderr, "Error: Tempo factor must be positive.\n");
        return;
    }

    FILE *input = fopen(input_filename, "rb");
    if (input == NULL) {
        perror("Error opening input file");
        return;
    }

    FILE *output = fopen(output_filename, "wb");
    if (output == NULL) {
        perror("Error opening output file");
        fclose(input);
        return;
    }

    // Read and copy header from input to output
    unsigned char header[HEADER_SIZE];
    fread(header, sizeof(unsigned char), HEADER_SIZE, input);

    // Adjust sample rate in the header based on the tempo factor
    int sample_rate = *(int *)(header + 24);
    int new_sample_rate = (int)(sample_rate * tempo_factor);
    *(int *)(header + 24) = new_sample_rate;
    *(int *)(header + 28) = new_sample_rate * (*(short *)(header + 32)); // Byte rate

    // Write adjusted header to output
    fwrite(header, sizeof(unsigned char), HEADER_SIZE, output);

    // Copy audio data from input to output
    unsigned char buffer[4096];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, sizeof(unsigned char), sizeof(buffer), input)) > 0) {
        fwrite(buffer, sizeof(unsigned char), bytesRead, output);
    }

    fclose(input);
    fclose(output);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s input.wav output.wav tempo_factor\n", argv[0]);
        return 1;
    }

    float tempo_factor = atof(argv[3]);
    adjust_tempo(argv[1], argv[2], tempo_factor);

    printf("Tempo adjustment complete.\n");
    return 0;
}
