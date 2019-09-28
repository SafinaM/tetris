#include "Painter.h"
#include <cassert>


void Painter::drawFigure(const Figure& figure, const uint32_t xOffsetOrigin, const uint32_t yOffsetOrigin, bool draw) const {
	const auto& points = figure.getPoints();
	assert(!points.empty());
//	clearScreen();
	const int xOffset = figure.getXOffset();
	const int yOffset = figure.getYOffset();
	uint32_t color = 0;
	uint32_t textColor = Board::textColor;
	char symbol = Board::bufferFreeSymbol;
	if (draw) {
		color = figure.getColor();
		textColor = figure.getColor();
		symbol = Board::figureSymbol;
	}
	
	for (auto i = 0; i < points.size(); ++i) {
		for (auto j = 0; j < points[0].size(); ++j) {
			if (points[i][j]) {
				assert(j + xOffset + xOffsetOrigin >= 0);
				assert(i + yOffset +  yOffsetOrigin >= 0);
				// 4 - is Red
				drawPoint(j + xOffset + xOffsetOrigin, i + yOffset +  yOffsetOrigin, symbol, color, textColor);
			}
		}
		std::cout << std::endl;
	}
}

void Painter::drawBoard(const Board &board, const uint32_t xOffset, const uint32_t yOffset) const {
	const auto& buffer = board.buffer;
	for (uint8_t i = 0; i < Board::heightBoard; ++i) {
		for (uint8_t j = 0; j < Board::widthBoard; ++j) {
			// 0 - is Black
			if (!buffer[i][j])
				InsidePainter::drawPoint(
					j + xOffset,
					i + yOffset,
					Board::bufferFreeSymbol,
					0,
					Board::textColor);
			else
				InsidePainter::drawPoint(
					j + xOffset,
					i + yOffset,
					Board::bufferBusySymbol,
					Board::backGroundColor,
					0);
		}
		std::cout << std::endl;
	}
}

void InsidePainter::drawPoint(uint32_t x, uint32_t y, char ch, uint32_t color, uint32_t textColor) const {
	rlutil::locate(x, y);
	rlutil::setColor(textColor);
	rlutil::setBackgroundColor(color);
	std::cout << ch;
	rlutil::resetColor();
}

void InsidePainter::clearScreen() const {
	rlutil::cls();
}

void InsidePainter::paintOver() const {
	const auto width = rlutil::tcols();
	const auto height = rlutil::trows();
	for (auto i = 0; i < height; ++i) {
		for (auto j = 0; j < width; ++j) {
			drawPoint(j, i, ' ', 0, 0);
		}
	}
}

void Painter::drawPoint(uint32_t x, uint32_t y, char ch, uint32_t color, uint32_t textColor) const {
	InsidePainter::drawPoint(x, y, ch, color, textColor);
}

void Painter::clearScreen() const {
	InsidePainter::clearScreen();
}

void Painter::paintOver() const {
	InsidePainter::paintOver();
}

void InsidePainter::setScreenSize() {
	screenWidth = rlutil::tcols();
	screenHeight = rlutil::trows();
}

void Painter::setScreenSize() {
	InsidePainter::setScreenSize();
}

uint32_t Painter::getScreenWidth() {
	return InsidePainter::screenWidth;
}

uint32_t Painter::getScreenHeight() {
	return InsidePainter::screenHeight;
}