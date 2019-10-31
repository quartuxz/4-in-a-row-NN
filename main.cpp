#include <iostream>
#include "FourInARow.h"
#include "NeuralNetwork.h"

int main() {
	NeuralNetwork NN;
	std::vector<unsigned int> NNConfig;
	NNConfig.push_back(2);
	NNConfig.push_back(1);
	NNConfig.push_back(1);
	NN.createSynapses(NNConfig);
	std::vector<float> inputs;
	inputs.push_back(2);
	inputs.push_back(10);
	std::cout << NN.simulateOnce(inputs) << std::endl;
	return 0;

	unsigned int move = 0;
	pieceTypes player = blue;

	FourInARow game;
	game.drawToConsole();

	while (true) {
		std::cin >> move;
		system("cls");
		endGameTypes endGameType = game.play(move, player);
		if (endGameType != playing) {
			if (endGameType==blue) {
				std::cout << "BLUE WINS!!" << std::endl;

			}
			else if (endGameType == red) {
				std::cout << "RED WINS!!" << std::endl;
			}
			else if (endGameType == tie) {
				std::cout << "TIE!!" << std::endl;
			}
		}
		if (player == blue) {
			player = red;
		}
		else if (player== red) {
			player = blue;
		}
		game.drawToConsole();
		
	}


	return 0;
}