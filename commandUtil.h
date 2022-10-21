#ifndef COMMANDUTIL_H
#define COMMANDUTIL_H

int isInteger(char* testee);

int checkBounds(int image_rows, int image_cols, int x1, int y1, int x2, int y2);

int processArguments(int argc, char* argv[]);

#endif
