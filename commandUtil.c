#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "ppmIO.h"
#include "imageManip.h"

int isInteger(char* testee) {

    char* temp;
    strtol(testee, &temp, 10);
    return *temp == 0;
}

int checkBounds(int image_rows, int image_cols, int x1, int y1, int x2, int y2) {
    if ((x1 < 0 || x2 < 0 || y1 < 0 || y2 < 0) ||
           (x1 > image_cols || x2 > image_cols ||
            y1 > image_rows || y2 > image_rows)) {
        return 0;
    }
    return 1;
}

int processArguments(int argc, char* argv[]) {
    
    char* infile;
    char* outfile;
    // Check that user entered minimum amount of arguments.
    if (argc < 3) {
        printf("Input and/or output filenames missing.\n");
        return 1;
    } else {
        infile = argv[1];
        outfile = argv[2];
    }

    // Check that user inputted valid filenames.
    FILE* ifp = fopen(infile, "rb");
    if (ifp == NULL) {
        printf("Specified input file could not be found.\n");
        fclose(ifp);
        return 2;
    }
    FILE* ofp = fopen(outfile, "wb");
    if (ofp == NULL) {
        printf("Specified output file could not be opened for writing.\n");
        fclose(ofp);
        return 4;
    }
    
    // Check that operation was specified.
    if (argc == 3) {
        printf("No operation specified.\n");
        fclose(ifp);
        fclose(ofp);
        return 5;
    }

    // Generate Image* from user file.
    
    Image* user_image = malloc(sizeof(Image));
    readPPM(ifp, user_image);

    // Determine what operation was called.
    // List of arguments.
    //       0         1             2            3    4   5
    // ./project.c nika.ppm nika-blackout.ppm blackout 30 100
    char* operation = argv[3];
    for(int i = 0; operation[i]; i++){
        operation[i] = tolower(operation[i]);
    }
    if (strcmp(operation, "swap") == 0) {
        if (argc != 4) {
            printf("Incorrect number of arguments for specified operation.\n");
            free(user_image->data);
            free(user_image);
            return 6;
        } else {
            swap(user_image);
        }
    } else if (strcmp(operation, "blackout") == 0) {
        if (argc != 4) {
            printf("Incorrect number of arguments for specified operation.\n");
            free(user_image->data);
            free(user_image);
            return 6;
        } else {
            blackout(user_image);
        }
    } else if (strcmp(operation, "crop") == 0) {
        if (argc != 8) {
            printf("Incorrect number of arguments for specified operation.\n");
            free(user_image->data);
            free(user_image);
            return 6; 
        } else {
            for (int i = 4; i < 8; i++) {
                if(!isInteger(argv[i])) {        
                    printf("Invalid argument(s) for specified operation.\n");
                    free(user_image->data);
                    free(user_image);
                    return 6;
                }
            }
            int x1 = atoi(argv[4]);
            int y1 = atoi(argv[5]);
            int x2 = atoi(argv[6]);
            int y2 = atoi(argv[7]);
            if (!checkBounds(user_image->rows, user_image->cols, x1, y1, x2, y2)) {
                printf("Crop parameters out-of-range for specified image.\n");
                    free(user_image->data);
                    free(user_image);
                    return 7;
            }
            Image* cropped_image = crop(user_image, x1, y1, x2, y2);
            writePPM(ofp, cropped_image);
            free(cropped_image->data);
            free(cropped_image);
            free(user_image->data);
            free(user_image);
            return 0;
        }
    } else if (strcmp(operation, "grayscale") == 0) {
        if (argc != 4) {
            printf("Incorrect number of arguments for specified operation.\n");
            free(user_image->data);
            free(user_image);
            return 6;
        } else {
            grayscale(user_image);
        }
    } else if (strcmp(operation, "contrast") == 0) {
        if (argc != 5) {
            printf("Incorrect number of arguments for specified operations.\n");
            free(user_image->data);
            free(user_image);
            return 6;
        } else {
            // Check that value entered is a valid double.
            double amount = atof(argv[4]);
            if (amount == 0.0) {
                printf("Invalid value entered for contrast operation.\n");
                return 6;
            }
            contrast(user_image, amount);
        }
    } else {
        printf("Invalid operation selected.\n");
        free(user_image->data);
        free(user_image);
        return 5;
    }
    writePPM(ofp, user_image);
    free(user_image->data);
    free(user_image);
    return 0;
}
