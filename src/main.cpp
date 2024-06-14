#include "Ollama.hpp"
#include "Model.hpp"

int	main(void)
{
	Ollama jarvis;
	
	jarvis.getOllamaList();
	jarvis.printWelcome();
	jarvis.setPrompt();

	while (true)
	{
		cout << jarvis.getPrompt();

		// Ask user to choose a model
		getline(cin, jarvis.cmd);

		// Handle Command
		if (jarvis.handleCommand(jarvis.cmd) == -1)
			break ;
	}

	return (EXIT_SUCCESS);
}
