#include "Signals.hpp"

void    signalHandler(int signum)
{
    if (signum == SIGINT)
    {
        std::cout << std::endl;
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
}

void    setSignalHandler(void)
{
    signal(SIGINT, signalHandler);
    signal(SIGQUIT, SIG_IGN);
}