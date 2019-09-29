#include "LRFigure.h"
#include <iostream>

LRFigure::LRFigure() {
	m_orientation = Orientation::Second_90;
	points = getPoints(m_orientation);
	m_Color = 2; // Green
}

void LRFigure::setNextPoints() {
	setOrientationType(getNextOrientationType());
	points = getPoints(m_orientation);
}

std::vector<std::vector<uint8_t>> LRFigure::getPoints(Orientation orientation) const {
	switch (orientation) {
		case Orientation::First_0: {
			return {{0, 1, 0},
					{0, 1, 0},
					{1, 1, 0}};
		}
		case Orientation::Second_90: {
			return {{1, 0, 0},
					{1, 1, 1},
					{0, 0, 0}};
		}
		case Orientation::Third_180: {
			return {{0, 1, 1},
					{0, 1, 0},
					{0, 1, 0}};
		}
		case Orientation::Fourth_270: {
			return {{0, 0, 0},
					{1, 1, 1},
					{0, 0, 1}};
		}
	}
}

Orientation LRFigure::getNextOrientationType() const noexcept{
	switch (m_orientation) {
		case Orientation::First_0: {
			return Orientation:: Second_90;
		}
		case Orientation::Second_90: {
			return Orientation::Third_180;
		}
		case Orientation::Third_180: {
			return Orientation::Fourth_270;
		}
		case Orientation::Fourth_270: {
			return Orientation::First_0;
		}
	}
}

LRFigure::~LRFigure() {
//	std::cout << "Desctructor of LRFigure" << std::endl;
}
