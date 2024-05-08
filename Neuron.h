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

	void changeW(vector<double> w);
	void replaceFuncActivation(function<double(double)> funcActivationVoid) {funcActivation = funcActivationVoid;}
	vector<double> getW();
};

