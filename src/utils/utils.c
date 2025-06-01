/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:49:05 by thorgal           #+#    #+#             */
/*   Updated: 2025/06/02 00:14:33 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_current_dir_name(void)
{
	char	pwd[PATH_MAX];
	char	*dir;

	if (getcwd(pwd, PATH_MAX) == NULL)
		return (strdup("minishell"));
	dir = strrchr(pwd, '/');
	if (!dir || !dir[1])
		return (strdup(pwd));
	return (strdup(dir + 1));
}

char	*ft_get_env_var(char **env, char *var)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var);
	while (env[i])
	{
		if (ft_strncmp(env[i], var, len) == 0 && env[i][len] == '=')
			return (&env[i][len + 1]);
		i++;
	}
	return (NULL);
}

char	**copy_env(char **envp)
{
	char	**env;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	env = malloc(sizeof(char *) * (i + 1));
	if (!env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		env[i] = strdup(envp[i]);
		if (!env[i])
		{
			while (--i >= 0)
				free(env[i]);
			free(env);
			return (NULL);
		}
		i++;
	}
	env[i] = NULL;
	return (env);
}

char	*get_env_value(char *var_name, t_shell *shell)
{
	int	i;
	int	var_len;

	if (!var_name || !shell || !shell->env)
		return (NULL);
	if (var_name[0] == '$')
		var_name++;
	if (var_name[0] == '?')
	{
		printf("%d", shell->exit_status);
		return (0);
	}
	var_len = 0;
	while (var_name[var_len] && (ft_isalnum(var_name[var_len]) \
	|| var_name[var_len] == '_'))
		var_len++;
	if (var_len == 0)
		return (NULL);
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], var_name, var_len) == 0
			&& shell->env[i][var_len] == '=')
			return (shell->env[i] + var_len + 1);
		i++;
	}
	return (NULL);
}
