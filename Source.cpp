#include <iostream>
#include <vector>
#include <functional>
#include "NeuronNetwork.h"
#include <fstream>
#include "GeneratePoints.h"
#include <time.h>
#include <thread>
using namespace std;


//double func(double x) {
//	return -7 * sin(x) + 10 * exp(cos(x)) + 0.8 * x;
//}
double func(double x) {
	return sin(x) + x + 10;
}



void thr(string filename,int noise) {
	int ammount = 100;
	double left = 0;
	double right = 10;
	GeneratePoints points(func, left, right);
	points.readFromFile(filename);
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

	ofstream file_error("Ошибка_"+to_string(noise) + ".txt");
	ofstream file("Результаты_" + to_string(noise) + ".txt");
	proba.saveSettings("Settings_" + to_string(noise));
	file_error << proba.getError(xTest, yTest);
	for (int i = 0; i < 25; i++) {
		xOne[0] = xTest[i];
		file << xOne[0] << '\t' << proba.getValue(xOne) << '\t' << yTest[i] << endl;
	}
	file_error.close();
	file.close();

}





int main() {
	//Количество точен
	clock_t start = clock();
	setlocale(0, "");
	//srand(12);
	srand(time(0));

	int ammount = 100;
	double left = 0;
	double right = 10;

	int noiseArr[5] = { 5,10,15,20,40 };



	for (int i = 0; i < 5; i++) {

		string noise = ("Noise_" + to_string(noiseArr[i]));
		cout << noise << endl;
		thr(noise, noiseArr[i]);
	}





	//GeneratePoints points(func, left, right);
	//string filename = "20_Noise";
	//points.readFromFile(filename);
	///*string filename = "20_Noise";
	//points.readFromFile(filename);*/
	//thread thr1([&]() {
	//	thr(points);

	//	});



	//GeneratePoints points2(func, left, right);
	//filename = "40_Noise";
	//points2.readFromFile(filename);

	//thread thr2([&]() {
	//	thr(points2);
	//	});

	
	
	//filename = "40_Noise";
	//points.readFromFile(filename);
	//thr(points);
	//GeneratePoints points(func, left, right);
	//points.generateRandomly(ammount);
	//////points.saveInFile("ClearPoints");
	//
	//vector<double> noiseY;
	//noiseY = points.addNoise(points.getVectorY(), 40);
	//points.saveInFile("40_Noise",points.getVectorX(),noiseY);
	//Формирование выборки для обучения
	
	





	/*thr1.join();
	thr2.join();*/
	clock_t end = clock();

	printf("Work time: %f seconds\n", double(end - start) / CLOCKS_PER_SEC);
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