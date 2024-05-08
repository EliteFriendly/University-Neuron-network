#pragma once
#include "Individual.h"
#include <iostream>
#include <vector>
class SurviveCrossover
{
public:
	virtual vector<Individual> forming(vector<Individual>, vector<Individual>) = 0;
};

class BestAndOffspring : public SurviveCrossover {
private:
	double max;//Максимальное значение пригодности
	int number = 0;//Номер такого индивида
public:
	vector<Individual> forming(vector<Individual>, vector<Individual>);
};


class OnlyOffspring : public SurviveCrossover {
private:
public:
	vector<Individual> forming(vector<Individual>, vector<Individual>);
};


class BestIndividualsAndOffspring : public SurviveCrossover {
private:
	void sortv(vector<Individual>& arr);
public:
	vector<Individual> forming(vector<Individual>, vector<Individual>);
};