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

	Suburb(int i);

	int prepare_to_move();

	void reset_migrated_counters();

	void print() const;

	void print_migration_stats() const;
};
#endif // SUBURB_H