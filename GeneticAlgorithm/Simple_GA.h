#pragma once
#include <iostream>
#include "Individual.h"
#include "Selection.h"
#include "Crossover.h"
#include "Mutation.h"
#include "SurviveCrossover.h"
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

class Simple_GA
{
private:
	int am_individuals;//Количество индивидов в поколении
	int am_generations;//Колчиество поколений
	int dimensions;//Количество пространств
	function<double(vector<double>)> func;
	vector<double> limits_var_LR;//Границы слева и справа на каждой оси
	double accuracy; //Точность с которой счиатется 
	vector<double> ratio_conv;//Коэфициент домножения для точей
	vector<int> bits_dimension;//Количество битов на каждой оси
	Selection* selection;
	Crossover* crossover;
	Mutation mutation;
	SurviveCrossover* surcross;
	string type_of_selection,
		type_of_crossover, 
		type_of_surcross,
		type_of_mutation,
		target;
	vector<Individual> arr_individuals,arr_childs;
	Individual best;


	void find_best(vector<Individual>);
public:
	void set_procent(double procent) {
		mutation.set_procent(procent);
	}

	Simple_GA(function<double(vector<double>)> func, vector<double> limits_var_LR, int dimensions, string target);//Без параметров настройки
	void set_types(string type_of_selection, string type_of_crossover, string type_of_surcross, string type_of_mutation);
	void set_tour_size(int size) {
		selection->set_tour_size(size);
	}

	double start(int am_individuals, int am_generations, double accuracy);
	vector<double> get_all() {
		return best.get_all(accuracy);
		
	}
};

