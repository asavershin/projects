//Header file with paring functions

#ifndef CheckFunc_hpp
#define CheckFunc_hpp
#include <iostream>

bool yearCheck(const int Y);
bool dateCheck(const char date[],char error[]);

bool fileProcessing(char args[], int ArgsCount, char error[], int Max);

bool checkNum(const char args[], char*& pointer, int& arg);
bool checkNum(const char args[], int Max, int& arg);

int parsing(char args[], int& End);
bool parsingForAdd(char args[], int Max, int& num1, int& num2, int& num3, int& num4, char*& Beg, char*& End, char error[]);

#endif
