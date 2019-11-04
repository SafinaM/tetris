#pragma once
#include "FigureLocal.h"
#include "enums.h"
#include <vector>
#include <cstdint>

struct LLFigure : FigureLocal {
	LLFigure();
	void setNextPoints();
	std::vector<std::vector<uint8_t>> getPoints(Orientation orientation) const;
	~LLFigure() = default;

protected:
	Orientation getNextOrientationType() const noexcept;
};