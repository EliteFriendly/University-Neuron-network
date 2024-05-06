#include "Neuron.h"



Neuron::Neuron(function<double(double)> funcActivation, int ammountNeuronLayer):funcActivation(funcActivation)
{
	w.resize(ammountNeuronLayer + 1);//Создание массива для входящих нейронов +смещение
	for (int i = 0; i < w.size(); i++) {
		w[i] = rand() % 1000 * 0.01;
	}
}


Neuron::Neuron(const Neuron& copy):w(copy.w),funcActivation(copy.funcActivation){}



void Neuron::changeW(vector<double> wChange)
{
	for (int i = 0; i < w.size(); i++) {
		w[i] = wChange[i];
	}
}

vector<double> Neuron::getW()
{
	return w;
}
