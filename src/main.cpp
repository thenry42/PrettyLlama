#include "Ollama.hpp"
#include "Model.hpp"

int	main(void)
{
	Ollama jarvis;

	jarvis.getOllamaList();
	jarvis.printWelcome();
	jarvis.setPrompt();

	jarvis.loadConfig();

	while (true)
	{
		cout << jarvis.getPrompt();

		// Get User Input
		if (!getline(cin, jarvis.cmd))
		{
			if (cin.eof())
				break ;
		}

		// Handle Command
		if (jarvis.handleCommand(jarvis.cmd) == -1)
			break ;
	}

	return (EXIT_SUCCESS);
}
