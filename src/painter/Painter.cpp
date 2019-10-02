#include "Painter.h"
#include <cassert>


void Painter::drawFigure(const Figure& figure, bool draw) const {
	const auto& points = figure.getPoints();
	assert(!points.empty());
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
				assert(j + xOffset + xOffsetBoard >= 0);
				assert(i + yOffset +  yOffsetBoard >= 0);
				// 4 - is Red
				drawPoint(j + xOffset + xOffsetBoard, i + yOffset +  yOffsetBoard, symbol, color, textColor);
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
				InsidePainter::drawPoint(
					j + xOffsetBoard,
					i + yOffsetBoard,
					Board::bufferFreeSymbol,
					0,
					Board::textColor);
			else
				InsidePainter::drawPoint(
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
			InsidePainter::drawPoint(x + i, y, text[i], color, textColor);
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

void Painter::drawPoint(uint32_t x, uint32_t y, char ch, uint32_t color, uint32_t textColor) const {
	InsidePainter::drawPoint(x, y, ch, color, textColor);
}

void Painter::clearScreen() const {
	InsidePainter::clearScreen();
}

void Painter::hideCursor() const {
	InsidePainter::hideCursor();
}

void Painter::showCursor() const {
	InsidePainter::showCursor();
}

void InsidePainter::setScreenSize() {
	if (screenWidth != rlutil::tcols() || screenHeight != rlutil::trows()) {
		screenWidth = rlutil::tcols();
		screenHeight = rlutil::trows();
		screenSizeChanged = true;
	} else
		screenSizeChanged = false;
}

bool Painter::isScreenSizeChanged() {
	return screenSizeChanged;
}

void InsidePainter::hideCursor() const {
	rlutil::hidecursor();
}
void InsidePainter::showCursor() const {
	rlutil::showcursor();
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

void Painter::setXY(uint32_t x, uint32_t y) {
	xOffsetBoard = x;
	yOffsetBoard = y;
}
