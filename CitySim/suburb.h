#ifndef SUBURB_H
#define SUBURB_H
#include <vector>
#include "population.h"

class Suburb {
public:
	int id;                          // ID of the suburb
	Population<int> pop;             // Population of the suburb
	Population<int> migrated_in;     // Population migrated into the suburb
	Population<int> migrated_out;    // Population migrated out of the suburb
	std::vector<int> neighbour_ids;  // IDs of neighbouring suburbs

	// Constructor to initialise the suburb with given ID
	Suburb(int i);

	// Function to determine the number of people preparing to move
	int prepare_to_move();

	// Function to reset migration counters to initial state
	void reset_migrated_counters();

	// Function to print current suburb's population details
	void print() const;

	// Function to print migration statistics for the suburb
	void print_migration_stats() const;
};
#endif // SUBURB_H