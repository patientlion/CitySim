#include "population.h"

using namespace std;

template class Population<int>;  // Explicit instantiation

// Constructor for initialising population numbers
template <typename T>
Population<T>::Population(T workers, T teachers, T artists)
	: workers(workers), teachers(teachers), artists(artists) {}

// Method to return total population
template <typename T>
T Population<T>::total() const {
	return workers + teachers + artists;
}

// Method to decrement the count of a profession by 1
template <typename T>
void Population<T>::decrement(Profession prof) {
	switch (prof) {
	case Profession::Worker:
		if (workers > 0) workers--;
		break;
	case Profession::Teacher:
		if (teachers > 0) teachers--;
		break;
	case Profession::Artist:
		if (artists > 0) artists--;
		break;
	}
}

// Method to increment the count of a profession by 1
template <typename T>
void Population<T>::increment(Profession prof) {
	switch (prof) {
	case Profession::Worker:
		workers++;
		break;
	case Profession::Teacher:
		teachers++;
		break;
	case Profession::Artist:
		artists++;
		break;
	}
}

// Method to kill a random amount of the population
template <typename T>
int Population<T>::kill_random() {
		int total_killed = rand() % (total() + 1);
		int killed_workers = min(static_cast<int>(workers), total_killed / 3);
		int killed_teachers = min(static_cast<int>(teachers), total_killed / 3);
		int killed_artists = min(static_cast<int>(artists), total_killed - killed_workers - killed_teachers);

		workers -= killed_workers;
		teachers -= killed_teachers;
		artists -= killed_artists;

		return killed_workers + killed_teachers + killed_artists;
}


