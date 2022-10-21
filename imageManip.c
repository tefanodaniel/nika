#include "ppmIO.h"
#include <stdlib.h>
#include <assert.h>

void swap(Image* image) {
    
    unsigned char temp;
    for (int i = 0; i < (image->rows * image->cols); i++) {
        temp = image->data[i].r;
        image->data[i].r = image->data[i].g;
        image->data[i].g = image->data[i].b;
        image->data[i].b = temp;
    }
}

void grayscale(Image* image) {

    int i = 0;
    double NTSC_red = 0.3;
    double NTSC_green = 0.59;
    double NTSC_blue = 0.11;
    for ( i = 0; i < (image->rows * image->cols); i++) {
        double result_r = (double)image->data[i].r * NTSC_red;
        double result_g = (double)image->data[i].g * NTSC_green;
        double result_b = (double)image->data[i].b * NTSC_blue;
        double total_result = result_r + result_b + result_g;
        //int rounded_result = (total_result >= 0) ? (int)(total_result + 0.5) : (int)(total_result - 0.5);
        //int rounded_result = (int) total_result;
        image->data[i].r = (unsigned char)total_result;
        image->data[i].g = (unsigned char)total_result;
        image->data[i].b = (unsigned char)total_result;
    }
}

void blackout(Image* image) {

    for (int cur_row = 0; cur_row < image->rows / 2; cur_row++) {
        for (int cur_col = image->cols / 2; cur_col < image->cols; cur_col++) {
            image->data[(cur_row * image->cols) + cur_col].r = 0;
            image->data[(cur_row * image->cols) + cur_col].g = 0;
            image->data[(cur_row * image->cols) + cur_col].b = 0;
        }
    } 
}
unsigned char max(double num) {
    if(num > 255) {
        num = 255;
    }
    if (num < 0) {
        num = 0;
    }
    return num;
}

void contrast(Image* image, double amt){
    for (int i = 0; i < (image->rows * image->cols); i++) {
        Pixel *t = &(image->data[i]);
        double cr = (double)((*t).r);
        double cg = (double)((*t).g);
        double cb = (double)((*t).b);

        cr = (cr/255) - 0.5;
        cg = (cg/255) - 0.5;
        cb = (cb/255) - 0.5;


        cr = cr * amt;
        cg = cg * amt;
        cb = cb * amt;

        cr = (cr + 0.5)*255.0;
        cg = (cg + 0.5)*255.0;
        cb = (cb + 0.5)*255.0;
    
        ((*t).r) = max(cr);
        ((*t).g) = max(cg);
        ((*t).b) = max(cb);
  }
}

Image* crop(Image *image, int x1, int y1, int x2, int y2) {

    int startCol = 0;
    int startRow = 0;
    int endCol = 0;
    int endRow = 0;
    int cropped_cols;
    int cropped_rows;
    if (x2 > x1) {
        cropped_cols = x2 - x1;
        startCol = x1;
        endCol = x2;
    } else if (x1 > x2) {
        cropped_cols = x1 - x2;
        startCol = x2;
        endRow = x1;
    }
    if (y2 > y1) {
        cropped_rows = y2 - y1;
        startRow = y1;
        endRow = y2;
    } else if (y1 > y2) {
        cropped_rows = y1 - y2;
        startRow = y2;
        endRow = y1;
    }
    Image* cropped_image = malloc(sizeof(Image));
    cropped_image->data = malloc(sizeof(Pixel) * cropped_rows * cropped_cols);
    cropped_image->rows = cropped_rows;
    cropped_image->cols = cropped_cols;
    int i = 0;
    for (int r = startRow; r < endRow; r++) {
        for (int c = startCol; c < endCol; c++) {
            cropped_image->data[i] = image->data[(r * image->cols) + c];
            i++;
        }
    }
    return cropped_image;
}
