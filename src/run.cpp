#include <curses.h>

#include <memory>
#include <iostream>
#include <thread>
#include <Figure.h>
#include <LLFigure.h>
#include <LRFigure.h>
#include <IFigure.h>
#include <Point.h>
#include <Board.h>


int kbhit() {
	int ch;
	if ((ch = getch()) == ERR)
		return 0;
	else
		return ch;
}

void rotate(std::unique_ptr<Figure>& owner, std::vector<std::vector<uint8_t>>& points, int maxX) {
	Orientation nextOrientation = owner->getNextOrientationType();
	std::vector<std::vector<uint8_t>> nextPoints = owner->getPoints(nextOrientation);
	owner->setNextPoints();
	points = owner->getPoints();
	refresh();
	attrset(COLOR_PAIR(1));
	init_pair(1, 3, 1);
	for (int i = 0; i < points.size(); ++i) {
		for (int j = 0; j < points[0].size(); ++j) {
			if (points[i][j]) {
				move(i + owner->getXOffset(), j + maxX / 2 + owner->getXOffset());
				printw(" ");
			}
		}
	}
	clear();
}

void draw(std::unique_ptr<Figure>& owner, int maxX) {
	auto points = owner->getPoints();
	refresh();
	attrset(COLOR_PAIR(1));
	init_pair(1, 3, 1);
	for (int i = 0; i < points.size(); ++i) {
		for (int j = 0; j < points[0].size(); ++j) {
			if (points[i][j]) {
				move(i + owner->getYOffset(), j + maxX / 2 + owner->getXOffset());
				printw(" ");
			}
		}
	}
	clear();
}


int main() {
	std::cout << Board::widthBoard << " " << Board::heightBoard << std::endl;
	std::unique_ptr<Figure> owner;
	int ch;
	std::vector<std::vector<uint8_t>> points;
	owner.reset(dynamic_cast<Figure*>(new LLFigure));
	if (owner != nullptr) {
		bool verifying = owner->verifyDown();
	}
	points = owner->getPoints();

//	std::cout << points.size() << " "<< points[0].size() << std::endl;

	initscr();
	int maxX = 0;
	int maxY = 0;
	curs_set(0);
	cbreak();
	noecho();
	timeout(0);            // no blocking on getch()
	nodelay(stdscr, TRUE);
	scrollok(stdscr, TRUE);
	keypad(stdscr, TRUE);
	getmaxyx(stdscr, maxY, maxX);
	auto start = std::chrono::system_clock::now();
	while (true) {
		getmaxyx(stdscr, maxY, maxX);
//		printf("maxX = %d, maxY = %d", maxX, maxY);
		start_color();
		const Point orig(maxX / 2, 0);

		while(ch = kbhit()) {
			if (ch == 'q')
				break;
			if (ch == 'r') {
				rotate(owner, points, maxX);
			}
			switch (ch) {
				case KEY_UP:
					break;
				case KEY_LEFT:
					owner->move(Direction::Left);
					break;
				case KEY_RIGHT:
					owner->move(Direction::Right);
					break;
				case KEY_DOWN:
					owner->move(Direction::Down);
					break;
				default:
					break;
			}
			draw(owner, maxX);
		}
		if (ch == 'q')
			break;
		refresh();
		attrset(COLOR_PAIR(1));
		init_pair(1, 3, 1);
		for (int i = 0; i < points.size(); ++i) {
			for (int j = 0; j < points[0].size(); ++j) {
				if (points[i][j]) {
					move(i + owner->getYOffset(), j + maxX / 2 + owner->getXOffset());
					printw(" ");
				}
			}
		}
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> diff = end-start;
		refresh();
		if (diff.count() > 0.5) {
			start = std::chrono::system_clock::now();
			diff.zero();
			attrset(COLOR_PAIR(0));
			for (int i = 0; i < points.size(); ++i) {
				for (int j = 0; j < points[0].size(); ++j) {
					if (points[i][j]) {
						move(i + owner->getYOffset(), j + maxX / 2 + owner->getXOffset());
						printw(" ");
					}
				}
			}
			refresh();
			owner->move(Direction::Down);
		}

	}
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



