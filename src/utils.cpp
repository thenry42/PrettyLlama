#include "utils.hpp"
#include <SDL2/SDL.h>
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

int* getScreenSize(void)
{
    int *size = new int[2];
    
    // Bash cmd:
    // $> xrandr | grep "current" | cut -d' ' -f4- | awk '{print $5, $7}' | rev | cut -c2- | rev
    
    size[0] = 2560;
    size[1] = 1600;
    return (size);
}