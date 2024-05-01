#pragma once
#include <iostream>
#include <vector>
#include <functional>

using namespace std;

class Neuron
{
private:
	vector<Neuron> in;//Список нейронов входящие в этот нейрон
	vector<double> w;//Весовые коэффициенты входящих нейронов
	double index = 0;//Какой номер выхода
	function <double(double)> funcActivation;//Функция активации
public:
	Neuron() {}
	Neuron(double index) :index(index) {}
	Neuron(const Neuron&);
	Neuron(vector<Neuron> in, function<double(double)> );

	void changeW(vector<double> w);
	double getValue(vector<double>);
};

