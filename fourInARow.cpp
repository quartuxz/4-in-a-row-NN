#include "FourInARow.h"
#include <stdexcept>
#include <iostream>

FourInARow::FourInARow()
{
	for (size_t i = 0; i < 7; i++)
	{
		m_board.push_back(std::vector<pieceTypes>());
		for (size_t o = 0; o < 6; o++)
		{
			m_board[i].push_back(empty);
		}
	}
}

void FourInARow::drawToConsole() const
{
	for (size_t i = 0; i < m_board[0].size(); i++)
	{
		for (size_t o = 0; o < m_board.size(); o++)
		{
			
			std::cout << m_board[o][i];
		}
		std::cout << std::endl;
	}
}

bool FourInARow::playSimple(unsigned int xPosition, pieceTypes pieceType)
{
	if (xPosition >= m_board.size()) {
		return false;
	}
	if (m_board[xPosition][0] == empty) {
		for (int o = m_board[xPosition].size() - 1; o >= 0; o--)
		{
			if (m_board[xPosition][o] == empty) {
				m_board[xPosition][o] = pieceType;
				return true;
			}

		}
	}
	return false;
}

endGameTypes FourInARow::play(unsigned int xPosition, pieceTypes pieceType)
{
	endGameTypes retVal = playing;
	if (!playSimple(xPosition, pieceType)) {
		throw std::invalid_argument("column full!");
	}

	for (size_t i = 0; i < m_board.size(); i++)
	{
		if (m_board[i][0] == empty) {
			retVal = playing;
			break;
		}
		else {
			retVal = tie;
		}
	}



	for (size_t i = 0; i < m_board[0].size(); i++)
	{
		for (size_t o = 0; o < m_board.size()-3; o++)
		{
			for (size_t color = 1; color <= 2; color++)
			{
				if (m_board[o][i] == color && m_board[o + 1][i] == color && m_board[o + 2][i] == color && m_board[o + 3][i] == color) {
					retVal = endGameTypes(color);
				}
			}
		}
	}

	for (size_t i = 0; i < m_board.size(); i++)
	{
		for (size_t o = 0; o < m_board[i].size() - 3; o++)
		{
			for (size_t color = 1; color <= 2; color++)
			{
				if (m_board[i][o] == color && m_board[i][o + 1] == color && m_board[i][o + 2] == color && m_board[i][o + 3] == color) {
					retVal = endGameTypes(color);
				}
			}
		}
	}




	for (size_t i = 0; i < m_board.size() - 3; i++)
	{
		for (size_t o = 0; o < m_board[i].size() - 3; o++)
		{
			for (size_t color = 1; color <= 2; color++)
			{
				if (m_board[i][o] == color && m_board[i + 1][o + 1] == color && m_board[i + 2][o + 2] == color && m_board[i + 3][o + 3] == color) {
					retVal = endGameTypes(color);
				}
			}

		}
	}

	for (size_t i = m_board.size() - 1; i >= 3; i--)
	{
		for (size_t o = 0; o < m_board[i].size() - 3; o++)
		{
			for (size_t color = 1; color <= 2; color++)
			{
				if (m_board[i][o] == color && m_board[i - 1][o + 1] == color && m_board[i - 2][o + 2] == color && m_board[i - 3][o + 3] == color) {
					retVal = endGameTypes(color);
				}
			}

		}
	}
	
	return retVal;
}

std::vector<std::vector<pieceTypes>> FourInARow::getBoard() const
{
	return m_board;
}

void FourInARow::setBoard(const std::vector<std::vector<pieceTypes>>&board)
{
	m_board = board;
}
