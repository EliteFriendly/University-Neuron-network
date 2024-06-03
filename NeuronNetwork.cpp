#include "NeuronNetwork.h"


vector<double> NeuronNetwork::matrixMulti(vector<Neuron> neuron, vector<double> inMatrix)
{
	vector<double> out(neuron.size());//Выходная матрица
	double sum = 0;//Сумма что в нейроне
	//Основной цикл перемножения слоя на входы
	for (int i = 0; i < neuron.size(); i++) {
		sum = 0;
		for (int j = 0; j < inMatrix.size(); j++) {
			sum += neuron[i].getW()[j] * inMatrix[j];
		}
		sum += neuron[i].getW()[inMatrix.size()];//Добавление смещения нейрона
		out[i] = neuron[i].useFuncActivation(sum);
	}
	
	return out;
}

double NeuronNetwork::funcActivation(double x)
{
	return 1/(1+exp(-x));
}

double NeuronNetwork::getError(vector<double> w, vector<double> x, vector<double> y)
{
	changeW(w);

	double sum = 0;//Среднеквадратичная ошибка
	vector<double> onlyX(1);//Сделано для того чтобы получить значение из getValue
	for (int i = 0; i < x.size(); i++) {
		onlyX[0] = x[i];
		sum += pow(getValue(onlyX) - y[i], 2);
	}
	sum = pow(sum, 0.5);
	return sum;
}

void NeuronNetwork::setFuncActivation(vector<double> numbersFuncs)
{
	vector<function<double(double)>> allFuncActivation = {
		[](double x) { return 0; } ,//1
		[](double x) {return sin(x); },//2
		[](double x) {if (x < -1) return -1.0; if (x > 1) return 1.0; else return x; },//3
		[](double x) {return 2 / (1 + exp(x)) - 1; },//4
		//5 пропущена
		[](double x) {return exp(x); },//6
		[](double x) {return abs(x); },//7
		[](double x) {return 1 - exp(x); },//8
		[](double x) {return x; },//9
		[](double x) {return pow(x,2); },//10
		[](double x) {return pow(x,3); },//11
		[](double x) { if (x == 0) return 0.0; return pow(x,-1); },//12
		[](double x) {return 1; },//13
		[](double x) {return 1 / (1 + exp(-x)); },//14
		[](double x) {return exp(-(x * x) / 2); },//15
		[](double x) {if (x < -1 / 2) return -1.0; if (x > 1 / 2) return 1.0; else return x + 1 / 2; }//16

	};
	//Замена функции активации первого слоя
	for (int i = 0; i < layerCount; i++) {
		for (int j = 0; j < neuronCount; j++) {
			grid[i][j].replaceFuncActivation(allFuncActivation[int(numbersFuncs[i * layerCount + j])]);
		}
	}
}

void NeuronNetwork::changeW(vector<double> w)
{
	//Замена весовых коэффициентов первого слоя
	vector<double> replace;
	for (int i = 0; i < neuronCount; i++) {
		replace = w;
		replace.erase(replace.cbegin(), replace.cbegin() + i * (inCount + 1));//Удаление значений не для первых нейронов
		grid[0][i].changeW(replace);
	}
	vector<double> wWithoutFirstLayer = w;
	wWithoutFirstLayer.erase(wWithoutFirstLayer.cbegin(), wWithoutFirstLayer.cbegin() + neuronCount * (inCount + 1));
	//Замена весовый коэффициентов скрытых слоев без первого
	for (int i = 1; i < layerCount; i++) {
		for (int j = 0; j < neuronCount; j++) {
			replace = wWithoutFirstLayer;
			replace.erase(replace.cbegin(), replace.cbegin() + (i - 1) * ((neuronCount + 1) * layerCount) + j * (neuronCount + 1));
			grid[i][j].changeW(replace);
		}

	}

	//Замена выходных коэффициентов
	wWithoutFirstLayer.erase(wWithoutFirstLayer.cbegin(), wWithoutFirstLayer.cend() - neuronCount-1);//Попытка подобраться к коэффициентам последнего слоя
	outCoef = wWithoutFirstLayer;
	
}

