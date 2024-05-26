#pragma once
#include <iostream>
#include <vector>
#include <functional>
#include "Neuron.h"
#include "DiffEvolution.h"
#include "GeneticAlgorithm/Simple_GA.h"
#include <fstream>
#include <ctime>
using namespace std;

class NeuronNetwork
{
private:
	int layerCount;//Количество слоев или строки
	int neuronCount;//Количество нейронов в каждом слое, столбцы
	int inCount;//Количество входящих параметров

	vector<double> outCoef;//Выходные коэффициенты для получения ОДНОГО y
	vector<vector<Neuron>> grid;//Сетка из нейронов
	//Обычное умножение матрицы строки на матрицу столбец, для получения вектора суммы в нейронах, а после использование функции активации нейрона
	vector<double> matrixMulti(vector<Neuron>, vector<double>);
	double funcActivation(double);
	double getError(vector<double> w, vector<double> x, vector<double> y);
	void setFuncActivation(vector<double>);
	
public:
	double startTrainDE(vector<double> x, vector<double> y);
	NeuronNetwork(int layerCount, int neuronCount,int inCount);
	void changeW(vector<double> w);
	void startTrainGA(vector<double> x, vector<double> y);
	double getValue(vector<double>);
	
};

