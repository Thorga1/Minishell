#include "../../includes/minishell.h"

int ft_cd(const char *path)
{
    char *home;

    if (path == NULL || strlen(path) == 0)
    {
        home = getenv("HOME");
        if (home == NULL)
            return (1);
        if (chdir(home) == -1)
        {
            perror("cd");
            return (1);
        }
        return (0);
    }

    if (chdir(path) == -1)
    {
        printf("cd: command not found\n");
        return (1);
    }
    return (0);
}
