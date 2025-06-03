/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:25:59 by tordner           #+#    #+#             */
/*   Updated: 2025/06/03 03:05:55 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_parent(int *infile, int pipefd[2], t_cmd *cmd)
{
	if (*infile != STDIN_FILENO)
		close(*infile);
	if (cmd->next)
	{
		close(pipefd[1]);
		*infile = pipefd[0];
	}
	else if (pipefd[0] != -1)
		close(pipefd[0]);
}

int	run_child_pipe(t_cmd *cmd, t_shell *shell, int *infile)
{
	int		pipefd[2];
	pid_t	pid;

	if (cmd->next && pipe(pipefd) == -1)
		return (1);
	else if (!cmd->next)
	{
		pipefd[0] = -1;
		pipefd[1] = STDOUT_FILENO;
	}
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
		handle_child(cmd, *infile, pipefd, shell);
	handle_parent(infile, pipefd, cmd);
	return (0);
}

int	spawn_pipeline(t_cmd *cmd, t_shell *shell)
{
	int		infile;
	int		exit_status;

	shell->child_running = 1;
	shell->signaled = 0;
	set_signal_parent_exec();
	infile = STDIN_FILENO;
	while (cmd)
	{
		if (run_child_pipe(cmd, shell, &infile) != 0)
		{
			shell->child_running = 0;
			set_signal_parent();
			return (1);
		}
		cmd = cmd->next;
	}
	exit_status = 0;
	exit_status = wait_for_children(-1);
	shell->child_running = 0;
	if (g_signal)
		shell->signaled = 1;
	set_signal_parent();
	return (exit_status);
}

void	restore_fds(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}
