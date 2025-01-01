#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define HEADER_SIZE 44

// Check if the file is a valid WAV file
int isWavFile(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        return 0;
    }

    char header[HEADER_SIZE];
    fread(header, sizeof(char), HEADER_SIZE, file);
    fclose(file);

    if (strncmp(header, "RIFF", 4) == 0 && strncmp(header + 8, "WAVE", 4) == 0) {
        return 1; // Valid WAV file
    }
    return 0; // Not a WAV file
}

int remove_vocals(const char *src_file_name, const char *dest_file_name)
{
    FILE *src_file, *dest_file;
    short l_sample, r_sample;
    short blend_sample;
    unsigned char wav_header[HEADER_SIZE];
    size_t read_count;

    // Open source file
    src_file = fopen(src_file_name, "rb");
    if (src_file == NULL)
    {
        fprintf(stderr, "Error: Unable to open source file\n");
        return 1;
    }

    // Open destination file
    dest_file = fopen(dest_file_name, "wb");
    if (dest_file == NULL)
    {
        fprintf(stderr, "Error: Unable to open destination file\n");
        fclose(src_file);
        return 1;
    }

    // Read and copy WAV header
    if (fread(wav_header, 1, HEADER_SIZE, src_file) != HEADER_SIZE)
    {
        fprintf(stderr, "Error: Unable to read WAV header\n");
        fclose(src_file);
        fclose(dest_file);
        return 1;
    }

    // Write unchanged WAV header to the destination file
    if (fwrite(wav_header, 1, HEADER_SIZE, dest_file) != HEADER_SIZE)
    {
        fprintf(stderr, "Error: Unable to write WAV header\n");
        fclose(src_file);
        fclose(dest_file);
        return 1;
    }

    // Process audio data
    while ((read_count = fread(&l_sample, sizeof(short), 1, src_file)) == 1 &&
           fread(&r_sample, sizeof(short), 1, src_file) == 1)
    {
        // Compute the blended sample
        blend_sample = (short)((l_sample - r_sample) / 2);

        // Write the blended sample to both left and right channels
        if (fwrite(&blend_sample, sizeof(short), 1, dest_file) != 1 ||
            fwrite(&blend_sample, sizeof(short), 1, dest_file) != 1)
        {
            fprintf(stderr, "Error: Unable to write stereo frame\n");
            fclose(src_file);
            fclose(dest_file);
            return 1;
        }
    }

    if (ferror(src_file))
    {
        fprintf(stderr, "Error: Reading source file failed\n");
        fclose(src_file);
        fclose(dest_file);
        return 1;
    }

    // Close files
    fclose(src_file);
    fclose(dest_file);

    return 0; // Success
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

    remove_vocals(argv[1], argv[2]);
    
    // Exit program
    return 0;
}
