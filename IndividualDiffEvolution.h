#pragma once
#include<iostream>
#include<vector>
#include <functional>
using namespace std;

class IndividualDiffEvolution
{
private:
	vector<double> coordinats ;//���������� ��������
	vector <double> limitsDimension;//����������� �� ������ ���
	double acc;//�������� ������ �����
	double fitness;//�������� �����������
	double error;//������
	

public:
	IndividualDiffEvolution(const IndividualDiffEvolution&);
	IndividualDiffEvolution() { fitness = -99999999; }
	IndividualDiffEvolution(vector <double> limitsDimension, double acc);
	void replaceCoordinats(vector<double> repCoord) {
		coordinats = repCoord;

	}
	void calcFitness(function<double(vector<double>)>func ,string aim) {
		if (aim == "max") {
			error = func(coordinats);
			fitness = error;
		}
		if (aim == "min") {
			error = func(coordinats);
			fitness = 1 / (error + 1);
		}
	}
	double getFitness() {return fitness;}
	vector<double> getCoordinats() { return coordinats; }

	double getError() { return error; }



	
	bool operator <(const IndividualDiffEvolution&);
	bool operator >(const IndividualDiffEvolution&);
	bool operator ==(const IndividualDiffEvolution&);
	IndividualDiffEvolution operator +(const IndividualDiffEvolution&);
	IndividualDiffEvolution operator -(const IndividualDiffEvolution&);
	//IndividualDiffEvolution operator =(const IndividualDiffEvolution&);
	IndividualDiffEvolution operator *(double);
};

