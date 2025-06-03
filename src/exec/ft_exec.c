/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 04:08:12 by tordner           #+#    #+#             */
/*   Updated: 2025/06/03 04:09:39 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_child_process(t_cmd *cmd, char **envp)
{
	if (cmd->redir)
	{
		if (loop_open_files(cmd) != 0)
			exit(1);
	}
	run_child_process(cmd, envp);
}

static int	get_exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			return (130);
		return (128 + WTERMSIG(status));
	}
	return (1);
}

int	ft_exec(t_cmd *cmd, char **envp, t_shell *shell)
{
	pid_t	pid;
	int		status;

	shell->child_running = 1;
	pid = fork();
	if (pid == -1)
	{
		write(2, "Error forking process\n", 23);
		shell->child_running = 0;
		return (1);
	}
	if (pid == 0)
		handle_child_process(cmd, envp);
	waitpid(pid, &status, 0);
	shell->child_running = 0;
	return (get_exit_status(status));
}
