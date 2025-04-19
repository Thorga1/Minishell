/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:30:02 by tordner           #+#    #+#             */
/*   Updated: 2025/04/19 12:39:55 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*join_path(char *directory, char *cmd)
{
	char	*path;
	size_t	dir_len;
	size_t	cmd_len;
	size_t	total_len;

	dir_len = ft_strlen(directory);
	cmd_len = ft_strlen(cmd);
	total_len = dir_len + cmd_len + 2;
	path = malloc(total_len);
	if (!path)
		return (NULL);
	ft_strcpy(path, directory);
	path[dir_len] = '/';
	ft_strcpy(path + dir_len + 1, cmd);
	return (path);
}

char	*get_path_env(char **envp)
{
	int		i;
	char	*path_env;

	i = 0;
	path_env = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_env = envp[i] + 5;
			break ;
		}
		i++;
	}
	return (path_env);
}

char	*find_command(char **paths, char *cmd)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		full_path = join_path(paths[i], cmd);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}
