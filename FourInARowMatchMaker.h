#pragma once
#include "FourInARowNN.h"

class FourInARowMatchMaker
{
private:
	std::vector<std::pair<FourInARowNN*,unsigned int>> m_neuralNetworks;
	bool m_displayEverything = true;
	const unsigned int m_mutateChance = 10;
	const unsigned int m_maxMutateChance = 1000;
public:
	//first argument is number of neural networks(an even number is recommended), second is neuron configuration by layer, third is mutate chace, fourth is max mutate chance
	FourInARowMatchMaker(unsigned int, neuronLayerConfig, unsigned int, unsigned int);
	void setDisplayEverything(bool);
	bool getDisplayEverything()const;

	//plug the first and second ID of the playing NNs
	void playOneAgainstAnother(unsigned int, unsigned int);
	void playOneGeneration();
	void playGivenGenerations(unsigned int);
	~FourInARowMatchMaker();
};

