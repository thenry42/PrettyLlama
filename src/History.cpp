#include "History.hpp"

bool    history(char *str)
{
    int i = 0;
    if (!str || str[0] == '\0')
        return (false);
    while (str[i])
    {
        if (!isspace(str[i]))
            return (true);
        i++;
    }
    return (false);
}