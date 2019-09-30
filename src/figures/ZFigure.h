#pragma once
#include "Figure.h"
#include "enums.h"
#include <vector>
#include <cstdint>

struct ZFigure : Figure {
	ZFigure();
	void setNextPoints();
	std::vector<std::vector<uint8_t>> getPoints(Orientation orientation) const;
	~ZFigure();

protected:
	Orientation getNextOrientationType() const noexcept;
};