void NeuronNetwork::startTrainGA(vector<double> x, vector<double> y)
{
	//Создание функции которая будет обучать ДЭ и получать от туда ошибку нейронной сети
	function<double(vector<double>)> error = [&](vector<double> numbersFuncActivation) {
		setFuncActivation(numbersFuncActivation);
		return startTrainDE(x, y);
		};
	//Задание ограничений
	vector<double> limitsVarLR(neuronCount * layerCount*2);
	for (int i = 0; i < limitsVarLR.size(); i++) {
		if (i % 2 == 0) {
			limitsVarLR[i] = 0;
		}
		else {
			limitsVarLR[i] = 14;
		}
	}

	//Обучение
	Simple_GA train(error, limitsVarLR, neuronCount * layerCount, "min");
	train.set_types("Tournament", "TwoPoint", "BestAndOffspring", "Average");
	train.start(30, 50, 1);
	//Получение наилучшей найденной комбинации функций для нейронной сети 
	vector<double> numFunc = train.get_all();
	setFuncActivation(numFunc);//Установка их и последующее сохранение
	ofstream file("Settings.txt");
	for (int i = 0; i < numFunc.size(); i++) {
		file << numFunc[i] << " ";
	}
	file << endl;
	startTrainDE(x, y);
	//Получение всех весовых коэффициентов в файл
	for (int i = 0; i < layerCount; i++) {
		for (int j = 0; j < neuronCount; j++) {
			for (int w = 0; w < grid[i][j].getW().size(); w++) {
				file << grid[i][j].getW()[w] << ' ';
			}
		}
	}


}

NeuronNetwork::NeuronNetwork(int neuronCount, int layerCount, int inCount):layerCount(layerCount), neuronCount(neuronCount), inCount(inCount)
{

	outCoef.resize(neuronCount);
	function <double(double)> funcIn = [&](double x) {return funcActivation(x); };//Функция активации

	Neuron neuronOut(funcIn, neuronCount);//Сделано чтобы получить рандомные коэф для выходного вектора
	outCoef = neuronOut.getW();
	//Создание нейронов в скрытых слоях
	grid.resize(layerCount, vector<Neuron>(neuronCount));

	//Создание первого слоя
	for (int i = 0; i < neuronCount; i++) {
		Neuron neuron(funcIn, inCount);
		grid[0][i] = neuron;
	}

	//Создание скрытых слоев
	for (int i = 1; i < layerCount ; i++) {
		for (int j = 0; j < neuronCount; j++) {
			Neuron neuron(funcIn, neuronCount);
			grid[i][j] = neuron;
		}

	}

}

double NeuronNetwork::startTrainDE(vector<double> x, vector<double> y)
{
	function<double(vector<double>)> error = [&](vector<double> w) {return getError(w, x, y); };

	//Границы параметров, включая ВЫХОДНЫЕ коэфф
	vector<double> limits((neuronCount * (inCount + 1) + (layerCount - 1) * (neuronCount + 1)*neuronCount+ (neuronCount + 1))*2);
	for (int i = 0; i < limits.size(); i++) {
		if (i % 2 == 0) {
			limits[i] = -50;
		}
		else {
			limits[i] = 50;
		}
	}

	DiffEvolution train(error, limits, "best1", "min");
	train.startSearch(0.01, 0.5, 0.5, 30, 50);
	changeW(train.getBestCoordinates());
	return train.getError();//Возвращает ошибку для работы ГА
}

double NeuronNetwork::getValue(vector<double> in)
{

	vector <double> layerValues = in;//То что будет хранить значения нейронов до самого выхода
	//Цикл прогонки по нейронам
	for (int i = 0; i < layerCount; i++) {
		layerValues = matrixMulti(grid[i], layerValues);
	}

	//Цикл получения выходящего значения
	double sum = 0;//Здесь будет хранится значение у
	for (int i = 0; i < neuronCount; i++) {
		sum += outCoef[i] * layerValues[i];
	}
	sum += outCoef[neuronCount];//Добавление смещения
	return sum;
}



