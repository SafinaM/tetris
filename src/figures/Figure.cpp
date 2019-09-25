#include <iostream>
#include <cassert>
#include "Figure.h"
#include "LLFigure.h"
#include "LRFigure.h"
#include "IFigure.h"

Figure::~Figure() {

}

void Figure::setOrientationType(Orientation orientation) {
	m_orientation = orientation;
}

std::vector<std::vector<uint8_t>> Figure::getPoints() const {
	assert(points.size() != 0);
	return points;
}

bool Figure::verifyDown() {
//	std::cout << "verifyDown" << std::endl;
	return true;
}

void Figure::move(Direction direction) noexcept {
	if (direction == Direction::Right) {
		++m_offsetX;
	} else if (direction == Direction::Left) {
		--m_offsetX;
	} else if (direction == Direction::Down) {
		++m_offsetY;
	}
}

// for debug
void Figure::setXY(int x, int y) noexcept {
	m_offsetX = x;
	m_offsetY = y;
}

int Figure::getXOffset() const noexcept {
	return m_offsetX;
}

int Figure::getYOffset() const noexcept {
	return m_offsetY;
}

void Figure::resetOffset()  noexcept {
	m_offsetX = 0;
	m_offsetY = 0;
}