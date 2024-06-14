#include "Ollama.hpp"
#include "Model.hpp"
#include "History.hpp"

int	main(void)
{
	Ollama jarvis;
	
	jarvis.getOllamaList();
	jarvis.printWelcome();
	jarvis.setPrompt();

	while (true)
	{
		cout << jarvis.getPrompt();

		// Get User Input
		getline(cin, jarvis.cmd);
		addToHistory(jarvis.cmd);

		// Handle Command
		if (jarvis.handleCommand(jarvis.cmd) == -1)
			break ;
	}

	return (EXIT_SUCCESS);
}
