#include "Movement.h"

void Movement::moveRight() noexcept {
	++m_offsetX;
}

void Movement::moveLeft() noexcept {
	--m_offsetX;
}

void Movement::moveDown() noexcept {
	++m_offsetY;
}

int Movement::getXOffset() const noexcept {
	return m_offsetX;
}

int Movement::getYOffset() const noexcept {
	return m_offsetY;
}

void Movement::reset() noexcept {
	m_offsetX = 0;
	m_offsetY = 0;
}