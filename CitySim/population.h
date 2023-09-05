#ifndef POPULATION_H
#define POPULATION_H
#include <iostream>
#include <cstdlib>    // for std::rand

// Enum to define professions
enum Profession {
	Worker,
	Teacher,
	Artist,
};

// Template class for Population to work with different data types for counts
template <typename T>
class Population {
public:
	T workers;
	T teachers;
	T artists;

	// Constructor for initialising population numbers
	Population(T workers = 0, T teachers = 0, T artists = 0);

	// Method to return total population
	T total() const;

	// Method to decrement the count of a profession by 1
	void decrement(Profession prof);

	// Method to increment the count of a profession by 1
	void increment(Profession prof);

	// Method to kill a random amount of the population
	int kill_random();
};

#endif // POPULATION_H
