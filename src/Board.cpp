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

void Board::addFigureToBuffer(const Figure& figure, const Movement& movement) {
	const auto& points = figure.points;
	uint32_t xOffset = movement.getXOffset();
	uint32_t yOffset = movement.getYOffset();
	m_lastChangedY = yOffset;
	assert(xOffset < widthBoard);
	assert(yOffset >= 0 && yOffset < heightBoard);
	for (auto i = 0; i < points.size(); ++i) {
		for (auto j = 0; j < points[0].size(); ++j) {
			if (points[i][j]) {
				assert(!buffer[i + yOffset][j + xOffset]);
				buffer[i + yOffset][j + xOffset] = points[i][j];
			}
		}
	}
}

void Board::verifyLines() {
	std::cout << "lastChangedY = " << m_lastChangedY << std::endl;
	// max height of figure is 4
	const uint32_t maxOfFigure = 4;
	bool wasDeleted = false;
	// verify only last changed y and yet 4 lines
	for (auto i = m_lastChangedY; i < maxOfFigure + maxOfFigure; ++i) {
		if (i >= heightBoard) {
			break;
		}
		// erase full line and insert empty line at the begin of vector
		// TODO replace it on faster way without allocation!!!
		if (verifyLine(i)) {
			buffer.erase(buffer.begin() + i);
			buffer.insert(buffer.begin(), std::vector<uint8_t>(widthBoard, 0));
			wasDeleted = true;
		}
	}
	
	if (wasDeleted)
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

bool Board::verifyLine(uint32_t numY) {
	assert(numY >= 0 && numY < heightBoard);
	auto width = buffer[m_lastChangedY].size();
		for (auto j = 0; j < widthBoard; ++j) {
			if (!buffer[numY][j])
				return false;
	}
	return true;
}
