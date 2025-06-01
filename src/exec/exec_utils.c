/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 00:42:13 by tordner           #+#    #+#             */
/*   Updated: 2025/06/02 01:03:26 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	setup_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		write(2, "Error creating pipe\n", 21);
		return (1);
	}
	return (0);
}

int	open_file(char *file, int flags, int mode)
{
	int	fd;

	if (!file)
		return (-1);
	fd = open(file, flags, mode);
	if (fd == -1)
	{
		perror(file);
		return (-1);
	}
	return (fd);
}

int	wait_for_children(pid_t last_pid)
{
	int		status;
	int		exit_status;
	pid_t	pid;

	exit_status = 0;
	pid = wait(&status);
	while (pid > 0)
	{
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				exit_status = 128 + WTERMSIG(status);
		}
		pid = wait(&status);
	}
	return (exit_status);
}

void	handle_child(t_cmd *cmd, int infile, int pipefd[2], t_shell *shell)
{
	if (cmd->redir && setup_input_redirections(cmd->redir) != 0)
		exit(1);
	if (!has_input_redirection(cmd->redir))
	{
		if (dup2(infile, STDIN_FILENO) == -1)
			exit(1);
	}
	if (cmd->next && dup2(pipefd[1], STDOUT_FILENO) == -1)
		exit(1);
	if (infile != STDIN_FILENO)
		close(infile);
	if (cmd->next)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
	if (cmd->redir && setup_output_redirections(cmd->redir) != 0)
		exit(1);
	if (is_builtin(cmd->args[0]))
		exit(execute_builtin(cmd, shell));
	execute_ve(cmd, shell->env);
	exit(1);
}
