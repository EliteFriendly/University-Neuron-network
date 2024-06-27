#pragma once
#include <iostream>
#include <vector>
#include <functional>
#include<fstream>
#include <algorithm>

using namespace std;

class GeneratePoints
{
private:
	function<double(double)> func;//Функция по которой будут генерироваться точки
	double leftLimits;
	double rightLimits;

	double* x = nullptr;
	double* y = nullptr;
	vector<double> vectorX;
	vector<double> vectorY;
	int ammountPoints = 0;


public:
	GeneratePoints(function<double(double)> func, double leftLimits, double rightLimits):func(func),leftLimits(leftLimits),
		rightLimits(rightLimits)
	{

	}

	vector<double> addNoise(vector<double> vectorY,int power) {

		vector<double> arrWithNoise = vectorY;
		int ammount = vectorY.size();
		for (int i = 0; i < ammount; i++) {
			if (rand()%1) {
				arrWithNoise[i] = arrWithNoise[i] + double(rand() % power + rand() % 1)/100.0 * arrWithNoise[i];
			}
			else {
				arrWithNoise[i] = arrWithNoise[i] - double(rand() % power + rand() % 1)/100.0 * arrWithNoise[i];
			}
		}
		return arrWithNoise;

	}


	void generateRandomly(int ammountPoints) {
		srand(time(0));
		GeneratePoints::ammountPoints = ammountPoints;
		vectorX.resize(ammountPoints);
		vectorY.resize(ammountPoints);
		int range = int(abs(leftLimits - rightLimits)*ammountPoints);//Диапозон который может принимать rand
		double value;
		for (int i = 0; i < ammountPoints; i++) {
			value = leftLimits + double(rand() % range+rand()%1) / ammountPoints;
			vectorX[i] = value;
		}
		sort(begin(vectorX),end(vectorX));
		
		for (int i = 0; i < ammountPoints; i++) {
			vectorY[i] = func(vectorX[i]);
		}
	}

	void saveInFile(string nameFile) {
		if (nameFile.find('.') != 1) {
			nameFile = string(nameFile + ".txt");
		}

		ofstream file(nameFile);
		
		for (int i = 0; i < ammountPoints; i++) {
			file << vectorX[i] << '\t' << vectorY[i] << endl;
		}
		file.close();

	}
	void saveInFile(string nameFile,vector<double>vectorX, vector<double>vectorY) {
		if (nameFile.find('.') != 1) {
			nameFile = string(nameFile + ".txt");
		}

		ofstream file(nameFile);

		for (int i = 0; i < ammountPoints; i++) {
			file << vectorX[i] << '\t' << vectorY[i] << endl;
		}
		file.close();

	}
	void readFromFile(string nameFile) {
		if (nameFile.find('.') != 1) {
			nameFile = string(nameFile + ".txt");
		}
		ifstream file;
		file.open(nameFile);
		if (file.is_open()) {
			double value;
			while (file) {
				file >> value;
				vectorX.push_back(value);
				file >> value;
				vectorY.push_back(value);
			}
			vectorX.erase(vectorX.end()-1);
			vectorY.erase(vectorY.end()-1);
		}
		else {
			cout << "Файл не найден";
			exit(0);
		}
		
	}
	vector<double> getVectorX() {
		return vectorX;
	}
	vector<double> getVectorY() {
		return vectorY;
	}
	~GeneratePoints() {
		if (x != nullptr) {
			delete[] x;
		}
		if (y != nullptr) {
			delete[] y;
		}
		
	}
};

