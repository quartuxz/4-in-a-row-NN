#include "NeuralNetwork.h"
#include <cmath>
#include <iostream>
#include <time.h>


std::default_random_engine Neuron::m_engine = std::default_random_engine();

void Neuron::seedRandomEngine()
{
	m_engine.seed(time(NULL));
}

void NeuralNetwork::createFrom(const NeuralNetwork &other)
{

	createSynapses(other.m_neuronConfig);
	for (size_t i = 0; i < m_neurons.size(); i++)
	{
		for (size_t o = 0; o < m_neurons[i].size(); o++)
		{
			m_neurons[i][o]->setSynapses(other.m_neurons[i][o]->getSynapses());
		}
	}
}

void NeuralNetwork::mutate(unsigned int amountRange, unsigned int dividedBy)
{
	
	for (size_t i = 0; i < m_neurons.size(); i++)
	{
		for (size_t o = 0; o < m_neurons[i].size(); o++)
		{
			m_neurons[i][o]->mutateSynapses(amountRange, dividedBy);
		}
	}
}

void NeuralNetwork::createSynapses(neuronLayerConfig layers)
{

	m_neurons.clear();
	m_neuronConfig = layers;
	const unsigned int detail = 1000;
	
	std::uniform_int_distribution<int> range(-int(detail), detail);
	for (size_t i = 0; i < layers.size(); i++)
	{
		m_neurons.push_back(std::vector<Neuron*>());
		std::vector<Neuron*> thisLayerNeurons;
		for (size_t o = 0; o < layers[i]; o++)
		{
			
			m_neurons[i].push_back(new Neuron());
			thisLayerNeurons.push_back(m_neurons[i].back());
		}
		if (i > 0) {
			for (size_t o = 0; o < m_neurons[i-1].size(); o++)
			{
				for (size_t p = 0; p < thisLayerNeurons.size(); p++)
				{
					m_neurons[i - 1][o]->addOutGoingNeuron(std::pair<Neuron*, float>(thisLayerNeurons[p], float(range(Neuron::m_engine)) / detail));
				}
				
			}
		}

	}
}

float NeuralNetwork::simulateOnce(std::vector<float> input)
{
	for (size_t i = 0; i < m_neurons[0].size(); i++)
	{
		m_neurons[0][i]->setOutPutValueDirect(input[i]);
	}

	for (size_t i = 0; i < m_neurons.size() - 1; i++)
	{
		for (size_t o = 0; o < m_neurons[i].size(); o++)
		{
			m_neurons[i][o]->simulate();
			//std::cout << m_neurons[i][o].getOutPutValue() << std::endl;
			//m_neurons[i][o].displaySynapseWeightsToConsole();
			m_neurons[i][o]->setOutPutValueDirect(0);
		}
	}
	float retVal = m_neurons.back().back()->getOutPutValue();
	m_neurons.back().back()->setOutPutValueDirect(0);
	return retVal;
}

void NeuralNetwork::saveToFile(std::string) const
{
}

void NeuralNetwork::readFromFile(std::string)
{
}

NeuralNetwork::~NeuralNetwork()
{
	for (size_t i = 0; i < m_neurons.size(); i++)
	{
		for (size_t o = 0; o < m_neurons[i].size(); o++)
		{
			delete m_neurons[i][o];
		}
	}
}

void Neuron::simulate()
{
	for (size_t i = 0; i < m_outGoingNeurons.size(); i++)
	{
		m_outGoingNeurons[i].first->addOutPutValue(getOutPutValue() *m_outGoingNeurons[i].second);
	}
}

void Neuron::addOutPutValue(float outPutValue)
{
	m_outPutValue += outPutValue;
}

void Neuron::setOutPutValueDirect(float outPutValue)
{
	m_outPutValue = outPutValue;
}

float Neuron::getOutPutValue() const
{
	return	(1 / (1 + pow(std::exp(1), -m_outPutValue)));
}

void Neuron::addOutGoingNeuron(std::pair<Neuron*, float> outGoingNeuron)
{
	m_outGoingNeurons.push_back(outGoingNeuron);
}

void Neuron::mutateSynapses(unsigned int amountRange, unsigned int dividedBy)
{
	std::uniform_int_distribution<int> range(-int(amountRange), amountRange);
	for (size_t i = 0; i < m_outGoingNeurons.size(); i++)
	{
		m_outGoingNeurons[i].second += range(m_engine) / dividedBy;
	}
}

void Neuron::displaySynapseWeightsToConsole() const
{
	std::cout << "(";
	for (size_t i = 0; i < m_outGoingNeurons.size(); i++)
	{
		
		std::cout << m_outGoingNeurons[i].second;
	}
	std::cout << ")" << std::endl;
}

void Neuron::setSynapses(std::vector<float> synapseWeights)
{
	for (size_t i = 0; i < m_outGoingNeurons.size(); i++)
	{
		m_outGoingNeurons[i].second = synapseWeights[i];
	}
}

std::vector<float> Neuron::getSynapses() const
{
	std::vector<float> retVal;
	for (size_t i = 0; i < m_outGoingNeurons.size(); i++)
	{
		retVal.push_back(m_outGoingNeurons[i].second);
	}
	return retVal;
}

Neuron::~Neuron()
{
}
