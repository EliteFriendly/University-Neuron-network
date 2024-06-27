#include <iostream>
#include <vector>
#include <functional>
#include "NeuronNetwork.h"
#include <fstream>
#include "GeneratePoints.h"
#include <thread>
using namespace std;


//double func(double x) {
//	return -7 * sin(x) + 10 * exp(cos(x)) + 0.8 * x;
//}

double func(double x) {
	return sin(x) + x + 10;
}


void main() {
	int ammount = 100;//Количество точен
	double left = 0;
	double right = 10;
	setlocale(0, "");
	//srand(12);
	srand(time(0));
	//GeneratePoints points(func, left, right);
	//points.generateRandomly(ammount);
	//////points.saveInFile("ClearPoints");
	//
	//vector<double> noiseY;
	//noiseY = points.addNoise(points.getVectorY(), 40);
	//points.saveInFile("40_Noise",points.getVectorX(),noiseY);
	//Формирование выборки для обучения
	

	thread thr1([&]() {
		GeneratePoints points(func, left, right);
		points.readFromFile("20_Noise");
		vector<double> noiseY = points.getVectorY();
		vector<double> x = points.getVectorX();

		int i1 = 0;//Счетчики
		int i2 = 0;

		double h = (right - left) / ammount;
		vector<double> xTrain(int(0.75 * ammount));
		vector<double> yTrain(int(0.75 * ammount));
		vector<double> xTest(int(0.25 * ammount));
		vector<double> yTest(int(0.25 * ammount));
		for (int i = 0; i < ammount; i++) {
			if (i % 4 != 0) {
				xTrain[i1] = x[i];
				yTrain[i1] = noiseY[i];
				i1++;
			}
			else {
				xTest[i2] = x[i];
				yTest[i2] = noiseY[i];
				i2++;
			}
		}



		//Начало
		vector<double> xOne(1);

		NeuronNetwork proba(3, 3, 1);
		//proba.startTrainDE(xTrain, yTrain);
		proba.startTrainGA(xTrain, yTrain);

		//proba.changeFromFile("Settings_best");

		ofstream file_error("Ошибка_20.txt");
		ofstream file("Результаты_20.txt");
		proba.saveSettings("Settings_20");
		file_error << proba.getError(xTest, yTest);
		for (int i = 0; i < 25; i++) {
			xOne[0] = xTest[i];
			file << xOne[0] << '\t' << proba.getValue(xOne) << '\t' << yTest[i] << endl;
		}
		file_error.close();
		file.close();


		});

	thread thr2([&]() {
			GeneratePoints points(func, left, right);
			points.readFromFile("40_Noise");
			vector<double> noiseY = points.getVectorY();
			vector<double> x = points.getVectorX();

			int i1 = 0;//Счетчики
			int i2 = 0;

			double h = (right - left) / ammount;
			vector<double> xTrain(int(0.75 * ammount));
			vector<double> yTrain(int(0.75 * ammount));
			vector<double> xTest(int(0.25 * ammount));
			vector<double> yTest(int(0.25 * ammount));
			for (int i = 0; i < ammount; i++) {
				if (i % 4 != 0) {
					xTrain[i1] = x[i];
					yTrain[i1] = noiseY[i];
					i1++;
				}
				else {
					xTest[i2] = x[i];
					yTest[i2] = noiseY[i];
					i2++;
				}
			}



			//Начало
			vector<double> xOne(1);

			NeuronNetwork proba(3, 3, 1);
			//proba.startTrainDE(xTrain, yTrain);
			proba.startTrainGA(xTrain, yTrain);

			//proba.changeFromFile("Settings_best");

			ofstream file_error("Ошибка_40.txt");
			ofstream file("Результаты_40.txt");
			proba.saveSettings("Settings_40");
			file_error << proba.getError(xTest, yTest);
			for (int i = 0; i < 25; i++) {
				xOne[0] = xTest[i];
				file << xOne[0] << '\t' << proba.getValue(xOne) << '\t' << yTest[i] << endl;
			}
			file_error.close();
			file.close();



			});





	thr1.join();
	thr2.join();

	//points.readFromFile("10_Noise");
	//vector<double> noiseY = points.getVectorY();
	//vector<double> x = points.getVectorX();

	//int i1 = 0;//Счетчики
	//int i2 = 0;

	//double h = (right - left) / ammount;
	//vector<double> xTrain(int(0.75 * ammount));
	//vector<double> yTrain(int(0.75 * ammount));
	//vector<double> xTest(int(0.25 * ammount));
	//vector<double> yTest(int(0.25 * ammount));
	//for (int i = 0; i < ammount; i++) {
	//	if (i % 4 != 0) {
	//		xTrain[i1] = x[i];
	//		yTrain[i1] = noiseY[i];
	//		i1++;
	//	}
	//	else {
	//		xTest[i2] = x[i];
	//		yTest[i2] = noiseY[i];
	//		i2++;
	//	}
	//}



	////Начало
	//vector<double> xOne(1);
	//
	//NeuronNetwork proba(3, 3, 1);
	////proba.startTrainDE(xTrain, yTrain);
	//proba.startTrainGA(xTrain, yTrain);

	////proba.changeFromFile("Settings_best");

	//ofstream file_error("Ошибка_5.txt");
	//ofstream file("Результаты_5.txt");

	//file_error <<proba.getError(xTest, yTest);
	//for (int i = 0; i < 25; i++) {
	//	xOne[0] = xTest[i];
	//	file<< xOne[0] <<'\t' << proba.getValue(xOne) << '\t' << yTest[i] << endl;
	//}
	//file_error.close();
	//file.close();
}