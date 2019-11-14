#include "FourInARowNN.h"
#include <limits>

void FourInARowNN::setNNColor(pieceTypes pieceType)
{
	m_NNColor = pieceType;
}

pieceTypes FourInARowNN::getNNColor() const
{
	return m_NNColor;
}

unsigned int FourInARowNN::simulate(const FourInARow &gameState)
{
	unsigned int bestPlay = 0;
	float lastBestNNValue = std::numeric_limits<float>::min();
	for (size_t i = 0; i < gameState.getBoard().size(); i++)
	{
		if (gameState.canPlay(i)) {
			FourInARow tempGameState = gameState;
			tempGameState.playSimple(i, m_NNColor);
			float thisNNValue = simulateOnce(tempGameState.getPlainRepresantation(m_NNColor));
			if (thisNNValue > lastBestNNValue) {
				lastBestNNValue = thisNNValue;
				bestPlay = i;
			}
		}
	}
	return bestPlay;
}
