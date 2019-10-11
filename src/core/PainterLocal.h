#include <Board.h>
#include <Painter.h>

struct PainterLocal: Painter {
	static std::unique_ptr<PainterLocal> createPainter();
	~PainterLocal() = default;
	void drawFigure(const Figure &figure, bool draw = true, char ch = ' ') const;
	void drawBoard(const Board &board) const;
	void redrawCounters(const Board& board) noexcept;

private:
	PainterLocal() = default;
};
