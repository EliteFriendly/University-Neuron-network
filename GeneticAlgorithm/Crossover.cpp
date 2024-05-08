#include "Crossover.h"

Individual OnePoint::get_child(Individual &parent1,
	Individual &parent2) 
{
	bool* gen = parent2.get_binary();//Возможен мусор в памяти!!!!!
	int break_point = rand() % parent2.get_allbits();
	for (int i = 0; i < break_point; i++) {
		gen[i] = parent1.get_binary()[i];
	}
	Individual child(parent1);
	child.replace_code(gen);
	return child;
}


Individual TwoPoint::get_child(Individual& parent1,
	Individual& parent2) 
{
	bool* gen = parent2.get_binary();
	int break_point1 = rand() % parent2.get_allbits();
	int break_point2 = rand() % parent2.get_allbits();
	while (break_point1 == break_point2) {
		break_point2 = rand() % parent2.get_allbits();
	}
	int point1 = min(break_point1, break_point2);
	int point2 = max(break_point1, break_point2);
	for (int i = point1; i < point2; i++) {
		gen[i] = parent1.get_binary()[i];
	}
	Individual child(parent1);
	child.replace_code(gen);
	return child;
}


Individual Uniform::get_child(Individual& parent1,
	Individual& parent2)
{
	bool* gen = parent2.get_binary();
	int ra;
	for (int i = 0; i < parent2.get_allbits(); i++) {
		ra = rand() % 2;
		if (ra == 1) {
			gen[i] = parent1.get_binary()[i];
		}
		
	}
	Individual child(parent1);
	child.replace_code(gen);
	return child;
}