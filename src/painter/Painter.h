#pragma once
#include <Board.h>
#include <rlutil.h>
struct InsidePainter {
	
	uint32_t screenWidth = rlutil::tcols();
	uint32_t screenHeight = rlutil::trows();
	
protected:
	const  uint32_t m_minimalWidth = 40;
	const  uint32_t m_minimalHeight = 20;
	void drawPoint(uint32_t x, uint32_t y, char ch, uint32_t color, uint32_t textColor = 0) const;
	void clearScreen() const;
	void setScreenSize();
	void hideCursor() const;
	void showCursor() const;
	void drawRectangle(
		uint32_t x,
		uint32_t y,
		uint32_t width,
		uint32_t height,
		char ch,
		uint32_t,
		uint32_t textColor) const;
	bool screenSizeChanged = false;
};

struct Painter: protected InsidePainter, Singleton<Painter> {
	Painter(token) {
	}
	~Painter() {}
	void drawFigure(const Figure &figure, bool draw = true, char ch = ' ') const;
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
	bool isSizeOk();
	void setXY(uint32_t x, uint32_t y);
	uint32_t getWinWidth();
	uint32_t getWinHeight();
	void drawRectangle(
		uint32_t x,
		uint32_t y,
		uint32_t width,
		uint32_t height,
		char ch = ' ',
		uint32_t color = 0,
		uint32_t textColor = 0) const;
	void drawHead(const std::string &head) noexcept;
	void redrawCounters(const Board& board) noexcept;
	uint32_t xOffsetBoard = 0;
	uint32_t yOffsetBoard = 0;
};

