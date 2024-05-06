#pragma once
#include <iostream>
#include <vector>
#include <functional>

using namespace std;

class Neuron
{
private:
	vector<double> w;//Весовые коэффициенты входящих нейронов
	function <double(double)> funcActivation;//Функция активации
public:
	Neuron() {}
	Neuron(const Neuron&);
	Neuron(function<double(double)>, int);

	double useFuncActivation(double x) { return funcActivation(x); }

	void changeFuncActivation(function<double(double)> funcIn) { funcActivation = funcIn; }
	void changeW(vector<double> w);
	vector<double> getW();
};

