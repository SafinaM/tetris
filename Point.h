#pragma once

struct Point {
	int x = 0;
	int y = 0;
	Point(int x = 0, int y = 0) : x(x), y(y) {}

	Point& operator+=(const Point& other) {
		x += other.x;
		y += other.y;
		return *this;
	}

	Point& operator-=(const Point& other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}
};