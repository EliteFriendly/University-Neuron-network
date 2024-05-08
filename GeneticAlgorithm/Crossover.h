#pragma once
#include<iostream>
#include<vector>
#include"Individual.h"
class Crossover
{
protected:

public:
	virtual Individual get_child(Individual &parent1,
		Individual &parent2) = 0;
};



class OnePoint : public Crossover
{
public:
	Individual get_child(Individual& parent1,
		Individual& parent2);
};

class TwoPoint : public Crossover
{
public:
	Individual get_child(Individual& parent1,
		Individual& parent2);
};

class Uniform : public Crossover
{
public:
	Individual get_child(Individual& parent1,
		Individual& parent2);
};

