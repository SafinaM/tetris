#pragma once
#include "Figure.h"
#include <vector>
#include <cstdint>
#include "enums.h"

struct LLFigure : Figure {
	LLFigure();
	void setNextPoints();
	std::vector<std::vector<uint8_t>> getPoints(Orientation orientation) const;
	~LLFigure();

protected:
	Orientation getNextOrientationType() const noexcept;
};