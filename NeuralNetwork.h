#pragma once
#include <vector>


class Neuron {
public:
	//passes on the outputValue multiplied by the activation function and corresponding synapse weight to the other neuron, where it is added to its own outPutValue ad infinitum.
	void simulate();
	void addOutPutValue(float);
	void setOutPutValueDirect(float);
	float getOutPutValue()const;
	void addOutGoingNeuron(std::pair<Neuron*, float>);

	void mutateSynapses(unsigned int, unsigned int);
	
	void displaySynapseWeightsToConsole()const;

	void setSynapses(std::vector<float>);
	std::vector<float> getSynapses()const;

	~Neuron();
private:
	std::vector<std::pair<Neuron*, float>> m_outGoingNeurons;
	float m_outPutValue;
};

class NeuralNetwork
{
private:
	std::vector<std::vector<Neuron>> m_neurons;
	std::vector<unsigned int> m_neuronConfig;
public:
	//creates neurons and synapses based on another object
	void createFrom(const NeuralNetwork&);
	//mutates the values of the synapses by the given amount
	void mutate(unsigned int, unsigned int);
	//creates random synapses with the provided number of neurons per layer
	void createSynapses(std::vector<unsigned int>);
	//simulates one run of the NN with the given values
	float simulateOnce(std::vector<float>);

	~NeuralNetwork();
};

