#include "SQFigure.h"
#include <iostream>

SQFigure::SQFigure() {
	m_orientation = Orientation::First_0;
	points = getPoints(m_orientation);
	m_Color = 5; // blue
}

void SQFigure::setNextPoints() {
	setOrientationType(getNextOrientationType());
	points = getPoints(m_orientation);
}

std::vector<std::vector<uint8_t>> SQFigure::getPoints(Orientation orientation) const {
	return {{1, 1},
			{1, 1}};
}

Orientation SQFigure::getNextOrientationType() const noexcept{
	return Orientation:: First_0;
}
