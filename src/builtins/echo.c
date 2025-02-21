#include "../../includes/minishell.h"

int ft_echo(char **args)
{
    int print_newline = 1;
    int i = 1;
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

/*int main(int ac, char **av)
{
    (void)ac;
    return (ft_echo(av));
}*/