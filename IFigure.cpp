#include "IFigure.h"
#include <iostream>

void IFigure::move() {
	std::cout << "I move" << std::endl;
	return;
}

void IFigure::rotate() {
	std::cout << "I rotate" << std::endl;
	return;
}

IFigure::~IFigure() {
	std::cout << "Desctructor of IFigure" << std::endl;
}
