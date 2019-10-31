#pragma once
#include <vector>

enum pieceTypes {
	empty, blue, red
};

enum endGameTypes {
	playing, blueWin, redWin, tie
};

class FourInARow
{
private:
	std::vector<std::vector<pieceTypes>> m_board;
public:
	FourInARow();

	void drawToConsole()const;

	bool playSimple(unsigned int, pieceTypes);
	endGameTypes play(unsigned int, pieceTypes);
	std::vector<std::vector<pieceTypes> > getBoard()const;
	void setBoard(const std::vector<std::vector<pieceTypes> >&);
};

