#pragma once

#include <memory>

namespace helper {
	uint32_t generateNumber(uint32_t downLimit, uint32_t upLimit);
	void generateFigure(std::unique_ptr<Figure>& figure);
};
