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
	vector <double> limitsDimension;//Ограничения каждой оси
	double F;//Масштабирующий фактор
	double Cr;//Вероятность скрещивания
	int N;//Количество индивидов
	int generations;//Количество поколений
	vector<IndividualDiffEvolution> arrIndividuals;//Вектор содержащий целевые вектора
	IndividualDiffEvolution best;//Лучшее найденное решение
	DiffMutation mutation;
	string aim;//Цель задачи

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

