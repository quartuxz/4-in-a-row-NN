#pragma once
#include <vector>

enum pieceTypes {
	empty, blue, red
};

enum endGameTypes {
	playing, blueWin, redWin, tie
};

void printGameEndType(endGameTypes endGameType);

class FourInARow
{
private:
	std::vector<std::vector<pieceTypes>> m_board;
public:
	FourInARow();

	void drawToConsole()const;

	//gets a representation inputtable into a neural network
	std::vector<float> getPlainRepresantation(pieceTypes);
	//checks wether a given play is legal
	bool canPlay(unsigned int)const;
	//playsthe given play for the given piece color, returns false if play is illegal, doesnt check for victory/defeat/tie
	bool playSimple(unsigned int, pieceTypes);
	//plays the given play for the given piece color, checks for victory/defeat/tie and returns such resultant end game type
	endGameTypes play(unsigned int, pieceTypes);
	//gets a representation easier for a human to read
	std::vector<std::vector<pieceTypes> > getBoard()const;
	//sets the board state
	void setBoard(const std::vector<std::vector<pieceTypes> >&);
};

