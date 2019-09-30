#include "SFigure.h"

SFigure::SFigure() {
	m_orientation = Orientation::First_0;
	points = getPoints(m_orientation);
	m_Color = 6; // Magenta
}

void SFigure::setNextPoints() {
	setOrientationType(getNextOrientationType());
	points = getPoints(m_orientation);
}

std::vector<std::vector<uint8_t>> SFigure::getPoints(Orientation orientation) const {
	switch (orientation) {
		case Orientation::First_0: {
			return {{0, 1, 1},
					{1, 1, 0},
					{0, 0, 0}};
		}
		case Orientation::Second_90: {
			return {{1, 0, 0},
					{1, 1, 0},
					{0, 1, 0}};
		}
	}
}

Orientation SFigure::getNextOrientationType() const noexcept{
	switch (m_orientation) {
		case Orientation::First_0: {
			return Orientation:: Second_90;
		}
		case Orientation::Second_90: {
			return Orientation::First_0;
		}
	}
}

SFigure::~SFigure() {
//	std::cout << "Desctructor of LLFigure" << std::endl;
}
