#include "History.hpp"

void addToHistory(string cmd)
{
    char *tmp = static_cast<char *>(malloc(sizeof(char) * cmd.length() + 1));
    strcpy(tmp, cmd.c_str());
    
    if (tmp[0] == '\0')
    {
        free(tmp);
        return ;
    }
    add_history(tmp);
    free(tmp);
    return ;
}