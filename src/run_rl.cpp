#include <memory>
#include <thread>
#include <iostream>
#include <Figure.h>
#include <LLFigure.h>
#include <LRFigure.h>
#include <IFigure.h>
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

int main() {
	std::shared_ptr<Figure> figure;
	int ch;
	std::vector<std::vector<uint8_t>> points;
	Board& board = Board::instance();
	auto start = std::chrono::system_clock::now();
//	rlutil::saveDefaultColor();
	Painter& painter = Painter::instance();
	painter.hideCursor();
	painter.clearScreen();
	int x = painter.getScreenWidth();
	int y = painter.getScreenHeight();
	painter.setXY((x - Board::widthBoard) / 2, (y - Board::heightBoard) / 2);
	painter.drawBoard(board);
	figure.reset(new LLFigure);
	figure->setXY(Board::widthBoard / 2 - 1, 0);
	noecho();
	while (true) {
		painter.setScreenSize();
		if (painter.isScreenSizeChanged()) {
			painter.clearScreen();
			painter.setFlagScreenSizeChangedInFalse();
			x = painter.getScreenWidth();
			y = painter.getScreenHeight();
			painter.setXY((x - Board::widthBoard) / 2, (y - Board::heightBoard) / 2);
			painter.drawBoard(board);
		}
		if (kbhit()) {
			painter.drawFigure(*figure, false);
			ch = rlutil::getkey();
			if (ch == 'q')
				break;
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
		if (diff.count() > 1.5) {
			painter.drawFigure(*figure, false);
			start = std::chrono::system_clock::now();
			diff.zero();
			if (board.allowMove(Direction::Down, *figure)) {
				figure->move(Direction::Down);
			} else {
				board.addFigureToBuffer(*figure);
				painter.drawBoard(board);
				if (board.verifyLines())
					painter.drawBoard(board);
				figure.reset(new LLFigure);
				figure->setXY(Board::widthBoard / 2 - 1, 0);
			}
		}
//		painter.drawFigure(*figure, false);
		painter.drawFigure(*figure);
//		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	
	painter.showCursor();
	painter.clearScreen();
	echo();
	
	return 0;
}



