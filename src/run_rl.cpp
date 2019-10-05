#include <memory>
#include <thread>
#include <iostream>
#include <random>
#include <cassert>

#include <Figure.h>
#include <LLFigure.h>
#include <LRFigure.h>
#include <IFigure.h>
#include <TFigure.h>
#include <SFigure.h>
#include <ZFigure.h>
#include <SQFigure.h>
#include <Point.h>
#include <Board.h>
#include <rlutil.h>
#include <Painter.h>


// TODO noecho for windows
void noecho() {
	struct termios dt;
	tcgetattr(STDIN_FILENO, &dt);
	dt.c_lflag    &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &dt);
}

void echo() {
	struct termios dt;
	tcgetattr(STDIN_FILENO, &dt);
	dt.c_lflag    |= (ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &dt);
}

uint32_t generateNumber(uint32_t downLimit, uint32_t upLimit) {
	std::random_device rd;
	std::uniform_int_distribution<uint32_t> distribution(downLimit, upLimit);
	return distribution(rd);
}

void generateFigure(std::unique_ptr<Figure>& figure) {
	
	uint32_t number = generateNumber(0, 6);
	switch(number) {
		case 0:
			figure.reset(new IFigure);
			break;
		case 1:
			figure.reset(new LLFigure);
			break;
		case 2:
			figure.reset(new LRFigure);
			break;
		case 3:
			figure.reset(new SFigure);
			break;
		case 4:
			figure.reset(new ZFigure);
			break;
		case 5:
			figure.reset(new TFigure);
			break;
		case 6:
			figure.reset(new SQFigure);
			break;
		default:
			std::cerr << "Unsupported type of figure" << std::endl;
			assert(false);
			break;
	}
}

int main() {
	
	std::unique_ptr<Figure> nextFigure;
	std::unique_ptr<Figure> figure;
	int ch = 0;
	std::vector<std::vector<uint8_t>> points;
	Board& board = Board::instance();
	auto start = std::chrono::system_clock::now();
	Painter& painter = Painter::instance();
	painter.hideCursor();
	painter.clearScreen();
	const std::string gameOverStr = " GAME OVER!!! press Q - to quite, any other key - to repeat! ";
	painter.setXY(
		(painter.getScreenWidth() - Board::widthBoard) / 2,
		(painter.getScreenHeight() - Board::heightBoard) / 2);
	
	painter.drawBoard(board);
	const double originTimePeriod = 1.2;
	double currentTimePeriod = originTimePeriod;
	generateFigure(figure);
	
	while(true) {
		if (ch == 'q')
			break;
		generateFigure(nextFigure);
		nextFigure->setXY(Board::widthBoard + 4, 6);
		painter.drawFigure(*nextFigure, false, ' ');
		figure->setXY(Board::widthBoard / 2 - 1, 0);
		noecho();
		while (true) {
			painter.setScreenSize();
			if (painter.isScreenSizeChanged()) {
				painter.clearScreen();
				painter.setXY(
					(painter.getScreenWidth() - Board::widthBoard) / 2,
					(painter.getScreenHeight() - Board::heightBoard) / 2);
				painter.drawBoard(board);
				painter.printColoredText(
					board.getNumberOfErasedLinesStr(),
					painter.xOffsetBoard + Board::widthBoard + 4,
					painter.yOffsetBoard,
					0,
					2);
				
				painter.printColoredText(
					board.getLevelStr(),
					painter.xOffsetBoard + Board::widthBoard + 4,
					painter.yOffsetBoard + 3,
					0,
					2);
			}
			if (kbhit()) {
				// erase prev figure!!!
				painter.drawFigure(*figure, false, 0);
				ch = rlutil::getkey();
				switch (ch) {
					case 'w':
					case rlutil::KEY_UP:
					case rlutil::KEY_SPACE:
						if (board.allowRotate(*figure)) {
							figure->setNextPoints();
						}
						break;
					case 'a':
					case rlutil::KEY_LEFT:
						if (board.allowMove(Direction::Left, *figure)) {
							figure->move(Direction::Left);
						}
						break;
					case 'd':
					case rlutil::KEY_RIGHT:
						if (board.allowMove(Direction::Right, *figure)) {
							figure->move(Direction::Right);
						}
						break;
					case 's':
					case rlutil::KEY_DOWN:
						if (board.allowMove(Direction::Down, *figure)) {
							figure->move(Direction::Down);
						}
						break;
					default:
						break;
				}
			}
			
			if (ch == 'q')
				break;
			
			auto end = std::chrono::system_clock::now();
			std::chrono::duration<double> diff = end-start;
			if (diff.count() > currentTimePeriod) {
				painter.drawFigure(*figure, false, 0);
				start = std::chrono::system_clock::now();
				diff.zero();
				if (board.allowMove(Direction::Down, *figure)) {
					figure->move(Direction::Down);
				} else {
					if (figure->getYOffset() <= 0) {
						painter.clearScreen();
						painter.printColoredText(
							gameOverStr,
							painter.getScreenWidth() / 2 - gameOverStr.size() / 2,
							painter.getScreenWidth() / 2,
							6,
							12);
						ch = getchar();
						if (ch == 'q')
							break;
						board.clear();
						painter.clearScreen();
						currentTimePeriod = originTimePeriod;
						painter.drawBoard(board);
						break;
					}
					board.addFigureToBuffer(*figure);
					painter.drawFigure(*nextFigure, false, ' ');
					figure = std::move(nextFigure);
					
					painter.drawBoard(board);
					if (board.verifyLines()) {
						// TODO move in one method
						painter.printColoredText(
							board.getNumberOfErasedLinesStr(),
							painter.xOffsetBoard + Board::widthBoard + 4,
							painter.yOffsetBoard,
							0,
							2);
						if (board.levelIsChanged()) {
							currentTimePeriod -= 0.1;
							auto color = generateNumber(1, 7);
							Board::backGroundColor = color;
							painter.printColoredText(
								board.getLevelStr(),
								painter.xOffsetBoard + Board::widthBoard + 4,
								painter.yOffsetBoard + 3,
								0,
								2);
						}
						painter.drawBoard(board);
					}
					break;
				}
			}
			painter.drawFigure(*figure);
			painter.drawFigure(*nextFigure);
			
		} // one figure movement
	}     // main cycle
	
	painter.showCursor();
	painter.clearScreen();
	echo();
	
	return 0;
}



