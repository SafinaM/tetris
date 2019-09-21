#pragma once
#include <cstdint>
#include <iostream>
#include <memory>
#include <vector>

#include "Singletone.h"
#include "Figure.h"

struct Board final: Singleton<Board> {

	constexpr static uint32_t widthBoard = 10;
	constexpr static uint32_t heightBoard = 20;
	std::vector<std::vector<uint8_t>> buffer;
	uint32_t m_lastChangedY = 0;
	
	Board(token) {
		// matrix of size width x height initialized by 0
		std::vector<std::vector<uint8_t>> tmp(heightBoard, std::vector<uint8_t>(widthBoard, 0));
		std::swap(buffer, tmp);
	}
	~Board() {}
	
	void debugPrint() const;
	
	void addFigureToBuffer(const Figure& figure, const Movement& movement);
	bool verifyLine(uint32_t numY);
	void verifyLines();
};

