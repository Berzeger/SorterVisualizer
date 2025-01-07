#include <iostream>
#include "application/sfml_application.h"
#include "application/sdl_application.h"
#include "sort_algorithm_registry.h"

int main(int argc, char** argv)
{
	std::unique_ptr<Application> app;
	int libChoice;

	// let the user select the library (SDL/SFML)
LIB_CHOICE:
	std::cout << "Select library:\n1. SFML\n2. SDL\n";
	std::cin >> libChoice;

	switch (libChoice)
	{
	case 1:
		app = std::make_unique<SfmlApplication>();
		break;
	case 2:
		app = std::make_unique<SdlApplication>();
		break;
	default:
		std::cout << "Unrecognized choice.\n";
		goto LIB_CHOICE;
	}

	// let the user select the algorithm
	auto sortAlgorithmNames = SortAlgorithmRegistry::instance().getRegisteredNames();
	
SORT_ALGORITHM_CHOICE:
	std::cout << "Select sorting algorithm:\n";
	size_t nSortAlgorithms = sortAlgorithmNames.size();
	for (size_t i = 0; i < nSortAlgorithms; ++i)
	{
		std::cout << i + 1 << ". " << sortAlgorithmNames[i] << "\n";
	}

	int sortAlgorithmChoice;
	std::cin >> sortAlgorithmChoice;

	if (sortAlgorithmChoice < 1 || sortAlgorithmChoice > nSortAlgorithms)
	{
		std::cout << "Unrecognized choice.\n";
		goto SORT_ALGORITHM_CHOICE;
	}

	std::string chosenName = sortAlgorithmNames[sortAlgorithmChoice - 1];

	// create the algorithm
	auto mySorter = SortAlgorithmRegistry::instance().createSortAlgorithm(chosenName);

	app->run(std::move(mySorter));

	return 0; // SDL requires the main function to return, even though standard C++ doesn't need it.
}
