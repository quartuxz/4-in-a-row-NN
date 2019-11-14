#include <iostream>
#include <algorithm>
#include <time.h>
#include "FourInARow.h"
#include "FourInARowNN.h"
#include "NeuralNetwork.h"
#include "FourInARowMatchMaker.h"


int main() {
	srand(time(NULL));
	Neuron::seedRandomEngine();

	std::vector<unsigned int> NNConfig;
	NNConfig.push_back(126);
	NNConfig.push_back(63);
	NNConfig.push_back(32);
	NNConfig.push_back(16);
	NNConfig.push_back(8);
	NNConfig.push_back(4);
	NNConfig.push_back(2);
	NNConfig.push_back(1);
	FourInARowMatchMaker fourInARowMatchMaker(6, NNConfig, 1, 1000);

	fourInARowMatchMaker.playGivenGenerations(20);


	return 0;

	std::vector<int> tempVec;
	tempVec.push_back(4);
	tempVec.push_back(10);
	tempVec.push_back(2);
	tempVec.push_back(1);
	tempVec.push_back(8);
	std::sort(tempVec.begin(), tempVec.end(), [](auto& left, auto& right) {
		return left > right;
		});
	for (size_t i = 0; i < tempVec.size(); i++)
	{
		std::cout << tempVec[i] << std::endl;
	}


	return 0;

	FourInARowNN FNNRed;
	FNNRed.setNNColor(red);
	FourInARowNN FNNBlue;
	FNNBlue.setNNColor(blue);
	//std::vector<unsigned int> NNConfig;
	NNConfig.push_back(126);
	NNConfig.push_back(63);
	NNConfig.push_back(32);
	NNConfig.push_back(16);
	NNConfig.push_back(8);
	NNConfig.push_back(4);
	NNConfig.push_back(2);
	NNConfig.push_back(1);
	FNNRed.createSynapses(NNConfig);
	FNNBlue.createSynapses(NNConfig);
	FourInARow gameState;

	endGameTypes gameEndState = playing;
	pieceTypes player = blue;
	FourInARowNN* currentNN = &FNNBlue;
	//gameState.drawToConsole();

	while (gameEndState == playing) {
		system("cls");
		gameEndState = gameState.play(currentNN->simulate(gameState), player);
		if (player == blue) {
			currentNN = &FNNRed;
			player = red;
		}
		else if (player == red) {
			currentNN = &FNNBlue;
			player = blue;
		}
		gameState.drawToConsole();
	}
	printGameEndType(gameEndState);
	return 0;

	//unsigned int move = 0;
	//pieceTypes player = blue;

	//FourInARow game;
	//game.drawToConsole();

	//while (true) {
	//	std::cin >> move;
	//	system("cls");
	//	endGameTypes endGameType = game.play(move, player);
	//	if (endGameType != playing) {
	//		if (endGameType == blue) {
	//			std::cout << "BLUE WINS!!" << std::endl;

	//		}
	//		else if (endGameType == red) {
	//			std::cout << "RED WINS!!" << std::endl;
	//		}
	//		else if (endGameType == tie) {
	//			std::cout << "TIE!!" << std::endl;
	//		}
	//	}
	//	if (player == blue) {
	//		player = red;
	//	}
	//	else if (player == red) {
	//		player = blue;
	//	}
	//	game.drawToConsole();

	//}


	return 0;
}