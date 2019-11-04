#pragma once
#include "FigureLocal.h"
#include "enums.h"
#include <vector>
#include <cstdint>

struct TFigure : FigureLocal {
	TFigure();
	void setNextPoints();
	std::vector<std::vector<uint8_t>> getPoints(Orientation orientation) const;
	~TFigure() = default;

protected:
	Orientation getNextOrientationType() const noexcept;
};