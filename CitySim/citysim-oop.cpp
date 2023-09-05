#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include "population.h"
#include "suburb.h"

using namespace std;

// Enum to define disasters
enum Disaster {
	Earthquake,
	Asteroid,
	Cyclone,
	Plague,
};

void disaster_strike(vector<Suburb>& suburbs, float disaster_chance) {
	// Compare a random float in the range [0, 1) with disaster_chance
	if ((float)rand() / RAND_MAX < disaster_chance) {
		int disaster_index = rand() % 4;
		int suburb_index = rand() % suburbs.size();
		int affected_neighbours_count = 0;  // Counter for affected neighbouring suburbs

		// Directly cast disaster_index to the Disaster enum type
		Disaster disaster = (Disaster)disaster_index;
		string disaster_name;

		switch (disaster) {
		case Disaster::Earthquake:
			disaster_name = "Earthquake";
			break;
		case Disaster::Asteroid:
			disaster_name = "Asteroid";
			break;
		case Disaster::Cyclone:
			disaster_name = "Cyclone";
			break;
		case Disaster::Plague:
			disaster_name = "Plague";
			break;
		}

		cout << "Disaster struck! " << disaster_name << " has hit Suburb " << suburbs[suburb_index].id << ".\n";

		// Apply the same disaster to the neighbouring suburbs randomly
		cout << "Neighbouring Suburbs affected by " << disaster_name << ":\n";
		for (int neighbour_id : suburbs[suburb_index].neighbour_ids) {
			// Randomly decide whether this neighbouring suburb is affected or not
			if ((float)rand() / RAND_MAX < 0.5) {  // 0.5 is a placeholder probability 
				int neighbour_mortality = suburbs[neighbour_id - 1].pop.kill_random();
				cout << "Suburb " << neighbour_id << " - Mortality: " << neighbour_mortality << "\n";
				affected_neighbours_count++;  // Increase the counter
			}
		}

		// If no neighbouring suburbs are affected, print a specific message
		if (affected_neighbours_count == 0) {
			cout << "No neighbouring suburbs affected by the disaster.\n";
		}
	}
}


int main() {
	cout <<
		" ## ##     ####   #### ##  ##  ##          ## ##     ####   ##   ##  \n"
		"##   ##     ##    # ## ##  ##  ##         ##   ##     ##     ## ##   \n"
		"##          ##      ##     ##  ##         ####        ##    # ### #  \n"
		"##          ##      ##      ## ##          #####      ##    ## # ##  \n"
		"##          ##      ##       ##               ###     ##    ##   ##  \n"
		"##   ##     ##      ##       ##           ##   ##     ##    ##   ##  \n"
		" ## ##     ####    ####      ##            ## ##     ####   ##   ##  \n"
		"                                                                     \n";

	srand(static_cast<unsigned int>(time(0)));

	// Create 8 suburbs using a vector
	vector<Suburb> suburbs(8, Suburb(0));
	for (int i = 0; i < 8; i++) {
		suburbs[i].id = i + 1; // Assign an id to each suburb
		// Randomly initialize the population for each suburb
		suburbs[i].pop = Population<int>(rand() % 100, rand() % 100, rand() % 100);
	}

	// Define the neighbors for each suburb
	suburbs[0].neighbour_ids = { 2, 3, 4, 5, 8 };
	suburbs[1].neighbour_ids = { 1, 3, 6, 8 };
	suburbs[2].neighbour_ids = { 1, 2, 4, 6 };
	suburbs[3].neighbour_ids = { 1, 3, 5, 6 };
	suburbs[4].neighbour_ids = { 1, 4, 6, 7 };
	suburbs[5].neighbour_ids = { 2, 3, 4, 5, 8 };
	suburbs[6].neighbour_ids = { 5 };
	suburbs[7].neighbour_ids = { 1, 2, 6 };

	int turns;
	// Continue asking for input until a positive integer is entered
	do {
		// Ask the user to input the number of turns to simulate
		cout << "Enter the number of turns to simulate (must be positive): ";
		cin >> turns;
		cin.ignore(); // Clears the input buffer

		// If the input is not positive, display an error message
		if (turns <= 0) {
			cout << "Error: Please enter a positive integer. Try again.\n";
		}
	} while (turns <= 0);

	float disaster_chance;
	// Continue asking for input until a float between 0 and 1 is entered
	do {
		// Ask the user to input the chance of a disaster occurring each turn
		cout << "Enter the chance of a disaster occurring each turn (as a float between 0 and 1, e.g. 0.05 for 5%): ";
		cin >> disaster_chance;
		cin.ignore(); // Clears the input buffer

		// If the input is not a float between 0 and 1, display an error message
		if (disaster_chance < 0.0f || disaster_chance > 1.0f) {
			cout << "Error: Please enter a float between 0 and 1. Try again.\n";
		}
	} while (disaster_chance < 0.0f || disaster_chance > 1.0f);

	// Simulation loop for the number of turns
	for (int i = 0; i < turns; i++) {
		cout << "\nTurn " << i + 1 << "\n"; // Output the turn number

		// Check for disasters at the start of the turn
		disaster_strike(suburbs, disaster_chance);

		int total_population = 0;

		// Iterate through each suburb
		for (auto& suburb : suburbs) {
			int num = suburb.prepare_to_move(); // Prepare the number of people moving
			// Move people while there are still people to move
			while (num > 0 && suburb.pop.total() > 0) {
				int to_id = suburb.neighbour_ids[rand() % suburb.neighbour_ids.size()]; // Choose a random neighboring suburb
				Suburb& to = suburbs[to_id - 1];

				// Randomly select a profession to move
				Profession type = static_cast<Profession>(rand() % 3);

				// Check if the suburb has the profession to move and move them
				if ((type == Profession::Worker && suburb.pop.workers > 0) ||
					(type == Profession::Teacher && suburb.pop.teachers > 0) ||
					(type == Profession::Artist && suburb.pop.artists > 0)) {
					suburb.pop.decrement(type);
					to.pop.increment(type);
					suburb.migrated_out.increment(type);
					to.migrated_in.increment(type);
					num--;
				}
			}

			suburb.print(); // Print population details for the current suburb
			if (i > 0) {
				suburb.print_migration_stats(); // Print migration stats for the current suburb
			}
			suburb.reset_migrated_counters(); // Reset migration counters for the current suburb
			total_population += suburb.pop.total(); // Add the current suburb's population to the total
		}

		cout << "\nTotal Population: " << total_population << "\n"; // Output the total population of all suburbs

		// Pause for the user to continue to the next turn
		if (i < turns - 1) {
			cout << "\nPress enter to continue to the next turn...\n";
			cin.get();
		}
	}
}