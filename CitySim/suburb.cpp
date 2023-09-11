#include "suburb.h"
#include <iostream>

using namespace std;

// Constructor to initialise the suburb with given ID
Suburb::Suburb(int i) : id(i), migrated_in(0, 0, 0), migrated_out(0, 0, 0) {}

// Function to determine the number of people preparing to move
int Suburb::prepare_to_move() {
	return rand() % (pop.total() + 1);
}

// Function to reset migration counters to initial state
void Suburb::reset_migrated_counters() {
	migrated_in = Population<int>();
	migrated_out = Population<int>();
}

// Function to print current suburb's population details
void Suburb::print() const {
	cout << "\nSuburb " << id << ": Workers: " << pop.workers
		<< ", Teachers: " << pop.teachers
		<< ", Artists: " << pop.artists
		<< ", Total: " << pop.total() << "\n";
}

// Function to print migration statistics for the suburb
void Suburb::print_migration_stats() const {
	cout << "Suburb " << id << " Migration Stats: \n"
		<< "Migrated In - Workers: " << migrated_in.workers
		<< ", Teachers: " << migrated_in.teachers
		<< ", Artists: " << migrated_in.artists
		<< ", Total: " << migrated_in.total() << "\n"
		<< "Migrated Out - Workers: " << migrated_out.workers
		<< ", Teachers: " << migrated_out.teachers
		<< ", Artists: " << migrated_out.artists
		<< ", Total: " << migrated_out.total() << "\n";
}
