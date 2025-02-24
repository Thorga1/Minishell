#include "../../includes/minishell.h"

int ft_echo(char **args)
{
    int print_newline = 1;
    int i = 0;  // On commence à 0 car on n'a plus le nom du programme en args[0]
    
    if (args[i] && strcmp(args[i], "-n") == 0)
    {
        print_newline = 0;
        i++;
    }
    
    int first = 1;
    while (args[i])
    {
        if (!first)
            printf(" ");
        printf("%s", args[i]);
        first = 0;
        i++;
    }
    if (print_newline)
        printf("\n");
    return (0);
}
