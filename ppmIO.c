//ppmIO.c
//601.220, Spring 2018
//Starter code for midterm project - feel free to edit/add to this file

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ppmIO.h"

/* read PPM formatted image from a file (assumes fp != NULL) */
void readPPM(FILE *fp, Image* user_image) {

  //TODO: fill in this definition
  char buffer[100];
  char fileType[2];

  //Check that PPM file is P6 format
  fgets(buffer, 100, fp);
  sscanf(buffer, "%s", fileType);
    if (strcmp(fileType, "P6") != 0) {
    printf("PPMIO error: File type is not P6.");
    }

  //Advance buffer past comment lines beginning with a hash.
  fgets(buffer, 100, fp);
  while (buffer[0] == '#') {
    fgets(buffer, 100, fp);
  }	

  //Read in values for number of rows and columns
  sscanf(buffer, "%d %d", &user_image->cols, &user_image->rows);   
  fgets(buffer, 100, fp);
  while (buffer[0] == '#') {
    fgets(buffer, 100, fp);
  }
  int colors;
  sscanf(buffer, "%d", &colors);

  //Fill image struct with data
  user_image->data = malloc(sizeof(Pixel)* user_image->rows * user_image->cols);
  fread(user_image->data, sizeof(Pixel), user_image->rows * user_image->cols, fp);
  fclose(fp);
}

/* write PPM formatted image to a file (assumes fp != NULL and img != NULL) */
int writePPM(FILE *fp, const Image* user_image) {
    
  /* abort if either file pointer is dead or image pointer is null; indicate failure with -1 */
  if (!fp || !user_image) {
    return -1;
  }

  /* write tag and dimensions; colors is always 255 */
  fprintf(fp, "P6\n%d %d\n%d\n", user_image->cols, user_image->rows, 255);

  /* write pixels */
  int num_pixels_written = (int) fwrite(user_image->data, sizeof(Pixel), (user_image->rows) * (user_image->cols), fp);

  /* check if write was successful or not; indicate failure with -1 */
  if (num_pixels_written != (user_image->rows) * (user_image->cols)) {
    return -1;
  }
  
  fclose(fp);
  /* success, so return number of pixels written */
  return num_pixels_written;
}
