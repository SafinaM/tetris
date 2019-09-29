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
	std::shared_ptr<Figure> figure;
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
	painter.setXY((x - Board::widthBoard) / 2, 0.1 * y);
	painter.drawBoard(board);
	figure.reset(new LLFigure);
	figure->setXY(Board::widthBoard / 2 - 1, 0);
	while (true) {
		if (kbhit()) {
			ch = rlutil::getkey();
			if (ch == 'q')
				break;
			switch (ch) {
				case 'w':
				case rlutil::KEY_UP:
				case rlutil::KEY_SPACE:
					if (board.allowRotate(*figure)) {
						painter.drawFigure(*figure, false);
						figure->setNextPoints();
					}
					break;
				case 'a':
				case rlutil::KEY_LEFT:
					if (board.allowMove(Direction::Left, *figure)) {
						painter.drawFigure(*figure, false);
						figure->move(Direction::Left);
					}
					break;
				case 'd':
				case rlutil::KEY_RIGHT:
					if (board.allowMove(Direction::Right, *figure)) {
						painter.drawFigure(*figure, false);
						figure->move(Direction::Right);
					}
					break;
				case 's':
				case rlutil::KEY_DOWN:
					if (board.allowMove(Direction::Down, *figure)) {
						painter.drawFigure(*figure, false);
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
			
			start = std::chrono::system_clock::now();
			diff.zero();
			if (board.allowMove(Direction::Down, *figure)) {
				painter.drawFigure(*figure, false);
				figure->move(Direction::Down);
				rlutil::cls();
				painter.drawBoard(board);
			} else {
					board.addFigureToBuffer(*figure);
					painter.drawBoard(board);
					board.verifyLines();
					rlutil::cls();
					painter.drawBoard(board);
					figure.reset(new LLFigure);
					figure->setXY(Board::widthBoard / 2 - 1, 0);
			}
		}
		painter.drawFigure(*figure, false);
		painter.drawFigure(*figure);
//		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	rlutil::showcursor();
	
	return 0;
}



