#include <thread>
#include "Board.h"
#include "assert.h"



// yellow
uint32_t Board::backGroundColor = 6;
double Board::currentTimePeriod = originTimePeriod;


void Board::addFigureToBuffer(const FigureLocal& figure) {
	const auto& points = figure.getPoints();
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
	m_levelIsChanged = false;
	for (auto i = m_minNoneZeroY; i < heightBoard; ++i) {
		// erase full line and insert empty line at the begin of vector - not effective way
		if (verifyLine(i)) {
			++m_nErasedLines;
			resetLine(i);
			// lower all lines one level below
			for (auto k = i; k > m_minNoneZeroY; --k) {
				swapLines(k, k - 1);
			}
			foundAtLeastOneFilledLine = true;
			// line was erased, the with non zero number is decreased
			++m_minNoneZeroY;
			if (m_nErasedLines % Board::levelNumberOfLines == 0) {
				++m_level;
				m_levelIsChanged = true;
			}
		}
	}
	
	if (foundAtLeastOneFilledLine) {
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}
	return foundAtLeastOneFilledLine;
}

std::string Board::getCountOfLinesStr() const noexcept {
	
	return std::move(std::string("Lines: ") + std::to_string(m_nErasedLines));
}

std::string Board::getLevelStr() const noexcept {
	
	return std::move(std::string("Level: ") + std::to_string(m_level));
}

uint32_t Board::getNumberOfErasedLines() const noexcept {
	return m_nErasedLines;
}

bool Board::verifyLine(uint32_t numY) {
	assert(numY >= 0 && numY < heightBoard);
		for (auto j = 0; j < widthBoard; ++j) {
			if (!buffer[numY][j])
				return false;
	}
	return true;
}

bool Board::levelIsChanged() {
	return m_levelIsChanged;
}

void Board::swapLines(uint32_t i, uint32_t j) {
	std::swap(buffer[i], buffer[j]);
}

void Board::resetLine(uint32_t numY) {
	for (uint32_t j = 0; j < widthBoard; ++j) {
		buffer[numY][j] = 0;
	}
}

bool Board::allowRotate(const FigureLocal &figure) const {
	Orientation orientation = figure.getNextOrientationType();
	auto points = figure.getPoints(orientation);
	uint32_t xOffset = figure.getXOffset();
	uint32_t yOffset = figure.getYOffset();
	
	return
		isCrossedFigureWithBuffer(points, xOffset, yOffset) &&
		isCrossedFigureWithWalls(points, xOffset, yOffset);
}

