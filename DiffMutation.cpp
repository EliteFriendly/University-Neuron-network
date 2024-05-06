#include "DiffMutation.h"

void DiffMutation::outLimits(IndividualDiffEvolution donor)
{
    vector<double> coordinats = donor.getCoordinats();

    for (int i = 0; i < limitsDimension.size(); i+=2) {
        if (!(limitsDimension[i] <= donor.getCoordinats()[i / 2]) ) {
            coordinats[i / 2] = (limitsDimension[i] + coordinats[i / 2]) / 2;
        }
        if (!(limitsDimension[i+1] >= donor.getCoordinats()[i / 2])) {
            coordinats[i / 2] = (limitsDimension[i+1] + coordinats[i / 2]) / 2;
        }
    }
    donor.replaceCoordinats(coordinats);
}

IndividualDiffEvolution DiffMutation::getDonor(vector<IndividualDiffEvolution>& arrIndividuals, IndividualDiffEvolution& best)
{
    selectedInd.resize(ammount);
    int number;
    IndividualDiffEvolution donor;

    for (int i = 0; i < ammount; i++) {
        number = rand() % arrIndividuals.size();
        while (find(selectedInd.begin(), selectedInd.end(),number)!= selectedInd.end())
            number = rand() % arrIndividuals.size();
        selectedInd[i] = number;
    }


    if (type == "rand1") {
        donor=( arrIndividuals[selectedInd[0]] + ((arrIndividuals[selectedInd[1]]
            - arrIndividuals[selectedInd[2]]) * F) );
    }

    if (type == "rand2") {
        donor = arrIndividuals[selectedInd[0]]+(arrIndividuals[selectedInd[1]]- arrIndividuals[selectedInd[2]])*F+
            (arrIndividuals[selectedInd[3]]- arrIndividuals[selectedInd[4]])*F;
    }

    if (type == "best1") {
        donor = best+(arrIndividuals[selectedInd[0]]- arrIndividuals[selectedInd[1]])*F;
    }

    if (type == "best2") {
        donor = best + (arrIndividuals[selectedInd[0]] - arrIndividuals[selectedInd[1]]) * F +
            (arrIndividuals[selectedInd[2]] - arrIndividuals[selectedInd[3]]) * F;
    }

    if (type == "targetToRand1") {
        donor = arrIndividuals[selectedInd[0]] + (arrIndividuals[selectedInd[1]] - arrIndividuals[selectedInd[0]]) * F +
            (arrIndividuals[selectedInd[2]] - arrIndividuals[selectedInd[3]]) * F;
    }
    if (type == "targetToBest1") {
        donor = arrIndividuals[selectedInd[0]] + (best - arrIndividuals[selectedInd[0]]) * F +
            (arrIndividuals[selectedInd[1]] - arrIndividuals[selectedInd[2]]) * F;
    }


    outLimits(donor);
    return donor;
}
