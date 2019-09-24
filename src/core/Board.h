#pragma once
#include <cstdint>
#include <iostream>
#include <memory>
#include <vector>

#include <Singletone.h>
#include <Figure.h>

struct Board final: Singleton<Board> {

	constexpr static uint32_t widthBoard = 10;
	constexpr static uint32_t heightBoard = 20;
	uint8_t buffer[heightBoard][widthBoard] = {};
	uint32_t m_minNoneZeroY = heightBoard;
	
	Board(token) {
	}
	~Board() {}
	void addFigureToBuffer(const Figure& figure);
	void debugPrint() const;
	void verifyLines();
	// for debug
	void setLine(uint32_t numY, uint32_t value = 1);
	void setPoint(uint32_t x, uint32_t y, uint32_t value = 1);
	// public for tests
	bool verifyLine(uint32_t numY);
	
	bool allowMove(Direction direction, const Figure &figure) const;
	bool allowRotate(const Figure &figure) const;
	
private:
	void swapLines(uint32_t i, uint32_t j);
	void resetLine(uint32_t numY);
	bool isCrossedFigureWithBuffer(
		const std::vector<std::vector<uint8_t>> &points,
		int xOffset,
		int yOffset) const;
	bool isCrossedFigureWithWalls(
		const std::vector<std::vector<uint8_t>> &points,
		int xOffset,
		int yOffset) const;
};
