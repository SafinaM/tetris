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

int main() {
	std::cout << Board::widthBoard << " " << Board::heightBoard << std::endl;
	std::cout << rlutil::trows() << " Rows" << std::endl;
	std::cout << rlutil::tcols() << " Columns" << std::endl;
	std::unique_ptr<Figure> owner;
	int ch;
	std::vector<std::vector<uint8_t>> points;
	owner.reset(new LLFigure);
	if (owner != nullptr) {
		bool verifying = owner->verifyDown();
	}
	Board& board = Board::instance();
	points = owner->getPoints();
	int maxX = 0;
	int maxY = 0;
	auto start = std::chrono::system_clock::now();
	rlutil::hidecursor();
	rlutil::cls();
	while (true) {
		const Point orig(maxX / 2, 0);
		if(kbhit()) {
			ch = rlutil::getkey(); // Get character
			if (ch == 'q')
				break;
			switch (ch) {
				case 'w':
				case rlutil::KEY_UP:
				case rlutil::KEY_SPACE:
					points = owner->getPoints();
					std::cout << "w - rotate" << std::endl;
					owner->debugPrint();
//					if (board.allowRotate(*owner)) {
						owner->setNextPoints();
//						points = owner->getPoints();
//					}
					break;
				case 'a':
				case rlutil::KEY_LEFT:
					std::cout << "KEY_LEFT" << std::endl;
					owner->move(Direction::Left);
					std::cout << owner->getXOffset() << " " << owner->getYOffset() << std::endl;
					break;
				case 'd':
				case rlutil::KEY_RIGHT:
					std::cout << "KEY_RIGHT" << std::endl;
					std::cout << owner->getXOffset() << " " << owner->getYOffset() << std::endl;
					owner->move(Direction::Right);
					break;
				case 's':
				case rlutil::KEY_DOWN:
					std::cout << "KEY_DOWN" << std::endl;
					std::cout << owner->getXOffset() << " " << owner->getYOffset() << std::endl;
					owner->move(Direction::Down);
					break;
				default:
					break;
			}
			ch = 0;
		}
		if (ch == 'q')
			break;
		std::cout.flush();
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> diff = end-start;
		if (diff.count() > 1.5) {
			start = std::chrono::system_clock::now();
			diff.zero();
			std::cout << "gravity!" << std::endl;
			owner->move(Direction::Down);
			std::cout << owner->getXOffset() << " " << owner->getYOffset() << std::endl;
		}
//		std::cout << "loop end" << std::endl;
//		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

	return 0;
}



