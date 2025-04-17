#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <Windows.h>
#include <curses.h>
#include "method.h"

void getGurrentDirectory(char* currentDirectory) {
	GetCurrentDirectory(CHARBUFF, currentDirectory);
}

char* getini(char* sec, char* key) {
	char currentDirectory[CHARBUFF];
	char section[CHARBUFF];
	char keyWord[CHARBUFF];
	char settingFile[CHARBUFF];
	char keyValue[CHARBUFF];

	getGurrentDirectory(currentDirectory);
	sprintf_s(section, sec);
	sprintf_s(keyWord, key);
	sprintf_s(settingFile, "%s\\data.ini", currentDirectory);
	GetPrivateProfileString(section, keyWord, "none", keyValue, CHARBUFF, settingFile);

	return keyValue;
}

void CSVArray(const char* fileName, double data[DAYS * 4 + DAYS2][NUMDATA]) {
	FILE* fp;
	char s[BUFFSIZE];
	errno_t error;
	char* p1;
	char delim[] = ", ";
	char* ctx;
	double tmp;
	int count = 1;
	int i = 0;

	error = fopen_s(&fp, fileName, "r");

	if (error != 0)
		fprintf_s(stderr, "failed to open");
	else {
		while (fgets(s, BUFFSIZE, fp) != NULL) {
			int index = 0;
			if (count >= 8) {	// 1～7行目の文字列を無視する
				p1 = strtok_s(s, delim, &ctx);
				int count2 = 1;
				int index = 0;
				while (p1 != NULL) {
					if (count2 == 2 || count2 == 5 || count2 == 8) {	// 2、5、8列目以外を無視する
						tmp = atof(p1);
						data[i][index++] = tmp;
					}
					p1 = strtok_s(NULL, delim, &ctx);
					count2++;
				}
				i++;
			}
			count++;
		}
		fclose(fp);
	}
}

