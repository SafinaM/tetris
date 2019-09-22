#pragma once

#include "Figure.h"

struct IFigure : Figure {
public:
	void move();
	void rotate();
	~IFigure();
};

