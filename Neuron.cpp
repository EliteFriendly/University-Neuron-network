#include "Neuron.h"



Neuron::Neuron(vector<Neuron> in, function<double(double)> funcActivation):in(in), funcActivation(funcActivation)
{
	w.resize(in.size() + 1);//Создание массива для входящих нейронов +смещение
	for (int i = 0; i < w.size(); i++) {
		w[i] = rand() % 1000 * 0.01;
	}
}


Neuron::Neuron(const Neuron& copy):in(copy.in),w(copy.w),index(copy.index),funcActivation(copy.funcActivation){}



void Neuron::changeW(vector<double> wChange)
{
	for (int i = 0; i < w.size(); i++) {
		w[i] = wChange[i];
	}
}

double Neuron::getValue(vector<double> inGrid)
{
	
	//Если это первый нейрон
	if (w.size() == 0) {
		return inGrid[index];
	}
	double sum = 0;
	//Сумматор
	for (int i = 0; i < w.size() - 1; i++) {
		sum += in[i].getValue(inGrid) * w[i];
	}
	//Добавляется смещение
	sum += w[w.size() - 1];
	//cout << 1;
	return funcActivation(sum);

}
