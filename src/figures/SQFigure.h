#pragma once
#include "Figure.h"
#include "enums.h"
#include <vector>
#include <cstdint>

struct SQFigure : Figure {
	SQFigure();
	void setNextPoints();
	std::vector<std::vector<uint8_t>> getPoints(Orientation orientation) const;
	~SQFigure();

protected:
	Orientation getNextOrientationType() const noexcept;
};