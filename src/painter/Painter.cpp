#include "Painter.h"
#include "PainterImpl.h"
#include <cassert>

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



