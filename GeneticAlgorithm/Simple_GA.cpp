#include "Simple_GA.h"






Simple_GA::Simple_GA(function<double(vector<double>)> func, vector<double> limits_var_LR, int dimensions, string target):
	func(func), limits_var_LR(limits_var_LR), dimensions(dimensions), target(target)
{
	srand(time(0));
}

void Simple_GA::set_types(string type_of_selection, string type_of_crossover, string type_of_surcross, string type_of_mutation)
{
	//Selection types
	if (type_of_selection == "Tournament") {
		selection = new Tournament;
	}
	if (type_of_selection == "Proportional") {
		selection = new Proportional;
	}
	if (type_of_selection == "Ranked") {
		selection = new Ranked;
	}
	//Crossover types
	if (type_of_crossover == "OnePoint") {
		crossover = new OnePoint;
	}
	if (type_of_crossover == "TwoPoint") {
		crossover = new TwoPoint;
	}
	if (type_of_crossover == "Uniform") {
		crossover = new Uniform;
	}

	//Surcross types
	if (type_of_surcross == "BestAndOffspring") {
		surcross = new BestAndOffspring;
	}
	if (type_of_surcross == "OnlyOffspring") {
		surcross = new OnlyOffspring;
	}
	if (type_of_surcross == "BestIndividualsAndOffspring") {
		surcross = new BestIndividualsAndOffspring;
	}


	//Mutation types
	
	mutation.set_mutation(type_of_mutation);
}

double Simple_GA::start(int ammount_individuals, int ammount_generations, double accuracy_f) {
	am_individuals = ammount_individuals;
	am_generations = ammount_generations;
	accuracy = accuracy_f;

	ratio_conv.resize(dimensions);
	
	vector<double>  limits(dimensions);
	//определение ограничений для будущей кодировки
	for (int i = 0; i < dimensions * 2; i += 2) {
		limits[i / 2] = abs(limits_var_LR[i] - limits_var_LR[i + 1]) / accuracy/10;
	}

	

	bits_dimension.resize(dimensions);
	//определение количества битов на одну ось
	int bits_individuals = 0, allbits=0;
	for (int i = 0; i < dimensions; i++) {
		bits_individuals = 0;
		while (pow(2, bits_individuals) < limits[i]) {
			bits_individuals++;
		}
		bits_individuals++;
		allbits += bits_individuals;
		bits_dimension[i] = bits_individuals;
	}

	//определения коэфициента для домножения
	for (int i = 0; i < dimensions; i++) {
		ratio_conv[i] = limits[i] / pow(2, bits_dimension[i])* accuracy;
	}


	//Создание индивидов
	for (int i = 0; i < am_individuals; i++) {
		Individual ind(dimensions, ratio_conv, bits_dimension, limits_var_LR, func, target);
		arr_individuals.push_back(ind);
	}
	

	find_best(arr_individuals);


	int parent1, parent2;//Номер родителя
	//начало всего
	for (int i = 0; i < am_generations; i++) {

		for (int j = 0; j < am_individuals; j++) {//Создание и мутирование потомков
			parent1 = selection->get_num_parent(arr_individuals);//ОТбор 1 родителя
			parent2 = selection->get_num_parent(arr_individuals);//Отбор 2 родителя
			while (parent1 == parent2) {
				parent2 = selection->get_num_parent(arr_individuals);//Отбор 2 родителя при повторе
			}

			arr_childs.push_back(crossover->get_child(
				arr_individuals[parent1], arr_individuals[parent2]));//Кроссовер

			arr_childs[j] = mutation.mutation(arr_childs[j]);//Мутация зародыша
		}

		arr_individuals = surcross->forming(arr_individuals, arr_childs);//Формирование нового поколения
		find_best(arr_individuals);
		arr_childs.clear();
	}

	return 0;
}

void Simple_GA::find_best(vector<Individual> arr) {
	//double max = arr[0].get_fitness();//Максимальный фитнес
	int number = 0;//Номер индивида с таким фитнесом
	for (int i = 0; i < arr.size(); i++) {
		if (arr[i].get_fitness()>best.get_fitness()) {
			best = arr[i];
		}
	}
	
	
}


