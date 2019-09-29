#pragma once
#include "Figure.h"
#include "enums.h"
#include <vector>
#include <cstdint>

struct IFigure : Figure {
	IFigure();
	void setNextPoints();
	std::vector<std::vector<uint8_t>> getPoints(Orientation orientation) const;
	~IFigure();

protected:
	Orientation getNextOrientationType() const noexcept;
};