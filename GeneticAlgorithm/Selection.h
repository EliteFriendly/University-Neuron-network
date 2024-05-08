#pragma once
#pragma once
#include<iostream>
#include<vector>
#include"Individual.h"
//#include "Support_func.h"


class Selection
{
protected:
	int tour_size = 3;
public:
	virtual int get_num_parent(vector<Individual>& arr)=0;
	void set_tour_size(int size) {
		tour_size = size;
	}
};



class Tournament : public Selection
{
protected:
	int number, number_best = -1;
	double max_fitness = -1;
public:
	int get_num_parent(vector<Individual> &arr);
};

class Ranked : public Selection//Неоптимизированна 
{
protected:
	double* rank_arr;
	void sortv(vector<Individual>& arr);
public:
	int get_num_parent(vector<Individual>& arr);
};


class Proportional : public Selection
{
protected:
	double min = 0;
	int size;
	double* fitness_arr;
	void aligment(vector<Individual>&);
	void norm();
public:
	int get_num_parent(vector<Individual>& arr);
};


