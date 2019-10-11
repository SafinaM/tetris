#pragma once
#include <PainterImpl.h>
#include <memory>

struct Painter {
	Painter() : m_painter(new PainterImpl) {}
	~Painter() = default;

	
	void printColoredText(
		const std::string &text,
		uint32_t x,
		uint32_t y,
		uint32_t color,
		uint32_t textColor);
	bool isScreenSizeChanged() noexcept;
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
	void drawPoint(uint32_t x, uint32_t y, char ch, uint32_t color, uint32_t textColor = 0) const;
	void clearScreen() const noexcept ;
	void hideCursor() const noexcept;
	void showCursor() const;
	void setScreenSize();
	void drawHead(const std::string &head) noexcept;
	uint32_t xOffsetBoard = 0;
	uint32_t yOffsetBoard = 0;
	
private:
	std::unique_ptr<PainterImpl> m_painter;
};

