#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>
#include <curses.h>
#include "method.h"

void set_struct();

double data[DAYS * 4 + DAYS2][NUMDATA];
double avedata[60][NUMDATA];
Climate* firstMonth;
Climate* nowMonth;

int main()
{
	int key;

	char section[] = "section1";
	char keyword[] = "keyword1";
	char* filename = getini(section, keyword);
	CSVArray(filename, data);

	Averagedata(data, avedata);
	set_struct();

	write_file(firstMonth);

	nowMonth = firstMonth;
	int count = 0;
	while (count < 12) {
		for (int i = 0; i < 5; i++) {
			fprintf_s(stdout, "%d年%d月 %lf, %lf, %lf\n", 2018 + i, nowMonth->num, nowMonth->max[i], nowMonth->min[i], nowMonth->rain[i]);
		}
		printf("\n");
		nowMonth = nowMonth->nextMonth;
		count++;
	}

	initscr();

	noecho();
	cbreak();
	keypad(stdscr, TRUE);

	nowMonth = firstMonth;
	while(true) {

		draw_graph(nowMonth);

		key = getch();
		if (key == KEY_RIGHT) {
			nowMonth = nowMonth->nextMonth;
		} 
		else if (key == KEY_LEFT) {
			break;
		}
	}
	endwin();
}

void set_struct() {
	Climate* prevMonth = NULL;
	for (int i = 0; i < 12; i++) {
		Climate* tmp = new Climate();
		int index = i;

		tmp->num = i + 1;
		for (int j = 0; j < 5; j++) {
			tmp->max[j] = avedata[index][0];
			tmp->min[j] = avedata[index][1];
			tmp->rain[j] = avedata[index][2];
			index += 12;
		}
		tmp->nextMonth = NULL;

		if (i == 0) {
			firstMonth = tmp;
		}
		else {
			prevMonth->nextMonth = tmp;
		}
		if (i == 11) {	// 12月の構造体と1月の構造体をつなぐ
			tmp->nextMonth = firstMonth;
		}
		prevMonth = tmp;
	}
}