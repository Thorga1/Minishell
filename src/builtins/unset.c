#include "../../includes/minishell.h"
int	delete_line(char **array, int index)
{
    if (!array[index])
        return (0);
    free(array[index]);
    while (array[index + 1])
    {
        array[index] = array[index + 1];
        index++;
    }
    array[index] = NULL;
    return (1);
}

int find_env_var(char **env, char *var)
{
    int i;
    int len;

    i = 0;
    len = ft_strlen(var);
    while (env[i])
    {
        if (ft_strncmp(env[i], var, len) == 0 && env[i][len] == '=')
    return (i);
        i++;
    }
    return (-1);
}

int	ft_unset(t_shell *shell, t_smd *cmd)
{
    int i;
    int index;

    i = 1;
    while (cmd->args[i])
    {
        index = find_env_var(shell->env, cmd->args[i]);
        if (index != -1)
            delete_line(shell->env, index);
        i++;
    }
    return (0);
}
