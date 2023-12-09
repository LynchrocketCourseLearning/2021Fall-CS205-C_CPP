#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>
using namespace std;

int getRow(const string filename);
int getCol(const string filename);
void inputdo(double *matrix, int row, int col, const string filename);
void outputdo(double *matrix,int row,int col,const string filename);
void inputfl(float *matrix, int row, int col, const string filename);
void outputfl(float *matrix,int row,int col,const string filename);
