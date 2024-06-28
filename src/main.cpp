#include "Model.hpp"
#include "Ollama.hpp"
#include "Signals.hpp"
#include "History.hpp"

int	main(void)
{
	Ollama jarvis;

	jarvis.getOllamaList();
	jarvis.printWelcome();
	jarvis.setPrompt();

	jarvis.loadConfig();

	while (true)
	{
		// Set Signal Handler
		setSignalHandler();

		// Get command from user
		jarvis.command = readline(jarvis.getPrompt().c_str());

		// Check if command is empty
		if (jarvis.command == nullptr)
			break ;

		// Add command to history
		if (history(jarvis.command))
			add_history(jarvis.command);
		else
			continue;
		
		// Handle Command
		if (jarvis.handleCommand(jarvis.command) == -1)
			break ;
		free(jarvis.command);
	}

	return (EXIT_SUCCESS);
}
