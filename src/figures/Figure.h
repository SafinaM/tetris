#pragma once

#include <vector>
#include <cstdint>
#include "enums.h"

struct Figure {
	bool verifyDown();
	std::vector<std::vector<uint8_t>> getPoints() const;
	
	virtual std::vector<std::vector<uint8_t>> getPoints(Orientation orientation) const = 0;
	virtual void setNextPoints() = 0;
	virtual Orientation getNextOrientationType() const noexcept = 0;

	void setOrientationType(Orientation orientation);
	virtual ~Figure();
	void move(Direction direction) noexcept;
	void setXY(int x, int y) noexcept;
	int getXOffset() const noexcept;
	int getYOffset() const noexcept;
	void resetOffset() noexcept;
	
	friend class Board;


protected:
	std::vector<std::vector<uint8_t>> points;
	Orientation m_orientation;
	int m_offsetX = 0;
	int m_offsetY = 0;
};
