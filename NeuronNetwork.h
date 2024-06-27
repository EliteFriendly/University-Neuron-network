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
	int layerCount;//���������� ����� ��� ������
	int neuronCount;//���������� �������� � ������ ����, �������
	int inCount;//���������� �������� ����������

	vector<double> outCoef;//�������� ������������ ��� ��������� ������ y
	vector<vector<Neuron>> grid;//����� �� ��������
	//������� ��������� ������� ������ �� ������� �������, ��� ��������� ������� ����� � ��������, � ����� ������������� ������� ��������� �������
	vector<double> matrixMulti(vector<Neuron>, vector<double>);
	double funcActivation(double);
	double getError(vector<double> w, vector<double> x, vector<double> y);
	
	
	double errorCombination = 9999999;//������ ��� ���������� ����������
	vector<double> bestCombination;//��������� �������� ��� ������� �������������
	vector<double> bestFuncCombo;//��������� �������� ��� ������� ���������
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

