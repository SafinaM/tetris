#include <PainterLocal.h>
#include <cassert>

void PainterLocal::redrawCounters(const Board& board) noexcept {
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

void PainterLocal::drawFigure(const Figure &figure, bool draw, char symbol) const noexcept {
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

void PainterLocal::drawBoard(const Board &board) const noexcept{
	const auto& buffer = board.buffer;
	for (uint8_t i = 0; i < Board::heightBoard; ++i) {
		for (uint8_t j = 0; j < Board::widthBoard; ++j) {
			// 0 - is Black
			if (!buffer[i][j])
				drawPoint(
					j + xOffsetBoard,
					i + yOffsetBoard,
					Board::bufferFreeSymbol,
					0,
					Board::textColor);
			else
				drawPoint(
					j + xOffsetBoard,
					i + yOffsetBoard,
					Board::bufferBusySymbol,
					Board::backGroundColor,
					0);
		}
		std::cout << std::endl;
	}
}
