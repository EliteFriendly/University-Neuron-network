#pragma once
#include "IndividualDiffEvolution.h"
#include <vector>
#include<iostream>
#include <algorithm>
#include<thread>
#include "DiffMutation.h"
#include<ctime>
#include <functional>

using namespace std;

class DiffEvolution
{
private:
	function<double(vector<double>)>func;
	vector <double> limitsDimension;//����������� ������ ���
	double F;//�������������� ������
	double Cr;//����������� �����������
	int N;//���������� ���������
	int generations;//���������� ���������
	vector<IndividualDiffEvolution> arrIndividuals;//������ ���������� ������� �������
	IndividualDiffEvolution best;//������ ��������� �������
	DiffMutation mutation;
	string aim;//���� ������

	IndividualDiffEvolution crossover(IndividualDiffEvolution);
	void surviveCrossover(IndividualDiffEvolution);
	void saveBest();
public:
	DiffEvolution(function<double(vector<double>)>func, vector<double> limitsDimension, string typeMut, string aim) :func(func),
		limitsDimension(limitsDimension), aim(aim)
	{
		mutation.setType(typeMut);
		mutation.setLimits(limitsDimension);
	}
	void startSearch(double acc,double F, double Cr, int N,int generation);

	double getBest() {
		return func(best.getCoordinats());
	}
	vector<double> getBestCoordinates() {
		return best.getCoordinats();
	}
	double getError() { return best.getFitness(); }
};

