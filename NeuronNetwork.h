#pragma once
#include <iostream>
#include <vector>
#include <functional>
#include "Neuron.h"

using namespace std;

class NeuronNetwork
{
private:
	int layerCount;//���������� ����� ��� ���������� �������� �� �������
	int neuronCount;//���������� �������� � ������ ����
	int inCount;//���������� �������� ����������
	vector<vector<Neuron>> grid;//����� �� ��������� ��������
	vector<Neuron> in;//�����

	double funcActivation(double);
public:
	NeuronNetwork(int layerCount, int neuronCount,int inCount);

	double getValue(vector<double>);
	void changeW();

};

