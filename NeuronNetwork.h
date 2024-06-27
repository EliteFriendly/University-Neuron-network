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
	
	
	double errorCombination = 9999999;//Ошибка для сохранения комбинации
	vector<double> bestCombination;//Наилучшие значения для весовых коэффициентов
	vector<double> bestFuncCombo;//Наилучшие значения для функций активации
	void setFuncActivation(vector<double>);
	void changeW(vector<double> w);
	double startTrainDE(vector<double> x, vector<double> y);

public:
	void changeFromFile(string nameFile);
	double getError(vector<double> x, vector<double> y);
	NeuronNetwork(int layerCount, int neuronCount,int inCount);
	void saveSettings(string fileName);
	void startTrainGA(vector<double> x, vector<double> y);
	double getValue(vector<double>);
	
};

