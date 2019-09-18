#include <curses.h>
#include <stdlib.h>

#include <memory>
#include <iostream>
#include <thread>
#include <mutex>
#include <zconf.h>

#include "Figure.h"
#include "LLFigure.h"
#include "LRFigure.h"
#include "IFigure.h"
#include "Point.h"


void printTriangle(int startrow, int startcol, int height)
{
	int x=startcol;

	for(int r = startrow; r <= startrow + height; r++)
	{
		for(int c = startcol; c <= x; c++)
		{
			move(r, c);
			printw(" ");
		}
		x++;
		startcol--;
	}

}

void printRectangle(int startrow, int startcol, int height, int width)
{
	for(int r = startrow; r <= startrow+height; r++)
	{
		for(int c=startcol; c <= startcol+width; c++)
		{
			move(r, c);
			printw(" ");
		}
	}
}

int kbhit(void)
{
	char ch;
	if ((ch = getch()) == ERR) {
//		std::cout << "ERR" << std::endl;
		return 0;
	}
	else {
//		std::cout << ch << std::endl;
		return ch;
	}
}
std::mutex mutex;
std::unique_ptr<Figure> owner;
char ch;
std::vector<std::vector<uint8_t>> points;

void interaction(int offset, int maxX) {
	while (true) {
		while(ch = kbhit()) {
			mutex.lock();
			if (ch == 'q')
				break;
			if (ch == 'r') {
			Orientation nextOrientation = owner->getNextOrientationType();
			std::vector<std::vector<uint8_t>> nextPoints = owner->getNextPoints(nextOrientation);
				owner->setNextPoints();
				points = owner->getPoints();
				refresh();
				attrset(COLOR_PAIR(1));
				init_pair(1, 3, 1);
				for (int i = 0; i < points.size(); ++i) {
					for (int j = 0; j < points[0].size(); ++j) {
						if (points[i][j]) {
							move(i + offset, j + maxX / 2);
							printw(" ");
						}
					}
				}
//				clear();
				refresh();
				attrset(COLOR_PAIR(0));
				for (int i = 0; i < points.size(); ++i) {
					for (int j = 0; j < points[0].size(); ++j) {
						if (points[i][j]) {
							move(i + offset, j + maxX / 2);
							printw(" ");
						}
					}
				}
				refresh();

			}
		}
		mutex.unlock();
		std::this_thread::sleep_for(std::chrono::milliseconds(5));

	}

}

int main() {


	owner.reset(dynamic_cast<Figure*>(new LLFigure));
	if (owner != nullptr) {
		owner->move();
		owner->rotate();
		bool verifying = owner->verifyDown();
	}
//	owner->setOrientationType(Orientation::First_0);
//	owner->setPoints(Orientation::First_0);
	points = owner->getPoints();

//	std::cout << points.size() << " "<< points[0].size() << std::endl;

	initscr();
	int maxX = 0;
	int maxY = 0;
	int offset = 0;
	curs_set(0);
	cbreak();
	noecho();
	timeout(0);            // no blocking on getch()
	nodelay(stdscr, TRUE);
	scrollok(stdscr, TRUE);
	keypad(stdscr, TRUE);
	getmaxyx(stdscr, maxY, maxX);
	std::thread threadInteraction(interaction, offset, maxX);

	while (true) {
		mutex.lock();
		getmaxyx(stdscr, maxY, maxX);
//		printf("maxX = %d, maxY = %d", maxX, maxY);
		start_color();
		const Point orig(maxX / 2, 0);


		if (ch == 'q')
			break;
		refresh();
		attrset(COLOR_PAIR(1));
		init_pair(1, 3, 1);
		for (int i = 0; i < points.size(); ++i) {
			for (int j = 0; j < points[0].size(); ++j) {
				if (points[i][j]) {
					move(i + offset, j + maxX / 2);
					printw(" ");
				}
			}
		}
		refresh();
		mutex.unlock();
		std::this_thread::sleep_for(std::chrono::milliseconds(400));
		mutex.lock();
		attrset(COLOR_PAIR(0));
		for (int i = 0; i < points.size(); ++i) {
			for (int j = 0; j < points[0].size(); ++j) {
				if (points[i][j]) {
					move(i + offset, j + maxX / 2);
					printw(" ");
				}
			}
		}
		refresh();
		++offset;
		mutex.unlock();

	}
	threadInteraction.join();
	endwin();
//	init_pair(2, 4, 2);
//	init_pair(3, 7, 4);
////		init_pair(4, 5, 3);
//
//	attrset(COLOR_PAIR(2));
//	printRectangle(8, 10 , 7, 10);
//
//	attrset(COLOR_PAIR(3));
//	printRectangle(11 ,12 , 4, 2);
	return 0;
}



