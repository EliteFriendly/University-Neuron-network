#include "IndividualDiffEvolution.h"


IndividualDiffEvolution::IndividualDiffEvolution(vector <double> limitsDimension, function<double(vector<double>)>func, double acc,string aim) :
	limitsDimension(limitsDimension), func(func), acc(acc), aim(aim) {
	coordinats.resize(limitsDimension.size() / 2);
	int n;//Хранит количество точек, временна

	for (int i = 0; i < limitsDimension.size(); i+=2) {
		n = (abs(limitsDimension[i] - limitsDimension[i + 1])) / acc;
		coordinats[i / 2] = (rand() % n)*acc + limitsDimension[i];

	}
	calcFitness();

}

IndividualDiffEvolution::IndividualDiffEvolution(const IndividualDiffEvolution& copy):
	limitsDimension(copy.limitsDimension), func(copy.func), 
	acc(copy.acc),fitness(copy.fitness),coordinats(copy.coordinats),aim(copy.aim){}

















bool IndividualDiffEvolution::operator <(const IndividualDiffEvolution& copy) {
	if (fitness < copy.fitness)
		return true;
	return false;
}
bool IndividualDiffEvolution::operator >(const IndividualDiffEvolution& copy) {
	if (fitness > copy.fitness)
		return true;
	return false;
}
bool IndividualDiffEvolution::operator ==(const IndividualDiffEvolution& copy) {
	if (fitness == copy.fitness)
		return true;
	return false;
}

IndividualDiffEvolution IndividualDiffEvolution::operator+(const IndividualDiffEvolution& sec) 
{
	IndividualDiffEvolution copy(*this);
	for (int i = 0; i < copy.coordinats.size(); i++) {
		copy.coordinats[i] += sec.coordinats[i];
	}
	copy.fitness = copy.func(coordinats);
	return copy;
}




IndividualDiffEvolution IndividualDiffEvolution::operator -(const IndividualDiffEvolution& sec)
{
	IndividualDiffEvolution copy(*this);
	for (int i = 0; i < copy.coordinats.size(); i++) {
		copy.coordinats[i] = copy.coordinats[i]- sec.coordinats[i];
	}
	copy.fitness = copy.func(coordinats);
	return copy;
}
IndividualDiffEvolution IndividualDiffEvolution::operator *(double sec)
{
	IndividualDiffEvolution copy(*this);
	for (int i = 0; i < copy.coordinats.size(); i++) {
		copy.coordinats[i] *= sec;
	}
	copy.fitness = copy.func(coordinats);
	return copy;
}