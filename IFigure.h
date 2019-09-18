#pragma once

#include "Figure.h"

class IFigure : public Figure {
public:
	void move();
	void rotate();
	~IFigure();
};

