#pragma once
#include <iostream>
#include <vector>
#include <functional>

using namespace std;

class Neuron
{
private:
	vector<double> w;//������� ������������ �������� ��������
	function <double(double)> funcActivation;//������� ���������
public:
	Neuron() {}
	Neuron(const Neuron&);
	Neuron(function<double(double)>, int);

	double useFuncActivation(double x) { return funcActivation(x); }

	void changeFuncActivation(function<double(double)> funcIn) { funcActivation = funcIn; }
	void changeW(vector<double> w);
	vector<double> getW();
};

