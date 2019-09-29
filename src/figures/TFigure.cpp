#include "TFigure.h"
#include <iostream>

TFigure::TFigure() {
	m_orientation = Orientation::Third_180;
	points = getPoints(m_orientation);
	m_Color = 1; // Blue
}

void TFigure::setNextPoints() {
	setOrientationType(getNextOrientationType());
	points = getPoints(m_orientation);
}

std::vector<std::vector<uint8_t>> TFigure::getPoints(Orientation orientation) const {
	switch (orientation) {
		case Orientation::First_0: {
			return {{0, 1, 0},
					{1, 1, 1},
					{0, 0, 0}};
		}
		case Orientation::Second_90: {
			return {{0, 1, 0},
					{0, 1, 1},
					{0, 1, 0}};
		}
		case Orientation::Third_180: {
			return {{0, 0, 0},
					{1, 1, 1},
					{0, 1, 0}};
		}
		case Orientation::Fourth_270: {
			return {{0, 1, 0},
					{1, 1, 0},
					{0, 1, 0}};
		}
	}
}

Orientation TFigure::getNextOrientationType() const noexcept {
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

TFigure::~TFigure() {
//	std::cout << "Desctructor of LLFigure" << std::endl;
}
