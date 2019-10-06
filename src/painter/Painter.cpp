#include "Painter.h"
#include "PainterImpl.h"
#include <cassert>


void Painter::drawFigure(const Figure &figure, bool draw, char symbol) const {
	const auto& points = figure.getPoints();
	assert(!points.empty());
	const int xOffset = figure.getXOffset();
	const int yOffset = figure.getYOffset();
	uint32_t color = 0;
	uint32_t textColor = Board::textColor;
	if (draw) {
		color = figure.getColor();
		textColor = figure.getColor();
	}
	
	for (auto i = 0; i < points.size(); ++i) {
		for (auto j = 0; j < points[0].size(); ++j) {
			if (points[i][j]) {
				assert(j + xOffset + xOffsetBoard >= 0);
				assert(i + yOffset +  yOffsetBoard >= 0);
				drawPoint(
					j + xOffset + xOffsetBoard,
					i + yOffset +  yOffsetBoard,
					symbol,
					color,
					textColor);
			}
		}
		std::cout << std::endl;
	}
}

void Painter::drawBoard(const Board &board) const {
	const auto& buffer = board.buffer;
	for (uint8_t i = 0; i < Board::heightBoard; ++i) {
		for (uint8_t j = 0; j < Board::widthBoard; ++j) {
			// 0 - is Black
			if (!buffer[i][j])
				m_painter->drawPoint(
					j + xOffsetBoard,
					i + yOffsetBoard,
					Board::bufferFreeSymbol,
					0,
					Board::textColor);
			else
				m_painter->drawPoint(
					j + xOffsetBoard,
					i + yOffsetBoard,
					Board::bufferBusySymbol,
					Board::backGroundColor,
					0);
		}
		std::cout << std::endl;
	}
}

void
Painter::printColoredText(const std::string &text, uint32_t x, uint32_t y, uint32_t color, uint32_t textColor) {
	for (auto i = 0; i < text.size(); ++i) {
		m_painter->drawPoint(x + i, y, text[i], color, textColor);
	}
}


void Painter::drawPoint(uint32_t x, uint32_t y, char ch, uint32_t color, uint32_t textColor) const {
	m_painter->drawPoint(x, y, ch, color, textColor);
}

void Painter::clearScreen() const noexcept {
	m_painter->clearScreen();
}

void Painter::hideCursor() const noexcept {
	m_painter->hideCursor();
}

void Painter::showCursor() const {
	m_painter->showCursor();
}

bool Painter::isScreenSizeChanged() noexcept {
	return m_painter->screenSizeChanged;
}

bool Painter::isSizeOk() {
	return m_painter->isSizeOk();
}

void Painter::drawRectangle(
	uint32_t x,
	uint32_t y,
	uint32_t width,
	uint32_t height,
	char ch,
	uint32_t color,
	uint32_t textColor) const {
	
	m_painter->drawRectangle(
		x,
		y,
		width,
		height,
		ch,
		color,
		textColor);
}


void Painter::setScreenSize() {
	m_painter->setScreenSize();
}

uint32_t Painter::getWinWidth() {
	return m_painter->screenWidth;
}

uint32_t Painter::getWinHeight() {
	return m_painter->screenHeight;
}

void Painter::setXY(uint32_t x, uint32_t y) {
	xOffsetBoard = x;
	yOffsetBoard = y;
}

void Painter::drawHead(const std::string &head) noexcept {
	clearScreen();
	printColoredText(
		head,
		getWinWidth() / 2 - head.size() / 2,
		getWinHeight() / 2,
		0,
		2);
}

void Painter::redrawCounters(const Board& board) noexcept {
	printColoredText(
		board.getCountOfLinesStr(),
		xOffsetBoard + Board::widthBoard + 4,
		yOffsetBoard,
		0,
		2);
	
	printColoredText(
		board.getLevelStr(),
		xOffsetBoard + Board::widthBoard + 4,
		yOffsetBoard + 3,
		0,
		2);
	
	printColoredText(
		"Q - quite, P - pause",
		xOffsetBoard + Board::widthBoard + 4,
		yOffsetBoard + 9,
		0,
		2);
}


