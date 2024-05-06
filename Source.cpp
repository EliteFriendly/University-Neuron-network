#include <iostream>
#include <vector>
#include <functional>
#include "NeuronNetwork.h"
using namespace std;


double func(double x) {
	return -7 * sin(x) + 10 * exp(cos(x)) + 0.8 * x;
}


void main() {

	srand(10);
	//Формирование выборки для обучения
	int ammount = 100;//Количество точен
	int i1 = 0;//Счетчики
	int i2 = 0;
	double left = 0;
	double right = 10;
	double h = (right - left) / ammount;
	vector<double> xTrain(int(0.75 * ammount));
	vector<double> yTrain(int(0.75 * ammount));
	vector<double> xTest(int(0.25 * ammount));
	vector<double> yTest(int(0.25 * ammount));
	for (int i = 0; i < ammount; i++) {
		if (i % 4 != 0) {
			xTrain[i1] = left + i * h;
			yTrain[i1] = func(xTrain[i1]);
			i1++;
		}
		else {
			xTest[i2] = left + i * h;
			yTest[i2] = func(xTest[i2]);
			i2++;
		}
	}



	//Начало
	vector<double> xOne(1);
	xOne[0] = xTest[0];
	NeuronNetwork proba(3, 3, 1);
	proba.startTrain(xTrain, yTrain);
	cout<<proba.getValue(xOne)<<" "<<yTest[0];
}