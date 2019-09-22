#include "LLFigure.h"
#include <iostream>

LLFigure::LLFigure() {
	m_orientation = Orientation::Second_90;
	points = getPoints(m_orientation);
}

void LLFigure::setNextPoints() {
	setOrientationType(getNextOrientationType());
	points = getPoints(m_orientation);
}

std::vector<std::vector<uint8_t>> LLFigure::getPoints(Orientation orientation) {
	switch (orientation) {
		case Orientation::First_0: {
			return {{0, 1, 0},
					{0, 1, 0},
					{0, 1, 1}};
		}
		case Orientation::Second_90: {
			return {{0, 0, 1},
					{1, 1, 1},
					{0, 0, 0}};
		}
		case Orientation::Third_180: {
			return {{1, 1, 0},
					{0, 1, 0},
					{0, 1, 0}};
		}
		case Orientation::Fourth_270: {
			return {{0, 0, 0},
					{1, 1, 1},
					{1, 0, 0}};
		}
	}
}

Orientation LLFigure::getNextOrientationType() {
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

LLFigure::~LLFigure() {
//	std::cout << "Desctructor of LLFigure" << std::endl;
}
