#pragma once
#include <iostream>
#include <vector>
#include <functional>

using namespace std;

class Neuron
{
private:
	vector<Neuron> in;//������ �������� �������� � ���� ������
	vector<double> w;//������� ������������ �������� ��������
	double index = 0;//����� ����� ������
	function <double(double)> funcActivation;//������� ���������
public:
	Neuron() {}
	Neuron(double index) :index(index) {}
	Neuron(const Neuron&);
	Neuron(vector<Neuron> in, function<double(double)> );

	void changeW(vector<double> w);
	double getValue(vector<double>);
};

