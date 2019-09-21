#include <iostream>
#include <cassert>
#include "Figure.h"
#include "LLFigure.h"
#include "LRFigure.h"
#include "IFigure.h"
#include "Movement.h"

Figure::~Figure() {

}

void Figure::setOrientationType(Orientation orientation) {
	m_orientation = orientation;
}

std::vector<std::vector<uint8_t>> Figure::getPoints() {
	assert(points.size() != 0);
	return points;
}

bool Figure::verifyDown() {
//	std::cout << "verifyDown" << std::endl;
	return true;
}
