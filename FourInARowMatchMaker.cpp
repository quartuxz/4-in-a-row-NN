#include "FourInARowMatchMaker.h"
#include <algorithm>
#include <cmath>
#include <iostream>

FourInARowMatchMaker::FourInARowMatchMaker(unsigned int numberOfNNs, neuronLayerConfig layers, unsigned int mutateChance, unsigned int maxMutateChance):
	m_mutateChance(mutateChance),
	m_maxMutateChance(maxMutateChance)
{
	for (size_t i = 0; i < numberOfNNs; i++)
	{
		FourInARowNN* tempNN = new FourInARowNN();
		tempNN->createSynapses(layers);
		m_neuralNetworks.push_back(std::pair<FourInARowNN*, unsigned int>(tempNN, 0));
	}

}

void FourInARowMatchMaker::setDisplayEverything(bool displayEverything)
{
	m_displayEverything = displayEverything;
}

bool FourInARowMatchMaker::getDisplayEverything() const
{
	return m_displayEverything;
}

void FourInARowMatchMaker::playOneAgainstAnother(unsigned int firstID, unsigned int secondID)
{
	FourInARow game;

	if (rand()%2==0) {
		unsigned int lastFirstID = firstID;
		firstID = secondID;
		secondID = lastFirstID;
	}

	m_neuralNetworks[firstID].first->setNNColor(blue);
	m_neuralNetworks[secondID].first->setNNColor(red);

	endGameTypes playResult = playing;
	pieceTypes nextColor = blue;
	do{
		
		bool isBluePlaying = (nextColor == blue);
		playResult = game.play(m_neuralNetworks[isBluePlaying?firstID:secondID].first->simulate(game), nextColor);
		nextColor = isBluePlaying?red:blue;
		if (m_displayEverything) {
			system("cls");
			game.drawToConsole();
		}
		
	} while (playResult == playing);
	

	if (playResult == tie) {
		m_neuralNetworks[firstID].second++;
		m_neuralNetworks[secondID].second++;
	}
	else {
		bool didBlueWin = (playResult == blueWin);
		m_neuralNetworks[didBlueWin ? firstID : secondID].second += 2;
	}

	

}

void FourInARowMatchMaker::playOneGeneration()
{
	for (size_t i = 0; i < m_neuralNetworks.size(); i++)
	{
		for (size_t o = i; o < m_neuralNetworks.size(); o++)
		{
			if (i!=o) {
				playOneAgainstAnother(i, o);
			}
			
		}
	}
	std::sort(m_neuralNetworks.begin(), m_neuralNetworks.end(), [](auto& left, auto& right) {
		return left.second > right.second;
	});
	system("cls");
	size_t o = 0;
	for (size_t i = std::ceil(m_neuralNetworks.size()/2); i < m_neuralNetworks.size(); i++)
	{
		std::cout << "winners:" << o << ", " << m_neuralNetworks[o].second << "--" << "losers: " << i << ", " << m_neuralNetworks[i].second << std::endl;
		m_neuralNetworks[i].first->createFrom(*m_neuralNetworks[o].first);
		m_neuralNetworks[i].first->mutate(1,1000);
		o++;
		
	}
	for (size_t i = 0; i < m_neuralNetworks.size(); i++)
	{
		m_neuralNetworks[i].second = 0;
	}
}

void FourInARowMatchMaker::playGivenGenerations(unsigned int numberOfGenerations)
{
	for (size_t i = 0; i < numberOfGenerations; i++)
	{
		playOneGeneration();
	}
}

FourInARowMatchMaker::~FourInARowMatchMaker()
{
	for (size_t i = 0; i < m_neuralNetworks.size(); i++)
	{
		delete m_neuralNetworks[i].first;
	}
}
