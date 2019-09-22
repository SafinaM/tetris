#pragma once

#include "Figure.h"

struct LRFigure : Figure {
public:
	void move();
	void rotate();
	~LRFigure();
};