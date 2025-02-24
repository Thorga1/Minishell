#include "../../includes/minishell.h"

void ft_pwd(void)
{
    static char pwd[PATH_MAX];

    if (getcwd(pwd, PATH_MAX) == NULL)
    {
        perror("getcwd() error");
        return ;
    }
    printf("%s\n", pwd);
    return ;
}
