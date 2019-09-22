#include <thread>
#include "Board.h"
#include "assert.h"

void Board::debugPrint() const {
	for (uint8_t i = 0; i < heightBoard; ++i) {
		for (uint8_t j = 0; j < widthBoard; ++j) {
			std::cout << +buffer[i][j];
		}
		std::cout << std::endl;
	}
}

void Board::addFigureToBuffer(const Figure& figure) {
	const auto& points = figure.points;
	uint32_t xOffset = figure.getXOffset();
	uint32_t yOffset = figure.getYOffset();
	assert(xOffset < widthBoard);
	assert(yOffset >= 0 && yOffset < heightBoard);
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

void Board::verifyLines() {
	bool wasDeleted = false;
	for (auto i = m_minNoneZeroY; i < heightBoard; ++i) {
		// erase full line and insert empty line at the begin of vector - not effective way
		if (verifyLine(i)) {
			resetLine(i);
			// lower all lines one level below
			for (auto k = i; k > m_minNoneZeroY; --k) {
				swapLines(k, k - 1);
			}
			wasDeleted = true;
			// line was erased, the with non zero number is decreased
			++m_minNoneZeroY;
		}
	}
	
	if (wasDeleted)
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
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