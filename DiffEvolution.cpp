#include "DiffEvolution.h"


IndividualDiffEvolution DiffEvolution::crossover(IndividualDiffEvolution donor)
{
	
	int ammount=0;//���������� ��� ����� ��������� ������
	int number = rand() % arrIndividuals.size();//����� ��������
	double rep;//����������� �������� ����������
	vector<double> coordinates = donor.getCoordinats();

	//������� ��������� ����
	for (int i = 0; i < (limitsDimension.size() / 2); i++) {
		rep = rand() % 1000 / 1000.0;
		if (rep < Cr) {
			coordinates[i] = arrIndividuals[number].getCoordinats()[i];
			ammount++;
		}
	}
	if (ammount == 0) {//� ������ ���� ��� �� ���� �� ���������
		int ran = rand() % (limitsDimension.size() / 2);
		coordinates[ran] = arrIndividuals[number].getCoordinats()[ran];
	}
	donor.replaceCoordinats(coordinates);
	return donor;
}

void DiffEvolution::surviveCrossover(IndividualDiffEvolution trial)
{
	for (int i = 0; i < N; i++) {
		if (arrIndividuals[i] < trial) {
			arrIndividuals[i] = trial;
			break;
		}
	}
}

void DiffEvolution::saveBest()
{
	for (int i = 0; i < N; i++) {
		if (best < arrIndividuals[i]) {
			best = arrIndividuals[i];
		}
	}
}

void DiffEvolution::startSearch(double acc, double F, double Cr, int N, int generations) {
	DiffEvolution::F = F;
	DiffEvolution::Cr = Cr;
	DiffEvolution::N = N;
	DiffEvolution::generations = generations;
	mutation.setF(F);//���������� ��� ���������� ������ �������

	arrIndividuals.resize(N);
	//��������� ������ ���������
	for (int i = 0; i < N; i++) {
		IndividualDiffEvolution ind(limitsDimension, acc);
		arrIndividuals[i] = ind;
		arrIndividuals[i].calcFitness(func,aim);
	}
	saveBest();

	//������ ������ �������� ����� ���������
	IndividualDiffEvolution newInd;
	for (int i = 0; i < generations; i++)
	{
		/*if (i == 18) {
			cout << "������ �������:" << endl;
		}*/
		for (int j = 0; j < N; j++) {
			/*if (j == 9) {
				cout << endl;
			}*/
			newInd = mutation.getDonor(arrIndividuals,best);
			newInd = crossover(newInd);
			newInd.calcFitness(func,aim);
			surviveCrossover(newInd);
		}
		saveBest();
	}
	

}
