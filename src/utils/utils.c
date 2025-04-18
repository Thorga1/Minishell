/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:49:05 by thorgal           #+#    #+#             */
/*   Updated: 2025/04/18 14:01:00 by tordner          ###   ########.fr       */
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

int	is_git_repository(void)
{
	FILE	*fp;
	int		result;
	char	line[10];

	result = 0;
	fp = popen("git rev-parse --is-inside-work-tree 2>/dev/null", "r");
	if (fp != NULL)
	{
		if (fgets(line, sizeof(line), fp) != NULL)
		{
			if (strncmp(line, "true", 4) == 0)
				result = 1;
		}
		pclose(fp);
	}
	return (result);
}

char	*get_git_branch(void)
{
	FILE	*fp;
	char	*branch;
	char	line[1024];

	branch = NULL;
	fp = popen("git branch 2>/dev/null | grep \\* | cut -d ' ' -f2", "r");
	if (fp == NULL)
		return (NULL);
	if (fgets(line, sizeof(line), fp) != NULL)
	{
		line[strcspn(line, "\n")] = 0;
		branch = strdup(line);
	}
	pclose(fp);
	return (branch);
}
