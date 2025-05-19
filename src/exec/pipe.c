/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfirmin <lfirmin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 13:25:59 by tordner           #+#    #+#             */
/*   Updated: 2025/05/17 04:25:46 by lfirmin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_child_pipe(int pipefd[2], int infile)
{
	close(pipefd[0]);
	dup2(infile, 0);
	dup2(pipefd[1], 1);
	close(infile);
	close(pipefd[1]);
}

static void	exec_child(t_cmd *cmd, int infile, int pipefd[2], t_shell *shell)
{
	if (cmd->next)
		handle_child_pipe(pipefd, infile);
	else
		dup2(infile, STDIN_FILENO);
	if (cmd->redir)
	{
		if (loop_open_files(cmd) != 0)
			exit(1);
	}
	if (is_builtin(cmd->args[0]))
		exit(execute_builtin(cmd, shell));
	else
		execute_ve(cmd, shell->env);
}

static void	exec_parent(int *infile, int pipefd[2], t_cmd *cmd)
{
	if (*infile != STDIN_FILENO)
		close(*infile);
	if (cmd->next)
	{
		close(pipefd[1]);
		*infile = pipefd[0];
	}
}

static int	spawn_processes(t_cmd *cmd, t_shell *shell, int infile)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;
	int		exit_status;

	while (cmd)
	{
		if (cmd->next)
			pipe(pipefd);
		else
			pipefd[1] = STDOUT_FILENO;
		pid = fork();
		if (pid == 0)
			exec_child(cmd, infile, pipefd, shell);
		else
			exec_parent(&infile, pipefd, cmd);
		cmd = cmd->next;
	}
	
	exit_status = 0;
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			exit_status = 128 + WTERMSIG(status);
	}
	return (exit_status);
}

int	execute_pipeline(t_cmd *cmd_list, t_shell *shell)
{
	int		infile;
	int		exit_status;
	int		redir_status;

	infile = STDIN_FILENO;
	if (cmd_list && !cmd_list->next && is_builtin(cmd_list->args[0]))
	{
		if (cmd_list->redir)
		{
			redir_status = loop_open_files(cmd_list);
			if (redir_status != 0)
				return (shell->exit_status = 1);
		}
		return (shell->exit_status = execute_builtin(cmd_list, shell));
	}
	exit_status = spawn_processes(cmd_list, shell, infile);
	shell->exit_status = exit_status;
	return (exit_status);
}
