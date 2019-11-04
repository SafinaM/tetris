#pragma once
#include "FigureLocal.h"
#include "enums.h"
#include <vector>
#include <cstdint>

struct IFigure : FigureLocal {
	IFigure();
	void setNextPoints();
	std::vector<std::vector<uint8_t>> getPoints(Orientation orientation) const;
	~IFigure() = default;

protected:
	Orientation getNextOrientationType() const noexcept;
};