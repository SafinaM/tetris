#pragma once
#include "FigureLocal.h"
#include "enums.h"
#include <vector>
#include <cstdint>

struct SFigure : FigureLocal {
	SFigure();
	void setNextPoints();
	std::vector<std::vector<uint8_t>> getPoints(Orientation orientation) const;
	~SFigure() = default;

protected:
	Orientation getNextOrientationType() const noexcept;
};