#include "Model.hpp"
#include "Ollama.hpp"
#include "Signals.hpp"
#include "History.hpp"

int	main(void)
{
	Ollama jarvis;

	jarvis.getOllamaList();
	printWelcome();
	jarvis.setPrompt();
	jarvis.loadConfig();

	while (true)
	{
		// Set Signal Handler
		setSignalHandler();

		// Get command from user
		jarvis.setCmd(readline(jarvis.getPrompt().c_str()));

		// Check if command is empty
		if (jarvis.getCmd() == nullptr)
			break ;

		// Add command to history
		if (!history(jarvis.getCmd()))
			continue ;
		add_history(jarvis.getCmd());
		
		// Handle Command
		if (jarvis.handleCommand(jarvis.getCmd()) == -1)
		{
			free(jarvis.getCmd());
			break ;
		}
		free(jarvis.getCmd());
	}

	return (EXIT_SUCCESS);
}
