#include "NeuronNetwork.h"

vector<double> NeuronNetwork::matrixMulti(vector<Neuron> neuron, vector<double> inMatrix)
{
	vector<double> out(neuron.size());//�������� �������
	double sum = 0;//����� ��� � �������
	//�������� ���� ������������ ���� �� �����
	for (int i = 0; i < neuron.size(); i++) {
		sum = 0;
		for (int j = 0; j < inMatrix.size(); j++) {
			sum += neuron[i].getW()[j] * inMatrix[j];
		}
		sum += neuron[i].getW()[inMatrix.size()];//���������� �������� �������
		out[i] = neuron[i].useFuncActivation(sum);
	}
	
	return out;
}

double NeuronNetwork::funcActivation(double x)
{
	return 1/(1+exp(pow(x,-1)));
}

double NeuronNetwork::getError(vector<double> w, vector<double> x, vector<double> y)
{
	changeW(w);


	double sum = 0;//������������������ ������
	vector<double> onlyX(1);//������� ��� ���� ����� �������� �������� �� getValue
	for (int i = 0; i < x.size(); i++) {
		onlyX[0] = x[i];
		sum += pow(getValue(onlyX) - y[i], 2);
	}
	sum = pow(sum, 0.5);
	return sum;
}

void NeuronNetwork::changeW(vector<double> w)
{
	//������ ������� ������������� ������� ����
	vector<double> replace;
	for (int i = 0; i < neuronCount; i++) {
		replace = w;
		replace.erase(replace.cbegin(), replace.cbegin() + i * (inCount + 1));//�������� ������������� ��� ������ ��������
		//replace.erase(replace.cbegin() + i * (inCount + 1) * 2, replace.cend());//�������� ��������� �����
		grid[0][i].changeW(replace);
	}
	vector<double> wWithoutFirstLayer = w;
	wWithoutFirstLayer.erase(wWithoutFirstLayer.cbegin(), wWithoutFirstLayer.cbegin() + neuronCount * (inCount + 1));
	//������ ������� ������������� ������� ����� ��� �������
	for (int i = 1; i < layerCount; i++) {
		for (int j = 0; j < neuronCount; j++) {
			replace = wWithoutFirstLayer;
			replace.erase(replace.cbegin(), replace.cbegin() + (i - 1) * ((neuronCount + 1) * layerCount) + j * (neuronCount + 1));
			grid[i][j].changeW(replace);
		}

	}

	//������ �������� �������������
	wWithoutFirstLayer.erase(wWithoutFirstLayer.cbegin(), wWithoutFirstLayer.cend() - neuronCount-1);//������� ����������� � ������������� ���������� ����
	outCoef = wWithoutFirstLayer;
	
}

NeuronNetwork::NeuronNetwork(int neuronCount, int layerCount, int inCount):layerCount(layerCount), neuronCount(neuronCount), inCount(inCount)
{

	outCoef.resize(neuronCount);
	function <double(double)> funcIn = [&](double x) {return funcActivation(x); };//������� ���������

	Neuron neuronOut(funcIn, neuronCount);//������� ����� �������� ��������� ���� ��� ��������� �������
	outCoef = neuronOut.getW();
	//�������� �������� � ������� �����
	grid.resize(layerCount, vector<Neuron>(neuronCount));

	//�������� ������� ����
	for (int i = 0; i < neuronCount; i++) {
		Neuron neuron(funcIn, inCount);
		grid[0][i] = neuron;
	}

	//�������� ������� �����
	for (int i = 1; i < layerCount ; i++) {
		for (int j = 0; j < neuronCount; j++) {
			Neuron neuron(funcIn, neuronCount);
			grid[i][j] = neuron;
		}

	}

}

void NeuronNetwork::startTrain(vector<double> x, vector<double> y)
{
	function<double(vector<double>)> error = [&](vector<double> w) {return getError(w, x, y); };

	vector<double> limits((neuronCount * (inCount + 1) + (layerCount - 1) * (neuronCount + 1)*neuronCount+ (neuronCount + 1))*2);//������� ����������, ������� �������� �����
	for (int i = 0; i < limits.size(); i++) {
		if (i % 2 == 0) {
			limits[i] = -10;
		}
		else {
			limits[i] = 10;
		}
	}

	DiffEvolution train(error, limits, "best1", "min");
	train.startSearch(0.01, 0.5, 0.5, 50, 50);
	changeW(train.getBestCoordinates());
}

double NeuronNetwork::getValue(vector<double> in)
{

	vector <double> layerValues = in;//�� ��� ����� ������� �������� �������� �� ������ ������
	//���� �������� �� ��������
	for (int i = 0; i < layerCount; i++) {
		layerValues = matrixMulti(grid[i], layerValues);
	}

	//���� ��������� ���������� ��������
	double sum = 0;//����� ����� �������� �������� �
	for (int i = 0; i < neuronCount; i++) {
		sum += outCoef[i] * layerValues[i];
	}
	sum += outCoef[neuronCount];//���������� ��������
	return sum;
}



