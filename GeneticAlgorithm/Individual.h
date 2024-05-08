#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include <functional>
using namespace std;
class Individual
{
private:
	string target;//Цель функции
	double fitness;//Значение пригодности
	vector<bool> bin_code;//Ген индивида
	vector<double> coordinates;//Точка где сейчас индивид
	vector<double> ratio_conv;//Коэфициент домножения
	int var_of_dimension;//Количество пространств
	vector<int> bits_dim;//Количество битов на каждую ось
	int allbits;//Суммарное количество битов
	vector<double> limits_var_LR;//Ограничения слева и справа


	function<double(vector<double>)> func;

	void decoding();//Перевод из двоичный системы в десятичную
	void fitness_func();

public:
	Individual() {}
	Individual(const Individual& copy);
	Individual(int var_of_dimension, vector<double> ration_conv, vector<int> bits_dim, vector<double> limits_var_LR,
		function<double(vector<double>)> func,string target);
	
	double get_fitness();
	void replace_code(vector<bool> bin_code);
	vector<double> get_point();
	string get_point_str();
	vector<bool>  get_binary();
	int get_allbits() { return allbits; }

	vector<double> get_all(double acc);


	//Individual operator =(Individual copy);
};

