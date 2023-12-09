//IO.h
#ifndef _IO_H
#define _IO_H

#include "matrix.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <sys/mman.h>
//#include <fcntl.h>

void valid_file(FILE *, const char *);

void close_file(FILE *);

size_t get_rows(FILE *);

size_t get_cols(FILE *);

void mat_init(FILE *, size_t, size_t, matp);

void mat_out_file(FILE *, matp);

//void map_read(const char *, matp);
//
//void map_write(const char *, matp);

#endif //_IO_H
