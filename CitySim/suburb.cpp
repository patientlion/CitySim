#include "suburb.h"
#include <iostream>

using namespace std;

Suburb::Suburb(int i) : id(i), migrated_in(0, 0, 0), migrated_out(0, 0, 0) {}

int Suburb::prepare_to_move() {
	return rand() % (pop.total() + 1);
}

void Suburb::reset_migrated_counters() {
	migrated_in = Population<int>();
	migrated_out = Population<int>();
}

void Suburb::print() const {
	cout << "\nSuburb " << id << ": Workers: " << pop.workers
		<< ", Teachers: " << pop.teachers
		<< ", Artists: " << pop.artists
		<< ", Total: " << pop.total() << "\n";
}

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
