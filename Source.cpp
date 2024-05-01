#include <iostream>
#include <vector>
#include <functional>
#include "NeuronNetwork.h"
using namespace std;

void main() {

	srand(time(0));
	NeuronNetwork proba(2, 2, 1);
	
	cout<<proba.getValue({ 0 })<<endl;
	proba.changeW();
	cout << proba.getValue({ 0 });
}