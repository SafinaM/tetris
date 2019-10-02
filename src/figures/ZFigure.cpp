#include "ZFigure.h"
#include <iostream>

ZFigure::ZFigure() {
	m_orientation = Orientation::First_0;
	points = getPoints(m_orientation);
	m_Color = 7; // Magenta
}

void ZFigure::setNextPoints() {
	setOrientationType(getNextOrientationType());
	points = getPoints(m_orientation);
}

std::vector<std::vector<uint8_t>> ZFigure::getPoints(Orientation orientation) const {
	switch (orientation) {
		case Orientation::First_0: {
			return {{1, 1, 0},
					{0, 1, 1},
					{0, 0, 0}};
		}
		case Orientation::Second_90: {
			return {{0, 0, 1},
					{0, 1, 1},
					{0, 1, 0}};
		}
	}
}

Orientation ZFigure::getNextOrientationType() const noexcept{
	switch (m_orientation) {
		case Orientation::First_0: {
			return Orientation:: Second_90;
		}
		case Orientation::Second_90: {
			return Orientation::First_0;
		}
	}
}
