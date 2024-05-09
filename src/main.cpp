#include "Meta.hpp"
#include "Model.hpp"
#include "imgui.h"

int	main(int ac, char **av)
{
	Meta meta;

	if (ac != 2)
		return (EXIT_FAILURE);

	(void)av, (void)meta;

	// Get models info using ollama list
	//meta.getModelInfos();
	//meta.printModels();

	// Pass user prompt to every model
	//meta.setPrompt(av[1]);

	// Aks models for answers
	//meta.askModels();

	// imgui build that work for my machine
	// - example_glfw_opengl2 (not the greatest)
	// - example_glfw_opengl3 (not the greatest)
	// - example_sdl2_opengl3
	// - example_sdl2_opengl2
	// - example_sdl2_sdlrenderer2
	
	// Show Demo Window
	ImGui::CreateContext();
	ImGui::ShowDemoWindow();

	return (EXIT_SUCCESS);
}
