#pragma once
#include "IndividualDiffEvolution.h"
#include<vector>
#include <iostream>

using namespace std;

class DiffMutation
{
private:
	string type;//��� �������
	vector <int> selectedInd;//������ ��������� ���������
	double F;//�������������� ������
	int ammount;//���������� ��������� � ����� �������
	vector <double> limitsDimension;//����������� �� ������ ���

	void outLimits(IndividualDiffEvolution);//�������� ����� �� ������� �� �������
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
			ammount = 4;//������� i - ��� ������
		}
		if (type == "targetToBest1") {
			ammount = 3;//������� i - ��� ������
		}
	}
	void setLimits(vector<double> limits) {
		limitsDimension = limits;
	}

	IndividualDiffEvolution getDonor(vector<IndividualDiffEvolution>&, IndividualDiffEvolution&);

};

