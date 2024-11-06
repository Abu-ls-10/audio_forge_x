#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define HEADER_SIZE 44

// Read and write WAV header
void read_wav_header(FILE *file, uint8_t *header) {
    fread(header, sizeof(uint8_t), HEADER_SIZE, file);
}

void write_wav_header(FILE *file, uint8_t *header) {
    fwrite(header, sizeof(uint8_t), HEADER_SIZE, file);
}

// Adjust pitch by resampling
void shift_pitch(FILE *input, FILE *output, float pitch_factor) {
    int16_t sample;
    int sample_count = 0;
    while (fread(&sample, sizeof(int16_t), 1, input) == 1) {
        if ((sample_count++ % (int)(1 / pitch_factor)) == 0) {
            fwrite(&sample, sizeof(int16_t), 1, output);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Usage: %s <input.wav> <output.wav> <pitch_factor>\n", argv[0]);
        return 1;
    }

    FILE *input = fopen(argv[1], "rb");
    FILE *output = fopen(argv[2], "wb");
    float pitch_factor = atof(argv[3]);

    uint8_t header[HEADER_SIZE];
    read_wav_header(input, header);
    write_wav_header(output, header);

    shift_pitch(input, output, pitch_factor);

    fclose(input);
    fclose(output);

    printf("Pitch shifted with factor %.2f\n", pitch_factor);
    return 0;
}
