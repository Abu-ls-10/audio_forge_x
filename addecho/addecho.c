#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
// #include <unistd.h>

#define HEADER_SIZE 22

int main(int argc, char *argv[]) {
    FILE *src_file, *dest_file;
    int delay = 8000;
    int volume_scale = 4;
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
                long d = strtol(optarg, &endptr, 10);
                // Handle when delay value is too large
                if (d != delay){
                    if (d <=0){
                        fprintf(stderr, "Error: Invalid delay value %s. Delay must be a positive integer.\n", optarg);
                        return 1;
                    }
                    fprintf(stderr, "Error: Invalid delay scale value %s. Delay value is too large.\n", optarg);
                    return 1;
                }
                // Handle when delay <= 0
                if (d <= 0 || delay <= 0){
                    fprintf(stderr, "Error: Invalid delay value %s. Delay value must be a positive integer.\n", optarg);
                    return 1;
                }

                if (*endptr != '\0') {
                    fprintf(stderr, "Error: Invalid delay value %s.\n", optarg);
                    return 1;
                }
                break;

            case 'v':
                volume_scale = (int)strtol(optarg, &endptr, 10);
                long v = strtol(optarg, &endptr, 10);

                // Handle when volume-scale value is too large
                if (v != volume_scale){
                    if (v <= 0){
                        fprintf(stderr, "Error: Invalid volume scale value %s. volume_scale must be a positive integer.\n", optarg);
                        return 1;
                    }
                    fprintf(stderr, "Error: Invalid volume scale value %s. Value of Volume scale is too large.\n", optarg);
                    return 1;
                }

                // Handle when volume-scale <= 0
                if (volume_scale <= 0 || v <= 0){
                    fprintf(stderr, "Error: Invalid volume scale value %s. volume_scale must be a positive integer.\n", optarg);
                    return 1;
                }

                if (*endptr != '\0') {
                    fprintf(stderr, "Error: Invalid volume scale value %s\n", optarg);
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
    src_file = fopen(argv[argc-2], "rb");
    if (src_file == NULL) {
        fprintf(stderr, "Error: Unable to open source file\n");
        return 1;
    }

    // Open destination file
    dest_file = fopen(argv[argc-1], "wb");
    if (dest_file == NULL) {
        fprintf(stderr, "Error: Unable to open destination file\n");
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

    // Write header to source file
    fwrite(header, sizeof(short), HEADER_SIZE, dest_file);

    //
    short *echo_buffer = (short *) malloc(delay * sizeof(short));
    if (!echo_buffer) {
        fprintf(stderr, "Error: Memory allocation failed.");
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

    // Add 0-samples
    int x = delay - echo_i;
    int zero_sample = 0;
    int i = 0;
    for (; i < x; i++) {
        fwrite(&zero_sample, sizeof(short), 1, dest_file);
    }


    // Write remaining samples from echo buffer
    for (int j = (echo_i % delay); j < (delay-i); j++) {
        short sample = (short)(echo_buffer[j] / volume_scale);
        fwrite(&sample, sizeof(short), 1, dest_file);
    }

    for (int j = 0; j < (echo_i % delay); j++) {
        short sample = (short)(echo_buffer[j] / volume_scale);
        fwrite(&sample, sizeof(short), 1, dest_file);
    }

    free(echo_buffer);

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