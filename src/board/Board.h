#pragma once

#include <cstdint>
#include <iostream>
#include <memory>
#include <vector>

#include <Singletone.h>
#include <FigureLocal.h>
#include <BoardBase.h>

struct Board final: Singleton<Board>, BoardBase {
	constexpr static uint32_t textColor = 15;
	constexpr static uint32_t bufferFreeSymbol = '.';
	constexpr static uint32_t bufferBusySymbol = '#';
	constexpr static uint32_t levelNumberOfLines = 20;
	
	constexpr static double originTimePeriod = 1.5;
	static uint32_t backGroundColor;
	static double currentTimePeriod;
	
	Board(token) {
	}
	~Board() = default;
	void addFigureToBuffer(const FigureLocal& figure);
	bool verifyLines();
	
	// public for tests
	bool verifyLine(uint32_t numY);
	bool allowRotate(const FigureLocal &figure) const;
	
	std::string getCountOfLinesStr() const noexcept;
	std::string getLevelStr() const noexcept;
	uint32_t getNumberOfErasedLines() const noexcept;
	bool levelIsChanged();
	
private:
	int m_minNoneZeroY = heightBoard;
	uint32_t m_nErasedLines = 0;
	uint32_t m_level = 0;
	bool m_levelIsChanged = false;
	void swapLines(uint32_t i, uint32_t j);
	void resetLine(uint32_t numY);
};

