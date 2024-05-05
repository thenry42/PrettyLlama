#include "Meta.hpp"
#include "Model.hpp"

int	main(int ac, char **av)
{
	Meta meta;

	if (ac != 2)
		return (EXIT_FAILURE);

	// Get models info using ollama list
	meta.getModelsInfo();
	meta.printModels();

	// Pass user prompt to every model
	meta.answerPrompt(av[1]);

	return (EXIT_SUCCESS);
}
