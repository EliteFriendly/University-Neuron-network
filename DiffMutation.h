#pragma once
#include "IndividualDiffEvolution.h"
#include<vector>
#include <iostream>

using namespace std;

class DiffMutation
{
private:
	string type;//Тип мутации
	vector <int> selectedInd;//Номера выбранных индивидов
	double F;//Масштабирующий фактор
	int ammount;//Количество родителей в донор векторе
	vector <double> limitsDimension;//Ограничение на каждую ось

	void outLimits(IndividualDiffEvolution);//Проверка вышел ли индивид за границы
public:
	void setF(double F) {
		DiffMutation::F = F;
	}

	void setType(string type) {
		DiffMutation::type = type;
		if (type == "rand1") {
			ammount = 3;
		}
		if (type == "rand2") {
			ammount = 5;
		}
		if (type == "best1") {
			ammount = 2;
		}
		if (type == "best2") {
			ammount = 4;
		}
		if (type == "targetToRand1") {
			ammount = 4;//Включая i - тый вектор
		}
		if (type == "targetToBest1") {
			ammount = 3;//Включая i - тый вектор
		}
	}
	void setLimits(vector<double> limits) {
		limitsDimension = limits;
	}

	IndividualDiffEvolution getDonor(vector<IndividualDiffEvolution>&, IndividualDiffEvolution&);

};

