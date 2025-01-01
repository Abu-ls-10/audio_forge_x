#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#define HEADER_SIZE 22


int add_echo(const char *src_file_name, const char *dest_file_name, int delay, float volume_scale) {
    FILE *src_file, *dest_file;
    // int delay = 8000;
    // float volume_scale = 4.0f;
    int err;

    // Open source file
    src_file = fopen(src_file_name, "rb");
    if (src_file == NULL) {
        fprintf(stderr, "Error: Unable to open source file\n");
        return 1;
    }

    // Open destination file
    dest_file = fopen(dest_file_name, "wb");
    if (dest_file == NULL) {
        fprintf(stderr, "Error: Unable to open destination file\n");
        fclose(src_file);
        return 1;
    }

    // Read header from source file
    short header[HEADER_SIZE];
    fread(header, sizeof(short), HEADER_SIZE, src_file);

    // Update header
    unsigned int *head_sizeptr = (unsigned int *)(header + 2);
    *head_sizeptr += delay * 2;
    head_sizeptr = (unsigned int *)(header + 20);
    *head_sizeptr += delay * 2;

    // Write header to destination file
    fwrite(header, sizeof(short), HEADER_SIZE, dest_file);

    short *echo_buffer = (short *)malloc(delay * sizeof(short));
    if (!echo_buffer) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        fclose(src_file);
        fclose(dest_file);
        return 1;
    }

    int orig_sample;
    int mix_sample;
    int echo_i = 0;

    while (fread(&orig_sample, sizeof(short), 1, src_file) == 1) {
        if (echo_i < delay) {
            // Write original sample
            fwrite(&orig_sample, sizeof(short), 1, dest_file);
        } else {
            // Mix sample using delay and volume-scale parameters
            mix_sample = orig_sample + (short)(echo_buffer[echo_i % delay] / volume_scale);
            fwrite(&mix_sample, sizeof(short), 1, dest_file);
        }

        echo_buffer[echo_i % delay] = orig_sample;
        echo_i++;
    }

    // Add zero samples
    int zero_sample = 0;
    for (int i = 0; i < delay; i++) {
        fwrite(&zero_sample, sizeof(short), 1, dest_file);
    }

    free(echo_buffer);

    // Close files
    err = fclose(src_file);
    if (err != 0) {
        fprintf(stderr, "Error: Unable to close source file\n");
        return 1;
    }

    err = fclose(dest_file);
    if (err != 0) {
        fprintf(stderr, "Error: Unable to close destination file\n");
        return 1;
    }

    return 0;
}

int main(int argc, char *argv[]) {
    FILE *src_file, *dest_file;
    int delay = 8000;
    float volume_scale = 4.0f;
    int err;

    // Check if at least 3 command-line arguments were passed
    if (argc < 3) {
        fprintf(stderr, "Error: Source file or destination file not provided\n");
        return 1;
    }

    // Handle optional command-line arguments
    int opt;
    while ((opt = getopt(argc, argv, "d:v:")) != -1) {
        switch (opt) {
            char *endptr;

            case 'd':
                delay = (int)strtol(optarg, &endptr, 10);
                if (*endptr != '\0' || delay <= 0) {
                    fprintf(stderr, "Error: Invalid delay value '%s'. Delay must be a positive integer.\n", optarg);
                    return 1;
                }
                break;

            case 'v':
                volume_scale = strtof(optarg, &endptr);
                if (*endptr != '\0' || volume_scale <= 0.0f) {
                    fprintf(stderr, "Error: Invalid volume scale value '%s'. Volume scale must be a positive float.\n", optarg);
                    return 1;
                }
                break;

            default:
                // Handle incorrect optional inputs
                fprintf(stderr, "Usage: %s [-d delay] [-v volume_scale] sourcewav destwav\n", argv[0]);
                return 1;
        }
    }

    // Check for input and output filenames
    if (optind + 2 != argc) {
        fprintf(stderr, "Usage: %s [-d delay] [-v volume_scale] sourcewav destwav.\n", argv[0]);
        return 1;
    }

    // Open source file
    src_file = fopen(argv[argc - 2], "rb");
    if (src_file == NULL) {
        fprintf(stderr, "Error: Unable to open source file\n");
        return 1;
    }

    // Open destination file
    dest_file = fopen(argv[argc - 1], "wb");
    if (dest_file == NULL) {
        fprintf(stderr, "Error: Unable to open destination file\n");
        fclose(src_file);
        return 1;
    }

    // Read header from source file
    short header[HEADER_SIZE];
    fread(header, sizeof(short), HEADER_SIZE, src_file);

    // Update header
    unsigned int *head_sizeptr = (unsigned int *)(header + 2);
    *head_sizeptr += delay * 2;
    head_sizeptr = (unsigned int *)(header + 20);
    *head_sizeptr += delay * 2;

    // Write header to destination file
    fwrite(header, sizeof(short), HEADER_SIZE, dest_file);

    short *echo_buffer = (short *)malloc(delay * sizeof(short));
    if (!echo_buffer) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        fclose(src_file);
        fclose(dest_file);
        return 1;
    }

    int orig_sample;
    int mix_sample;
    int echo_i = 0;

    while (fread(&orig_sample, sizeof(short), 1, src_file) == 1) {
        if (echo_i < delay) {
            // Write original sample
            fwrite(&orig_sample, sizeof(short), 1, dest_file);
        } else {
            // Mix sample using delay and volume-scale parameters
            mix_sample = orig_sample + (short)(echo_buffer[echo_i % delay] / volume_scale);
            fwrite(&mix_sample, sizeof(short), 1, dest_file);
        }

        echo_buffer[echo_i % delay] = orig_sample;
        echo_i++;
    }

    // Add zero samples
    int zero_sample = 0;
    for (int i = 0; i < delay; i++) {
        fwrite(&zero_sample, sizeof(short), 1, dest_file);
    }

    free(echo_buffer);

    // Close files
    err = fclose(src_file);
    if (err != 0) {
        fprintf(stderr, "Error: Unable to close source file\n");
        return 1;
    }

    err = fclose(dest_file);
    if (err != 0) {
        fprintf(stderr, "Error: Unable to close destination file\n");
        return 1;
    }

    return 0;
}
