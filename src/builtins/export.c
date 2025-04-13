#include "minishell.h"

static int is_valid_identifier(char *str)
{
    int i;

    if (!str || !*str)
        return (0);
    
    if (!((str[0] >= 'a' && str[0] <= 'z') || 
          (str[0] >= 'A' && str[0] <= 'Z') || 
          str[0] == '_'))
        return (0);
    i = 1;
    while (str[i] && str[i] != '=')
    {
        if (!((str[i] >= 'a' && str[i] <= 'z') || 
              (str[i] >= 'A' && str[i] <= 'Z') || 
              (str[i] >= '0' && str[i] <= '9') || 
              str[i] == '_'))
            return (0);
        i++;
    }
    return (1);
}

static char **add_env_var(char **env, char *new_var)
{
    char **new_env;
    int i;
    int count;

    count = 0;
    while (env[count])
        count++;
    new_env = malloc(sizeof(char *) * (count + 2));
    if (!new_env)
        return (NULL);
    i = 0;
    while (i < count)
    {
        new_env[i] = env[i];
        i++;
    }
    new_env[i] = strdup(new_var);
    if (!new_env[i])
    {
        free(new_env);
        return (NULL);
    }
    new_env[i + 1] = NULL;
    free(env);
    return (new_env);
}

static int update_env_var(char **env, char *var)
{
    int i;
    char *equal_sign;
    int var_name_len;
    
    equal_sign = strchr(var, '=');
    if (!equal_sign)
        return (0);
    var_name_len = equal_sign - var;
    i = 0;
    while (env[i])
    {
        if (strncmp(env[i], var, var_name_len) == 0 && 
            (env[i][var_name_len] == '=' || env[i][var_name_len] == '\0'))
        {
            free(env[i]);
            env[i] = strdup(var);
            if (!env[i])
                return (-1);
            return (1);
        }
        i++;
    }
    return (0);
}
int ft_export(t_shell *shell, t_smd *cmd)
{
    int i;
    int ret;
    if (!cmd->args[1])
    {
        i = 0;
        while (shell->env[i])
        {
            printf("declare -x %s\n", shell->env[i]);
            i++;
        }
        return (0);
    }
    i = 1;
    ret = 0;
    while (cmd->args[i])
    {
        if (!is_valid_identifier(cmd->args[i]))
        {
            printf("export: '%s': not a valid identifier\n", cmd->args[i]);
            ret = 1;
            i++;
            continue;
        }
        if (strchr(cmd->args[i], '='))
        {
            int update_result = update_env_var(shell->env, cmd->args[i]);
            
            if (update_result == 0)
            {
                shell->env = add_env_var(shell->env, cmd->args[i]);
                if (!shell->env)
                {
                    printf("export: memory allocation error\n");
                    return (1);
                }
            }
            else if (update_result == -1)
            {
                printf("export: memory allocation error\n");
                return (1);
            }
        }
        i++;
    }
    return (ret);
}