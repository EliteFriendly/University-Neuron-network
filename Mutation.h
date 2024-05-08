#pragma once
#include "Individual.h"
#include <iostream>
class Mutation
{
protected:
	bool* gen;
	double probability;
	double mut;
	string type_of_mutation = "Average";
public:
	void set_mutation(string type_of_mutation_v) {
		type_of_mutation = type_of_mutation_v;
	}
	void set_procent(double probability_in) {
		probability = probability_in;
	}
	Individual mutation(Individual& child) 
	{
		int allbits = child.get_allbits();
		double probability, mut;
		if (type_of_mutation == "Average") {

			probability = 1.0 / allbits;

		}

		if (type_of_mutation == "Weak") {

			probability = 1.0 / (allbits * 3);

		}
		if (type_of_mutation == "Strong") {

			probability = 3.0 / allbits;
			if (probability > 1) {
				probability = 1;
			}

		}
		if (type_of_mutation == "Own") {

			if (!probability) {
				probability = 0.5;
			}

		}

		vector<bool> gen = child.get_binary();




		//cout << "mut" << endl;
		for (int i = 0; i < allbits; i++) {

			mut = rand() % 10000 / 10000.0;
			if (probability > mut) {
				gen[i] = !gen[i];
			}
		}
		Individual mut_child(child);
		mut_child.replace_code(gen);
		return mut_child;

	}
};



