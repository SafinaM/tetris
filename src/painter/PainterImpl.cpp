#include "PainterImpl.h"


void PainterImpl::drawRectangle(
	uint32_t x,
	uint32_t y,
	uint32_t width,
	uint32_t height,
	char ch,
	uint32_t color,
	uint32_t textColor) const noexcept {
	
	for (uint32_t i = y; i < y + height; ++i) {
		for (uint32_t j = x; j < x + width; ++j) {
			drawPoint(j, i, ch, color, textColor);
		}
	}
}

void PainterImpl::hideCursor() const noexcept {
	rlutil::hidecursor();
}
void PainterImpl::showCursor() const noexcept{
	rlutil::showcursor();
}

void PainterImpl::drawPoint(uint32_t x, uint32_t y, char ch, uint32_t color, uint32_t textColor) const {
	rlutil::locate(x, y);
	rlutil::setColor(textColor);
	rlutil::setBackgroundColor(color);
	std::cout << ch;
	rlutil::resetColor();
}

void PainterImpl::clearScreen() const noexcept {
	rlutil::cls();
}

bool PainterImpl::isSizeOk() const noexcept {
	return screenWidth >= m_minimalWidth && screenHeight >= m_minimalHeight;
}

void PainterImpl::setScreenSize() noexcept {
	if (screenWidth != rlutil::tcols() || screenHeight != rlutil::trows()) {
		screenWidth = rlutil::tcols();
		screenHeight = rlutil::trows();
		screenSizeChanged = true;
	} else
		screenSizeChanged = false;
}