void Averagedata(double data[DAYS * 4 + DAYS2][NUMDATA], double avedata[60][NUMDATA]) {
	int mi[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int index, index2;

	for (int year = 2018; year <= 2022; year++) {
		double sum[12][3] = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
		if (year == 2018) {
			index = 0;
			index2 = 0;
			mi[1] = 28;
		}
		else if (year == 2019) {
			index = 365;
			index2 = 12;
			mi[1] = 28;
		}
		else if (year == 2020) {
			index = 730;
			index2 = 24;
			mi[1] = 29;
		}
		else if (year == 2021) {
			index = 1096;
			index2 = 36;
			mi[1] = 28;
		}
		else if (year == 2022) {
			index = 1461;
			index2 = 48;
			mi[1] = 28;
		}

		// 1月の最高気温・最低気温・降水量の合計を計算
		for (int i = index; i < (index + mi[0]); i++) {
			sum[0][0] += data[i][0];
			sum[0][1] += data[i][1];
			sum[0][2] += data[i][2];
		}

		// 2月の最高気温・最低気温・降水量の合計を計算
		for (int i = (index + mi[0]); i < (index + mi[0] + mi[1]); i++) {
			sum[1][0] += data[i][0];
			sum[1][1] += data[i][1];
			sum[1][2] += data[i][2];
		}

		// 3月の最高気温・最低気温・降水量の合計を計算
		for (int i = (index + mi[0] + mi[1]); i < (index + mi[0] + mi[1] + mi[2]); i++) {
			sum[2][0] += data[i][0];
			sum[2][1] += data[i][1];
			sum[2][2] += data[i][2];
		}

		// 4月の最高気温・最低気温・降水量の合計を計算
		for (int i = (index + mi[0] + mi[1] + mi[2]); i < (index + mi[0] + mi[1] + mi[2] + mi[3]); i++) {
			sum[3][0] += data[i][0];
			sum[3][1] += data[i][1];
			sum[3][2] += data[i][2];
		}

		// 5月の最高気温・最低気温・降水量の合計を計算
		for (int i = (index + mi[0] + mi[1] + mi[2] + mi[3]); i < (index + mi[0] + mi[1] + mi[2] + mi[3] + mi[4]); i++) {
			sum[4][0] += data[i][0];
			sum[4][1] += data[i][1];
			sum[4][2] += data[i][2];
		}

		// 6月の最高気温・最低気温・降水量の合計を計算
		for (int i = (index + mi[0] + mi[1] + mi[2] + mi[3] + mi[4]); i < (index + mi[0] + mi[1] + mi[2] + mi[3] + mi[4] + mi[5]); i++) {
			sum[5][0] += data[i][0];
			sum[5][1] += data[i][1];
			sum[5][2] += data[i][2];
		}

		// 7月の最高気温・最低気温・降水量の合計を計算
		for (int i = (index + mi[0] + mi[1] + mi[2] + mi[3] + mi[4] + mi[5]); i < (index + mi[0] + mi[1] + mi[2] + mi[3] + mi[4] + mi[5] + mi[6]); i++) {
			sum[6][0] += data[i][0];
			sum[6][1] += data[i][1];
			sum[6][2] += data[i][2];
		}

		// 8月の最高気温・最低気温・降水量の合計を計算
		for (int i = (index + mi[0] + mi[1] + mi[2] + mi[3] + mi[4] + mi[5] + mi[6]); i < (index + mi[0] + mi[1] + mi[2] + mi[3] + mi[4] + mi[5] + mi[6] + mi[7]); i++) {
			sum[7][0] += data[i][0];
			sum[7][1] += data[i][1];
			sum[7][2] += data[i][2];
		}

		// 9月の最高気温・最低気温・降水量の合計を計算
		for (int i = (index + mi[0] + mi[1] + mi[2] + mi[3] + mi[4] + mi[5] + mi[6] + mi[7]); i < (index + mi[0] + mi[1] + mi[2] + mi[3] + mi[4] + mi[5] + mi[6] + mi[7] + mi[8]); i++) {
			sum[8][0] += data[i][0];
			sum[8][1] += data[i][1];
			sum[8][2] += data[i][2];
		}

		// 10月の最高気温・最低気温・降水量の合計を計算
		for (int i = (index + mi[0] + mi[1] + mi[2] + mi[3] + mi[4] + mi[5] + mi[6] + mi[7] + mi[8]); i < (index + mi[0] + mi[1] + mi[2] + mi[3] + mi[4] + mi[5] + mi[6] + mi[7] + mi[8] + mi[9]); i++) {
			sum[9][0] += data[i][0];
			sum[9][1] += data[i][1];
			sum[9][2] += data[i][2];
		}

		// 11月の最高気温・最低気温・降水量の合計を計算
		for (int i = (index + mi[0] + mi[1] + mi[2] + mi[3] + mi[4] + mi[5] + mi[6] + mi[7] + mi[8] + mi[9]); i < (index + mi[0] + mi[1] + mi[2] + mi[3] + mi[4] + mi[5] + mi[6] + mi[7] + mi[8] + mi[9] + mi[10]); i++) {
			sum[10][0] += data[i][0];
			sum[10][1] += data[i][1];
			sum[10][2] += data[i][2];
		}

		// 12月の最高気温・最低気温・降水量の合計を計算
		for (int i = (index + mi[0] + mi[1] + mi[2] + mi[3] + mi[4] + mi[5] + mi[6] + mi[7] + mi[8] + mi[9] + mi[10]); i < (index + mi[0] + mi[1] + mi[2] + mi[3] + mi[4] + mi[5] + mi[6] + mi[7] + mi[8] + mi[9] + mi[10] + mi[11]); i++) {
			sum[11][0] += data[i][0];
			sum[11][1] += data[i][1];
			sum[11][2] += data[i][2];
		}

		// 最高気温・最低気温・降水量の平均を求め配列に格納
		for (int i = 0; i < 12; i++) {
			avedata[index2][0] = sum[i][0] / mi[i];
			avedata[index2][1] = sum[i][1] / mi[i];
			avedata[index2][2] = sum[i][2] / mi[i];
			index2++;
		}
	}
}

void draw_graph(Climate* nowMonth) {
	int xmin = 6;
	int xmax = 112;
	int ymin = 3;
	int ymax = 23;

	start_color();
	init_pair(1, COLOR_RED, COLOR_RED);
	init_pair(2, COLOR_GREEN, COLOR_GREEN);
	init_pair(3, COLOR_CYAN, COLOR_CYAN);
	init_pair(4, COLOR_WHITE, COLOR_BLACK);

	erase();

	// グラフ枠の生成
	for (int i = ymin; i <= ymax; i++) {
		mvaddstr(i, xmin, "|");
		mvaddstr(i, xmax, "|");
	}

	for (int i = xmin; i <= xmax; i++) {
		mvaddstr(ymin, i, "-");
		mvaddstr(ymax, i, "-");
	}

	// グラフのxラベル
	for (int i = 1; i <= 5; i++) {
		mvprintw(ymax + 1, xmin + i * 17, "%d年", i + 2017);
	}

	// グラフのyラベル
	for (int i = 1; i <= 4; i++) {
		mvprintw(ymax - i * 5, xmin - 2, "%d", i * 10);
	}

	// 平均最高気温の描画
	for (int i = 1; i <= 5; i++) {
		int x = xmin + i * 17;
		int y = ymax - (int)round(nowMonth->max[i - 1]) / 2;
		if (y == ymax) {
			y = 22;
		}
		while (y < ymax) {
			attrset(COLOR_PAIR(1));
			mvaddstr(y, x, " ");
			mvaddstr(y, x + 1, " ");
			y++;
		}
	}

	// 平均最低気温の描画
	for (int i = 1; i <= 5; i++) {
		int x = xmin + i * 17;
		int y = ymax - (int)round(nowMonth->min[i - 1]) / 2;
		if (y == ymax) {
			y = 22;
		}
		while (y < ymax) {
			attrset(COLOR_PAIR(2));
			mvaddstr(y, x + 2, " ");
			mvaddstr(y, x + 3, " ");
			y++;
		}
	}

	// 平均降水量の描画
	for (int i = 1; i <= 5; i++) {
		int x = xmin + i * 17;
		int y = ymax - (int)round(nowMonth->rain[i - 1]) / 2;
		if (y == ymax) {
			y = 22;
		}
		while (y < ymax) {
			attrset(COLOR_PAIR(3));
			mvaddstr(y, x + 4, " ");
			mvaddstr(y, x + 5, " ");
			y++;
		}
	}

	attrset(COLOR_PAIR(4));
	mvprintw(ymin - 1, xmin, "%d月", nowMonth->num);
	attrset(COLOR_PAIR(1));
	mvaddstr(ymax + 3, xmax - 12, " ");
	attrset(COLOR_PAIR(4));
	mvaddstr(ymax + 3, xmax - 11, " : 平均最高気温");
	attrset(COLOR_PAIR(2));
	mvaddstr(ymax + 4, xmax - 12, " ");
	attrset(COLOR_PAIR(4));
	mvaddstr(ymax + 4, xmax - 11, " : 平均最低気温");
	attrset(COLOR_PAIR(3));
	mvaddstr(ymax + 5, xmax - 12, " ");
	attrset(COLOR_PAIR(4));
	mvaddstr(ymax + 5, xmax - 11, " : 平均降水量");

	refresh();
}

void write_file(Climate* nowMonth) {
	FILE* fp;
	char s[BUFFSIZE];
	errno_t error;

	error = fopen_s(&fp, "kyoto_averagedata.csv", "w");
	if (error != 0)
		fprintf_s(stderr, "failed to open");
	else {
		fputs("年/月, 平均最高気温, 平均最低気温, 平均降水量\n", fp);
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 12; j++) {
				fprintf(fp, "%d/%d, %lf, %lf, %lf\n", i + 2018, nowMonth->num, nowMonth->max[i], nowMonth->min[i], nowMonth->rain[i]);
				nowMonth = nowMonth->nextMonth;
			}
		}
		fclose(fp);
	}
}