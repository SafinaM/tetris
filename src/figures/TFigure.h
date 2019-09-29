#pragma once
#include "Figure.h"
#include "enums.h"
#include <vector>
#include <cstdint>

struct TFigure : Figure {
	TFigure();
	void setNextPoints();
	std::vector<std::vector<uint8_t>> getPoints(Orientation orientation) const;
	~TFigure();

protected:
	Orientation getNextOrientationType() const noexcept;
};