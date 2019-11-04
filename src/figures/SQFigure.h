#pragma once
#include "FigureLocal.h"
#include "enums.h"
#include <vector>
#include <cstdint>

struct SQFigure : FigureLocal {
	SQFigure();
	void setNextPoints();
	std::vector<std::vector<uint8_t>> getPoints(Orientation orientation) const;
	~SQFigure() = default;

protected:
	Orientation getNextOrientationType() const noexcept;
};