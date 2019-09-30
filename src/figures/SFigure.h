#pragma once
#include "Figure.h"
#include "enums.h"
#include <vector>
#include <cstdint>

struct SFigure : Figure {
	SFigure();
	void setNextPoints();
	std::vector<std::vector<uint8_t>> getPoints(Orientation orientation) const;
	~SFigure();

protected:
	Orientation getNextOrientationType() const noexcept;
};