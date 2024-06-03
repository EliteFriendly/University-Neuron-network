#pragma once
#include<iostream>
#include<vector>
#include <functional>
using namespace std;

class IndividualDiffEvolution
{
private:
	vector<double> coordinats ;//Координаты индивида
	vector <double> limitsDimension;//Ограничение на каждую ось
	double acc;//Точность поиска точки
	double fitness;//Значение пригодности
	
	

public:
	IndividualDiffEvolution(const IndividualDiffEvolution&);
	IndividualDiffEvolution() { fitness = -99999999; }
	IndividualDiffEvolution(vector <double> limitsDimension, double acc);
	void replaceCoordinats(vector<double> repCoord) {
		coordinats = repCoord;

	}
	void calcFitness(function<double(vector<double>)>func ,string aim) {
		if (aim == "max") {
			fitness = func(coordinats);
		}
		if (aim == "min") {
			fitness = 1 / (func(coordinats) + 1);
		}
	}
	double getFitness() {return fitness;}
	vector<double> getCoordinats() { return coordinats; }





	
	bool operator <(const IndividualDiffEvolution&);
	bool operator >(const IndividualDiffEvolution&);
	bool operator ==(const IndividualDiffEvolution&);
	IndividualDiffEvolution operator +(const IndividualDiffEvolution&);
	IndividualDiffEvolution operator -(const IndividualDiffEvolution&);
	//IndividualDiffEvolution operator =(const IndividualDiffEvolution&);
	IndividualDiffEvolution operator *(double);
};

