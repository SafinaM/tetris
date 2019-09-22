#include "Board.h"
#include <iostream>
#include <memory>
#include <cassert>
#include "figures/Figure.h"
#include "figures/LLFigure.h"


int main() {
	Board& board = Board::instance();
	std::unique_ptr<Figure> figure(new LLFigure);
	assert(figure);
	Movement movement;
//	movement.moveRight();
//	movement.moveLeft();
	movement.moveDown();
	assert(movement.getYOffset() == 1);
	movement.moveDown();
	assert(movement.getYOffset() == 2);
	movement.moveDown();
	assert(movement.getYOffset() == 3);
	
	board.addFigureToBuffer(*figure, movement);
	
	movement.set(3, 3);
	assert(movement.getXOffset() == 3);
	assert(movement.getYOffset() == 3);
	board.addFigureToBuffer(*figure, movement);
	
	movement.set(6, 3);
	board.addFigureToBuffer(*figure, movement);
	figure->setNextPoints();

	movement.set(8, 2);
	board.addFigureToBuffer(*figure, movement);
	figure->setNextPoints();
	board.setLine(5);
	assert(board.verifyLine(5));
	board.setLine(6);
	assert(!board.verifyLine(7));
	board.debugPrint();
	
	board.verifyLines();
	// after verifying we do not have filled lines
	for (auto i = 0; i < Board::heightBoard; ++i) {
		assert(!board.verifyLine(i));
	}

}
