#include <memory>
#include <iostream>
#include <Figure.h>
#include <LLFigure.h>
#include <LRFigure.h>
#include <IFigure.h>
#include <Point.h>
#include <Board.h>
#include <rlutil.h>


int kbhit() {
	int ch;
	if ((ch = getch()) == ERR)
		return 0;
	else
		return ch;
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

	int maxX = 0;
	int maxY = 0;
	auto start = std::chrono::system_clock::now();
	while (true) {
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

		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> diff = end-start;
		if (diff.count() > 0.5) {
			start = std::chrono::system_clock::now();
			diff.zero();
			
		}
		
	}

	return 0;
}



