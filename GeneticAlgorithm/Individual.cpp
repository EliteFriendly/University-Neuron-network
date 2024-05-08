#include "Individual.h"


Individual::Individual(const Individual& copy):
	var_of_dimension(copy.var_of_dimension),
	ratio_conv(copy.ratio_conv), bits_dim(copy.bits_dim),
	limits_var_LR(copy.limits_var_LR), func(copy.func), target(copy.target),
	allbits(copy.allbits),
	fitness(copy.fitness)
{
	coordinates .resize(var_of_dimension);
	bin_code.resize(allbits);
	for (int i = 0; i < var_of_dimension; i++) {
		coordinates[i] = copy.coordinates[i];
	}
	for (int i = 0; i < allbits; i++) {
		bin_code[i] = copy.bin_code[i];
	}
}




Individual::Individual(int var_of_dimension, vector<double> ration_conv, vector<int> bits_dim, vector<double> limits_var_LR,
	function<double(vector<double>)> func, string target):var_of_dimension(var_of_dimension),
	ratio_conv(ration_conv), bits_dim(bits_dim),
	limits_var_LR(limits_var_LR),func(func), target(target)
{
	//memcpy(bits_dim, bits_dim1,u);
	coordinates.resize(var_of_dimension);
	allbits = 0;// Определение общего количества битов
	for (int i = 0; i < var_of_dimension; i++) {
		allbits += bits_dim[i];
	}
	bin_code .resize(allbits);//Иницилизация гена
	for (int i = 0; i < allbits; i++) {
		bin_code[i] = rand() % 2;
	}

	fitness_func();
	
}

void Individual::decoding() {
	int bit_indent = 0;//На каком бите сейчас
	for (int i = 0; i < var_of_dimension; i++) {
		double decod_score = 0;
		for (int bit = 0; bit < bits_dim[i]; bit++) {
			decod_score += pow(2, bit) * bin_code[bit + bit_indent];
		}
		//cout << decod_score << endl;
		bit_indent += bits_dim[i];
		coordinates[i] = decod_score * ratio_conv[i] + limits_var_LR[i * 2];
	}
}

void Individual::fitness_func() {
	decoding();
	if (target == "max") {
		fitness = func(coordinates);
	}
	else if (target == "min") {
		//fitness = 1.0 / (func(coordinates) + 1);
		fitness = -1*func(coordinates);
	}
	else {
		cout << "Ошибка цели";
		exit(0);
	}
}

double Individual::get_fitness() {
	return fitness;
}
void Individual::replace_code(bool* bin_code_replace) {
	for (int i = 0; i < allbits; i++) {
		bin_code[i] = bin_code_replace[i];
	}
	fitness_func();
}

vector<double> Individual::get_point() {
	return coordinates;
}
string Individual::get_point_str() {
	stringstream ss;
	for (int i = 0;i < var_of_dimension; i++) {
		ss << coordinates[i];
	}
	return ss.str();
}
vector<bool>  Individual::get_binary() {
	return bin_code;
}

vector<double> Individual::get_all(double acc) {
	int acc_u = 1 / acc;//Используется для округления
	vector<double> coord_func;//Хранится координаты точки и значение функции
	for (int i = 0; i < var_of_dimension; i++) {
		coord_func.push_back(round(coordinates[i] * acc_u) * acc);
	}
	vector<double> in_func (coord_func.size());//Костыль, чтобы отправить значение в функцию
	for (int i = 0; i < var_of_dimension; i++) {
		in_func[i] = coord_func[i];
	}
	coord_func.push_back(round(func(in_func) * acc_u) * acc);
	return coord_func;
}



