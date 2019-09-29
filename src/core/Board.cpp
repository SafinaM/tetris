#include <thread>
#include "Board.h"
#include "assert.h"

void Board::debugPrint() const {
	std::cout.clear();
	for (uint8_t i = 0; i < heightBoard; ++i) {
		for (uint8_t j = 0; j < widthBoard; ++j) {
			std::cout << +buffer[i][j];
		}
		std::cout << std::endl;
	}
}

void Board::addFigureToBuffer(const Figure& figure) {
	const auto& points = figure.points;
	int xOffset = figure.getXOffset();
	int yOffset = figure.getYOffset();
	for (auto i = 0; i < points.size(); ++i) {
		for (auto j = 0; j < points[0].size(); ++j) {
			if (points[i][j]) {
				// save the minimum number of string with the non zero value
				if (m_minNoneZeroY > i + yOffset)
					m_minNoneZeroY = i + yOffset;
				assert(!buffer[i + yOffset][j + xOffset]);
				buffer[i + yOffset][j + xOffset] = points[i][j];
			}
		}
	}
}

bool Board::verifyLines() {
	bool foundAtLeastOneFilledLine = false;
	for (auto i = m_minNoneZeroY; i < heightBoard; ++i) {
		// erase full line and insert empty line at the begin of vector - not effective way
		if (verifyLine(i)) {
			resetLine(i);
			// lower all lines one level below
			for (auto k = i; k > m_minNoneZeroY; --k) {
				swapLines(k, k - 1);
			}
			foundAtLeastOneFilledLine = true;
			// line was erased, the with non zero number is decreased
			++m_minNoneZeroY;
		}
	}
	
	if (foundAtLeastOneFilledLine)
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	return foundAtLeastOneFilledLine;
}

bool Board::verifyLine(uint32_t numY) {
	assert(numY >= 0 && numY < heightBoard);
		for (auto j = 0; j < widthBoard; ++j) {
			if (!buffer[numY][j])
				return false;
	}
	return true;
}

void Board::swapLines(uint32_t i, uint32_t j) {
	std::swap(buffer[i], buffer[j]);
}

void Board::resetLine(uint32_t numY) {
	for (uint32_t j = 0; j < widthBoard; ++j) {
		buffer[numY][j] = 0;
	}
}

// for debug
void Board::setLine(uint32_t numY, uint32_t value) {
	for (uint32_t j = 0; j < widthBoard; ++j) {
		buffer[numY][j] = value;
	}
}
void Board::setPoint(uint32_t x, uint32_t y, uint32_t value) {
	buffer[y][x] = value;
}

bool Board::allowRotate(const Figure &figure) const {
	Orientation orientation = figure.getNextOrientationType();
	auto points = figure.getPoints(orientation);
	uint32_t xOffset = figure.getXOffset();
	uint32_t yOffset = figure.getYOffset();
	
	return
		isCrossedFigureWithBuffer(points, xOffset, yOffset) &&
		isCrossedFigureWithWalls(points, xOffset, yOffset);
}

bool Board::isCrossedFigureWithBuffer(
	const std::vector<std::vector<uint8_t>> &points,
	int xOffset,
	int yOffset) const {
		for (auto i = 0; i < points.size(); ++i) {
			for (auto j = 0; j < points[0].size(); ++j) {
				// if buffer elements points are busy we cannot do this action
				if (points[i][j] && buffer[i + yOffset][j + xOffset]) {
					return false;
				}
			}
		}
		return true;
	}

bool Board::isCrossedFigureWithWalls(
	const std::vector<std::vector<uint8_t>> &points,
	int xOffset,
	int yOffset) const {
	
	for (auto i = 0; i < points.size(); ++i) {
		for (auto j = 0; j < points[0].size(); ++j) {
			if (!points[i][j])
				continue;
			if ((j + xOffset >= widthBoard) ||
				(j + xOffset < 0) ||
				(i + yOffset >= heightBoard)) {
				return false;
			}
		}
	}
	return true;
}

bool Board::allowMove(Direction direction, const Figure &figure) const {
	const auto& points = figure.points;
	int xOffset = figure.getXOffset();
	int yOffset = figure.getYOffset();
	
	if (direction == Direction::Right) {
		++xOffset;
	} else if (direction == Direction::Left) {
		--xOffset;
	} else if (direction == Direction::Down){
		++yOffset;
	} else {
		std::cerr << "User error: unsupported direction type." << std::endl;
	}
	return
		isCrossedFigureWithBuffer(points, xOffset, yOffset) &&
		isCrossedFigureWithWalls(points, xOffset, yOffset);
}