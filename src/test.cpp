#include <Board.h>
#include <iostream>
#include <memory>
#include <cassert>
#include <FigureLocal.h>
#include <LLFigure.h>
#include <LRFigure.h>
#include <random>
#include <unordered_map>
#include <SQFigure.h>

int main() {
	std::random_device generator;
	uint32_t upLimit = 6;
	std::uniform_int_distribution<int> distribution(0, upLimit);
	std::unordered_map<int, int> map;
	const uint32_t numberOfTicks = 5000;
	int ticks = numberOfTicks;
	while (ticks > 0){
		int number = distribution(generator);
		++map[number];
		--ticks;
	}
	// generating figures checking
	for (const auto &it: map) {
		std::cout << it.first << " was generated " << it.second << " times" << std::endl;
		assert(it.second / (numberOfTicks / upLimit) < 0.1);
	}
	
	Board board(10, 20);
	std::unique_ptr<FigureLocal> figureLL(new LLFigure);
	std::unique_ptr<FigureLocal> figureSQ(new SQFigure);
	std::unique_ptr<FigureLocal> figureLR(new LRFigure);
	assert(figureLL);
	assert(figureLR);
	figureLL->move(Direction::Down);
	assert(figureLL->getYOffset() == 1);
	figureLL->move(Direction::Down);
	assert(figureLL->getYOffset() == 2);
	figureLL->move(Direction::Down);
	assert(figureLL->getYOffset() == 3);
	
	figureLR->move(Direction::Down);
	assert(figureLR->getYOffset() == 1);
	figureLR->move(Direction::Down);
	assert(figureLR->getYOffset() == 2);
	figureLR->move(Direction::Down);
	assert(figureLR->getYOffset() == 3);
	
	board.addFigureToBuffer(*figureLL);
	board.debugPrint();
	
	figureLL->setXY(3, 3);
	assert(figureLL->getXOffset() == 3);
	assert(figureLL->getYOffset() == 3);
	board.addFigureToBuffer(*figureLL);
	
	figureLL->setXY(6, 3);
	board.addFigureToBuffer(*figureLL);
	figureLL->setNextPoints();
	
	figureLL->setXY(8, 2);
	board.addFigureToBuffer(*figureLL);
	figureLL->setNextPoints();
	board.setLine(5);
	assert(board.verifyLine(5));
	board.setLine(6);
	
	assert(!board.verifyLine(7));
	assert(board.verifyLines());
	// after checking we do not have filled lines
	const uint32_t height = board.getHeight();
	
	uint32_t getHeight();
	for (auto i = 0; i < height; ++i) {
		assert(!board.verifyLine(i));
	}
	std::cout << std::endl;
	figureLL->setNextPoints();
	figureLL->setXY(-1, 1);
//	board.addFigureToBuffer(*figureLL);
//	board.debugPrint();
	assert(board.allowMove(Direction::Right, *figureLL) == true);
	
	assert(board.allowMove(Direction::Left, *figureLL) == false);
	assert(board.allowMove(Direction::Down, *figureLL) == true);
	
	figureLL->setXY(0, 1);
	assert(board.allowRotate(*figureLL) == true);
	
	figureLL->setXY(7, 1);
	
	assert(board.allowMove(Direction::Right, *figureLL) == false);
	assert(board.allowMove(Direction::Left, *figureLL) == true);
	assert(board.allowMove(Direction::Down, *figureLL) == true);
	assert(board.allowRotate(*figureLL) == true);
	
	figureLL->setXY(7, 1);
	
	assert(board.allowMove(Direction::Right, *figureLL) == false);
	assert(board.allowMove(Direction::Left, *figureLL) == true);
	assert(board.allowMove(Direction::Down, *figureLL) == true);
	assert(board.allowRotate(*figureLL) == true);
	
	figureLL->setXY(7, 2);

	assert(board.allowMove(Direction::Right, *figureLL) == false);
	assert(board.allowMove(Direction::Left, *figureLL) == true);
	assert(board.allowMove(Direction::Down, *figureLL) == false);
	assert(board.allowRotate(*figureLL) == true);
	
	figureLL->setNextPoints();
	figureLL->setXY(8, 2);
	
	figureLL->setNextPoints();
	assert(board.allowRotate(*figureLL) == false);
	
	figureLL->setXY(0, 2);
	assert(board.allowRotate(*figureLL) == true);
	figureLL->setNextPoints();
	figureLL->setNextPoints();
	figureLL->setXY(-1, 2);
	assert(board.allowRotate(*figureLL) == false);
	
	figureLL->setXY(-1, 4);
	assert(board.allowMove(Direction::Right, *figureLL) == false);
	assert(board.allowMove(Direction::Left, *figureLL) == false);
	assert(board.allowMove(Direction::Down, *figureLL) == true);
	assert(board.allowRotate(*figureLL) == false);
	
	figureLL->setXY(2, 4);
	assert(board.allowMove(Direction::Right, *figureLL) == false);
	assert(board.allowMove(Direction::Left, *figureLL) == false);
	assert(board.allowMove(Direction::Down, *figureLL) == true);
	assert(board.allowRotate(*figureLL) == true);
	
	figureLL->setXY(2, 5);
	assert(board.allowMove(Direction::Right, *figureLL) == true);
	assert(board.allowMove(Direction::Left, *figureLL) == false);
	assert(board.allowMove(Direction::Down, *figureLL) == true);
	assert(board.allowRotate(*figureLL) == false);
	
	figureLL->setXY(2, 17);
	assert(board.allowMove(Direction::Right, *figureLL) == true);
	assert(board.allowMove(Direction::Left, *figureLL) == true);
	assert(board.allowMove(Direction::Down, *figureLL) == false);
	assert(board.allowRotate(*figureLL) == true);
	
	figureLL->setNextPoints();
	figureLL->setXY(0, 18);
	assert(board.allowMove(Direction::Right, *figureLL) == true);
	assert(board.allowMove(Direction::Left, *figureLL) == false);
	assert(board.allowMove(Direction::Down, *figureLL) == false);
	assert(board.allowRotate(*figureLL) == false);
	
	figureSQ->setXY(2, 18);
	assert(board.allowMove(Direction::Right, *figureSQ) == true);
	assert(board.allowMove(Direction::Left, *figureSQ) == true);
	assert(board.allowMove(Direction::Down, *figureSQ) == false);
	assert(board.allowRotate(*figureSQ) == true);
	
	
	figureSQ->setXY(2, 21);
	assert(board.allowMove(Direction::Right, *figureSQ) == false);
	assert(board.allowMove(Direction::Left, *figureSQ) == false);
	assert(board.allowMove(Direction::Down, *figureSQ) == false);
	assert(board.allowRotate(*figureSQ) == false);
	
	// it should not be added because out of range
	//	board.addFigureToBuffer(*figureSQ);
	//	board.debugPrint();
	
	std::cout << "\nLRFigureTest\n"<< std::endl;
	
	figureLR->setXY(0, 0);
	board.addFigureToBuffer(*figureLR);
	figureLR->setNextPoints();
	figureLR->setXY(-1, 5);
	board.addFigureToBuffer(*figureLR);
	figureLR->setNextPoints();
	figureLR->setXY(7, 0);
	board.addFigureToBuffer(*figureLR);
	figureLR->setNextPoints();
	figureLR->setXY(3, 14);
	board.addFigureToBuffer(*figureLR);
	board.debugPrint();
}
