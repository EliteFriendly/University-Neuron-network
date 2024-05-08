#include "SurviveCrossover.h"



vector<Individual> BestAndOffspring::forming(vector<Individual> individuals, vector<Individual> childs) {
	max = individuals[0].get_fitness();
	for (int i = 0; i < individuals.size(); i++) {
		if (individuals[i].get_fitness() > max) {
			max = individuals[i].get_fitness();
			number = i;
		}
	}
	individuals[0] = individuals[number];

	for (int i = 1; i < individuals.size(); i++) {
		individuals[i] = childs[i];
	}
	childs.clear();
	return individuals;
}


vector<Individual> OnlyOffspring::forming(vector<Individual> individuals, vector<Individual> childs) {
	return childs;
}



void BestIndividualsAndOffspring::sortv(vector<Individual>& arr) {
	int listLength = arr.size();
	while (listLength--)
	{
		bool swapped = false;

		for (int i = 0; i < listLength; i++)
		{
			if (arr[i].get_fitness() < arr[i + 1].get_fitness())
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
vector<Individual> BestIndividualsAndOffspring::forming(vector<Individual> individuals, vector<Individual> childs) {
	int size = individuals.size();
	individuals.insert(individuals.end(), childs.begin(), childs.end());
	sortv(individuals);
	individuals.erase(individuals.begin()+size, individuals.end());
	return individuals;
}