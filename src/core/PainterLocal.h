#include <Board.h>
#include <Painter.h>

struct PainterLocal: Painter, Singleton<PainterLocal> {
	PainterLocal(token) {};
	~PainterLocal() = default;
	void drawFigure(const Figure &figure, bool draw = true, char ch = ' ') const noexcept;
	void drawBoard(const Board &board) const noexcept;
	void redrawCounters(const Board& board) noexcept;
};
