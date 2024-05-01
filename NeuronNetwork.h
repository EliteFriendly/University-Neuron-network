#pragma once
#include <iostream>
#include <vector>
#include <functional>
#include "Neuron.h"

using namespace std;

class NeuronNetwork
{
private:
	int layerCount;//Количество слоев или количество столбцов по другому
	int neuronCount;//Количество нейронов в каждом слое
	int inCount;//Количество входящих параметров
	vector<vector<Neuron>> grid;//Сетка из связанных нейронов
	vector<Neuron> in;//Входы

	double funcActivation(double);
public:
	NeuronNetwork(int layerCount, int neuronCount,int inCount);

	double getValue(vector<double>);
	void changeW();

};

