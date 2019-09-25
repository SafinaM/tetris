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
	// after checking we do not have filled lines
	for (auto i = 0; i < Board::heightBoard; ++i) {
		assert(!board.verifyLine(i));
	}
	std::cout << std::endl;
	figure->setNextPoints();
	figure->setXY(-1, 1);
	assert(board.allowMove(Direction::Right, *figure) == true);
	assert(board.allowMove(Direction::Left, *figure) == false);
	assert(board.allowMove(Direction::Down, *figure) == true);
	
	figure->setXY(0, 1);
	assert(board.allowRotate(*figure) == true);
	
	figure->setXY(7, 1);
	
	assert(board.allowMove(Direction::Right, *figure) == false);
	assert(board.allowMove(Direction::Left, *figure) == true);
	assert(board.allowMove(Direction::Down, *figure) == true);
	assert(board.allowRotate(*figure) == true);
	
	figure->setXY(7, 2);

	assert(board.allowMove(Direction::Right, *figure) == false);
	assert(board.allowMove(Direction::Left, *figure) == true);
	assert(board.allowMove(Direction::Down, *figure) == false);
	assert(board.allowRotate(*figure) == true);
	
	figure->setNextPoints();
	figure->setXY(8, 2);
	
	figure->setNextPoints();
	assert(board.allowRotate(*figure) == false);
	
	figure->setXY(0, 2);
	assert(board.allowRotate(*figure) == true);
	figure->setNextPoints();
	figure->setNextPoints();
	figure->setXY(-1, 2);
	assert(board.allowRotate(*figure) == false);
	
	figure->setXY(-1, 4);
	assert(board.allowMove(Direction::Right, *figure) == false);
	assert(board.allowMove(Direction::Left, *figure) == false);
	assert(board.allowMove(Direction::Down, *figure) == true);
	assert(board.allowRotate(*figure) == false);
	
	figure->setXY(2, 4);
	assert(board.allowMove(Direction::Right, *figure) == false);
	assert(board.allowMove(Direction::Left, *figure) == false);
	assert(board.allowMove(Direction::Down, *figure) == true);
	assert(board.allowRotate(*figure) == true);
	
	figure->setXY(2, 5);
	assert(board.allowMove(Direction::Right, *figure) == true);
	assert(board.allowMove(Direction::Left, *figure) == false);
	assert(board.allowMove(Direction::Down, *figure) == true);
	assert(board.allowRotate(*figure) == false);
	
	figure->setXY(2, 17);
	assert(board.allowMove(Direction::Right, *figure) == true);
	assert(board.allowMove(Direction::Left, *figure) == true);
	assert(board.allowMove(Direction::Down, *figure) == false);
	assert(board.allowRotate(*figure) == true);
	
	figure->setNextPoints();
	figure->setXY(0, 18);
	assert(board.allowMove(Direction::Right, *figure) == true);
	assert(board.allowMove(Direction::Left, *figure) == false);
	assert(board.allowMove(Direction::Down, *figure) == false);
	assert(board.allowRotate(*figure) == false);
	board.addFigureToBuffer(*figure);
	board.debugPrint();
}
