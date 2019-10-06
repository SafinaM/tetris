#pragma once
#include <rlutil.h>

struct PainterImpl {
	PainterImpl() = default;
	~PainterImpl() = default;
	
	uint32_t screenWidth = rlutil::tcols();
	uint32_t screenHeight = rlutil::trows();
	const  uint32_t m_minimalWidth = 40;
	const  uint32_t m_minimalHeight = 20;
	void drawPoint(
		uint32_t x,
		uint32_t y,
		char ch,
		uint32_t color,
		uint32_t textColor = 0) const;
	void clearScreen() const noexcept;
	void setScreenSize() noexcept;
	void hideCursor() const noexcept;
	void showCursor() const noexcept;
	bool isSizeOk() const noexcept;
	void drawRectangle(
		uint32_t x,
		uint32_t y,
		uint32_t width,
		uint32_t height,
		char ch,
		uint32_t,
		uint32_t textColor) const noexcept;
	bool screenSizeChanged = false;
};
