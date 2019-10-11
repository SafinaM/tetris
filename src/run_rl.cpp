#include <thread>
#include <Board.h>
#include <Painter.h>
#include <PainterLocal.h>
#include <helper.h>

// TODO noecho for windows
void noecho() {
	struct termios dt;
	tcgetattr(STDIN_FILENO, &dt);
	dt.c_lflag    &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &dt);
}

void echo() {
	struct termios dt;
	tcgetattr(STDIN_FILENO, &dt);
	dt.c_lflag    |= (ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &dt);
}

int main() {
	std::unique_ptr<Figure> nextFigure;
	std::unique_ptr<Figure> figure;
	Board& board = Board::instance();
	auto start = std::chrono::system_clock::now();
//	PainterLocal& painter = PainterLocal::instance();
	PainterLocal painter;
	painter.hideCursor();
	
	painter.drawHead(" T E T R I S ");
	int ch = getch();
	
	painter.setXY(
		(painter.getWinWidth() - Board::widthBoard) / 2,
		(painter.getWinHeight() - Board::heightBoard) / 2);
	painter.clearScreen();
	painter.drawBoard(board);
	painter.redrawCounters(board);
	
	helper::generateFigure(figure);
	const std::string gameOverStr = " GAME OVER! press Q - to quite! * - to repeate";
	noecho();
	
	while(true) {
		if (ch == 'q')
			break;

		helper::generateFigure(nextFigure);
		nextFigure->setXY(Board::widthBoard + 4, 6);
		painter.drawRectangle(
			painter.xOffsetBoard + Board::widthBoard + 4,
			painter.yOffsetBoard + 6,
			4,
			2);
		figure->setXY(Board::widthBoard / 2 - 1, 0);
		
		while (true) {
			bool wasStopped = false;
			painter.setScreenSize();
			if (ch == 'p') {
				painter.clearScreen();
				painter.drawHead("Pause! Press any key!");
				wasStopped = true;
				ch = getch();
			}
			if (!painter.isSizeOk()) {
				painter.clearScreen();
				painter.drawHead("SMALL WIN SIZE! Press any key!");
				getch();
			}

			if (painter.isScreenSizeChanged() && painter.isSizeOk() || wasStopped) {
				painter.clearScreen();
				painter.setXY(
					(painter.getWinWidth() - Board::widthBoard) / 2,
					(painter.getWinHeight() - Board::heightBoard) / 2);
				painter.drawBoard(board);
				painter.redrawCounters(board);
				
				nextFigure->setXY(Board::widthBoard + 4, 6);
				painter.drawRectangle(
					painter.xOffsetBoard + Board::widthBoard + 4,
					painter.yOffsetBoard + 6,
					4,
					2);
			}

			if (kbhit()) {
				// erase prev figure!!!
				painter.drawFigure(*figure, false, Board::bufferFreeSymbol);
				ch = rlutil::getkey();
				switch (ch) {
					case 'w':
					case rlutil::KEY_UP:
					case rlutil::KEY_SPACE:
						if (board.allowRotate(*figure)) {
							figure->setNextPoints();
						}
						break;
					case 'a':
					case rlutil::KEY_LEFT:
						if (board.allowMove(Direction::Left, *figure)) {
							figure->move(Direction::Left);
						}
						break;
					case 'd':
					case rlutil::KEY_RIGHT:
						if (board.allowMove(Direction::Right, *figure)) {
							figure->move(Direction::Right);
						}
						break;
					case 's':
					case rlutil::KEY_DOWN:
						if (board.allowMove(Direction::Down, *figure)) {
							figure->move(Direction::Down);
						}
						break;
					default:
						break;
				}
			}
			
			if (ch == 'q')
				break;
			
			auto end = std::chrono::system_clock::now();
			std::chrono::duration<double> diff = end-start;
			if (diff.count() > Board::currentTimePeriod) {
				// erase prev figure!!!
				painter.drawFigure(*figure, false, Board::bufferFreeSymbol);
				start = std::chrono::system_clock::now();
				diff.zero();
				if (board.allowMove(Direction::Down, *figure)) {
					figure->move(Direction::Down);
				} else {
					if (figure->getYOffset() <= 0) {
						// game over
						painter.clearScreen();
						painter.drawHead(gameOverStr);
						ch = getch();
						if (ch == 'q')
							break;
						board.clear();
						painter.clearScreen();
						Board::currentTimePeriod = Board::originTimePeriod;
						painter.drawBoard(board);
						painter.redrawCounters(board);
						break;
					}
					board.addFigureToBuffer(*figure);
					painter.drawFigure(*nextFigure, false);
					painter.drawRectangle(
						painter.xOffsetBoard + Board::widthBoard + 4,
						painter.yOffsetBoard + 6,
						4,
						2);
					
					figure = std::move(nextFigure);
					
					painter.drawBoard(board);
					if (board.verifyLines()) {
						if (board.levelIsChanged()) {
							Board::currentTimePeriod -= 0.1;
							Board::backGroundColor = helper::generateNumber(1, 7);
						}
						painter.redrawCounters(board);
						painter.drawBoard(board);
					}
					break;
				}
			}
			painter.drawFigure(*figure);
			painter.drawFigure(*nextFigure);
			
		} // one figure movement
	}     // main cycle
	
	painter.showCursor();
	painter.clearScreen();
	echo();
	
	return 0;
}



