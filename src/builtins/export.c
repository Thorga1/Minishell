/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:54:38 by lfirmin           #+#    #+#             */
/*   Updated: 2025/04/23 11:59:42 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	if (!((str[0] >= 'a' && str[0] <= 'z')
			|| (str[0] >= 'A' && str[0] <= 'Z')
			|| str[0] == '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!((str[i] >= 'a' && str[i] <= 'z')
				|| (str[i] >= 'A' && str[i] <= 'Z')
				|| (str[i] >= '0' && str[i] <= '9')
				|| str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

char	**add_env_var(char **env, char *new_var)
{
	char	**new_env;
	int		i;
	int		count;

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
	new_env[i] = ft_strdup(new_var);
	if (!new_env[i])
		return (free(new_env), NULL);
	new_env[i + 1] = NULL;
	free(env);
	return (new_env);
}

int	update_env_var(char **env, char *var)
{
	int		i;
	char	*equal_sign;
	int		var_name_len;

	equal_sign = ft_strchr(var, '=');
	if (!equal_sign)
		return (0);
	var_name_len = equal_sign - var;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, var_name_len) == 0
			&& (env[i][var_name_len] == '=' || env[i][var_name_len] == '\0'))
		{
			free(env[i]);
			env[i] = ft_strdup(var);
			if (!env[i])
				return (-1);
			return (1);
		}
		i++;
	}
	return (0);
}

int	process_export_args(t_shell *shell, char **args, int i)
{
	int	ret;
	int	status;

	ret = 0;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			printf("export: '%s': not a valid identifier\n", args[i]);
			ret = 1;
			i++;
			continue ;
		}
		if (ft_strchr(args[i], '='))
		{
			status = handle_env_var(shell, args[i]);
			if (status != 0)
				return (status);
		}
		i++;
	}
	return (ret);
}

int	ft_export(t_shell *shell, t_cmd *cmd)
{
	int	i;

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
	return (process_export_args(shell, cmd->args, 1));
}
