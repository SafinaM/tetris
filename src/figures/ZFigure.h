#pragma once
#include "FigureLocal.h"
#include "enums.h"
#include <vector>
#include <cstdint>

struct ZFigure : FigureLocal {
	ZFigure();
	void setNextPoints();
	std::vector<std::vector<uint8_t>> getPoints(Orientation orientation) const;
	~ZFigure() = default;

protected:
	Orientation getNextOrientationType() const noexcept;
};