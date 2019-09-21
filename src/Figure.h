#pragma once

#include <vector>
#include <cstdint>
#include "enums.h"
#include "Movement.h"

class Figure {
public:

	bool verifyDown();
	std::vector<std::vector<uint8_t>> getPoints() const;

	virtual void move() = 0;
	virtual void rotate() = 0;
	virtual std::vector<std::vector<uint8_t>> getPoints(Orientation orientation) = 0;
	virtual void setNextPoints() = 0;
	virtual Orientation getNextOrientationType() = 0;

	void setOrientationType(Orientation orientation);
	virtual ~Figure();
	
	friend class Board;

protected:
	std::vector<std::vector<uint8_t>> points;
	Orientation m_orientation;
};
