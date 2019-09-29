#include "IFigure.h"
#include <iostream>
#include <cassert>

IFigure::IFigure() {
	m_orientation = Orientation::Third_180;
	points = getPoints(m_orientation);
	m_Color = 4; // Red
}

void IFigure::setNextPoints() {
	setOrientationType(getNextOrientationType());
	points = getPoints(m_orientation);
}

std::vector<std::vector<uint8_t>> IFigure::getPoints(Orientation orientation) const {
	assert(m_orientation == Orientation::First_0 || m_orientation == Orientation::Third_180);
	switch (orientation) {
		case Orientation::First_0: {
			return {{0, 0, 1, 0},
					{0, 0, 1, 0},
					{0, 0, 1, 0},
					{0, 0, 1, 0}};
		}
		case Orientation::Third_180: {
			return {{0, 0, 0, 0},
					{0, 0, 0, 0},
					{1, 1, 1, 1},
					{0, 0, 0, 0}};
		}
	}
}

Orientation IFigure::getNextOrientationType() const noexcept {
	assert(m_orientation == Orientation::First_0 || m_orientation == Orientation::Third_180);
	switch (m_orientation) {
		case Orientation::First_0: {
			return Orientation:: Third_180;
		}
		case Orientation::Third_180: {
			return Orientation::First_0;
		}
	}
}

IFigure::~IFigure() {
//	std::cout << "Desctructor of IFigure" << std::endl;
}
