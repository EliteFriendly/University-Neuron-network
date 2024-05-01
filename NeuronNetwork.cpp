#include "NeuronNetwork.h"

double NeuronNetwork::funcActivation(double x)
{
	return 1/(1+exp(pow(x,-1)));
}

NeuronNetwork::NeuronNetwork(int neuronCount, int layerCount, int inCount):layerCount(layerCount), neuronCount(neuronCount), inCount(inCount)
{
	in.resize(inCount);
	//Создание входных нейронов(они не имеет вес коэффициенты и возвращают входные данные)
	for (int i = 0; i < inCount; i++)
	{
		Neuron inNeuron(i);
		in[i] = inNeuron;
	}
	//Создание нейронов в скрытых слоях
	grid.resize(neuronCount, vector<Neuron>(layerCount));
	//Создание первого слоя, которые опирается на входы
	function <double(double)> funcIn = [&](double x) {return funcActivation(x); };
	for (int i = 0; i < neuronCount; i++) {
		Neuron neuron(in, funcIn);
		grid[0][i] = neuron;
	}
	//Создание скрытых слоев
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
