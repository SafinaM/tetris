#pragma once
#include <Board.h>
#include <rlutil.h>
struct InsidePainter {
	// standard ubuntu terminal size
	uint32_t screenWidth = 80;
	uint32_t screenHeight = 24;
protected:
	void drawPoint(uint32_t x, uint32_t y, char ch, uint32_t color, uint32_t textColor = 0) const;
	void clearScreen() const;
	void setScreenSize();
	void hideCursor() const;
	void showCursor() const;
	bool screenSizeChanged = false;
};

struct Painter: protected InsidePainter, Singleton<Painter> {
	Painter(token) {
	}
	~Painter() {}
	void drawFigure(const Figure& figure, bool draw = true) const;
	void drawBoard(const Board &board) const;
	void drawPoint(uint32_t x, uint32_t y, char ch, uint32_t color, uint32_t textColor = 0) const;
	void clearScreen() const;
	void hideCursor() const;
	void showCursor() const;
	void setScreenSize();
	void printColoredText(
		const std::string &text,
		uint32_t x,
		uint32_t y,
		uint32_t color,
		uint32_t textColor);
	bool isScreenSizeChanged();
	void setXY(uint32_t x, uint32_t y);
	uint32_t getScreenWidth();
	uint32_t getScreenHeight();
	uint32_t xOffsetBoard = 0;
	uint32_t yOffsetBoard = 0;
};

