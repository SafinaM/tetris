#include "LLFigure.h"
#include <iostream>

LLFigure::LLFigure() {
	m_orientation = Orientation::First_0;
	points = {{0, 1, 0},
			  {0, 1, 0},
			  {0, 1, 1}};
}


void LLFigure::move() {
//	std::cout << "LL move" << std::endl;
	return;
}

void LLFigure::rotate() {
//	std::cout << "LL rotate" << std::endl;

	return;
}

void LLFigure::setNextPoints() {
//	std::cout << "LL setPoints" << std::endl;
	setOrientationType(getNextOrientationType());
	points = getNextPoints(m_orientation);
}

std::vector<std::vector<uint8_t>> LLFigure::getNextPoints(Orientation orientation) {
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
