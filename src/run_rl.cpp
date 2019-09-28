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

int main() {
//	std::cout << Board::widthBoard << " " << Board::heightBoard << std::endl;
	std::unique_ptr<Figure> owner;
	int ch;
	std::vector<std::vector<uint8_t>> points;
	Board& board = Board::instance();
	auto start = std::chrono::system_clock::now();
	rlutil::saveDefaultColor();
	rlutil::hidecursor();
	rlutil::cls();
	Painter& painter = Painter::instance();
	
	int x = painter.getScreenWidth();
	int y = painter.getScreenHeight();
	painter.drawPoint(0, 0, '#', 6, 0);
	uint32_t originX = (x - Board::widthBoard) / 2;
	uint32_t originY = 0.1 * y;
	painter.drawBoard(board, originX,originY);
	
	owner.reset(new LLFigure);
	painter.drawFigure(*owner, originX, originY);
	while (true) {

		if(kbhit()) {
			ch = rlutil::getkey(); // Get character
			if (ch == 'q')
				break;
			switch (ch) {
				case 'w':
				case rlutil::KEY_UP:
				case rlutil::KEY_SPACE:
					if (board.allowRotate(*owner)) {
						painter.drawFigure(*owner, originX, originY, false);
						owner->setNextPoints();
					}
					break;
				case 'a':
				case rlutil::KEY_LEFT:
					if (board.allowMove(Direction::Left, *owner)) {
						painter.drawFigure(*owner, originX, originY, false);
						owner->move(Direction::Left);
					}
					break;
				case 'd':
				case rlutil::KEY_RIGHT:
					if (board.allowMove(Direction::Right, *owner)) {
						painter.drawFigure(*owner, originX, originY, false);
						owner->move(Direction::Right);
					}
					break;
				case 's':
				case rlutil::KEY_DOWN:
					if (board.allowMove(Direction::Down, *owner)) {
						painter.drawFigure(*owner, originX, originY, false);
						owner->move(Direction::Down);
					}
					break;
				default:
					break;
			}
			ch = 0;
		}
		if (ch == 'q')
			break;
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> diff = end-start;
		if (diff.count() > 1.5) {
			
			start = std::chrono::system_clock::now();
			diff.zero();
			if (board.allowMove(Direction::Down, *owner)) {
				painter.drawFigure(*owner, originX, originY, false);
				owner->move(Direction::Down);
			}
		}
		painter.drawFigure(*owner, originX, originY, false);
		painter.drawFigure(*owner, originX, originY);
//		std::this_thread::sleep_for(std::chrono::milliseconds(500));

	}
	rlutil::showcursor();
	
	return 0;
}



