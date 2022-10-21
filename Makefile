# Lines starting with # are comments

# Some variable definitions to save typing later on
CC = gcc
CONSERVATIVE_FLAGS = -std=c99 -Wall -Wextra -pedantic
DEBUGGING_FLAGS = -g -O0
CFLAGS = $(CONSERVATIVE_FLAGS) $(DEBUGGING_FLAGS)


# Links the project executable
project: project.o imageManip.o commandUtil.o ppmIO.o
	$(CC) -o project project.o imageManip.o commandUtil.o ppmIO.o

# Compiles project.c into an object file.
project.o: project.c commandUtil.c commandUtil.h
	$(CC) $(CFLAGS) -c project.c

# Compiles imageManip.c into an object file.
imageManip.o: imageManip.c imageManip.h ppmIO.c ppmIO.h
	$(CC) $(CFLAGS) -c imageManip.c ppmIO.c

# Compiles commandUtil.c into an object file.
commandUtil.o: commandUtil.c commandUtil.h ppmIO.c ppmIO.h
	$(CC) $(CFLAGS) -c commandUtil.c ppmIO.c

# Compiles ppmIO.c into an object file.
ppmIO.o: ppmIO.c ppmIO.h
	$(CC) $(CFLAGS) -c ppmIO.c

# 'make clean' will remove intermediate & executable files.
clean:
	rm -f *.o project *.gcov
