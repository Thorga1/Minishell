#include "../../includes/minishell.h"

int ft_cd(t_cmd *cmd, t_shell *shell)
{
    char *home;
    char *path;

    if (!cmd || !cmd->args || !cmd->args[1] || ft_strlen(cmd->args[1]) == 0)
    {
        home = ft_get_env_var(shell->env, "HOME");
        if (home == NULL)
            return (1);
        if (chdir(home) == -1)
        {
            perror("cd");
            return (1);
        }
        return (0);
    }
    path = cmd->args[1];
    if (chdir(path) == -1)
    {
        printf("cd: %s: No such file or directory\n", path);
        return (1);
    }
    return (0);
}
