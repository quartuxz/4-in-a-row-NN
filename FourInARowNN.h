#pragma once
#include "NeuralNetwork.h"
#include "FourInARow.h"

class FourInARowNN :
	public NeuralNetwork
{
private:
	pieceTypes m_NNColor;
public:
	void setNNColor(pieceTypes);
	pieceTypes getNNColor()const;
	//simulates the best possible play for given board state
	unsigned int simulate(const FourInARow&);

};

