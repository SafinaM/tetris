#pragma once
#include "Figure.h"
#include <vector>
#include <cstdint>
#include "enums.h"

class LLFigure : public Figure {
public:
	LLFigure();
	void move();
	void rotate();
	void setNextPoints();
	std::vector<std::vector<uint8_t>> getNextPoints(Orientation orientation);
	~LLFigure();

protected:
	Orientation getNextOrientationType();
};