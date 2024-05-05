#include "Meta.hpp"
#include "Model.hpp"

int	main(int ac, char **av)
{
	Meta meta;

	if (ac != 2)
		return (EXIT_FAILURE);

	// Get models info using ollama list
	meta.getModelsInfo();
	//meta.printModels();

	// Pass user prompt to every model
	meta.setPrompt(av[1]);
	//meta.printModels();

	// Aks models for answers
	meta.askModels();

	return (EXIT_SUCCESS);
}
