#include "Painter.h"

void Painter::drawFigure(const Figure& figure, bool draw) {
	const auto& points = figure.getPoints();
	assert(!points.empty());
	clearScreen();
	const int xOffset = figure.getYOffset();
	const int yOffset = figure.getYOffset();
	uint32_t color = 0;
	if (draw)
		color = figure.getColor();
	for (auto i = 0; i < points.size(); ++i) {
		for (auto j = 0; j < points[0].size(); ++j) {
			if (points[i][j]) {
				assert(j + xOffset >= 0);
				assert(i + yOffset >= 0);
				// 4 - is Red
				drawPoint(j + xOffset, i + yOffset, color);
			}
		}
		std::cout << std::endl;
	}
}

void Painter::drawBoard(const Board& board) {
	const auto& buffer = board.buffer;
	for (uint8_t i = 0; i < Board::heightBoard; ++i) {
		for (uint8_t j = 0; j < Board::widthBoard; ++j) {
			// 0 - is Black
			drawPoint(j, i, 0);
		}
		std::cout << std::endl;
	}
}

void InsidePainter::drawPoint(uint32_t x, uint32_t y, uint32_t color) {
	rlutil::locate(x, y);
	rlutil::setBackgroundColor(color);
	std::cout << ' ';
	rlutil::resetColor();
}

void InsidePainter::clearScreen() {
	rlutil::cls();
}

void InsidePainter::paintOver() {
	const auto width = rlutil::tcols();
	const auto height = rlutil::trows();
	for (auto i = 0; i < width; ++i) {
		for (auto j = 0; j < height; ++j) {
			drawPoint(j, i, 0);
		}
	}
}