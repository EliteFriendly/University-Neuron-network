#include "Selection.h"



int Tournament::get_num_parent(vector<Individual> &arr) {
	max_fitness = -99999999;

	for (int i = 0; i < tour_size; i++) {
		number = rand() % arr.size();
		if (arr[number].get_fitness() > max_fitness) {
			max_fitness = arr[number].get_fitness();
			number_best = number;
		}
	}
	return number_best;
}






void Ranked::sortv(vector<Individual>& arr) {
	int listLength = arr.size();
	while (listLength--)
	{
		bool swapped = false;

		for (int i = 0; i < listLength; i++)
		{
			if (arr[i].get_fitness() > arr[i + 1].get_fitness())
			{
				Individual tmp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = tmp;
				swapped = true;
			}
		}

		if (swapped == false)
			break;
	}
}

int Ranked::get_num_parent(vector<Individual>& arr) {
	sortv(arr);
	vector<double> rank_arr;
	for (int i = 0; i < arr.size(); i++) {
		rank_arr.push_back(i + 1);
	}
	int c = 1, k = 0;

	int z=0;
	/*for (int i = 0; i < arr.size() - 1; i++) {

		while (arr[i].get_fitness() == arr[i + c].get_fitness()and (i+c)<arr.size()) {
			c++;
			k++;
			z = c;
		}

		while (k > 0) {
			if (i + k > arr.size()) {
				cout << "eror";
			}
			rank_arr[i + k] = rank_arr[i + k] / z;
			k--;

		}
		if (c > 1) {
			c--;
		}
	}*/

	double sum = 0;
	for (int i = 0; i < arr.size(); i++) {
		sum += rank_arr[i];
	}
	for (int i = 0; i < arr.size(); i++) {
		rank_arr[i] /= sum;
	}
	sum = 0;
	int number = 0;
	double probability = rand() % 10000 / 10000.0;
	while (probability > sum) {
		number++;
		if (number == arr.size()) {
			return number - 1;
		}
		sum += rank_arr[number];
	}
	return number;
}








void Proportional::aligment(vector<Individual>& arr) {
	vector<double> fitness_arr (arr.size());
	for (int i = 0; i < arr.size(); i++) {
		fitness_arr[i] = arr[i].get_fitness();
		if (fitness_arr[i] < min) {
			min = fitness_arr[i];
		}
	}
	if (min < 0) {
		for (int i = 0; i < arr.size(); i++) {
			fitness_arr[i] += min;
		}
	}

}
void Proportional::norm() {
	double sum = 0;
	for (int i = 0; i < size; i++) {
		sum += fitness_arr[i];
	}
	for (int i = 0; i < size; i++) {
		fitness_arr[i]/=sum;
	}
}
int Proportional::get_num_parent(vector<Individual>& arr) {
	size = arr.size();
	aligment(arr);
	norm();
	double sum=fitness_arr[0];
	int number = 0;
	double probability = rand() % 10000 / 10000.0;
	while (probability > sum) {
		number++;
		sum += fitness_arr[number];
	}
	return number;
}