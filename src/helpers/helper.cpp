#include <random>
#include <FigureLocal.h>
#include <IFigure.h>
#include <LLFigure.h>
#include <LRFigure.h>
#include <SFigure.h>
#include <ZFigure.h>
#include <TFigure.h>
#include <SQFigure.h>
#include <FigureLocal.h>
#include "helper.h"
#include <iostream>
#include <cassert>

namespace helper {
	uint32_t generateNumber(uint32_t downLimit, uint32_t upLimit) {
		std::random_device rd;
		std::uniform_int_distribution<uint32_t> distribution(downLimit, upLimit);
		return distribution(rd);
	}
	
	void generateFigure(std::unique_ptr<FigureLocal>& figure) {
		uint32_t number = helper::generateNumber(0, 6);
		switch(number) {
			case 0:
				figure.reset(new IFigure);
				break;
			case 1:
				figure.reset(new LLFigure);
				break;
			case 2:
				figure.reset(new LRFigure);
				break;
			case 3:
				figure.reset(new SFigure);
				break;
			case 4:
				figure.reset(new ZFigure);
				break;
			case 5:
				figure.reset(new TFigure);
				break;
			case 6:
				figure.reset(new SQFigure);
				break;
			default:
				std::cerr << "Unsupported type of figure" << std::endl;
				assert(false);
				break;
		}
	}
	
};
