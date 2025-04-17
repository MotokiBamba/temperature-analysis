#pragma once
#define CHARBUFF 124
#define BUFFSIZE 1024
#define DAYS 365
#define DAYS2 366
#define NUMDATA 3

struct Climate {
	int num;
	double max[5];
	double min[5];
	double rain[5];
	Climate* nextMonth;
};

void getGurrentDirectory(char* currentDirectory);
char* getini(char* sec, char* key);
void CSVArray(const char* fileName, double data[DAYS * 4 + DAYS2][NUMDATA]);
void Averagedata(double data[DAYS * 4 + DAYS2][NUMDATA], double avedata[60][NUMDATA]);
void draw_graph(Climate* nowMonth);
void write_file(Climate* nowMonth);