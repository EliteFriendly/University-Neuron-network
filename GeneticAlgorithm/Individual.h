#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include <functional>
using namespace std;
class Individual
{
private:
	string target;//���� �������
	double fitness;//�������� �����������
	vector<bool> bin_code;//��� ��������
	vector<double> coordinates;//����� ��� ������ �������
	vector<double> ratio_conv;//���������� ����������
	int var_of_dimension;//���������� �����������
	vector<int> bits_dim;//���������� ����� �� ������ ���
	int allbits;//��������� ���������� �����
	vector<double> limits_var_LR;//����������� ����� � ������


	function<double(vector<double>)> func;

	void decoding();//������� �� �������� ������� � ����������
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

