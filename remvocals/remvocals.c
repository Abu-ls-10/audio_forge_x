#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define HEADER_SIZE 44

// Function to check if the file has a WAV header
int isWavFile(const char *filename)
{
    FILE *file = fopen(filename, "rb");

    if (file == NULL)
    {
        perror("Error opening file");
        return 0; // Return false
    }

    // Read the first 44 bytes (WAV header)
    char header[44];
    fread(header, sizeof(char), sizeof(header), file);
    fclose(file);

    // Check if the header indicates a WAV file
    if (strncmp(header, "RIFF", 4) == 0 && strncmp(header + 8, "WAVE", 4) == 0)
    {
        // Additional checks can be added if necessary
        return 1; // Return true, the file is a WAV file
    }
    else
    {
        return 0; // Return false, the file is not a WAV file
    }
}

int main(int argc, char *argv[]) {
    FILE *src_file, *dest_file;
    short blend_sample, l_sample, r_sample;
    short wav_header[HEADER_SIZE];
    int err;

    // Check number of command-line arguments passed
    if (argc != 3) {
        fprintf(stderr, "Usage: %s src_file dest_file\n", argv[0]);
        return 1;
    }

    // Open source file
    src_file = fopen(argv[1], "rb");
    if (src_file == NULL) {
        fprintf(stderr, "Error: Unable to open source file\n");
        return 1;
    }

    // Open destination file
    dest_file = fopen(argv[2], "wb");
    if (dest_file == NULL) {
        fprintf(stderr, "Error: Unable to open destination file\n");
        return 1;
    }

    // Copy WAV header
    fread(wav_header, HEADER_SIZE, 1, src_file);
    err = fwrite(wav_header, HEADER_SIZE, 1, dest_file);
    if (err != 1) {
        fprintf(stderr, "Error: Could not write .WAV header to destination file\n");
        return 1;
    }

    while ((fread(&l_sample, sizeof(short), 1, src_file) == 1) &&
           (fread(&r_sample, sizeof(short), 1, src_file) == 1)) {

        blend_sample = (l_sample - r_sample) / 2;

        err = fwrite(&blend_sample, sizeof(short), 1, dest_file);
        if (err != 1) {
            fprintf(stderr, "Error: Unable to write blended sample to destination file\n");
            return 1;
        }
    }

    // Close source file
    err = fclose(src_file);
    if (err != 0) {
        fprintf(stderr, "Error: Unable to close source file\n");
        return 1;
    }

    // Close destination file
    err = fclose(dest_file);
    if (err != 0) {
        fprintf(stderr, "Error: Unable to close destination file\n");
        return 1;
    }

    // Exit program
    return 0;
}
