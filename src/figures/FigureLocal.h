#pragma once

#include <vector>
#include <cstdint>
#include <memory>
#include <Figure.h>
#include "enums.h"

struct FigureLocal : Figure {
	FigureLocal(Orientation orientation) : Figure(orientation) {}
	virtual void setNextPoints() = 0;
	virtual Orientation getNextOrientationType() const noexcept = 0;
	virtual ~FigureLocal() = default;
};

