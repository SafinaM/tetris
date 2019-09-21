#include "Board.h"
#include <iostream>
#include <memory>
#include "Figure.h"
#include "LLFigure.h"

using namespace std;



int main() {
//	Singleton* p1 = Singleton::getInstance();
	Board& board = Board::instance();
//	board.clear();
//	board.debugPrint();
	Figure* figure = new LLFigure;
	Movement movement;
//	movement.moveRight();
//	movement.moveLeft();
	movement.moveDown();
	movement.moveDown();
	movement.moveDown();
	if (figure) {
		board.addFigureToBuffer(*figure, movement);
	}
	
	movement.set(3, 3);
	board.addFigureToBuffer(*figure, movement);
	
	movement.set(6, 3);
	board.addFigureToBuffer(*figure, movement);
	figure->setNextPoints();

	movement.set(8, 2);
	board.addFigureToBuffer(*figure, movement);
	figure->setNextPoints();
	board.debugPrint();
	
	board.verifyLines();
	std::cout << std::endl;
	board.debugPrint();
	
}
