#include <Board.h>
#include <iostream>
#include <memory>
#include <cassert>
#include <rlutil.h>
#include <Figure.h>
#include <LLFigure.h>

int main() {
	Board& board = Board::instance();
	std::unique_ptr<Figure> figure(new LLFigure);
	assert(figure);
	figure->move(Direction::Down);
	assert(figure->getYOffset() == 1);
	figure->move(Direction::Down);
	assert(figure->getYOffset() == 2);
	figure->move(Direction::Down);
	assert(figure->getYOffset() == 3);
	
	board.addFigureToBuffer(*figure);
	
	figure->setXY(3, 3);
	assert(figure->getXOffset() == 3);
	assert(figure->getYOffset() == 3);
	board.addFigureToBuffer(*figure);
	
	figure->setXY(6, 3);
	board.addFigureToBuffer(*figure);
	figure->setNextPoints();
	
	figure->setXY(8, 2);
	board.addFigureToBuffer(*figure);
	figure->setNextPoints();
	board.setLine(5);
	assert(board.verifyLine(5));
	board.setLine(6);
	board.debugPrint();
	
	assert(!board.verifyLine(7));
	
	board.verifyLines();
	// after verifying we do not have filled lines
	for (auto i = 0; i < Board::heightBoard; ++i) {
		assert(!board.verifyLine(i));
	}
	std::cout << std::endl;
	figure->setXY(0, 1);
//	board.addFigureToBuffer(*figure);
	board.debugPrint();
	
	assert(board.allowMove(Direction::Right, *figure) == true);
	assert(board.allowMove(Direction::Left, *figure) == false);
	assert(board.allowMove(Direction::Down, *figure) == true);
	
}
