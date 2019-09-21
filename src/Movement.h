#pragma once

#include <cstdint>
#include "Figure.h"

struct Movement {
	Movement() = default;
	~Movement() = default;
	void moveRight() noexcept;
	void moveLeft() noexcept;
	void moveDown() noexcept;
	void set(uint32_t x, uint32_t y) noexcept;
	int getXOffset() const noexcept;
	int getYOffset() const noexcept;
	void reset() noexcept;
	
private:
	int m_offsetX = 0;
	int m_offsetY = 0;
};


