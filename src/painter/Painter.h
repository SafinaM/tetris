#pragma once
#include <Board.h>
#include <cassert>
#include <rlutil.h>
struct InsidePainter {
	void drawPoint(uint32_t x, uint32_t y, uint32_t color);
	void clearScreen();
	void paintOver();
};

struct Painter: InsidePainter {
	void drawFigure(const Figure& figure, bool draw = true);
	void drawBoard(const Board& board);

private:
	virtual void drawPoint(uint32_t x, uint32_t y, uint32_t color);
	virtual void clearScreen();
	virtual void paintOver();
};


