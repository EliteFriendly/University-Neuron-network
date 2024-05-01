#include "NeuronNetwork.h"

double NeuronNetwork::funcActivation(double x)
{
	return 1/(1+exp(pow(x,-1)));
}

NeuronNetwork::NeuronNetwork(int neuronCount, int layerCount, int inCount):layerCount(layerCount), neuronCount(neuronCount), inCount(inCount)
{
	in.resize(inCount);
	//�������� ������� ��������(��� �� ����� ��� ������������ � ���������� ������� ������)
	for (int i = 0; i < inCount; i++)
	{
		Neuron inNeuron(i);
		in[i] = inNeuron;
	}
	//�������� �������� � ������� �����
	grid.resize(neuronCount, vector<Neuron>(layerCount));
	//�������� ������� ����, ������� ��������� �� �����
	function <double(double)> funcIn = [&](double x) {return funcActivation(x); };
	for (int i = 0; i < neuronCount; i++) {
		Neuron neuron(in, funcIn);
		grid[0][i] = neuron;
	}
	//�������� ������� �����
	for (int i = 1; i < layerCount ; i++) {
		for (int j = 0; j < neuronCount; j++) {
			Neuron neuron(grid[i-1], funcIn);
			grid[i][j] = neuron;
		}

	}

}

double NeuronNetwork::getValue(vector<double> in)
{
	
	return grid[1][1].getValue(in);;
}

void NeuronNetwork::changeW()
{
	grid[0][0].changeW({ 10,10 });
}
