/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:49:05 by thorgal           #+#    #+#             */
/*   Updated: 2025/06/02 23:59:34 by tordner          ###   ########.fr       */
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
