/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 03:53:31 by tordner           #+#    #+#             */
/*   Updated: 2025/06/03 04:01:20 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

static int	check_absolute_path(t_cmd *cmd)
{
	struct stat	file_stat;

	if (file_exists(cmd->args[0]) != 0)
	{
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(127);
	}
	if (stat(cmd->args[0], &file_stat) == 0 && S_ISDIR(file_stat.st_mode))
	{
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": Is a directory\n", 2);
		exit(126);
	}
	if (access(cmd->args[0], X_OK) == 0)
		return (1);
	ft_putstr_fd(cmd->args[0], 2);
	ft_putstr_fd(": Permission denied\n", 2);
	exit(126);
}

static void	handle_path_execution(t_cmd *cmd, char **envp)
{
	char	*full_path;
	char	*path_env;

	path_env = get_path_env(envp);
	full_path = execute_ve_2(cmd, path_env, NULL);
	if (full_path)
		execve(full_path, cmd->args, envp);
	ft_putstr_fd("Error: Command execution failed\n", 2);
	exit(126);
}

int	execute_ve(t_cmd *cmd, char **envp)
{
	if (cmd->args[0][0] == '/' || cmd->args[0][0] == '.')
	{
		if (check_absolute_path(cmd))
			execve(cmd->args[0], cmd->args, envp);
	}
	handle_path_execution(cmd, envp);
	return (0);
}
