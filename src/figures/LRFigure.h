#pragma once
#include "Figure.h"
#include <vector>
#include <cstdint>
#include "enums.h"

struct LRFigure : Figure {
	LRFigure();
	void setNextPoints();
	std::vector<std::vector<uint8_t>> getPoints(Orientation orientation) const;
	~LRFigure() = default;

protected:
	Orientation getNextOrientationType() const noexcept;
};