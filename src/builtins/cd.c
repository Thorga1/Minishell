#include "../../includes/minishell.h"

int ft_cd(const char *path)
{
    if (path == NULL || strlen(path) == 0)
    {
        char *home = getenv("HOME");
        if (home == NULL)
            return (-1);
        return (chdir(home));
    }
    if (chdir(path) == -1)
    {
        perror("cd:");
        return (-1);
    }
    return (0);
}

/*int main(int ac, char **av)
{
    if (ac > 2)
    {
        printf("Error: too many arguments\n");
        return (1);
    }
    return (ft_cd(av[1]));
}*/