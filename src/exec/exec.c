/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:25:52 by tordner           #+#    #+#             */
/*   Updated: 2025/06/03 04:11:33 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	file_exists(const char *path)
{
	return (access(path, F_OK));
}

char	*execute_ve_2(t_cmd *cmd, char	*path_env, char	*full_path)
{
	if (!path_env)
	{
		write(2, "Error: PATH not found\n", 22);
		exit(127);
	}
	full_path = find_command(ft_split(path_env, ':'), cmd->args[0]);
	if (!full_path)
	{
		write(2, "Error: Command not found\n", 25);
		exit(127);
	}
	return (full_path);
}

void	run_child_process(t_cmd *cmd, char **envp)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execute_ve(cmd, envp);
}
